

void __stdcall _start()
{
    int32_t v_1;
    v_1 = (*_fib)(10);
    (*_prctl)(v_1);
    (*_syscall)(v_1);
    (*_ptrace)(v_1);
    (*_scanf)();
    (*_malloc)(v_1);
    (*_free)(v_1);
    (*_setvbuf)();
    (*_write)();
    (*_getenv)();
    (*_prctl)(*_g_data + v_1);
    return;
}



int32_t __stdcall fib(int32_t param_1)
{
    int32_t v_1;
    int32_t v_2;
    v_2 = 0;
    for (; 1 < param_1; param_1 += -2) {
        v_1 = (*_fib)(param_1 + -1);
        v_2 += v_1;
    }
    return param_1 + v_2;
}

