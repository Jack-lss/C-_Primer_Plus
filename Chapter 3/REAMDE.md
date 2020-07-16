# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## Chapter 3

- arith

  - cout.setf的使用

  ```c++
  cout.setf(ios_base::fixed, ios_base::floatfield);
  // cout.setf()设置cout流的输出格式
  // ios_base::fixed是设置cout为定点输出格式
  // ios_base::floatfield是设置输出时按浮点格式，小数点后有6位数字
  ```

- assign

  - double转int的限制

  ```c++
  int debt = 7.2E12;
  // result not defined in C++
  // int储存的限制
  cout << "debt = " << debt << endl;
  // debt = 2147483647
  ```

- bondini

  - 转义字符的使用

  |                            转义符                            |  描述(10进制)   |
  | :----------------------------------------------------------: | :-------------: |
  |                              \a                              |  响铃(BEL) 007  |
  | \b |  退格(BS) 008   |
  |                              \f                              |  换页符(FF)012  |
  |                              \n                              |   换行(LF)010   |
  |                              \r                              |   回车(CR)013   |
  |                              \t                              | 水平制表(HT)009 |
  |                              \v                              | 垂直制表(VT)011 |
  |                             \\\                              |    反斜杠092    |
  |                              \?                              |    问号符063    |
  |\\' | 单引号039 |
  |\\"| 双引号034|
  |\0|空字符(NULL)000|
  |\ddd|任意字符 三位八进制|
  |\xhh |任意字符 二位十六进制|

  ```c++
  // \a 响铃是指系统的响铃声，执行这一步时，系统响铃
  // \b 退格相当于键盘的删除键
  long code;
  // long型是加长整型
  ```

- chartype

  - char的使用

  ```c++
  char ch;
  // 只接受一个字符，多余的丢掉
  ```

- divide

  - 除法的使用

  ```c++
  cout.setf(ios_base::fixed, ios_base::floatfield);
  cout << "Integer division: 9/5 = " << 9 / 5 << endl;
  // Integer division: 9/5 = 1
  cout << "Floating-point division: 9.0/5.0 = " << 9.0 / 5.0 << endl;
  // Floating-point division: 9.0/5.0 = 1.800000
  cout << "Mixed division: 9.0/5 = " << 9.0 / 5 << endl;
  // Mixed division: 9.0/5 = 1.800000
  cout << "double constants: 1e7/9.0 = " << 1.e7 / 9.0 << endl;
  // double constants: 1e7/9.0 = 1111111.111111
  cout << "float constants: 1e7f/9.0f = " << 1.e7f / 9.0f << endl;
  // float constants: 1e7f/9.0f = 1111111.125000
  // 这里是因为设置了cout流格式，所以两者不同

  // 小数默认表示双精度
  ```

  - 数字后面跟u,l,f的作用
    - U表示该常数用无符号整型方式存储，相当于 unsigned int
    - L表示该常数用长整型方式存储，相当于 long
    - F表示该常数用浮点方式存储，相当于 float

- exceed

  - 短整型和无符号短整型

  ```c++
  #include <climits>
  #define ZERO 0
  short sam = SHRT_MAX;
  unsigned short sue = sam;
  cout << "Sam has " << sam << " dollars and Sue has " << " dollars deposited." << endl
  // Sam has 32767 dollars and Sue has 32767 dollars deposited.
  sam = sam + 1;
  sue = sue + 1;
  cout << "Sam has " << sam << " dollars and Sue has " << " dollars deposited." << endl;
  // Now Sam has -32768 dollars and Sue has 32768 dollars deposited.
  sam = ZERO;
  sue = ZERO;
  cout << "Sam has " << sam << " dollars and Sue has " << sue << " dollars deposited." << endl;
  // Sam has 0 dollars and Sue has 0 dollars deposited.
  sam = sam - 1;
  sue = sue - 1;
  cout << "Sam has " << sam << " dollars and Sue has " << sue << " dollars deposited." << endl
  // Sam has -1 dollars and Sue has 65535 dollars deposited.
  ```

  - 有符号短整型

    范围在-32768~32767，值循环

  - 无符号短整型

    范围在0~65535，值循环

- floatnum

  ```c++
  float tub = 10.0 / 3.0;
  double mint = 10.0 / 3.0;
  const float million = 1.0e6;

  cout << "tub = " << tub << ", a million tubs = " << million * tub;
  // tub = 3.333333, a million tubs = 3333333.250000,
  cout << ",\nand ten million tubs = " << 10 * million * tub << endl;
  // and ten million tubs = 33333332.000000
  cout << "mint = " << mint << " and a million mints = " << million * mint << endl;
  // mint = 3.333333 and a million mints = 3333333.333333
  ```

  - float

    (32bit二进制)1符号位、8整数位、23小数位

    十进制精度是6位

  - double

    (64bit二进制)1符号位、11整数位、52小数位

    十进制进度是15位

