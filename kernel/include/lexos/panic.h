#ifndef H_LEXOS_PANIC
#define H_LEXOS_PANIC
#include "lexos/boot/except.h"
#include "util.h"


__NORETURN
void panic(interrupt_stack_frame_s *stackframe, const char *fmt, ...);


#endif /// #ifndef H_LEXOS_PANIC
