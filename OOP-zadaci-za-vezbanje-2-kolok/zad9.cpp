#include <iostream>
#include<cstring>
using namespace std;
class Exception
{
public:
    void pecati()
    {
        cout<<"Ne moze da se vnese dadeniot trud"<<endl;
    }
};
class Trud
{
private:
    char trud;
    int godina;
public:
    Trud(const char trud='C',int godina=0)
    {
        this->trud=toupper(trud);
        this->godina=godina;
    }
    Trud &operator=(const Trud &t)
    {
        if(this!=&t)
        {
            this->trud=toupper(t.trud);
            this->godina=t.godina;
        }
        return *this;
    }
int getGod()
{
    return godina;
}
char getTrud()
{
    return trud;
}
friend istream &operator>>(istream & in,Trud &t)
{
    in>>t.trud>>t.godina;
    return in;
}
};
class Student
{
private:
    char ime[31];
    int index;
    int godina_upis;
    int niza[50];
    int n;
    void kopiraj(const Student &s)
    {
        strcpy(this->ime,s.ime);
        this->index=s.index;
        this->godina_upis=s.godina_upis;
        this->n=s.n;
        for(int i=0;i<n;i++)
            this->niza[i]=s.niza[i];
    }
public:
    Student(char *ime=NULL,int index=0,int godina_upis=0,int *niza=NULL,int n=0)
    {
        strcpy(this->ime,ime);
        this->index=index;
        this->godina_upis=godina_upis;
        this->n=n;
        for(int i=0;i<n;i++)
        this->niza[i]=niza[i];
    }
    Student(const Student &s)
    {
        kopiraj(s);
    }
    int getIndex()
    {
        return index;
    }
    Student &operator=(const Student &s)
    {
        if(this!=&s)
            kopiraj(s);
        return *this;
    }
    int getGodina_Upis()
    {
        return godina_upis;
    }
    virtual double rang()
    {
        double zbir=0;
        for(int i=0;i<n;i++)
            zbir+=niza[i];
        return zbir/(n*1.0);
    }
     friend ostream &operator<<(ostream &o,Student &s)
     {
         o<<s.index<<" "<<s.ime<<" "<<s.godina_upis<<" "<<s.rang()<<endl;
         return o;
     }

};
class PhDStudent:public Student
{
private:
    Trud *trudovi;
    int br_trudovi;
    static int konf;
    static int spisanie;

public:
    PhDStudent(char *ime=NULL,int index=0,int godina_upis=0,int *niza=NULL,int n=0,Trud *trudovi=NULL,int br_trudovi=0):Student(ime,index,godina_upis,niza,n)
    {
            int brojac=0;
            this->trudovi=new Trud[100];
            for(int i=0;i<br_trudovi;i++)
            {
                try{
                if(this->getGodina_Upis()>trudovi[i].getGod())
                    throw Exception();
                this->trudovi[brojac++]=trudovi[i];
                }
                catch(Exception &e)
            {
                e.pecati();
            }
            }

            this->br_trudovi=brojac;
    }

