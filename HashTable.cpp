/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#include "HashTable.h"
#include <cstring>
#include <fstream>


HashTable::HashTable()
{
	initialize();
}

HashTable::HashTable(char * fileName)
{
	initialize();
	strcpy(this->fileName, fileName);
}

HashTable::HashTable(const HashTable & aHashTable)
{
	table = new Node*[maxSize];

	//copy the array of linked list
	for (size_t i = 0; i < maxSize; i++)
	{
		//copy each linked list in the array
		if (aHashTable.table[i] == nullptr)
			table[i] = nullptr;
		else
		{
			//copy the first node in current chain
			table[i] = new Node();
			table[i]->data = aHashTable.table[i]->data;

			//copy the rest of the chain
			Node* srcNode = aHashTable.table[i]->next;
			Node* destNode = table[i];
			while (srcNode)
			{
				destNode->next = new Node();
				destNode->next->data = srcNode->data;
				destNode = destNode->next;
				srcNode = srcNode->next;
			}
			destNode->next = nullptr;
		}
	}
}

HashTable::~HashTable()
{
	destroy();
}

const HashTable & HashTable::operator=(const HashTable & aHashTable)
{
	if (this == &aHashTable)
		return *this;
	else
	{
		//release dynamically allocated memory held by current object
		destroy();

		//make *this a deep copy of "aHashTable"
		table = new Node*[maxSize];
		maxSize = aHashTable.maxSize;
		currentSize = aHashTable.currentSize;

		//copy the array of linked list
		for (size_t i = 0; i < maxSize; i++)
		{
			//copy each linked list in the array
			if (aHashTable.table[i] == nullptr)
				table[i] = nullptr;
			else
			{
				//copy the first node in current chain
				table[i] = new Node();
				table[i]->data = aHashTable.table[i]->data;

				//copy the rest of the chain
				Node * srcNode = aHashTable.table[i]->next;
				Node * destNode = table[i];
				while (srcNode)
				{
					destNode->next = new Node();
					destNode->next->data = srcNode->data;
					destNode = destNode->next;
					srcNode = srcNode->next;
				}
				destNode->next = nullptr;
			}
		}
		return *this;
	}
}

bool HashTable::insert(Data * aData)
{
	bool flag = false;
	bool retVal = false;

	//calculate the insertion position (the index of the array)
	size_t index = calculateIndex(aData->getVendorName());
	//check for duplicate entries in the chain.
	retVal = searchTable(aData->getVendorName());
	
	if (!retVal)
	{
		Node * curr = table[index];
		Node * prev = nullptr;

		while (curr != nullptr && *curr->data->getVendorName() < *aData->getVendorName())
		{
			prev = curr;
			curr = curr->next;
		}

		Node* newNode = new Node();
		newNode->data = aData;
		newNode->next = curr;

		if (prev == nullptr)
		{
			curr = table[index] = newNode;
		}
		else
		{
			prev->next = newNode;
		}
		currentSize++;
		flag = true;
	}
	return flag;
}

