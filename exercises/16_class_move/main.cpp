#include "../exercise.h"

// READ: 左值右值（概念）<https://learn.microsoft.com/zh-cn/cpp/c-language/l-value-and-r-value-expressions?view=msvc-170>
// READ: 左值右值（细节）<https://zh.cppreference.com/w/cpp/language/value_category>
// READ: 关于移动语义 <https://learn.microsoft.com/zh-cn/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170#move-semantics>
// READ: 如果实现移动构造 <https://learn.microsoft.com/zh-cn/cpp/cpp/move-constructors-and-move-assignment-operators-cpp?view=msvc-170>

// READ: 移动构造函数 <https://zh.cppreference.com/w/cpp/language/move_constructor>
// READ: 移动赋值 <https://zh.cppreference.com/w/cpp/language/move_assignment>
// READ: 运算符重载 <https://zh.cppreference.com/w/cpp/language/operators>

class DynFibonacci {
    size_t *cache;
    int cached;

public:
    // TODO: 实现动态设置容量的构造器
    DynFibonacci(int capacity): cache(new size_t[capacity]), cached(1) {
        // 初始化斐波那契数列的前两个值
        cache[0] = 0;  // F(0) = 0
        cache[1] = 1;  // F(1) = 1
    }

    // TODO: 实现移动构造器
    DynFibonacci(DynFibonacci &&other) noexcept : cache(other.cache), cached(other.cached) {
        // 窃取资源：直接接管other的资源
        other.cache = nullptr;  // 将other置于有效但未指定的状态
        other.cached = 0;
    }

    // TODO: 实现移动赋值
    // NOTICE: ⚠ 注意移动到自身问题 ⚠
    DynFibonacci &operator=(DynFibonacci &&other) noexcept {
        // 检查自赋值：防止移动到自身
        if (this != &other) {
            // 释放当前对象的资源
            delete[] cache;
            
            // 窃取other的资源
            cache = other.cache;
            cached = other.cached;
            
            // 将other置于有效但未指定的状态
            other.cache = nullptr;
            other.cached = 0;
        }
        return *this;
    }

    // TODO: 实现析构器，释放缓存空间
    ~DynFibonacci() {
        delete[] cache;  // 释放动态分配的数组（nullptr是安全的）
    }

    // TODO: 实现正确的缓存优化斐波那契计算
    size_t operator[](int i) {
        // 当请求的索引i大于已缓存的最大索引时，继续计算
        for (; cached < i; ++cached) {
            // 计算下一个斐波那契数：F(cached+1) = F(cached) + F(cached-1)
            cache[cached + 1] = cache[cached] + cache[cached - 1];
        }
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    size_t operator[](int i) const {
        ASSERT(i <= cached, "i out of range");
        return cache[i];
    }

    // NOTICE: 不要修改这个方法
    bool is_alive() const {
        return cache;
    }
};

int main(int argc, char **argv) {
    DynFibonacci fib(12);
    ASSERT(fib[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci const fib_ = std::move(fib);  // 调用移动构造函数
    ASSERT(!fib.is_alive(), "Object moved");   // fib的资源已被移走
    ASSERT(fib_[10] == 55, "fibonacci(10) should be 55");

    DynFibonacci fib0(6);
    DynFibonacci fib1(12);

    fib0 = std::move(fib1);  // 调用移动赋值运算符
    fib0 = std::move(fib0);  // 自赋值测试
    ASSERT(fib0[10] == 55, "fibonacci(10) should be 55");

    return 0;
}