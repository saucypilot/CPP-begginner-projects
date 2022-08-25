#include <vector>
#include <algorithm>   
#include <iostream>
using namespace std;

const unsigned int STOCK_COUNT = 1000;

void loadArray(string theStocks[], const unsigned int LIMIT) {
	const unsigned int NBR_OF_VALID_LETTERS = 24;
	srand(8); // force to have same results for each run
	cout << "Loading Array with Random Data ..." << endl;

	vector<string> myStocks;
	string tempString;
	char tempChar;
	int postSortCount;

	while (myStocks.size() < LIMIT) {
		tempString = "";
		for (int attempt = 1; attempt < 4; ++attempt) {
			tempChar = (rand() % NBR_OF_VALID_LETTERS) + 65; // calc random letter char A-Z
			tempString += tempChar; // append to target string
		}
		myStocks.push_back(tempString); // load vector
		if (myStocks.size() == LIMIT) { // if @ limit - remove dups - if no dups loop will end
			cout << "Removing Duplicates in the List " << endl;

			sort(myStocks.begin(), myStocks.end()); // sort stock vector
			myStocks.erase(unique(myStocks.begin(), myStocks.end()), myStocks.end()); // remove duplicate entries
			postSortCount = LIMIT - myStocks.size();
			if (postSortCount != 0) {
				cout << "Removed " << postSortCount << " duplicated entries ..." << endl;
			}
		}
	}

	copy(myStocks.begin(), myStocks.end(), theStocks); // copy vector to array
	cout << "Array is loaded with " << LIMIT << " values!" << endl;

}

/*
showStockSymbols
Display the generated stock symbols
*/

void showStockSymbols(string showStocks[], const unsigned int LIMIT) {
	cout << "** Stock List ** " << endl;
	const int WRAP_MAX = 18;
	bool wrapped = false;
	for (unsigned int idx = 0; idx < LIMIT; ++idx) {
		cout << showStocks[idx] << " ";
		wrapped = false;
		if ((idx + 1) % WRAP_MAX == 0) { //Wrap every 18 entries (+1 fixes 0 start)
			cout << endl;
			wrapped = true;
		}
	}
	if (not wrapped) { // avoids a duplicate wrap
		cout << endl;
	}
    cout << "** End of Stock List ** " << endl << endl;
}


void linearSearch(string stocks[STOCK_COUNT],int size, string stockToFind)
{
    bool found = false;
    int i;
    int compare=0;
    for(i = 0; i < size; i++)
    {
        compare++;
        if(stocks[i] == stockToFind)
        {
            found = true;
            break;
        }
    }
    cout<<"Liner Search"<<endl;
    if(found==true)
    {
        cout << stockToFind << " found at index " << compare << endl << endl;
    }
    // flag==0 means Stock symbol is not present in the array
    else
    {
        // print not found
        cout << stockToFind << " not found" << endl << endl;
    }
}

int main() {
    cout << "Stock Search Program" << endl;
    //create stock array
string stocks[STOCK_COUNT];
string stockToFind;
loadArray(stocks, STOCK_COUNT);
while (true)
{
    cout << "Enter a 3 charcter Stock Symbol or X to exit: ";
    cin >> stockToFind;
    if(stockToFind=="X")
    {
        break;
    }
    else
    {
        linearSearch(stocks,STOCK_COUNT,stockToFind);
    }
}
cout << "END OF PROGRAM" << endl;
return (0);
}