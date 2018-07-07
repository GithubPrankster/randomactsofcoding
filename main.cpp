#include <iostream>
#include <fstream>
#include <string>

int versionNum = 2;

using namespace std;

int main(){
    cout << "Version " << versionNum << " of Jimmy's Unlikely Editor!" << endl;
    string filename;
    getline(cin, filename);
    ofstream thefile(filename+".txt");

    string prompt;
    bool writting = true;
    getline(cin, prompt);
    if(prompt == "write"){
            while(writting){
                string written;
                getline(cin, written);
                if(written == "|"){
                    writting = false;
                } else {
                    thefile << written;
                }
                thefile << endl;

            }

    } else {
        cout << "goof off." << endl;

    }


}
