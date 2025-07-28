#include "../exercise.h"

// 修改：去掉 constexpr 关键字，使函数可以在运行时执行深度递归
unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main(int argc, char **argv) {
    // 修正：去掉constexpr，因为函数不再是constexpr的
    auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // 现在可以编译运行了（虽然运行时间会很长）
    constexpr auto ANS_N = 30;  // 这个constexpr是可以的，因为90是编译时常量
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}