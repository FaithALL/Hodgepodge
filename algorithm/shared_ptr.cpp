/**
 * 自实现shared_ptr
 */

#include <cstdio>
#include <cstring>

template<typename T>
class shared_ptr {
public:
    //无参构造函数，默认初始为空指针
    shared_ptr() = default;

    //裸指针转移资源管理权
    explicit shared_ptr(T *ptr) : mPtr(ptr) {
        addRefer();
    }

    //智能指针共享资源
    shared_ptr(const shared_ptr<T> &sharedPtr)
            : mPtr(sharedPtr.mPtr), mRefCount(sharedPtr.mRefCount) {
        addRefer();
    }

    shared_ptr<T> &operator=(const shared_ptr<T> &sharedPtr) {
        //排除自赋值情况
        if (this != &sharedPtr) {
            removeRefer();
            mPtr = sharedPtr.mPtr;
            mRefCount = sharedPtr.mRefCount;
            addRefer();
        }
        return *this;
    }

    ~shared_ptr() {
        removeRefer();
    }

    //解引用
    T &operator*() const {
        return *mPtr;
    }

    //ptr->mem
    //如果ptr是内置指针,等价于(*ptr).mem
    //如果ptr是类对象,等价于(ptr.operator->())->mem
    T *operator->() const {
        return mPtr;
        //相当于return &this->operator*();
    }

    //转换为bool类型的规则
    explicit operator bool() const {
        return mPtr;
    }

private:
    T *mPtr = nullptr;
    int *mRefCount = nullptr;

    void addRefer() {
        //空指针不改变引用计数
        if (!mPtr) return;
        if (mRefCount) {
            ++(*mRefCount);
        } else {
            mRefCount = new int(1);
        }
    }

    void removeRefer() {
        //空指针不改变引用计数
        if (!mPtr) return;
        if (mRefCount) {
            --(*mRefCount);
            if (*mRefCount == 0) {
                delete mRefCount;
                delete mPtr;
                mRefCount = nullptr;
                mPtr = nullptr;
            }
        }
    }
};

class Test {
private:
    char name[20]{};
public:
    explicit Test(const char *str) {
        strcpy(name, str);
        printf("%s constructor\n", name);
    }

    void test() {
        printf("%s test\n", name);
    }

    ~Test() {
        printf("%s destructor\n", name);
    }
};

void print(void *ptr) {
    int *mPtr = *reinterpret_cast<int **>(ptr);
    int *mRefCount = *(reinterpret_cast<int **>(ptr) + 1);
    int count = 0;
    if (mRefCount != nullptr) count = *mRefCount;
    printf("addr: 0x%x count: %d\n", mPtr, count);
}

int main() {
    shared_ptr<Test> ptr1;
    print(&ptr1);

    shared_ptr<Test> ptr2(new Test("test2 "));
    print(&ptr2);

    shared_ptr<Test> ptr3(ptr2);
    print(&ptr3);

    ptr1 = ptr3;
    print(&ptr1);

    ptr1->test();

    if (ptr1) (*ptr3).test();
    return 0;
}
