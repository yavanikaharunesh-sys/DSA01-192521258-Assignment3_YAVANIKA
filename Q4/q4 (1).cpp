#include <iomanip>
#include <iostream>

class Money {
    long long paise;                       // exact: no floating-point error

public:
    Money(long long rupees = 0, int p = 0) : paise(rupees * 100 + p) {}

    // TODO 1: + as a member, returns a NEW Money
    Money operator+(const Money& o) const
    {
        Money r;
        r.paise = paise + o.paise;
        return r;
    }

    Money operator-(const Money& o) const
    {
        Money r;
        r.paise = paise - o.paise;
        return r;
    }

    // += changes this object, so it returns a reference to *this
    Money& operator+=(const Money& o)
    {
        paise += o.paise;
        return *this;
    }

    // TODO 2: == as a member, << as a friend
    bool operator==(const Money& o) const { return paise == o.paise; }
    bool operator<(const Money& o) const { return paise < o.paise; }

    friend std::ostream& operator<<(std::ostream& os, const Money& m)
    {
        long long p = m.paise < 0 ? -m.paise : m.paise;
        if (m.paise < 0) os << "-";
        os << "Rs " << p / 100 << "." << std::setw(2) << std::setfill('0') << p % 100;
        return os << std::setfill(' ');
    }
};

int main()
{
    Money a(120, 75), b(79, 25);
    Money c = a + b;
    std::cout << c << '\n' << std::boolalpha << (c == Money(200)) << '\n';

    // Carry test: paise roll into rupees
    std::cout << "Rs 0.75 + Rs 0.50 = " << Money(0, 75) + Money(0, 50) << '\n';

    // Negative result: handled by printing a minus sign
    std::cout << "Rs 0.25 - Rs 0.75 = " << Money(0, 25) - Money(0, 75) << '\n';

    // Bill calculation using operators
    Money bill = Money(250, 50);
    bill += Money(49, 50);
    std::cout << "Bill total = " << bill << '\n';

    // 1,000,000 additions of Rs 0.10: Money vs double
    Money m;
    double d = 0;
    for (int i = 0; i < 1000000; i++) { m += Money(0, 10); d += 0.10; }
    std::cout << "Money : " << m << '\n';
    std::cout << std::fixed << std::setprecision(6) << "double: Rs " << d << '\n';
    return 0;
}
