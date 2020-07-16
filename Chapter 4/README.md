# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## Chapter 4

- addpntrs

  - 指针*的使用

  ```c++
  double wages[3] = {10000.0, 20000.0, 30000.0};
  short stacks[3] = {3, 2, 1};
  double *pw = wages;
  short *ps = &stacks[0];
  cout << "pw = " << pw << ", *pw = " << *pw << endl;
  // pw = 0x61fdf0, *pw = 10000
  // 地址加1，再取指针的时候按类型+1
  pw = pw + 1;
  cout << "pw = " << pw << ", *pw = " << *pw << "\n\n";
  // pw = 0x61fdf8, *pw = 20000

  // 同理
  cout << "ps = " << ps << ", *ps = " << *ps << endl;
  ps = ps + 1;
  cout << "ps = " << ps << ", *ps = " << *ps << "\n\n";

  // 取指针，相当于数组取值
  cout << "stacks[0] = " << stacks[0] << ", stacks[1] = " << stacks[1] << endl;
  // stacks[0] = 3, stacks[1] = 2
  cout << "*stacks = " << *stacks << ", *(stacks + 1) =  " << *(stacks + 1) << endl;
  // *stacks = 3, *(stacks + 1) =  2
  ```

  - 指针的长度

  ```c++
  cout << sizeof(wages) << " = size of wages array\n";
  // 24 = size of wages array
  cout << sizeof(pw) << " = size of pw pointer\n";
  // 8 = size of pw pointer

  cout << sizeof(stacks) << " = size of stacks array\n";
  // 6 = size of stacks array
  cout << sizeof(ps) << " = size of ps pointer\n";
  // 8 = size of ps pointer
  ```

  - 指针长度的解释

    1. 操作系统有32/64位之分，但同时CPU也有32/64位之分(Windows 在cmd终端下用 systeminfo 命令可以查看自己的操作系统以及cpu位数)；

    2. 32位CPU只能安装32位系统，64位CPU可以安装32位操作系统，也可以安装64位操作系统；

    3. 一般来说，在64位系统下，指针长度为8，32位系统下，指针长度位4；但是有的编译器为了不同的操作系统之间相互兼容，内部对指针进行了包装，使得不管在64位还是32位系统下，指针都是4个字节长度。

    4. 64位系统，这个位数指的是CPU里面的通用寄存器的数据宽度为64位，也就是说一个地址占二进制位数是64，而指针其实是一个地址，所以：

       ```c++
       sizeof(double *)==sizeof(int *)==sizeof(char *)==64/8==8
       ```

    5. 这里除以8是因为，我们用sizeof（）计算的是某个数据类型所占的字节个数，用此字节个数来表示这个数据类型的大小 ，而我们都知道，一个字节所占的二进制位为8位，因此才除以8.

    6. 32位系统，同理，一个地址占32位二进制空间:

       ```c++
       sizeof(double *)==sizeof(int *)==sizeof(char *)==32/8==4
       ```

- address

  - 取地址符&的使用

  ```c++
  int donuts = 6;
  double cups = 4.5;
  unsigned cdowns = 5;

  cout << "donuts value = " << donuts << " and donuts address = " << &donuts << endl;
  // donuts value = 6 and donuts address = 0x61fe1c
  cout << "donuts value = " << cdowns << " and donuts address = " << &cdowns << endl;
  // cdowns value = 5 and cdowns address = 0x61fe0c
  cout << "cups value = " << cups << " and cups address = " << &cups << endl;
  // cups value = 4.5 and cups address = 0x61fe10
  ```

- arraynew

  - 动态分配空间与释放

  ```c++
  double *p3 = new double[3]; // space for 3 doubles
  p3[0] = 0.2;                // treat p3 like an array name
  p3[1] = 0.5;
  p3[2] = 0.8;
  cout << "p3[1] is " << p3[1] << ".\n";
  p3 = p3 + 1; // increment the pointer
  // p3[1] is 0.5.

  cout << "Now p3[0] is " << p3[0] << " and " << "p3[1] is " << p3[1] << ".\n";
  // Now p3[0] is 0.5 and p3[1] is 0.8.
  p3 = p3 - 1; // point back to beginning
  delete[] p3;

  // double *p1 = new double;
  // delete p1;
  ```

