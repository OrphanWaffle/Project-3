#pragma once
#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include <typeinfo>
using namespace std;

class Farmacie
{
public:
    Farmacie() {}
    virtual ~Farmacie(){}
};

class Farmacie_Offline : public Farmacie
{
    string denumire;
    int nr_ang,profit;
public:
    Farmacie_Offline();
    ~Farmacie_Offline();
    void operator = (const Farmacie_Offline&);
    friend istream& operator >> (istream&, Farmacie_Offline&);
    friend ostream& operator << (ostream&, Farmacie_Offline&);
};

class Farmacie_Online : public Farmacie
{
    string web;
    int nr_vizitatori,discount;
public:
    Farmacie_Online();
    ~Farmacie_Online();
    void operator = (const Farmacie_Online&);
    friend istream& operator >> (istream&, Farmacie_Online&);
    friend ostream& operator << (ostream&, Farmacie_Online&);
    int get_nr_viz(){ return nr_vizitatori; }
};

void exc(int a)
{
    try { if(a<0) throw 1;}
    catch(int i)
    {
        cout<<"nr angajati sau nr de vizitatori nu paote sa fie negativ";
        terminate();
    }
}

Farmacie_Offline::Farmacie_Offline() { denumire='\0'; nr_ang=0; profit=0;}
Farmacie_Offline::~Farmacie_Offline(){ }
void Farmacie_Offline::operator = (const Farmacie_Offline& F)
{
    denumire=F.denumire;
    nr_ang=F.nr_ang;
    profit=F.profit;
}
istream& operator>>(istream& in,Farmacie_Offline& F)
{
    cout<<"  Denumire farmacie: ";
    in>>F.denumire;
    cout<<"  Nr de angajati: ";
    in>>F.nr_ang; exc(F.nr_ang);
    cout<<"  Profitul: ";
    in>>F.profit;
    return in;
}
ostream& operator<<(ostream& out,Farmacie_Offline& F)
{
    out<<"Denumire farmacie este: ";
    out<<F.denumire<<" // ";
    out<<"angajati: "<<F.nr_ang;
    out<<" // profit: "<<F.profit<<endl;
    return out;
}
///-------------------

Farmacie_Online::Farmacie_Online(){ web='\0'; nr_vizitatori=0; discount=0; }
Farmacie_Online::~Farmacie_Online(){ }
void Farmacie_Online::operator = (const Farmacie_Online& F)
{
    web=F.web;
    nr_vizitatori=F.nr_vizitatori;
    discount=F.discount;
}
istream& operator>>(istream& in,Farmacie_Online& F)
{
    cout<<"  Web-ul farmaciei: ";
    in>>F.web;
    cout<<"  Nr de vizitatori: ";
    in>>F.nr_vizitatori; exc(F.nr_vizitatori);
    cout<<"  Discountul: ";
    in>>F.discount;
    return in;
}
ostream& operator<<(ostream& out,Farmacie_Online& F)
{
    out<<"Web-ul farmaciei este: ";
    out<<F.web<<" // ";
    out<<"nr_vizitatori: "<<F.nr_vizitatori;
    out<<" // Discount: "<<F.discount<<endl;
    return out;
}

///------------------------------------------------
template<class T> class Gestionare_Farmacii;
template<class T> istream& operator >>(istream&,Gestionare_Farmacii<T>&);
template<class T> ostream& operator <<(ostream&,Gestionare_Farmacii<T>&);

template <class T>
class Gestionare_Farmacii
{
    const T id_lant;
    int index;
    static int n;
    vector<Farmacie*> v;
public:
    //Gestionare_Farmacii ();
    Gestionare_Farmacii (T n);
    ~Gestionare_Farmacii();
    void operator = (const Gestionare_Farmacii<T>&);
    friend istream& operator >> <T>(istream&,Gestionare_Farmacii<T>&);
    friend ostream& operator << <T>(ostream&,Gestionare_Farmacii<T>&);
    void operator += (T);
    static const int get_n() {return n;}
    static void set_n (int x){n=x;}
    vector<Farmacie *>::iterator get_beg(){ return v.begin(); }
    vector<Farmacie *>::iterator get_end() { return v.end(); }
};

template <>
class Gestionare_Farmacii<Farmacie_Online>
{
    int nr_tot;
public:
    //Gestionare_Farmacii();
    template<class T>
    Gestionare_Farmacii(Gestionare_Farmacii<T>&);
    ~Gestionare_Farmacii(){}
    void afisare_utilizatori(){cout<<nr_tot<<" ";}
};

template<class T>
Gestionare_Farmacii<Farmacie_Online>::Gestionare_Farmacii(Gestionare_Farmacii<T>& F)
{
    nr_tot=0;
    vector< Farmacie* >::iterator it;
    for(it=F.get_beg();it!=F.get_end();it++)
    {
        if(typeid(**it)==typeid(Farmacie_Online))
        {
            nr_tot=nr_tot+(*dynamic_cast<Farmacie_Online*>(*it)).get_nr_viz();
        }
    }
}
//template <class T>
//Gestionare_Farmacii<T>::Gestionare_Farmacii(){ index=0;}
template <class T>
Gestionare_Farmacii<T>::Gestionare_Farmacii(T n):id_lant(n){ index=0; n=0;}

template <class T>
Gestionare_Farmacii<T>::~Gestionare_Farmacii()
{
    typename vector< Farmacie* >::iterator it;
    for(it=v.begin();it!=v.end();it++) delete(*it);
    v.clear();
    vector<Farmacie *>().swap(v);
}

template<class T>
void Gestionare_Farmacii<T>::operator =(const Gestionare_Farmacii<T>& F)
{
    index=F.index;
    v=F.v;
}
///SUPER
template <class T>
istream& operator>> (istream&in, Gestionare_Farmacii<T>& F)
{
    int x;  char y='d';
    vector< Farmacie* >::iterator it;
    while(y=='d')
    {
        cout<<"ce tip de farmacie: "; cin>>x; cout<<"\n";
        switch(x)
        {
        case 1:
            F.index++;
            F.v.push_back(new Farmacie_Offline);
            it=(F.v.end()-1);
            in >> *dynamic_cast<Farmacie_Offline*>(*it);
            break;
        case 2:
            F.index++;
            F.v.push_back(new Farmacie_Online);
            it=(F.v.end()-1);
            in >> *dynamic_cast<Farmacie_Online*>(*it);
            break;

        }
        cout<<"adaugam farmacie (d/n)?"; cin>>y; cout<<"\n";
    }
    return in;
}
template<class T>
ostream& operator<< (ostream&out, Gestionare_Farmacii<T>& F)
{
    out<<"indexul: "<< F.index<<" // ";
    out<<"id_lant: "<< F.id_lant<<"// \n";
    vector< Farmacie* >::iterator it;
    for(it=F.v.begin();it!=F.v.end();it++)
    {
        if(typeid(**it)==typeid(Farmacie_Online)) out<<*dynamic_cast<Farmacie_Online*>(*it);
        if(typeid(**it)==typeid(Farmacie_Offline)) out<<*dynamic_cast<Farmacie_Offline*>(*it);
    }
    return out;
}

template<class T>
void Gestionare_Farmacii<T>::operator +=(T i)
{
    cout<<"A mai fost adaugata o farmacie in lantul "<<id_lant;
    vector< Farmacie* >::iterator it;
    index++;
    v.push_back(new Farmacie_Online);
    it=(v.end()-1);
    cin >> *dynamic_cast<Farmacie_Online*>(*it);
}
