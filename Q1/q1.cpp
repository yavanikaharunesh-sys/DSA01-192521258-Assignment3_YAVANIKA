#include <iostream>
#include <string>
using namespace std;

class Book {
    string title;                  // members are initialised in THIS (declaration) order
    string author;
    int copies;
public:
    // Main constructor: the ONLY place that checks copies (no negative allowed)
    Book(const string& t, const string& a, int c)
        : title(t), author(a), copies(c < 0 ? 0 : c) {}

    // Donated book (title only): delegates to the main constructor
    explicit Book(const string& t) : Book(t, "Unknown", 1) {}

    // Empty record to fill later: delegates, copies = 0 (never garbage)
    Book() : Book("Untitled", "Unknown", 0) {}

    void print() const
    {
        cout << title << " | " << author << " | copies: " << copies << endl;
    }
};

int main()
{
    Book b1("C++ Primer", "Lippman", 5);   // new book, full details
    Book b2("Donated Novel");              // donated, title only
    Book b3;                               // empty record
    Book b4("Bad Book", "Nobody", -3);     // invalid copies -> becomes 0
    Book shelf[2];                         // array needs the default constructor

    b1.print();
    b2.print();
    b3.print();
    b4.print();
    shelf[0].print();

    // explicit: Book b5 = string("X");   <- compiles WITHOUT explicit, ERROR with it
    return 0;
}
