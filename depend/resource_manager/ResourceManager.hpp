/* This file is part of Groogy's SFML Utilities.
 *
 * Groogy's SFML Utilities is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Groogy's SFML Utilities is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Groogy's SFML Utilities.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ASCENSION_RESOURCEMANAGER_HEADER_
#define ASCENSION_RESOURCEMANAGER_HEADER_

#include <SFML/System/Lock.hpp>
#include <SFML/System/Mutex.hpp>
#include <string>

#ifdef _DEBUG
#include <iostream>
#endif

#include "MemoryPool.hpp"
#include "Resource.hpp"
#include "../../ErrorHandler.hpp"

////////////////////////////////////////////////////////////////////////////////////
/// @brief Abstract class for managing resources.
///
/// Instances of this class will manage a set of resources. You can set what type
/// for it to manage, what type for symbol, and the size of the memory pool.
/// The twist to this manager is that it also counts the references of the resources
/// and the only access to them is on-demand trough the symbol(but this is hidden
/// trough the Resource class) so we don't need to know if they are loaded or not.
////////////////////////////////////////////////////////////////////////////////////
template<class Type, class Identifier = std::string, size_t MaxNum = 10000>
class ResourceManager
{
public:
	////////////////////////////////////////////////////////////////////////////////////
    /// @brief Exception class
    ////////////////////////////////////////////////////////////////////////////////////
    class Error : public std::exception {};

    ////////////////////////////////////////////////////////////////////////////////////
    /// @brief Exception class for when load returned false.
    ////////////////////////////////////////////////////////////////////////////////////
    class LoadError : public Error {};

	////////////////////////////////////////////////////////////////////////////////////
    /// @brief Exception class for when unload returned false.
    ////////////////////////////////////////////////////////////////////////////////////
    class UnloadError : public Error {};

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Default constructor
	////////////////////////////////////////////////////////////////////////////////////
	ResourceManager() : myMemory(sizeof(Type) * MaxNum)
	{
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Destructor
	////////////////////////////////////////////////////////////////////////////////////
	~ResourceManager() 
	{
		for(ResourceList::iterator it = myResources.begin(), end = myResources.end(); it != end; it++)
		{
			if (unload(*it->second, it->first) == false)
			{
				Keiyaku::ErrorHandler::reportError("~ResourceManager(): Failed to unload resource");
			}
			myMemory.FreeMemory(it->second);
		}
		myReferences.clear();
		myResources.clear();
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Get a handle to the wanted resource
	///
	/// This is the only method you need to use. It will always return a resource handle.
	/// It will check if the resource is already loaded and return it otherwise it will
	/// load the object and return that. This method can throw several different
	/// exceptions. The concerned exceptions are:
	///  * ResourceManager::LoadError
	///  * ResourceManager::UnloadError
	///  * MemoryPool::AllocationError
	///  * MemoryPool::InsufficentMemoryError
	///
	/// @param id The identifier for the resource. This parameter will be passed to the
	///           Load and Unload methods too.
	/// @return The resource handle that you access the resource trough.
	////////////////////////////////////////////////////////////////////////////////////
	Resource<Type, Identifier, MaxNum> get(const Identifier &id)
	{
		sf::Lock lock(myMutex);
		ReferenceList::iterator it = myReferences.find(id);
		if(it != myReferences.end())
		{
			if(it->second.getCount() > 0)
			{
				return Resource<Type, Identifier, MaxNum>(this, &it->second, id);
			}
			else
			{
				ReferenceData &data = it->second;
				if(myResources.find(id) == myResources.end())
				{
					createObject(id);
				}
				return Resource<Type, Identifier, MaxNum>(this, &data, id);
			}
		}
		else
		{
			myReferences.insert(std::pair<Identifier, ReferenceData>(id, ReferenceData()));
			ReferenceData &data = myReferences[id];
			createObject(id);
			return Resource<Type, Identifier, MaxNum>(this, &data, id);
		}		
	}

protected:
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief We make Resource a friend so that it can retrieve the real resource data.
	////////////////////////////////////////////////////////////////////////////////////
	friend class Resource<Type, Identifier, MaxNum>;

	Type *getResource(const Identifier &id) const
	{
		return myResources.find(id)->second;
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Defines how to load the resource.
	/// 
	/// If this method returns false then a LoadError exception will be thrown.
	/// In this method you should define how to load the actual resource.
	/// @param resource The allocated resource object.
	/// @param id The identifier that was used in Get.
	/// @return True if the resource loading succeeded.
	////////////////////////////////////////////////////////////////////////////////////
	virtual bool load(Type &resource, const Identifier &id) const = 0;

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Defines how to unload the resource.
	/// 
	/// If this method returns false then a UnloadError exception will be thrown.
	/// In this method you should define how to unload the actual resource. For most
	/// resources it will be enough with the default implementation which calls on the
	/// resource destructor.
	/// @param resource The allocated resource object.
	/// @param id The identifier that was used in Get.
	/// @return True if the resource unloading succeeded.
	////////////////////////////////////////////////////////////////////////////////////
	virtual bool unload(Type &resource, const Identifier &id)
	{
		(void)id; //fix warning C4100: 'id': unreferenced formal parameter
		resource.~Type();
		return true;
	}

private:
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief The resource list type
	////////////////////////////////////////////////////////////////////////////////////
	using ResourceList = std::map<Identifier, Type *>;
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief The reference list type
	////////////////////////////////////////////////////////////////////////////////////
	using ReferenceList = std::map<Identifier, ReferenceData>;

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Allocate a resource instance for the specified identifier.
	///
	/// @param id The identifier passed trough Get.
	////////////////////////////////////////////////////////////////////////////////////
	void createObject(const Identifier &id)
	{
		void *memory = getMemory();
		auto *object = new(memory) Type();
		if(load(*object, id) == false) throw LoadError();
		myResources.insert(std::pair<Identifier, Type *>(id, object));
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Get a pointer to free memory. 
	///
	/// Will try and allocate enough memory for a new resource and return it. If there
	/// is not enough memory then it will go trough all the current resources and check
	/// if they are in use. if they are not in use then they will be unloaded to be
	/// replaced with a new resource.
	////////////////////////////////////////////////////////////////////////////////////
	void *getMemory()
	{
		if(myMemory.CanAllocate(sizeof(Type)) == false)
		{
			ResourceList::iterator resourceEnd = myResources.end();
			for(ReferenceList::iterator it = myReferences.begin(), end = myReferences.end(); it != end; it++)
			{
				ResourceList::iterator resourceIterator = myResources.find(it->first);
				if(resourceIterator != resourceEnd) // If the object is still allocated.
				{
					if(it->second.getCount() <= 0)
					{
						if(unload(*resourceIterator->second, it->first) == false)
						{
							throw UnloadError();
						}
						myMemory.FreeMemory(resourceIterator->second);
						myResources.erase(resourceIterator);
					}
				}
			}
		}

		return myMemory.GetMemory(sizeof(Type));
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief The managers memory pool
	////////////////////////////////////////////////////////////////////////////////////
	MemoryPool myMemory;
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief The list with all allocated resources.
	////////////////////////////////////////////////////////////////////////////////////
	ResourceList myResources;
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief List with all reference data for each resources.
	////////////////////////////////////////////////////////////////////////////////////
	ReferenceList myReferences;
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Mutex to make the manager thread-safe.
	////////////////////////////////////////////////////////////////////////////////////
	sf::Mutex myMutex;

};

#endif // ASCENSION_RESOURCEMANAGER_HEADER_