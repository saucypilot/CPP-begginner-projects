#include<iostream>
using namespace std;

void displayGrade(int grade);

int main()
{
   	int grade;
   	cout << "Enter your grade: ";
   	cin >> grade;
	while(grade!=999)
	{
   		displayGrade(grade);
		cout << "Enter your grade: ";
   		cin >> grade;
	}
	cout<<"Done."<<endl;
    return 0;
}

void displayGrade(int grade)
{
	if(grade<=-10 || grade>=110) 	
	{
		cout<<"Invalid Grade!"<<endl;
		return;
	}
	else if (grade>=90)
		cout<<"Good Job!"<<endl;
	else if (grade>=70)	
		cout<<"You may need to visit the Lab."<<endl;
	else
		cout<<"Please ask help!"<<endl;
}