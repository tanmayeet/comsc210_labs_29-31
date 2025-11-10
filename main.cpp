// COMSC210 | Lab 29-31 | Tanmayee Chalamalasetti
// IDE Used: VS Code

// Include necesssary headers for file handling, data structures, etc.

// Define a function to simulate astronomical changes over time
//  -Function: simulateTimePeriod

// Parameters:
//  -map of solar system zones (each with stars, planets, and black holes)
//  -current time period

// Logic
// Begin a time-based simulation for astronomical changes for 50 time intervals
//   -For each zone:
//       -Simulate astronomical changes holistically
//       -Randomly pick one of the three categories
//       -Randomly decide whether to add or remove an object
//       -If adding: create a new celestial body and put it in the list
//       -If removing: randomly pick a body from the list and remove it
//       -Print out what occurred during that time period

// Main function
// 1) Initialize a map to store solar system zone info, each associated with an
// array of lists for planets, stars, and black holes

// 2) Open an external file to read data about solar system zones and to
// populate the map
//  -If file does not open, print an error and exit

// 3) Read data from the file and populate the map
//  -For each line, extract solar system zone and celestial body data
//  -Each line contains zone, category, and event

// 4) Insert celestial bodies into the appropriate list in the array for their
// solar system zone

// 5) Close the file

// Simulate more complex astronomical changes like random events impacting the
// solar system, eclipses, meteor showers, etc.

// Wait or pause briefly to simulate the passage of time between intervals

// End of main function

#include <array>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>
using namespace std;

const int num_periods = 50;
const int num_categories = 3;
const int rand_range = 100;

// Function prototype
void simulateTimePeriod(map<string, array<list<string>, 3>>& solarMap,
                        int period);

// simulateTimePeriod: Used to simulate astronomical changes for one time period
// Arguments: map<string, array<list<string>, 3>>& solarMap,int period
// Returns: nothing
void simulateTimePeriod(map<string, array<list<string>, 3>>& solarMap,
                        int period) {
  cout << "Simulating time period " << period << " million years.\n";
  for (auto it = solarMap.begin(); it != solarMap.end(); it++) {
    string zone = it->first;
    array<list<string>, 3>& bodies = it->second;
    // bodies[0].push_back("Star event at period " + to_string(period));
    // bodies[1].push_back("Planet event at period " + to_string(period));
    // bodies[2].push_back("Black hole event at period " + to_string(period));

    int category = rand() % num_categories;
    bool add = rand() % 2;
    string name =
        "Body " + to_string(period) + "-" + to_string(rand() % rand_range);
    string categoryName;
    while {
      if (category == 0) {
        categoryName = "Star";
      } else if (category == 1) {
        categoryName = "Planet";
      } else if (category == 2) {
        categoryName = "Black Hole";
      } else {
        cout << "Invalid entry for this data set. Please try again.\n";
      }
    }

    if (add) {
      bodies[category].push_back(name);
      cout << "Added " << name << " to " << zone << " (" << categoryName
           << ")\n";
    } else {
      if (!bodies[category].empty()) {
        int size = bodies[category].size();
        int randomIndex = rand() % size;
        // defining an element at a random index to remove from the list

        auto it = bodies[category].begin();
        advance(it, randomIndex);
        // iterates through the list from the start and advances 'it''s index to
        // the element at index randomIndex

        string removed = *it;
        bodies[category].erase(it);
        // sets the string to remove as the address of it, which is a data entry
        // with all of a celestial body's info

        cout << "Removed " << removed << " from " << zone << " ("
             << categoryName << ")\n";
      } else {
        cout << "No " << categoryName << " to remove from " << zone << "\n";
      }
    }
  }
}

int main() {
  // Initializing a map for the solar system map
  map<string, array<list<string>, 3>> solarMap;

  // For randomly deciding whether to add or remove from list
  srand(time(0));

  // Add a function to read data from external file
  ifstream file("data.txt");
  if (!file) {
    cout << "Error opening data.txt\n";
    return 1;
  }

  // We go through each line of the input file to extract info
  // Format: zone, category, name
  string line;
  while (getline(file, line)) {
    int comma1 = 0, comma2 = 0;
    for (int i = 0; i < line.length(); i++) {
      if (line[i] == ',' && comma1 == 0) {
        comma1 = i;
      } else if (line[i] == ',' && comma1 != 0) {
        comma2 = i;
        break;
      }
    }

    string zone = line.substr(0, comma1);
    string category = line.substr(comma1 + 1, comma2 - comma1 - 1);
    string name = line.substr(comma2 + 1);

    int index;
    if (category == "star") {
      index = 0;
    } else if (category == "planet") {
      index = 1;
    } else {
      index = 2;
    }
    // adding celestial body to the appropriate list in the zone
    solarMap[zone][index].push_back(name);
  }
  file.close();

  // Test data from Lab 29
  // solarMap["Inner Solar System"][0].push_back("Sun");
  // solarMap["Outer Solar System"][1].push_back("Jupiter");
  // solarMap["Kuiper Belt"][2].push_back("BH-1");

  // Displaying initial state of zone
  for (auto it = solarMap.begin(); it != solarMap.end(); it++) {
    string zone = it->first;
    const array<list<string>, 3>& bodies = it->second;
    cout << "Zone: " << zone << "\n";

    cout << "Stars: ";
    for (const string& star : bodies[0]) {
      cout << star << " ";
    }
    cout << "\n";

    cout << "Planets: ";
    for (const string& planet : bodies[1]) {
      cout << planet << " ";
    }
    cout << "\n";

    cout << "Black Holes: ";
    for (const string& bh : bodies[2]) {
      cout << bh << " ";
    }
    cout << "\n";
  }

  // Simulating for 50 time periods
  // Want to do 1 through 50 to show a change instead of from 0 to 49
  for (int i = 1; i <= num_periods; i++) {
    simulateTimePeriod(solarMap, i);
  }
  return 0;
}
