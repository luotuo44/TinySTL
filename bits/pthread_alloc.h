//Author: luotuo44@gmail.com
//Use of this source code is governed by a BSD-style license

#ifndef PTHREAD_ALLOC_H
#define PTHREAD_ALLOC_H

#include<cstddef>

namespace stl
{

class Mutex
{
public:
    Mutex();
    ~Mutex();

    void lock();
    void unlock();

private:
    //uncopyable
    Mutex(const Mutex&);
    Mutex& operator = (const Mutex&);

private:
    class Impl;
    Impl *m_impl;
};

class PthreadAlloc
{
private:
    enum { ALIGN = 8};//可以分配的最小内存块，以及不同内存块之间的公差
    enum { BIT_NUM_OF_ALIGN = 3 };//用于右移
    enum { MAX_BYTES = 128 };//可以分配的最大内存块
    enum { FREELIST_NUM = MAX_BYTES/ALIGN };//不同尺寸内存块的数量

public:
    static size_t roundUp(size_t bytes);//将bytes提升到ALIGN的倍数

    static void* allocate(size_t bytes);
    static void deallocate(void *p, size_t bytes);
    static void* reallocate(void *p, size_t old_size, size_t new_size);

private:
    static size_t freelistIndex(size_t bytes);//获取对应的桶
    static void allocChunk(size_t index);

private:
    struct obj
    {
        struct obj *free_list_link;
    };

    static obj* free_list[FREELIST_NUM];//空闲内存桶list
    static Mutex mutex_list[FREELIST_NUM];//每一个内存块对应有一个锁
    //当某个桶没有空闲内存时，一次性向系统申请内存块的个数
    static size_t factor_list[FREELIST_NUM];
    static size_t max_factor;//最大可以申请内存块的个数
};


inline size_t PthreadAlloc::roundUp(size_t bytes)
{
    size_t tmp = (bytes + ALIGN -1) & (~(ALIGN -1));
    tmp *= 1;
    return tmp;
}


//bytes 必须是ALIGN的倍数
inline size_t PthreadAlloc::freelistIndex(size_t bytes)
{
    return (bytes-1)>>BIT_NUM_OF_ALIGN;// (n-1)/ALIGN
}

}

#endif // PTHREAD_ALLOC_H

