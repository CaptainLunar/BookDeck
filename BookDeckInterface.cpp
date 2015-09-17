#include "BookDeckInterface.h"
#include "BookDeck.h"
#include <iostream>
#include <string>
using namespace std;

BookDeckInterface::BookDeckInterface()
{
	program = new BookDeck;
}

BookDeckInterface::~BookDeckInterface()
{
	delete program;
	delete this;
}

void BookDeckInterface::startInterface()
{
	int x;
	bool p = true;
	cout << "Welcome to BookDeck - An application for readers" << endl;
	readFile();
	
	while (p)
	{	
		promptChoices();
		cin >> x;			//endless loop occurs if x is not an integer
		cin.ignore();

		switch (x)
		{
			case 1:
				addBook();
				break;
			case 2:
				deleteBook(); // fix this
				break;
			case 3:
				printBooks();
				break;
			case 4:
				unavailableMsg();
				break;
			case 5:
				unavailableMsg();
				break;
			case 6:
				unavailableMsg();
				break;
			case 7:
				backupToFile();
				break;
			case 8:
				cout << "Exiting program...\n";
				cout << "Press any key to close window...";
				p = false;
				break;
			default:
				//Endless loop occurs 
				cout << "Please enter a valid menu choice.\n";
				break;
		}
	}
}

void BookDeckInterface::promptChoices()
{
	cout << "\nWhat would you like to do? (Enter a number)\n";
	cout << "1) Add a book\n";
	cout << "2) Delete a book\n";
	cout << "3) Print your book list\n";
	cout << "4) See book information\n";
	cout << "5) Search by Author\n";
	cout << "6) Search by Book Name\n"; 
	cout << "7) Save your book list\n";
	cout << "8) Exit BookDeck" << endl;
}

void BookDeckInterface::addBook()
{
	string author, bookname, date;
	
	//getline DOES include the terminating newline character
	cout << "Enter Author: ";
	getline(cin, author);

	cout << "Enter Book Name: ";
	getline(cin, bookname);
	
	cout << "Enter date completed: ";
	getline(cin, date);
	
	if (program->addBook(author, bookname, date)){
		cout << "Succesfully stored!" << endl;
	}
	else
		cout << "Could not save information. Please try again.";
}

void BookDeckInterface::deleteBook()
{
	string bookname;
	cout << "Enter the name of of the book you wish to delete: ";
	getline(cin, bookname);
	
	if (program->removeBookByName(bookname))
	{
		cout << bookname << " succesfully deleted." << endl;
		//backupToFile(); // backup the data into the file
		return;
	}
	else {
		cout << "Could not delete book. Please try again." << endl;
		return;
	}
}

void BookDeckInterface::printBooks()
{
	cout << "Printing your books...\n" << endl;
	program->printBooks();
}

void BookDeckInterface::unavailableMsg()
{
	cout << "This feature is not available at the moment. Sorry!";
}

void BookDeckInterface::backupToFile()
{
	if (program->isEmpty()) {
		cout << "Please add some books first to backup to a file.";
		return;
	}
	else {
		program->backupToFile();
		cout << "Successfully saved!" << endl;
	}
}

void BookDeckInterface::readFile()
{
	cout << "Reading your book data...\n";
	program->readfromFile();
}
