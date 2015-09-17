// BookDeck - An application to help you sort your book collection
#ifndef BOOKDECK_H
#define BOOKDECK_H

#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class BookDeck
{
private:
struct BookInfo {
	string author;
	string bookName;
	string date;
	//Binary Search Tree Node pointers
	BookInfo *left;
	BookInfo *right;
};

BookInfo *root;
ifstream readFile;
ofstream outFile;

public:
	BookDeck();		 
	~BookDeck();	
	bool isEmpty() const { return root == NULL; };
	
	//Tree functions
	bool addBook(string author, string bookName, string date);
	bool addBook(BookInfo *newNode);
	bool removeBookByName(string BookName);
	bool removeBookByAuthor(string author);
	BookInfo *searchByAuthor(string au);
	BookInfo *searchByBookName(string bn);
	
	//Print Tree functions
	void printOneBook(BookInfo *T);
	void printBooks();
	
	//I/O functions to help backup data
	void backupToFile();
	void readfromFile();

	//To-Do functions
	bool searchByDate(string date);
	void sortByAuthor();
	void sortByBookName();
	void sortByDate();
	void editAuthor();
	void editBookName();
	void editDate();

private:
	
	//Duplicates a node
	BookInfo *DupNode(BookInfo *T);
	
	//Helper function for printBooks to print all elements of tree in root instance
	void PrintAll(BookInfo *T);

	//Functions to Handle library backup to file in case of program crash or user exit
	void printBooksToFile();
	void printOneBookToFile(BookInfo *T);
	void printAllFile(BookInfo *T);
};

#endif
