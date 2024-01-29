#include <iostream>
#include<cstring>
using namespace std;
class Transport
{
protected:
    char destinacija[100];
    int osnovna_cena;
    int rastojanie;
    void kopiraj(const Transport &t)
    {
        strcpy(this->destinacija,t.destinacija);
        this->osnovna_cena=t.osnovna_cena;
        this->rastojanie=t.rastojanie;
    }
public:
    Transport(char *destinacija,int osnovna_cena,int rastojanie)
    {
        strcpy(this->destinacija,destinacija);
        this->osnovna_cena=osnovna_cena;
        this->rastojanie=rastojanie;
    }
Transport(const Transport &t)
{
    kopiraj(t);
}
Transport &operator=(const Transport &t)
{
    if(this!=&t)
    {
        kopiraj(t);
    }
    return *this;
}
    char *getDestinacija()
    {
        return destinacija;
    }
    int getOsnovnaCena()
    {
        return osnovna_cena;
    }
    int getRastojanie()
    {
        return rastojanie;
    }
    void setDestinacija(char *a)
    {
        strcpy(destinacija,a);
    }
    void setOsnovnaCena(int a)
    {
        osnovna_cena=a;
    }
    void setRastojanie(int a)
    {
        rastojanie=a;
    }
    bool operator<(Transport &t)
    {
        return(this->getRastojanie()<t.getRastojanie());
    }
friend    ostream &operator<<(ostream &o,Transport &t)
    {
        o<<t.destinacija<<" "<<t.rastojanie<<" "<<t.cenaTransport()<<endl;
        return o;
    }
    virtual double cenaTransport()=0;
};
class AvtomobilTransport:public Transport
{
private:
    bool sofer;
public:
    AvtomobilTransport(char *destinacija,int osnovna_cena,int rastojanie,bool sofer):Transport(destinacija,osnovna_cena,rastojanie)
    {
        this->sofer=sofer;
    }
    bool getSofer()
    {
        return sofer;
    }
    void setSofer(bool a)
    {
        sofer=a;
    }
    double cenaTransport()
    {
        if(sofer)
            return osnovna_cena*1.2;
        return osnovna_cena;
    }
};
class KombeTransport:public Transport
{
private:
    int broj_luge;
public:
    KombeTransport(char *destinacija,int osnovna_cena,int rastojanie,int broj_luge):Transport(destinacija,osnovna_cena,rastojanie)
    {
        this->broj_luge=broj_luge;
    }
    void setBrojLujge(int a)
    {
        broj_luge=a;
    }
    int getBrojLujge()
    {
        return broj_luge;
    }
    double cenaTransport()
    {
        return osnovna_cena-(200*broj_luge);
    }
};
void pecatiPoloshiPonudi(Transport **niza,int n,Transport &t)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(niza[j]->cenaTransport()>niza[j+1]->cenaTransport())
            {
                Transport *tmp=niza[j];
                niza[j]=niza[j+1];
                niza[j+1]=tmp;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(niza[i]->cenaTransport()>t.cenaTransport())
        {
            cout<<*niza[i];
        }
    }

}
int main(){

char destinacija[20];
int tip,cena,rastojanie,lugje;
bool shofer;
int n;
cin>>n;
Transport  **ponudi;
ponudi=new Transport *[n];

for (int i=0;i<n;i++){

    cin>>tip>>destinacija>>cena>>rastojanie;
    if (tip==1) {
        cin>>shofer;
        ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

    }
    else {
        cin>>lugje;
        ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
    }


}

AvtomobilTransport nov("Ohrid",2000,600,false);
pecatiPoloshiPonudi(ponudi,n,nov);

for (int i=0;i<n;i++) delete ponudi[i];
delete [] ponudi;
return 0;
}
