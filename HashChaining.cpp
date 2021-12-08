//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: HashChaining.cpp
// Defines functions for HashChaining class
//-----------------------------------------------------------------------------

#include "HashChaining.h"

using namespace std;

//HashChaining(int size)
//creates an empty hash table with number of buckets passed as a command line arg
//dynamically allocates memory
//input: int
//output: void
HashChaining::HashChaining(int size)
{
    this->hashTableSize= size; //set hashTableSize attribute

    hashTable = new Course *[hashTableSize]; // allocated memory for hashtable array
    for (int i = 0; i < hashTableSize; i++) { //now allocate memory for each pointer
            hashTable[i] = nullptr;
    }
}

//~HashChaining()
//destructor for hash table. clears dynamically allocated memory
//input: none
//output void
HashChaining::~HashChaining()
{
    for (int i = 0; i < hashTableSize; i++) { //iterate through hash table and delete each element

        Course *temp = hashTable[i];
        Course *next = NULL;
        while (temp) {
            next = temp->next;
            delete temp;
            temp = next;
        }
        hashTable[i] = NULL;
    }
}

//hash
//use to get hash code of each course Number
//input: int
//output: int
int HashChaining::hash(int courseNumber) 
{
    return (courseNumber % hashTableSize); //returns hash of coursenumber
}

//bulkinsert
//opens csv file, reads in data, and stores it in a hash table. Populates ProfBST as well
//input: string
//output: void
void HashChaining::bulkInsert(string filename)
{
    fstream coursefile;
    coursefile.open(filename, ios::in);

    vector<string> rowvec;
    string line, word, content;

    int x = 0;
    int collisions = 0;
    int searches = 0;
    while (getline(coursefile, content)) {
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
                hashTable[hashcode] = newcourse;
            }
            else {
                collisions ++;
                Course *temp = hashTable[hashcode];
                while (temp->next) {
                    searches++;
                    temp = temp->next;
                }
                searches++;
                newcourse->previous = temp;
                temp->next = newcourse;  
            }

        }
        x++;
    }     

    cout << "[CHAINING] Hash table populated" << endl
    << "--------------------------------" << endl
    << "Collisions using chaining: " << collisions << endl
    << "Search operations using chaining: " << searches << endl << endl;
}

//search
//uses course year, course number, and professor id to serach through hash table and print out information about the searched course
//input: int, int, string
//output: void
void HashChaining::search(int courseYear, int courseNumber, string profId)
{
    int hashcode = hash(courseNumber);
    int searches = 1;

    cout << "[CHAINING] Search for a course" << endl << "--------------------" << endl;
    if(hashTable[hashcode]->year == courseYear && hashTable[hashcode]->courseNum == courseNumber && hashTable[hashcode]->prof->profId == profId) {
        cout << "search operations using chaining: " << searches << endl;
        displayCourseInfo(hashTable[hashcode]);
    }
    else {
        Course *temp = hashTable[hashcode];
        while(true) {
            temp = temp->next;
            if (temp->year == courseYear && temp->courseNum == courseNumber && temp->prof->profId == profId) {
                cout << "search operations using chaining: " << searches << endl;
                displayCourseInfo(temp);
                cout << endl;
                break;
            }
            else if (!temp) {
                displayCourseInfo(temp);
                cout << endl;
                break;
            }
            searches++;
        }
    }
}

//displayallcourses
// iterates through entire hash table and prints out data for each bucket
//input: none
//output: void
void HashChaining::displayAllCourses()
{
    cout << "[CHAINING] displayAllCourses()" << endl
         << "-------------------------------" << endl;

    for (int i = 0; i < hashTableSize; i++) {
        if (hashTable[i]) {
            Course *temp = hashTable[i];
            // cout << "bucket" << i << ": " << endl;
            while(temp) {
                cout << " - " << temp->year << " ";
                //cout << temp->department << " ";
                cout << temp->courseName << " ";
                cout << temp->courseNum << " ";
                //cout << temp->prof->profId << " ";
                cout << temp->prof->profName << " ";
                cout << endl;
                temp = temp->next;
            }
        }
    }
}

//displaycourseinfo
//prints information from course node
//input: pointer to Course struct
//output: void
void HashChaining::displayCourseInfo(Course* c)
{
    if (!c) {
        cout << "Course not found. Try again" << endl;
        return;
    }
    cout << c->year << " " << c->courseName << " " << c->prof->profName << endl;
}
