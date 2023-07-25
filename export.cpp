#include <iostream>
#include <fstream>

using namespace std;

int main(){
    ofstream myFile;
    myFile.open(".csv");

    for (int i = 0; i < 20; i++)
    {
        myFile << i << "," << i;
    }

}