- arrayone

  - 数组的使用

    数组与指针的差异在于指针和数组储存形式不同

    > 1. 概念
    >
    >    数组：存储连续多个相同类型的数据；
    >
    >    指针：变量，存的是地址
    >
    > 2. 赋值
    >
    >    同类型的指针变量可以相互赋值，数组不行，只能一个一个元素的赋值或拷贝
    >
    > 3. 存储方式
    >
    >    数组：连续内存空间。
    >
    >    指针：灵活，可以指向任意类型的数据。指向的是地址空间的内存。
    >
    > 4. sizeof
    >
    >    数组的sizeof求的是占用的空间（字节）。

  ```c++
  int yams[3]; // creates array with three elements
  yams[0] = 7; // assign value to first element
  yams[1] = 8;
  yams[2] = 6;

  int yamcosts[3] = {20, 30, 5};
  cout << "Total yams = " << yams[0] + yams[1] + yams[2] << endl;
  // Total yams = 21
  cout << "The package with " << yams[1] << " yams costs " << yamcosts[1] << " cents per yam.\n";
  // The package with 8 yams costs 30 cents per yam.
  int total = yams[0] * yamcosts[0] + yams[1] * yamcosts[1];
  total = total + yams[2] * yamcosts[2];

  cout << "The total yam expense is " << total << " cents.\n";
  // The total yam expense is 410 cents.
  cout << "\nSize of yams array = " << sizeof yams << " bytes.\n";
  // Size of yams array = 12 bytes.
  cout << "Size of one element = " << sizeof yams[0] << " bytes.\n";
  // Size of one element = 4 bytes.
  ```

- arrstruct

  - 结构体的创建

  ```c++
  struct inflatable
  {
      char name[20];
      float volume;
      double price;
  };
  ```

  - 结构体的使用

  ```c++
  inflatable guests[2] = // initializing an array of structs
      {
          {"Bambi", 0.5, 21.99},     // first structure in array
          {"Godzilla", 2000, 565.99} // next structure in array
      };
  inflatable myguest = {"Jack", 2200, 234};
  cout << "The guests " << guests[0].name << " and " << guests[1].name << " and " << myguest.name
      // The guests Bambi and Godzilla and Jack
       << "\nhave a combined volume of " << guests[0].volume + guests[1].volume + myguest.volume << " cubic feet.\n";
      // have a combined volume of 4200.5 cubic feet.
  ```

- assgn_st

  - 结构体的赋值

  ```c++
  inflatable bouquet = {"sunflowers", 0.20, 12.49};
  inflatable choice;
  cout << "bouquet: " << bouquet.name << " for $" << bouquet.price << endl;
  // bouquet: sunflowers for $12.49

  choice = bouquet; // assign one structure to another
  cout << "choice: " << choice.name << " for $" << choice.price << endl;
  // choice: sunflowers for $12.49
  ```

- choices

  - \<vector\>的使用

  ```c++
  #include <vector> // STL C++98
  vector<double> a2(4); // create vector with 4 elements
                        // no simple way to initialize in C98
  a2[0] = 1.0 / 3.0;
  a2[1] = 1.0 / 5.0;
  a2[2] = 1.0 / 7.0;
  a2[3] = 1.0 / 9.0;
  cout << "a2[2]: " << a2[2] << " at " << &a2[2] << endl;
  // a2[2]: 0.142857 at 0xff1340
  ```

  - \<array\>的使用

    赋值为软赋值（地址不同）

  ```c++
  #include <array>  // C++0x
  // C++0x -- create and initialize array object
  array<double, 4> a3 = {3.14, 2.72, 1.62, 1.41};
  array<double, 4> a4;
  a4 = a3; // valid for array objects of same size
           // use array notation
  cout << "a3[2]: " << a3[2] << " at " << &a3[2] << endl;
  // a3[2]: 1.62 at 0x61fdb0
  cout << "a4[2]: " << a4[2] << " at " << &a4[2] << endl;
  // a4[2]: 1.62 at 0x61fd90
  ```

  - 对比简单数组

    c++数组是不会检查越界的，java/OC中会检查

    同时c++数组下标可以为负，相当于指针迭代改变，不初始化取值为乱码

  ```c++
  double a1[4] = {1.2, 2.4, 3.6, 4.8};
  cout << "a1[2]: " << a1[2] << " at " << &a1[2] << endl;
  // a1[2]: 3.6 at 0x61fdf0
  a1[-2] = 20.2;
  cout << "a1[-2]: " << a1[-2] << " at " << &a1[-2] << endl;
  // a1[-2]: 20.2 at 0x61fdd0
  ```

