#include "iostream"
#include "vector"
using namespace std;

void winOrLoss(vector<char> &cowboys)
{
	while (true)
	{
		cout << "Enter the letter W for a win or L for a Loss or X to end: " << endl;
		char result;
		cin >> result;
		while (result != 'W' && result != 'L' && result != 'X')
		{
			cout << "Invalid Input" << endl;
			cin >> result;
		}
		if (result == 'X')
		{
			break;
		}
		else (result == 'W' || result == 'L');
		{
			cowboys.push_back(result);
		}
	}
}

void total(vector<char> &cowboys)
{
	int wins = 0, loss = 0;
	for (int count = 0;count < cowboys.size();count++)
	{
		if (cowboys[count] == 'W')
		{
			wins++;
		}
		else if(cowboys[count] == 'L')
		{
			loss++;
		}
		else
		{
			cout << "Invalid Input"<<endl;
		}
	}
	cout << endl << "Win count is " << wins << " - " << "Loss Count is " << loss;
}

int main() {
	vector<char> cowboys;
	winOrLoss(cowboys);
	total(cowboys);
	cout << endl << "Done!";
}