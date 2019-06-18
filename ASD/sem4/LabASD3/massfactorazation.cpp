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

void sieve(size_t n, std::vector<std::pair<size_t, size_t>> & ans, char * a) {
  for (size_t i = 2; i < n+1; ++i) {
    if (a[i]) {
        for (unsigned long long j = static_cast<unsigned long long>(i)*i; j < n+1; j+=i) {
          a[j] = false;
          if(ans[j].second == 1) {
            ans[j].first = i;
            ans[j].second = j/(unsigned long long)i;
          }
          // cout << "D: " << ans[j].first << " " << ans[j].second << "\n";
        }
    }
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  // unsigned int start_time =  clock(); // начальное время
  // // здесь должен быть фрагмент кода, время выполнения которого нужно измерить
  std::vector<std::pair<size_t, size_t>> ans(1000001);
  char * primes = new char[1000001];
  for(int i = 0; i < 1000001; ++i) {
    primes[i] = true;
    ans[i].second = 1;
    ans[i].first = i;
  }
  //vector<char> ans(1000000, true);
  primes[0] = false;
  primes[1] = false;
  sieve(1000000, ans, primes);

  size_t n;
  cin >> n;

  for (size_t i = 0; i < n; ++i) {
    unsigned int k;
    cin >> k;
    while (ans[k].second != 1) {
      cout << ans[k].first << " ";
      k = ans[k].second;
    } cout << ans[k].first << "\n";
  }

  delete[] primes;

  // unsigned int end_time = clock(); // конечное время
  // time_ << end_time - start_time; // искомое время

  return 0;
}
