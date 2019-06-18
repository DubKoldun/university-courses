#include <iostream>
#include <fstream>

std::ofstream out("out/less.out");

int main() {

  // conditions
  out << "start: s\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

  // start condition
  out << "s 0 -> go_to_right_A A >\n";
  out << "s 1 -> go_to_right_B B >\n";

  out << "go_to_right_A 0 -> go_to_right_A 0 >\n";
  out << "go_to_right_A 1 -> go_to_right_A 1 >\n";
  out << "go_to_right_A < -> check_0 < >\n";

  out << "go_to_right_B 0 -> go_to_right_B 0 >\n";
  out << "go_to_right_B 1 -> go_to_right_B 1 >\n";
  out << "go_to_right_B < -> check_1 < >\n";

  out << "check_0 0 -> go_to_left E <\n";
  out << "check_0 1 -> go_to_left M <\n";
  out << "check_0 M -> check_0 M >\n";
  out << "check_0 E -> check_0 E >\n";
  out << "check_0 L -> check_0 L >\n";
  out << "check_0 _ -> rj _ ^\n";

  out << "check_1 0 -> go_to_left L <\n";
  out << "check_1 1 -> go_to_left E <\n";
  out << "check_1 M -> check_1 M >\n";
  out << "check_1 E -> check_1 E >\n";
  out << "check_1 L -> check_1 L >\n";
  out << "check_1 _ -> rj _ ^\n";

  out << "go_to_left M -> go_to_left M <\n";
  out << "go_to_left E -> go_to_left E <\n";
  out << "go_to_left L -> go_to_left L <\n";
  out << "go_to_left < -> checks < <\n";

  out << "checks A -> go_to_end A >\n";
  out << "checks B -> go_to_end B >\n";
  out << "checks 0 -> go_left 0 <\n";
  out << "checks 1 -> go_left 1 <\n";

  out << "go_left 0 -> go_left 0 <\n";
  out << "go_left 1 -> go_left 1 <\n";
  out << "go_left A -> s A >\n";
  out << "go_left B -> s B >\n";

  out << "go_to_end 0 -> ac _ ^\n";
  out << "go_to_end 1 -> ac _ ^\n";
  out << "go_to_end _ -> endof _ <\n";
  out << "go_to_end E -> go_to_end E >\n";
  out << "go_to_end M -> go_to_end M >\n";
  out << "go_to_end L -> go_to_end L >\n";
  out << "go_to_end < -> go_to_end < >\n";

  out << "endof E -> endof E <\n";
  out << "endof M -> endof M <\n";
  out << "endof L -> endof L <\n";
  out << "endof < -> lul < >\n";

  out << "lul M -> ac _ ^\n";
  out << "lul E -> lul E >\n";
  out << "lul L -> rj _ ^\n";

}


/*
  out << "check2 1 -> skip_to_left_B B <\n";
  out << "check2 0 -> skip_to_left_A A <\n";
  out << "check2 < -> rj < ^\n";

  out << "skip_to_left_A 0 -> skip_to_left_A 0 <\n";
  out << "skip_to_left_A 1 -> skip_to_left_A 1 <\n";
  out << "skip_to_left_A < -> checkA < <\n";

  out << "skip_to_left_B 0 -> skip_to_left_B 0 <\n";
  out << "skip_to_left_B 1 -> skip_to_left_B 1 <\n";
  out << "skip_to_left_B < -> checkB < <\n";

  out << "checkA A -> checkA A <\n";
  out << "checkA B -> checkA B <\n";
  out << "checkA 1 -> check_rj B ^\n";
  out << "checkA 0 -> skip_to_less A >\n";
  out << "checkA _ -> ac _ ^\n";

  out << "checkB A -> checkB A <\n";
  out << "checkB B -> checkB B <\n";
  out << "checkB 1 -> skip_to_less B >\n";
  out << "checkB 0 -> check_ac A ^\n";
  out << "checkB _ -> ac _ ^\n";

  out << "skip_to_less A -> skip_to_less A >\n";
  out << "skip_to_less B -> skip_to_less B >\n";
  out << "skip_to_less < -> skip_to_right < >\n";

  out << "skip_to_right 1 -> skip_to_right 1 >\n";
  out << "skip_to_right 0 -> skip_to_right 0 >\n";
  out << "skip_to_right B -> check2 B <\n";
  out << "skip_to_right A -> check2 A <\n";

  out << "check_rj A -> check_rj A >\n";
  out << "check_rj B -> check_rj B >\n";
  out << "check_rj < -> rej < >\n";

  out << "rej 1 -> rej 1 >\n";
  out << "rej 0 -> rej 0 >\n";
  out << "rej A -> rejec A <\n";
  out << "rej B -> rejec B <\n";

  out << "rejec < -> rj < ^\n";
  out << "rejec 1 -> go_to B <\n";
  out << "rejec 0 -> go_to A <\n";

  out << "go_to <"*/
