#include <iostream>
#include<fstream>
#include<string>
#include<stdio.h>
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
class sell
{
protected:
    int book_isbn_number;
    string book_name,publisher_name;//,author_name[10];
    float book_price;
    int book_page,book_edition;
public:
    void set_data()
    {
      //  int n;
        cout<<"Enter Book ISBN number : ";  cin>>book_isbn_number; //fflush(stdin);
        cout<<"Enter book name : ";         cin>>book_name;//getline(cin,book_name); fflush(stdin);
        cout<<"Enter publisher_name : ";    cin>>publisher_name;//getline(cin,publisher_name); fflush(stdin);
        // cout<<"How many author are? : ";    cin>>n; fflush(stdin);
        // cout<<"Enter author name : ";
        // for(int i=0; i<n; i++)
        //     getline(cin,author_name[i]);
        cout<<"Enter book price : ";    cin>>book_price; //fflush(stdin);
        cout<<"Enter book page : ";     cin>>book_page; //fflush(stdin);
        cout<<"Enter book edition : ";  cin>>book_edition; //fflush(stdin);
    }
     void display_data(){
         book_id++;
        cout<<my_print(book_id,7)<<" | "<<my_print(book_isbn_number,16)<<" | "<<my_print(book_page,9)<<" | "<<my_print(book_edition,12)<<" | "<<my_print(book_name,25)<<" | "<<my_print(publisher_name,25)<<" | "<<my_print(book_price,10)<<" |"<<endl;
    }
};
class buy : public sell
{

public:
    void delete_book(int);
};
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
void buy :: delete_book(int rno)
{
    int pos,flag=0;
    ifstream ifs;
    ifs.open("Books_information.txt",ios::in);

    ofstream ofs;
    ofs.open("temp.txt",ios::out);
    // int c;
    // int line_no = 1;
    while(!ifs.eof()){
    //     if(c=='\n')
    //         line_no++;
    //     if(line_no!=n)
        ifs.read((char*)this,sizeof(buy));
        if(ifs){
            if(rno==book_id){
                flag=1;
            }
        }
        else{
            ofs.write((char*)this,sizeof(buy));
        }
    }
    ofs.close();
    ifs.close();
    remove("Books_information.txt");
    rename("temp.txt","Book_information.txt");
    // }
    // string line;
    // ifstream myfile;
    // ofstream temp;
    // myfile.open("Books_information.txt",ios::in);
    // temp.open("temp.txt",ios::out);
    // while(getline(myfile,line)){
    //     if(line!=rno)
    // }
}
int main()
{
    cout<<"Welcome to online book store\n\n";
    cout<<"1. For sell Book\n";
    cout<<"2. For buy Book\n";
    int c;
    cout<<"Enter choice : ";    cin>>c;
    sell s;
    buy b;
    fstream inout;
    inout.open("Books_information.txt",ios::in|ios::out|ios::ate);
    
    /// ### for writing into file
    if(c==1){
    cout<<"Enter book information\n";
    s.set_data();
    inout.seekp(0,ios::end);
    inout.write((char*)&s,sizeof(s));
    }
//    //ofstream fout;
//     //fout.open("Books_information.txt",ios::app);
    // // ifstream fin;
    // // fin.open("Books_information.txt");
    // // buy b;
    // fin.read((char*)&s,sizeof(s));
    // s.display_data();


    /// ### for dislay all file
    if(c==2){
    cout<<center("book_id",7)<<" | "<<center("book_isbn_number",16)<<" | "<<center("book_page",9)<<" | "<<center("book_edition",12)<<" | "<<center("book_name",25)<<" | "<<center("publisher_name",25)<<" | "<<center("book_price",10)<<" \n ";
    cout<<string(20*7 + 2*3, '-')<<"\n";
    inout.seekg(0,ios::beg);
    while(inout.read((char*)&s,sizeof(s)))
        s.display_data();
    
    // cout<<"Which Book You want to buy ? \n";
    // cout<<"Enter Book id number : ";
    // int pos,up;    cin>>pos;
    // up = (pos-1)*sizeof(sell);
    // inout.seekp(up,ios::beg);
    // inout.read((char*)&b,sizeof(buy));
    // b.delete_book(pos);
    }
}
