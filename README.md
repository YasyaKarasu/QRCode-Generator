# QRCode Generator

## 1. 简介

QRCode Generator是按照求是潮技术二面的技术规范（即遵循$ISO/IEC 18004:2006$标准，仅考虑$Alphanumeric mode$编码模式，仅实现$Ver.1$和$Ver.2$ ）编写的简易的二维码生成器，通过用户选择的二维码版本，将用户输入的字符串转换为相应的二维码的程序。

## 2.特点

- 简明的输入引导
- 无需其他依赖文件
- 生成速度快
- 保存成$png$图片文件

## 3.使用方式

打开$main.exe$后，会提示输入二维码版本及纠错等级，此时用户可以键入一位阿拉伯数字($1$或$2$)，随后键入一位大写字母（$L,M,Q,H$中任意一个）。键入此内容时对格式没有要求，及二维码版本与纠错等级之间可以是任意个空格、短横线等任意字符。

随后会提示输入需要转换的字符串。在输入引导中，会根据用户选择的二维码版本和纠错等级，提示用户所能键入的字符串的最大长度。在用户输入字符串后，若长度超过最大长度，也会提示用户字符串过长，并要求重新输入。

所有合法输入内容获取以后，生成器将迅速将字符串转换为二维码并生成$png$图片文件保存在同一路径下。

## 4.分模块介绍

### 1.$main.cpp$

此文件为生成器主程序，主要体现的是生成二维码的总流程和结构。通过调用各模块的$cpp$文件及其中的功能函数，

实现对二维码的生成。

包含一个函数$void\ combine()$，实现将信息码和纠错码连接在一起。

### 2.$encode.cpp$

此文件为对用户键入字符串进行编码的程序，共包含$4$个函数（需要编码时调用的函数为$encode$）。下面将对其进行一一介绍。

#### 1) $inline\ void\ encode\_init()$

此函数为初始化函数，将在编码最初调用，其功能在于初始化$Alphanumeric$编码表及不同版本、纠错等级的二维码信息串的数据位数。$Alphanumeric$编码表将保存在$alpcod[]$数组中，数据位数将保存在$mp[i][j]$二维数组中（$i$为版本，$1$或$2$；$j$为纠错等级，$L,M,Q,H$分别对应$1,2,3,4$）。

#### 2) $inline\ void\ bin\_code(char\ a[],int\ cod,int\ ep)$

此函数可以将十进制数码转换为二进制数码并补全所需长度保存在字符串数组$a[]$中。三个参数中，$a[]$为需要保存的目标字符串数组，$cod$为转码的待十进制数码，$ep$为补全长度后字符串数组最后一位的数组下标（考虑到$mod2$法转换为二进制需要倒存余数，及方便补齐长度）。

| 参数  | 类型     | 含义                                   |
| ----- | -------- | -------------------------------------- |
| $a[]$ | $char[]$ | 需要保存的目标字符串数组               |
| $cod$ | $int$    | 待转码的十进制数码                     |
| $ep$  | $int$    | 补全长度后字符串数组最后一位的数组下标 |

#### 3) $inline\ void\ \_encode(char\ s[],char\ a[])$

此函数是将数据编码的主要函数，传入的两个参数$s[]$和$a[]$分别为用户键入的待编码信息串和需要存入的目标数组。函数实现的过程中需要调用$bin\_code$函数。

| 参数  | 类型     | 含义                   |
| ----- | -------- | ---------------------- |
| $s[]$ | $char[]$ | 用户键入的待编码信息串 |
| $a[]$ | $char[]$ | 需要存入的目标数组     |

#### 4)$void\ encode(char\ s[],int\ v,int\ erl,char\ a[])$☆

此函数为$main.cpp$调用$encode.cpp$的主要接口，也是将字符串编码时需要调用的函数。工作流程为$encode\_init()$初始化，$\_encode()$将信息串编码，再填上终止符及依据对应版本的数据位数补足信息编码的长度。

| 参数  | 类型     | 含义                   |
| ----- | -------- | ---------------------- |
| $s[]$ | $char[]$ | 待编码信息串           |
| $v$   | $int$    | 二维码版本             |
| $erl$ | $int$    | 二维码纠错等级         |
| $a[]$ | $char[]$ | 信息编码存入的目标数组 |

### 3. $gf.h$与$gf.cpp$

$gf$即为$Galois\ Field$（伽罗华域）的首字母。$gf.h$中定义了$poly$结构体，即为$polynomial$（多项式），其中包含$2$个变量和$3$个函数，下面一一介绍。

| 变量名  | 类型    | 含义                                                         |
| ------- | ------- | ------------------------------------------------------------ |
| $coe[]$ | $int[]$ | 多项式系数（$coe[i]$表示$x^i$的系数）                        |
| $len$   | $int$   | 多项式算上$0$次项和$0$系数项的总长度（即最高次项系数为$len-1$） |

#### 1) $void\ init()$

