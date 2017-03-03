#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string removeWhitespace(string inputString) {
  // funtion to remove the leading whitespace - ie spaces between course code
  // and course title
  int startPos;
  startPos = inputString.find_first_not_of(" "); // find first non-whitespace
  return inputString.substr(startPos); // return from startPos til the end
}

int main() {
  const string coursePrefix("PHYS");
  string courseInput;          // input line
  stringstream courseStream;   // to extract course code and title
  int courseCode;              // course code
  string courseTitle;          // course title
  stringstream course;         // course prefix + course code + course title
  vector<int> courseCodes;     // vector of "courseCode"
  vector<string> courseTitles; // vector of "courseTitle"
  vector<string> courses;      // vector of "course"

  // Ask whether to read from a file or wait for user input
  cout << "Would you like to read the courselist from a file (f) or enter the "
          "courses manually (m)? (f/m): ";
  string entryMethod;
  cin >> entryMethod;

  // Check input
  while (cin.fail() || !(entryMethod == "f" || entryMethod == "m")) {
    cerr << "Error: Invalid input, please enter f to read in from a file or m "
            "to enter the courses manually: ";
    // Clear fail bit and ignore til end of line
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // Input again
    cin >> entryMethod;
  }

  if (entryMethod == "f") {
    // Read from file
    // Get filename
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    // Check it opened correctly
    ifstream inputFile(filename.c_str());
    if (!inputFile.good()) {
      cerr << "Error: could not open input file.\n";
      return 1;
    } else {
      cout << filename << " opened successfully.\n";
    }
    while (!inputFile.eof()) {
      // Check that the line has at least a full course number
      inputFile >> courseCode;
      if (!inputFile.fail()) {
        getline(inputFile, courseTitle, '\n');
        courseTitle = removeWhitespace(courseTitle);
        // Construct string of full course information
        course << coursePrefix << courseCode << " " << courseTitle;

        // Push all variables to vectors
        courses.push_back(course.str());
        courseCodes.push_back(courseCode);
        courseTitles.push_back(courseTitle);

        // Purge course buffer
        course.str(std::string());
      }
    }
    inputFile.close();
  } else {
    // Enter manually
    // Get list of courses and store in a vector
    bool finished{false};
    do {
      cout << "Please enter a course name (or 0 to finish): ";
      cin >> courseCode;
      getline(cin, courseTitle, '\n');
      if (courseCode == 0) {
        // Do not add to vector, exit while loop
        finished = true;
      } else {
        // Construct string of full course information
        course << coursePrefix << courseCode << " " << courseTitle;
        // Push all variables to vectors
        courses.push_back(course.str());
        courseCodes.push_back(courseCode);
        courseTitles.push_back(courseTitle);

        // Purge course buffer
        course.str(std::string());
      }
    } while (!finished);
  }

  // User interface
  string mainMenu; // Option input
  int year;        // Year input
  bool userInterface{true};
  while (userInterface) {
    cout << "Please choose an option:\n- Print out the full courselist (l)\n- "
            "Print out the courses for one year (y)\n- Sort the list by course "
            "code (c)\n- Sort the list by course title (t)\n- Exit the program "
            "(x)\nOption: ";

    cin >> mainMenu;
    while (cin.fail() ||
           !(mainMenu == "l" || mainMenu == "y" || mainMenu == "c" ||
             mainMenu == "t" || mainMenu == "x")) {
      // Invalid input
      cout << "Not a valid option. Please enter l, y, c, t or x: ";
      cin >> mainMenu;
    }
    if (mainMenu == "l") {
      cout << "Printing out full courselist.\n";
      for (auto it = courses.begin(); it != courses.end(); it++) {
        cout << *it << endl;
      }
    } else if (mainMenu == "y") {
      // Print out courses for a particular year
      cout << "Please enter a year to print courses for: ";
      cin >> year;
      cout << "Printing out courses for year " << year << endl;
      bool yearExist{false};
      int i{0};
      for (auto it{courses.begin()}; it != courses.end(); it++) {
        // Check if year is in position 4 (after PHYS)
        stringstream yearString;
        yearString << year;
        string fullInfo;
        fullInfo = *it;
        if (fullInfo.find(yearString.str()) == 4) {
          // course is from this year
          cout << *it << endl;
          yearExist = true;
        }
        yearString.str(std::string());
      }
      if (!yearExist) {
        cout << "There are no courses for year " << year << "!\n";
      }
    } else if (mainMenu == "c") {
      // Sort list by course code
      cout << "Sorting the list by course code\n";
      sort(courseCodes.begin(), courseCodes.end());
      for (auto itCode = courseCodes.begin(); itCode != courseCodes.end();
           itCode++) {
        stringstream tempCode;
        tempCode << *itCode;
        for (auto itFull = courses.begin(); itFull != courses.end(); itFull++) {
          string fullName = *itFull;
          if (fullName.find(tempCode.str()) == 4) {
            cout << fullName << endl;
          }
        }
        tempCode.str(std::string());
      }
    } else if (mainMenu == "t") {
      // Sort list by course title
      cout << "Sorting the list by course title\n";
      // Sort
      sort(courseTitles.begin(), courseTitles.end());
      for (auto itTitle = courseTitles.begin(); itTitle != courseTitles.end();
           itTitle++) {
        for (auto itFull = courses.begin(); itFull != courses.end(); itFull++) {
          string fullName = *itFull;
          if (fullName.find(*itTitle) == 10) {
            cout << fullName << endl;
          }
        }
      }
    } else if (mainMenu == "x") {
      // exit
      cout << "Exiting\n";
      userInterface = false;
    }
  }
  return 0;
}
