#include <iostream>
#include <fstream>
using namespace std;

const int row = 8;
const int col = 10;

int inputNums(int args[row][col])
{
    ifstream myFile;
    myFile.open("8x10ints.txt");
    for (int i = 0; i <= row - 1; i++)
    {
        for (int j = 0; j <= col - 1; j++)
        {
            myFile >> args[i][j];
            cout << args[i][j] << " ";
        }
        cout << endl;
    }
    myFile.close();
    return 0;
}

int smallestVal(int args[row][col])
{
    int smallest = args[0][1];
    for (int i = 0; i <= row - 1; i++)
    {
        for (int j = 0; j <= col - 1; j++)
        {
            if (args[i][j] <= smallest)
            {
                smallest = args[i][j];
            }
        }
    }
    cout << endl
         << "smallest number is: " << smallest;
    return 0;
}

int main()
{
    int arr[row][col];
    inputNums(arr);
    smallestVal(arr);
    return 0;
}