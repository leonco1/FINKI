#include<cstring>
#include<iostream>
using namespace std;
class Vozac
{
protected:
    char ime[100];
    int vozrast;
    int brtrki;
    bool veteran;
public:
    Vozac(char *ime=NULL,int vozrast=0,int brtrki=0,bool veteran=false)
    {
        strcpy(this->ime,ime);
        this->vozrast=vozrast;
        this->brtrki=brtrki;
        this->veteran=veteran;
    }
    Vozac(const Vozac &v)
    {
        strcpy(this->ime,v.ime);
        this->vozrast=v.vozrast;
        this->brtrki=v.brtrki;
        this->veteran=v.veteran;
    }
    ~Vozac()
    {

    }
    friend ostream &operator<<( ostream &o, Vozac &v)
    {
        if(v.veteran)
        {
            o<<v.ime<<endl<<v.vozrast<<endl<<v.brtrki<<endl<<"VETERAN"<<endl;
            return o;
        }
        o<<v.ime<<endl<<v.vozrast<<endl<<v.brtrki<<endl;
        return o;

    }
    virtual double zarabotuvacka()=0;
    virtual double danok()=0;

};
bool operator==(Vozac *v1,Vozac &v2)
{
if(v1->zarabotuvacka()==v2.zarabotuvacka())
    return true;
return false;
}
class Avtomobilist:public Vozac
{
private:
    double cena;
public:
    Avtomobilist(char *ime=NULL,int vozrast=0,int brtrki=0,bool veteran=false,double cena=0):Vozac(ime,vozrast,brtrki,veteran)
    {
        this->cena=cena;
    }
    double zarabotuvacka()
    {
        return(cena/5);
    }
    double danok()
    {
        if(brtrki>10)
            return zarabotuvacka()*0.15;
        return zarabotuvacka()*0.10;
    }

};
class Motociklist:public Vozac
{
private:
    int mok;
public:
    Motociklist(char *ime=NULL,int vozrast=0,int brtrki=0,bool veteran=false,int mok=0):Vozac(ime,vozrast,brtrki,veteran)
                {
                    this->mok=mok;
                }
    double zarabotuvacka()
    {
        return mok*20;
    }
    double danok()
    {
        if(veteran)
            return zarabotuvacka()*0.25;
        return zarabotuvacka()*0.20;
    }
};

int soIstaZarabotuvachka (Vozac **v,int n,Vozac *vz)
{
    int brojac=0;

    for(int i=0;i<n;i++)
    {
        if(v[i]->zarabotuvacka()==vz->zarabotuvacka())
            brojac++;

    }
    return brojac;

}
int main() {
	int n, x;
	cin >> n >> x;
	Vozac **v = new Vozac*[n];
	char ime[100];
	int vozrast;
	int trki;
	bool vet;
	for(int i = 0; i < n; ++i) {
		cin >> ime >> vozrast >> trki >> vet;
		if(i < x) {
			float cena_avto;
			cin >> cena_avto;
			v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
		} else {
			int mokjnost;
			cin >> mokjnost;
			v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
		}
	}
	cout << "=== DANOK ===" << endl;
	for(int i = 0; i < n; ++i) {
		cout << *v[i];
		cout << v[i]->danok() << endl;
	}
	cin >> ime >> vozrast >> trki >> vet;
	int mokjnost;
	cin >> mokjnost;
	Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
	cout << "=== VOZAC X ===" << endl;
	cout << *vx;
	cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
	cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
	return 0;
}