- delete

  - 指针函数的使用

  - new、delete的使用

  - \<cstring\>的srelen,srecpy使用

    strlen(a)：函数，返回字符串a的长度，不包括null，取未初始化字符串时值不定

    strcpy(a)：单目运算符，参数可以是数组、指针、类型、对象、函数等，当值是字符串时，包含null

  ```c++
  #include <cstring> // or string.h
  char *getname(void);
  main()
  {
      char *name; // create pointer but no storage

      name = getname(); // assign address of string to name
      cout << name << " at " << (int *)name << "\n";
      delete[] name; // memory freed

      name = getname(); // reuse freed memory
      cout << name << " at " << (int *)name << "\n";
      delete[] name;
  }

  char *getname() // return pointer to new string
  {
      char temp[80]; // temporary storage
      cout << "Enter last name: ";
      cin >> temp;
      char *pn = new char[strlen(temp) + 1];
      strcpy(pn, temp); // copy string into smaller space

      return pn; // temp lost when function ends
  }
  ```

  当char \*name第二次再使用时替换成char \*name_1也不会出现地址不同

  ```cmd
  Enter last name: Jack
  Jack at 0xe55f90
  Enter last name: Liu
  Liu at 0xe55f90
  ```

- init_ptr

  - 指针*和取地址符&的使用

  ```c++
  int higgens = 5;
  int *pt = &higgens;

  cout << "Value of higgens = " << higgens << "; Address of higgens = " << &higgens << endl;
  // Value of higgens = 5; Address of higgens = 0x61fe14
  cout << "Value of *pt = " << *pt << "; Value of pt = " << pt << endl;
  // Value of *pt = 5; Value of pt = 0x61fe14
  ```

- instr1

  - char数组的定义及使用

  ```c++
  const int ArSize = 20;
  char name[ArSize];
  char dessert[ArSize];

  cout << "Enter your name:\n";
  cin >> name;
  cout << "Enter your favorite dessert:\n";
  cin >> dessert;
  cout << "I have some delicious " << dessert << " for you, " << name << ".\n";
  ```

  - cin的使用

    - **cin不会读入空格，\t，\n（跳过，但流指针还在开头）**

    - 另外还有geyline(流，string)的用法
    - cin.ignore()可以防止cin.get()不读\n的影响（清空缓冲区）

  ```cmd
  Enter your name:
  Jack Liu
  Enter your favorite dessert:
  I have some delicious Liu for you, Jack.
  ```

- instr2

  - cin.getline()的使用

  ```c++
  const int ArSize = 20;
  char name[ArSize];
  char dessert[ArSize];

  cout << "Enter your name:\n";
  cin.getline(name, ArSize); // reads through newline
  cout << "Enter your favorite dessert:\n";
  cin.getline(dessert, ArSize);
  cout << "I have some delicious " << dessert << " for you, " << name << ".\n";
  ```

  - **cin.getline()函数读入一行字符（流指针指向下一个字符）**

    getline函数的作用是从输入流中读取一行字符,其用法与带3个参数的cin.get()类似。即cin.getline(字符数组(或字符指针), 字符个数n, 终止标志字符)，终止标志字符默认为'\n'。读\n

  ```cmd
  Enter your name:
  Liu Jack
  Enter your favorite dessert:
  sdcxas
  I have some delicious sdcxas for you, Liu Jack.
  ```

