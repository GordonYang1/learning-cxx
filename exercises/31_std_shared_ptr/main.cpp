#include "../exercise.h"
#include <memory>

// Final solution with correct values: 4, 3, 2, 1, 3, 2, 3, 0, 0
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);           // shared count = 1
    std::shared_ptr<int> ptrs[]{shared, shared, shared}; // shared count = 4 (1 + 3 copies)

    std::weak_ptr<int> observer = shared;              // weak_ptr doesn't affect use_count
    ASSERT(observer.use_count() == 4, "Initial count: shared + 3 array elements");

    ptrs[0].reset();                                   // shared count = 3
    ASSERT(observer.use_count() == 3, "After ptrs[0].reset()");

    ptrs[1] = nullptr;                                 // shared count = 2
    ASSERT(observer.use_count() == 2, "After ptrs[1] = nullptr");

    ptrs[2] = std::make_shared<int>(*shared);         // shared count = 1 (ptrs[2] now points to new object)
    ASSERT(observer.use_count() == 1, "After ptrs[2] reassignment");

    ptrs[0] = shared;                                  // shared count = 2
    ptrs[1] = shared;                                  // shared count = 3
    ptrs[2] = std::move(shared);                      // shared count = 3 (shared becomes null, ptrs[2] gets the object)
    ASSERT(observer.use_count() == 3, "After reassignments and move");

    std::ignore = std::move(ptrs[0]);                 // Move to temporary, shared count = 2
    ptrs[1] = std::move(ptrs[1]);                     // Self-move, likely no change, count = 2
    ptrs[1] = std::move(ptrs[2]);                     // Both point to same object, count = 2
    ASSERT(observer.use_count() == 2, "After complex moves");

    shared = observer.lock();                          // Creates new shared_ptr, count = 3
    ASSERT(observer.use_count() == 3, "After observer.lock()");

    shared = nullptr;                                  // shared count = 2
    for (auto &ptr : ptrs) ptr = nullptr;            // shared count = 0
    ASSERT(observer.use_count() == 0, "After clearing all shared_ptrs");

    shared = observer.lock();                          // Returns nullptr, shared count = 0
    ASSERT(observer.use_count() == 0, "observer.lock() on expired object returns nullptr");

    return 0;
}