## Function Calls in x86

1. When a function is called in the x86 architecture (whether recursive or not), the system performs several steps:

1. Push the Return Address:
     * Before jumping to the function being called, the current address (the point in the program where the call occurred) is saved on the stack. This is called the return address, which allows the program to know where to return to after the function completes.

1. Push Function Parameters:
    * The parameters passed to the function are pushed onto the stack.

1. Push Caller-Saved Registers:
    * Some registers (like eax, ecx, and edx in x86) are caller-saved. This means the caller function is responsible for saving their values on the stack if it needs them later, as the called function is allowed to modify them.

1. Call the Function:
    * The call instruction (e.g., call \<address\>) is executed, which transfers control to the function being called. The program counter jumps to the function’s starting address.

1. Allocate Stack Space for Local Variables:
    * The called function creates space on the stack for its local variables by adjusting the stack pointer (esp), which points to the current top of the stack.

1. Execute Function Body:
    * The function performs its task, potentially calling itself recursively.

1. Return from the Function:
    * When the function finishes, the return instruction (ret) is executed, which pops the return address off the stack and jumps back to that address (resuming execution at the call site).
