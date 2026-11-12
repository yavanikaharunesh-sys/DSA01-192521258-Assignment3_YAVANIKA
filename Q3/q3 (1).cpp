#include <iostream>
#include <string>
using namespace std;

class Event {
    string name;
    int rows, seats;
    bool** map;                          // map[r][s] = true if booked
public:
    // Dynamic constructor: allocates a 2D seat map with new
    Event(const string& n, int r, int s) : name(n), rows(r), seats(s)
    {
        map = new bool*[rows];
        for (int i = 0; i < rows; i++) map[i] = new bool[seats]();   // () sets all false
        cout << "[+] " << name << " created: " << rows << " x " << seats
             << " = " << rows * seats * sizeof(bool) << " bytes of seats" << endl;
    }

    bool book(int r, int s)
    {
        if (r < 0 || r >= rows || s < 0 || s >= seats || map[r][s]) return false;
        map[r][s] = true;
        return true;
    }
    bool cancel(int r, int s)
    {
        if (r < 0 || r >= rows || s < 0 || s >= seats || !map[r][s]) return false;
        map[r][s] = false;
        return true;
    }
    int booked() const
    {
        int c = 0;
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < seats; j++) if (map[i][j]) c++;
        return c;
    }

    // Destructor: releases EVERY allocation (each row, then the row pointers)
    ~Event()
    {
        cout << "[-] " << name << " closing: " << booked() << " of "
             << rows * seats << " seats booked" << endl;
        for (int i = 0; i < rows; i++) delete[] map[i];
        delete[] map;
    }
};

int main()
{
    Event hall("Stack Event", 2, 3);          // on the stack: destroyed at end of main
    hall.book(0, 1);
    hall.book(1, 2);
    hall.cancel(0, 1);

    {
        Event blockEvent("Block Event", 2, 2); // destroyed at the closing brace
        blockEvent.book(0, 0);
    }

    Event* heapEvent = new Event("Heap Event", 3, 3);   // on the heap
    heapEvent->book(2, 2);
    delete heapEvent;                                    // destroyed here

    Event empty("Zero Rows Event", 0, 5);     // zero rows is safe
    cout << "end of main" << endl;
    return 0;
}
