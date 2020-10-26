#include<iostream>
#include<fstream>
#include<cstring>
#include<ctime>
#include<direct.h>
#include<unistd.h>
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


//   ------   to get current working directory
string get_current_dir() {
   char buff[FILENAME_MAX]; 
   _getcwd( buff, FILENAME_MAX );
   string current_working_dir(buff);
   return current_working_dir;
}

///   ------ Book class ------   ///
class Book
{
    int book_isbn_number;
    char book_name[50],publisher_name[50];
    float book_price;
    int book_page,book_edition;
public:

///  --- constructor which will initilaze default values
    Book(){
        book_isbn_number=0;
        strcpy(book_name,"no title");
        strcpy(publisher_name,"no publisher");
        book_price=0;
        book_page=0;
        book_edition=0;
    }

///  ---  to get data from user  ---
    void getBookData()
    {
        cout<<"\t\tEnter Book ISBN number : ";  cin>>book_isbn_number; cin.ignore();
        cout<<"\t\tEnter book name : ";         cin.getline(book_name,50); //cin.ignore();
        cout<<"\t\tEnter publisher_name : ";    cin.getline(publisher_name,50);// cin.ignore();
        cout<<"\t\tEnter book price : ";    cin>>book_price;
        cout<<"\t\tEnter book page : ";     cin>>book_page; 
        cout<<"\t\tEnter book edition : ";  cin>>book_edition; 
    }
    void showBookData()
    {
        book_id++;
        cout<<my_print(book_id,7)<<" | "<<my_print(book_isbn_number,16)<<" | "<<my_print(book_page,9)<<" | "<<my_print(book_edition,12)<<" | "<<my_print(book_name,25)<<" | "<<my_print(publisher_name,25)<<" | "<<my_print(book_price,10)<<" |"<<endl;
    }
    int storeBook();
    void viewAllbooks();
    void delete_book(const char *);
    int search_book(const char *);
    void generate_bill();
};


///   ------ store book in file   ------    ///
int Book :: storeBook()
{
    if(book_isbn_number==0&&book_price==0){
        cout<<"Book data not initialized";
        return(0);
    }
    else{
        ofstream fout;
        fout.open("books.dat",ios::app|ios::binary);
        fout.write((char*)this,sizeof(*this));
        fout.close();
        return(1);
    }
}


