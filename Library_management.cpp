#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

class Book{
    bool is_available;
    public:
    string BookTitle;
    int BookNumber;
    int BookCost;
    Book(string name, int cost, int number)
    {
        this->BookTitle = name;
        this->BookNumber = number;
        this->BookCost = cost;
        this->is_available = true;
    }
    void set_isavailable(bool var)
    {
        this->is_available = var;
    }
    bool get_isavailable()
    {
        return this->is_available;
    }
};
class Library {
    static int book_id;
    vector<Book> lst_books;
    public:
    int addbook(string name,int cost)
    {
        for(Book a: lst_books)
        {
            string b_name = a.BookTitle;
            int res = b_name.compare(name);
            if(res == 0) return -1;
        }
        Book b(name,cost,book_id++);
        lst_books.push_back(b);
        return book_id;
    }
    bool issuebook(string name)
    {
        for(Book& a:lst_books)
        {
            string b_name = a.BookTitle;
            int res = b_name.compare(name);
            if(res == 0)
            {
                if(a.get_isavailable())
                {
                    a.set_isavailable(false);
                    return true;
                }
            }
        }
        return false;
    }
    void return_issuedBook(string name)
    {
        for(Book& a:lst_books)
        {
            string b_name = a.BookTitle;
            if(b_name.compare(name) == 0)
            {
                a.set_isavailable(true);
                return;
            }
        }
    }
    void view_issued_books()
    {
        for(Book a:lst_books)
        {
            if(!a.get_isavailable())
            {
                cout<<"Book Title: "<<a.BookTitle<<endl;
            }
        }
    }
    string search_book(string name)
    {
        for(Book a:lst_books)
        {
            string b_name = a.BookTitle;
            if(b_name.compare(name) == 0)
            {
             if(a.get_isavailable())
             {
                 return "Book is available in Library";
             }
             else
             {
                 return "Book is currently not available";
             }
            }
        }
        return "Book is not added in Library";
    }
};
int Library::book_id = 0;
class LibraryManager {
    private:
    Library L;
    public:
    string addbook(string name,int cost)
    {
        int res = this->L.addbook(name,cost);
        if(res == -1)
        {
            return "Book is already added";
        }
        else
        {
            return "Book is added with reference Id:" + to_string(res);
        }
    }
    string issuebook(string name)
    {
        if(this->L.issuebook(name))
        {
            return "Please take Book";
        }
        else
        {
            return "Entered book is currently not available in library";
        }
    }
    void view_issuebooks()
    {
        this->L.view_issued_books();
    }
    string searchBook(string name)
    {
        return this->L.search_book(name);
    }
    void return_book(string name)
    {
        this->L.return_issuedBook(name);
    }
};

int main()
{
    LibraryManager lm;
    string res;
    res = lm.addbook("Secret",550);
    cout<<res<<endl;
    res = lm.addbook("Prince",650);
    cout<<res<<endl;
    res = lm.addbook("Brave",10);
    cout<<res<<endl;
    res = lm.issuebook("Brave1");
    cout<<res<<endl;
    res = lm.issuebook("Brave");
    cout<<res<<endl;
    cout<<"Issued Books"<<endl;
    lm.view_issuebooks();
    res = lm.searchBook("Prince");
    cout<<res<<endl;
    lm.return_book("Brave");
    cout<<"Issued Books"<<endl;
    lm.view_issuebooks();
    return 0;
}
