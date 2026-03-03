# Bomb Lab Answer

## Phase 1

第一个炸弹小试牛刀，主要在于考察汇编程序的基本语法理解。

```assembly
0000000000400ee0 <phase_1>:
  400ee0:	48 83 ec 08          	sub    rsp,0x8
  400ee4:	be 00 24 40 00       	mov    esi,0x402400
  400ee9:	e8 4a 04 00 00       	call   401338 <strings_not_equal>
  400eee:	85 c0                	test   eax,eax
  400ef0:	74 05                	je     400ef7 <phase_1+0x17>
  400ef2:	e8 43 05 00 00       	call   40143a <explode_bomb>
  400ef7:	48 83 c4 08          	add    rsp,0x8
  400efb:	c3                   	ret    
```

- 准备参数。将地址 0x402400 放入 esi 寄存器。在 x86-64 调用约定中，rsi 是第 2 个参数。这里传入的是正确答案的字符串地址。
- 核心在于 `call   401338 <strings_not_equal>` 这个函数的调用！这一行会把 402400 地址的字符串和输入字符串进行比较（rsi 和 esi）

因此，使用 gdb 查看特定地址的字符串即可：

```bash
(gdb) x/s 0x402400
0x402400:       "Border relations with Canada have never been better."
```

## Phase 2

第二个炸弹考察循环语法。

```assembly
0000000000400efc <phase_2>:
  400efc:	55                   	push   rbp
  400efd:	53                   	push   rbx
  400efe:	48 83 ec 28          	sub    rsp,0x28
  400f02:	48 89 e6             	mov    rsi,rsp
  400f05:	e8 52 05 00 00       	call   40145c <read_six_numbers>
  400f0a:	83 3c 24 01          	cmp    DWORD PTR [rsp],0x1
  400f0e:	74 20                	je     400f30 <phase_2+0x34>
  400f10:	e8 25 05 00 00       	call   40143a <explode_bomb>
  400f15:	eb 19                	jmp    400f30 <phase_2+0x34>
  400f17:	8b 43 fc             	mov    eax,DWORD PTR [rbx-0x4]
  400f1a:	01 c0                	add    eax,eax
  400f1c:	39 03                	cmp    DWORD PTR [rbx],eax
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  400f20:	e8 15 05 00 00       	call   40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    rbx,0x4
  400f29:	48 39 eb             	cmp    rbx,rbp
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
  400f2e:	eb 0c                	jmp    400f3c <phase_2+0x40>
  400f30:	48 8d 5c 24 04       	lea    rbx,[rsp+0x4]
  400f35:	48 8d 6c 24 18       	lea    rbp,[rsp+0x18]
  400f3a:	eb db                	jmp    400f17 <phase_2+0x1b>
  400f3c:	48 83 c4 28          	add    rsp,0x28
  400f40:	5b                   	pop    rbx
  400f41:	5d                   	pop    rbp
  400f42:	c3                   	ret   
```

- 函数参数输入，分配 40 字节的空间（注意 0x28 是十六进制，转化为十进制是 40）
- read_six_numbers 读取六个输入参数
- `cmp DWORD PTR [rsp], 0x1`: **检查第一个数字是否为 1**
- 如果是 跳转到循环 `<phase_2+0x34>` (0x400f30)
    - `400f30:	48 8d 5c 24 04       	lea    rbx,[rsp+0x4]`: 将内存地址 rsp+0x4 的值计算出来，并存入 rbx 寄存器
    - `400f35:	48 8d 6c 24 18       	lea    rbp,[rsp+0x18]`: 将内存地址 rsp+0x18 计算出来，存储到 rbp 寄存器
- 继续进行跳转：`400f17:	8b 43 fc             	mov    eax,DWORD PTR [rbx-0x4]`
- 接下来在 eax 寄存器执行自加翻倍操作
- 比较 rbx（下一个函数输入参数）和当前 eax 寄存器存储的指进行比较
    - 比较通过 则跳转到 `400f25:	48 83 c3 04          	add    rbx,0x4`
    - `400f29:	48 39 eb             	cmp    rbx,rbp`:  rbx 到下一个地址，和栈指针比较（判断循环结束的逻辑）

因此 核心的循环是：

```text
  400f1a:	01 c0                	add    eax,eax
  400f1c:	39 03                	cmp    DWORD PTR [rbx],eax
  400f1e:	74 05                	je     400f25 <phase_2+0x29>
  400f20:	e8 15 05 00 00       	call   40143a <explode_bomb>
  400f25:	48 83 c3 04          	add    rbx,0x4
  400f29:	48 39 eb             	cmp    rbx,rbp
  400f2c:	75 e9                	jne    400f17 <phase_2+0x1b>
```

