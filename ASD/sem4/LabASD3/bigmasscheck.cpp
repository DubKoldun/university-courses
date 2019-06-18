#include <iostream>
#include <math.h>
#include <algorithm>
#include <vector>
#include <ctime>

using std::cin;
using std::cout;
using std::vector;

long long pows[63];
const long long INF = 1e18;

void sieve(long long n, char * a) {
    for (long long i = 2; i < n+1; ++i) {
        if (a[i]) {
            for (unsigned long long j = static_cast<unsigned long long>(i)*i; j < n+1; j+=i) {
                a[j] = false;
            }
        }
    }
}

long long anoPower(long long a, long long b, long long mod) {
    long long res = 0;
    while (b) {
        if (b & 1)
            res = (res + a) % mod;
        a = (a * 2ll) % mod;
        b >>= 1;
    }
    return res;
}

long long power(long long a, long long b, long long mod) {
    long long res = 1;
    while (b) {
        if (b & 1)
            res = anoPower(res, a, mod);
        a = anoPower(a, a, mod);
        b >>= 1;
    }
    return res;
}

bool isPrime(long long n, long long count) {
    switch (n) {
      case 1: {
         return false;
      }
      case 2: {
        return true;
      }
      case 3: {
        return true;
      }
      case 4: {
        return false;
      }
      default: {
        size_t s = 0;
        long long d = n - 1;

        while (!(d&1)) {
            d /= 2;
            ++s;
        }
        srand(time(NULL));
        for (size_t i = 0; i < count; ++i) {
            long long a = 2 + rand() % (n-4);
            bool flag1 = false, flag2 = false;
            int x = power(a % n, d, n);

            if (x == 1 || x == n-1) flag1 = true;

            if (!flag1) {
                for (int r = 0; r < s; ++r) {
                    if (power(a % n, pows[r] * d, n) == n - 1) {
                        flag2 = true;
                    }
                }
            }

            if (!flag1 && !flag2) return false;
        }
          return true;
      }
  }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    char * ans = new char[20000010];
    for(int i = 0; i < 20000010; ++i) {
      ans[i] = true;
    }
    pows[0] = 1ll;
    for (size_t i = 1; i < 63; ++i)
        pows[i] = pows[i - 1] * 2ll;
    //vector<char> ans(1000000, true);
    ans[0] = false;
    ans[1] = false;
    sieve(20000000, ans);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
      long long k;
      cin >> k;
      // if (k < 20000000) {
      //     if(ans[k]) cout << "YES\n";
      //     else cout << "NO\n";
      // } else {
          if (isPrime(k,3)) cout << "YES\n";
          else cout << "NO\n";
      // }
    }

    return 0;
}
