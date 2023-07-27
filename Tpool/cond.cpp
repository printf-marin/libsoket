// 这段代码是一个条件变量的封装类的实现。条件变量是一种线程同步机制，用于在线程之间传递信号和等待特定条件的发生。
// 该类的构造函数使用pthread_cond_init函数初始化条件变量。该函数接受两个参数，第一个参数是要初始化的条件变量，第二个参数是条件变量的属性，这里传入NULL表示使用默认属性。
// 析构函数使用pthread_cond_destroy函数销毁条件变量。
// wait函数用于等待条件变量的发生。它接受一个互斥锁作为参数，线程在调用该函数时会释放该互斥锁，并在条件变量发生之前一直等待。如果函数返回true，表示等待成功。
// timewait函数与wait函数类似，但是它在等待一段时间后会超时返回。它接受一个互斥锁和一个绝对时间作为参数，线程会在指定的时间内等待条件变量的发生。
// signal函数用于发送一个信号给等待该条件变量的线程。它会唤醒一个等待的线程，使其继续执行。
// broadcast函数用于发送广播信号给等待该条件变量的所有线程。它会唤醒所有等待的线程，使它们继续执行。
// 这个类的作用是封装了条件变量的常用操作，提供了更方便的接口供其他线程使用。
#include"cond.h"

cond::cond()
{
    pthread_cond_init(&m_cond,NULL);
}
cond::~cond()
{
    pthread_cond_destroy(&m_cond);
}
bool cond::wait(pthread_mutex_t *mutex)
{
    return pthread_cond_wait(&m_cond,mutex) == 0;
}
bool cond::timewait(pthread_mutex_t *mutex,struct timespec t)
{
   return  pthread_cond_timedwait(&m_cond,mutex,&t) == 0;
}
bool cond::signal()
{
    return pthread_cond_signal(&m_cond) == 0;
}
bool cond::broadcast()
{
    return pthread_cond_broadcast(&m_cond);
}