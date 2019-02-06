#include<iostream>
#include<vector>
#include<fstream>
#include <time.h>
#include<math.h>
#include<algorithm>
#include <iomanip>
using namespace std;
bool isPrime(unsigned long long int a)
{
    for(int i=2; i<=sqrt(a); ++i)
    {

        if(a%i==0)
        {
            return false;
            break;
        }
    }
    return true;
}
void *keyGeneration(unsigned long long int a[])
{
    unsigned long long int p=rand();
    unsigned long long int q=rand();
    bool pChecker=0;
    bool qChecker=0;
    while(pChecker!=1 && p!=q)
    {
        pChecker=isPrime(p);

        if(pChecker==0)
        {
            p=rand();
        }
    };
    while(qChecker!=1 && p!=q)
    {
        qChecker=isPrime(q);

        if(qChecker==0)
        {
            q=rand();
        }
    };
    cout<<p<<" "<<q<<endl;
    a[0]=p*q;
    unsigned long long int fiN=(p-1)*(q-1);
    unsigned long long int e=2;
    while(e<fiN)
    {
        if(__gcd(e,fiN)==1 && __gcd(e,fiN)==1)
        {
            break;
        }
        else
        {

            e++;

        }

    }
    a[1]=e;
    unsigned long long int d=1;
    while(((e*d)%fiN)!=1)
    {
        d++;
    }
    a[2]=d;
    return a;
}
void encrypt(unsigned long long int n,unsigned long long int e,string fIn,string fileOut)
{
    unsigned long long int c;
    ifstream in;
    ofstream out;
    in.open(fIn.c_str(),ios::binary);
    out.open(fileOut.c_str());
    string text;
    //cout<<"Tekst iz file-a"<<" | "<<"ascii oznaka znaka iz file-a"<<" | "<<"dobiveni znak"<<" | "<<"ascii oznaka dobivenog znaka"<<endl;
    while(!in.eof())
    {
        getline(in,text);
        for(int i=0; i<text.length(); i++)
        {
            c=pow((int)text[i],e);
            c=c%n;
            char f=c;
            //cout<<text[i]<<" | "<<(int)text[i]<<" | "<<f<<" | "<<(int)f<<endl;
            //!u lijevom stupcu je tekst iz originalnog filea, a u desnom je tekst koji ce se upitsti u datoteku
            cout<<text[i]<<" "<<f<<endl;

            out<<f;
        }
    }
    in.close();
    out.close();
}
void decrypt(unsigned long long int n,unsigned long long int d,string fileIn,string fileOut)
{
    unsigned long long int m;
    double mint;
    double mDob1;
    unsigned long long int m_str;
    double mDouble;
    setprecision(1000000000);
    ifstream in;
    ofstream out;
    in.open(fileIn.c_str(),ios::binary);
    out.open(fileOut.c_str());
    string encr;
    //cout<<"Tekst iz file-a"<<" | "<<"ascii oznaka znaka iz file-a"<<" | "<<"dobiveni znak"<<" | "<<"ascii oznaka dobivenog znaka"<<endl;
    while(!in.eof())
    {
        getline(in,encr);

        for(int i=0; i<encr.length(); i++)
        {
            m=pow((int)encr[i],d);
            mDouble=m%n;
            mDob1=modf(mDouble , &mint);
            m=(mDouble-mDob1)*n;
            char g=m;
            //cout<<encr[i]<<" | "<<(int)encr[i]<<" | "<<g<<" | "<<(int)g<<endl;
            //!u lijevom stupcu je tekst iz enkriptiranog filea, a u desnom je tekst koji ce se upitsti u datoteku
            cout<<encr[i]<<" "<<g<<" "<<mDouble<<" "<<(int)mDouble<<" "<<(mDouble-mDob1)<<endl;
            out<<g;

        }
    }

    in.close();
    out.close();
}
int main()
{
    srand(time(0));
    int unos;
    ifstream in;
    ofstream out;
    //unsigned int PUBLIC_KEY=rand(rand() % 10 + 1);
    unsigned long long int keys[3];
    string tekstIn="test.txt";
    string enkripcija= " ";
    string dekripcija= " ";
    string tekstOut1="encrypt-test.txt";
    string tekstOut2="decrypt-test.txt";
    string ciphertextStr;
    string textDecoded;
    vector<string> datoteka;
    keyGeneration(keys);
    /**
    for(int i=0; i<3; i++)
    {
        if(i==0)
        {
            cout<<i+1<<" "<<" "<<"N"<<" "<<keys[i]<<endl;
        }
        else if(i==1)
        {
            cout<<i+1<<" "<<" "<<"E"<<" "<<keys[i]<<endl;
        }
        else if(i==2)
        {
            cout<<i+1<<" "<<" "<<"D"<<" "<<keys[i]<<endl;
        }
    }
    **/
    //cout<<"--------------------------------------------------"<<endl;
    //cout<<"| UNESI IME TXT DATOTEKE (SA .TXT NASTAVKOM):";
    //cin>>tekstIn;
    in.open(tekstIn);
    while(true)
    {
        cout<<"---------------------IZBORNIK---------------------"<<endl;
        cout<<"|"<<"1. ENKODIRAJ"<<"                                    |"<<endl;
        cout<<"|"<<"2. DEKODIRAJ"<<"                                    |"<<endl;
        cout<<"|"<<"3. EXIT"<<"                                         |"<<endl;
        cout<<"--------------------------------------------------"<<endl;
        cout<<"| IZBOR: ";
        cin>>unos;

        if(unos==1)
        {
            cout<<"--------------------------------------------------"<<endl;
            //cout<<"|"<<"UNESI IME DATOTEKE U KOJU ZELIS SPREMITI ENKODIRANI TEKST:";
            //cin>>tekstOut1;
            encrypt(keys[0],keys[1],tekstIn,tekstOut1);
        }
        if(unos==2)
        {
            cout<<"--------------------------------------------------"<<endl;
            //cout<<"|"<<"UNESI IME DATOTEKE U KOJU ZELIS SPREMITI DEKODIRANI TEKST:";
            //cin>>tekstOut2;
            decrypt(keys[0],keys[2],tekstOut1,tekstOut2);
        }
        else if(unos==3)
        {
            return 0;
        }
    }
}

