#include "lexos/string.h"


int memcmp(const void *ptr1, const void *ptr2, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (((const uint8_t *)ptr1)[i] != ((const uint8_t *)ptr2)[i])
        {
            return ((const uint8_t *)ptr1)[i] - ((const uint8_t *)ptr2)[i];
        }
    }
    return 0;
}

void *memcpy(void *dst, const void *src, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        ((char *)dst)[i] = ((char *)src)[i];
    }
    return dst;
}
