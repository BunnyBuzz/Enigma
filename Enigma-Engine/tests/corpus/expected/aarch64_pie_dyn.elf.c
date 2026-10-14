void __cdecl entry()
{
    code *UNRECOVERED_JUMPTABLE;
    UNRECOVERED_JUMPTABLE = (code *)__libc_init();
    if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    
                    
        (*UNRECOVERED_JUMPTABLE)();
        return;
    }
    return;
}



void __cdecl __libc_init()
{
                    
                    
    (*___libc_init)();
    return;
}

void __cdecl func_0xc8c(uint64_t param_1)
{
    code *UNRECOVERED_JUMPTABLE;
    uint64_t local_0x40;
    uint64_t local_0x38;
    uint64_t local_0x30;
    uint64_t local_0x28;
    uint64_t local_0x20;
    uint64_t local_0x18;
    local_0x28 = 0;
    local_0x30 = 0;
    local_0x18 = 0;
    local_0x20 = 0;
    local_0x38 = 0;
    local_0x40 = 0;
    if (0 < ptr_0x5760 - ptr_0x5758) {
        local_0x30 = 0x9810;
    }
    UNRECOVERED_JUMPTABLE = (code *)__libc_init(param_1,0,ptr_0x5768,&local_0x40);
    if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    
                    
        (*UNRECOVERED_JUMPTABLE)();
        return;
    }
    return;
}

void __cdecl func_0xce4(code *UNRECOVERED_JUMPTABLE)
{
    if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    
                    
        (*UNRECOVERED_JUMPTABLE)();
        return;
    }
    return;
}



void __cdecl func_0xcf8(uint64_t param_1)
{
                    
                    
    (*___cxa_atexit)(0xce4,param_1,0x9828);
    return;
}



void __cdecl func_0xd14()
{
                    
                    
    (*___register_atfork)();
    return;
}

void __cdecl func_0xd24()
{
    int64_t v_1;
    int64_t v_2;
    int64_t v_3;
    v_2 = ptr_0x5758;
    if (ptr_0x5760 - ptr_0x5758 != 0) {
        v_3 = ptr_0x5760 - ptr_0x5758 >> 3;
        do {
            v_1 = v_3 * 8;
            v_3 += -1;
            (**(code **)(v_2 + v_1 + -8))();
        } while (v_3 != 0);
    }
    return;
}

void __cdecl func_0xd78()
{
    int64_t v_1;
    int64_t v_2;
    uint64_t local_0x50;
    uint64_t local_0x48;
    uint16_t local_0x42;
    uint64_t local_0x40;
    uint64_t local_0x3a;
    int64_t local_0x28;
    v_1 = tpidr_el0;
    local_0x28 = *(int64_t *)(v_1 + 0x28);
    v_2 = ptrace(0,0,1,0);
    if (v_2 < 0) {
        local_0x48 = 0x636574656420;
        local_0x50 = 0x7265676775626544;
        local_0x3a = 0xabf979ff02074;
        local_0x42 = 0x6574;
        local_0x40 = 0x697845202e64;
        syscall(0x40,1,&local_0x50,0x1d);
        syscall(0x5e,1);
    }
    v_2 = getenv(0x8e4);
    if (v_2 != 0) {
        syscall(0x5e,2);
    }
    if (*(int64_t *)(v_1 + 0x28) == local_0x28) {
        return;
    }
                    
    __stack_chk_fail();
}

void __cdecl func_0xe24()
{
    int64_t v_1;
    uint8_t local_0x48 [32];
    int64_t local_0x28;
    v_1 = tpidr_el0;
    local_0x28 = *(int64_t *)(v_1 + 0x28);
    write(1,0x8b8,0xf);
    __read_chk(0,local_0x48,0x300,0x20);
    write(1,0x8cf,0xd);
    if (*(int64_t *)(v_1 + 0x28) == local_0x28) {
        return;
    }
                    
    __stack_chk_fail();
}

void __cdecl func_0xea8()
{
    int64_t v_1;
    uint64_t v_2;
    uint32_t v_3;
    void *v_4;
    uint64_t v_5;
    uint64_t local_0x48;
    uint32_t local_0x3c;
    int64_t local_0x38;
    v_1 = tpidr_el0;
    local_0x38 = *(int64_t *)(v_1 + 0x28);
    write(1,0x8f3,5);
    v_3 = scanf("%d",&local_0x3c);
    v_5 = (uint64_t)v_3;
    if (local_0x3c < 8) {
        write(1,0x8dd,6);
        v_3 = scanf("%zu",&local_0x48);
        v_2 = local_0x48;
        v_5 = (uint64_t)v_3;
        if (0xfffffffffffffaff < local_0x48 - 0x501) {
            v_4 = malloc(local_0x48);
            *(void **)((int64_t)(int32_t)local_0x3c * 8 + 0x9830) = v_4;
            *(uint64_t *)((int64_t)(int32_t)local_0x3c * 8 + 0x9870) = v_2;
            write(1,0x8c8,6);
            v_5 = __read_chk(0,*(uint64_t *)((int64_t)(int32_t)local_0x3c * 8 + 0x9830)
                              ,local_0x48,0xffffffffffffffff);
        }
    }
    if (*(int64_t *)(v_1 + 0x28) == local_0x38) {
        return;
    }
                    
    __stack_chk_fail(v_5);
}

