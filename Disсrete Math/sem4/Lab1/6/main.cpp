#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::cin;

static const long long MOD = 104857601;

class Polynom {
    vector<long long> coefficients;
    size_t size;

public:

    explicit Polynom(size_t size) : size(size) {
        coefficients.resize(size);
    }

    explicit Polynom(vector<long long> generator) : coefficients(std::move(generator)), size(coefficients.size()) {};

    vector<long long> const &return_coef() const;

    long long return_size() const;

    Polynom operator*(Polynom const &a) const;

    Polynom operator*(size_t i);

    Polynom(Polynom const &a) : coefficients(a.return_coef()), size(a.return_size()) {};

    Polynom &operator=(Polynom const &a);

    long long &operator[](size_t i);

    long long operator[](size_t i) const;
};

vector<long long> const &Polynom::return_coef() const {
    return coefficients;
}

Polynom Polynom::operator*(Polynom const &a) const {

    vector<long long> newCoef(size);

    for (size_t i = 0; i < 2 * (size) - 1; i += 2) {
        long long buff = 0;
        for (size_t j = 0; j < i + 1; ++j) {
            long long this_ = (j > size - 1 ? 0 : (*this)[j]);
            long long a_ = (i - j > size - 1 ? 0 : a[i - j]);
            buff = (( buff + this_ * a_) + MOD) % MOD;
        }
        newCoef[i / 2] = buff;
    }
    return Polynom(newCoef);
}

long long Polynom::return_size() const {
    return size;
}

long long &Polynom::operator[](size_t i) {
    return coefficients[i];
}

long long Polynom::operator[](size_t i) const {
    return coefficients[i];
}

Polynom &Polynom::operator=(Polynom const &a) {
    for (size_t i = 0; i < size; ++i) {
        (*this)[i] = a[i];
    }
    return *this;
}


long long return_A_n(long long n, vector<long long> &a, Polynom &Q) {

    long long k = a.size() >> 1;

    Polynom negQ(k + 1);

    Polynom R(k + 1);

    while (n > k - 1) {
        for (size_t i = k; i < 2 * k; ++i) {
            a[i] = 0;
            for (size_t j = 1; j < k + 1; ++j) {
                a[i] -=  Q[j] * a[i - j];
                a[i] %= MOD;
                while (a[i] < 0)
                    a[i] += MOD;
            }
        }

        for (size_t i = 0; i < k + 1; ++i)
            negQ[i] = (i % 2 == 0 ? Q[i] : -Q[i] + MOD);

        R = Q * negQ;
        Q = R;

        size_t currentIndex = 0;
        for (size_t i = 0; i < 2 * k; ++i) {
            if (n % 2 == i % 2) {
                a[currentIndex] = a[i];
                ++currentIndex;
            }
        }
        n >>= 1;
    }
    return a[n];
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    size_t k, n;
    cin >> k >> n;
    vector<long long> A(2 * k);
    --n;

    Polynom Q(k + 1);
    Q[0] = 1;

    for (size_t i = 0; i < k; ++i) cin >> A[i];
    for (size_t i = 1; i < k + 1; ++i) {
        cin >> Q[i];
        Q[i] = (-Q[i] + MOD);
    }

    cout << return_A_n(n, A, Q);

    return 0;
}
