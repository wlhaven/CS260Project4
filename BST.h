/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#ifndef BST_H
#define BST_H
#include "Data.h"
#include <fstream>

class BST
{
public:
	BST();
	BST(const char * fileName);
	BST(const BST& aBST);
	void operator= (const BST& aBST);
	~BST();

	/** Adds an item into the tree.
	@post  If the insertion is successful, aData is in its
	proper position within the tree.
	@param aData. The item to add to the tree.
	@return  True if item was successfully added, or false if not.
	*/
	bool add(Data * aData);

	/** Removes an item from the tree.
	@post  If the deletion is successful, aData is removed from the tree.
	@param searchKey. The item to remove from the tree.
	@param match holds a copy of the data prior to the delete for use by client
	@return  True if item was successfully removed, or false if not.
	*/
	bool remove(const char* searchKey, Data& match);

	/** Sees whether the tree contains an item with a given search key.
	@post  tree is unchanged.
	@param searchKey  The search key of the item to be retrieved.
	@param match holds a copy of the data for use by client.
	@return  True if an item with the given search key exists in the table.
	*/
	bool retrieve(const char* searchKey, Data& match) const;

	/** Displays the items in the tree in order fashion.
	@post Displays the tree contents
	*/
	void listAll() const;
	
	/** Gets the number of nodes in the tree
	@return the size of the tree
	*/
	int getSize() const;

	/** Gets the smallest data element in the tree
	@param smallest Data reference to hold the smallest data item
	@post client has an object with smallest data.
	*/
	void getSmallest(Data & smallest) const;
	/** Saves the data to a flat file
	@post  data writen to file
	*/
	void saveData(char * fileName) const;

	/** Gets the height of the tree
	@return the length of the tree
	*/
	int height();

private:
	struct Node
	{		
		Data * data;
		Node * left, * right;
		Node() : data(nullptr), left(nullptr), right(nullptr) {};
		~Node() { delete data; data = nullptr; }
	};

	Node * root;
	int size;
	char fileName[MAX_CHAR];

	//private helper functions for the class
	void init();
	bool add(Node *& currRoot,  Data * aData);	
	void destroy(Node *& currRoot);
	void copy(Node * srcRoot, Node*& destRoot);
	bool retrieve(Node * currRoot, const char* id, Data& match) const;
	bool remove(Node *& currRoot, const char* id, Data& match);
	void deleteNode(Node *& currRoot);
	int getSize(Node * currRoot) const;
	Node * getSmallest(Node * currRoot) const;
	void listAll(Node * currRoot) const;
	void saveData(std::ofstream& out) const;
	void saveData(Node * currRoot, std::ofstream& out) const;
	void printLeaves(Node * currRoot) const;
	int BST::height(Node * root);
};
#endif