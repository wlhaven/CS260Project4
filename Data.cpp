/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#include "Data.h"
#include <cstring>

Data::Data() : vendorName(nullptr), phoneNumber(nullptr), size(0), type(UNKNOWN)
{
	for (int i = 0; i < MAX_MARKET; i++)
		event[i] = NO_EVENT;
}

Data::~Data()
{
	if (vendorName)
		delete[] vendorName;
	if (phoneNumber)
		delete[] phoneNumber;
}

Data::Data(const Data & aData)
{
	if (this == &aData)
		return;

	setVendorName(aData.vendorName);
	setPhoneNumber(aData.phoneNumber);
	setProductType(aData.type);
	setEventType(aData.event,aData.size);
}

const Data & Data::operator=(const Data & aData)
{
	if (this == &aData)
		return *this;
	else
	{
		setVendorName(aData.vendorName);
		setPhoneNumber(aData.phoneNumber);
		setProductType(aData.type);
		setEventType(aData.event, aData.size);
		return *this;
	}
}

const char * Data::getVendorName() const
{
	return this->vendorName;
}

const char * Data::getPhoneNumber() const
{
	return this->phoneNumber;
}

const char * Data::getProductTypeString(ProductType type)
{
	switch (type) {
	case CERAMICS:
		return "Ceramics";
	case ELECTRONICS:
		return "Electronics";
	case JEWELRY:
		return "Jewelry";
	case PRODUCE:
		return "Produce";
	case TOYS:
		return "Toys";
	case WINE:
		return "Wine";
	default:
		return "?";
	}
}

const char * Data::getEventTypeString(EventType  Event)
{
	switch (Event)
	{
	case ART_ON_THE_PEARL:
		return "Art on the Pearl";
	case BLUES_FESTIVAL:
		return "Blues Festival";
	case FARMERS_MARKET:
		return "Farmer's Market";
	case ROSE_FESTIVAL:
		return "Rose Festival";
	case SATURDAY_MARKET:
		return "Saturday Market";
	default:
		return "?";
	}
}

ProductType Data::getProductType()
{
	return type;
}

EventType & Data::getEventType(int count)
{
	return event[count];
}

int Data::getEventSize()
{
	return size;
}

void Data::setVendorName(const char * VendorName)
{
	if (this->vendorName)
		delete[] vendorName;
	this->vendorName = new char[strlen(VendorName) + 1];
	strcpy(this->vendorName, VendorName);
	
}

void Data::setPhoneNumber(const char * PhoneNumber)
{
	if (this->phoneNumber)
		delete[] phoneNumber;
	this->phoneNumber = new char[strlen(PhoneNumber) + 1];
	strcpy(this->phoneNumber, PhoneNumber);
}

void Data::setProductType(ProductType Type)
{
	this->type = Type;
}


void Data::setEventType(const EventType * Event, int Size)
{
	for (int i = 0; i < Size; i++)
	{
		this->event[i] = Event[i];
	}
	this->size = Size;
}


void Data::Display(std::ostream & out) 
{
	EventType tmp;
	out << "\nVendor Name: " << "\t\t" << vendorName
		<< "\nPhone number: " << "\t\t" << phoneNumber
		<< "\nProduct: " << "\t\t" << getProductTypeString(type);
	out << "\nEvents: " << "\t\t";
		for (int i = 0; i < getEventSize(); i++)
		{
			tmp = getEventType(i);
			out << getEventTypeString(tmp) << " - ";
		}
}

bool Data::operator==(const Data & aData) const
{
	bool flag = false;
	if (strcmp(this->getVendorName(), aData.getVendorName()) == 0)
		flag = true;

	return flag;
}

bool Data::operator<(const Data & aData)
{
	bool flag = false;

	if (strcmp(this->vendorName, aData.vendorName) < 0)
		flag = true;
	return flag;
}

std::ostream & operator<<(std::ostream & out, Data & aData)
{
	aData.Display(out);
	return out;
}


