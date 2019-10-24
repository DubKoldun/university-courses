#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

static const long long MOD = 998244353;

class Polynom {
    vector<long long> coefficients;
    size_t size;

    Polynom create_buffer(size_t size1, Polynom const &buff, long long neutral) {
        Polynom ans(vector<long long>(size1, neutral));
        for (size_t i = 0; i < buff.return_size(); ++i) {
            ans[i] = buff[i];
        }
        return ans;
    }

public:

    explicit Polynom(size_t size) : size(size) {
        coefficients.resize(size);
    }

    explicit Polynom(vector<long long> generator) : coefficients(std::move(generator)), size(coefficients.size()) {};

    void refresh_size(size_t size1);

    vector<long long> const &return_coef() const;

    vector<long long> &get_coef();

    long long return_size() const;

    Polynom operator*(Polynom const &a);

    Polynom operator+(Polynom const &a);

    Polynom operator/(Polynom const &a);

    long long &operator[](size_t i);

    long long operator[](size_t i) const;
};

vector<long long> const &Polynom::return_coef() const {
    return coefficients;
}


Polynom Polynom::operator*(Polynom const &a) {
    vector<long long> newCoef(this->return_size() + a.return_size() - 1);

    Polynom buff1 = create_buffer(this->return_size() + a.return_size() - 1, a, 0);

    Polynom buff2 = create_buffer(this->return_size() + a.return_size() - 1, *this, 0);

    for (size_t i = 0; i < newCoef.size(); ++i) {
        for (size_t j = 0; j < i + 1; ++j) {
            newCoef[i] += ((buff1[j] * buff2[i - j]) % MOD);
            newCoef[i] %= MOD;
        }
    }

    return Polynom(newCoef);
}

Polynom Polynom::operator+(Polynom const &a) {

    Polynom minimum = this->return_size() > a.return_size() ?
                      create_buffer(this->return_size(), a, 0) : create_buffer(a.return_size(), *this, 0);

    Polynom maximum = this->return_size() > a.return_size() ? *this : a;

    vector<long long> newCoef(maximum.return_size());

    for (size_t i = 0; i < newCoef.size(); ++i) {
        newCoef[i] = (maximum.return_coef()[i] + minimum.return_coef()[i]) % MOD;
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

int main() {
    size_t n, m;
    cin >> n >> m;
    Polynom P(n + 1);
    Polynom Q(m + 1);

    for (size_t i = 0; i < n + 1; ++i) {
        cin >> P[i];
    }

    for (size_t i = 0; i < m + 1; ++i) {
        cin >> Q[i];
    }

    Polynom ans = P + Q;
    Polynom ans2 = P * Q;

    cout << ans.return_size() - 1 << "\n";

    for (size_t i = 0; i < ans.return_size(); ++i) {
        cout << ans[i] % MOD << " ";
    }
    cout << "\n";

    cout << ans2.return_size() - 1 << "\n";

    for (size_t i = 0; i < ans2.return_size(); ++i) {
        cout << ans2[i] % MOD << " ";
    }
    cout << "\n";

    Polynom P1(vector<long long>(1000));
    Polynom Q1(vector<long long>(1000));

    for (size_t i = 0; i < P.return_size(); ++i) {
        P1[i] = P[i];
    }

    for (size_t i = 0; i < Q.return_size(); ++i) {
        Q1[i] = Q[i];
    }

    Polynom ans3 = P1 / Q1;

    for (size_t i = 0; i < 1000; ++i) {
        while (ans3[i] < 0) ans3[i] += MOD;
        cout << (ans3[i]) % MOD << " ";
    }

    return 0;
}