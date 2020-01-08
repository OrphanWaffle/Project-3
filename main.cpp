#include <iostream>
#include "clase.h"
#include <vector>
using namespace std;

template<class T>
void citire(vector< Gestionare_Farmacii<T> > a,int n)
{
    int x;
    for(int i=0;i<n;i++)
    {
        cout<<"Ce id_lant va avea lantul de farmacii "<<i<<": ";
        cin>>x;
        a.push_back(Gestionare_Farmacii<T>(x));
    }
    typename vector< Gestionare_Farmacii<T> >::iterator it;

    for(it=a.begin();it!=a.end();it++) {cin>>*it; cout<<"-----\n";}
    //*(a.begin())+=1;
    for(it=a.begin();it!=a.end();it++) cout<<*it;

    vector<Gestionare_Farmacii<Farmacie_Online> > A;
    vector<Gestionare_Farmacii<Farmacie_Online> >::iterator IT;
    for(it=a.begin();it!=a.end();it++) A.push_back(Gestionare_Farmacii<Farmacie_Online>(*it));
    cout<<endl;
    for(IT=A.begin();IT!=A.end();IT++) IT->afisare_utilizatori();
    cout<<endl<<Gestionare_Farmacii<int>::get_n();
    //Gestionare_Farmacii<Farmacie_Online> *A=new Gestionare_Farmacii<Farmacie_Online>(*(a.begin()));
    //A->afisare_utilizatori();
}
template <class T>
int Gestionare_Farmacii<T>::n=0;
int main()
{
    int n;
    cout<<"1.Farmacie offline \n2.Farmacie online\n";
    cout<<"Cate lantiru de farmacii vor fi? : "; cin>>n;
    vector< Gestionare_Farmacii<int> > a;
    Gestionare_Farmacii<int>::set_n(n);
    citire(a,n);

    return 0;
}
