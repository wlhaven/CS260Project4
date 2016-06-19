/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
of a collection.
Date Due:	06-06-2016
*/

#include "Util.h"
#include <iostream>

using namespace std;

void displayMenu()
{
	cout << "\n\t  Welcome to CS260 Vendor Locator System! " << endl;
	cout << "\n\t\tImplemented by: Wally Haven" << endl << endl;
	cout << "\t\t(A) Add a vendor." << endl
		<< "\t\t(D) Delete a vendor." << endl
		<< "\t\t(S) Search for a vendor by name." << endl
		<< "\t\t(R) Retrieve vendors by productType." << endl
		<< "\t\t(N) Display vendors by name" << endl
		<< "\t\t(P) Display vendors sorted by product types" << endl
		<< "\t\t(X) Get the height of the binary tree" << endl
		<< "\t\t(Q) Quit the application" << endl << endl;
}

char getCommand()
{
	char cmd;
	cout << "Please enter your choice (A, D, S, R, N, P, X or Q):";
	cin >> cmd;
	cin.ignore(MAX_LEN, '\n');
	return tolower(cmd);
}
void executeCmd(char command, Collection & aCollection)
{
	Data vendor;
	Data arrayVendor[MAX_LEN];
	ProductType type{};
	int tmpType;
	char key[MAX_LEN];
	bool flag = false;

	switch (command)
	{
	case 'a':
		getData(vendor);
		flag = aCollection.add(vendor);
		if (flag)
			cout << endl << "The vendor " << vendor.getVendorName()
			<< " has been added to the database. " << endl;
		else
			cout << endl << "The vendor " << vendor.getVendorName()
			<< " was not added to the database" << endl;
		pause();
		break;

	case 'd':
		getString("\nPlease enter the name of the vendor you want to remove: ", key);
		flag = aCollection.remove(key, vendor);
		if (flag)
			cout << endl << "The vendor \"" << key << "\" has been removed from the database. " << endl
			<< endl << "Information about " << key << ": " << endl << '\t' << vendor << endl;
		else
			cout << endl << "Unable to remove \"" << key << "\" from the database. " << endl;
		pause();
		break;
	case 's':
		getString("\nPlease enter the name of the vendor you wish to retrieve: ", key);
		flag = aCollection.retrieve(key, vendor);
		if (flag)
			cout << "\nThe vendor \"" << key << "\" was found in the database."
			<< endl << "Information about " << key << ": " << endl << '\t' << vendor << endl;
		else
			cout << endl << "There is no information about " << key << "; " << endl;
		pause();
		break;
	case 'r':
		cout << "\nPlease select a product to find vendors that carry the product. ";
		displayProductTypes();
		tmpType = getInt("\t\t ");
		tmpType -= 1;
		type = static_cast<ProductType>(tmpType);
		flag = aCollection.retrieve(type, arrayVendor);
		if (flag)
		{
			cout << "\nThe product \"" << vendor.getProductTypeString(type) << "\" was found in the database."
				<< endl << "Vendors who carry this product: ";
			aCollection.printProducts(arrayVendor);
			cout << endl;
		}
		else
			cout << endl << "There is no information about " << vendor.getProductTypeString(type) << ". " << endl;
		pause();
		break;
	case 'n':
		aCollection.displayByName();
		pause();
		break;
	case 'p':
		cout << endl;
		aCollection.displayByProductType();
		pause();
		break;
	case 'x':
		cout << endl;
		aCollection.getHeight();
		pause();
		break;
	default:
		cout << "illegal command!" << endl;
		cout << "\nPress <Enter> to continue:  ";
		cin.get();
		break;
	}
}

void getData(Data & aVendor)
{
	EventType  eventType[MAX_MARKET];
	char	vendor[MAX_LEN];
	char	phoneNumber[MAX_LEN];
	char	ans = 'y';
	int		tmpType = 0;
	int		numEvents = 0;
	ProductType type;

	cout << "\nPlease enter information about the vendor: " << endl;
	getString("\tVendor name: ", vendor);
	getString("\tPhone number: ", phoneNumber);
	cout << "\tSelect the product the vendor sells:";
	displayProductTypes();
	tmpType = getInt("\t\t ");
	tmpType -= 1;
	type = static_cast<ProductType>(tmpType);
	cout << "\tSelect the events that the vendor attends:";
	while (ans == 'y')
	{
		displayEventTypes();
		tmpType = getInt("\t\t ");
		tmpType -= 1;
		eventType[numEvents] = static_cast<EventType>(tmpType);
		numEvents++;
		if (numEvents > SATURDAY_MARKET)
		{
			cout << "\nMaximum number of events vendor can attend reached. ";
			break;
		}
		cout << "\nDo you wish to add another event? y/n  ";
		cin >> ans;
		ans = tolower(ans);
	}
	aVendor.setVendorName(vendor);
	aVendor.setPhoneNumber(phoneNumber);
	aVendor.setProductType(type);
	aVendor.setEventType(eventType, numEvents);
}

void displayProductTypes()
{
	cout << "\n\t\tAvailable products:" << endl;
	cout << endl << "\t\t(1) Ceramics";
	cout << endl << "\t\t(2) Electronics";
	cout << endl << "\t\t(3) Jewelry";
	cout << endl << "\t\t(4) Produce";
	cout << endl << "\t\t(5) Toys";
	cout << endl << "\t\t(6) Wine";
	cout << endl;
}

void displayEventTypes()
{
	cout << "\n\t\tAvailable events:" << endl;
	cout << endl << "\t\t(1) Art on the Pearl";
	cout << endl << "\t\t(2) Blue's Festival";
	cout << endl << "\t\t(3) Farmer's Market";
	cout << endl << "\t\t(4) Rose Festival";
	cout << endl << "\t\t(5) Saturday Market";
	cout << endl;
}

int getInt(const char * prompt)
{
	int temp;
	cout << prompt;
	cin >> temp;
	while (!cin)
	{
		cin.clear();
		cin.ignore(MAX_LEN, '\n');
		cout << "Illegal input -- try again: ";
		cin >> temp;
	}
	cin.ignore(MAX_LEN, '\n');
	return temp;
}

double getDouble(const char * prompt)
{
	double temp;
	cout << prompt;
	cin >> temp;
	while (!cin)
	{
		cin.clear();
		cin.ignore(MAX_LEN, '\n');
		cout << "Illegal input -- try again: ";
		cin >> temp;
	}
	cin.ignore(MAX_LEN, '\n');
	return temp;
}

void getString(const char * prompt, char * input)
{
	cout << prompt;
	cin.get(input, MAX_LEN, '\n');
	cin.ignore(MAX_LEN, '\n');
}

void pause()
{
	cout << "\n\nPress <Enter> to continue:\n";
	cin.get();
}
