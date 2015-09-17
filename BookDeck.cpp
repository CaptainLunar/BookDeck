#include "BookDeck.h"
#include <fstream>
#include <iostream>

using namespace std;

BookDeck::BookDeck()
{
	root = NULL;
}

BookDeck::~BookDeck()
{

}

BookDeck::BookInfo *BookDeck::DupNode(BookInfo * T)
{
	BookInfo *node;
	node = new BookInfo;
	*node = *T;
	node->left = NULL;
	node->right = NULL;
	return node;
}

bool BookDeck::addBook(BookInfo *newNode)
{
	BookInfo *temp;
	BookInfo *parent;
	temp = root;
	parent = NULL;

	while (temp != NULL)
	{
		parent = temp;
		if (newNode->author < temp->author)
			temp = temp->left;
		else
			temp = temp->right;
	}

	if (parent == NULL) {
		root = newNode;
	}
	else {
		if (newNode->author < parent->author)
			parent->left = newNode;
		else
			parent->right = newNode;
	}
	return true;
}

bool BookDeck::addBook(string author, string bookName, string date)
{
	BookInfo *node;
	node = new BookInfo;
	node->author = author;
	node->bookName = bookName;
	node->date = date;
	node->right = NULL;
	node->left = NULL;

	return (addBook(node));
}