- instr3

  - cin.get()的使用

  ```c++
  const int ArSize = 20;
  char name[ArSize];
  char dessert[ArSize];

  cout << "Enter your name:\n";
  cin.get(name, ArSize).get(); // read string, newline
  cout << "Enter your favorite dessert:\n";
  cin.get(dessert, ArSize).get();
  cout << "I have some delicious " << dessert << " for you, " << name << ".\n";
  ```

  - **cin.get()用来从指定的输入流中提取一个字符（包括空白字符），函数的返回值就是读入的字符**

    若遇到输入流中的文件结束符，则函数值返回文件结束标志EOF(End Of File)，一般以-1代表EOF，用-1而不用0或正值，是考虑到不与字符的ASCII代码混淆，但不同的C ++系统所用的EOF值有可能不同,windows系统中用Ctrl+Z来表示EOF。

  - **cin.get(ch)其作用是从输入流中读取一个字符，赋给字符变量ch**

    如果读取成功则函数返回true(真)，如失败(遇文件结束符) 则函数返回false(假)。

  - **cin.get(字符数组, 字符个数n, 终止字符)或cin.get(字符指针, 字符个数n, 终止字符)**
    其作用是从输入流中读取n-1个字符，赋给指定的字符数组(或字符指针指向的数组)，如果在读取n-1个字符之前遇到指定的终止字符，则提前结束读取。如果读取成功则函数返回true(真)，如失败(遇文件结束符) 则函数返回false(假)。

  ```cmd
  Enter your name:
  liu jack
  Enter your favorite dessert:
  asdc
  I have some delicious asdc for you, liu jack.
  ```

  可以看到使用了cin.get().get()，这是在读取一行的时候读取'\n'，但getline没有这个限制

- mixtypes

  - 结构体指针

    ```c++
    struct antarctica_years_end
    {
        int year;
        /* some really interesting data, etc. */
    };
    antarctica_years_end *pa;
    ```

    antarctica_years_end是结构体。

    调用使用pa->year。

  - std::的使用

    ```c++
    using namespace std;
    ```

    - **所谓namespace，是指标识符的各种可见范围**

      C＋＋标准程序库中的所有标识符都被定义于一个名为std的namespace中。

    - 当使用\<iostream.h\>时，相当于在c中调用库函数，使用的是全局命名空间，也就是早期的c++实现；

      当使用\<iostream\>的时候，该头文件没有定义全局命名空间，必须使用namespace std；这样才能正确使用cout。

    - 也可以引用你自己的名字空间。比如说：

      ```c++
      import "C:\\MyTest\\test.tlb"
      using namespace CMyTest
      ```

      就可以引用CMyTest内的各个类型名

    - 当两个文件内含名字冲突时，使用

      ```c++
      // txt1.h
      namespace MyNamespace1{
          class S{
              ..
          }
      };
      // txt2.h
      namespace MyNamespace2{
          class S{
              ..
          }
      };

      main(){
          MyNamespace1::S A;
          MyNamespace2::S B;
      }
      ```

    - 尽量不要使用

      ```c++
      using namespace std;
      ```

      因为当你定义的名字与命名空间std里面的名字重名时，会发生重定向错误。

  - 指针数组和数组指针的区别

    - 数组指针和指针数组在处理同一个二维数组时，数组指针的元素个数和指针数组的数组长度不相同，

      数组指针的元素个数和二维数组的列长度相同;

      而指针数组的数组长度和二维数组的行长度相同。

      ```c++
      antarctica_years_end s01, s02, s03;
      s01.year = 1998;
      antarctica_years_end *pa = &s02;
      pa->year = 1999;
      antarctica_years_end trio[3]; // array of 3 structures
      trio[0].year = 2003;
      const antarctica_years_end arp1[3] = {s01, s02, s03};
      ```

    - 一维指针

      ```c++
      std::cout << trio->year << std::endl;
      // 2003
      const antarctica_years_end *arp2 = arp1;
      std::cout << (arp2 + 1)->year << std::endl;
      // 1999
      ```

    - 指针数组

      - 指针指向数组首元素的首地址（列指针）

        ```c++
        const antarctica_years_end *arp[3] = {&s01, &s02, &s03};
        std::cout << (*(arp + 1))->year << std::endl;
        // 1999
        ```

    - 数组指针

      - 指针指向数组首地址（行指针）

        ```c++
        const antarctica_years_end(*arp3)[3] = &arp1;
        const antarctica_years_end arp4[][3] = {s01, s02, s03};
        std::cout << ((*arp3) + 1)->year << std::endl;
        // 1999
        std::cout << ((*arp4) + 1)->year << std::endl;
        // 1999
        ```

    - 二维指针

      ```c++
      const antarctica_years_end **ppa = arp;
      auto ppb = arp; // C++0x automatic type deduction
                      // or else use const antarctica_years_end ** ppb = arp;
      std::cout << (*ppa)->year << std::endl;
      // 1998
      std::cout << (*(ppb + 1))->year << std::endl;
      // 1999
      ```

