#include <cstdio>
#include <vector>
#include <cstdlib>
#include "gtest/gtest.h"
using namespace std;
// 如何构造一个二维数组，使得每一行都是从左到右都是递增的，然后从
// 上到下都是递增的

vector<int> get_matrix(int n){
  // 用一个一维vector来代表二维数组
  srand(100);
  vector<int> ret_vec(n * n);
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      int pos = i * n + j;
      int up_pos = -1;
      int left_pos = -1;
      if(i > 0){
        up_pos = (i - 1) * n + j;
      }
      if (j > 0){
        left_pos = pos - 1;
      }
      int up_value = up_pos != -1 ? ret_vec[up_pos] : 0;
      int left_value = left_pos != -1 ? ret_vec[left_pos] : 0;
      while(1){
        int data = rand();
        if(data >= up_value && data >= left_value){
          ret_vec[pos] = data;
          break;
        }
      }
    }
  } 
  return ret_vec;
}

void show_matrix(vector<int>& vec, int n){
  for(int i = 0; i < n; ++i){
    for(int j = 0; j < n; ++j){
      printf("%d ", vec[i * n + j]);
    }
    printf("\n");
  }
}

bool find_element(const vector<int>& vec, const int n, int data){
  int row = 0;
  int col = n - 1;
  bool flag = false;
  while(row < n && col >= 0){
    if(data > vec[row * n + col]){
      // we will find next row
      ++row;  
    }
    else if(data < vec[row * n + col]){
      --col;
    }
    else{
      flag = true;
      break;
    }
  }
  return flag;
}

bool data_in_matrix(const vector<int>& matrix, const int data){
  bool flag = false;
  for(unsigned int i = 0; i < matrix.size(); ++i){
    if(matrix[i] == data){
      flag = true;
    }
  }
  return flag;
}

TEST(testFindNumFromMatrix, constructMatrix){
  int n = 5;
  vector<int> matrix = get_matrix(n);
  for(int i = 0; i < n; ++i){
    for(int j = 1; j < n; ++j){
      EXPECT_GE(matrix[i * n + j], matrix[i * n + j - 1]);
    }
  }
  for(int j = 1; j < n; ++j){
    for(int i = 0; i < n; ++i){
      EXPECT_GE(matrix[j * n + i], matrix[(j - 1) * n + i]);
    }
  }
  
  for(int i = 0; i < n * n; ++i){
    int data = matrix[rand() % (n * n)];
    EXPECT_TRUE(find_element(matrix, n, data));
  }
  
  for(int i = 0; i < n * n; ++i){
    int data = rand() % 1000;
    EXPECT_EQ(data_in_matrix(matrix, data), find_element(matrix, n, data));
  }
}


