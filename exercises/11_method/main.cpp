#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // TODO: 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        // 当请求的索引i大于已缓存的最大索引时，继续计算
        for (; cached < i; ++cached) {
            // 计算下一个斐波那契数：F(cached+1) = F(cached) + F(cached-1)
            cache[cached + 1] = cache[cached] + cache[cached - 1];
        }
        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化缓存结构体：设置前两个斐波那契数和已缓存的索引
    Fibonacci fib = {{0, 1}, 1};  // cache[0]=0, cache[1]=1, cached=1
    
    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}