/*
- BookDeck - For Book Enthusiasts
- A program to help organize your book collection!

:::::::::::::::::::::::::::::::::::::::::::::::::
				 To-Do List
* Deleting from a tree node is not working, need to fix as program crashes once deletion operation is called
* Implement the following remaining menu options for the program
  - Fetching book information from the Internet. Option 3.
  - Searching by Author
  - Searching by name of the book
* Wrap a GUI around the program.
* Endless loop occurs when menu choice user selects isn't an integer value. Possible fix -> Use an exception handler to catch unwanted input.

*/

#include "BookDeckInterface.h"
#pragma once

int main()
{
	BookDeckInterface *start;
	start = new BookDeckInterface;
	start->startInterface();
	getchar(); //get character from the screen to exit the program
	return 0;
}
