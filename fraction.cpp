#include <iostream>
#include <cstdlib>
#include <cmath>


class Fraction {
    int numerator_;
    int denominator_;
    //no more variables
    void Check(int numerator, int denominator);
    public:
    Fraction() {
            numerator_ = 0;
            denominator_ = 1;
        }

    Fraction(int numerator, int denominator) {
        if (denominator == 0) {
            denominator = 1;
            std::cout << "Error! Now denominator is 1." << std::endl;
        }
        Check(numerator, denominator);
        numerator_ = numerator;
        denominator_ = denominator;
    }

    int Nok(int numerator, int denominator);
    int Nod(int numerator, int denominator);

    bool operator < (const Fraction & cFraction) const;
    bool operator > (const Fraction & cFraction) const;
    bool operator == (const Fraction & cFraction) const;
    bool operator != (const Fraction & cFraction) const;
    bool operator <= (const Fraction & cFraction) const;
    bool operator >= (const Fraction & cFraction) const;

    Fraction operator * (int integer) const;
    friend Fraction operator * (int integer,
        const Fraction & cFraction);
    Fraction operator / (int integer) const;
    friend Fraction operator / (int integer,
        const Fraction & cFraction);
    Fraction operator + (int integer) const;
    friend Fraction operator + (int integer,
        const Fraction & cFraction);
    Fraction operator - (int integer) const;
    friend Fraction operator - (int integer,
        const Fraction & cFraction);

    Fraction operator = (const Fraction & cFraction);
    Fraction & operator /= (const Fraction & cFraction);
    Fraction & operator *= (const Fraction & cFraction);
    Fraction & operator -= (Fraction & cFraction);
    Fraction & operator += (Fraction & cFraction);

    Fraction operator * (const Fraction & cFraction) const;
    Fraction operator / (const Fraction & cFraction) const;
    Fraction operator + (Fraction & cFraction);
    Fraction operator - (Fraction & cFraction);

    Fraction & operator++();
    Fraction & operator--();
    Fraction operator--(int);
    Fraction operator++(int);

////////////
    int GetNumerator() { 
        return numerator_; 
    }
    int GetDenominator() {
        return denominator_; 
    }
    void ReplaceFraction(int numerator,  int denominator);
    void ReplaceNumerator(const int numerator)
    {
        numerator_ = numerator;
    }
    void ReplaceDenominator(int denominator);
/////////////
    void Display(); //one display
    void Enter();
    void Pow(const int k);
    void Abs();
};

void Fraction::ReplaceDenominator(int denominator)
{
        if (denominator == 0)
        {
            std::cout << "Error! Denominator is zero. Reenter: ";
            int temp;
            while (!(std::cin >> temp) || temp == 0)
            {
                std::cin.clear();
                while(std::cin.get() != '\n')
                    continue;
                std::cout << "Reenter again! " << std::endl;
            }
            denominator = temp;
        }
        denominator_ = denominator;
}
void Fraction::Enter() {

    std::cout << "Enter numerator and denominator: " << std::endl;
    std::cin >> numerator_;
    while (!(std::cin >> denominator_) || (denominator_ == 0)) {
        std::cin.clear();
        while (std::cin.get() != '\n')
            continue;
        std::cout << "Enter again your denominator. " << std::endl;
    } //denominator can't be zero

}
void Fraction::ReplaceFraction(int numerator,  int denominator)
{   //instead of constr.
        if (denominator == 0)
        {
            std::cout << "Error! Denominator is zero. Reenter: ";
            int temp;
            while (!(std::cin >> temp) || temp == 0)
            {
                std::cin.clear();
                while(std::cin.get() != '\n')
                    continue;
                std::cout << "Reenter again! " << std::endl;
            }
            denominator = temp;
        }
        numerator_ = numerator;
        denominator_ = denominator;
        Check(numerator_, denominator_);
}
void Fraction::Display() {
    Check(numerator_, denominator_);
    if (numerator_ % denominator_ == 0) {
        std::cout << numerator_ / denominator_ << std::endl;
    } else if ((numerator_ > denominator_) && (numerator_ % denominator_ != 0)) {
        int cl, num, dem;
        cl = numerator_ / denominator_;
        num = numerator_ % denominator_;
        dem = denominator_;
        std::cout << cl << " * (" << num << " / " << dem << ")  ||  " <<
            numerator_ << '/' << denominator_ << std::endl;
    } else {
        std::cout << numerator_ << '/' << denominator_ << std::endl;
    }

}
void Fraction::Check(int numerator, int denominator) {

    int del = Nod(numerator, denominator);
    numerator_ /= del;
    denominator_ /= del;
    if (numerator_ < 0 && denominator_ < 0) {
        numerator_ = -numerator_;
        denominator_ = -denominator_;
    }
}

