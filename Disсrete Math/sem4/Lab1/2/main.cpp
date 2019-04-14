#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;


static const long long MOD = 998244353;

class Polynom {
    vector<long long> coefficients;
    size_t size;
public:

    explicit Polynom(size_t size) : size(size) {
        coefficients.resize(size);
    }

    explicit Polynom(vector<long long> generator) : coefficients(std::move(generator)), size(coefficients.size()) {};

    void refresh_size(size_t size1);

    vector<long long> const &return_coef() const;

    vector<long long> &get_coef();

    long long return_size() const;

    Polynom operator*(Polynom const &a) const;

    Polynom operator*(size_t i);

    Polynom operator+(Polynom const &a) const;

    Polynom operator/(Polynom const &a);

    long long &operator[](size_t i);

    long long operator[](size_t i) const;
};

vector<long long> const &Polynom::return_coef() const {
    return coefficients;
}


//Polynom Polynom::operator*(Polynom const &a) const {
//    vector<long long> newCoef(this->return_size() + a.return_size() - 1);
//
//    Polynom buff1 = create_buffer(this->return_size() + a.return_size() - 1, a, 0);
//
//    Polynom buff2 = create_buffer(this->return_size() + a.return_size() - 1, *this, 0);
//
//    for (size_t i = 0; i < newCoef.size(); ++i) {
//        for (size_t j = 0; j < i + 1; ++j) {
//            newCoef[i] += ((buff1[j] * buff2[i - j]) % MOD);
//            newCoef[i] %= MOD;
//        }
//    }
//
//    return Polynom(newCoef);
//}


Polynom Polynom::operator*(Polynom const &a) const {

    vector<long long> newCoef(size);

    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < i + 1; ++j) {
            newCoef[i] += ((a[j] * (*this)[i - j]) % MOD);
            newCoef[i] %= MOD;
        }
    }

    return Polynom(newCoef);
}


Polynom Polynom::operator+(Polynom const &a) const {

    vector<long long> newCoef(size);

    for (size_t i = 0; i < newCoef.size(); ++i) {
        newCoef[i] = ((*this)[i] + a[i]) % MOD;
    }

    return Polynom(newCoef);
}

long long Polynom::return_size() const {
    return size;
}

vector<long long> &Polynom::get_coef() {
    return coefficients;
}

long long &Polynom::operator[](size_t i) {
    return coefficients[i];
}

long long Polynom::operator[](size_t i) const {
    return coefficients[i];
}

Polynom Polynom::operator/(Polynom const &a) {

    vector<long long> newCoef(1000);

    for (size_t i = 0; i < newCoef.size(); ++i) {

        newCoef[i] += (*this)[i];
        for (size_t j = 0; j < i; ++j) {
            newCoef[i] = newCoef[i] - ((newCoef[j] * a[i - j]) % MOD) + MOD;
        }
        newCoef[i] %= MOD;

        newCoef[i] /= a[0];
    }

    return Polynom(newCoef);
}


void Polynom::refresh_size(size_t size1) {
    size = size1;
    coefficients.resize(size1);
}

Polynom Polynom::operator*(size_t i) {
    for (size_t k = 0; k < size; ++k) {
        (*this)[k] *= i;
    }
    return *this;
}


struct Fraction {
    long long numerator, denominator;

    Fraction(long long n, long long m) : numerator(n), denominator(m) {};

    Fraction operator*(Fraction const &a) {
        long long num = (this->numerator * a.numerator + MOD) % MOD, denum = (this->denominator * a.denominator + MOD) % MOD;
        return {num, denum};
    }

    Fraction operator+(Fraction const &a) {
        long long num = (((this->numerator * a.denominator + MOD) % MOD) + ((a.numerator * this->denominator + MOD) % MOD)), denum = (
                this->denominator * a.denominator);
        return {num, denum};
    }

    long long normalize() {
        long long x, y;
        long long g = gcdex(std::abs(denominator), MOD, x, y);
        x = (x % MOD + MOD) % MOD;
        return (std::abs(numerator) * x) % MOD;
    }

private:

