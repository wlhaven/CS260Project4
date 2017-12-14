/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016
*/

#include "BST.h"
#include <cstring>

BST::BST()
{
	init();
}
BST::BST(const char * fileName)
{
	init();
	strcpy(this->fileName, fileName);
}
BST::BST(const BST& aBST) : root(nullptr), size(0)
{
	*this = aBST;
}
void BST::operator=(const BST& aBST)
{
	if (this == &aBST)
		return;
	if (this->root)
	{
		destroy(this->root);
	}
	copy(aBST.root, this->root);
	this->size = aBST.size;
	strcpy(this->fileName, aBST.fileName);
}

void BST::copy(Node * srcRoot, Node *& destRoot)
{
	if (!srcRoot)
	{
		destRoot = nullptr;
	}
	else
	{
		destRoot = new Node();
		destRoot->data = srcRoot->data;
		copy(srcRoot->left, destRoot->left);
		copy(srcRoot->right, destRoot->right);
	}
}

void BST::init()
{
	root = nullptr;
	size = 0;
}


BST::~BST()
{
	destroy(root);
}

void BST::destroy(Node *& currRoot)
{
	if (currRoot)
	{
		destroy(currRoot->left);
		destroy(currRoot->right);		
		delete currRoot;
		currRoot = nullptr;
	}	
}

bool BST::add(Data * aData)
{
	return add(root, aData);
}

bool BST::add(Node *& currRoot, Data * aData)
{
	bool flag = false;
	if (!currRoot)
	{
		Node * newNode = new Node();
		currRoot = newNode;
		currRoot->data = aData;
		size++;
		return true;
	}
	if (*aData < *currRoot->data)
	{
		add(currRoot->left, aData);
		flag = true;
	}
	else
	{
		add(currRoot->right, aData);
		flag = true;
	}	
	return flag;
}

bool BST::retrieve(const char * key, Data& match)  const
{
	return retrieve(root, key, match);
}

bool BST::retrieve(Node * currRoot, const char * key, Data& match) const
{
	if (!currRoot)
	{
		return false;
	}
	int temp = strcmp(key, currRoot->data->getVendorName());
	if ( temp == 0)
	{
		match = *currRoot->data;
		return true;
	}
	else if (temp < 0)
	{
		return retrieve(currRoot->left, key, match);
	}
	else 
	{
		return retrieve(currRoot->right, key, match);
	}
}

bool BST::remove(const char* searchKey, Data& match)
{
	return remove(root, searchKey, match);
}

bool BST::remove(Node *& currRoot, const char* searchKey, Data& match)
{
	if (!currRoot)
	{
		return false;
	}
	int temp = strcmp(searchKey, currRoot->data->getVendorName());
	if (temp == 0)
	{
		match = *currRoot->data;
		deleteNode(currRoot);
		return true;
	}
	else if (temp < 0)
	{
		return remove(currRoot->left, searchKey, match);
	}
	else 
	{
		return remove(currRoot->right, searchKey, match);
	}
}

void BST::deleteNode(Node *& toBeDeleted)
{
	//it's a leaf, no children
	if (!toBeDeleted->left && !toBeDeleted->right)
	{
		delete toBeDeleted;
		toBeDeleted = nullptr;
	}
	//it has one left child
	else if (!toBeDeleted->right)
	{
		Node * temp = toBeDeleted;
		toBeDeleted = toBeDeleted->left;
		delete temp;
	}

	//if it has one right child
	else if (!toBeDeleted->left)
	{
		Node *temp = toBeDeleted;
		toBeDeleted = toBeDeleted->right;
		delete temp;
	}

	//if it has two children
	else
	{
		//find the in-order successor
		Node * prev = nullptr;
		Node * curr = toBeDeleted->right;
		while (curr->left)
		{
			prev = curr;
			curr = curr->left;
		}

		toBeDeleted->data = curr->data;
		Node * temp = curr;
		if (!prev)
		{
			toBeDeleted->right = curr->right;
		}
		else
		{
			prev->left = curr->right;
		}
		delete temp;
	}
}
void BST::listAll() const
{
	listAll(root);
}

void BST::listAll(Node * currRoot) const
{
	if (currRoot)
	{
//	  std::cout << *currRoot->data << std::endl;  //pre-order 
	  listAll(currRoot->left);
	  std::cout << *currRoot->data << std::endl;   //inorder traveral (sorted in order)
	  listAll(currRoot->right);
//	  std::cout << *currRoot->data << std::endl;  //post order
	}
}


void BST::saveData(char * fileName) const
{
	std::ofstream out;
	out.open(fileName);
	if (!out)
	{
		std::cerr << "Failed to open " << fileName << " for ouput!" << std::endl;
		exit(1);
	}
	saveData(out);
	out.close();
}

void BST::saveData(std::ofstream& out) const
{
	saveData(root, out);
}

void BST::saveData(Node * currRoot, std::ofstream& out) const
{
	if (currRoot)
	{
		out << currRoot->data->getVendorName() << ';'
			<< currRoot->data->getPhoneNumber() << ';'
			<< currRoot->data->getProductType() << ';'
			<< currRoot->data->getEventSize() << ';';
		for (int i = 0; i < currRoot->data->getEventSize(); i++)
			out << currRoot->data->getEventType(i) << ' ';
		out << ";" << std::endl;
		saveData(currRoot->left, out);
		saveData(currRoot->right, out);
	}
}

int BST::getSize() const
{
	return getSize(root);
}

int BST::getSize(Node * currRoot) const
{
	if (!currRoot)
		return 0;
	return 1 + getSize(currRoot->left) + getSize(currRoot->right);
}

void BST::getSmallest(Data& smallest) const
{
	smallest = *getSmallest(root)->data;
}

BST::Node* BST::getSmallest(Node * currRoot) const
{
	if (!currRoot->left)
		return currRoot;
	return getSmallest(currRoot->left);
}

void BST::printLeaves(Node * currRoot) const
{
	if (!currRoot)
		return;
	if (!currRoot->left && !currRoot->right)
	{
		std::cout << *currRoot->data << std::endl;
		return;
	}
	printLeaves(currRoot->left);
	printLeaves(currRoot->right);	
}

int BST::height()
{
	return height(root);
}

int BST::height(Node * root)
{
	int leftHeight, rightHeight;

	if (!root)
		return 0;

	leftHeight = height(root->left);
	rightHeight = height(root->right);

	if (leftHeight > rightHeight)
		return leftHeight + 1;
	else
		return rightHeight + 1;
}

