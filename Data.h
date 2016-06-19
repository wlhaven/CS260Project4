/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#ifndef DATA_H
#define DATA_H

#include <iostream>

enum ProductType { UNKNOWN = -1, CERAMICS, ELECTRONICS, JEWELRY, PRODUCE, TOYS, WINE };
enum EventType { NO_EVENT = -1, ART_ON_THE_PEARL, BLUES_FESTIVAL, FARMERS_MARKET,
				 ROSE_FESTIVAL, SATURDAY_MARKET, MAX_MARKET };

const int MAX_CHAR = 128;

class Data
{
public:
	Data();
	~Data();
	Data(const Data & aData);
	const Data& operator= (const Data &aData);
	
	//accessor functions
	const char * getVendorName() const;
	const char * getPhoneNumber() const;
	const char * getProductTypeString(ProductType type);
	const char * getEventTypeString(EventType  Event);
	ProductType  getProductType();
	EventType &  getEventType(int count);
	int			 getEventSize();	

	//mutator functions
	void setVendorName(const char * VendorName);
	void setPhoneNumber(const char * PhoneNumber);
	void setProductType(ProductType type);
	void setEventType(const EventType * event, int Size);

	//output functions
	void Display(std::ostream& out);

	// overloaded operators
	bool operator== (const Data& aData) const;
	bool operator< (const Data& aData);
	friend std::ostream& operator<< (std::ostream& out,  Data& aData);

private:
	char * vendorName;
	char * phoneNumber;
	int size;
	ProductType type;
	EventType  event[MAX_MARKET];
};
#endif // !DATA_H