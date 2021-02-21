#include <iostream>
#include <cstddef>
#include <cstring>
#include "gtest/gtest.h"
// 自己实现一个string类

class MyString{
public:
    MyString(char* data = nullptr);
    MyString(const MyString& str);
    MyString& operator=(const MyString& str);
    ~MyString();
    void print(){
	std::cout << data_ << std::endl;
    }
private:
    char* data_;
    int size_;
};

MyString::MyString(char* data){
    if(data == nullptr){
	// 如果是空指针的话则要进行如下处理
	size_ = 1;
	data_ = new char[1];
	data_[0] = '\0';
	return;
    }
    // 用strlen这个函数来记录字符串的长度
    size_ = strlen(data);
    // 这里多分配一个字节的原因是我们调用strcpy拷贝函数是拷贝到'\0'这个位置的
    // 同理我们的strlen函数也是统计到'\0'这个位置
    data_ = new char[size_ + 1];
    strcpy(data_, data);
}

MyString::MyString(const MyString& str){
    size_ = str.size_;
    data_ = new char[size_ + 1];
    strcpy(data_, str.data_);
}

MyString& MyString::operator=(const MyString& str){
    if(this == &str){
	return *this;
    }
    delete [] data_;
    size_ = str.size_;
    data_ = new char[size_ + 1];
    strcpy(data_, str.data_);
    return *this;
}

MyString::~MyString(){
    if(data_){
	delete [] data_;
	data_ = nullptr;
    }
}