bool Fraction::operator < (const Fraction & cFraction) const {
    if (numerator_ * cFraction.denominator_ < cFraction.numerator_ * denominator_)
        return true;
    return false;
}
bool Fraction::operator > (const Fraction & cFraction) const {
    if (numerator_ * cFraction.denominator_ > cFraction.numerator_ * denominator_)
        return true;
    return false;
}
bool Fraction::operator == (const Fraction & cFraction) const {
    if (numerator_ * cFraction.denominator_ == cFraction.numerator_ * denominator_)
        return true;
    return false;
}
bool Fraction::operator != (const Fraction & cFraction) const {
    if ((numerator_ * cFraction.denominator_) != (cFraction.numerator_ * denominator_))
        return true;
    return false;
}
bool Fraction::operator <= (const Fraction & cFraction) const {
    if ((numerator_ * cFraction.denominator_ < cFraction.numerator_ * denominator_) || numerator_ * cFraction.denominator_ == cFraction.numerator_ * denominator_)
        return true;
    return false;
}
bool Fraction::operator >= (const Fraction & cFraction) const {
    if ((numerator_ * cFraction.denominator_ > cFraction.numerator_ * denominator_) || numerator_ * cFraction.denominator_ == cFraction.numerator_ * denominator_)
        return true;
    return false;
}

Fraction Fraction::operator * (int integer) const {
    Fraction temp;
    temp.numerator_ = integer * numerator_;
    temp.denominator_ = denominator_;
    return temp;
}
Fraction operator * (int integer,
    const Fraction & cFraction) {
    Fraction temp;
    integer *= cFraction.denominator_;
    temp.numerator_ = integer - cFraction.numerator_;
    temp.denominator_ = cFraction.denominator_;
    return temp;
}
Fraction operator / (int integer,
    const Fraction & cFraction) {
    Fraction temp;
    if (integer == 0) {
        std::cout << "Can't calculate this operation!  ";
        temp.numerator_ = cFraction.numerator_;
        temp.denominator_ = cFraction.denominator_;
        return temp;
    }
    temp.numerator_ = cFraction.numerator_;
    temp.denominator_ = integer * cFraction.denominator_;
    return temp;
}
Fraction Fraction::operator / (int integer) const {
    if (integer == 0) {
        std::cout << "Cann't calculate this operation!  ";
        return *this;
    }

    Fraction temp;
    temp.numerator_ = numerator_;
    temp.denominator_ = denominator_ * integer;
    return temp;

}
Fraction Fraction::operator - (int integer) const {
    Fraction temp;
    integer *= denominator_;
    temp.numerator_ = numerator_ - integer;
    temp.denominator_ = denominator_;
    return temp;
}
Fraction Fraction::operator + (int integer) const {
    Fraction temp;
    integer *= denominator_;
    temp.numerator_ = numerator_ + integer;
    temp.denominator_ = denominator_;
    return temp;
}
Fraction operator + (int integer,
    const Fraction & cFraction) {
    Fraction temp;
    integer *= cFraction.denominator_;
    temp.numerator_ = cFraction.numerator_ + integer;
    temp.denominator_ = cFraction.denominator_;
    return temp;
}
Fraction operator - (int integer,
    const Fraction & cFraction) {
    Fraction temp;
    integer *= cFraction.denominator_;
    temp.numerator_ = integer - cFraction.numerator_;
    temp.denominator_ = cFraction.denominator_;
    return temp;
}

Fraction Fraction::operator * (const Fraction & cFraction) const {
    Fraction temp;
    temp.numerator_ = cFraction.numerator_ * numerator_;
    temp.denominator_ = cFraction.denominator_ * denominator_;
    return temp;
}
Fraction Fraction::operator / (const Fraction & cFraction) const {

    if (cFraction.numerator_ == 0) {
        std::cout << "Cann't calculate this operation! " << std::endl;
        return *this;
    }

    Fraction temp;
    temp.numerator_ = numerator_ * cFraction.denominator_;
    temp.denominator_ = denominator_ * cFraction.numerator_;
    return temp;

}
Fraction Fraction::operator + (Fraction & cFraction) {
    Fraction temp;
    if (denominator_ == cFraction.denominator_) {
        temp.numerator_ = numerator_ + cFraction.numerator_;
        temp.denominator_ = denominator_;
    } else {
        int k = Nok(denominator_, cFraction.denominator_);
        int k2 = k / cFraction.denominator_;
        k /= denominator_;
        denominator_ *= k;
        numerator_ *= k;
        cFraction.denominator_ *= k2;
        cFraction.numerator_ *= k2;
        temp.numerator_ = numerator_ + cFraction.numerator_;
        temp.denominator_ = cFraction.denominator_;

    }
    return temp;
}
Fraction Fraction::operator - (Fraction & cFraction) {
    Fraction temp;
    if (denominator_ == cFraction.denominator_) {
        temp.numerator_ = numerator_ - cFraction.numerator_;
        temp.denominator_ = denominator_;
    } else {
        int k = Nok(denominator_, cFraction.denominator_);

        int k2 = k / cFraction.denominator_;
        k /= denominator_;
        denominator_ *= k;
        numerator_ *= k;
        cFraction.denominator_ *= k2;
        cFraction.numerator_ *= k2;
        temp.numerator_ = numerator_ - cFraction.numerator_;
        temp.denominator_ = cFraction.denominator_;
    }
    return temp;
}
Fraction & Fraction::operator *= (const Fraction & cFraction) {
    numerator_ *= cFraction.numerator_;
    denominator_ *= cFraction.denominator_;
    return *this;
}
Fraction & Fraction::operator += (Fraction & cFraction) {

    if (denominator_ == cFraction.denominator_) {
        numerator_ += cFraction.numerator_;
    } else {
        int k = Nok(denominator_, cFraction.denominator_);
        int k2 = k / cFraction.denominator_;
        k /= denominator_;
        denominator_ *= k;
        numerator_ *= k;
        cFraction.denominator_ *= k2;
        cFraction.numerator_ *= k2;
        numerator_ += cFraction.numerator_;
    }
    return *this;
}
Fraction & Fraction::operator /= (const Fraction & cFraction) {
    if (cFraction.numerator_ == 0) {
        std::cout << "Cann't calculate this operation! " << std::endl;
        return *this;
    }
    numerator_ *= cFraction.denominator_;
    denominator_ *= cFraction.numerator_;
    return *this;
}
Fraction & Fraction::operator -= (Fraction & cFraction) {
    if (denominator_ == cFraction.denominator_) {
        numerator_ -= cFraction.numerator_;
    } else {
        int k = Nok(denominator_, cFraction.denominator_);

        int k2 = k / cFraction.denominator_;
        k /= denominator_;
        denominator_ *= k;
        numerator_ *= k;
        cFraction.denominator_ *= k2;
        cFraction.numerator_ *= k2;
        numerator_ -= cFraction.numerator_;

    }
    return *this;
}
Fraction Fraction::operator = (const Fraction & cFraction) {
    numerator_ = cFraction.numerator_;
    denominator_ = cFraction.denominator_;
    return *this;
}
Fraction Fraction::operator++(int) {
    Fraction temp = ++( * this);
    return temp;
}
Fraction Fraction::operator--(int) {
    Fraction temp = --( * this);
    return temp;
}