void __cdecl func_0xfa4()
{
    int64_t v_1;
    uint32_t local_0x2c;
    int64_t local_0x28;
    v_1 = tpidr_el0;
    local_0x28 = *(int64_t *)(v_1 + 0x28);
    write(1,0x8f3,5);
    scanf("%d",&local_0x2c);
    if (local_0x2c < 8) {
        free(*(void **)((uint64_t)local_0x2c * 8 + 0x9830));
    }
    if (*(int64_t *)(v_1 + 0x28) == local_0x28) {
        return;
    }
                    
    __stack_chk_fail();
}

void __cdecl func_0x1024()
{
    int64_t v_1;
    uint32_t v_2;
    uint64_t v_3;
    int64_t v_4;
    uint32_t local_0x2c;
    int64_t local_0x28;
    v_1 = tpidr_el0;
    local_0x28 = *(int64_t *)(v_1 + 0x28);
    write(1,0x8f3,5);
    v_2 = scanf("%d",&local_0x2c);
    v_3 = (uint64_t)v_2;
    if ((local_0x2c < 8) && 
           (v_4 = *(int64_t *)((uint64_t)local_0x2c * 8 + 0x9830), v_4 != 0)) {
        v_3 = __write_chk(1,v_4,*(uint64_t *)((uint64_t)local_0x2c * 8 + 0x9870),
                           0xffffffffffffffff);
    }
    if (*(int64_t *)(v_1 + 0x28) == local_0x28) {
        return;
    }
                    
    __stack_chk_fail(v_3);
}

void __cdecl func_0x10bc()
{
    int64_t v_1;
    uint32_t v_2;
    uint64_t v_3;
    uint32_t local_0x2c;
    int64_t local_0x28;
    v_1 = tpidr_el0;
    local_0x28 = *(int64_t *)(v_1 + 0x28);
    write(1,0x8f3,5);
    v_2 = scanf("%d",&local_0x2c);
    v_3 = (uint64_t)v_2;
    if ((local_0x2c < 8) && (*(int64_t *)((uint64_t)local_0x2c * 8 + 0x9830) != 0)) {
        write(1,0x8c8,6);
        v_3 = __read_chk(0,*(uint64_t *)((int64_t)(int32_t)local_0x2c * 8 + 0x9830),
                          *(uint64_t *)((int64_t)(int32_t)local_0x2c * 8 + 0x9870),
                          0xffffffffffffffff);
    }
    if (*(int64_t *)(v_1 + 0x28) == local_0x28) {
        return;
    }
                    
    __stack_chk_fail(v_3);
}



