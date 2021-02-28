#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
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
  Node* head = nullptr;
  Node* cur = nullptr;
  if(!left_list){
    head = right_list;
    return head;
  }
  else if(!right_list){
    head = left_list;
    return head;
  }
  if(left_list->data < right_list->data){
    head = left_list;
    left_list = left_list->next;
  }
  else{
    head = right_list;
    right_list = right_list->next;
  }
  cur = head;
  while(left_list && right_list){
    if(left_list->data < right_list->data){
      cur->next = left_list;
      cur = cur->next;
      left_list = left_list->next;
    }
    else{
      cur->next = right_list;
      cur = cur->next;
      right_list = right_list->next; 
    }
  }
  if(left_list){
    cur->next = left_list;
  }
  if(right_list){
    cur->next = right_list;
  }
  return head;
}

TEST(MergeList, test1){
  vector<int> vec1{1,4,5};
  vector<int> vec2{1,10,13,24};
  Node* list1 = nullptr;
  Node* list2 = nullptr;
  Node* merged_list = nullptr;
  merged_list = merge_2_list(list1, list2);
  EXPECT_EQ(merged_list, nullptr);
  list1 = initialize_list_from_vector(vec1);
  merged_list = merge_2_list(list1, list2);
  Node* tmp_list = merged_list;
  for(int i = 0; i < 3; ++i){
    EXPECT_EQ(tmp_list->data, vec1[i]);
    tmp_list = tmp_list->next;
  }
  EXPECT_EQ(tmp_list, nullptr);
  list2 = initialize_list_from_vector(vec2);
  merged_list = merge_2_list(list1, list2);
  vector<int> merged_vec = vec1;
  for(unsigned int i = 0; i < vec2.size(); ++i){
    merged_vec.push_back(vec2[i]);
  }
  std::sort(merged_vec.begin(), merged_vec.end());
  tmp_list = merged_list;
  for(unsigned int i = 0; i < merged_vec.size(); ++i){
    EXPECT_EQ(tmp_list->data, merged_vec[i]);
    tmp_list = tmp_list->next;
  }
  EXPECT_EQ(tmp_list, nullptr);
  free_list(&merged_list);
  EXPECT_EQ(merged_list, nullptr);

}

struct NodeCompare : public std::binary_function<Node*, Node*, bool>{
  bool operator()(const Node* left, const Node* right) const{
    return left->data > right->data; 
  }
};

Node* merge_n_list(vector<Node*> list_vec){
  std::priority_queue<Node*, vector<Node*>, NodeCompare> node_queue;
  for(auto item : list_vec){
    if(item){
      node_queue.push(item);
    }
  }
  Node* head = nullptr;
  Node* cur = nullptr;
  if(!node_queue.empty()){
    head = node_queue.top();
    node_queue.pop();
    cur = head;
    if(cur->next){
      node_queue.push(cur->next);
    }
  }
  while(!node_queue.empty()){
    cur->next = node_queue.top();
    node_queue.pop();
    cur = cur->next;
    if(cur->next){
      node_queue.push(cur->next);
    }
  }
  return head;
}

vector<int> merge_n_vec(vector<vector<int>>& matrix){
  vector<int> ret_vec;
  for(unsigned int i = 0; i < matrix.size(); ++i){
    for(auto item : matrix[i]){
      ret_vec.push_back(item);
    }
  }
  std::sort(ret_vec.begin(), ret_vec.end());
  return ret_vec;
}

TEST(MergeNList, test1){
  vector<Node*> vec_list(5, nullptr);
  Node* merged_list = merge_n_list(vec_list);
  EXPECT_EQ(merged_list, nullptr);
  vector<vector<int>> matrix;
  vector<int> vec1{1,2,4,5};
  vector<int> vec2{2,3,4,5,5,5,5,6,7,8};
  vector<int> vec3{3,4,5,6};
  Node* list1 = initialize_list_from_vector(vec1);
  Node* list2 = initialize_list_from_vector(vec2);
  Node* list3 = initialize_list_from_vector(vec3);
  matrix.push_back(vec1);
  matrix.push_back(vec2);
  matrix.push_back(vec3);
  vec_list[0] = list1;
  vec_list[1] = list2;
  vec_list[2] = list3;
  merged_list = merge_n_list(vec_list);
  auto merge_vec = merge_n_vec(matrix);
  Node* tmp_list = merged_list;
  for(unsigned int i = 0; i < merge_vec.size(); ++i){
    EXPECT_EQ(tmp_list->data, merge_vec[i]);
    tmp_list = tmp_list->next;
  }
  EXPECT_EQ(tmp_list, nullptr);
}


