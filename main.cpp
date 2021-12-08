//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: main.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"
#include "HashChaining.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int main (int argc, char* argv[])
{   
    if (argc != 3) {
        cout << "Invalid number of arguments." << endl
             << "Usage: ./<program name> <csv filename> <hashTableSize>" << endl;
        return 0;
    }

    int tablesize = atoi(argv[2]);
    string filename = argv[1];

    ifstream csvfile(filename);
    if (csvfile.fail()) {
        cout << "File failed to open. Try again." << endl;
        return 0;
    }

    HashChaining chainingHashTable(tablesize);
    HashOpenAddressing openAddressingHashTable(tablesize);
    bool alreadyselected = false;
    int userinput = 0;
    string inputprofID;
    int courseyear;
    int coursenumber;
    string profID;
    int tableoption;
    while (userinput != 5) {
        cout << "~~~~~~~~ Main Menu ~~~~~~~~" << endl
             << "1. Populate hash tables" << endl
             << "2. Search for a course" << endl
             << "3. Search for a Professor" << endl
             << "4. Display all courses" << endl
             << "5. Exit" << endl
             << "Enter the number that corresponds with task you'd like performed" << endl;
             cin >> userinput;

        switch(userinput) {
            case 1:
                if (alreadyselected) {
                    cout << "Hash tables already populated" << endl;
                }
                else {
                    alreadyselected = true;
                    chainingHashTable.bulkInsert(filename);
                    openAddressingHashTable.bulkInsert(filename);
                }
                break;
            case 2:
                if (alreadyselected) {
                
                    cout << "Enter the course year (e.g. 2021)" << endl;
                    cin >> courseyear;
                    cout << "Enter the coursenumber (e.g. 2270)" << endl;
                    cin >> coursenumber;
                    cout << "Enter the professor ID (e.g. llytellf)" << endl;
                    cin >> profID;
                    cout << endl;
                    chainingHashTable.search(courseyear, coursenumber, profID);
                    openAddressingHashTable.search(courseyear, coursenumber, profID);
                }
                else {
                    cout << "Hash tables must be populated first. Please select option 1." << endl;
                }
                break;
            case 3:
                if (alreadyselected) {
                    cout << "Enter a professor's ID (e.g. nscollan0)" << endl;
                    cin >> inputprofID;

                    cout << "[CHAINING] Search for Professor" << endl;
                    chainingHashTable.profDb.publicSearchProfessor(inputprofID);
                    
                    cout << endl;

                    cout << "[OPEN ADRESSING] Search for Professor" << endl;
                    openAddressingHashTable.profDb.publicSearchProfessor(inputprofID);
                }
                else {
                    cout << "Hash tables must be populated first. Please select option 1." << endl;
                }   
                break;
            case 4:
                if (alreadyselected) {
                    cout << "Which hash table would you like to display courses for? (1 = Open Addressing, 2 = Chaining)" << endl;
                    cin >> tableoption;

                    switch (tableoption) {
                        case 1:
                            openAddressingHashTable.displayAllCourses();
                            break;
                        case 2:
                            chainingHashTable.displayAllCourses();
                            break;
                        default:
                            cout << "Please input either 1 or 2" << endl;
                    }
                }
                else {
                    cout << "Hash tables must be populated first. Please select option 1." << endl;
                }
                break;
            case 5:
                // chainingHashTable.profDb.~ProfBST();
                // openAddressingHashTable.profDb.~ProfBST();
                // chainingHashTable.~HashChaining();
                // openAddressingHashTable.~HashOpenAddressing();
                return 0;
            default:
                cout << "Please input a valid number (1-5)" << endl;
                break;
        }
    }

}