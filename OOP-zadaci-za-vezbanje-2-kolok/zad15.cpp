#include <iostream>
#include<cstring>
using namespace std;
class BadInputException
{
public:
    void pecati()
    {
        cout<<"Greshna opisna ocenka"<<endl;
    }
};
class StudentKurs
{
protected:
    char ime[100];
    int ocenka;
    bool isprasuvanje;
    static int MAX;
    const static int MINOCENKA;
public:
    StudentKurs()
    {
        strcpy(ime,"");
        ocenka=0;
        isprasuvanje=false;
    }
    StudentKurs(char *ime,int ocenka)
    {
        strcpy(this->ime,ime);
        this->ocenka=ocenka;
        this->isprasuvanje=false;
        }
    StudentKurs(const StudentKurs &s)
    {
        strcpy(this->ime,s.ime);
        ocenka=s.ocenka;
        isprasuvanje=s.isprasuvanje;
    }
    StudentKurs &operator=(const StudentKurs &s)
    {
        if(this!=&s)
        {
        strcpy(this->ime,s.ime);
        ocenka=s.ocenka;
        isprasuvanje=s.isprasuvanje;
        }
        return *this;
    }
    bool getDaliUsno()
    {
        return isprasuvanje;
    }
     int getOcenka()
    {
        return ocenka;
    }
    static void setMAX(int a)
    {
        MAX=a;
    }
    void setOcenka(int o)
    {
        ocenka=o;
    }
    friend ostream &operator<<(ostream &o,StudentKurs &sk)
    {
        o<<sk.ime<<" --- "<<sk.ocenka<<endl;
        return o;
    }
    const static int getMIN()
    {
        return MINOCENKA;
    }
    static int getMAX()
    {
        return MAX;
    }
    char *getIme()
    {
        return ime;
    }
    virtual ~StudentKurs()
    {

    }
};
int StudentKurs::MAX=10;
const int StudentKurs::MINOCENKA=6;
class StudentKursUsno:public StudentKurs
{
private:
    char *opisna;
public:
    StudentKursUsno()
    {
        this->opisna=new char[0];
    }
    StudentKursUsno(char *ime,int ocenka):StudentKurs(ime,ocenka)
    {
        isprasuvanje=true;
    }
    ~StudentKursUsno()
    {
        delete[]opisna;
    }
    char *getOpisna()
    {
        return opisna;
    }
    StudentKursUsno &operator+=(const char *text)
    {
        char temp[20];
        int flag=0;
        int brojac=0;
        for(int i=0;i<strlen(text);i++)
        {
            if(!isalpha(text[i]))
                flag=1;
            else
                temp[brojac++]=text[i];
        }
        temp[brojac]='\0';
        this->opisna=new char[strlen(temp)+1];
        strcpy(this->opisna,temp);
        if(strcmp(opisna,"odlicen")==0)
        {
            if(ocenka+2<=MAX)
                ocenka+=2;
        }
        else if(strcmp(opisna,"dobro")==0)
        {
            if(ocenka+1<=MAX)
                ocenka+=1;
        }
        else if(strcmp(opisna,"losho")==0)
        {
            ocenka-=1;
        }
        if(flag)
            throw BadInputException();
        return *this;
    }
};
class KursFakultet{
private:
    char naziv[30];
    StudentKurs *studenti[20];
    int broj;

public:
    KursFakultet(char *naziv, StudentKurs** studenti,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        if (studenti[i]->getDaliUsno()){
            this->studenti[i]=new StudentKursUsno(*dynamic_cast<StudentKursUsno*>(studenti[i]));
        }
        else this->studenti[i]=new StudentKurs(*studenti[i]);
      }
      this->broj=broj;
    }
    ~KursFakultet(){
    for (int i=0;i<broj;i++) delete studenti[i];
    }
    void pecatiStudenti()
    {
        cout<<"Kursot "<<naziv<<" go polozile:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(studenti[i]->getOcenka()>=StudentKurs::getMIN())
            {
                if(studenti[i]->getOcenka()>studenti[i]->getMAX())
                {
                    studenti[i]->setOcenka(studenti[i]->getMAX());

                }
                cout<<*studenti[i];

            }
        }
    }
    void postaviOpisnaOcenka(char *ime,char *opisnaOcenka)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(studenti[i]->getIme(),ime)==0 && studenti[i]->getDaliUsno())
            {
                StudentKursUsno *tmp=dynamic_cast<StudentKursUsno*>(studenti[i]);
                if(tmp)
                {
                    *tmp+=opisnaOcenka;
                    break;
                }
            }

        }

    }
};

int main(){

StudentKurs **niza;
int n,m,ocenka;
char ime[30],opisna[10];
bool daliUsno;
cin>>n;
niza=new StudentKurs*[n];
for (int i=0;i<n;i++){
   cin>>ime;
   cin>>ocenka;
   cin>>daliUsno;
   if (!daliUsno)
    niza[i]=new StudentKurs(ime,ocenka);
   else
    niza[i]=new StudentKursUsno(ime,ocenka);
}

KursFakultet programiranje("OOP",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;

for (int i=0;i<m;i++){
   cin>>ime>>opisna;
   try{
   programiranje.postaviOpisnaOcenka(ime,opisna);
   }
   catch(BadInputException &e)
   {
       e.pecati();
   }
}

StudentKurs::setMAX(9);

programiranje.pecatiStudenti();

}
