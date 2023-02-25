#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

// Read a Sudoku grid from a file
void readGrid(ifstream &fin, int grid[9][9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            fin >> grid[i][j];
        }
    }
}

// Check if a proposed solution is correct
bool isSolutionCorrect(const int grid[9][9])
{
    // Check rows and columns
    for (int i = 0; i < 9; i++)
    {
        set<int> row, col;
        for (int j = 0; j < 9; j++)
        {
            if (row.count(grid[i][j]) > 0 || col.count(grid[j][i]) > 0)
            {
                return false;
            }
            row.insert(grid[i][j]);
            col.insert(grid[j][i]);
        }
    }

    // Check sub-grids
    for (int i = 0; i < 9; i += 3)
    {
        for (int j = 0; j < 9; j += 3)
        {
            set<int> subgrid;
            for (int k = i; k < i + 3; k++)
            {
                for (int l = j; l < j + 3; l++)
                {
                    if (subgrid.count(grid[k][l]) > 0)
                    {
                        return false;
                    }
                    subgrid.insert(grid[k][l]);
                }
            }
        }
    }

    return true;
}

// Find the row numbers of any rows that have errors in a Sudoku grid
vector<int> findRowErrors(const int grid[9][9])
{
    vector<int> errors;
    for (int i = 0; i < 9; i++)
    {
        set<int> row;
        for (int j = 0; j < 9; j++)
        {
            row.insert(grid[i][j]);
        }
        if (row.size() < 9)
        {
            errors.push_back(i);
        }
    }
    return errors;
}

// Find the column numbers of any columns that have errors in a Sudoku grid
vector<int> findColumnErrors(const int grid[9][9])
{
    vector<int> errors;
    for (int i = 0; i < 9; i++)
    {
        set<int> col;
        for (int j = 0; j < 9; j++)
        {
            col.insert(grid[j][i]);
        }
        if (col.size() < 9)
        {
            errors.push_back(i);
        }
    }
    return errors;
}

// Print a vector of integers separated by spaces
void printVector(const vector<int> &vec)
{
    for (int i : vec)
    {
        cout << i + 1 << " ";
    }
}

int main()
{
    string filename;
    cout << "Enter the file name: ";
    cin >> filename;
    ifstream fin(filename);

    if (!fin)
    {
        cerr << "Unable to open input file " << filename << endl;
        return 1;
    }

    int num_test_cases;
    fin >> num_test_cases;

    for (int test_case = 1; test_case <= num_test_cases; test_case++)
    {
        int grid[9][9];
        readGrid(fin, grid);
        cout << "GRID #" << test_case << ": ";
        if (isSolutionCorrect(grid))
        {
            cout << "SOLUTION IS CORRECT\n";
        }
        else
        {
            vector<int> rowErrors = findRowErrors(grid);
            vector<int> colErrors = findColumnErrors(grid);
            cout << "NOT A SOLUTION\n";
            cout << "ROWS WITH ERRORS: ";
            if (rowErrors.empty())
            {
                cout << "NONE\n";
            }
            else
            {
                printVector(rowErrors);
                cout << endl;
            }
            cout << "COLUMNS WITH ERRORS: ";
            if (colErrors.empty())
            {
                cout << "NONE\n";
            }
            else
            {
                printVector(colErrors);
                cout << endl;
            }
        }

        // read the line of equal signs
        string equalSigns;
        getline(fin, equalSigns);
        cout << equalSigns << endl;
    }

    fin.close();
    return 0;
}