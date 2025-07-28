#include "../exercise.h"
#include <cstring>
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    {
        std::vector<int> vec{1, 2, 3, 4, 5};
        ASSERT(vec.size() == 5, "Fill in the correct value.");
        // THINK: `std::vector` 的大小是什么意思？与什么有关？
        // sizeof(vec) 返回vector对象本身的大小，不是存储的元素大小
        // 在64位系统上通常是24字节（指针8字节 + size_t 8字节 + capacity 8字节）
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        int ans[]{1, 2, 3, 4, 5};
        ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
    }
    {
        std::vector<double> vec{1, 2, 3, 4, 5};
        {
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");  // vector对象大小不变
            double ans[]{1, 2, 3, 4, 5};
            ASSERT(std::memcmp(vec.data(), ans, sizeof(ans)) == 0, "Fill in the correct values.");
        }
        {
            vec.push_back(6);  // 添加元素
            ASSERT(vec.size() == 6, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");  // vector对象大小仍不变
            vec.pop_back();    // 移除最后一个元素
            ASSERT(vec.size() == 5, "Fill in the correct value.");
            ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        }
        {
            vec[4] = 6;  // 修改第5个元素
            ASSERT(vec[0] == 1, "Fill in the correct value.");
            ASSERT(vec[1] == 2, "Fill in the correct value.");
            ASSERT(vec[2] == 3, "Fill in the correct value.");
            ASSERT(vec[3] == 4, "Fill in the correct value.");
            ASSERT(vec[4] == 6, "Fill in the correct value.");  // 被修改为6
        }
        {
            // THINK: `std::vector` 插入删除的时间复杂度是什么？
            // insert: O(n) - 需要移动后续元素
            // erase: O(n) - 需要移动后续元素
            vec.insert(vec.begin() + 1, 1.5);  // 在位置1插入1.5
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 3, 4, 6}), "Make this assertion pass.");
            vec.erase(vec.begin() + 3);  // 删除位置3的元素（3）
            ASSERT((vec == std::vector<double>{1, 1.5, 2, 4, 6}), "Make this assertion pass.");
        }
        {
            vec.shrink_to_fit();  // 将capacity缩减到size
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");
            vec.clear();          // 清空所有元素
            ASSERT(vec.empty(), "`vec` is empty now.");
            ASSERT(vec.size() == 0, "Fill in the correct value.");
            ASSERT(vec.capacity() == 5, "Fill in the correct value.");  // clear不改变capacity
        }
    }
    {
        std::vector<char> vec(48, 'z'); // 构造函数：48个'z'字符
        ASSERT(vec[0] == 'z', "Make this assertion pass.");
        ASSERT(vec[47] == 'z', "Make this assertion pass.");
        ASSERT(vec.size() == 48, "Make this assertion pass.");
        ASSERT(sizeof(vec) == 24, "Fill in the correct value.");
        {
            auto capacity = vec.capacity();  // 保存当前容量
            vec.resize(16);  // 调整大小到16
            ASSERT(vec.size() == 16, "Fill in the correct value.");
            ASSERT(vec.capacity() == capacity, "Fill in a correct identifier.");  // capacity不变
        }
        {
            vec.reserve(256);  // 预留容量到256
            ASSERT(vec.size() == 16, "Fill in the correct value.");      // size不变
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");  // capacity增加到256
        }
        {
            vec.push_back('a');
            vec.push_back('b');
            vec.push_back('c');
            vec.push_back('d');
            ASSERT(vec.size() == 20, "Fill in the correct value.");       // 16 + 4 = 20
            ASSERT(vec.capacity() == 256, "Fill in the correct value.");   // capacity不变
            ASSERT(vec[15] == 'z', "Fill in the correct value.");         // 第16个元素仍是'z'
            ASSERT(vec[16] == 'a', "Fill in the correct value.");         // 新添加的元素
            ASSERT(vec[17] == 'b', "Fill in the correct value.");
            ASSERT(vec[18] == 'c', "Fill in the correct value.");
            ASSERT(vec[19] == 'd', "Fill in the correct value.");
        }
    }

    return 0;
}