#include "../exercise.h"
#include <array>
#include <cstring>

// READ: std::array <https://zh.cppreference.com/w/cpp/container/array>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::array<int, 5> arr{{1, 2, 3, 4, 5}};
        ASSERT(arr.size() == 5, "Fill in the correct value.");                    // 数组元素个数
        ASSERT(sizeof(arr) == 20, "Fill in the correct value.");                 // 5个int，每个4字节，共20字节
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(arr.data(), ans, 20) == 0, "Fill in the correct values."); // data()返回底层数组指针，20字节比较
    }
    {
        std::array<double, 8> arr;  // 默认初始化（未初始化）
        ASSERT(arr.size() == 8, "Fill in the correct value.");                   // 数组元素个数
        ASSERT(sizeof(arr) == 64, "Fill in the correct value.");                // 8个double，每个8字节，共64字节
    }
    {
        std::array<char, 21> arr{"Hello, InfiniTensor!"};
        ASSERT(arr.size() == 21, "Fill in the correct value.");                 // 数组大小固定为21
        ASSERT(sizeof(arr) == 21, "Fill in the correct value.");               // 21个char，每个1字节，共21字节
        ASSERT(std::strcmp(arr.data(), "Hello, InfiniTensor!") == 0, "Fill in the correct value."); // data()返回C风格字符串指针
    }
    return 0;
}