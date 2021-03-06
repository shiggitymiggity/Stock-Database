#include <cstring>
#include <iostream>
#include <iomanip>
#include "hashmap.h"

using namespace std;

HashMap		*hm;

static void printStocks(void)
{
	cout << endl
		 << "----------------------------------------------------------------------------"
		 << endl << endl
		 << *hm				// print the contents of the HashMap
		 << endl
		 << "----------------------------------------------------------------------------"
		 << endl << endl;
}

// prints information about how an item was stored by the code
static void printAdditional(unsigned int symbolHash, unsigned int hashIndex,
							unsigned int usedIndex, unsigned int sequenceLgth)
{
	cout << "(hc 0x"
		 << right
		 << hex << setfill('0')
		 << uppercase << setw(8) << symbolHash
		 << dec << setfill(' ')
		 << ", hi "		<< setw(2) << hashIndex
		 << ", ui "		<< setw(2) << static_cast<signed int>(usedIndex)
		 << ", sl "		<< setw(2) << sequenceLgth
		 << ")" 
		 << left << endl;
}

// exercises HashMap::get() function
static void searchStock(char const * const symbol)
{
	unsigned int	usedIndex, hashIndex, symbolHash, sequenceLgth;
	Stock	s;

	if (hm->get(symbol, s, symbolHash, hashIndex, usedIndex, sequenceLgth))
		cout << "found " << left << setw(8) << symbol;
	else
		cout << symbol << " not found ";
	printAdditional(symbolHash, hashIndex, usedIndex, sequenceLgth);
}

// exercises HashMap::put() function. Creates an instance of Stock, hands that
// to the code, and then totally destroys it. This makes sure that the code will
// fail unless there is a "deep copy" of the Stock instance.
static void addStock(char *symbol, char *name, int sharePrice, Date priceDate)
{
	unsigned int	usedIndex, hashIndex, symbolHash, sequenceLgth;
	char			*sym = new char[strlen(symbol) + 1];
	char			*nm =  new char[strlen(name)   + 1];
	Stock			*s;
	
	strcpy(sym, symbol);
	strcpy(nm, name);
	s = new Stock(sym, nm, sharePrice, priceDate);
	if (hm->put(*s, symbolHash, hashIndex, usedIndex, sequenceLgth)) {
		cout << "added " << left << setw(8) << s->getSymbol();
		printAdditional(symbolHash, hashIndex, usedIndex, sequenceLgth);
		}
	else
		cout << s->getSymbol() << " not added" << endl;

	delete[] sym;
	delete[] nm;
	delete s;
}

// exercises HashMap::remove() function
static void removeStock(char *symbol)
{
	unsigned int	usedIndex, hashIndex, symbolHash, sequenceLgth;
	Stock	s;

	if (hm->remove(symbol, s, symbolHash, hashIndex, usedIndex, sequenceLgth)) {
		cout << "removed " << left << setw(6) << symbol;
		printAdditional(symbolHash, hashIndex, usedIndex, sequenceLgth);
		}
	else
		cout << symbol << " not removed" << endl;
}

int main(int argc, char **argv)
{
	cout << "CS260 - Assignment 3 - " << HashMap::YOUR_NAME << endl;

	hm = new HashMap(13);

	printStocks();
	searchStock("IBM");
	addStock("IBM", "International Business Machines", 2573, Date(Date::MAY, 23, 1967));
	printStocks();
	searchStock("IBM");
	removeStock("IBM");
	searchStock("IBM");
	removeStock("IBM");
	addStock("MLT", "MLT Software, Inc.", 800, Date(Date::APRIL, 18, 1988));
	addStock("IBM", "International Business Machines", 2573, Date(Date::MAY, 23, 1967));
	addStock("XRX", "Xerox", 1892, Date(Date::JUNE, 1, 1980));
	addStock("US:BA", "Boeing", 6407, Date(Date::DECEMBER, 14, 1993));
	addStock("GD", "General Dynamics", 7281, Date(Date::OCTOBER, 24, 2006));
	addStock("AAPL", "Apple Computer, Inc.", 2308, Date(Date::MAY, 1, 1980));
	addStock("AAPL", "Apple Computer, Inc.", 2308, Date(Date::MAY, 1, 1980));
	addStock("GE", "General Electric", 1948, Date(Date::MARCH, 22, 1987));
	addStock("ATT", "American Telephone & Telegraph", 20, Date(Date::MAY, 10, 1998));
	printStocks();
	searchStock("ATT");
	removeStock("AAPL");
	removeStock("AAPL");
	searchStock("ATT");
	removeStock("US:BA");
	searchStock("GE");
	removeStock("GE");
	searchStock("ATT");
	addStock("AAPL", "Apple Computer, Inc.", 2308, Date(Date::MAY, 1, 1980));
	addStock("GE", "General Electric", 1948, Date(Date::MARCH, 22, 1987));
	addStock("US:BA", "Boeing", 6407, Date(Date::DECEMBER, 14, 1993));
	printStocks();

	delete hm;
	
	// report on memory leaks in the Output Window
	#ifdef _DEBUG
	if (argc == 2) {
		_CrtSetReportMode( _CRT_WARN , _CRTDBG_MODE_FILE );
		_CrtSetReportFile( _CRT_WARN , _CRTDBG_FILE_STDERR );
		}
	_CrtDumpMemoryLeaks();
	#endif

	return 0;
}
