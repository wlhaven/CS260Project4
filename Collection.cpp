/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#include "Collection.h"
#include <cstring>

Collection::Collection()
{
}

Collection::Collection(char * fileName)
{
	strcpy(this->fileName, fileName);
	loadData();
}

Collection::Collection(const Collection & otherObject)
{
	tree = otherObject.tree;
	table = otherObject.table;
}

Collection::~Collection()
{
//	saveData();
}

bool Collection::add(const Data & item)
{
	bool flag = false;
	Data * ptrItem = new Data;
	*ptrItem = item;	//make a deep copy

	flag = table.insert(ptrItem);
	if (flag)
		flag = tree.add(ptrItem);
	else
		delete ptrItem;  // data was not added to collection so remove the data.
	return flag;
}

bool Collection::remove(char * name, Data & match)
{	
	table.remove(name);
	return tree.remove(name, match);
}

bool Collection::retrieve(const char * name, Data & match) const
{
	return tree.retrieve(name, match);
}

bool Collection::retrieve(ProductType productType, Data * vendor)
{
	return table.retrieve(productType,  vendor);
}

void Collection::displayByName() const
{
	tree.listAll();
}

void Collection::displayByProductType() 
{
	table.printVendorsByProducts();
}

void Collection::printProducts(Data arrayVendor[])
{
	table.printProducts(arrayVendor);
}

void Collection::loadData()
{
	std::ifstream	in;
	EventType  eventType[MAX_MARKET];
	Data 	newData;
	char	vendorName[MAX_CHAR] = {};
	char	phoneNumber[MAX_CHAR] = {};
	int		type;
	int		getEvent = 0;
	int		numEvents = 0;
	

	in.open(this->fileName);
	if (!in)
	{
		std::cerr << "Fail to open " << fileName << " for input!" << std::endl;
		exit(1);
	}

	in.get(vendorName, MAX_CHAR, ';');
	while (!in.eof())
	{
		in.ignore(MAX_CHAR, ';');
		in.get(phoneNumber, MAX_CHAR, ';');
		in.ignore(MAX_CHAR, ';');
		in >> type;
		in.ignore(MAX_CHAR, ';');
		in >> numEvents;
		in.ignore(MAX_CHAR, ';');
		for (int i = 0; i < numEvents; i ++)
		{
			in >> getEvent;
			eventType[i] = static_cast<EventType>(getEvent);
		}
		in.ignore(MAX_CHAR, ';');
		in.ignore(MAX_CHAR, '\n');

		newData.setVendorName(vendorName);
		newData.setPhoneNumber(phoneNumber);
		newData.setProductType(static_cast <ProductType>(type));
		newData.setEventType(eventType, numEvents);

		add(newData);

		in.get(vendorName, MAX_CHAR, ';');
	}
	in.close();
}

void Collection::saveData(char * fileName) const
{
	tree.saveData(fileName);
}

void Collection::getHeight()
{
	int height;
	height = tree.height();
	std::cout << "\nTree has a height of:  " << height;

}