- newstrct

  - 指针->和.的使用

    ```c++
    struct inflatable // structure definition
    {
        char name[20];
        float volume;
        double price;
    };

    main(){
        inflatable *ps = new inflatable; // allot memory for structure
        cout << "Enter name of inflatable item: ";
        cin.get(ps->name, 20); // method 1 for member access
        cout << "Enter volume in cubic feet: ";
        cin >> (*ps).volume; // method 2 for member access
        cout << "Enter price: $";
        cin >> ps->price;
        cout << "Name: " << (*ps).name << endl;              // method 2
        cout << "Volume: " << ps->volume << " cubic feet\n"; // method 1
        cout << "Price: $" << ps->price << endl;             // method 1
        delete ps;
    }
    ```

    ```cmd
    Enter name of inflatable item: liu jack
    Enter volume in cubic feet: 33
    Enter price: $57
    Name: liu jack
    Volume: 33 cubic feet
    Price: $57
    ```

- numstr

  - cin.get()和cin.getline()的区别

    ```c++
    cout << "What year was your house built?\n";
    int year;
    cin >> year;
    cin.get();
    cout << "What is its street address?\n";
    char address[80];
    cin.getline(address, 80);
    cout << "Year built: " << year << endl;
    cout << "Address: " << address << endl;
    cout << "Done!\n";
    ```

    ```cmd
    What year was your house built?
    2007
    What is its street address?
    dsvsdv
    Year built: 2007
    Address: dsvsdv
    Done!
    ```

- pointer

  - 指针的意义

    ```c++
    int updates = 6; // declare a variable
    int *p_updates;  // declare pointer to an int
    p_updates = &updates; // assign address of int to pointer
    // express values two ways
    cout << "Values: updates = " << updates << ", *p_updates = " << *p_updates << endl;
    // express address two ways
    cout << "Addresses: &updates = " << &updates << ", p_updates = " << p_updates << endl;
    // use pointer to change value
    *p_updates = *p_updates + 1;
    cout << "Now updates = " << updates << endl;
    ```

    ```cmd
    Values: updates = 6, *p_updates = 6
    Addresses: &updates = 0x61fe14, p_updates = 0x61fe14
    Now updates = 7
    ```

