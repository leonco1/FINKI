#include <iostream>
#include<cstring>
using namespace std;
class Book
{
protected:
    char ISBN[21];
    char title[51];
    char avtor[31];
    double ocena;
    void kopiraj(const Book &b)
    {
        strcpy(this->ISBN,b.ISBN);
        strcpy(this->title,b.title);
        strcpy(this->avtor,b.avtor);
        this->ocena=b.ocena;
    }
public:
    Book(char *ISBN=NULL,char *title=NULL,char *avtor=NULL,double ocena=0)
    {
        strcpy(this->ISBN,ISBN);
        strcpy(this->title,title);
        strcpy(this->avtor,avtor);
        this->ocena=ocena;
    }
    char *getISBN()
    {
        return ISBN;

    }
    Book(const Book &b)
    {
        kopiraj(b);
    }
    Book &operator=(const Book &b)
    {
        if(this!=&b)
            kopiraj(b);
        return *this;
    }
    char *gettitle()
    {
        return title;
    }
    char *getAvtor()
    {
        return avtor;

    }
    double getcena()
    {
        return ocena;

    }
    void setISBN(char *i)
    {
        strcpy(ISBN,i);
    }
    friend ostream &operator<<(ostream &o,Book &b)
    {
        o<<b.ISBN<<": "<<b.title<<", "<<b.avtor<<" "<<b.bookPrice()<<endl;
        return o;
    }

    virtual double bookPrice()=0;
};
class OnlineBook:public Book
{
private:
    char *niza;
    int golemina;
public:
    OnlineBook(char *ISBN=NULL,char *title=NULL,char *avtor=NULL,double ocena=0,char *niza=NULL,int golemina=0):Book(ISBN,title,avtor,ocena)
    {
        this->niza=new char[strlen(niza)+1];
        this->golemina=golemina;
        strcpy(this->niza,niza);
    }
    OnlineBook(const Book &b,char *niza=NULL,int golemina=0):Book(b)
    {
        this->niza=new char[strlen(niza)+1];
        this->golemina=golemina;
        strcpy(this->niza,niza);
    }
    OnlineBook(const OnlineBook &ob):Book(ob)
    {
        this->niza=new char[strlen(ob.niza)+1];
        strcpy(this->niza,ob.niza);
        this->golemina=ob.golemina;
    }
    OnlineBook &operator=(const OnlineBook &ob)
    {
        if(this!=&ob)
        {
            strcpy(ISBN,ob.ISBN);
            strcpy(title,ob.title);
            strcpy(avtor,ob.avtor);
            ocena=ob.ocena;
            delete[] niza;
            this->niza=new char[strlen(ob.niza)+1];
        strcpy(this->niza,ob.niza);
        this->golemina=ob.golemina;
        }
        return *this;
    }
    double bookPrice()
    {
        if(golemina>20)
        return ocena*1.2;
        return ocena;
    }
    ~OnlineBook()
    {
        delete[]niza;
    }
};
class PrintBook:public Book
{
private:
    double masa;
    bool ima;
public:
    PrintBook(char *ISBN=NULL,char *title=NULL,char *avtor=NULL,double ocena=0,double masa=0,bool ima=false):Book(ISBN,title,avtor,ocena)
    {
        this->masa=masa;
        this->ima=ima;
    }
    double bookPrice()
    {
        if(masa>0.7)
            return ocena*1.15;
        return ocena;
    }
};
void mostExpensiveBook(Book **b,int n)
{   int index=0;
    int bronline,brpecateni;
    bronline=brpecateni=0;
    int maximum=b[0]->bookPrice();
    cout<<"FINKI-Education"<<endl;
    for(int i=0;i<n;i++)
    {
        OnlineBook *ob=dynamic_cast<OnlineBook*>(b[i]);
        PrintBook *pb=dynamic_cast<PrintBook*>(b[i]);
        if(ob)
            bronline++;
        else if(pb)
            brpecateni++;
            if(maximum<b[i]->bookPrice())
            {
                maximum=b[i]->bookPrice();
                index=i;
            }
    }
    cout<<"Total number of online books: "<<bronline<<endl;
    cout<<"Total number of print books: "<<brpecateni<<endl;
    cout<<"The most expensive book is:"<<endl;
    cout<<*b[index];

}
bool operator>(Book &b,Book &b1)
{
    if(b.bookPrice()>b1.bookPrice())
        return true;
    return false;
}
int main(){

	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
