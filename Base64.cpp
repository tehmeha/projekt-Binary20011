#include<iostream>
#include<bitset>
#include<fstream>
using namespace std;
int main()
{
    int iter=0;
    ifstream datoteka;
    string tekst;
    datoteka.open("test.txt");
    getline(datoteka,tekst);
    while(iter!=tekst.length())
    {
        for(int i=iter;i<i+6;i++)
        {

        }
    }
}
