/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#ifndef COLLECTION_H
#define COLLECTION_H

#include <iostream>
#include "BST.h"
#include "HashTable.h"

class Collection
{
public:
	Collection();
	Collection(char * fileName);
	Collection(const Collection& otherObject);
	~Collection();

	/** Adds an item into the data structures.
	@pre   Checks to ensure that item is unique before adding to the data structures.
	@post  If the insertion is successful, aData is in its
	 proper position within the table.
	@param aData. The item to add to the table.
	@return  True if item was successfully added, or false if not.
	*/
	bool add(const Data&);

	/** Removes an item from the table.
	@post  If the deletion is successful, aData is removed from the data structures.
	@param searchKey. The item to remove from the table.
	@param match holds a copy of the data prior to the delete for use by client
	@return  True if item was successfully removed, or false if not.
	*/
	bool remove(char * name, Data&);

	/** Sees whether this table contains an item with a given search key.
	@post  table is unchanged.
	@param searchKey  The search key of the item to be retrieved.
	@param match holds a copy of the data for use by client.
	@return  True if an item with the given search key exists in the table.
	*/
	bool retrieve(const char * name, Data&)const;

	/** Sees whether this table contains an item with a given search key.
	@post  table is unchanged.
	@param searchKey  The search key of the item to be retrieved.
	@param match holds a copy of the data for use by client.
	@return  True if an item with the given search key exists in the table.
	*/
	bool retrieve(ProductType productType, Data*);

	/** Displays the items in the BST data structure sorted in descending order by name
	@post Displays the table contents
	*/
	void displayByName()const;

	/** Displays the items in the table  data structuresorted in descending order by product
	@post Displays the table contents
	*/
	void displayByProductType();

	/** Displays the vendors whose products have been retrieved
	@param arrayVendor client supplied array
	@post Displays vendor information*/
	void printProducts(Data arrayVendor[]);

	/** Saves the data to a flat file 
	@post  data writen to file
	*/
	void saveData(char * fileName) const;

	/** Gets the height of the tree
	@return the length of the tree
	*/
	void getHeight();


private:
	BST tree;
	HashTable table;

	char fileName[MAX_CHAR];
	void loadData();	
};
#endif
