//-----------------------------------------------------------------------------
// CSCI2270 Course Project
//
// Identification: ProfBST.cpp
//-----------------------------------------------------------------------------

#include "ProfBST.h"

#include <iostream>

using namespace std;

ProfBST::ProfBST()
{
    root = NULL;
}

void cleartree(Professor *node) {
    if (node == NULL) return;
 
    /* first delete both subtrees */
    cleartree(node->left);
    cleartree(node->right);
    //then delete parent node
    delete node;
}

ProfBST::~ProfBST()
{
    cleartree(root);
}

Professor* insert(Professor *node, string ID, string name) {
    if (!node) {
        Professor *newprof = new Professor(ID, name);
        //cout << "node inserted" << endl;
        return newprof;
    }

    // if the given key is less than the root node, recur for the left subtree
    if (ID < node->profId) {
        node->left = insert(node->left, ID, name);
        //cout << "left recur insert" << endl;
    }
    // if the given key is more than the root node, recur for the right subtree
    else {
        node->right = insert(node->right, ID, name);
        //cout << "right recur insert" << endl;
    }

    return node;
}

void ProfBST::addProfessor(string profId, string profName)
{
    Professor *foundprofnode = searchProfessor(profId);

    if (!foundprofnode) {
        //cout << "prof not found, new prof created and inserted" << endl;
        if (!root) {
            root = insert(root, profId, profName);
        }
        else {
            insert(root, profId, profName);
        }
    }

    else {
        //cout << "prof found, no insertion performed" << endl;
    }
}

Professor* searchhelper(Professor *node, string profId) {
    if (node == NULL || node->profId == profId) {
       return node;
    }
    // Key is greater than root's key
    if (node->profId < profId) {
       return searchhelper(node->right, profId);
    }
    // Key is smaller than root's key
    return searchhelper(node->left, profId);
}

Professor* ProfBST::searchProfessor(string profId)
{
    Professor* temp = searchhelper(root, profId);

    if (!root) {
       return root;
    }
    return temp;
}

void ProfBST::addCoursetoVector(Professor *profnode, Course *newcourse) {
    profnode->coursesTaught.push_back(newcourse);
}

void displayBSThelper(Professor *node) { //delete eventually
    if(!node) {
        return;
    }
    displayBSThelper(node->left);
    cout << node->profId << ", " << node->profName << endl;
    cout << "COURSES TAUGHT" << endl << "***********************" << endl;
    for (int i = 0; i < node->coursesTaught.size(); i++) {
        cout << node->coursesTaught[i]->courseNum  << " " << node->coursesTaught[i]->courseName << endl;
    }
    cout << endl;
    displayBSThelper(node->right);
}

void ProfBST::displayBST() { //delete eventually
    if(!root) {
        cout << "tree is empty :-( root is null" << endl;
    }

    cout << "INORDER PRINT OF BST: " << endl << endl;
    displayBSThelper(root);
}

void ProfBST::publicSearchProfessor(string profId)
{
    Professor* temp = searchhelper(root, profId);

    if (!root) {
       cout << "Professor BST is empty" << endl;
       return;
    }
    
    displayProfessorInfo(temp);
    return;
}

void ProfBST::displayProfessorInfo(Professor* p)
{
    if (!p) {
        cout << "Professor not found" << endl;
        return;
    }

    else {
        cout << p->profName << endl;
        for (int i = 0; i < p->coursesTaught.size(); i++) {
            cout << p->coursesTaught[i]->courseNum << ": "
                 << p->coursesTaught[i]->courseName << ", "
                 << p->coursesTaught[i]->year << endl;
        }
    }
}
