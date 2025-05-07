#pragma once

#define ANSWER_00 <functional>

#define ANSWER_10 std::function
#define ANSWER_11 bool
#define ANSWER_12 T&
#define ANSWER_13 T
#define ANSWER_14

#define ANSWER_20 [&value](int x) { return x < value; }
#define ANSWER_21 [](std::string& string) { string = string + " " + string; }
#define ANSWER_22 []() {  static unsigned int i = 0; return i++;  }
