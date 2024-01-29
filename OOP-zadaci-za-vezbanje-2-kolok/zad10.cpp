#include <iostream>
#include <string.h>
#include <cstdlib>
using namespace std;
class NegativnaVrednost
{
public:
    void pecati()
    {
    cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};
class Oglas
{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    void kopiraj(const Oglas &o)
    {
        strcpy(this->naslov,o.naslov);
        strcpy(this->kategorija,o.kategorija);
        strcpy(this->opis,o.opis);
        this->cena=o.cena;

    }
public:
    Oglas()
    {
        strcpy(this->naslov,"");
        strcpy(this->kategorija,"");
        strcpy(this->opis,"");
        this->cena=0;

    }
    Oglas(char *naslov,char *kategorija,char *opis,float cena)
    {
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena=cena;
    }
    Oglas(const Oglas &o)
    {
        kopiraj(o);
    }
    Oglas &operator=(const Oglas &o)
    {
        if(this!=&o)
            kopiraj(o);
            return *this;
    }
    char *getKategorija()
    {
        return kategorija;
    }
    bool operator>(Oglas &o)
    {
        return(this->cena>o.cena);

    }
     friend ostream &operator<<(ostream &o,Oglas &og)
    {
        o<<og.naslov<<endl<<og.opis<<endl<<og.cena<<" evra"<<endl;
        return o;
    }
    float getCena()
    {
        return cena;
    }
};
class Oglasnik
{
private:
    char naziv[50];
    Oglas *oglasi;
    int n;
    void kopiraj(const Oglasnik &o)
    {
        strcpy(this->naziv,o.naziv);
        this->n=o.n;
        this->oglasi=new Oglas[n];
        for(int i=0;i<n;i++)
            this->oglasi[i]=o.oglasi[i];
    }
public:
    Oglasnik()
    {
        strcpy(this->naziv,"");
    }
        Oglasnik(char *naziv)
        {
            strcpy(this->naziv,naziv);
            this->oglasi=new Oglas[0];
            this->n=0;
        }
        Oglasnik(const Oglasnik &o)
        {
            kopiraj(o);
        }
        Oglasnik &operator=(const Oglasnik &o)
        {
            if(this!=&o)
            {
                delete[]oglasi;
                kopiraj(o);
            }
            return *this;
        }
        Oglasnik &operator +=(Oglas &o)
        {
            if(o.getCena()<0)
                throw NegativnaVrednost();

                Oglas *tmp=new Oglas[n+1];
                for(int i=0;i<n;i++)
                    tmp[i]=oglasi[i];
                tmp[n++]=o;
                delete[]oglasi;
                oglasi=tmp;
                return *this;

        }
      friend  ostream &operator<<(ostream &o,Oglasnik &og)
        {
            o<<og.naziv<<endl;
            for(int i=0;i<og.n;i++)
                o<<og.oglasi[i]<<endl;
                return o;
        }

        ~Oglasnik()
        {
         delete[]oglasi;
        }
        void oglasiOdKategorija(const char *k)
        {
         for(int i=0;i<n;i++)
         {
             if(strcmp(oglasi[i].getKategorija(),k)==0)
                cout<<oglasi[i]<<endl;

         }
        }
        void najniskaCena()
        {
            double minimum=oglasi[0].getCena();
            int index=0;
            for(int i=1;i<n;i++)
            {
                if(minimum>oglasi[i].getCena())
                {
                    minimum=oglasi[i].getCena();
                    index=i;
                }
            }
            cout<<oglasi[index];
        }
};
int main(){

    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
    	cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
		cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
      	cout<<"-----Test oglasOdKategorija -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
    	cout<<"-----Test Exception -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
			ogl+=o;
        	}
        	catch (NegativnaVrednost &n)
        	{
        	    n.pecati();
        	}
        }
        cout<<ogl;

    }
    else if (tip==6){
    	cout<<"-----Test najniskaCena -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
            ogl+=o;
        	}
        	catch(NegativnaVrednost &n)
        	{
        	    n.pecati();
        	}
        }
        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }
    else if (tip==7){
    	cout<<"-----Test All -----" <<endl ;
      	cin.get();
		cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
        	Oglas o(naslov, kategorija, opis, cena);
        	try{
            ogl+=o;
        	}
        	catch(NegativnaVrednost &n)
        	{
        	    n.pecati();
        	}
        }
        cout<<ogl;

        cin.get();
        cin.get();
		cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
      	ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
      	ogl.najniskaCena();

    }

	return 0;
}
