// Include necesssary headers for file handling, data structures, etc.

// Define a function to simulate astronomical changes over time
//  -Function: simulateTimePeriod

// Parameters:
//  -map of solar system zones (each with stars, planets, and black holes)
//  -current time period

// Logic
// Begin a time-based simulation for astronmical changes for 50 time intervals
//   -For each zone:
//       -Simulate astronomical changes holistically
//       -Randomly pick one of the three categories
//       -Randomly decide whether to add or remove an object
//       -If adding: create a new celestial body and put it in the list
//       -If removing: randomly pick a body from the list and remove it
//       -Print out what occured during that time period

// Main function
// 1) Initialize a map to store solar system zone info, each associoated with an
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

// Function prototype
void simulateTimePeriod(map<string, array<list<string>, 3>>& solarMap,
                        int period);

void simulateTimePeriod(map<string, array<list<string>, 3>>& solarMap,
                        int period) {
  cout << "Simulating time period " << period << " million years.\n";
  for (auto it = solarMap.begin(); it != solarMap.end(); it++) {
    string zone = it->first;
    array<list<string>, 3>& bodies = it->second;
    // bodies[0].push_back("Star event at period " + to_string(period));
    // bodies[1].push_back("Planet event at period " + to_string(period));
    // bodies[2].push_back("Black hole event at period " + to_string(period));

    int category = rand() % 3;
    bool add = rand() % 2;
    string name = "Body " + to_string(period) + "-" + to_string(rand() % 100);
    string categoryName;

    if (category == 0) {
      categoryName = "Star";
    } else if (category == 1) {
      categoryName = "Planet";
    } else {
      categoryName = "Black Hole";
    }

    if (add) {
      bodies[category].push_back(name);
      cout << "Added " << name << " to " << zone << " (" << categoryName
           << ")\n";
    } else {
      if (!bodies[category].empty()) {
        string removed = bodies[category].front();
        bodies[category].pop_front();
        cout << "Removed " << removed << " from " << zone << " ("
             << categoryName << ")\n";
      } else {
        cout << "No " << categoryName << " to remove from " << zone << "\n";
      }
    }
  }
}

int main() {
  // Intializing a map for the solar system map
  map<string, array<list<string>, 3>> solarMap;

  // For randomly deciding whether to add or remove from list
  srand(time(0));

  // Add a function to read data from external file
  ifstream file("data.txt");
  if (!file) {
    cout << "Error opening data.txt\n";
    return 1;
  }

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
    solarMap[zone][index].push_back(name);
  }
  file.close();

  // Test data
  solarMap["Inner Solar System"][0].push_back("Sun");
  solarMap["Outer Solar System"][1].push_back("Jupiter");
  solarMap["Kuiper Belt"][2].push_back("BH-1");

  // Displaying intial state
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
  for (int i = 1; i <= 50; i++) {
    simulateTimePeriod(solarMap, i);
  }
  return 0;
}
