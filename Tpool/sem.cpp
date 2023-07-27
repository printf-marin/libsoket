#include"sem.h"
sem::sem(/* args */)
{
    sem_init(&m_sem,0,0);
}
sem::sem(int val)
{
    sem_init(&m_sem,0,val);
}
sem::~sem()
{
    sem_destroy(&m_sem);
}
bool sem::post()
{
    return sem_post(&m_sem) == 0;
}
bool sem::wait()
{
    return sem_wait(&m_sem) == 0;
}
// 这段代码是一个简单的信号量（semaphore）封装类的实现。信号量是一种用于进程间同步和互斥的机制。

// 代码中定义了一个名为sem的类，包含了构造函数、析构函数以及两个成员函数post和wait。

// 构造函数sem::sem()是一个无参构造函数，用于初始化信号量。在这里使用了sem_init函数来初始化一个名为m_sem的信号量，初始值为0。

// 构造函数sem::sem(int val)是一个有参构造函数，用于初始化信号量并指定初始值。在这里使用了sem_init函数来初始化一个名为m_sem的信号量，初始值为val。

// 析构函数sem::~sem()用于销毁信号量。在这里使用了sem_destroy函数来销毁m_sem信号量。

// 成员函数bool sem::post()用于对信号量进行V操作（释放资源）。在这里使用了sem_post函数来对m_sem信号量进行V操作，并返回操作结果。

// 成员函数bool sem::wait()用于对信号量进行P操作（申请资源）。在这里使用了sem_wait函数来对m_sem信号量进行P操作，并返回操作结果。