Fraction & Fraction::operator--() {
    numerator_ -= denominator_;
    return *this;
}
Fraction & Fraction::operator++() {
    numerator_ += denominator_;
    return *this;
}

int Fraction::Nod(int numerator, int denominator) {
    numerator = (numerator < 0) ? -numerator : numerator;
    denominator = (denominator < 0) ? -denominator : denominator;
    if (numerator % denominator == 0)
        return denominator;
    if (denominator % numerator == 0)
        return numerator;
    if (numerator > denominator)
        return Nod(numerator % denominator, denominator);
    return Nod(numerator, denominator % numerator);
}
int Fraction::Nok(int numerator, int denominator) {
    return (numerator * denominator) / Nod(numerator, denominator);
}

void Fraction::Pow(const int k) {
    if (k > 0) {
        numerator_ = pow(numerator_, k);
        denominator_ = pow(denominator_, k);
    } else {

        int temp = numerator_;
        numerator_ = pow(denominator_, -k);
        denominator_ = pow(temp, -k);

    }
}
void Fraction::Abs() {
    numerator_ = numerator_ < 0 ? -numerator_ : numerator_;
    denominator_ = denominator_ < 0 ? -denominator_ : denominator_;
}

int main() {
    using std::cin;
    using std::cout;
    using std::endl;
    Fraction a, b, c;
    std::cin >> c;
    //  c = c - 1;
    //  c = 1 - c;
    c.Display();
    c.ReplaceFraction(8,0);
    //c = Fraction(12,16);
    //c = {3,8};
    c.Display();
    c.ReplaceNumerator(3);
    c.ReplaceDenominator(0);
    c.Display();
    c.ReplaceFraction(-2,-4);
    cout << c.GetNumerator()  << "  "
    << c.GetDenominator() << endl;

    a.Enter();
    b.Enter();
    Fraction res;

    cout << "a * b = ";
    res = a * b;
    res.Display();

    cout << "a + b = ";
    res = a + b;
    res.Display();

    cout << "a - b = ";
    res = a - b;
    res.Display();

    cout << "a / b = ";
    res = a / b;
    res.Display();

    Fraction x;
    std::cout << "For Abs " << std::endl;
    x.Enter();
    cout << "abs: ";
    x.Abs();
    x.Display();

    int forPow;
    Fraction s;
    cout << "Enter for pow integer: ";
    cin >> forPow;
    s.Enter();
    s.Pow(forPow);
    s.Display();

    Fraction press;
    press.Enter();
    Fraction f;
    f.Enter();
    press += f;
    cout << "Result is: " << endl;
    press.Display();

    c.Enter();
    cout << "++c: ";
    ++c;
    cout << endl;
    c.Display();
    cout << "c++:";
    c++;
    c.Display();
    cout << endl;
    c--;
    c.Display();
    cout << endl;

    Fraction y;
    x.Enter();
    y.Enter();
    cout.setf(std::ios::boolalpha);
    cout << "x < y is " << (x < y) << endl;
    cout << "x > y is " << (x > y) << endl;
    cout << "x <= y is " << (x <= y) << endl;
    cout << "x >= y is " << (x >= y) << endl;
    cout << "x == y is " << (x == y) << endl;
    cout << "x != y is " << (x != y) << endl;

    return 0;
}

