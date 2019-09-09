#include "../expression.h"

#include <set>
#include <limits>

using std::set;

const int INF = std::numeric_limits<int>::max();

struct mp {
    expression* general;
    int size = INF;
};

struct Compare {
    bool operator()(mp a, mp b) const {
          return a.size < b.size;
    }
};
