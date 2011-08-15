#ifndef _MONA_ARRAY_
#define _MONA_ARRAY_

#include "sys/types.h"

#define FOREACH(type, iterator, array) \
        if ((array).GetLength() > 0) {type iterator;\
                for (int __##iterator = 0;\
                        __##iterator < (array).GetLength() && (&(iterator = (array)[__##iterator]) || true); __##iterator++)
#ifndef END_FOREACH
#define END_FOREACH }
#endif
/*----------------------------------------------------------------------
    Array
----------------------------------------------------------------------*/
template <class T> class Array
{
  public:
    Array(uint32_t length) : length(length), alloc(true)
    {
        this->array = new T[length];
    }

    Array(T* array, uint32_t length) : array(array), length(length), alloc(false)
    {
    }

    Array(const Array& src) : array(src.array),
                              length(src.length),
                              alloc(src.alloc)
    {
        MONA_ASSERT(false);
    }

    Array& operator=(const Array& src)
    {
        array = src.array;
        length = src.length;
        array = src.alloc;
        return *this;
    }

    virtual ~Array()
    {
        if (this->alloc)
        {
            delete[] this->array;
        }
    }

  public:
    T& operator [](uint32_t index)
    {
#if 1
        if (index >= length)
        {
            g_console->printf("array index outof range %d\n", index);
            panic("array");
        }
#endif
        return this->array[index];
    }

    int GetLength() const
    {
        return this->length;
    }

  private:
    T* array;
    uint32_t length;
    bool alloc;
};

#endif
