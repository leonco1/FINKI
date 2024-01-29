#include <iostream>
#include<cstring>
#include<cstdlib>
using namespace std;
class SMS
{
protected:
    double osnovna_cena;
    char pretplata[15];
public:
    SMS()
    {
    }
    SMS(char *pretplata,double osnovna_cena)
    {
        this->osnovna_cena=osnovna_cena;
        strcpy(this->pretplata,pretplata);
    }
    SMS(const SMS &s)
    {
        strcpy(this->pretplata,s.pretplata);
        this->osnovna_cena=s.osnovna_cena;
    }

    virtual double SMS_cena() {
    return osnovna_cena;
    }

    friend ostream &operator<<(ostream &o,SMS &s)
    {
       o<<"Tel: "<<s.pretplata<<" - cena: "<<s.SMS_cena()<<"den. "<<endl;
        return o;

    }

};
class RegularSMS:public SMS
{
private:
    bool roaming;
    char text[1000];
    static int rprocent;
public:
    RegularSMS(char *pretplata,double osnovna_cena,char *text,bool roaming):SMS(pretplata,osnovna_cena)
    {
        this->roaming=roaming;
        strcpy(this->text,text);
    }
    static void set_rProcent(int a)
    {
        rprocent=a;
    }
    int broj()
    {
        int tmp=strlen(text);
        int brojac=0;
        while(tmp>0)
        {
            tmp-=160;
            brojac++;
        }
        return brojac;
    }
double SMS_cena()
{

    double zbir=SMS::SMS_cena();
    if(roaming)
         zbir=zbir+(zbir*rprocent/100);
         else zbir=zbir+(zbir*0.18);
         return zbir*broj();
}
};
int RegularSMS::rprocent=300;
class SpecialSMS:public SMS
{
private:
    bool humanitarna;
    static int sprocent;
public:
    SpecialSMS()
    {
        this->humanitarna=true;
    }
    SpecialSMS(char *pretplata,double osnovna_cena,bool humanitarna):SMS(pretplata,osnovna_cena)
    {
        this->humanitarna=humanitarna;
    }
    double SMS_cena()
    {
        if(humanitarna)
            return SMS::SMS_cena();
        else
            return SMS::SMS_cena()+SMS::SMS_cena()*sprocent/100;
    }
    static void set_sProcent(int a)
    {
        sprocent=a;
    }

};
int SpecialSMS::sprocent=150;
void vkupno_SMS(SMS **poraka,int n)
{
    double rbrojac,sbrojac,rzbir,szbir;
    rbrojac=sbrojac=rzbir=szbir=0;
    for(int i=0;i<n;i++)
    {
        if(dynamic_cast<RegularSMS*>(poraka[i]))
        {
            rzbir+=poraka[i]->SMS_cena();
            rbrojac++;
        }
        else if(dynamic_cast<SpecialSMS*>(poraka[i]))
        {
            sbrojac++;
            szbir+=poraka[i]->SMS_cena();
    }

}
cout<<"Vkupno ima "<<rbrojac<<" regularni SMS poraki i nivnata cena e: "<<rzbir<<endl;
 cout<<"Vkupno ima "<<sbrojac<<" specijalni SMS poraki i nivnata cena e: "<<szbir<<endl;
}

int main(){

	char tel[20], msg[1000];
	float cena;
	float price;
    int p;
	bool roam, hum;
	SMS  **sms;
	int n;
	int tip;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing RegularSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new RegularSMS(tel, cena, msg, roam);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 2){
		cout << "====== Testing SpecialSMS class ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i < n; i++){
			cin >> tel;
			cin >> cena;
			cin >> hum;
			cout << "CONSTRUCTOR" << endl;
			sms[i] = new SpecialSMS(tel, cena, hum);
			cout << "OPERATOR <<" << endl;
			cout << *sms[i];
		}
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
	if (testCase == 3){
		cout << "====== Testing method vkupno_SMS() ======" << endl;
		cin >> n;
		sms = new SMS *[n];

		for (int i = 0; i<n; i++){

			cin >> tip;
			cin >> tel;
			cin >> cena;
			if (tip == 1) {

				cin.get();
				cin.getline(msg, 1000);
                cin >> roam;

				sms[i] = new RegularSMS(tel, cena, msg, roam);

			}
			else {
				cin >> hum;

				sms[i] = new SpecialSMS(tel, cena, hum);
			}
		}

		vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
		delete[] sms;
	}
    if (testCase == 4){
		cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
			sms1 = new RegularSMS(tel, cena, msg, roam);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
            cin.get();
			cin.getline(msg, 1000);
			cin >> roam;
        	cin >> p;
        	RegularSMS::set_rProcent(p);
        	sms2 = new RegularSMS(tel, cena, msg, roam);
        	cout << *sms2;

        delete sms1, sms2;
	}
    if (testCase == 5){
		cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
        	cin >> tel;
			cin >> cena;
			cin >> hum;
			sms1 = new SpecialSMS(tel, cena, hum);
			cout << *sms1;

            cin >> tel;
			cin >> cena;
			cin >> hum;
        	cin >> p;
        	SpecialSMS::set_sProcent(p);
        	sms2 = new SpecialSMS(tel, cena, hum);
        	cout << *sms2;

        delete sms1, sms2;
	}

	return 0;
}

