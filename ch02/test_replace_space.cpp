#include <string>
#include <vector>
#include <algorithm>
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

struct Node{
  Node(int data_) : 
    data(data_),
    next(nullptr){}
  Node* next;
  int data;
};

Node* initialize_list_from_vector(const vector<int>& vec){
  std::vector<int> my_vec = vec;
  std::sort(my_vec.begin(), my_vec.end());
  Node* head = nullptr;
  Node* cur = nullptr;
  for(unsigned int i = 0; i < my_vec.size(); ++i){
    if(0 == i){
      head = new Node(my_vec[i]);
      cur = head;
    }
    else{
      cur->next = new Node(my_vec[i]);
      cur = cur->next;
    }
  }
  return head;
}

void free_list(Node** list){
  Node* node_list = *list; 
  while(node_list){
    Node* next = node_list->next;
    delete node_list;
    node_list = next;
  }
  *list = nullptr;
}

TEST(MergeList, initAndFree){
  vector<int> vec;
  for(int i = 0; i < 10; ++i){
    vec.push_back(rand() % 1000);
  }   
  Node* list_node = initialize_list_from_vector(vec);
  Node* head = list_node;
  std::sort(vec.begin(), vec.end());
  int i = 0;
  while(list_node){
    EXPECT_EQ(list_node->data, vec[i++]);
    list_node = list_node->next;
  }
  free_list(&head);
  EXPECT_EQ(head, list_node);
}

Node* merge_2_list(Node* left_list, Node* right_list){

}

Node* merge_n_list(vector<Node*> list_vec){

}