因此，输入的六个函数参数输入需要不断的自增。`1 2 4 8 16 32`

## Phase 3

第三个炸弹考察跳转表和分支语法。

```assembly
0000000000400f43 <phase_3>:
  400f43:	48 83 ec 18          	sub    rsp,0x18
  400f47:	48 8d 4c 24 0c       	lea    rcx,[rsp+0xc]
  400f4c:	48 8d 54 24 08       	lea    rdx,[rsp+0x8]
  400f51:	be cf 25 40 00       	mov    esi,0x4025cf
  400f56:	b8 00 00 00 00       	mov    eax,0x0
  400f5b:	e8 90 fc ff ff       	call   400bf0 <__isoc99_sscanf@plt>
  400f60:	83 f8 01             	cmp    eax,0x1
  400f63:	7f 05                	jg     400f6a <phase_3+0x27>
  400f65:	e8 d0 04 00 00       	call   40143a <explode_bomb>
  400f6a:	83 7c 24 08 07       	cmp    DWORD PTR [rsp+0x8],0x7
  400f6f:	77 3c                	ja     400fad <phase_3+0x6a>
  400f71:	8b 44 24 08          	mov    eax,DWORD PTR [rsp+0x8]
  400f75:	ff 24 c5 70 24 40 00 	jmp    QWORD PTR [rax*8+0x402470]
  400f7c:	b8 cf 00 00 00       	mov    eax,0xcf
  400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
  400f83:	b8 c3 02 00 00       	mov    eax,0x2c3
  400f88:	eb 34                	jmp    400fbe <phase_3+0x7b>
  400f8a:	b8 00 01 00 00       	mov    eax,0x100
  400f8f:	eb 2d                	jmp    400fbe <phase_3+0x7b>
  400f91:	b8 85 01 00 00       	mov    eax,0x185
  400f96:	eb 26                	jmp    400fbe <phase_3+0x7b>
  400f98:	b8 ce 00 00 00       	mov    eax,0xce
  400f9d:	eb 1f                	jmp    400fbe <phase_3+0x7b>
  400f9f:	b8 aa 02 00 00       	mov    eax,0x2aa
  400fa4:	eb 18                	jmp    400fbe <phase_3+0x7b>
  400fa6:	b8 47 01 00 00       	mov    eax,0x147
  400fab:	eb 11                	jmp    400fbe <phase_3+0x7b>
  400fad:	e8 88 04 00 00       	call   40143a <explode_bomb>
  400fb2:	b8 00 00 00 00       	mov    eax,0x0
  400fb7:	eb 05                	jmp    400fbe <phase_3+0x7b>
  400fb9:	b8 37 01 00 00       	mov    eax,0x137
  400fbe:	3b 44 24 0c          	cmp    eax,DWORD PTR [rsp+0xc]
  400fc2:	74 05                	je     400fc9 <phase_3+0x86>
  400fc4:	e8 71 04 00 00       	call   40143a <explode_bomb>
  400fc9:	48 83 c4 18          	add    rsp,0x18
  400fcd:	c3                   	ret    
```

- 将 rsp+0xc（偏移 12 字节）地址对应的值读取到 rcx 中
- 将 rsp+0x8（偏移 8 字节）地址对应的值读取到 rdx 中
- 0x4025cf 地址：**该函数需要接收两个函数参数的输入值**
    ```text
    Breakpoint 1, 0x0000000000400f43 in phase_3 ()
    (gdb) x/s 0x4025cf
    0x4025cf:       "%d %d"
    ```
- `call   400bf0 <__isoc99_sscanf@plt>` 之后 eax 返回的是 scanf 的返回值 即输入参数的个数（必须大于 1）
- `cmp    DWORD PTR [rsp+0x8],0x7`: 比较第一个输入参数是否为 7

> x86-64 架构要求 栈地址 16 字节对齐。编译器可能为了保持内部对齐，从 rsp+8 开始存储函数的输入参数。

- 如果第一个输入参数 > 7: 跳转到 400fad 引发炸弹
- 从地址中读取具体的指，存储到 eax 寄存器中
- `400f75:	ff 24 c5 70 24 40 00 	jmp    QWORD PTR [rax*8+0x402470]` 构建跳转表（第一个输入参数的值 * 8 + 基地址）

