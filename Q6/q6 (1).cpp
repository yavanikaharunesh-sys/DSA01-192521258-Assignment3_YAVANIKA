#include <cstring>
#include <iostream>
using namespace std;

class Text {
    char* data;
    int len;
    static int copies;                       // counts copy constructor calls
public:
    Text(const char* s = "")                 // constructor
    {
        len = strlen(s);
        data = new char[len + 1];
        strcpy(data, s);
    }
    Text(const Text& o)                      // copy constructor (deep copy)
    {
        copies++;
        len = o.len;
        data = new char[len + 1];
        strcpy(data, o.data);
    }
    Text& operator=(const Text& o)           // copy assignment: member, so it can change *this
    {
        if (this == &o) return *this;        // self-assignment guard
        char* fresh = new char[o.len + 1];
        strcpy(fresh, o.data);
        delete[] data;
        data = fresh;
        len = o.len;
        return *this;
    }
    ~Text() { delete[] data; }

    Text operator+(const Text& o) const      // concatenation: returns a new Text
    {
        char* tmp = new char[len + o.len + 1];
        strcpy(tmp, data);
        strcat(tmp, o.data);
        Text r(tmp);
        delete[] tmp;
        return r;
    }
    bool operator==(const Text& o) const { return strcmp(data, o.data) == 0; }
    bool operator!=(const Text& o) const { return !(*this == o); }

    friend ostream& operator<<(ostream& os, const Text& t) { return os << t.data; }
    static int copyCount() { return copies; }
};
int Text::copies = 0;

int main()
{
    Text a("Hello "), b("SMS "), c("Gateway");
    Text msg = a + b + c;
    cout << "a + b + c = " << msg << endl;
    cout << "copies made by the copy constructor: " << Text::copyCount() << endl;

    cout << boolalpha << "msg == msg: " << (msg == msg)
         << ", a != b: " << (a != b) << endl;

    Text e;                                    // empty message
    cout << "empty message: [" << e << "]" << endl;

    msg = msg;                                 // self-assignment is safe
    cout << "after msg = msg: " << msg << endl;

    Text longMsg("This is a long SMS message used to test that the dynamic array "
                 "grows to the correct size without any overflow at all.");
    cout << "long message: " << longMsg << endl;
    return 0;
}