- fltaadd

  - 同floatnum

  ```c++
  float a = 2.34E+22f;
  float b = a + 1.0f;
  cout << "a = " << a << endl;
  // a = 2.34e+002
  cout << "b - a = " << b - a << endl;
  // b - a = 0
  ```

- hexoct1

  - 16进制和8进制

  ```c++
  int chest = 42;   // decimal integer literal
  int waist = 0x42; // hexadecimal integer literal
  int inseam = 042; // octal integer literal
  cout << "chest = " << chest << " (42 in decimal)\n";
  // chest = 42 (42 in decimal)
  cout << "waist = " << waist << " (0x42 in hex)\n";
  // waist = 66 (0x42 in hex)
  cout << "inseam = " << inseam << " (042 in octal)\n";
  // inseam = 34 (042 in octal)
  ```

- hexoct2

  - cout设置16进制和8进制

  ```c++
  int chest = 42;
  int waist = 42;
  int inseam = 42;
  cout << "chest = " << chest << " (decimal for 42)" << endl;
  // chest = 42 (decimal for 42)
  cout << hex; // 设置16进制输出
  cout << "waist = " << waist << " (hexadecimal for 42)" << endl;
  // waist = 2a (hexadecimal for 42)
  cout << oct; // 设置8进制输出
  cout << "inseam = " << inseam << " (octal for 42)" << endl;
  // inseam = 52 (octal for 42)
  ```

- init

  - 不同格式的初始化

  ```c++
  float tree = 3;
  int guess(3.9832); // 括号相当于函数赋值
  int debt = 7.2E12; // 错误，超出int上限
  ```

- limits

  - 不同类型所占字节、上下限

  ```c++
  #include <climits>
  int n_int = INT_MAX;      // initialize n_int to max int value
  short n_short = SHRT_MAX; // symbols defined in climits file
  long n_long = LONG_MAX;
  long long n_llong = LLONG_MAX;

  // sizeof operator yields size of type or of variable
  cout << "int is " << sizeof(int) << " bytes." << endl;
  // int is 4 bytes.
  cout << "short is " << sizeof n_short << " bytes." << endl;
  // short is 2 bytes.
  cout << "long is " << sizeof n_long << " bytes." << endl;
  // long is 4 bytes.
  cout << "long long is " << sizeof n_llong << " bytes." << endl;
  // long long is 8 bytes.
  cout << endl;

  Maximum values:
  cout << "Maximum values:" << endl;
  cout << "int: " << n_int << endl;
  // int: 2147483647
  cout << "short: " << n_short << endl;
  // short: 32767
  cout << "long: " << n_long << endl;
  // long: 2147483647
  cout << "long long: " << n_llong << endl
  // long long: 9223372036854775807
       << endl;

  cout << "Minimum int value = " << INT_MIN << endl;
  // Minimum int value = -2147483648
  cout << "Bits per byte = " << CHAR_BIT << endl;
  // Bits per byte = 8
  ```

  - sizeof的使用

    1. sizeof(type);
    2. sizeof value;
  - include <climits>包含的内容

    - 上限

      1. INT_MAX = 2147483647
      2. SHRT_MAX =  32767
      3. LONG_MAX = 2147483647
      4. LLONG_MAX = 9223372036854775807

    - 下限

      1. INT_MIN = -2147483648
      2. CHAR_BIT = 8

- modulus

  - 除和除余

- morechar

  - ASCII码的使用

  ```c++
  char ch = 'M'; // assign ASCII code for M to ch
  int i = ch;    // store same code in an int
  cout << "The ASCII code for " << ch << " is " << i << endl;
  // The ASCII code for M is 77
  ch = ch + 1; // change character code in ch
  i = ch;      // save new character code in i
  cout << "The ASCII code for " << ch << " is " << i << endl;
  // The ASCII code for N is 78
  ```

  - cout.put()的使用

    put()函数只能打印字符

  ```c++
  cout.put(ch);
  cout.put('!');
  ```

- typecast

  - 强制转换

    转换不会四舍五入；

    强制转换函数相当于调用static_cast<type>();

  ```c++
  int auks, bats, coots;
  auks = 19.99 + 11.99;

  // these statements add values as int
  bats = (int)19.99 + (int)11.99;  // old C syntax
  coots = int(19.99) + int(11.99); // new C++ syntax
  cout << "auks = " << auks << ", bats = " << bats << ", coots = " << coots << endl;
  // auks = 31, bats = 30, coots = 30

  char ch = 'Z';
  cout << "The code for " << ch << " is " << int(ch) << endl;
  // The code for Z is 90
  cout << "Yes, the code is " << static_cast<int>(ch) << endl;
  // Yes, the code is 90
  ```
