#include <string>
#include "gtest/gtest.h"

using namespace std;

void replace_string_space(string& str){
  int num = 0;
  for(unsigned int i = 0; i < str.size(); ++i){
    if(' ' == str[i]){
      ++num;
    }
  }
  int size = str.size();
  str.resize(str.size() + 2 * num);
  int right_pos = size + 2 * num - 1;
  int left_pos = size - 1;
  while(right_pos > left_pos){
    if(str[left_pos] != ' '){
      str[right_pos--] = str[left_pos--];
    }
    else{
      str[right_pos--] = '0';
      str[right_pos--] = '2';
      str[right_pos--] = '%';
      --left_pos;
    }
  }
} 


TEST(replaceStringSpace, test){
  string case1 = "hello";
  replace_string_space(case1);
  EXPECT_EQ("hello", case1);
  string case2 = " hello";
  replace_string_space(case2);
  EXPECT_EQ("%20hello", case2);
  string case3 = "hello ";
  replace_string_space(case3);
  EXPECT_EQ("hello%20", case3);
  string case4 = "";
  replace_string_space(case4);
  EXPECT_EQ("", case4);
  string case5 = " he  llo  ";
  replace_string_space(case5);
  EXPECT_EQ("%20he%20%20llo%20%20", case5);
}


