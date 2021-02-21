#include <iostream>
#include <vector>
#include "gtest/gtest.h"

bool find_one_duplicate_num(std::vector<int>& input_vec, std::vector<int>& output_vec){
  output_vec.clear();
  bool flag = false;
  if(input_vec.size() == 0){
    std::cout << "input vector is null " << std::endl;
    return false;
  }
  int max_num = input_vec.size() - 1;
  int min_num = 0;
  for(int i = 0; i < static_cast<int>(input_vec.size()); i++){
    if(input_vec[i] < min_num || input_vec[i] > max_num){
      std::cout << "number is too big or too small" << std::endl;
      return false;
    }
  }

  for(int i = 0; i < static_cast<int>(input_vec.size()); i++){
    while(input_vec[i] != i){
      if(input_vec[i] == input_vec[input_vec[i]]){
        // 说明出现了重复
        output_vec.push_back(input_vec[i]);
        flag = true;
        return flag;
      }
      else{
        int tmp = input_vec[i];
        input_vec[i] = input_vec[input_vec[i]];
        input_vec[input_vec[i]] = tmp;
      }
    }
  }
  std::cout << "there is no duplicate number " << std::endl;
  return flag;
}

bool find_all_duplicate_num(std::vector<int>& input_vec, std::vector<int>& output_vec){
  // 借用辅助内存空间来实现
  bool flag = false;
  output_vec.clear();
  if(input_vec.size() == 0){
    std::cout << "input vector is null " << std::endl;
    return false;
  }
  std::vector<int> vec(input_vec.size(), -1);
  int max_num = input_vec.size() - 1;
  int min_num = 0;
  for(int i = 0; i < static_cast<int>(input_vec.size()); i++){
    if(input_vec[i] < min_num || input_vec[i] > max_num){
      std::cout << "number is too big or too small " << std::endl;
      return false;

    }
    if(vec[input_vec[i]] == input_vec[i]){
      flag = true;
      output_vec.push_back(input_vec[i]);
    }
    else{
      vec[input_vec[i]] = input_vec[i];
    }
  }
  if(!flag){
    std::cout << "there is no duplicate number in input vector " << std::endl;
  }
  return flag;

}

TEST(testDuplicate, test1){
  std::vector<int> input_vec{0,1,2,3,4};
  std::vector<int> output_vec;
  if(find_one_duplicate_num(input_vec, output_vec)){
    for(auto item : output_vec){
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
}

TEST(testDuplicate, test2){
  std::vector<int> input_vec{1,2,3,4, 4, 3, 2, 1, 10};
  std::vector<int> output_vec;
  if(find_all_duplicate_num(input_vec, output_vec)){
    for(auto item : output_vec){
      std::cout << item << " ";
    }
    std::cout << std::endl;
  }
}