uint64_t __cdecl func_0x1184()
{
    int64_t v_1;
    int32_t v_2;
    int64_t v_3;
    int32_t local_0x114;
    uint64_t local_0x110;
    uint64_t *local_0x108;
    uint64_t local_0x100;
    uint64_t local_0xf8;
    uint64_t local_0xf0;
    uint64_t local_0xe8;
    uint64_t local_0xe0;
    uint64_t local_0xd8;
    uint64_t local_0xd0;
    uint64_t local_0xc8;
    uint64_t local_0xc0;
    uint64_t local_0xb8;
    uint64_t local_0xb0;
    uint64_t local_0xa8;
    uint64_t local_0xa0;
    uint64_t local_0x98;
    uint64_t local_0x90;
    uint64_t local_0x88;
    int64_t local_0x78;
    v_1 = tpidr_el0;
    local_0x78 = *(int64_t *)(v_1 + 0x28);
    setvbuf((void *)*_stdin,(char *)0x0,2,0);
    setvbuf((void *)*_stdout,(char *)0x0,2,0);
    local_0xb8 = 0xd601000015;
    local_0xc0 = 0x7fff000000000006;
    local_0xa8 = 0xde01000015;
    local_0xb0 = 0x7fff000000000006;
    local_0x98 = 0xe201000015;
    local_0xa0 = 0x7fff000000000006;
    local_0x88 = 6;
    local_0x90 = 0x7fff000000000006;
    local_0xf8 = 0x3f01000015;
    local_0x100 = 0x20;
    local_0xe8 = 0x4001000015;
    local_0xf0 = 0x7fff000000000006;
    local_0x110 = 0x10;
    local_0xd8 = 0x3801000015;
    local_0xe0 = 0x7fff000000000006;
    local_0xc8 = 0x5e01000015;
    local_0xd0 = 0x7fff000000000006;
    local_0x108 = &local_0x100;
    prctl(0x26,1,0,0,0);
    syscall(0x115,1,0,&local_0x110);
    write(1,0x8ff,0x49);
    write(1,0x8f9,2);
    v_2 = scanf("%d",&local_0x114);
    while (v_2 == 1) {
        if (local_0x114 < 4) {
            if (local_0x114 == 1) {
                local_0x110 = 0x300;
                write(1,0x8b8,0xf);
                __read_chk(0,&local_0x100,local_0x110,0x20);
                write(1,0x8cf,0xd);
            }
            else if (local_0x114 == 2) {
                func_0xea8();
            }
            else if (local_0x114 == 3) {
                write(1,0x8f3,5);
                scanf("%d",&local_0x100);
                if ((uint32_t)local_0x100 < 8) {
                    free(*(void **)((local_0x100 & 0xffffffff) * 8 + 0x9830));
                }
            }
        }
        else if (local_0x114 == 4) {
            write(1,0x8f3,5);
            scanf("%d",&local_0x100);
            if (((uint32_t)local_0x100 < 8) && 
                   (v_3 = *(int64_t *)((local_0x100 & 0xffffffff) * 8 + 0x9830), v_3 != 0)
                       ) {
                __write_chk(1,v_3,*(uint64_t *)
                                    ((local_0x100 & 0xffffffff) * 8 + 0x9870),
                             0xffffffffffffffff);
            }
        }
        else if (local_0x114 == 5) {
            write(1,0x8f3,5);
            scanf("%d",&local_0x100);
            if (((uint32_t)local_0x100 < 8) && 
                   (*(int64_t *)((local_0x100 & 0xffffffff) * 8 + 0x9830) != 0)) {
                write(1,0x8c8,6);
                __read_chk(0,*(uint64_t *)
                               ((int64_t)(int32_t)(uint32_t)local_0x100 * 8 + 0x9830),
                            *(uint64_t *)
                             ((int64_t)(int32_t)(uint32_t)local_0x100 * 8 + 0x9870),
                            0xffffffffffffffff);
            }
        }
        else if (local_0x114 == 6) {
            syscall(0x5e,0);
        }
        write(1,0x8ff,0x49);
        write(1,0x8f9,2);
        v_2 = scanf("%d",&local_0x114);
    }
    if (*(int64_t *)(v_1 + 0x28) == local_0x78) {
        return 0;
    }
                    
    __stack_chk_fail();
}

void __cdecl func_0x14b0()
{
                    
                    
    (*ptr_0x5790)();
    return;
}



void __cdecl __cxa_atexit()
{
                    
                    
    (*___cxa_atexit)();
    return;
}



void __cdecl __register_atfork()
{
                    
                    
    (*___register_atfork)();
    return;
}



void __cdecl ptrace()
{
                    
                    
    (*_ptrace)();
    return;
}



void __cdecl syscall()
{
                    
                    
    (*_syscall)();
    return;
}



void __cdecl getenv()
{
                    
                    
    (*_getenv)();
    return;
}



void __cdecl __stack_chk_fail()
{
                    
                    
    (*___stack_chk_fail)();
    return;
}



void __cdecl write()
{
                    
                    
    (*_write)();
    return;
}



void __cdecl __read_chk()
{
                    
                    
    (*___read_chk)();
    return;
}



int32_t __cdecl scanf(char *param_1,...)
{
    int32_t v_1;
                    
                    
    v_1 = (*_scanf)((int32_t)param_1);
    return v_1;
}



void * __cdecl malloc(uint64_t param_1)
{
    void *v_1;
                    
                    
    v_1 = (void *)(*_malloc)();
    return v_1;
}



void __cdecl free(void *param_1)
{
                    
                    
    (*_free)();
    return;
}



void __cdecl __write_chk()
{
                    
                    
    (*___write_chk)();
    return;
}



int32_t __cdecl setvbuf(void *param_1, char *param_2, int32_t param_3, uint64_t param_4)
{
    int32_t v_1;
                    
                    
    v_1 = (*_setvbuf)((int32_t)param_1,param_2,param_3);
    return v_1;
}



void __cdecl prctl()
{
                    
                    
    (*_prctl)();
    return;
}

