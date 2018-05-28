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

#include "MemoryPool.hpp"
#include <cstdlib>

MemoryPool::MemoryPool(size_t size) 
{
    mySize = size;
    myMemory = malloc(size);
	if(myMemory == nullptr) throw AllocationError();
}

MemoryPool::~MemoryPool() 
{
    free(myMemory);
}

void * MemoryPool::GetMemory(size_t size) 
{
    void * memory = FindFreeMemory(size);
    if(memory != nullptr) {
		myPointers.insert(std::pair<void *, size_t>(memory, size));
        return memory;
    } else {
        throw InsufficentMemoryError();
    }
}

void MemoryPool::FreeMemory(void * memory) 
{
	auto it = myPointers.find(memory);
	if(it == myPointers.end()) throw InvalidPointerError();
	myPointers.erase(it);
}

size_t MemoryPool::GetSize() const 
{
	return mySize;
}

bool MemoryPool::CanAllocate(size_t size) const 
{
	return FindFreeMemory(size) != nullptr;
}

void * MemoryPool::FindFreeMemory(size_t size) const 
{
	auto it = myPointers.begin(), end = myPointers.end(), last = it;
    void * memory = nullptr; size_t pointersSize = myPointers.size();

    if(pointersSize > 0) 
	{
        for(it++; it != end; it++, last++) 
		{
            if(((size_t)it->first) - ((size_t)last->first + last->second) > size) 
			{
                memory = (void *) (((size_t)last->first) + last->second + 1);
                break;
            }
        }
    }

    if(pointersSize == 0) 
	{
        memory = myMemory;
    } 
	else if(it == end) 
	{
        it--;
        memory = (void *) (((size_t)it->first) + it->second + 1);
        if((size_t)memory + size > (size_t)myMemory + mySize) memory = nullptr;
    }

	return memory;
}