#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;

struct Flight
{
    string departureCity;
    string departureTime;
    string destinationCity;
};

struct Time
{
    int hours;
    int minutes;
    string meridiem;
};

unordered_map<string, int> timeZoneDifference = {
    {"Charlotte", 0},
    {"Orlando", 0},
    {"Houston", -1},
    {"Denver", -2},
    {"San Diego", -3}};

Time parseTime(const string &timeStr)
{
    Time time;
    char trash;
    stringstream ss(timeStr);
    ss >> time.hours >> trash >> time.minutes >> time.meridiem;
    return time;
}

string formatTime(const Time &time)
{
    string formattedTime = to_string(time.hours) + ":" + (time.minutes < 10 ? "0" : "") + to_string(time.minutes) + " " + time.meridiem;
    return formattedTime;
}

Time calculateArrivalTime(const Time &departureTime, int diff)
{
    Time arrivalTime;
    arrivalTime.hours = departureTime.hours + diff;
    arrivalTime.minutes = departureTime.minutes + 1;
    arrivalTime.meridiem = departureTime.meridiem;

    if (arrivalTime.minutes >= 60)
    {
        arrivalTime.minutes -= 60;
        arrivalTime.hours++;
    }

    if (arrivalTime.hours > 12)
    {
        arrivalTime.hours -= 12;
    }
    else if (arrivalTime.hours == 12)
    {
        arrivalTime.meridiem = (arrivalTime.meridiem == "A.M.") ? "P.M." : "A.M.";
    }

    return arrivalTime;
}

int main()
{
    string fileName;
    cout << "Enter file name: ";
    cin >> fileName;

    ifstream inFile(fileName);
    if (!inFile)
    {
        cerr << "Unable to open file: " << fileName << endl;
        return 1;
    }

    int numFlights;
    inFile >> numFlights;

    vector<Flight> flights(numFlights);
    for (int i = 0; i < numFlights; i++)
    {
        inFile >> flights[i].departureCity >> flights[i].departureTime >> flights[i].destinationCity;
    }

    inFile.close();

    for (int i = 0; i < numFlights; i++)
    {
        Time departureTime = parseTime(flights[i].departureTime);
        int diff = timeZoneDifference[flights[i].destinationCity] - timeZoneDifference[flights[i].departureCity];
        Time arrivalTime = calculateArrivalTime(departureTime, diff);

        cout << "Flight " << i + 1 << ": "
             << flights[i].departureCity << " " << formatTime(departureTime) << " "
             << flights[i].destinationCity << " " << formatTime(arrivalTime) << endl;
    }

    return 0;
}
