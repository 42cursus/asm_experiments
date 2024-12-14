
### To start with:
* [CPU registers](https://datacadamia.com/computer/cpu/register/general)
* [Segmentation](https://datacadamia.com/computer/memory/segment/segment)
* 
* [main_function](https://en.cppreference.com/w/c/language/main_function)
* [startup](https://www.gnu.org/software/hurd/glibc/startup.html)
* [__libc_start_main](https://refspecs.linuxbase.org/LSB_3.1.1/LSB-Core-generic/LSB-Core-generic/baselib---libc-start-main-.html)

### How programs get run: ELF binaries
* https://lwn.net/Articles/631631/

### Understanding Frame Pointers:

* https://hackmd.io/@paolieri/x86_64
* https://wiki.osdev.org/System_V_ABI#x86-64
* https://people.cs.rutgers.edu/~pxk/419/notes/frames.html
* https://eli.thegreenplace.net/2011/09/06/stack-frame-layout-on-x86-64/
* https://insecure.org/stf/smashstack.html

#### Example representation:

    High Address
    +------------------+
    |  Parameter 2     |   <- rbp + 24 (0x18)
    +------------------+
    |  Parameter 1     |   <- rbp + 16 ()
    +------------------+
    |  Return Address  |   <- rbp + 8
    +------------------+
    |  Saved rbp       |   <- rbp
    +------------------+
    |  First Local     |   <- rbp - 8
    +------------------+
    |  Second Local    |   <- rbp - 16 ()
    +------------------+
    Low Address

### How to use assembly in a c code

* [https://gcc.gnu.org/onlinedocs/gcc/Constraints.html](https://gcc.gnu.org/onlinedocs/gcc/Constraints.html)
* [https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html](https://gcc.gnu.org/onlinedocs/gcc/Simple-Constraints.html)
* [https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html](https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html)
* [https://gcc.gnu.org/onlinedocs/gcc/Modifiers.html](https://gcc.gnu.org/onlinedocs/gcc/Modifiers.html)
* [https://gcc.gnu.org/onlinedocs/gcc/C-Extensions.html](https://gcc.gnu.org/onlinedocs/gcc/C-Extensions.html)
