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

#ifndef ASCENSION_RESOURCE_HEADER_
#define ASCENSION_RESOURCE_HEADER_

#include <string>

template<class Type, class Identifier, size_t MaxNum>
class ResourceManager;

////////////////////////////////////////////////////////////////////////////////////
/// @brief Helper class that holds all the reference data for a Resource.
////////////////////////////////////////////////////////////////////////////////////
class ReferenceData {
public:
	ReferenceData() { myCount = 0; };
    virtual ~ReferenceData() {};
    void incRef() { myCount++; };
    void decRef() { myCount--; };
	int getCount() const { return myCount; };

private:
    int myCount;
};

////////////////////////////////////////////////////////////////////////////////////
/// @brief The resource handle class.
///
/// This class hides the actual access to the resources and also implements our
/// way to know if a resource is still referenced or not.
////////////////////////////////////////////////////////////////////////////////////
template<class Type, class Identifier = std::string, size_t MaxNum = 10000>
class Resource
{
public:
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Default constructor
	////////////////////////////////////////////////////////////////////////////////////
	Resource()
	{
		myData = nullptr;
		myIdentifier = Identifier {};
		myManager = nullptr;
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Destructor
	////////////////////////////////////////////////////////////////////////////////////
	~Resource() 
	{
		if (myData)
			myData->decRef();
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Assignment operator
	/// 
	/// @param src The source resource we'll make this resource into.
	/// @return Reference to this resource.
	////////////////////////////////////////////////////////////////////////////////////
	Resource<Type, Identifier, MaxNum> &operator=(const Resource<Type, Identifier, MaxNum> &src)
	{
		if(myData != nullptr)
		{
			myData->decRef();
		}
		myData = src.myData;
		myData->incRef();
		myIdentifier = src.myIdentifier;
		myManager = src.myManager;
		return *this;
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Convert the handle to the real resource.
	///
	/// Get direct access to the actual resource. Use cautionally and don't save away
	/// a reference from this as it might get invalidated if the manager runs out of
	/// memory.
	////////////////////////////////////////////////////////////////////////////////////
	operator Type *() const
	{
		return myManager->getResource(myIdentifier);
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Get reference to the real resource.
	///
	/// Get direct access to the actual resource. Use cautionally and don't save away
	/// a reference from this as it might get invalidated if the manager runs out of
	/// memory.
	////////////////////////////////////////////////////////////////////////////////////
	Type &operator*() const
	{
		return *myManager->getResource(myIdentifier);
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Let us call on a method on a resource.
	///
	/// This is much safer than trying to get direct access to the resource.
	////////////////////////////////////////////////////////////////////////////////////
	Type* operator->() const
	{
		return myManager->getResource(myIdentifier);
	}

private:
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief We only want the appropriate ResourceManager to touch our private parts.
	////////////////////////////////////////////////////////////////////////////////////
	friend class ResourceManager<Type, Identifier, MaxNum>;

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief Constructor which will initialize the values properly.
	///
	/// This method should only be used by ResourceManager when it returns a resource
	/// handle back to the user trough the ResourceManager::Get method.
	/// @param manager The manager which holds the real resource data.
	/// @param data The reference data for this handle.
	/// @param identifier The identifier used for this resource.
	////////////////////////////////////////////////////////////////////////////////////
	Resource(ResourceManager<Type, Identifier, MaxNum> *manager, ReferenceData *data, const Identifier &identifier)
	{
		myManager = manager;
		myIdentifier = identifier;
		myData = data;
		myData->incRef();
	}

	////////////////////////////////////////////////////////////////////////////////////
	/// @brief The manager for this resource.
	////////////////////////////////////////////////////////////////////////////////////
	ResourceManager<Type, Identifier, MaxNum> *myManager;
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief The reference data for this resource.
	////////////////////////////////////////////////////////////////////////////////////
	ReferenceData *myData;
	////////////////////////////////////////////////////////////////////////////////////
	/// @brief The identifier for this resource.
	////////////////////////////////////////////////////////////////////////////////////
	Identifier myIdentifier;
};

#endif // ASCENSION_RESOURCE_HEADER_