//  rec09
//  Created by fanyue meng on 2022/10/28.
#include <iostream>
#include <ostream>

// If time allows use separate compilation, otherwise just define the
// class below with the methods / functions defined after main.
//#include "Rational.h"

using namespace std;

// If time allows after implementing separate compilation, then wrap
// the class in a namespace.
// using namespace CS2124;

class Rational{
    friend istream& operator>>(istream& input, Rational& rhs);
    friend ostream& operator<<(ostream& os, const Rational& rhs);
    friend bool operator==(const Rational& lhs, const Rational& rhs);
    friend bool operator<(const Rational& lhs, const Rational& rhs);
public:
    Rational(int num = 0, int den = 1);
    void normalize();
    Rational& operator+=(const Rational& rhs);
    Rational& operator++();
    Rational operator++(int dummy);
    explicit operator bool() const;
private:
    int numerator;
    int denominator;
};

Rational operator+(const Rational& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const Rational& rhs);
Rational operator--(Rational& rhs, int dummy);
Rational& operator--(Rational& rhs);
int greatestCommonDivisor(int x, int y);

int main() {
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;    // Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y) {
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

Rational operator+(const Rational& lhs, const Rational& rhs){
    Rational result(lhs);
    result += rhs;
    return result;
}

bool operator==(const Rational& lhs, const Rational& rhs){
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator!=(const Rational& lhs, const Rational& rhs){
    return !(lhs==rhs);
}

bool operator<(const Rational& lhs, const Rational& rhs){
    return (lhs.numerator/lhs.denominator) < (rhs.numerator/rhs.denominator);
}

bool operator>=(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs) || lhs == rhs;
}

bool operator<=(const Rational& lhs, const Rational& rhs){
    return (lhs < rhs) || lhs == rhs;
}

bool operator>(const Rational& lhs, const Rational& rhs){
    return !(lhs < rhs) && lhs !=rhs;
}


Rational operator--(Rational& rhs, int dummy){
    Rational result(rhs);
    rhs += -1;
    return result;
}

Rational& operator--(Rational& rhs) {
    rhs += -1;
    return rhs;
}

Rational::Rational(int num, int den): numerator(num), denominator(den) {normalize();}
void Rational::normalize() {
    if (numerator < 0 && denominator < 0){
        numerator *= -1;
        denominator *= -1;
    }
    int divisor = greatestCommonDivisor(numerator, denominator);
    numerator = numerator / divisor;
    denominator = denominator / divisor;
}
Rational& Rational::operator++() {
    numerator += denominator;
    return *this;
}
Rational& Rational::operator+=(const Rational& rhs){
    numerator += rhs.numerator;
    normalize();
    return *this;
}
Rational Rational::operator++(int dummy){
    Rational result(*this);
    numerator += denominator;
    return result;
}
Rational::operator bool() const{
    return !(numerator == 0);
}
istream& operator>>(istream& input, Rational& rhs){
    int num, den;
    char slash;
    input >> num >> slash >> den;
    rhs.numerator = num;
    rhs.denominator = den;
    return input;
}

ostream& operator<<(ostream& os, const Rational& rhs){
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
}
