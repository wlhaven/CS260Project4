# CS260Project4
Hash Table and BST use

Purpose of the project:

CS260 Data Structure Project 4
Programming Assignment Specifications:
In this program, our primary goal is to implement a non-linear data structure using a binary search tree. You have noticed that Portland has many different outdoor events: Farmers market, Saturday Market, Art Festivals in the Pearl, etc. You have decided it would be useful to have a quick way to search for different vendors to see where and when they will be selling their products.
For each vendor, keep track of:
Name:
phone number:
type of product (e.g. produce, ceramics, glass art, etc)
event(s) which they participate. Please note that some vendors participate in many of outdoor events.
Implementation Requirements:
-Create a vendor class to model the vendor object.
-Make sure you encapsulate the the data, i.e. put data members in private section of the class.
-Use char * to model strings instead of string.
-Create a collection class to manage the vendors you are interested.

The collection class will be implemented using a binary search tree (linked structure, each node has two children) organized by vendor name and a data structure of your choice organized by type of product. You have to keep one important requirement in mind:
You may not have two copies of the vendor data in this program. You can implement this by storing pointer to vendor data in both binary tree and this other data structure you choose.

 The collection class needs to provide operations to:
- add a vendor: void add(const vendor & aVendor);
- remove a vendor: bool remove(char * vendorName);
- retrieve a vendor by name: bool retrieve(char * vendorName, vendor & aVendor);
- retrieve vendors by product type: bool retrieve(type productType, vendor * vendors);
- you might need to return more than one vendor
- you can make the client program to pass in an array (vendors) and populate this array in the retrieve    function
- display all the vendors sorted by type of products: void displayByType();
- display all the vendors sorted by name: void displayByName();

 You are required to provide the following functions in the above classes:
- constructors including copy constructor.
- destructor. Use valgrind to check you don't have memory leaks.
- overload '=' operator so that a "deep copy" will be obtained.

 The client program needs to provide a menu-based command line user interface. All the keyboard input should be done in the client program instead of the ADT. You don't have to do extensive error checking this term. You may assume that only valid data will be entered. The clients programs need to provide at least the following menu items:

- add a vendor
- remove a vendor
- search a vendor by name
- search vendors who sell a specific type of product
- display vendors sorted by name
- display vendors sorted by type of products

 The collection should be populated with data in an external file (in the same directory as the source files) when the program starts. You need to provide a writeOut function to save any changes you've made to the vendors database. Please don't prompt user for external file name! You can refer to the sample code for how to read/write external files in your list class.

 You can use a driver that is similar to what I provided for lab1.