此函数为$poly$结构体的初始化函数，即将$coe[]$数组清空为$0$，并将$len$赋值为$0$。

#### 2) $void\ clean()$

此函数用于多项式进行计算以后，清除高次项的零系数。

#### 3) $void\ mulx(int\ m)$

此函数的作用是两个多项式进行加减时补齐较短多项式后方的$0$，其中的参数$m$表示需要补齐的长度，即两个多项式$len$的差。

| 参数 | 类型  | 含义           |
| ---- | ----- | -------------- |
| $m$  | $int$ | 需要补齐的长度 |

### 4. $correct.cpp$

根据$encode$模块中生成的信息编码以及对应二维码版本的生成多项式，通过调用$gf.h$中的多项式结构体来完成纠错码的计算。共包含$3$个函数（需要生成纠错码时调用的是$correct\_code$），下面进行介绍。

#### 1) $void\ ECcode\_table(int\ v,int\ erl)$

此函数为打表函数。考虑到本项目仅需实现版本为$1$或$2$的二维码的生成，而生成多项式仅与版本和纠错等级相关，故仅有$2*4-1=7$种（有一个重复），利用打表会比繁杂的多项式展开运行迅速。生成多项式将保存在$\_c$中。传入的两个参数为版本和纠错等级。

| 参数  | 类型  | 含义           |
| ----- | ----- | -------------- |
| $v$   | $int$ | 二维码版本     |
| $erl$ | $int$ | 二维码纠错等级 |

#### 2)  $void\ correct\_init(int\ v,int\ erl,poly\ \&\_p)$

此函数为纠错码生成的初始化函数，主要功能是生成$GF(256)$中对数表示的对数表及其反表方便后续计算，以及调用$ECcode\_table$函数打表。生成的对数表存在$alp[]$数组中，而反表存在$num\_to\_alp[]$数组中。传入的参数为版本，纠错等级和主程序传来的存储纠错码的$poly$结构体。

| 参数  | 类型   | 含义                     |
| ----- | ------ | ------------------------ |
| $v$   | $int$  | 二维码版本               |
| $erl$ | $int$  | 二维码纠错等级           |
| $\_p$ | $poly$ | 存储纠错码的$poly$结构体 |



#### 3) $void\ correct\_code(char\ \_cont[],int\ v,int\ erl,poly\ \&\_p)$☆

此函数是$main.cpp$调用纠错码模块时主要接口，也是生成纠错码时需要调用的函数。会先将上一步生成的信息编码按八位一组转换成十进制数码存储在$\_p$多项式结构体中，补上长度方便后续计算，然后不断使用它与生成多项式进行减法直到长度符合要求。四个参数分别为信息编码，版本，纠错等级和生成的纠错码存储的目标$poly$结构体；

| 参数       | 类型     | 含义                               |
| ---------- | -------- | ---------------------------------- |
| $\_cont[]$ | $char[]$ | 信息编码数组                       |
| $v$        | $int$    | 二维码版本                         |
| $erl$      | $int$    | 二维码纠错等级                     |
| $\_p$      | $poly$   | 生成的纠错码存储的目标$poly$结构体 |

### 5.$print.cpp$

这是在计算完信息编码和纠错码之后将这些编码形成最终的二维码图像并输出的程序文件，调用了绘图库$svpng$。需要注意到的是，本文件中$QRCode$二维数组对二维码数组的存储方式为$01$存储，$0$代表白色码元，$1$代表黑色码元，且二维数组的两个下标为**先列后行**。共包含$6$个函数，下面进行介绍。

#### 1) $void\ \_print(int\ v)$

这是将填充完的01矩阵进行最终输出，绘图库的调用就是在这个函数中。调用时需要$include$"$svpng.inc$"文件，调用方式为每一个像素占用一维数组$img$的三个下标，然后利用函数

```c++
void svpng(FILE* out, unsigned w, unsigned h, const unsigned char* img, int alpha);
```

即可简单完成对图片的输出。

传入的参数$v$即二维码版本。

| 参数 | 类型  | 含义       |
| ---- | ----- | ---------- |
| $v$  | $int$ | 二维码版本 |

#### 2) $void\ print\_init(int\ v)$

此函数为绘制二维码的初始化函数，作用是填充定位标志，校准标志，定时标志。传入参数$v$为二维码版本

| 参数 | 类型  | 含义       |
| ---- | ----- | ---------- |
| $v$  | $int$ | 二维码版本 |

#### 3) $void\ nxtp(int\ \&xx,int\ \&yy,int\ \&c,int\ \&r,int\ v,int\ \&f)$

此函数用于将编码串填入矩阵时获取下一步的坐标。共传入六个参数，下表进行详述。

