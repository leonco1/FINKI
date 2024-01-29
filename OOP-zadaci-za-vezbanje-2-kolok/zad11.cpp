#include <iostream>
#include<cstring>
using namespace std;
class Delo
{
private:
    char ime[51];
    int godina;
    char zemja[51];
public:
    Delo()
    {
        strcpy(this->ime,"");
        this->godina=0;
        strcpy(this->zemja,"");

    }
    Delo(char *ime,int godina,char *zemja)
    {
        strcpy(this->ime,ime);
        this->godina=godina;
        strcpy(this->zemja,zemja);
    }
    Delo(const Delo &d)
    {
        strcpy(this->ime,d.ime);
        this->godina=d.godina;
        strcpy(this->zemja,d.zemja);
    }
    Delo &operator=(const Delo &d)
    {
        if(this!=&d)
        {
            strcpy(this->ime,d.ime);
        this->godina=d.godina;
        strcpy(this->zemja,d.zemja);
        }
        return *this;
    }
    bool operator==(Delo &d)
    {
        return(strcmp(this->ime,d.ime)==0);
    }
    char *getIme()
    {
        return ime;
    }
    int getGod()
    {
        return godina;
    }
    char *getZemja()
    {
        return zemja;
    }
    void setIme(char *i)
    {
        strcpy(this->ime,i);
    }
    void setGod(int a)
    {
        this->godina=a;
    }
    void setZemja(char *z)
    {
        strcpy(this->zemja,z);
    }
};
class Pretstava
{
private:
    Delo del;
    int br_karti;
    char datum[16];
public:
    Pretstava()
    {
    }
    Pretstava(Delo d,int br_karti,char *datum)
    {
        this->del=d;
        this->br_karti=br_karti;
        strcpy(this->datum,datum);
    }
    Delo getDelo()
    {
        return del;
    }
    int getBr_karti()
    {
        return br_karti;
    }
    char *getDatum()
    {
        return datum;
    }
    void setDelo(Delo &delo)
    {
        this->del=delo;
    }
    void setBr_karti(int a)
    {
        this->br_karti=a;
    }
    void setDatum(char *a)
    {
        strcpy(this->datum,a);
    }
     virtual int cena()
    {
        if(del.getGod()>1900)
        {
            if(strcmp(del.getZemja(),"Italija")==0)
                return 150;
                if(strcmp(del.getZemja(),"Rusija")==0)
                    return 200;
                return 130;
        }
        if(del.getGod()>=1800 &&del.getGod()<=1900)
        {
            if(strcmp(del.getZemja(),"Italija")==0)
            return 175;
            if(strcmp(del.getZemja(),"Rusija")==0)
                return 225;
            return 155;
        }
        else

        {
            if(strcmp(del.getZemja(),"Italija")==0)
                return 200;
            if(strcmp(del.getZemja(),"Rusija")==0)
                return 250;
            return 180;
        }
    }


};
class Balet:public Pretstava
{
private:
    static int baletcena;
public:
    Balet(Delo d,int br_karti,char *datum):Pretstava(d,br_karti,datum)
    {

    }
    static void setCenaBalet(int a)
    {
        Balet::baletcena=a;
    }
    int cena()
    {
        return Pretstava::cena()+baletcena;
    }
};
int Balet::baletcena=150;
class Opera:public Pretstava
{
public:
    Opera(Delo d,int br_karti,char *datum):Pretstava(d,br_karti,datum)
    {

    }
};
int prihod(Pretstava **niza,int n)
{
    int zbir=0;
    for(int i=0;i<n;i++)
        zbir+=niza[i]->cena()*niza[i]->getBr_karti();
    return zbir;

}
int brojPretstaviNaDelo(Pretstava **niza,int n,Delo del)
{
    int brojac=0;
    for(int i=0;i<n;i++)
    {
        if(niza[i]->getDelo()==del)
            brojac++;
    }
    return brojac;
}
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}
int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
    case 1:
    //Testiranje na klasite Opera i Balet
    {
        cout<<"======TEST CASE 1======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->getDelo().getIme()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->getDelo().getIme()<<endl;
    }break;

    case 2:
    //Testiranje na  klasite Opera i Balet so cena
    {
        cout<<"======TEST CASE 2======="<<endl;
        Pretstava* p1=readPretstava();
        cout<<p1->cena()<<endl;
        Pretstava* p2=readPretstava();
        cout<<p2->cena()<<endl;
    }break;

    case 3:
    //Testiranje na operator ==
    {
        cout<<"======TEST CASE 3======="<<endl;
        Delo f1=readDelo();
        Delo f2=readDelo();
        Delo f3=readDelo();

        if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
        if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

    }break;

    case 4:
    //testiranje na funkcijata prihod
    {
        cout<<"======TEST CASE 4======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();

        }
        cout<<prihod(pole,n);
    }break;

    case 5:
    //testiranje na prihod so izmena na cena za 3d proekcii
    {
        cout<<"======TEST CASE 5======="<<endl;
        int cenaBalet;
        cin>>cenaBalet;
        Balet::setCenaBalet(cenaBalet);
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }
        cout<<prihod(pole,n);
        }break;

    case 6:
    //testiranje na brojPretstaviNaDelo
    {
        cout<<"======TEST CASE 6======="<<endl;
        int n;
        cin>>n;
        Pretstava **pole=new Pretstava*[n];
        for (int i=0;i<n;i++){
            pole[i]=readPretstava();
        }

        Delo f=readDelo();
        cout<<brojPretstaviNaDelo(pole,n,f);
    }break;

    };


return 0;
}
