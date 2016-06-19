/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
			of a collection.
Date Due:	06-06-2016 
*/

#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Collection.h"
#include "Util.h"

int main()
{
	//use memory leak detection tool in Visual Studio .Net. 
	//comment it out if you are not using Visual Studio
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	char command = 'a';
	char fileName[] = "data.txt";
	Collection vendors(fileName);
	
	displayMenu();
	command = getCommand();
	while (command != 'q')
	{
		executeCmd(command, vendors);
		displayMenu();
		command = getCommand();
	}
	std::cout << "\nThank you for using  the CS260 Vendor Locator System!" << std::endl << std::endl; 
	std::cout << "\nPress <Enter> to exit.";
	std::cin.get();
	vendors.saveData(fileName);
	return 0;
}





