#include <iostream>
#include <vector>
#include <math.h>

using std::cout;
using std::cin;

long long primeFind(long long n) {
  if (n % 2 == 0) return 2;
  for (long long i = 3; i*i < n; i+=2) {
    if (n % i == 0) return i;
  }
}

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



long long mul_mod(long long a, long long b, long long mod) {
    long long res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % mod;
        a = (a * 2ll) % mod;
        b >>= 1;
    }
    return res;
}
long long power(long long p, long long n, long long mod) {
    long long res = 1;
    while (n) {
        if (n & 1)
            res = mul_mod(res, p, mod);
        p = mul_mod(p, p, mod);
        n >>= 1;
    }
    return res;
}

int main() {
  long long n, e, C, p, q, d, fi, buff;
  cin >> n >> e >> C;
  p = primeFind(n);
  q = n/p;
  fi = (p-1)*(q-1);
  // cout << "D: " << p << " " << q << " " << fi << "\n";
  gcdex(e,fi,d,buff);
  d = (d % fi + fi) % fi;

  // cout << (e*d)%fi << "   ";
  cout << power(C,d,n);
}
