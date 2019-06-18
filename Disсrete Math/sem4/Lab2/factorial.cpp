#include <fstream>

std::ofstream out("out/factorial.out");

int main() {
  // conditions
  out << "start: s\n";
  out << "accept: ac\n";
  out << "reject: rj\n";
  out << "blank: _\n";

  // refactor factorial to useful form
  out << "s 0 -> s 0 >\n";
  out << "s 1 -> s 1 >\n";
  out << "s _ -> go * <\n";

  out << "go 0 -> go 0 <\n";
  out << "go 1 -> go 1 <\n";
  out << "go A -> save 0 >\n";
  out << "go B -> save 1 >\n";
  out << "go * -> save * >\n";
  out << "go _ -> save _ >\n";

  out << "save 1 -> write1 B >\n";
  out << "save 0 -> write0 A >\n";
  out << "save * -> minus_one * >\n";

  out << "write0 0 -> write0 0 >\n";
  out << "write0 1 -> write0 1 >\n";
  out << "write0 * -> write0 * >\n";
  out << "write0 _ -> go_to_left_ 0 <\n";

  out << "write1 0 -> write1 0 >\n";
  out << "write1 1 -> write1 1 >\n";
  out << "write1 * -> write1 * >\n";
  out << "write1 _ -> go_to_left_ 1 <\n";

  out << "go_to_left_ 0 -> go_to_left_ 0 <\n";
  out << "go_to_left_ 1 -> go_to_left_ 1 <\n"; //7
  out << "go_to_left_ * -> go * <\n";

  out << "minus_one 0 -> minus_one 0 >\n"; //6
  out << "minus_one 1 -> minus_one 1 >\n";
  out << "minus_one _ -> minus_here _ <\n";

  out << "minus_here 1 -> s 0 >\n";
  out << "minus_here 0 -> minus_here 1 <\n";
  out << "minus_here * -> end_of_fac * >\n";

  out << "end_of_fac 0 -> end_of_fac 0 >\n";
  out << "end_of_fac 1 -> end_of_fac 1 >\n";
  out << "end_of_fac _ -> delete_first _ <\n";

  out << "delete_first 0 -> delete_first _ <\n";
  out << "delete_first 1 -> delete_first _ <\n";
  out << "delete_first * -> delete_second _ <\n";

  out << "delete_second 0 -> delete_second _ <\n";
  out << "delete_second 1 -> delete_second _ <\n";
  out << "delete_second * -> delete_third _ <\n";

  out << "delete_third 0 -> delete_third _ <\n";
  out << "delete_third 1 -> delete_third _ <\n";
  out << "delete_third * -> go_to_multiply _ <\n";
  out << "delete_third _ -> ac 1 ^\n";

  //go to multiply "
  out << "go_to_multiply 0 -> go_to_multiply 0 <\n";
  out << "go_to_multiply 1 -> go_to_multiply 1 <\n";
  out << "go_to_multiply * -> go_to_multiply x <\n";
  out << "go_to_multiply _ -> put_mul _ >\n";

  out << "put_mul 0 -> put_mul 0 >\n";
  out << "put_mul 1 -> put_mul 1 >\n";
  out << "put_mul x -> s_ * >\n";
  out << "put_mul _ -> on_ended_lul _ < \n";

  out << "on_ended_lul 0 -> on_ended_lul 0 <\n";
  out << "on_ended_lul 1 -> on_ended_lul 1 <\n";
  out << "on_ended_lul _ -> ac _ >\n";

  out << "s_ 0 -> s_ 0 >\n";
  out << "s_ 1 -> s_ 1 >\n";
  out << "s_ * -> s_ * >\n";
  out << "s_ + -> s_ + >\n";
  out << "s_ x -> go_ x <\n";
  out << "s_ _ -> go_ _ <\n";

  out << "go_ 0 -> go_ 1 <\n";
  out << "go_ 1 -> go_to_first_number_ 0 <\n";
  out << "go_ * -> delete * >\n";

  out << "go_to_first_number_ 0 -> go_to_first_number_ 0 <\n";
  out << "go_to_first_number_ 1 -> go_to_first_number_ 1 <\n";
  out << "go_to_first_number_ * -> go_to_first_number_ * <\n";
  out << "go_to_first_number_ + -> read_ + >\n";
  out << "go_to_first_number_ _ -> read_ + >\n";

  out << "read_ 0 -> read_ 0 >\n";//19
  out << "read_ 1 -> read_ 1 >\n";
  out << "read_ A -> new_ 0 <\n";
  out << "read_ B -> new_ 1 <\n";
  out << "read_ * -> new_ * <\n";

  out << "new_ 0 -> write0_ A <\n";
  out << "new_ 1 -> write1_ B <\n";
  out << "new_ + -> minus + <\n"; //s_

  out << "write0_ 0 -> write0_ 0 <\n";
  out << "write0_ 1 -> write0_ 1 <\n";
  out << "write0_ + -> write0_ + <\n";//21
  out << "write0_ x -> skip_plus_ 0 >\n";
  out << "write0_ _ -> skip_plus_ 0 >\n";

  out << "write1_ 0 -> write1_ 0 <\n";
  out << "write1_ 1 -> write1_ 1 <\n";//22
  out << "write1_ + -> write1_ + <\n";
  out << "write1_ x -> skip_plus_ 1 >\n";
  out << "write1_ _ -> skip_plus_ 1 >\n";

  out << "skip_plus_ 0 -> skip_plus_ 0 >\n";
  out << "skip_plus_ 1 -> skip_plus_ 1 >\n";//24
  out << "skip_plus_ + -> read_ + >\n";

  out << "minus 0 -> minus 1 <\n";
  out << "minus 1 -> go_to_left 0 <\n"; // 23
  out << "minus = -> clear = >\n";

  out << "clear 0 -> clear x >\n";//26
  out << "clear 1 -> clear x >\n";
  out << "clear + -> s_ + >\n";

  out << "go_to_left 0 -> go_to_left 0 <\n";//25
  out << "go_to_left 1 -> go_to_left 1 <\n";
  out << "go_to_left _ -> plus = <\n";
  out << "go_to_left = -> plus = <\n";

  out << "plus _ -> go_to_right 1 >\n";//27
  out << "plus 0 -> go_to_right 1 >\n";
  out << "plus 1 -> plus 0 <\n";

  out << "go_to_right = -> go_to_right = >\n";
  out << "go_to_right 0 -> go_to_right 0 >\n";
  out << "go_to_right 1 -> go_to_right 1 >\n";
  out << "go_to_right + -> minus + <\n";

  out << "delete 0 -> delete 0 >\n";
  out << "delete 1 -> delete 1 >\n"; //18
  out << "delete x -> q1 * <\n";
  out << "delete _ -> acc _ <\n";

  out << "q1 0 -> q1 y <\n";
  out << "q1 1 -> q1 y <\n";//29
  out << "q1 * -> q1 y <\n";
  out << "q1 x -> q1 y <\n";
  out << "q1 + -> move_number y <\n";

  out << "move_number 0 -> move0_ y >\n";
  out << "move_number 1 -> move1_ y >\n";
  out << "move_number x -> move_number y <\n";
  out << "move_number = -> move_number y <\n";//31

  out << "move0_ y -> move0_ y >\n";
  out << "move0_ 0 -> wm0_ 0 <\n"; //32
  out << "move0_ 1 -> wm0_ 1 <\n";
  out << "move0_ * -> wm0_ * <\n";

  out << "move1_ y -> move1_ y >\n";
  out << "move1_ 0 -> wm1_ 0 <\n";
  out << "move1_ 1 -> wm1_ 1 <\n";
  out << "move1_ * -> wm1_ * <\n";//33

  out << "wm0_ y -> skip_spaces 0 <\n";//34
  out << "wm1_ y -> skip_spaces 1 <\n";//35

  out << "skip_spaces y -> skip_spaces y <\n";
  out << "skip_spaces 0 -> move_number 0 ^\n";
  out << "skip_spaces 1 -> move_number 1 ^\n";
  out << "skip_spaces _ -> skip_spaces2 _ >\n";

  out << "skip_spaces2 y -> skip_spaces2 _ >\n";
  out << "skip_spaces2 0 -> s_ 0 >\n";
  out << "skip_spaces2 1 -> s_ 1 >\n";

  out << "acc 0 -> acc _ <\n";
  out << "acc 1 -> acc _ <\n";
  out << "acc * -> acc _ <\n";
  out << "acc + -> acc _ <\n"; // 30
  out << "acc = -> not_zero _ <\n";
  out << "acc x -> acc _ <\n";

  out << "not_zero 0 -> not_zero 0 <\n";
  out << "not_zero 1 -> not_zero 1 <\n";
  out << "not_zero _ -> ac _ >\n";




}
