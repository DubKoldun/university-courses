#include <fstream>

std::ifstream in ("out/azam.out");
std::ofstream out("checker/azfac.out");

using std::string;

int main() {
  string name = "factorial";
  out << "Name: " << name << "\n";
  string start;
  getline(in, start);
  out << "init: " << start.substr(7,start.length()) << "\n";
  string reject, accept, blank;
  getline(in,accept);
  out << accept << "\n";
  getline(in,reject);
  //out << reject << "\n";
  getline(in,blank);
  //out << blank << "\n";
  string state;
  while (in >> state) {
    out << "\n";
    out << state << ',';
    in >> state;
    out << state << "\n";
    in >> state;
    in >> state;
    out << state << ',';
    in >> state;
    out << state << ',';
    in >> state;
    if (state == "^") state = "-";
    out << state << "\n";
  }

}
