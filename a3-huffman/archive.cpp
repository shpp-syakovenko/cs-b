#include "archive.h"

Archive::Archive()
{
    deBug = false;
}

// compress file
void Archive::zip(string fileAdress){

    /* Open stream and read frequency every char and save into map, where "key:char value:frequency" */
    ifstream fileRead(fileAdress.c_str(), ios::binary);
    if(!fileRead){
        cout << "Error! Incorrect path, try again!!! " << endl;
        return;
    }
    map<unsigned char, int>* dataChar = new map<unsigned char,int>;
    int dataSize = 0;

    char c ;
    while (fileRead.get(c)) {
        (*dataChar)[c]++;
        dataSize++;
    }


   /* Create list where will save leaf tree */
    myList<Node*> treeNodes;
    map<unsigned char, int>::iterator itr;

    for(itr = dataChar->begin(); itr != dataChar->end(); ++itr){
        Node* node = new Node;
        node->symbol = itr->first;
        node->count = itr->second;

        treeNodes.push_back(node); // закидуем узел в список нодов
    }


    /* Creat tree */
    while(treeNodes.size() != 1){

    treeNodes.sort(); // sort node

    Node* sonLeft = treeNodes.front();
    treeNodes.pop_front();
    Node* sonRight = treeNodes.front();
    treeNodes.pop_front();

    Node* parent = new Node(sonLeft,sonRight);
    treeNodes.push_back(parent);
    }
    root = treeNodes.front();// root of the tree



    myVector<bool>* code = new myVector<bool>;
    map<char,myVector<bool> > *table = new map<char, myVector<bool> >;


    // build table "char: value"
    buildTable(root,table,code);

    // save tree into string
    string* codelineTree = saveTree(root);
    int lengthTree = codelineTree->length();

    if(deBug){
        cout << "countTree: " << lengthTree << endl;
        cout << "datasize: " << dataSize << endl;
        cout << "codeline: " << *codelineTree << endl;

        // The output table "key:value"
                map<char, myVector<bool> >::iterator ii;
                for(ii = table->begin(); ii != table->end(); ++ii){ cout << ii->first << " : ";
                    for(int j = 0; j < (int)ii->second.size(); j++ ){cout << ii->second[j];}
                    cout << endl;}
        // print tree in the console
        printTree(root);
    }

    fileRead.clear();  // clear stream
    fileRead.seekg(0); // pointer on the start


    // open stream for write in the file.
    ofstream fileWrite((fileAdress + ".sy").c_str() , ios::binary);

    // write  length of the tree and size of the data into file.
    fileWrite.write(reinterpret_cast<char*>(&lengthTree), sizeof(int));
    fileWrite.write(reinterpret_cast<char*>(&dataSize), sizeof(int));



    /* Write tree into file. */
    int position = 0;  // position bit
    char byte = 0;
    for(int i = 0; i < lengthTree; i++){

        if((*codelineTree)[i] == '1')
        byte = byte | (1 << (7 - position));
        else {
           byte = byte | (0 << (7 - position));
        }
        position++;
        if(position == 8){
            position = 0;
            fileWrite.put(byte);
            byte = 0;
        }
    }
    if(position != 0){
       fileWrite.put(byte);
    }
    position = 0;
    byte = 0;


    /* Write data into file. */
    while(!fileRead.eof()){
        char c = fileRead.get();
        myVector<bool> x = (*table)[c];

        for(int i = 0; i < (int)x.size(); i++){
           byte = byte | (x[i] << (7 - position));
           position++;
           if(position == 8){
               position = 0;
               fileWrite.put(byte);
               byte = 0;
           }
        }
    }
    if(position != 0){
       fileWrite.put(byte);
    }

    /* Close stream */
    fileRead.close();
    fileWrite.close();

    // frees memory
    delete dataChar;
    delete table;
    delete code;
    delete codelineTree;
    deleteTree(root);

    cout << "The operation completed." << endl;
    cout <<"You file: " << fileAdress << ".sy" << endl;

}// the end zip


