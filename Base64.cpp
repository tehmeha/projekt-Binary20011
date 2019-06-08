#include<iostream>
#include<bitset>
#include<vector>
#include<fstream>
#include <string>
#include <sstream>
#include <math.h>
using namespace std;
string TextToBinaryString(string words)
{
    string binaryString;
    for (char& _char : words)
    {
        binaryString +=bitset<8>(_char).to_string();
    }
    return binaryString;
}
int main()
{
    string base6Ascii="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int iter=0;
    int temp=0;
    int brojac=0;
    int buffer;
    string encripted;
    string decripted;
    ifstream datoteka;
    string tekst;
    //datoteka.open("test.txt",ios::binary);
    //getline(datoteka,tekst);
    tekst="Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec nec tempor elit, eu blandit diam. Aliquam varius scelerisque orci, ac faucibus lorem. Sed sed interdum eros.";
    cout<<"text: "<<tekst<<endl;
    string tekstBinarni=TextToBinaryString(tekst);
    string decriptedbinary;
    string asciiNumberstring[tekstBinarni.size()];
    string decriptedstring[tekst.size()];
    vector<int>asciiNumbers;
    //cout<<"tekst u binarnom obliku: "<<tekstBinarni<<endl;

    for (int i=0; i<=tekst.size(); i++)
    {
        for (int j=5+iter; j>=0+iter; j--)
        {
            asciiNumberstring[i]+=tekstBinarni[j];
        }
        iter+=6;
    }
    //cout<<"Brojevi iz 6-bita: ";
    for (int i=0; i<=tekst.size(); i++)
    {
        for (int j=0; j<asciiNumberstring[i].length(); j++)
        {
            if(asciiNumberstring[i][j]=='1')
            {
                buffer=j;
                temp+=pow(2,j);
            }
        }
        //cout<<temp<<" ";
        if(asciiNumberstring[i][buffer]=='1')
        {
            asciiNumbers.push_back(temp);
            temp=0;
        }
    }
    temp=0;
    //cout<<endl;
    for (int i=0; i<=asciiNumbers.size(); i++)
    {
        for (int j=0; j<64; j++)
        {
            if(asciiNumbers[i]==j)
                encripted+=base6Ascii[j];
        }

    }
    //cout<<endl;
    int decriptedNumbers[encripted.size()];
    cout<<"Enkriptirano: "<<encripted<<endl;
    //cout<<"dekriptirani brojevi: ";
    for (int i=0; i<encripted.size(); i++)
    {

        for (int j=0; j<64; j++)
        {
            if(encripted[i]==base6Ascii[j])
                decriptedNumbers[i]=j;
        }
        //cout<<decriptedNumbers[i]<<" ";
    }
    //cout<<endl;
    for (int i=0; i<encripted.size(); i++ )
    {
        decriptedbinary+=bitset<6>(decriptedNumbers[i]).to_string();
        //decripted+=static_cast<char>(std::bitset<6>(decriptedbinary).to_ulong() + 64);

    }
    iter=0;
    for (int i=0; i<tekst.size(); i++)
    {
        for (int j=0+iter; j<=7+iter; j++)
        {
            decriptedstring[i]+=decriptedbinary[j];
        }
        iter+=8;
    }
    for (int i=0; i<tekst.size(); i++ )
    {
        stringstream sstream(decriptedstring[i]);
        while(sstream.good())
        {
            std::bitset<8> bits;
            sstream >> bits;
            if(bits != (bitset<8>)00000000)
            {
                decripted+=char(bits.to_ulong());
            }
        }
    }
    cout<<"dekriptirano: "<<decripted<<endl;
}
