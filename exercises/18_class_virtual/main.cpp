#include "../exercise.h"

// READ: 虚函数 <https://zh.cppreference.com/w/cpp/language/virtual>

struct A {
    virtual char virtual_name() const {
        return 'A';
    }
    char direct_name() const {
        return 'A';
    }
};
struct B : public A {
    // READ: override <https://zh.cppreference.com/w/cpp/language/override>
    char virtual_name() const override {
        return 'B';
    }
    char direct_name() const {
        return 'B';
    }
};
struct C : public B {
    // READ: final <https://zh.cppreference.com/w/cpp/language/final>
    char virtual_name() const final {
        return 'C';
    }
    char direct_name() const {
        return 'C';
    }
};
struct D : public C {
    char direct_name() const {
        return 'D';
    }
    // 注意：D无法重写virtual_name()，因为C中声明为final
};

int main(int argc, char **argv) {
    constexpr auto MSG = "Replace '?' with its correct name.";

    A a;
    B b;
    C c;
    D d;

    // 直接对象调用：调用对象实际类型的方法
    ASSERT(a.virtual_name() == 'A', MSG);  // A对象调用A::virtual_name()
    ASSERT(b.virtual_name() == 'B', MSG);  // B对象调用B::virtual_name()
    ASSERT(c.virtual_name() == 'C', MSG);  // C对象调用C::virtual_name()
    ASSERT(d.virtual_name() == 'C', MSG);  // D继承C的virtual_name()，因为C声明为final
    ASSERT(a.direct_name() == 'A', MSG);   // A对象调用A::direct_name()
    ASSERT(b.direct_name() == 'B', MSG);   // B对象调用B::direct_name()
    ASSERT(c.direct_name() == 'C', MSG);   // C对象调用C::direct_name()
    ASSERT(d.direct_name() == 'D', MSG);   // D对象调用D::direct_name()

    A &rab = b;  // A类型引用指向B对象
    B &rbc = c;  // B类型引用指向C对象
    C &rcd = d;  // C类型引用指向D对象

    // 通过引用调用：虚函数根据实际对象类型调用，非虚函数根据引用类型调用
    ASSERT(rab.virtual_name() == 'B', MSG);  // 虚函数：实际对象是B，调用B::virtual_name()
    ASSERT(rbc.virtual_name() == 'C', MSG);  // 虚函数：实际对象是C，调用C::virtual_name()
    ASSERT(rcd.virtual_name() == 'C', MSG);  // 虚函数：实际对象是D，但继承C的virtual_name()
    ASSERT(rab.direct_name() == 'A', MSG);   // 非虚函数：引用类型是A，调用A::direct_name()
    ASSERT(rbc.direct_name() == 'B', MSG);   // 非虚函数：引用类型是B，调用B::direct_name()
    ASSERT(rcd.direct_name() == 'C', MSG);   // 非虚函数：引用类型是C，调用C::direct_name()

    A &rac = c;  // A类型引用指向C对象
    B &rbd = d;  // B类型引用指向D对象

    ASSERT(rac.virtual_name() == 'C', MSG);  // 虚函数：实际对象是C，调用C::virtual_name()
    ASSERT(rbd.virtual_name() == 'C', MSG);  // 虚函数：实际对象是D，继承C的virtual_name()
    ASSERT(rac.direct_name() == 'A', MSG);   // 非虚函数：引用类型是A，调用A::direct_name()
    ASSERT(rbd.direct_name() == 'B', MSG);   // 非虚函数：引用类型是B，调用B::direct_name()

    A &rad = d;  // A类型引用指向D对象

    ASSERT(rad.virtual_name() == 'C', MSG);  // 虚函数：实际对象是D，继承C的virtual_name()
    ASSERT(rad.direct_name() == 'A', MSG);   // 非虚函数：引用类型是A，调用A::direct_name()

    return 0;
}

// READ: 扩展阅读-纯虚、抽象 <https://zh.cppreference.com/w/cpp/language/abstract_class>
// READ: 扩展阅读-虚继承 <https://zh.cppreference.com/w/cpp/language/derived_class>