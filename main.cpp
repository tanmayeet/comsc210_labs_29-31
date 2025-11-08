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

void simulateTimePeriod(map<string, array<list<string>, 3>>& solarMap,
                        int period) {
  cout << "Simulating time period " << period << " million years.\n";
  for (auto& [zone, bodies] : solarMap) {
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

  string zone, category, name;
  while (getline(file, zone, ",")) {
    getline(file, category, ",");
    getline(file, name);

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
  for (const auto& [zone, bodies] : solarMap) {
    cout << "Zone: " << zone << "\n";
    cout << "Stars: " << bodies[0].front() << "\n";
    cout << "Planets: " << bodies[1].front() << "\n";
    cout << "Black Holes: " << bodies[2].front() << "\n";
  }
  // Simulating for 50 time periods
  // Want to do 1 through 50 to show a change instead of from 0 to 49
  for (int i = 1; i <= 50; i++) {
    simulateTimePeriod(solarMap, i);
  }
  return 0;
}
