#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// 构造函数：100个true值
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");  // 在64位Linux系统上通常是40字节
    {
        vec[20] = false;  // 设置第21个元素为false
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");  // !vec[20] 因为现在是false
    }
    {
        vec.push_back(false);  // 添加一个false元素
        ASSERT(vec.size() == 101, "Fill in the correct value.");  // 大小变为101
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");  // !vec[100] 因为刚添加的是false
    }
    {
        auto ref = vec[30];  // 获取第31个元素的引用（实际是proxy对象）
        ASSERT(ref, "Fill in `ref` or `!ref`");  // ref 因为vec[30]初始化为true
        ref = false;  // 通过proxy设置为false
        ASSERT(!ref, "Fill in `ref` or `!ref`");  // !ref 因为现在是false
        // THINK: WHAT and WHY?
        // ref是一个proxy对象，修改ref会同步修改vec[30]
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");  // !vec[30] 因为通过ref修改了
    }
    return 0;
}