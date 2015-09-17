//Console Interface for bookdeck
#include "BookDeck.h"

using namespace std;

class BookDeckInterface
{
private:
	void promptChoices();
	BookDeck *program;
	void addBook();
	void deleteBook();
	void printBooks();
	void unavailableMsg();
	void backupToFile();
	void readFile();

public:
	BookDeckInterface();
	~BookDeckInterface();
	void startInterface();
};
