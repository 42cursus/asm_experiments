# https://youtrack.jetbrains.com/issue/CPP-7090

set confirm off
set pagination off
set height unlimited
#set verbose on
#set logging on
set trace-commands on
set print inferior-events on

show debug-file-directory
set disassembly-flavor intel
set debug-file-directory /usr/lib/debug
directory ~/git/c/42london/push_swap/src
directory ~/staging/glibc-2.31
directory ~/staging/glibc-2.31/elf
directory ~/staging/glibc-2.31/nptl
directory ~/staging/glibc-2.31/dlfcn
directory ~/staging/glibc-2.31/misc
directory ~/staging/glibc-2.31/csu
directory ~/staging/glibc-2.31/ctype
directory ~/staging/glibc-2.31/stdlib
directory ~/staging/glibc-2.31/sysdeps/x86_64
directory ~/staging/glibc-2.31/sysdeps/x86_64/multiarch
directory ~/git/c/coreutils/src
dir src
set breakpoint pending on
# br _start
# br _dl_start
# br _dl_start_final
# br _dl_start_user
# br _dl_init
# br _init
# br dl-sysdep.c:117
# br dl-sysdep.c:252
# br rtld.c:449
# br dl-init:118
# br check_stdfiles_vtables
br _start
br libc-start.c:308
br libc-start.c:339
br libc-start.c:342
br main
br exit
br _exit
br __GI__exit
br __run_exit_handlers
br __call_tls_dtors
br _dl_fini
br _fini
br __on_exit
