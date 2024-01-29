#include <iostream>
#include<cstring>
using namespace std;
class FudbalskaEkipa
{
protected:
    char ime_trener[100];
    int broj_golovi[10];
public:
    FudbalskaEkipa(char *ime,int *broj_golovi=0)
    {
        strcpy(this->ime_trener,ime);
        for(int i=0;i<10;i++)
            this->broj_golovi[i]=broj_golovi[i];
    }

    FudbalskaEkipa &operator+=(int broj)
    {
        int temp[10];
        int brojac=0;
        for(int i=1;i<10;i++)
        {
            temp[brojac++]=broj_golovi[i];
        }
        temp[brojac]=broj;
        for(int i=0;i<10;i++)
            broj_golovi[i]=temp[i];
        return *this;
    }
    virtual char *getImeKlub()=0;
    virtual int uspeh()=0;
    bool operator>(FudbalskaEkipa &f)
    {
        return(this->uspeh()>f.uspeh());
    }
    friend  ostream &operator<<(ostream &o,FudbalskaEkipa &f)
    {
        o<<f.getImeKlub()<<endl;
        o<<f.ime_trener<<endl;
        o<<f.uspeh()<<endl;
        return o;
    }
};
class Klub:public FudbalskaEkipa
{
private:
    int broj_tituli;
    char ime[100];
public:
    Klub(char *ime_trener,int *broj_golovi,char *ime,int broj_tituli):FudbalskaEkipa(ime_trener,broj_golovi)
    {
        this->broj_tituli=broj_tituli;
        strcpy(this->ime,ime);
    }
    char *getImeKlub()
    {
        return ime;
    }
    int uspeh()
    {
        int brojac=0;
        for(int i=0;i<10;i++)
        {
            brojac+=broj_golovi[i];
        }
        return (brojac*3)+(broj_tituli*1000);
    }
};
class Reprezentacija:public FudbalskaEkipa
{
private:
    char ime_drzava[100];
    int broj_nastani;
public:
    Reprezentacija(char *ime_trener,int *broj_golovi,char ime_drzava[],int broj_nastani):FudbalskaEkipa(ime_trener,broj_golovi)
    {
        strcpy(this->ime_drzava,ime_drzava);
        this->broj_nastani=broj_nastani;
    }
    char *getImeKlub()
    {
        return ime_drzava;
    }
    int uspeh()
    {
        int brojac=0;
        for(int i=0;i<10;i++)
        {
            brojac+=broj_golovi[i];
        }
        return (brojac*3)+broj_nastani*50;
    }


};
void najdobarTrener(FudbalskaEkipa **f,int n)
{   int index=0;
    int maximum=f[0]->uspeh();
    for(int i=0;i<n;i++)
    {
        if(maximum<f[i]->uspeh())
        {
            maximum=f[i]->uspeh();
            index=i;
        }
    }
    cout<<*f[index];
}
int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}
