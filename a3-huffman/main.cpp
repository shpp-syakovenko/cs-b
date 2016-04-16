#include <iostream>
#include <archive.h>
using namespace std;

void info();

int main()
{
    Archive archive;
    string adress;

    info();   

    while(true){
        string endAdress; // last three symbol of the address
        cout << "Enter adress file: ";
        getline(cin,adress);

        if(adress == "exit") {
            break;
        }

        for(int i = adress.length() - 3; i < (int)adress.length(); i++){
           endAdress += adress[i];
        }
        if(endAdress == ".sy"){
            archive.unZip(adress);
        }else{
            archive.zip(adress);
        }
        cout << endl;
    }    

    cout << endl << "Come again!!!";
    return 0;
}


void info(){
    cout << "Welcome it is ArchiveProgram made by Sergey Yakovenko" << endl;
    cout << "exit - for exit" << endl;
    cout << "Example:" << endl;
    cout << "Encode file: E:\\cs-b\\a3-huffman\\text.txt" << endl;
    cout << "Decode file: E:\\cs-b\\a3-huffman\\text.txt.sy" << endl;

}

