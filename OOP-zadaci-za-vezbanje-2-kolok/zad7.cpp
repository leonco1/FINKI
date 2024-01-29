#include <iostream>
#include<cstring>
using namespace std;
class OutOfBoundException
{
public:
    void pecati()
    {
        cout<<"Brojot na pin kodovi ne moze da go nadmine dozvolenoto"<<endl;
    }
};
class Karticka
{
protected:
    char smetka[16];
    int pin;
    bool dopolnitelen_pin;
public:
    Karticka(char *smetka,int pin)
    {
        strcpy(this->smetka,smetka);
        this->pin=pin;
        this->dopolnitelen_pin=false;
    }
    virtual bool getDopolnitelenPin()
    {
        return dopolnitelen_pin;
    }
    char *getSmetka()
    {
        return smetka;
    }
    virtual int presmetajTezina()
    {
        int tmp,br=0;
        tmp=pin;
        while(tmp)
        {
            br++;
            tmp/=10;
        }
        return br;
    }
    friend ostream &operator<<(ostream &o,Karticka &k)
    {
        o<<k.smetka<<": "<<k.presmetajTezina()<<endl;
        return o;
    }
int getPin()
{
    return pin;
}

};
class SpecijalnaKarticka:public Karticka
{
private:
    int *pinovi;
    int n;
    static const int P;
public:
    SpecijalnaKarticka(char *smetka,int pin):Karticka(smetka,pin)
    {
        this->n=0;
        this->pinovi=new int[0];
    dopolnitelen_pin=true;

    }
    ~SpecijalnaKarticka()
    {
        delete[]pinovi;
    }
    int presmetajTezina()
    {
        int t1=Karticka::presmetajTezina();
        return t1+n;
    }
    SpecijalnaKarticka &operator+=(int &p)
    {
        if(n>P)
            throw OutOfBoundException();
        int *tmp=new int[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=pinovi[i];
        }
        tmp[n++]=p;
            delete[]pinovi;
            pinovi=tmp;
            return *this;
    }
};
const int SpecijalnaKarticka::P=4;
class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    static void setLIMIT(int a)
    {
        LIMIT=a;
    }
     ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }
    void pecatiKarticki()
    {
        cout<<"Vo bankata "<<naziv<<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(karticki[i]->presmetajTezina()<=LIMIT)
                cout<<*karticki[i];
        }
    }
    void dodadiDopolnitelenPin(char *smetka,int novPin)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(karticki[i]->getSmetka(),smetka)==0 && karticki[i]->getDopolnitelenPin())
            {
                SpecijalnaKarticka *sk=dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                try{*sk+=novPin;}
                catch (OutOfBoundException &o)
                {
                    o.pecati();
                }
            }
        }
    }
};
int Banka::LIMIT=7;
int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;

   komercijalna.dodadiDopolnitelenPin(smetka,pin);

}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();
}

