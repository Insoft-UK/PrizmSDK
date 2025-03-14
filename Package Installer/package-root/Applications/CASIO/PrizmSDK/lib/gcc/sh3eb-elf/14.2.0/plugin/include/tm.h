#ifndef GCC_TM_H
#define GCC_TM_H
#define TARGET_CPU_DEFAULT (SELECT_SH3)
#ifndef LIBC_GLIBC
# define LIBC_GLIBC 1
#endif
#ifndef LIBC_UCLIBC
# define LIBC_UCLIBC 2
#endif
#ifndef LIBC_BIONIC
# define LIBC_BIONIC 3
#endif
#ifndef LIBC_MUSL
# define LIBC_MUSL 4
#endif
#ifndef HEAP_TRAMPOLINES_INIT
# define HEAP_TRAMPOLINES_INIT 0
#endif
#ifndef SH_MULTILIB_CPU_DEFAULT
# define SH_MULTILIB_CPU_DEFAULT "m3"
#endif
#ifndef SUPPORT_SH3
# define SUPPORT_SH3 1
#endif
#ifndef SUPPORT_SH3
# define SUPPORT_SH3 1
#endif
#ifndef DARWIN_AT_RPATH
# define DARWIN_AT_RPATH 1
#endif
#ifdef IN_GCC
# include "options.h"
# include "insn-constants.h"
# include "config/vxworks-dummy.h"
# include "config/sh/sh.h"
# include "config/elfos.h"
# include "config/sh/elf.h"
# include "config/sh/embed-elf.h"
# include "config/newlib-stdint.h"
# include "sysroot-suffix.h"
# include "config/initfini-array.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE && !defined USED_FOR_TARGET
# include "insn-flags.h"
#endif
#if defined IN_GCC && !defined GENERATOR_FILE
# include "insn-modes.h"
#endif
# include "defaults.h"
#endif /* GCC_TM_H */