- ptrstr

  - strcpy()的含义

    ```c++
    char animal[20] = "bear";  // animal holds bear
    const char *bird = "wren"; // bird holds address of string
    char *ps;                  // uninitialized
    cout << animal << " and " << bird << "\n"; // display wren
    // cout << ps << "\n";      //may display garbage, may cause a crash
    cout << "Enter a kind of animal: ";
    cin >> animal; // ok if input < 20 chars
    // cin >> ps; Too horrible a blunder to try; ps doesn't
    //            point to allocated space
    ps = animal;         // set ps to point to string
    cout << ps << "!\n"; // ok, same as using animal
    cout << "Before using strcpy():\n";
    cout << animal << " at " << (int *)animal << endl;
    cout << ps << " at " << (int *)ps << endl;

    ps = new char[strlen(animal) + 1]; // get new storage
    strcpy(ps, animal);                // copy string to new storage
    cout << "After using strcpy():\n";
    cout << animal << " at " << (int *)animal << endl;
    cout << ps << " at " << (int *)ps << endl;
    delete[] ps;
    ```

    ```cmd
    bear and wren
    Enter a kind of animal: cat
    cat!
    Before using strcpy():
    cat at 0x61fdf0
    cat at 0x61fdf0
    After using strcpy():
    cat at 0x61fdf0
    cat at 0xea5f90
    ```

    说明strcpy()另外创建了内存，进行软复制

- strings

  - sizeof()与strlen()的区别

  - cout()的输出遇\0阻断

    ```c++
    const int Size = 15;
    char name1[Size];              // empty array
    char name2[Size] = "C++owboy"; // initialized array
    // NOTE: some implementations may require the static keyword
    // to initialize the array name2

    cout << "Howdy! I'm " << name2 << "! What's your name?\n";
    cin >> name1;
    cout << "Well, " << name1 << ", your name has " << strlen(name1) << " letters and is stored\n";
    cout << "in an array of " << sizeof(name1) << " bytes.\n";
    cout << "Your initial is " << name1[0] << ".\n";
    name2[3] = '\0'; // set to null character
    cout << "Here are the first 3 characters of my name: " << name2 << endl;
    ```

    ```cmd
    Howdy! I'm C++owboy! What's your name?
    Jack
    Well, Jack, your name has 4 letters and is stored
    in an array of 15 bytes.
    Your initial is J.
    Here are the first 3 characters of my name: C++
    ```

- strtype

  - 字符串与string的相同点

    ```c++
    #include <string>

    char charr1[20];            // create an empty array
    char charr2[20] = "jaguar"; // create an initialized array
    string str1;                // create an empty string object
    string str2 = "panther";    // create an initialized string

    cout << "Enter a kind of feline: ";
    cin >> charr1;
    cout << "Enter another kind of feline: ";
    cin >> str1; // use cin for input
    cout << "Here are some felines:\n";
    cout << charr1 << " " << charr2 << " " << str1 << " " << str2 << endl;
    cout << "The third letter in " << charr2 << " is " << charr2[2] << endl;
    cout << "The third letter in " << str2 << " is " << str2[2] << endl;
    ```

    ```cmd
    Enter a kind of feline: ij
    Enter another kind of feline: sd
    Here are some felines:
    ij jaguar sd panther
    The third letter in jaguar is g
    The third letter in panther is n
    ```

- strtype2

  - string的简单使用

    ```c++
    string s1 = "penguin";
    string s2, s3;

    s2 = s1;
    cout << "s1: " << s1 << ", s2: " << s2 << endl;
    cout << "s2 = \"buzzard\"\n";
    s2 = "buzzard";
    cout << "s2: " << s2 << endl;
    s3 = s1 + s2;
    cout << "s3: " << s3 << endl;
    s1 += s2;
    cout << "s1 += s2 yields s1 = " << s1 << endl;
    s2 += " for a day";
    cout << "s2 += \" for a day\" yields s2 = " << s2 << endl;
    ```

    ```cmd
    s1: penguin, s2: penguin
    s2 = "buzzard"
    s2: buzzard
    s3: penguinbuzzard
    s1 += s2 yields s1 = penguinbuzzard
    s2 += " for a day" yields s2 = buzzard for a day
    ```

    - string可以相互赋值，字符串只能使用strcpy()

    - string可以加string或字符串，但不能减