    static void setKonf(int a)
    {
        konf=a;
    }
    static void setSpisanie(int a)
    {
        spisanie=a;
    }
    double rang()
    {
        double zbir=0;
        for(int i=0;i<br_trudovi;i++)
        {
            if(trudovi[i].getTrud()=='C')
                zbir+=konf;
            else zbir+=spisanie;

        }
        return Student::rang()+zbir;

    }
    PhDStudent &operator +=(Trud &t)
    {
        if(t.getGod()<getGodina_Upis())
        {throw Exception();
        }

        Trud *tmp=new Trud[br_trudovi+1];
        for(int i=0;i<br_trudovi;i++)
            tmp[i]=trudovi[i];
            tmp[br_trudovi++]=t;
            delete[]trudovi;
            trudovi=tmp;
            return *this;

    }
    ~PhDStudent()
    {
        delete[]trudovi;
    }
};
int PhDStudent::konf=1;
int PhDStudent::spisanie=3;
int main(){
	int testCase;
	cin >> testCase;

	int god, indeks, n, god_tr, m, n_tr;
	int izbor; //0 za Student, 1 za PhDStudent
	char ime[30];
	int oceni[50];
	char tip;
	Trud trud[50];

	if (testCase == 1){
		cout << "===== Testiranje na klasite ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		Student s(ime, indeks, god, oceni, n);
		cout << s;

		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);
		cout << phd;
	}
	if (testCase == 2){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks

		Trud t;
		cin >> indeks;
		cin >> t;
for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex() == indeks)
            {
                PhDStudent *temp = dynamic_cast<PhDStudent*>(niza[i]);
                if(temp)
                {
                    try
                    {
                        *temp+=t;
                    }
                    catch (Exception &e)
                    {
                        e.pecati();
                    }
                }
                else
                {
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    break;
                }

            }

        }


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 3){
		cout << "===== Testiranje na operatorot += ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;

for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex() == indeks)
            {
                PhDStudent *temp = dynamic_cast<PhDStudent*>(niza[i]);
                if(temp)
                {
                    try
                    {
                        *temp+=t;
                    }
                    catch (Exception &e)
                    {
                        e.pecati();
                    }
                }
                else
                {
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    break;
                }

            }

        }


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 4){
		cout << "===== Testiranje na isklucoci ======" << endl;
		cin >> ime;
		cin >> indeks;
		cin >> god;
		cin >> n;
		for (int j = 0; j < n; j++)
			cin >> oceni[j];
		cin >> n_tr;
		for (int j = 0; j < n_tr; j++){
			cin >> tip;
			cin >> god_tr;
			Trud t(tip, god_tr);
			trud[j] = t;
		}
		PhDStudent phd(ime, indeks, god, oceni, n, trud, n_tr);

		cout << phd;
	}
	if (testCase == 5){
		cout << "===== Testiranje na isklucoci ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		// dodavanje nov trud za PhD student spored indeks
		Trud t;
		cin >> indeks;
		cin >> t;
for(int i=0;i<m;i++)
        {
            if(niza[i]->getIndex() == indeks)
            {
                PhDStudent *temp = dynamic_cast<PhDStudent*>(niza[i]);
                if(temp)
                {
                    try
                    {
                        *temp+=t;
                    }
                    catch (Exception &e)
                    {
                        e.pecati();
                    }
                }
                else
                {
                    cout<<"Ne postoi PhD student so indeks "<<indeks<<endl;
                    break;
                }

            }

        }

		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}
	if (testCase == 6){
		cout << "===== Testiranje na static clenovi ======" << endl;
		Student **niza;
		cin >> m;
		niza = new Student *[m];
		for (int i = 0; i<m; i++){
			cin >> izbor;
			cin >> ime;
			cin >> indeks;
			cin >> god;
			cin >> n;
			for (int j = 0; j < n; j++)
				cin >> oceni[j];

			if (izbor == 0){
				niza[i] = new Student(ime, indeks, god, oceni, n);
			}
			else{
				cin >> n_tr;
				for (int j = 0; j < n_tr; j++){
					cin >> tip;
					cin >> god_tr;
					Trud t(tip, god_tr);
					trud[j] = t;
				}
				niza[i] = new PhDStudent(ime, indeks, god, oceni, n, trud, n_tr);
			}
		}
		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];

		int conf, journal;
		cin >> conf;
		cin >> journal;

        for(int i=0;i<m;i++)
        {
            PhDStudent *temp = dynamic_cast<PhDStudent*>(niza[i]);
            if(temp != 0)
            {
                temp->setKonf(conf);
                temp->setSpisanie(journal);
            }
        }


		// pecatenje na site studenti
		cout << "\nLista na site studenti:\n";
		for (int i = 0; i < m; i++)
			cout << *niza[i];
	}

	return 0;
}
