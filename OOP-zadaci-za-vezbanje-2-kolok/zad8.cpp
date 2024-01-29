#include <iostream>
#include<cstring>
using namespace std;
class Koncert
{
private:
    char naziv[21];
    char lokacija[21];
    static double sezonski_popust;
    double cenaBilet;
public:
    Koncert(char *naziv=NULL,char *lokacija=NULL,double cenaBilet=0)
    {
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cenaBilet=cenaBilet;
    }
    static void setSezonskiPopust(double sp)
    {
        sezonski_popust=sp;
    }
    static double getSezonskiPopust()
    {
        return sezonski_popust;
    }
    char *getNaziv()
    {
        return naziv;
    }
    virtual double cena()
    {
        return cenaBilet-(sezonski_popust*cenaBilet);
    }
};
double Koncert::sezonski_popust=0.2;
class ElektronskiKoncert:public Koncert
{
private:
    char *ime;
    double vremetraenje;
    bool dali;
public:
    ElektronskiKoncert(char *naziv,char *lokacija,double cenaBilet,char *ime=NULL,double vremetraenje=0,bool dali=false):Koncert(naziv,lokacija,cenaBilet)
    {
        this->vremetraenje=vremetraenje;
        this->dali=dali;
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
    }
    double cena()
    {
        double ocena=Koncert::cena();
        if(vremetraenje>7)
           ocena+=360;
        else if(vremetraenje>5)
            ocena+=150;
        if(dali)
            return ocena-50;
        return ocena+100;

    }
};
void najskapKoncert(Koncert **koncerti,int n)
{
    int maximum,index;
    maximum=koncerti[0]->cena();
    int brojac=0;
    for(int i=0;i<n;i++)
    {
        if(koncerti[i]->cena()>maximum)
        {
            maximum=koncerti[i]->cena();
            index=i;
        }
        ElektronskiKoncert *e=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
        if(e)
        {
            brojac++;
        }

    }
    cout<<"Najskap koncert: "<<koncerti[index]->getNaziv()<<" "<<maximum<<endl;
    cout<<"Elektronski koncerti: "<<brojac<<" od vkupno "<<n;
}
bool prebarajKoncert(Koncert **koncerti,int n,char *naziv,bool elektronski)
{
    bool najde=false;
    if(elektronski)
    {
        for(int i=0;i<n;i++)
        {
            ElektronskiKoncert *e=dynamic_cast<ElektronskiKoncert*>(koncerti[i]);
            if(e && strcmp(koncerti[i]->getNaziv(),naziv)==0)
            {
                najde=true;
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;

            }
        }
    }
    else
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(koncerti[i]->getNaziv(),naziv)==0)
            {
                najde=true;
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
            }
        }
    }
    return najde;

}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

        cin>>tip;
        if (tip==1){//Koncert
        	cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
        }
        else if (tip==2){//cena - Koncert
            cin>>naziv>>lokacija>>cenaBilet;
        	Koncert k1(naziv,lokacija,cenaBilet);
        	cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
        }
        else if (tip==3){//ElektronskiKoncert
            cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
            ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
            cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
        }
        else if (tip==4){//cena - ElektronskiKoncert
             cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
             ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
             cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
        }
        else if (tip==5) {//najskapKoncert

        }
        else if (tip==6) {//prebarajKoncert
            Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
        	najskapKoncert(koncerti,5);
        }
        else if (tip==7){//prebaraj
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
            char naziv[100];
            bool elektronski;
        	cin>>elektronski;
        	if(prebarajKoncert(koncerti,5, "Area",elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

            if(prebarajKoncert(koncerti,5, "Area",!elektronski))
                cout<<"Pronajden"<<endl;
            else cout<<"Ne e pronajden"<<endl;

        }
        else if (tip==8){//smeni cena
        	  Koncert ** koncerti = new Koncert *[5];
            int n;
            koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
            koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
            koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
            koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
            koncerti[2] -> setSezonskiPopust(0.9);
        	najskapKoncert(koncerti,4);
        }

    return 0;
}

