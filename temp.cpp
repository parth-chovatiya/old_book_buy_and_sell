#include<iostream>
#include<fstream>
#include<cstring>
#include<bits/stdc++.h>
using namespace std;
int book_id=0;
string my_print(const int s,const int width)
{
    stringstream ss;
    ss<<fixed<<right;
    ss.fill(' ');
    ss.width(width);
    ss<<s;
    return ss.str();
}
string my_print(const string &s,const int width)
{
    stringstream ss;
    ss<<fixed<<right;
    ss.fill(' ');
    ss.width(width);
    ss<<s;
    return ss.str();
}

string center(const string s, const int w){
    stringstream ss,spaces;
    int padding = w - s.size();
    for(int i=0; i<padding/2; ++i)
        spaces<<" ";
    ss<<spaces.str()<<s<<spaces.str();
    if(padding>0&&padding%2!=0)
        ss<<" ";
    return ss.str();
}

class Book
{
    // int bookid;
    // char title[30];
    // float price;

    int book_isbn_number;
    char book_name[50],publisher_name[50];
    float book_price;
    int book_page,book_edition;
public:
    // Book(){
    //     bookid=0;
    //     strcpy(title,"no title");
    //     price=0;
    // }
    void getBookData()
    {
        // cout<<"Enter bookid, title and price of a book : ";
        // cin>>bookid;
        // cin.ignore();
        // cin.getline(title,25);
        // cin>>price;

        cout<<"Enter Book ISBN number : ";  cin>>book_isbn_number; cin.ignore();
        cout<<"Enter book name : ";         cin.getline(book_name,50); //cin.ignore();
        cout<<"Enter publisher_name : ";    cin.getline(publisher_name,50);// cin.ignore();
        cout<<"Enter book price : ";    cin>>book_price;
        cout<<"Enter book page : ";     cin>>book_page; 
        cout<<"Enter book edition : ";  cin>>book_edition; 
    }
    void showBookData()
    {
        // cout<<"\n"<<book_isbn_number<<" "<<book_name<<" "<<publisher_name<<" "<<book_price<<" "<<book_page<<" "<<book_edition;
        
        book_id++;
        cout<<my_print(book_id,7)<<" | "<<my_print(book_isbn_number,16)<<" | "<<my_print(book_page,9)<<" | "<<my_print(book_edition,12)<<" | "<<my_print(book_name,25)<<" | "<<my_print(publisher_name,25)<<" | "<<my_print(book_price,10)<<" |"<<endl;
    }
    int storeBook();
    void viewAllbooks();
    void delete_book(const char *);
};
int Book :: storeBook()
{
    if(book_isbn_number==0&&book_price==0){
        cout<<"Book data not initialized";
        return(0);
    }
    else{
        ofstream fout;
        fout.open("file12.dat",ios::app|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return(1);
    }
}
void Book :: viewAllbooks()
    {
        ifstream fin;
        fin.open("file12.dat",ios::in|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            showBookData();
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }
void Book :: delete_book(const char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("file12.dat",ios::in|ios::binary);
    fout.open("file12_temp.dat",ios::out);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof()){
        if(strcmp(book_name,t))
            fout.write((char*)this,sizeof(*this));
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();
    fout.close();
    remove("file12.dat");
    rename("file12_temp.dat","file12.dat");
}
int main()
{
    Book b;

    cout<<"Welcome to online book store\n\n";
    cout<<"1. For sell Book\n";
    cout<<"2. For buy Book\n";
    int c;
    cout<<"Enter choice : ";    cin>>c;

    if(c==1){
        b.getBookData();
        b.storeBook();
    }
    if(c==2){
        cout<<center("book_id",7)<<" | "<<center("book_isbn_number",16)<<" | "<<center("book_page",9)<<" | "<<center("book_edition",12)<<" | "<<center("book_name",25)<<" | "<<center("publisher_name",25)<<" | "<<center("book_price",10)<<" |\n ";
        
        cout<<string(20*7 + 2*3, '-')<<"\n";
        
        b.viewAllbooks();
        char s[50];
        cout<<"Which book you want to purchase? \n";
        cout<<"Enter Book name : ";
        cin>>s;
        b.delete_book(s);
        cout<<endl;
    }
    // b.delete_book("css");
    // cout<<endl;

    cout<<center("book_id",7)<<" | "<<center("book_isbn_number",16)<<" | "<<center("book_page",9)<<" | "<<center("book_edition",12)<<" | "<<center("book_name",25)<<" | "<<center("publisher_name",25)<<" | "<<center("book_price",10)<<" |\n ";
    cout<<string(20*7 + 2*3, '-')<<"\n";
    b.viewAllbooks();
}
