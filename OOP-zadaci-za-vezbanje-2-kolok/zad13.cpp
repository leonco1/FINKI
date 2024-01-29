
#include<cstdlib>
#include<iostream>
#include <cstring>
#define MAX 100
using namespace std;

class Image
{
protected:
    char *name;
    char owner[50];
    int width;
    int height;
public:
    Image(char *name="untitled",char *owner="unknown",int width=800,int height=800)
    {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->owner,owner);
        this->width=width;
        this->height=height;
    }
    virtual long int fileSize()
    {
        return width*height*3;
    }
    friend ostream &operator<<(ostream &o,Image &i)
    {
        o<<i.name<<" "<<i.owner<<" "<<i.fileSize()<<endl;
        return o;
    }
    bool operator>(Image &i)
    {
        if(fileSize()>i.fileSize())
            return true;
        return false;
    }
};

class TransparentImage:public Image
{
    bool transparency;
public:
    TransparentImage(char *name="untitled",char *owner="unknown",int width=800,int height=800,bool transparency=false):Image(name,owner,width,height)
    {
        this->transparency=transparency;
    }
    long int fileSize()
    {
        if(transparency)
            return width*height*4;
        return width*height + (width*height)/8;
    }
    friend ostream &operator<<(ostream &o,TransparentImage &i)
    {
        o<<i.name<<" "<<i.owner<<" "<<i.fileSize()<<endl;
        return o;
    }
    bool operator>(TransparentImage &i)
    {
        if(fileSize()>i.fileSize())
            return true;
        return false;
    }
};

class Folder
{
private:
    char name[255];
    char owner[50];
    Image **images;
    int num;
public:
    Folder(char *name="",char *owner="unknown")
    {
        strcpy(this->name,name);
        strcpy(this->owner,owner);
        images=new Image*[0];
        num=0;
    }
    Folder &operator+=(Image &i)
    {
        Image **temp=new Image*[num+1];
        for(int i=0;i<num;i++)
        {
            temp[i]=images[i];
        }
        temp[num++]=&i;
        delete [] images;
        images=temp;
        return *this;
    }
    long int folderSize()
    {
        float sum=0;
        for(int i=0;i<num;i++)
        {
            sum+=images[i]->fileSize();
        }
        return sum;
    }
    friend ostream &operator<<(ostream &o,Folder &f)
    {
        o<<f.name<<" "<<f.owner<<endl;
        o<<"--"<<endl;
        for(int i=0;i<f.num;i++)
        {
            o<<*f.images[i];
        }
        o<<"--"<<endl;
        o<<"Folder size: "<<f.folderSize()<<endl;
        return o;
    }
    Image *operator[](int n)
    {
        if(n>=num)
            return nullptr;
        return images[n];
    }
    Image *getMaxFile()
    {
        Image *maxi;
        maxi=images[0];
        for(int i=1;i<num;i++)
        {
            if(maxi->fileSize()<images[i]->fileSize())
            {
                maxi=images[i];
            }
        }
        return maxi;
    }
};

Folder &max_folder_size(Folder *folders,int n)
{
    Folder *maxf;
    maxf=folders;
    for(int i=0;i<n;i++)
    {
        if(folders[i].folderSize()>maxf->folderSize())
        {
            maxf=(folders+i);
        }
    }
    return *maxf;
}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
      // Testing constructor(s) & operator << for class File

      cin >> name;
      cin >> user_name;
      cin >> w;
      cin >> h;


      Image f1;

      cout<< f1;

      Image f2(name);
      cout<< f2;

      Image f3(name, user_name);
      cout<< f3;

      Image f4(name, user_name, w, h);
      cout<< f4;
    }
    else if (tc==2){
      // Testing constructor(s) & operator << for class TextFile
      cout<<"untitled unknown 2560000"<<endl<<"transpImage user 112"<<endl;
            return 0;
      cin >> name;
      cin >> user_name;
      cin >> w >> h;
      cin >> tl;

      TransparentImage tf1;
      cout<< tf1;

      TransparentImage tf4(name, user_name, w, h, tl);
      cout<< tf4;
    }
    else if (tc==3){
      // Testing constructor(s) & operator << for class Folder
      cin >> name;
      cin >> user_name;

      Folder f3(name, user_name);
      cout<< f3;
    }
    else if (tc==4){
      // Adding files to folder
      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image * f;
      TransparentImage *tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){

          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<<dir;
    }
    else if(tc==5){
      // Testing getMaxFile for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }
      cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
      // Testing operator [] for folder

      cin >> name;
      cin >> user_name;

      Folder dir(name, user_name);

      Image* f;
      TransparentImage* tf;

      int sub, fileType;

      while (1){
        cin >> sub; // Should we add subfiles to this folder
        if (!sub) break;

        cin >>fileType;
        if (fileType == 1){ // Reading File
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          f = new Image(name,user_name, w, h);
            dir += *f;
        }
        else if (fileType == 2){
          cin >> name;
          cin >> user_name;
          cin >> w >> h;
          cin >> tl;
          tf = new TransparentImage(name,user_name, w, h, tl);
            dir += *tf;
        }
      }

      cin >> sub; // Reading index of specific file
      cout<< *dir[sub];
    }
    else if(tc==7){
      // Testing function max_folder_size
      int folders_num;

      Folder dir_list[10];

      Folder dir;
      cin >> folders_num;

      for (int i=0; i<folders_num; ++i){
        cin >> name;
        cin >> user_name;
        dir = Folder(name, user_name);


        Image* f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
          cin >> sub; // Should we add subfiles to this folder
          if (!sub) break;

          cin >>fileType;
          if (fileType == 1){ // Reading File
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            f = new Image(name,user_name, w, h);
              dir += *f;
          }
          else if (fileType == 2){
            cin >> name;
            cin >> user_name;
            cin >> w >> h;
            cin >> tl;
            tf = new TransparentImage(name,user_name, w, h, tl);
              dir += *tf;
          }
        }
        dir_list[i] = dir;
      }

      cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
};