```assembly
400f75:	ff 24 c5 70 24 40 00 	jmp    QWORD PTR [rax*8+0x402470]
400f7c:	b8 cf 00 00 00       	mov    eax,0xcf
400f81:	eb 3b                	jmp    400fbe <phase_3+0x7b>
400f83:	b8 c3 02 00 00       	mov    eax,0x2c3
400f88:	eb 34                	jmp    400fbe <phase_3+0x7b>
400f8a:	b8 00 01 00 00       	mov    eax,0x100
400f8f:	eb 2d                	jmp    400fbe <phase_3+0x7b>
400f91:	b8 85 01 00 00       	mov    eax,0x185
400f96:	eb 26                	jmp    400fbe <phase_3+0x7b>
400f98:	b8 ce 00 00 00       	mov    eax,0xce
400f9d:	eb 1f                	jmp    400fbe <phase_3+0x7b>
400f9f:	b8 aa 02 00 00       	mov    eax,0x2aa
400fa4:	eb 18                	jmp    400fbe <phase_3+0x7b>
400fa6:	b8 47 01 00 00       	mov    eax,0x147
400fab:	eb 11                	jmp    400fbe <phase_3+0x7b>
```

跳转表的具体跳转位置需要通过 gdb 动态查表并且确定：

```bash
(gdb) x/8gx 0x402470
# 使用十六进制的格式打印跳转表
0x402470:       0x0000000000400f7c      0x0000000000400fb9
0x402480:       0x0000000000400f83      0x0000000000400f8a
0x402490:       0x0000000000400f91      0x0000000000400f98
0x4024a0:       0x0000000000400f9f      0x0000000000400fa6
```

很神奇的发现，自动对应上面的格式！

- 索引为 0：跳转到 400f7c，将 eax 赋值为 `0xcf` (207)
- 索引为 2：跳转到 400f83，将 eax 赋值为 `0x2c3` (707)
- 索引为 3：跳转到 400f8a，将 eax 赋值为 `0x100` (256)
- 索引为 4：跳转到 400f91，将 eax 赋值为 `0x185` (389)
- 索引为 5：跳转到 400f98，将 eax 赋值为 `0xce` (206)
- 索引为 6：跳转到 400f9f，将 eax 赋值为 `0x2aa` (682)
- 索引为 7：跳转到 400fa6，将 eax 赋值为 `0x147` (327)
- 索引为 1：跳转到 400fb9，将 eax 赋值为 `0x137` (311)
- 其他索引 全部爆炸

将 eax 和 第二个函数输入参数进行比较

因此，上述所有成立的 switch 语句都是答案！

## Phase 4

第四个炸弹的拆除涉及函数的调用。

```assembly
000000000040100c <phase_4>:
  40100c:	48 83 ec 18          	sub    rsp,0x18
  401010:	48 8d 4c 24 0c       	lea    rcx,[rsp+0xc]
  401015:	48 8d 54 24 08       	lea    rdx,[rsp+0x8]
  40101a:	be cf 25 40 00       	mov    esi,0x4025cf
  40101f:	b8 00 00 00 00       	mov    eax,0x0
  401024:	e8 c7 fb ff ff       	call   400bf0 <__isoc99_sscanf@plt>
  401029:	83 f8 02             	cmp    eax,0x2
  40102c:	75 07                	jne    401035 <phase_4+0x29>
  40102e:	83 7c 24 08 0e       	cmp    DWORD PTR [rsp+0x8],0xe
  401033:	76 05                	jbe    40103a <phase_4+0x2e>
  401035:	e8 00 04 00 00       	call   40143a <explode_bomb>
  40103a:	ba 0e 00 00 00       	mov    edx,0xe
  40103f:	be 00 00 00 00       	mov    esi,0x0
  401044:	8b 7c 24 08          	mov    edi,DWORD PTR [rsp+0x8]
  401048:	e8 81 ff ff ff       	call   400fce <func4>
  40104d:	85 c0                	test   eax,eax
  40104f:	75 07                	jne    401058 <phase_4+0x4c>
  401051:	83 7c 24 0c 00       	cmp    DWORD PTR [rsp+0xc],0x0
  401056:	74 05                	je     40105d <phase_4+0x51>
  401058:	e8 dd 03 00 00       	call   40143a <explode_bomb>
  40105d:	48 83 c4 18          	add    rsp,0x18
  401061:	c3                   	ret 
```

```assembly
0000000000400fce <func4>:
  400fce:	48 83 ec 08          	sub    rsp,0x8
  400fd2:	89 d0                	mov    eax,edx
  400fd4:	29 f0                	sub    eax,esi
  400fd6:	89 c1                	mov    ecx,eax
  400fd8:	c1 e9 1f             	shr    ecx,0x1f
  400fdb:	01 c8                	add    eax,ecx
  400fdd:	d1 f8                	sar    eax,1
  400fdf:	8d 0c 30             	lea    ecx,[rax+rsi*1]
  400fe2:	39 f9                	cmp    ecx,edi
  400fe4:	7e 0c                	jle    400ff2 <func4+0x24>
  400fe6:	8d 51 ff             	lea    edx,[rcx-0x1]
  400fe9:	e8 e0 ff ff ff       	call   400fce <func4>
  400fee:	01 c0                	add    eax,eax
  400ff0:	eb 15                	jmp    401007 <func4+0x39>
  400ff2:	b8 00 00 00 00       	mov    eax,0x0
  400ff7:	39 f9                	cmp    ecx,edi
  400ff9:	7d 0c                	jge    401007 <func4+0x39>
  400ffb:	8d 71 01             	lea    esi,[rcx+0x1]
  400ffe:	e8 cb ff ff ff       	call   400fce <func4>
  401003:	8d 44 00 01          	lea    eax,[rax+rax*1+0x1]
  401007:	48 83 c4 08          	add    rsp,0x8
  40100b:	c3                   	ret    
```

