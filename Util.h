/**Wally Haven
Class:		CS260 Spring 2016
Project4:	Outdoor Events Locator using Hash Table and BST data structures as part
of a collection.
Date Due:	06-06-2016
*/

#ifndef UTIL_H
#define UTIL_H

#include "Collection.h"

const int MAX_LEN = 256;

void displayMenu();
char getCommand();
void executeCmd(char command, Collection& aCollection);

void getData(Data & aVendor);
void displayProductTypes();
void displayEventTypes();
int getInt(const char * prompt);
double getDouble(const char * prompt);
void getString(const char * prompt, char * input);
void pause();

#endif // !UTIL_H