BookDeck::BookInfo *BookDeck::searchByAuthor(string au)
{
	BookInfo *temp;
	temp = root;
	while ((temp != NULL) && (temp->author != au))
	{
		if (au < temp->author)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if (temp == NULL)
		return temp; // did not find key
	else
		return DupNode(temp); //found key, return duplicate
}

BookDeck::BookInfo *BookDeck::searchByBookName(string bn)
{
	BookInfo *temp;
	temp = root;
	while ((temp != NULL) && (temp->author != bn))
	{
		if (bn < temp->author)
			temp = temp->left;
		else
			temp = temp->right;
	}
	if (temp == NULL)
		return temp; // did not find key
	else
		return DupNode(temp); //found key, return duplicate
}

bool BookDeck::removeBookByAuthor(string author)
{
	bool found = false;
	if (isEmpty())
	{
		cout << "This Book collection is empty!" << endl;
		return false;
	}

	BookInfo *currentNode;
	BookInfo *parent = new BookInfo;
	currentNode = root;

	while (currentNode != NULL)
	{
		if (currentNode->author == author)
		{
			found = true;
			break;
		}
		else
		{
			parent = currentNode;
			if (author > currentNode->author)
				currentNode = currentNode->right;
			else
				currentNode = currentNode->left;
		}
	}

	if (!found) {
		cout << "Delete: " << author << " not found." << endl;
		return false;
	}

	//Node with a single child
	if ((currentNode->left == NULL && currentNode->right != NULL) || (currentNode->left != NULL && currentNode->right == NULL))
	{
		if (currentNode->left == NULL && currentNode->right != NULL)
		{
			if (parent->left == currentNode)
			{
				parent->left = currentNode->right;
				delete currentNode;
			}
			else {
				parent->right = currentNode->right;
				delete currentNode;
			}
		}
		else 
		{
			if (parent->left == currentNode) {
				parent->left = currentNode->left;
				delete currentNode;
			}
			else {
				parent->right = currentNode->left;
				delete currentNode;
			}
		}
		return true;
	}

	//just a leaf node
	if (currentNode->left == NULL && currentNode->right == NULL)
	{
		if (parent->left == currentNode)
			parent->left = NULL;
		else {
			parent->right = NULL;
			delete currentNode;
			return true;
		}
	}

	//Node with 2 children
	if (currentNode->left != NULL && currentNode->right != NULL)
	{
		BookInfo * l;
		l = currentNode->right;
		if ((l->left == NULL) && (l->right == NULL))
		{
			currentNode = l;
			delete l;
			currentNode->right = NULL;
		}
		else //right has children
		{	
			//Move all the way down left to locate smallest element of the tree
			if ((currentNode->right)->left != NULL)
			{
				BookInfo *lcurrentNode;
				BookInfo *lcurrentParent;
				lcurrentParent = currentNode->right;
				lcurrentNode = (currentNode->right)->left;
				while (lcurrentNode->left != NULL)
				{
					lcurrentParent = lcurrentNode;
					lcurrentNode = lcurrentNode->left;
				}
				currentNode->author = lcurrentNode->author;
				delete lcurrentNode;
				lcurrentParent->left = NULL;
			}
			else {
				BookInfo *temp;
				temp = currentNode->right;
				currentNode->author = temp->author;
				currentNode->right = temp->right;
				delete temp;
			}
		}
		return true;
	}
	return false; //book not removed
}

bool BookDeck::removeBookByName(string bookName)
{
	bool found = false;
	if (isEmpty())
	{
		cout << "This Book collection is empty!" << endl;
		return false;
	}

	BookInfo *currentNode;
	BookInfo *parent = new BookInfo;
	currentNode = root;

	while (currentNode != NULL)
	{
		if (currentNode->bookName == bookName)
		{
			found = true;
			break;
		}
		else
		{
			parent = currentNode;
			if (bookName > currentNode->bookName)
				currentNode = currentNode->right;
			else
				currentNode = currentNode->left;
		}
	}

	if (!found) {
		cout << "Delete: " << bookName << " not found." << endl;
		return false;
	}

	//Node with a single child
	if ((currentNode->left == NULL && currentNode->right != NULL) || (currentNode->left != NULL && currentNode->right == NULL))
	{
		if (currentNode->left == NULL && currentNode->right != NULL)
		{
			if (parent->left == currentNode)
			{
				parent->left = currentNode->right;
				delete currentNode;
			}
			else {
				parent->right = currentNode->right;
				delete currentNode;
			}
		}
		else
		{
			if (parent->left == currentNode) {
				parent->left = currentNode->left;
				delete currentNode;
			}
			else {
				parent->right = currentNode->left;
				delete currentNode;
			}
		}
		return true;
	}

	//just a leaf node
	if (currentNode->left == NULL && currentNode->right == NULL)
	{
		if (parent->left == currentNode)
			parent->left = NULL;
		else {
			parent->right = NULL;
			delete currentNode;
			return true;
		}
	}

	//Node with 2 children
	if (currentNode->left != NULL && currentNode->right != NULL)
	{
		BookInfo * l;
		l = currentNode->right;
		if ((l->left == NULL) && (l->right == NULL))
		{
			currentNode = l;
			delete l;
			currentNode->right = NULL;
		}
		else //right has children
		{
			//Move all the way down left to locate smallest element of the tree
			if ((currentNode->right)->left != NULL)
			{
				BookInfo *lcurrentNode;
				BookInfo *lcurrentParent;
				lcurrentParent = currentNode->right;
				lcurrentNode = (currentNode->right)->left;
				while (lcurrentNode->left != NULL)
				{
					lcurrentParent = lcurrentNode;
					lcurrentNode = lcurrentNode->left;
				}
				currentNode->bookName = lcurrentNode->bookName;
				delete lcurrentNode;
				lcurrentParent->left = NULL;
			}
			else {
				BookInfo *temp;
				temp = currentNode->right;
				currentNode->bookName= temp->bookName;
				currentNode->right = temp->right;
				delete temp;
			}
		}
		return true;
	}
	return false;
}

void BookDeck::printOneBook(BookInfo *T)
{
	cout << T->bookName << '\n';
	cout << T->author << '\n';
	cout << T->date << '\n' << endl;
}

void BookDeck::PrintAll(BookInfo *T)
{
	if (T != NULL) {
		PrintAll(T->left);
		printOneBook(T);
		PrintAll(T->right);
	}
}

void BookDeck::printBooks()
{
	if (root != NULL) {
		PrintAll(root);
		return;
	}
	else {
		cout << "No books found.\n";
		return;
	}
}

void BookDeck::backupToFile()
{
	//destroy the previous file saved
	remove("bookData.txt");

	//write to new one at the end
	//open file to append at end, write out
	outFile.open("bookData.txt", ios::app | ios::out);
	if (outFile.is_open())
	{
		printBooksToFile();
		outFile.close();
	}
	else
		cout << "Unable to backup book data into bookData.txt\n";
}

void BookDeck::readfromFile()
{
	string author, bookname, date;
	readFile.open("bookData.txt", ios::in);

	if (readFile.is_open())
	{
		while (readFile)
		{
			getline(readFile, bookname);
			getline(readFile, author);
			getline(readFile, date);
			if (readFile.eof()) { //if we reach the end of the file, exit this while loop and return control to caller
				cout << "Read file succesfully!\n";
				readFile.close();
				return;
			}
			else { //if this is not the end of the file, add book to the tree
				addBook(author, bookname, date);
			}
		}
		cout << "Read file succesfully!\n";
		readFile.close();
		return;
	}
	else {
		cout << "Could not open bookData.txt\n";
		cout << "You can create bookData.txt by choosing to export your book collection!\n";
		return;
	}
}

void BookDeck::printBooksToFile()
{
	printAllFile(root);
}

void BookDeck::printOneBookToFile(BookInfo *T)
{
	outFile << T->bookName << '\n';
	outFile << T->author << '\n';
	outFile << T->date << endl;
}

void BookDeck::printAllFile(BookInfo *T)
{
	if (T != NULL) {
		printAllFile(T->left);
		printOneBookToFile(T);
		printAllFile(T->right);
	}
}
