#include <iostream>
#include<cstring>
using namespace std;
enum tip{smartphone=0,computer};
class InvalidProductionDate
{
public:
    void pecati()
    {
    cout<<"Невалидна година на производство"<<endl;
    }
};
class Device
{
private:
    char ime[100];
    tip tipDevice;
    int godina;
    static float casovi;
public:
    Device()
    {
    }
    Device(char *ime,tip tipDevice,int godina)
    {
        strcpy(this->ime,ime);
        this->tipDevice=tipDevice;
        this->godina=godina;
    }
    static void setPocetniCasovi(float a)
    {
        casovi=a;
    }
    int getGod()
    {
        return godina;
    }
    char *getTip()
    {
        if(tipDevice==smartphone)
            return "Mobilen";
        return "Laptop";
    }
    float getCasovi()
    {
        float zbir=casovi;
        if(godina>2015)
        zbir+=2.0;
        if(tipDevice==computer)
            zbir+=2.0;
        return zbir;

    }

friend ostream &operator<<(ostream &o,Device &d)
    {
        o<<d.ime<<endl<<d.getTip()<<" "<<d.getCasovi()<<endl;
        return o;
    }
};
float Device::casovi=1;
class MobileServis
{
private:
    char adresa[100];
    Device *devices;
    int n;
public:
    MobileServis()
    {
    }
    MobileServis(char *adresa)
    {
        strcpy(this->adresa,adresa);
        this->devices=new Device[0];
        this->n=0;
    }
    MobileServis &operator+=(Device &d)
    {
        if(d.getGod()>2019||d.getGod()<2000)
            throw InvalidProductionDate();
        Device *tmp=new Device[n+1];
        for(int i=0;i<n;i++)
            tmp[i]=devices[i];
        tmp[n++]=d;
        delete[]devices;
        devices=tmp;
        return *this;
    }
    void pecatiCasovi()
    {
        cout<<"Ime: "<<adresa<<endl;
        for(int i=0;i<n;i++)
            cout<<devices[i];
    }
//    ~MobileServis()
//    {
//        delete[]devices;
//    }
};
int main()
{
	int testCase;
	cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> tipDevice;
		cin >> godina;
		Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
		MobileServis t(ime);
        cout<<ig;
		}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
	}
	if (testCase == 3){
		cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{t+=tmp;}
            catch(InvalidProductionDate &i)
            {
                i.pecati();
            }
        }
        t.pecatiCasovi();
	}
	if (testCase == 4){
		cout <<"===== Testiranje na konstruktori ======"<<endl;
		 cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{t+=tmp;}
            catch(InvalidProductionDate &i)
            {
                i.pecati();
            }

        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}
	if (testCase == 5){
		cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            try{t+=tmp;}
            catch(InvalidProductionDate &i)
            {
                i.pecati();
            }
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
		Device::setPocetniCasovi(2);
        t.pecatiCasovi();
	}

		if (testCase == 6){
		cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
		cin>>ime;
        cin >> n;
		MobileServis t(ime);
		for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            try{t+=tmp;}
            catch(InvalidProductionDate &i)
            {
                i.pecati();
            }
        }
		Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
	}

	return 0;

}
