

void __stdcall
_start(uint64_t param_1, char *param_2, uint64_t param_3, uint64_t param_4)
{
    uint32_t v_1;
    int32_t out_edx;
    char *v_2;
    void *v_3;
    v_1 = fib(10);
    prctl(v_1);
    syscall(v_1);
    v_2 = (char *)(uint64_t)v_1;
    ptrace();
    scanf(v_2);
    malloc((uint64_t)v_1);
    v_3 = (void *)(uint64_t)v_1;
    free(v_3);
    setvbuf(v_3,param_2,out_edx,param_4);
    write();
    getenv();
                    
                    
    (*_prctl)(v_1 + *_g_data);
    return;
}



void __stdcall fib()
{
                    
                    
    (*_fib)();
    return;
}



void __stdcall prctl()
{
                    
                    
    (*_prctl)();
    return;
}



void __stdcall syscall()
{
                    
                    
    (*_syscall)();
    return;
}



void __stdcall ptrace()
{
                    
                    
    (*_ptrace)();
    return;
}



int32_t __stdcall scanf(char *param_1,...)
{
    int32_t v_1;
                    
                    
    v_1 = (*_scanf)();
    return v_1;
}



void * __stdcall malloc(uint64_t param_1)
{
    void *v_1;
                    
                    
    v_1 = (void *)(*_malloc)();
    return v_1;
}



void __stdcall free(void *param_1)
{
                    
                    
    (*_free)();
    return;
}



int32_t __stdcall
setvbuf(void *param_1, char *param_2, int32_t param_3, uint64_t param_4)
{
    int32_t v_1;
                    
                    
    v_1 = (*_setvbuf)();
    return v_1;
}



void __stdcall write()
{
                    
                    
    (*_write)();
    return;
}



void __stdcall getenv()
{
                    
                    
    (*_getenv)();
    return;
}

int32_t __stdcall fib(int32_t param_1)
{
    int32_t v_1;
    int32_t v_2;
    v_2 = 0;
    for (; 1 < param_1; param_1 += -2) {
        v_1 = fib(param_1 + -1);
        v_2 += v_1;
    }
    return param_1 + v_2;
}

void __stdcall func_0x1550()
{
                    
                    
    (*ptr_0x36e8)();
    return;
}