///   ------   show all books from file   ------   ///
void Book :: viewAllbooks()
    {
        ifstream fin;
        fin.open("books.dat",ios::in|ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof()){
            showBookData();
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
    }


///   ------   delete book from file whose name is stored in variable t   ------   ///
void Book :: delete_book(const char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("books.dat",ios::in|ios::binary);
    fout.open("books_temp.dat",ios::out);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof()){
        if(strcmp(book_name,t))
            fout.write((char*)this,sizeof(*this));
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();
    fout.close();
    remove("books.dat");
    rename("books_temp.dat","books.dat");
}


///   ------   search book from file whose name is stored in variable t   ------   ///
int Book :: search_book(const char *t)
{
    int flag=0;
    ifstream fin;
    fin.open("books.dat",ios::in|ios::binary);
    fin.read((char*)this,sizeof(*this));
    while(!fin.eof()){
        if(!strcmp(t,book_name)){
            flag=1;
            break;
        }
        fin.read((char*)this,sizeof(*this));
    }
    fin.close();
    return flag;
}


///   ------   generate bill and stored in seprate text file   ------   ///
void Book :: generate_bill()
{
        string name;
        cout<<"\n\t\tEnter your name : "; cin>>name;
        ofstream fout;
        time_t current = time(0);
        char* dt = ctime(&current);
        fout.open("bill.txt",ios::out);
        fout<<"\t\t\t\tBook Bill\n";
        fout<<"\t\t\t\t---------\n\n";
        fout<<"Date : "<<dt<<"\n";
        fout<<"Customer Name : "<<name<<"\n\n\n";
        fout<<"\t\t\tBook Details\n";
        fout<<"\t\t\t-------------\n\n";
        fout<<"----------------------------------------------------------------------------------------------------------------------------\n";
        fout<<center("book_id",7)<<" | "<<center("book_isbn_number",16)<<" | "<<center("book_page",9)<<" | "<<center("book_edition",12)<<" | "<<center("book_name",25)<<" | "<<center("publisher_name",25)<<" | "<<center("book_price",10)<<" |\n";
        fout<<"----------------------------------------------------------------------------------------------------------------------------\n";
        fout<<my_print(book_id,7)<<" | "<<my_print(book_isbn_number,16)<<" | "<<my_print(book_page,9)<<" | "<<my_print(book_edition,12)<<" | "<<my_print(book_name,25)<<" | "<<my_print(publisher_name,25)<<" | "<<my_print(book_price,10)<<" |"<<endl;
        fout<<"----------------------------------------------------------------------------------------------------------------------------\n";
        fout<<"\n\n";
        fout<<"Book Price    : "<<book_price<<"\n";
        fout<<"Total tax(5%) : "<<book_price*0.05<<"\n";
        fout<<"-----------------------\n";
        fout<<"Total Price   : "<<book_price+book_price*0.05;
        fout<<"\n\n\n";

        ///  --- terms and condition ---

        fout<<"---: Terms & Conditions :---\n\n";
        fout<<"1. You can replace your order withon 7 working days\n";
        fout<<"2. This bill is very important when you replace order\n";
        fout<<"3. You can't give this book to other\n";
        fout<<"4. Damage during transist (if any) will be borne ny the supplier\n";
        fout<<"\n\n\t\t Thank You ...";
        fout<<"\n\t\t visit again ...\n";
}




///// -------  main  ---------
int main()
{
    Book b;
while(1){
    cout<<"\n\t\tWelcome to online book store\n\n";
    cout<<"\t\t1. For sell Book\n";
    cout<<"\t\t2. For buy Book\n";
    cout<<"\t\t3. Show all books\n";
    cout<<"\t\t4. Exit\n\n";

    int c;
    cout<<"\n\t\tEnter choice : ";    cin>>c;
    cout<<"\n";
    switch(c){
        case 1:
            b.getBookData();
            b.storeBook();
            break;
        case 2:
            cout<<center("book_id",7)<<" | "<<center("book_isbn_number",16)<<" | "<<center("book_page",9)<<" | "<<center("book_edition",12)<<" | "<<center("book_name",25)<<" | "<<center("publisher_name",25)<<" | "<<center("book_price",10)<<" |\n ";
        
            cout<<string(20*7 + 2*3, '-')<<"\n";
        
            b.viewAllbooks();
            char s[50];
            cout<<"\n\t\tWhich book you want to purchase? \n";
            cout<<"\n\t\tEnter Book name : ";
            cin>>s;
            if(b.search_book(s)==1){
                cout<<"\n\t\tYou have successfully purchased book\n";
                char c;
                cout<<"\n\t\tYou want bill? y/n : ";  cin>>c;
                if(c=='y'){
                    b.generate_bill();
                    cout<<"\n\t\tYour bill is stored in : "<<get_current_dir()<<"\\bill.txt\n";
                    b.delete_book(s);
                }
                else{
                    cout<<"\t\t\tThank You ..\n";
                }
            }
            else{
                cout<<"\n\t\tBook not found\n";
            }
            cout<<endl;
            break;
        case 3:
            cout<<center("book_id",7)<<" | "<<center("book_isbn_number",16)<<" | "<<center("book_page",9)<<" | "<<center("book_edition",12)<<" | "<<center("book_name",25)<<" | "<<center("publisher_name",25)<<" | "<<center("book_price",10)<<" |\n ";
        
            cout<<string(20*7 + 2*3, '-')<<"\n";
            b.viewAllbooks();
            break;
        case 4:
            cout<<"\n\t\tThank You ...\n";
            exit(0);
            break;
        default:
            cout<<"\t\tEnter valid choice\n";
            break;
    }
}
}
