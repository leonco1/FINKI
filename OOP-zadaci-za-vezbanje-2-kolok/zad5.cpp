#include <iostream>
#include<cstring>
#define MAX 100
using namespace std;
enum typeC{standard=0,loyal,vip};
class UserExistsException
{
public:

    void pecati()
    {
        cout<<"The user"<<" already exists in the list!"<<endl;
    }
};
class Customer
{
private:
    char ime[51];
    char email[51];
    typeC tip;
    static int opopust;
    const static int dpopust;
    int brproizvodi;
    void kopiraj(const Customer &c)
    {
        strcpy(this->ime,c.ime);
        strcpy(this->email,c.email);
        this->tip=c.tip;
        this->brproizvodi=c.brproizvodi;
        this->opopust=c.opopust;
    }
public:
    Customer()
    {
    }
    Customer(char ime[],char email[],typeC tip,int brproizvodi)
    {
        strcpy(this->ime,ime);
        strcpy(this->email,email);
        this->tip=tip;
        this->brproizvodi=brproizvodi;
        this->opopust=opopust;
    }
    Customer(const Customer &c)
    {
        kopiraj(c);
    }
    Customer &operator=(const Customer &c)
    {
        if(this!=&c)
        {
            kopiraj(c);
        }
        return *this;
    }

    static void setDiscount1(int popust)
    {
        opopust=popust;
    }
    char *getEmail()
    {
        return email;
    }

    int getproizvodi()
    {
        return brproizvodi;
    }
    typeC getTip()
    {
        return tip;
    }
    void setTip(typeC t)
    {
        this->tip=t;
    }
    friend ostream &operator<<(ostream &o,Customer &c)
    {
        o<<c.ime<<endl<<c.email<<endl<<c.brproizvodi<<endl;
        if(c.tip==standard)
        {
            o<<"standard "<<0<<endl;

        }
        else if(c.tip==loyal)
        {
            o<<"loyal "<<c.opopust<<endl;
        }
        else if(c.tip==vip)
        {
            o<<"vip "<<c.opopust+c.dpopust<<endl;
        }
        return o;
    }
};
 int Customer::opopust=10;
 const int Customer::dpopust=20;
class FINKI_bookstore
{
private:
    Customer *niza;
    int n;
    void kopiraj(const FINKI_bookstore &f)
    {
        this->n=f.n;
        this->niza=new Customer[f.n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=f.niza[i];
        }
    }
public:
    FINKI_bookstore()
    {

    }
    FINKI_bookstore(Customer *niza,int n)
    {   this->n=n;
        this->niza=new Customer[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=niza[i];
        }
    }
    FINKI_bookstore(const FINKI_bookstore &f)
    {
        kopiraj(f);
    }
    FINKI_bookstore &operator=(const FINKI_bookstore &f)
    {
        if(this!=&f)
        {
            delete[]niza;
            kopiraj(f);
        }
        return *this;
    }
    FINKI_bookstore &operator +=(Customer &c)
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(niza[i].getEmail(),c.getEmail())==0)
                throw UserExistsException();

        }
        Customer *tmp=new Customer[n+1];
        for(int i=0;i<n;i++)
        {
            tmp[i]=niza[i];
        }
        tmp[n++]=c;
        delete[]niza;
        niza=tmp;
        return *this;
    }
    void update()
    {
        for(int i=0;i<n;i++)
        {
            if(niza[i].getTip()==standard && niza[i].getproizvodi()>5)
            {
                niza[i].setTip(loyal);

                }
                else if(niza[i].getTip()==loyal && niza[i].getproizvodi()>10)
                {
                    niza[i].setTip(vip);
                }
                }
        }
    void setCustomers(Customer *customers,int n)
    {
        this->n=n;
        this->niza=new Customer[n];
        for(int i=0;i<n;i++)
        {
            this->niza[i]=customers[i];
        }
        }
        friend ostream &operator<<(ostream &o,FINKI_bookstore &f)
        {
            for(int i=0;i<f.n;i++)
            {
                o<<f.niza[i];
            }
            return o;
        }


};
int main() {

  int testCase;
  cin >> testCase;
  char name[MAX];
  char email[MAX];
  int tC;
  int discount;
  int numProducts;
  if (testCase == 1){
    cout << "===== Test Case - Customer Class ======" << endl;
    cin.get();
    cin.getline(name, MAX);
    cin.getline(email, MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;
  }
  if (testCase == 2){
    cout << "===== Test Case - Static Members ======" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    cout << "===== CONSTRUCTOR ======" << endl;
    Customer c(name, email, (typeC) tC, numProducts);
    cout << c;
    c.setDiscount1(5);
    cout << c;
  }
  if (testCase == 3){
    cout << "===== Test Case - FINKI-bookstore ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }
    fc.setCustomers(customers, n);
    cout << fc <<endl;
  }

  if (testCase == 4){
    cout << "===== Test Case - operator+= ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }

    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
    Customer c(name, email, (typeC) tC, numProducts);
    fc+=c;
    cout << fc;
  }

  if (testCase == 5){
    cout << "===== Test Case - operator+= (exception) ======" << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
        }
    fc.setCustomers(customers, n);
    cout << "OPERATOR +=" << endl;
    cin.get();
    cin.getline(name,MAX);
    cin.getline(email,MAX);
    cin >> tC;
    cin >> numProducts;
          Customer c(name, email, (typeC) tC, numProducts);
      try {
    fc+=c;
      }
         catch (UserExistsException &ex) {
      ex.pecati();
      }
    cout << fc;
  }
  if (testCase == 6){
    cout << "===== Test Case - update method  ======" << endl << endl;
    FINKI_bookstore fc;
    int n;
    cin >> n;
    Customer customers[MAX];
    for(int i = 0; i < n; ++i) {
      cin.get();
      cin.getline(name,MAX);
      cin.getline(email,MAX);
      cin >> tC;
      cin >> numProducts;
      Customer c(name, email, (typeC) tC, numProducts);
      customers[i] = c;
    }
    fc.setCustomers(customers, n);
    cout << "Update:" << endl;
    fc.update();
    cout << fc;
   }

  return 0;
}

