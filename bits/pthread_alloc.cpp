//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license


#include"pthread_alloc.h"

#include<pthread.h>

#include<cassert>
#include<new>//for std::bad_alloc

namespace stl
{


class Mutex::Impl
{
public:
    Impl()
    {
        pthread_mutex_init(&m_mutex, NULL);
    }

    Impl(const Mutex &);
    Impl& operator = (const Mutex &);

    ~Impl()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    void lock()
    {
        pthread_mutex_lock(&m_mutex);
    }

    void unlock()
    {
        pthread_mutex_unlock(&m_mutex);
    }

private:
    pthread_mutex_t m_mutex;
};



Mutex::Mutex()
    : m_impl(new Mutex::Impl)
{
}


Mutex::~Mutex()
{
    delete m_impl;
}


void Mutex::lock()
{
    m_impl->lock();
}

void Mutex::unlock()
{
    m_impl->unlock();
}


class LockGuard
{
public:
    LockGuard(Mutex &mutex)
        : m_mutex(mutex)
    {
        m_mutex.lock();
    }

    ~LockGuard()
    {
        m_mutex.unlock();
    }

private:
    //uncopyable
    LockGuard(const LockGuard&);
    LockGuard& operator = (const LockGuard&);

private:
    Mutex &m_mutex;
};



//--------------------------------------------------------------------


PthreadAlloc::obj* PthreadAlloc::free_list[PthreadAlloc::FREELIST_NUM] = {
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


Mutex PthreadAlloc::mutex_list[PthreadAlloc::FREELIST_NUM];



//每次向系统申请内存时的个数,以2倍的速度增长至PthreadAlloc::max_factor
size_t PthreadAlloc::factor_list[PthreadAlloc::FREELIST_NUM] = {
  32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32, 32
};


size_t PthreadAlloc::max_factor = 1024;

void* PthreadAlloc::allocate(size_t bytes)
{
    if(bytes == 0 || bytes > MAX_BYTES)
        return NULL;

    bytes = PthreadAlloc::roundUp(bytes);
    size_t index = PthreadAlloc::freelistIndex(bytes);

    LockGuard lock(mutex_list[index]);
    if(free_list[index] == NULL)//该桶没有空闲内存块，需要向系统申请
    {
        PthreadAlloc::allocChunk(index);
    }

    obj *result = free_list[index];
    free_list[index] = free_list[index]->free_list_link;
    result->free_list_link = NULL;//防止用户通过free_list_link得知下一个分配节点

    return result;
}



void* PthreadAlloc::reallocate(void *p, size_t old_size, size_t new_size)
{
    //不假设p指向的内存块中有数据，因此不会进行复制操作
    PthreadAlloc::deallocate(p, old_size);
    return PthreadAlloc::allocate(new_size);
}



void PthreadAlloc::deallocate(void *p, size_t bytes)
{
    if( p == NULL || bytes == 0 || bytes > 128 )
        return ;

    bytes = roundUp(bytes);
    size_t index = freelistIndex(bytes);

    obj *q = reinterpret_cast<obj*>(p);

    LockGuard lock(mutex_list[index]);
    //使用头插法归还内存块
    q->free_list_link = free_list[index];
    free_list[index] = q;
}


void PthreadAlloc::allocChunk(size_t index)//进入本函数之前必须加锁
{
    assert(index < FREELIST_NUM);

    size_t block_size = 8 * (index+1);
    size_t block_nums = factor_list[index];
    size_t alloc_bytes = block_size * block_nums;


    char *p = reinterpret_cast<char*>(::malloc(alloc_bytes));
    if( p == NULL)
        throw std::bad_alloc();

    obj tmp, *q = &tmp;
    for(size_t i = 0; i < block_nums; ++i)//将该块内存划分成一个个的小内存块,并用指针连接起来
    {
        obj* o = reinterpret_cast<obj*>(p + i*block_size);
        q->free_list_link = o;
        q = o;
    }

    q->free_list_link = NULL;
    free_list[index] = tmp.free_list_link;


    if( factor_list[index] < max_factor )
        factor_list[index] <<= 1;
}


}