- strtype3

  - string结合cstring的使用

    ```c++
    char charr1[20];
    char charr2[20] = "jaguar";
    string str1;
    string str2 = "panther";

    // assignment for string objects and character arrays
    str1 = str2;            // copy str2 to str1
    strcpy(charr1, charr2); // copy charr2 to charr1

    // appending for string objects and character arrays
    str1 += " paste";         // add paste to end of str1
    strcat(charr1, " juice"); // add juice to end of charr1

    // finding the length of a string object and a C-style string
    int len1 = str1.size();    // obtain length of str1
    int len2 = strlen(charr1); // obtain length of charr1

    cout << "The string " << str1 << " contains " << len1 << " characters.\n";
    cout << "The string " << charr1 << " contains " << len2 << " characters.\n";
    ```

    ```cmd
    The string panther paste contains 13 characters.
    The string jaguar juice contains 12 characters.
    ```

    - 字符串的拼接

      ```c++
      strcat(a,b)
      ```

    - string的拼接

      ```c++
      a+b
      ```

    - 字符串的长度

      ```c++
      strlen(a)
      ```

    - string的长度

      ```c++
      a.size()
      ```

- strpe4

  - 字符串和string的一些区别

    ```c++
    char charr[20];
    string str;

    cout << "Length of string in charr before input: " << strlen(charr) << endl;
    cout << "Length of string in str before input: " << str.size() << endl;
    cout << "Enter a line of text:\n";
    cin.getline(charr, 20); // indicate maximum length
    cout << "You entered: " << charr << endl;
    cout << "Enter another line of text:\n";
    getline(cin, str); // cin now an argument; no length specifier
    cout << "You entered: " << str << endl;
    cout << "Length of string in charr after input: " << strlen(charr) << endl;
    cout << "Length of string in str after input: " << str.size() << endl;
    ```

    - 未初始化的字符串使用strlen()

      查看内存的值，遇到\0结束，此时的结果没有意义

    - 未初始化的string使用.size()

      动态的分配内存，为0

    - cin.getline()会默认读取一行，包括\n，但要指定长度
    - getline()读取string不需要指定长度

    ```cmd
    Length of string in charr before input: 1
    Length of string in str before input: 0
    Enter a line of text:
    text
    You entered: text
    Enter another line of text:
    text2
    You entered: text2
    Length of string in charr after input: 4
    Length of string in str after input: 5
    ```

- structur

  - 结构体的运用

    ```c++
    struct inflatable // structure declaration
    {
        char name[20];
        float volume;
        double price;
    };
    main(){
        inflatable guest =
            {
                "Glorious Gloria", // name value
                1.88,              // volume value
                29.99              // price value
            };                     // guest is a structure variable of type inflatable
                                   // It's initialized to the indicated values
        inflatable pal =
            {
                "Audacious Arthur",
                3.12,
                32.99 // pal is a second variable of type inflatable
            };
        cout << "Expand your guest list with " << guest.name << " and " << pal.name << "!\n";
        // pal.name is the name member of the pal variable
        cout << "You can have both for $";
        cout << guest.price + pal.price << "!\n";
    }
    ```

    ```cmd
    Expand your guest list with Glorious Gloria and Audacious Arthur!
    You can have both for $62.98!
    ```

- use_new

  - 指针的大小及地址

    ```c++
    int nights = 1001;
    int *pt = new int; // allocate space for an int
    *pt = 1001;        // store a value there

    cout << "nights value = " << nights << ": location " << &nights << endl;
    cout << "int " << "value = " << *pt << ": location = " << pt << endl;

    double *pd = new double; // allocate space for a double
    *pd = 10000001.0;        // store a double there

    cout << "double " << "value = " << *pd << ": location = " << pd << endl;
    cout << "location of pointer pd: " << &pd << endl;
    cout << "size of pt = " << sizeof(pt) << ": size of *pt = " << sizeof(*pt) << endl;
    cout << "size of pd = " << sizeof pd << ": size of *pd = " << sizeof(*pd) << endl;
    delete pd;
    delete pt;
    ```

    可以看到，地址还能被取&，这是因为地址本身也是被作为数据储存的

    ```cmd
    nights value = 1001: location 0x61fe14
    int value = 1001: location = 0x721330
    double value = 1e+007: location = 0x721370
    location of pointer pd: 0x61fe08
    size of pt = 8: size of *pt = 4
    size of pd = 8: size of *pd = 8
    ```
