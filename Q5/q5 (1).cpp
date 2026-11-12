#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Time {
    int h, m, s;
public:
    Time(int hh = 0, int mm = 0, int ss = 0) : h(hh), m(mm), s(ss) {}

    // prefix ++t : add a second, return the NEW value by reference
    Time& operator++()
    {
        if (++s == 60) { s = 0; if (++m == 60) { m = 0; h++; } }
        return *this;
    }
    // postfix t++ : the dummy int tells the compiler this is postfix.
    // Returns the OLD value as a copy, so it is slower.
    Time operator++(int)
    {
        Time old = *this;
        ++(*this);
        return old;
    }

    bool operator==(const Time& o) const { return h == o.h && m == o.m && s == o.s; }
    bool operator<(const Time& o) const
    {
        return h * 3600 + m * 60 + s < o.h * 3600 + o.m * 60 + o.s;
    }

    friend ostream& operator<<(ostream& os, const Time& t)
    {
        os << t.h << ":" << (t.m < 10 ? "0" : "") << t.m << ":" << (t.s < 10 ? "0" : "") << t.s;
        return os;
    }
};

class Playlist {
    vector<string> tracks;
    string error = "Invalid track";      // returned when the index is bad
public:
    Playlist(const vector<string>& t) : tracks(t) {}

    // non-const version: can change the track (playlist[0] = "New")
    string& operator[](int i)
    {
        if (i < 0 || i >= (int)tracks.size()) {
            cout << "Error: index " << i << " out of range" << endl;
            return error;
        }
        return tracks[i];
    }
    // const version: needed when the Playlist itself is const
    const string& operator[](int i) const
    {
        if (i < 0 || i >= (int)tracks.size()) {
            cout << "Error: index " << i << " out of range" << endl;
            return error;
        }
        return tracks[i];
    }
};

int main()
{
    Time t(0, 59, 59);
    Time a = t++;                          // a = old value
    Time b = ++t;                          // b = new value
    cout << "a = " << a << ", b = " << b << ", t = " << t << endl;
    cout << boolalpha << "a < b: " << (a < b) << ", a == b: " << (a == b) << endl;

    Playlist list({"Song A", "Song B", "Song C"});
    const Playlist& view = list;
    cout << "Track 1: " << list[1] << endl;
    list[1] = "Song B (remix)";
    cout << "Track 1 now: " << view[1] << endl;
    list[-1];
    list[3];

    Time now(0, 0, 58);                    // short playback simulation
    for (int i = 0; i < 3; i++) { cout << "Playing " << list[i] << " at " << now << endl; ++now; }
    return 0;
}
