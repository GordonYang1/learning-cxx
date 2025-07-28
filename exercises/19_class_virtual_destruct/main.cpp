#include "../exercise.h"

// READ: 静态字段 <https://zh.cppreference.com/w/cpp/language/static>
// READ: 虚析构函数 <https://zh.cppreference.com/w/cpp/language/destructor>

struct A {
    // 静态成员变量声明（类内初始化）
    static int num_a;

    A() {
        ++num_a;
    }
    // 添加虚析构函数，确保通过基类指针删除派生类对象时正确调用派生类析构函数
    virtual ~A() {
        --num_a;
    }

    virtual char name() const {
        return 'A';
    }
};

struct B final : public A {
    // 静态成员变量声明（类内初始化）
    static int num_b;

    B() {
        ++num_b;
    }
    ~B() override {  // 重写虚析构函数
        --num_b;
    }

    char name() const final {
        return 'B';
    }
};

// 静态成员变量定义（类外初始化）
int A::num_a = 0;
int B::num_b = 0;

int main(int argc, char **argv) {
    auto a = new A;  // 创建A对象，A::num_a = 1
    auto b = new B;  // 创建B对象，A::num_a = 2（B继承A），B::num_b = 1
    ASSERT(A::num_a == 2, "Fill in the correct value for A::num_a");  // A和B各有一个A部分
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");  // 只有一个B对象
    ASSERT(a->name() == 'A', "Fill in the correct value for a->name()");  // A对象调用A::name()
    ASSERT(b->name() == 'B', "Fill in the correct value for b->name()");  // B对象调用B::name()

    delete a;  // 销毁A对象，A::num_a = 1
    delete b;  // 销毁B对象，先调用~B()，再调用~A()，A::num_a = 0，B::num_b = 0
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    A *ab = new B;// 派生类指针可以随意转换为基类指针
    // 创建B对象：先调用A构造函数，再调用B构造函数
    ASSERT(A::num_a == 1, "Fill in the correct value for A::num_a");  // B对象包含A部分
    ASSERT(B::num_b == 1, "Fill in the correct value for B::num_b");  // 一个B对象
    ASSERT(ab->name() == 'B', "Fill in the correct value for ab->name()");  // 虚函数，调用B::name()

    // 基类指针转换为派生类引用需要强制类型转换
    B &bb = static_cast<B&>(*ab);
    ASSERT(bb.name() == 'B', "Fill in the correct value for bb->name()");  // B对象调用B::name()

    // ---- 以下代码不要修改，通过改正类定义解决编译问题 ----
    delete ab;// 通过指针可以删除指向的对象，即使是多态对象
    // 有了虚析构函数，会正确调用B的析构函数，然后调用A的析构函数
    ASSERT(A::num_a == 0, "Every A was destroyed");
    ASSERT(B::num_b == 0, "Every B was destroyed");

    return 0;
}