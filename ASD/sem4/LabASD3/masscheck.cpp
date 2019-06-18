#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>

// std::ifstream cin("cout/cin.cin");
// std::ofstream cout("cout/cout.cout");
// std::ofstream time_("cout/time,cout");

using std::vector;
using std::cout;
using std::cin;

void sieve(size_t n, char * a) {
  for (size_t i = 2; i < n+1; ++i) {
    if (a[i]) {
        for (unsigned long long j = static_cast<unsigned long long>(i)*i; j < n+1; j+=i) {
          a[j] = false;
        }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // unsigned int start_time =  clock(); // начальное время
  // // здесь должен быть фрагмент кода, время выполнения которого нужно измерить

  char * ans = new char[20000010];
  for(int i = 0; i < 20000010; ++i) {
    ans[i] = true;
  }
  //vector<char> ans(1000000, true);
  ans[0] = false;
  ans[1] = false;
  sieve(20000000, ans);

  size_t n;
  cin >> n;

  for (size_t i = 0; i < n; ++i) {
    unsigned int k;
    cin >> k;
    if(ans[k]) cout << "YES\n";
    else cout << "NO\n";
  }

  delete[] ans;

  // unsigned int end_time = clock(); // конечное время
  // time_ << end_time - start_time; // искомое время

  return 0;
}
