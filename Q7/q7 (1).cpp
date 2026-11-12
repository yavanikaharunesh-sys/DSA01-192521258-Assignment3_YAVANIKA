#include <cmath>
#include <iomanip>
#include <iostream>
#include <stdexcept>
using namespace std;

// Complex number: re + j*im. Used for impedance Z = R + jX.
class Complex {
    double re, im;
public:
    Complex() : re(0), im(0) {}                         // default
    Complex(double r) : re(r), im(0) {}                 // from real part
    Complex(double r, double i) : re(r), im(i) {}       // from real and imaginary

    double magnitude() const { return sqrt(re * re + im * im); }

    // members: they work on the left operand (this)
    Complex operator+(const Complex& o) const { return Complex(re + o.re, im + o.im); }
    Complex operator-(const Complex& o) const { return Complex(re - o.re, im - o.im); }
    // (a+jb)(c+jd) = (ac - bd) + j(ad + bc)
    Complex operator*(const Complex& o) const
    {
        return Complex(re * o.re - im * o.im, re * o.im + im * o.re);
    }
    // (a+jb)/(c+jd) = ((ac + bd) + j(bc - ad)) / (c^2 + d^2)
    Complex operator/(const Complex& o) const
    {
        double d = o.re * o.re + o.im * o.im;
        if (d == 0) throw runtime_error("division by zero impedance");
        return Complex((re * o.re + im * o.im) / d, (im * o.re - re * o.im) / d);
    }
    bool operator==(const Complex& o) const { return re == o.re && im == o.im; }

    // friend: left operand is the stream, not a Complex
    friend ostream& operator<<(ostream& os, const Complex& z)
    {
        return os << z.re << (z.im < 0 ? " - j" : " + j") << fabs(z.im);
    }
};

int main()
{
    const double PI = 3.14159265358979;
    double R = 10, L = 0.1, C = 100e-6, w = 2 * PI * 50;   // 50 Hz supply

    Complex Zr(R, 0);                    // resistor:  R + j0
    Complex Zl(0, w * L);                // inductor:  0 + jwL
    Complex Zc(0, -1 / (w * C));         // capacitor: 0 - j/(wC)

    cout << fixed << setprecision(4);
    cout << "Zr = " << Zr << "\nZl = " << Zl << "\nZc = " << Zc << endl;

    Complex series = Zr + Zl + Zc;       // series: add
    cout << "\nSeries RLC   Z = " << series << "   |Z| = " << series.magnitude() << " ohm" << endl;

    Complex parallel = (Zr * Zl) / (Zr + Zl);   // parallel of R and L: (Z1*Z2)/(Z1+Z2)
    cout << "Parallel R||L Z = " << parallel << "   |Z| = " << parallel.magnitude() << " ohm" << endl;

    try {
        Complex bad = Zr / Complex(0, 0);       // division by a zero impedance
        cout << bad << endl;
    } catch (const exception& e) {
        cout << "Error handled: " << e.what() << endl;
    }
    return 0;
}
