#define LOCK_PREFIX    "lock;"  
#define __sync_bool_compare_and_swap(mem, oldval, newval) \
({  __typeof (*mem) ret; \
    __asm __volatile (LOCK_PREFIX "cmpxchgl %2, %1;sete %%al; movzbl %%al,%%eax"  \
        : "=a" (ret), "=m" (*mem)  \
        : "r" (newval), "m" (*mem), "a" (oldval)  \
        : "memory");  \
ret; })