void Archive::unZip(string fileAdress){    

    int lengthTree = 0; // length tree
    int dataSize = 0;   // size data

    ifstream fileReadBin(fileAdress.c_str(), ios::binary);

    if(!fileReadBin){
        cout << "Error! Incorrect path, try again!!! " << endl;
        return;
    }

    /* Read length of the tree and size of the data */
    fileReadBin.read(reinterpret_cast<char*>(&lengthTree), sizeof(int));
    fileReadBin.read(reinterpret_cast<char*>(&dataSize), sizeof(int));

    /* Read tree */
    int position = 0;
    string* codeLineTree = new string;
    char byte = fileReadBin.get();

    for(int i = 0; i < lengthTree; i++){
        bool bitTree = byte & (1 << (7 - position));
        if(bitTree) *codeLineTree +='1';
        else *codeLineTree += '0';

        position++;
        if(position == 8){
            position = 0;
            byte = fileReadBin.get();
        }
    }    

    if(deBug){
    cout << "countTree: " << lengthTree << endl;
    cout << "datasize: " << dataSize << endl;
    cout << "codeline: " << *codeLineTree << endl;
}    

    /* decode tree */
    openTree(codeLineTree);

    if(deBug){
        printTree(root);
    }


    // delete three last symbols from address
    for(int i = fileAdress.length() - 3; i < (int)fileAdress.length();i++){ // удаляем 3 последних символа
            fileAdress.erase(i,1);
            i--;
    }

   /* Read data from file, decode them and write into another file.*/
    position = 0; // position bit in byte
    byte = fileReadBin.get();
    Node* treeRoot = root;

    ofstream fileWrite(fileAdress.c_str(), ios::binary);

    while(dataSize != 0){
        bool bit = byte & (1 << (7 - position));

        if(bit)treeRoot = treeRoot->right;
        else  treeRoot = treeRoot->left;

        if(treeRoot->left == NULL && treeRoot->right == NULL){
            fileWrite.put(treeRoot->symbol);
            dataSize--;
            treeRoot = root;
        }
        position++;
        if(position == 8){
            position = 0;
            byte = fileReadBin.get();
        }
    }
    fileReadBin.close();
    fileWrite.close();

    /* frees memory */
    deleteTree(root);
    delete codeLineTree;


    cout << "The operation completed." << endl;
    cout <<"You file: " << fileAdress << endl;
}


/* // build table "char: value" */
void Archive::buildTable(Node *root, map<char,myVector<bool> > *table, myVector<bool> *code){

     if(root->left != NULL){
         code->push_back(0);
         buildTable(root->left, table, code);
     }
     if(root->right != NULL){
         code->push_back(1);
         buildTable(root->right,table, code);
     }
     if(root->left == NULL || root->right == NULL){
         (*table)[root->symbol] = *code;
     }
     code->pop_back();
}

/* save instructions for unpacking tree */
string* Archive::saveTree(Node *_root){

    myQueue<Node*> qNode; // create queue of the nodes
    qNode.push(_root);
    string* strCode = new string;

    while(!qNode.empty()){
        Node* temp = qNode.front();
        qNode.pop();

        if(temp->left){ // if there is a left son and right son
           *strCode += '0';
           qNode.push(temp->left);
           qNode.push(temp->right);
        }else{          // write 1 and value of the symbol
            *strCode += '1';
            char c = temp->symbol;

            for(int i = 0; i < 8; i++){
                bool b = c & (1 <<(7 - i));
                if(b) *strCode += '1';
                else *strCode += '0';
            }
        }
    }    
    return strCode;
}

/* decode tree */
void Archive::openTree(string* str){

     myQueue<char> bitString; // create queue for code tree
     for(int i = 0; i < (int)str->length(); i++){
         bitString.push((*str)[i]);
     }
     delete str;

     myQueue<Node*> nodeTree; // create queue for node of the tree
     root = 0;

     while(!bitString.empty()){
         if(!root){ // if no root.
             root = new Node();
             nodeTree.push(root);
         }
         char c = bitString.front();
         bitString.pop();

         if(c == '0'){
             Node* parent = nodeTree.front();
             nodeTree.pop();
             Node* leftSon = new Node();
             Node* rightSon = new Node();

             parent->left = leftSon;
             parent->right = rightSon;

             nodeTree.push(leftSon);
             nodeTree.push(rightSon);
         }else{ // if c == '1'
             Node* leaf = nodeTree.front();
             nodeTree.pop();

             char timeChar = 0;
             for(int i = 0; i < 8; i++){
                 timeChar = timeChar | ((bitString.front()-'0') << (7 - i));
                 bitString.pop();
             }
             leaf->symbol = timeChar;
         }
     }
}

// print tree in the console
void Archive::printTree(Node* root, unsigned k){
    if(root != NULL){
        printTree(root->left, k + 3);
                for(unsigned i = 0; i < k; i++){
                    cout << " ";
                }

                if(root->symbol) cout << root->count << " (" << root->symbol << ")" << endl;
                else cout << root->count << endl;
                printTree(root->right, k + 3);
    }

}

// delete tree
void Archive::deleteTree(Node *root){
    if(root->left != NULL){
        deleteTree(root->left);
    }
    if(root->right != NULL){
        deleteTree(root->right);
    }
    delete root;
}



