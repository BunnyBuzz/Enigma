

void __stdcall _start()
{
    int32_t v_1;
    v_1 = 00000000.plt_pic32.fib(10);
    00000000.plt_pic32.prctl();
    00000000.plt_pic32.syscall(v_1);
    00000000.plt_pic32.ptrace(v_1);
    00000000.plt_pic32.scanf();
    00000000.plt_pic32.malloc(v_1);
    00000000.plt_pic32.free(v_1);
    00000000.plt_pic32.setvbuf();
    00000000.plt_pic32.write();
    00000000.plt_pic32.getenv();
    00000000.plt_pic32.prctl(*_g_data + v_1);
    return;
}

void __stdcall 00000000.plt_pic32.fib()
{
                    
                    
    (*ptr_0x48598)();
    return;
}

void __stdcall 00000000.plt_pic32.prctl()
{
                    
                    
    (*ptr_0x4859c)();
    return;
}

void __stdcall 00000000.plt_pic32.syscall()
{
                    
                    
    (*ptr_0x485a0)();
    return;
}

void __stdcall 00000000.plt_pic32.ptrace()
{
                    
                    
    (*ptr_0x485a4)();
    return;
}

void __stdcall 00000000.plt_pic32.scanf()
{
                    
                    
    (*ptr_0x485a8)();
    return;
}

void __stdcall 00000000.plt_pic32.malloc()
{
                    
                    
    (*ptr_0x485ac)();
    return;
}

void __stdcall 00000000.plt_pic32.free()
{
                    
                    
    (*ptr_0x485b0)();
    return;
}

void __stdcall 00000000.plt_pic32.setvbuf()
{
                    
                    
    (*ptr_0x485b4)();
    return;
}

void __stdcall 00000000.plt_pic32.write()
{
                    
                    
    (*ptr_0x485b8)();
    return;
}

void __stdcall 00000000.plt_pic32.getenv()
{
                    
                    
    (*ptr_0x485bc)();
    return;
}

int32_t __stdcall fib(int32_t param_1)
{
    int32_t v_1;
    int32_t v_2;
    int32_t v_3;
    v_1 = param_1;
    if (0 < param_1) {
        v_1 = 1;
    }
    v_1 = ((param_1 - v_1) + 1U >> 1) + 1;
    v_3 = 0;
    while (v_1 += -1, v_1 != 0) {
        v_2 = 00000000.plt_pic32.fib(param_1 + -1);
        param_1 += -2;
        v_3 += v_2;
    }
    return param_1 + v_3;
}

