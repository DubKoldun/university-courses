#include <string>
#include "expression.h"

using std::string;

expression* yyparse(std::string const& some_str) {
    for (size_t i  = 0; i < some_str.size() || some_str[i] != '\n' || some_str[i] != '\t'; ++i) {

    }
}

int main() {

}