| 参数 | 类型  | 含义                                          |
| ---- | ----- | --------------------------------------------- |
| $xx$ | $int$ | 当前填充的列坐标                              |
| $yy$ | $int$ | 当前填充的行坐标                              |
| $c$  | $int$ | 当前列的移动是左还是右                        |
| $r$  | $int$ | 当前行的移动是上还是下                        |
| $v$  | $int$ | 二维码版本                                    |
| $f$  | $int$ | 是否需要换行（每两个填充换一行进行$Z$型填充） |

#### 4) $int\ calc(int\ mp[][30],int\ v,int\ erl,int\ idt)$

这是在应用每一个掩码模式后计算掩码罚分的函数，共传入四个参数，下面进行详述

| 参数       | 类型  | 含义                                           |
| ---------- | ----- | ---------------------------------------------- |
| $mp[][30]$ | $int$ | 应用了掩码模式后的二维码矩阵                   |
| $v$        | $int$ | 二维码版本                                     |
| $erl$      | $int$ | 二维码纠错等级                                 |
| $idt$      | $int$ | 当前掩码方案编号，以便在矩阵中填入掩码模式信息 |

#### 5) $int\ mask\_code(int\ v,int\ erl)$

此函数用于将八种掩码模式应用于仅填写完信息的二维码矩阵中，并通过调用$calc()$函数计算每一种模式下的罚分，以求得最优掩码模式，该模式的$id$将作为函数返回值。传入两个参数，二维码版本与纠错等级。

| 参数  | 类型  | 含义           |
| ----- | ----- | -------------- |
| $v$   | $int$ | 二维码版本     |
| $erl$ | $int$ | 二维码纠错等级 |

#### 6) $void\ print(int\ v,int\ erl,char\ \_cont[])$

这个函数是$main.cpp$调用最终绘画功能的主要接口，主体部分是在填入信息编码，其余则是调用上述函数进行绘图。共传入了三个参数，分别为二维码版本，纠错等级和需要填入的信息编码。

| 参数       | 类型     | 含义               |
| ---------- | -------- | ------------------ |
| $v$        | $int$    | 二维码版本         |
| $erl$      | $int$    | 二维码纠错等级     |
| $\_cont[]$ | $char[]$ | 需要填入的信息编码 |

## 5.后记（总结与反思）

### 1. 

- Q：你觉得解决这个任务的过程有意思吗？

- A：有意思。虽然在完成这个项目的过程中有很多抓耳挠腮的时候（乐），但是每当de了半小时一小时bug终于取得了阶段性的进展时还是特别开心，尤其是最终成功输出$png$图片的时候，这种喜悦让曾经的苦涩都变得甜了起来。

    

### 2.

- Q：你在网上找到了哪些资料供你学习？你觉得去哪里/用什么方式搜索可以比较有效的获得自己想要的资料？
- A：首先是一套对二维码编码讲解详细的博客，它是将$thonky.com$上的介绍完整翻译了的一套博客；其次是关于头文件引用和编写的一些博客，通过它们我得以将程序按功能拆分成部分；最后是$github$上的绘图库$svpng$和它的使用文档，它让我能将01矩阵输出成$png$图像。查找方式的话，首先肯定是百度、$google$，通过搜索关键字来找一些相关的博客进行学习；另外在$github$上进行关键字搜索，也可以获取到自己所需要的一些功能库及其使用方式。



### 3.

- Q：在过程中，你遇到最大的困难是什么？你是怎么解决的？
- A：往细了说，是最后将01矩阵图形化的过程。因为利用$C++$绘图对我而言确实是完全全新的一个领域，刚开始完全不知道从何下手，不知道怎么去寻找合适的库来调用。开始的时候我通过百度和谷歌查找"C++ 绘图库" “C++ 二维码绘图库”等等，但都很难找到适合我的简单易操作的绘图库来调用。后来我直接在$github$上搜索$png$并勾选$C++$，便寻找到了适合我的绘图库。往大了说的话，最大的困难就是面对开发和算法竞赛的巨大差异。没有对拍，没有题解，有时候一个bug可能要自己一个人摸很久也没有进展，有时候要实现一些功能也只能自己全网搜索。解决这个问题一方面靠的是对它的热情和阶段性的成就感，另一方面则是沉下心来克服debug过程中的烦躁。



### 4.

- Q：完成任务之后，再回去阅读你写下的代码和文档，有没有看不懂的地方？如果再过一年，你觉得那时你还可以看懂你的代码吗？
- A：暂时没有。再过一年，我觉得大体上的结构和流程还是可以看懂的的，但是有些细节上的灵光一现的实现方式或许会难以看懂。



### 5.

- Q：在完成任务之后，如果要求你在已写好的代码基础上再加入生成 version 3~40 的二维码的功能，你是否会选择重新规划代码结构并重写大部分代码？
- A：不会。相比于更大尺寸的版本，一和二的版本仅仅是缺少了对信息编码的划分以及版本信息，要大片改写的可能只有生成多项式的生成，相比于只有两个版本的简单打表，若是要打40个版本的表，或许不太合适，可能就要考虑写多项式展开了。