/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "Data.h"
#include <iostream>

class HashTable
{
public:
	HashTable();
	HashTable(char * fileName);
	HashTable(const HashTable & aHashTable);
	~HashTable();
	const HashTable& operator= (const HashTable & aHashTable);
	
	/** Inserts an item into the table.
	@post  If the insertion is successful, aData is in its
	proper position within the table.
	@param aData. The item to add to the table.
	@return  True if item was successfully added, or false if not.
	*/
	bool insert(Data * aData);

	/** Removes an item from the table.
	@post  If the deletion is successful, aData is removed from the table.
	@param searchKey. The item to remove from the table.
	@return  True if item was successfully removed, or false if not.
	*/
	bool remove(char const * const searchKey);

	/** Sees whether this table contains an item with a given
	search key.
	@post  table is unchanged.
	@param searchKey  The search key of the item to be retrieved.
	@return  True if an item with the given search key exists in the table.
	*/
	bool retrieve(ProductType aType, Data * aData);

	/** Displays the items in the table
	@post Displays the table contents
	*/
	void display() const;

	/** Displays the vendors whose products have been retrieved
	@param arrayVendor client supplied array
	@post Displays vendor information
	*/
	void printProducts(Data arrayVendor[]);

	/** Displays the vendors in the table sorted in descending order by product
	@post Displays the table contents
	*/
	void printVendorsByProducts();
	
	/** Displays the table distribution of the linked chains in the table
	@post Displays the number of nodes in a chain and number of collsions that
	occurred during the insertion. 
	*/
	void monitor() const;

private:
	struct Node
	{
		Data *  data;
		Node *	next;
		Node() : data(nullptr), next(nullptr) {};
	};

	Node **table;
	
	const static int MAX_SIZE = 128;
	const static int DEFAULT_TABLE_SIZE = 7;
	size_t	maxSize;
	int		currentSize;
	int		arraySize;
	char	fileName[MAX_SIZE];	

	//private helper functions for the class
	void initialize();
	void destroy();
	size_t calculateIndex(char const * const searchKey) const;
	bool searchTable(char const * const searchKey);

};

#endif // !HASHTABLE_H
