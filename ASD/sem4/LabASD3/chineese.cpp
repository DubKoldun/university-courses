#include <iostream>

using std::cin;
using std::cout;

int main() {
  long long a,b,n,m;
  cin >> a >> b >> n >> m;
  while (a != b) {
    if (a < b) {
      while (a < b) {
        a+=n;
      }
    } else {
      while (b < a) {
        b+=m;
      }
    }
  }
  cout << a;
}