    long long gcdex(long long a, long long b, long long &x, long long &y) {
        if (a == 0) {
            x = 0;
            y = 1;
            return b;
        }
        long long x1, y1;
        long long d = gcdex(b % a, a, x1, y1);
        x = y1 - (b / a) * x1;
        y = x1;
        return d;
    }

    long long gcd_func(long long a, long long b) {
        return b ? gcd_func(b, a % b) : a;
    }
};


size_t factorial(size_t i, vector<long long> &array_factorials) {
    for (size_t k = array_factorials.size(); k < i; ++k) {
        if (array_factorials.size() < k + 1) array_factorials.push_back(k + 1);
        array_factorials[k] *= array_factorials[k - 1];
        array_factorials[k] %= MOD;
    }
    return array_factorials[i - 1];
}


Polynom
tailorSeriesPolynom(size_t polynomSize, Polynom const &from, Fraction power, vector<long long> &array_factorials,
                    vector<Polynom> degrees) {
    Polynom to(100);

    to[0] = 1;

    for (size_t i = 1; i < polynomSize; ++i) {
        bool flag = false;
        Fraction coef{1, 1};
        long long coef2 = 0;
        for (size_t j = 0; j < i; ++j) {
            coef = coef * (power + Fraction(-j, 1));
        }
        coef2 += coef.normalize();
        if ((coef.denominator < false > 0) || (coef.numerator < false > 0)) {
            coef2 = -coef2;
            coef2 += MOD;
        }
        coef2 %= MOD;
        coef2 = Fraction(coef2, factorial(i, array_factorials)).normalize();
        to = to + degrees[i - 1] * coef2;
    }
    return to;
}

Polynom
tailorSeriesExponent(size_t polynomSize, Polynom const &from, vector<long long> &array_factorials,
                     vector<Polynom> degrees) {
    Polynom to(100);

    to[0] = 1;

    for (size_t i = 1; i < polynomSize; ++i) {
        long long coef = Fraction(1, factorial(i, array_factorials)).normalize();
        to = to + degrees[i - 1] * coef;
    }
    return to;
}

Polynom
tailorSeriesLn(size_t polynomSize, Polynom const &from, vector<long long> &array_factorials,
               vector<Polynom> degrees) {
    Polynom to(100);

    for (size_t i = 0; i < polynomSize; ++i) {

        long long coef = Fraction(1, i + 1).normalize();

        if (i % 2 == 1) {
            coef = -coef;
            coef += MOD;
        }

        coef %= MOD;


        to = to + degrees[i] * coef;
    }

    return to;
}


int main() {
    vector<long long> array_factorials(1, 1);

    size_t n, m;
    cin >> n >> m;


    Polynom P((vector<long long>(100)));

    for (size_t i = 0; i < n + 1; ++i) {
        cin >> P[i];
    }

    vector<Polynom> degrees(m, Polynom(P.return_coef()));

    degrees[0] = P;

    for (size_t k = 1; k < m; ++k) {
        degrees[k] = (degrees[k - 1] * P);
    }

//    for (const auto &i: degrees) {
//        for (size_t j = 0; j < i.return_size(); ++j) {
//            cout << "[" << j << "] = " << i[j] << " ";
//        }
//        cout << "\n";
//    }

    Polynom sqrt = tailorSeriesPolynom(m, P, Fraction(1, 2), array_factorials, degrees);
    Polynom exp = tailorSeriesExponent(m, P, array_factorials, degrees);
    Polynom ln = tailorSeriesLn(m, P, array_factorials, degrees);

    for (size_t i = 0; i < m; ++i) {
        cout << sqrt[i] << " ";
    }
    cout << "\n";

    for (size_t i = 0; i < m; ++i) {
        cout << exp[i] << " ";
    }
    cout << "\n";

    for (size_t i = 0; i < m; ++i) {
        cout << ln[i] << " ";
    }
    cout << "\n";

    return 0;
}