- phase 4 的字符读取逻辑和之前一样 需要读取超过 3 个参数的输入
- `	cmp    DWORD PTR [rsp+0x8],0xe`: 把第一个函数输入参数和 `0xe` (14) 进行比较。
- 如果第一个输入参数 <= 14 进行跳转，否则会被爆炸
- edx 寄存器写入 0xe
- esi 寄存器写入 0x0
- edi 寄存器写入函数的第一个参数
- 进入 func4 的函数调用 **二分查找**：

```assembly
400fce:  sub  rsp, 0x8          ; 栈指针减8，用于对齐栈帧
400fd2:  mov  eax, edx          ; eax = edx (high)
400fd4:  sub  eax, esi          ; eax = high - low
400fd6:  mov  ecx, eax          ; ecx = eax
400fd8:  shr  ecx, 0x1f         ; 逻辑右移31位，取符号位（如果是负数则ecx=1，否则0）
400fdb:  add  eax, ecx          ; 此时符号位为 1 或者 0 我们主要考虑为 1 的情况（可以保证负数除 2 的时候是向下取整的）
400fdd:  sar  eax, 1            ; sar eax, 1 (算术右移1位，即除以2)
400fdf:  lea  ecx,[rax+rsi*1]   ; lea ecx, [rax+rsi*1] (ecx = low + (high-low)/2)
```

公式等同于 `mid = low + (high - low) / 2`。

- rax 在之前的操作中被表示为 `(high - low) / 2`
- rsi 代表**函数的第二个参数输入**，在二分查找中就是 low_bound

```assembly
400fd6:  mov  ecx, eax          ; ecx = eax
400fd8:  shr  ecx, 0x1f         ; 逻辑右移31位，取符号位（如果是负数则ecx=1，否则0）
400fdb:  add  eax, ecx          ; 
```

实现了非常巧妙的**负数取整时向 0 取整**。但是直接使用 sar 指令进行取整是会导致结果为向下取整，因此需要对负数先执行 +1 操作

接下来就是一段非常经典的二分查找，edi 寄存器存储了需要被查找的函数。

```assembly
400fe2:  39 f9                  ; cmp ecx, edi (比较 mid 和 target)
400fe4:  7e 0c                  ; jle 400ff2 (如果 mid <= target，跳转到 400ff2)
400fe6:  8d 51 ff               ; lea edx, [rcx-0x1] (edx = mid - 1，更新上限)
400fe9:  e8 e0 ff ff ff         ; call 400fce <func4> (递归调用 func4)
400fee:  01 c0                  ; add eax, eax (eax = eax * 2)
400ff0:  eb 15                  ; jmp 401007 (跳转至结束)
```

```assembly
400ff2:  b8 00 00 00 00         ; mov eax, 0x0 (默认返回值为0)
400ff7:  39 f9                  ; cmp ecx, edi (再次比较 mid 和 target)
400ff9:  7d 0c                  ; jge 401007 (如果 mid >= target，即相等，则直接跳转结束，返回0)
400ffb:  8d 71 01               ; lea esi, [rcx+0x1] (esi = mid + 1，更新下限)
400ffe:  e8 cb ff ff ff         ; call 400fce <func4> (递归调用 func4)
401003:  8d 44 00 01            ; lea eax, [rax+rax*1+0x1] (eax = 2 * eax + 1)
```

因此，该函数可以转化为如下的代码：

```c
int func4(int target, int low, int high) {
    int mid = low + (high - low) / 2;

    if (mid > target) {
        return 2 * func4(target, low, mid - 1);
    } 
    else if (mid < target) {
        return 2 * func4(target, mid + 1, high) + 1;
    } 
    else {
        return 0; // mid == target
    }
}
```

> rdi, rsi, rdx 为传入的前三个参数

最后的逻辑非常简单：

- 第一个输入参数被当成 target 参数传入 phase_4 的函数中，要求 `test   eax,eax` 函数最终的返回值为 0
- 第二个输入参数为 0
    - 函数的输入参数是 x 0 14
    - 因此第一个输入参数要为 7！

因此输入为 7 0

## Phase 5

More on the way...