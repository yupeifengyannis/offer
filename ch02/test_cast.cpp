#include <iostream>
#include <memory>
// const_cast的用法
// 第一种：将常量指针转换为非常量指针
// 第二种：将常量引用转换为非常量引用
void test_const_cast(){
    int array[4] = {1, 2, 3, 4};
    const int* c_ptr = array;
    // 通过const cast来去除常量
    int* ptr = const_cast<int*>(c_ptr);
    for(int i = 0; i < 4; i++){
	ptr[i] += 1;
    }
    for(auto item : array){
	std::cout << item << " ";
    }
    std::cout << std::endl;
}

// static_cast和C语言风格的转换机制是一样的，
// 但是这种转换会存在一定的问题
class Base{
public:
    Base() {}
    virtual ~Base() {}
    void print(){
	std::cout << "I am Base " << std::endl;
    }
    virtual void foo(){}
};
class Derive : public Base{
public:
    Derive() : Base(){
    }
    ~Derive(){}
     void print(){
    	std::cout << "I am Derive " << std::endl;
    }
    virtual void foo(){}
};
void test_static_cast(){
    // 这是上行转换编译通过并且是安全的
    Derive d;
    Base* base_ptr = static_cast<Base*>(&d);

    // 这是下行转化，编译通过，但是实际上是不安全的
    Base base;
    Derive* d_ptr = static_cast<Derive*>(&base);
}

// 可以保证类的下行转换的安全性
void test_dynamic_cast(){
    // 这里是派生类向父类转换，编译是安全的
    {
	Derive* d_ptr = new Derive();
	d_ptr->print();
	Base* base_ptr = dynamic_cast<Base*>(d_ptr);
	base_ptr->print();
	delete d_ptr;
	// delete base_ptr;
    }
    
    {
	Base* base_ptr = new Base();
	base_ptr->print();
	Derive* d_ptr = dynamic_cast<Derive*>(base_ptr);
	d_ptr->print();
	delete base_ptr;
	// delete d_ptr;
    }
}
// 一般没怎么用到过
void test_reinterpret_cast(){
    int* ptr = new int(233);
    uint64_t ptr_addr = reinterpret_cast<uint64_t>(ptr);
    std::cout << "ptr is " << std::hex << ptr << std::endl;
    std::cout << "ptr addr is " << std::hex << ptr_addr << std::endl;
}


struct A{
    virtual ~A(){}
};
struct B : public A{
    int x_;
    int y_;
};
struct C : public A{
    C(int x, int y, int z) :
	x_(x), y_(y), z_(z){}
    int x_;
    int y_;
    int z_;
    ~C(){
	std::cout << "dtor" << std::endl;
    }
};

void test_class_trans(){
    std::shared_ptr<A> ptr_a (new C(1, 2, 3));
    B* ptr_b = static_cast<B*>(ptr_a.get());
    std::cout << ptr_b->x_ << " " << ptr_b->y_ << std::endl;
}


int main(){
    // test_const_cast();
    // test_static_cast();
    // test_dynamic_cast();
    // test_reinterpret_cast();
    test_class_trans();
}
