#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// TODO: 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 当请求的索引i大于已缓存的最大索引时，继续计算
    for (; cache.cached < i; ++cache.cached) {
        // 计算下一个斐波那契数：F(cached+1) = F(cached) + F(cached-1)
        cache.cache[cache.cached + 1] = cache.cache[cache.cached] + cache.cache[cache.cached - 1];
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // 初始化缓存结构体：设置前两个斐波那契数和已缓存的索引
    // 使用聚合初始化语法初始化结构体
    FibonacciCache fib = {{0, 1}, 1};  // cache[0]=0, cache[1]=1, cached=1
    
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}