#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

const int NUM_ROWS = 8;
const int NUM_COLS = 16;
const int NUM_PLOTS = 128;
const int ACRES_PER_PLOT = 5;
const int MAX_ROW = 8;
const int MAX_COL = 16;
const int MAX_ACRES = 128;
const char UNCLAIMED = '*';

// Data structure to represent a lot of land
struct Lot {
    int area; // area in acres
    bool visited; // flag to mark if lot has been visited during processing
};

// Function to compute the area of a lot of land
int computeLotArea(vector<vector<char>>& grid, int row_start, int row_end, int col_start, int col_end) {
    int num_unclaimed_plots = 0;
    for (int i = row_start; i <= row_end; i++) {
        for (int j = col_start; j <= col_end; j++) {
            if (grid[i][j] == '*') {
                num_unclaimed_plots++;
            }
        }
    }
    return num_unclaimed_plots * ACRES_PER_PLOT;
}

// Function to determine if a lot of land is completely surrounded by claimed plots
bool isEnclosedLot(vector<vector<char>>& grid, int row_start, int row_end, int col_start, int col_end) {
    // Check if any border plot is unclaimed
    for (int i = row_start; i <= row_end; i++) {
        if (grid[i][col_start] == '*' || grid[i][col_end] == '*') {
            return false;
        }
    }
    for (int j = col_start; j <= col_end; j++) {
        if (grid[row_start][j] == '*' || grid[row_end][j] == '*') {
            return false;
        }
    }
    return true;
}

// Function to traverse and mark all plots belonging to a specific lot of land
void traverseLot(vector<vector<char>>& grid, vector<vector<Lot>>& lots, int row, int col, int lot_num) {
    if (row < 0 || row >= NUM_ROWS || col < 0 || col >= NUM_COLS || lots[row][col].visited) {
        return;
    }
    if (grid[row][col] != '*') {
        return;
    }
    lots[row][col].visited = true;
    lots[row][col].area = ACRES_PER_PLOT;
    if (row > 0) {
        traverseLot(grid, lots, row - 1, col, lot_num);
    }
    if (row < NUM_ROWS - 1) {
        traverseLot(grid, lots, row + 1, col, lot_num);
    }
    if (col > 0) {
        traverseLot(grid, lots, row, col - 1, lot_num);
    }
    if (col < NUM_COLS - 1) {
        traverseLot(grid, lots, row, col + 1, lot_num);
    }
}

// Function to process a single survey
void processSurvey(int n, ifstream &infile)
{
    for (int i = 1; i <= n; i++)
    {
        char grid[MAX_ROW][MAX_COL];
        int numUnclaimed = 0;
        int acres[MAX_ACRES] = {0};

        // Read the section grid from the file
        for (int row = 0; row < MAX_ROW; row++)
        {
            for (int col = 0; col < MAX_COL; col++)
            {
                infile >> grid[row][col];
                if (grid[row][col] == UNCLAIMED)
                {
                    numUnclaimed++;
                }
            }
        }

        // Determine the size of each unclaimed lot
        int lotNum = 0;
        for (int row = 0; row < MAX_ROW; row++)
        {
            for (int col = 0; col < MAX_COL; col++)
            {
                if (grid[row][col] == UNCLAIMED)
                {
                    int lotSize = 0;
                    determineLotSize(grid, row, col, lotSize, row, col);
                    acres[lotSize]++;
                }
            }
        }

        // Output the results for the current survey
        cout << "Survey " << i << ":";
        for (int j = MAX_ACRES - 1; j >= 0; j--)
        {
            for (int k = 0; k < acres[j]; k++)
            {
                cout << " " << j * 5;
            }
        }
        cout << endl;

        // Skip the blank line after each section grid except for the last one
        if (i != n)
        {
            string blankLine;
            getline(infile, blankLine);
        }
    }
}

void determineLotSize(char grid[][MAX_COL], int row, int col, int &acreCount, int startRow, int startCol)
{
    if (grid[row][col] != '*')
    {
        return; // the current plot has already been claimed
    }

    // mark the current plot as visited
    grid[row][col] = '#';

    // add 5 acres to the current lot
    acreCount += 5;

    // check the neighboring plots
    if (row > startRow && grid[row - 1][col] == '*')
    {
        determineLotSize(grid, row - 1, col, acreCount, startRow, startCol);
    }

    if (row < MAX_ROW - 1 && grid[row + 1][col] == '*')
    {
        determineLotSize(grid, row + 1, col, acreCount, startRow, startCol);
    }

    if (col > startCol && grid[row][col - 1] == '*')
    {
        determineLotSize(grid, row, col - 1, acreCount, startRow, startCol);
    }

    if (col < MAX_COL - 1 && grid[row][col + 1] == '*')
    {
        determineLotSize(grid, row, col + 1, acreCount, startRow, startCol);
    }
}
