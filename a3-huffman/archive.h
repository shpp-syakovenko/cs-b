#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <iostream>

#include <map>
#include "myvector.h"
#include "mylist.h"
#include "myqueue.h"
#include <fstream>
#include "node.h"

using namespace std;

class Archive
{
public:
    Node* root;                        // root tree
    bool deBug;

    Archive();                         // consructor
    void zip(string fileAdress);       // compress file
    void unZip(string fileAdress);     // uncompress file

private:
    void buildTable(Node* root, map<char,myVector<bool> > *table, myVector<bool> *code); // build table "char: value"
    string* saveTree(Node* saveRoot);            // save instructions for unpacking tree in the string
    void openTree(string* str);                  // uncompress tree
    void printTree(Node* root, unsigned k = 0);  // print tree in the console
    void deleteTree(Node* root);                 // delete tree

};

#endif // ARCHIVE_H
