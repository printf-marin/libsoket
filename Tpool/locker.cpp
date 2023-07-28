#include"locker.h"

locker::locker()
{
    if(pthread_mutex_init(&m_mutex,NULL)!=0){}
}

locker::~locker()
{
    pthread_mutex_destroy(&m_mutex);
}
bool locker::lock()
{
    return pthread_mutex_lock(&m_mutex) == 0;
}
bool locker::unlock()
{
    return pthread_mutex_unlock(&m_mutex) == 0;
}
pthread_mutex_t* locker::getMutex()
{
    return &(this->m_mutex);
}
// 这段代码是一个简单的互斥锁封装类的实现。互斥锁用于保护临界区资源的访问，防止多个线程同时访问造成数据竞争和不一致的问题。

// 代码中的 `locker` 类拥有一个 `pthread_mutex_t` 类型的成员变量 `m_mutex`，用于表示互斥锁。

// 构造函数 `locker()` 中通过调用 `pthread_mutex_init()` 函数来初始化互斥锁。如果初始化失败，即 `pthread_mutex_init()` 函数返回非零值，那么构造函数中的 `if` 语句块内的代码将不会执行。

// 析构函数 `~locker()` 中调用 `pthread_mutex_destroy()` 函数来销毁互斥锁。

// `lock()` 方法通过调用 `pthread_mutex_lock()` 函数来加锁。如果加锁成功，即 `pthread_mutex_lock()` 函数返回零值，那么该方法返回 `true`，否则返回 `false`。

// `unlock()` 方法通过调用 `pthread_mutex_unlock()` 函数来解锁。如果解锁成功，即 `pthread_mutex_unlock()` 函数返回零值，那么该方法返回 `true`，否则返回 `false`。

// `getMutex()` 方法返回互斥锁的指针，以便其他代码可以直接操作互斥锁。