bool HashTable::remove(char const * const searchKey)
{
	bool flag = false;
	//calculate the removal position (the index of the array)
	size_t index = calculateIndex(searchKey);

	//search for the data to be removed in the chain (linked list)
	Node* curr = table[index];
	Node* prev = nullptr;

	while (curr)
	{
		if (strcmp(searchKey, curr->data->getVendorName()) == 0)
		{
			//find match and remove the node
			if (!prev)
				table[index] = curr->next;
			else
				prev->next = curr->next;

			delete curr; 
			currentSize--;
			flag = true;
			curr = nullptr;
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
	return flag;
}

bool HashTable::retrieve(ProductType aType, Data * aData)
{
	bool flag = false;
	int count = 0;

	for (size_t index = 0; index < maxSize; index++)
	{
		for (Node * curr = table[index]; curr; curr = curr->next)
		{
			if (curr && aType == curr->data->getProductType())
			{
				aData[count] = *curr->data;
				flag = true;
				count++;
				arraySize++;
			}
		}
	}
	return flag;
}

void HashTable::initialize()
{
	maxSize = DEFAULT_TABLE_SIZE;
	table = new Node*[maxSize];

	for (size_t i = 0; i < maxSize; i++)
	{
		table[i] = nullptr;
	}
	currentSize = 0;
	arraySize = 0;
}

void HashTable::destroy()
{
	Node * curr;
	for (size_t index = 0; index < maxSize; index++)
	{
		while (table[index])
		{
			curr = table[index]->next;
			delete table[index];
			table[index] = curr;
		}
	}
	delete[] table;

}

size_t HashTable::calculateIndex(char const * const searchKey)const
{
	size_t total = 0;
	const char * p = searchKey;
	while (*p != '\0')
	{
		total = (total * 32) + *p;
		p++;
	}
	return total % maxSize;
}

bool HashTable::searchTable(char const * const searchKey)
{
	bool flag = false;

	//calculate the retrieval position (the index of the array)
	size_t index = calculateIndex(searchKey);

	//search for the data in the chain (linked list)
	Node* curr = table[index];
	while (curr)
	{
		if (strcmp(searchKey, curr->data->getVendorName()) == 0)
		{
			//find match and return found
			curr = nullptr;
			flag = true;
		}
		else
			curr = curr->next;
	}
	delete curr;
	return flag;
}

void HashTable::display() const
{
	std::cout << std::endl;
	for (size_t index = 0; index < maxSize; index++)
	{
		std::cout << "Chain #" << index << ": " << std::endl;
		for (Node * curr = table[index]; curr; curr = curr->next)
		{
			std::cout << *curr->data << std::endl;
		}
		std::cout << std::endl;
	}
}

void HashTable::printProducts(Data  arrayVendor[])
{
	for (int i = 0; i < arraySize; i++)
	{
		std::cout << std::endl << arrayVendor[i];
	}
	arraySize = 0;
}

void HashTable::printVendorsByProducts()
{
	int count = 0;
	int minIndex;
	int location;
	Data tmpArray[MAX_SIZE];
	Data temp;

	for (size_t index = 0; index < maxSize; index++)
	{
		for (Node * curr = table[index]; curr; curr = curr->next)
		{
			tmpArray[count] = *curr->data;
			count++;
		}

	}
	for (int index = 0; index < count; index++)
	{
		minIndex = index;
		for (location = index + 1; location < count; location++)
		{
			if (tmpArray[location].getProductType() <= tmpArray[minIndex].getProductType())
			{
				minIndex = location;
			}
		}
		if (minIndex != index)
		{
			temp = tmpArray[minIndex];
			tmpArray[minIndex] = tmpArray[index];
			tmpArray[index] = temp;
		}
	}

	for (int index = 0; index < count; index++)
	{
		std::cout << tmpArray[index] << std::endl;;
	}
}

void HashTable::monitor() const
{
	for (size_t index = 0; index < maxSize; index++)
	{
		Node * curr = table[index];
		int nodeCount = 0;
		while (curr)
		{
			nodeCount++;
			curr = curr->next;
		}

		if (nodeCount == 0)
		{
			std::cout << "Chain #" << index << ":  " << "\n   There are " << nodeCount
				<< " nodes in this chain" << std::endl;
		}
		else if (nodeCount == 1)
		{
			std::cout << "Chain #" << index << ":  " << "\n   There is " << nodeCount
				<< " node in this chain, resulting in " << nodeCount - 1
				<< " collisions" << std::endl;
		}
		else
		{
			std::cout << "Chain #" << index << ":  " << "\n   There are " << nodeCount
				<< " nodes in this chain, resulting in " << nodeCount
				<< " collisions" << std::endl;
		}

		std::cout << std::endl;
	}
}
