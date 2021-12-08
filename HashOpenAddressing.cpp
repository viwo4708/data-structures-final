//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashOpenAddressing.cpp
//-----------------------------------------------------------------------------

#include "HashOpenAddressing.h"

using namespace std;

HashOpenAddressing::HashOpenAddressing(int size)
{
    this->hashTableSize= size; //set hashTableSize attribute

    hashTable = new Course *[hashTableSize]; // allocated memory for hashtable array
    for (int i = 0; i < hashTableSize; i++) { //now allocate memory for each pointer
            hashTable[i] = nullptr;
    }
}

HashOpenAddressing::~HashOpenAddressing()
{
    for (int i = 0; i < hashTableSize; i++) { //iterate through hash table and delete each element
        delete hashTable[i];
    }
}

int HashOpenAddressing::hash(int courseNumber)
{
    return (courseNumber % hashTableSize); //returns hash of coursenumber
}

void HashOpenAddressing::bulkInsert(string filename)
{   
    //cout << "bulkinsert is called" << endl;
    fstream coursefile;
    coursefile.open(filename, ios::in);

    vector<string> rowvec;
    string line, word, content;

    int collisions = 0;
    int searches = 0;
    int x = 0;
    while (getline(coursefile, content)) {
        //cout << "getline works" << endl;
        rowvec.clear();

        if (x > 0) {
            istringstream row(content);
            rowvec.push_back("dummy");
            while (getline(row, word, ',')) {
            rowvec.push_back(word);
            }

            Course *newcourse = new Course(atoi(rowvec[1].c_str()), rowvec[2], atoi(rowvec[3].c_str()), rowvec[4]);
            profDb.addProfessor(rowvec[5], rowvec[6] + " " + rowvec[7]);
            profDb.addCoursetoVector(profDb.searchProfessor(rowvec[5]), newcourse);
            Professor *profez = profDb.searchProfessor(rowvec[5]);
            newcourse->prof = profez;

            int hashcode = hash(newcourse->courseNum);

            if (!hashTable[hashcode]) {
                //cout << "no probing needed" << endl;
                hashTable[hashcode] = newcourse;
            }
            else {
                collisions ++;
                int i = 0;
                while (true) {
                    hashcode = (hashcode + (i*i)) % hashTableSize;
                    if (!hashTable[hashcode]) {
                        hashTable[hashcode] = newcourse;
                        break;
                    }
                    searches ++;
                    i++;
                } 
            }
        }
        x++;
    } 
    cout << "[OPEN ADDRESSING] Hash table populated" << endl
         << "--------------------------------" << endl
         << "Collisions using open addressing: " << collisions << endl
         << "Search operations using open addressing: " << searches << endl << endl;

}

void HashOpenAddressing::search(int courseYear, int courseNumber, string profId)
{
    int hashcode = hash(courseNumber);
    int firsthash = hashcode;
    int searches = 1;

    cout << "[OPEN ADDRESSING] Search for a course" << endl << "--------------------" << endl;
    if(hashTable[hashcode]->year == courseYear && hashTable[hashcode]->courseNum == courseNumber && hashTable[hashcode]->prof->profId == profId) {
        cout << "search operations using open addressing: " << searches << endl;
        displayCourseInfo(hashTable[hashcode]);
    }
    else {
        int i = 1;
        while (true) {
            searches ++;
            hashcode = (hashcode + (i*i)) % hashTableSize;
            if (hashcode == firsthash) {
                cout << "Course not found" << endl;
                break;
            }
            else if (hashTable[hashcode]->year == courseYear && hashTable[hashcode]->courseNum == courseNumber && hashTable[hashcode]->prof->profId == profId) {
                cout << "search operations using open addressing: " << searches << endl;
                displayCourseInfo(hashTable[hashcode]);
                break;
            }
            i++;
        }
    }
}

void HashOpenAddressing::displayAllCourses()
{
    cout << "[OPEN ADDRESSING] displayAllCourses()" << endl
         << "-------------------------------" << endl;

    for (int i = 0; i < hashTableSize; i++) {
        if (hashTable[i]) {
            // cout << "bucket" << i << ": " << endl;
            cout << " - " << hashTable[i]->year << " ";
            // cout << hashTable[i]->department << " ";
            cout << hashTable[i]->courseName << " ";
            cout << hashTable[i]->courseNum << " ";
            // cout << hashTable[i]->prof->profId << " ";
            cout << hashTable[i]->prof->profName << " ";
            cout << endl;
        }
        else {
            cout << "empty bucket" << endl;
        }
    }
}

void HashOpenAddressing::displayCourseInfo(Course* c)
{
    if (!c) {
        cout << "Course not found. Try again" << endl;
        return;
    }

	cout << c->year << " " << c->courseName << " " << c->prof->profName << endl;
}