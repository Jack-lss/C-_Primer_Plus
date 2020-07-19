# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapter 9

- coordin-file1-file2

  - 头文件

    - 包含结构声明和使用这些结构的函数原型
    - 不要将头文件加入项目列表中

    ```c++
    // coordin.h -- structure templates and function prototypes
    // structure templates
    #ifndef COORDIN_H_
    #define COORDIN_H_

    struct polar
    {
        double distance; // distance from origin
        double angle;    // direction from origin
    };
    struct rect
    {
        double x; // horizontal distance from origin
        double y; // vertical distance from origin
    };

    // prototypes
    polar rect_to_polar(rect xypos);
    void show_polar(polar dapos);

    #endif

    ```

    其中

    ```c++
    #ifndef COORDIN_H_
    ...
    #endif
    ```

    表示**仅当前**没有使用预处理器编译指令#define定义名称COORDIN\_H\_时，才处理#ifndef和#endif之间的语句

    编译器首次遇到该文件时，名称COORDIN\_H\_没有定义。这种情况下，编译器将查看#ifndef和#endif之间的内容，并读取定义COORDIN\_H\_的一行。如果在同一个文件中遇到其他包含coordin.h的代码（#include"coordin.h"），编译器将知道COORDIN\_H\_已经被定义，从而跳到#endif后面的一行上。

    - 这种方法并不能防止编译器将文件包含两次，而是让它忽略除第一次包含之外的所有内容（#ifndef和#endif之间的内容）

  - 源代码文件

    - 不要再源代码文件中使用#include包含其他源代码文件

    1. 包含与结构有关的函数的代码

       ```c++
       // file2.cpp -- contains functions called in file1.cpp
       #include <iostream>
       #include <cmath>
       #include "coordin.h" // structure templates, function prototypes

       // convert rectangular to polar coordinates
       polar rect_to_polar(rect xypos)
       {
           using namespace std;
           polar answer;

           answer.distance =
               sqrt(xypos.x * xypos.x + xypos.y * xypos.y);
           answer.angle = atan2(xypos.y, xypos.x);
           return answer; // returns a polar structure
       }

       // show polar coordinates, converting angle to degrees
       void show_polar(polar dapos)
       {
           using namespace std;
           const double Rad_to_deg = 57.29577951;

           cout << "distance = " << dapos.distance;
           cout << ", angle = " << dapos.angle * Rad_to_deg;
           cout << " degrees\n";
       }
       ```

    2. 包含调用与结构相关的函数的代码

       ```c++
       // file1.cpp -- example of a three-file program
       #include <iostream>
       #include "coordin.h" // structure templates, function prototypes
       using namespace std;
       int main()
       {
           rect rplace;
           polar pplace;

           cout << "Enter the x and y values: ";
           while (cin >> rplace.x >> rplace.y) // slick use of cin
           {
               pplace = rect_to_polar(rplace);
               show_polar(pplace);
               cout << "Next two numbers (q to quit): ";
           }
           cout << "Bye!\n";
           // keep window open in MSVC++
           /*
           cin.clear();
           while (cin.get() != '\n')
               continue;
           cin.get();
       */
           system("pause");
           return 0;
       }
       ```

  - 程序

    - 编译

      > 用指定编译器将源代码生成二进制文件，在Windows下时.obj文件，在UNIX/LINUX是.o文件。
      >
      > **注意**：编译时，需要源码语法正确，函数与变量的声明正确，编译器只检查程序语法、函数和变量是否声明，函数不需被定义

      ```g++
      g++ -c file1.cpp file2.cpp coordin.h
      ```

      此命令将生成file1.o，file2.o，coordin.gch目标文件

    - 链接

      > 找到所需要用到的函数所在的目标文件，将它们链接在一起合成可执行文件。

      ```g++
      g++ file1.o file2.o coordin.gch -o file.exe
      ```

      此命令将生成可执行文件，-o指定可执行文件名称

    - 编译-链接

      通常编译和链接可以一起使用

      ```g++
      g++ file1.cpp file2.cpp coordin.h -o file.exe
      ```

    - 库
    - 在编译时链接库

- autoscp

  ```c++
  void oil(int x);
  int main()
  {
      using namespace std;

      int texas = 31;
      int year = 2011;
      cout << "In main(), texas = " << texas << ", &texas = " << &texas << endl;
      // In main(), texas = 31, &texas = 0x61fe1c
      cout << "In main(), year = " << year << ", &year = " << &year << endl;
      // In main(), year = 2011, &year = 0x61fe18
      oil(texas);
      cout << "In main(), texas = " << texas << ", &texas = " << &texas << endl;
      // In main(), texas = 31, &texas = 0x61fe1c
      cout << "In main(), year = " << year << ", &year = " << &year << endl;
      // In main(), year = 2011, &year = 0x61fe18
      // cin.get();
      system("pause");
      return 0;
  }

  void oil(int x)
  {
      using namespace std;
      int texas = 5;

      cout << "In oil(), texas = " << texas << ", &texas = " << &texas << endl;
      // In oil(), texas = 5, &texas = 0x61fddc
      cout << "In oil(), x = " << x << ", &x = " << &x << endl;
      // In oil(), x = 31, &x = 0x61fdf0
      { // start a block
          int texas = 113;
          cout << "In block, texas = " << texas << ", &texas = " << &texas << endl;
          // In block, texas = 113, &texas = 0x61fdd8
          cout << "In block, x = " << x << ", &x = " << &x << endl;
          // In block, x = 31, &x = 0x61fdf0
      } // end a block
      cout << "Post-block texas = " << texas << ", &texas = " << &texas << endl;
      // Post-block texas = 5, &texas = 0x61fddc
  }
  ```

  oil函数中，内部代码的新定义的texas内存可见，离开代码块时，外部代码内存可见

- external-support

  ```c++
  // external.cpp -- external variable
  // compile with support.cpp
  #include <iostream>
  // external variable
  double warming = 0.3; // warming defined

  // function prototypes
  void update(double dt);
  void local();

  int main() // uses global variable
  {
      using namespace std;
      cout << "Global warming is " << warming << " degrees.\n";
      update(0.1); // call function to change warming
      cout << "Global warming is " << warming << " degrees.\n";
      local(); // call function with local warming
      cout << "Global warming is " << warming << " degrees.\n";
      // cin.get();
      system("pause");
      return 0;
  }
  ```

  ```c++
  // support.cpp -- use external variable
  // compile with external.cpp
  #include <iostream>
  extern double warming; // use warming from another file

  // function prototypes
  void update(double dt);
  void local();

  using std::cout;
  void update(double dt) // modifies global variable
  {
      extern double warming; // optional redeclaration
      warming += dt;         // uses global warming
      cout << "Updating global warming to " << warming;
      cout << " degrees.\n";
  }

  void local() // uses local variable
  {
      double warming = 0.8; // new variable hides external one

      cout << "Local warming = " << warming << " degrees.\n";
      // Access global variable with the
      // scope resolution operator
      cout << "But global warming = " << ::warming;
      cout << " degrees.\n";
  }
  ```

  ```cmd
  Global warming is 0.3 degrees.
  Updating global warming to 0.4 degrees.
  Global warming is 0.4 degrees.
  Local warming = 0.8 degrees.
  But global warming = 0.4 degrees.
  Global warming is 0.4 degrees.
  ```

  - 单定义规则

    external中，warming定义如下：

    ```c++
    double warming = 0.3;
    ```

    support中，使用关键字extern声明变量warming，让该文件中的函数能使用它：

    ```c++
    extern double warming;
    ```

    而在update函数中重新声明了该变量，即通过这个名称使用外部定义的变量。（可选）

    注意到

    ```c++
    cout << "But global warming = " << ::warming;
    ```

    ::warming说明将使用全局变量

- twofile1-twofile2

  - 使用全局变量和全局静态变量

  ```c++
  // twofile1.cpp -- variables with external and internal linkage
  #include <iostream>     // to be compiled with two file2.cpp
  int tom = 3;            // external variable definition
  int dick = 30;          // external variable definition
  static int harry = 300; // static, internal linkage
  // function prototype
  void remote_access();

  int main()
  {
      using namespace std;
      cout << "main() reports the following addresses:\n";
      cout << &tom << " = &tom, " << &dick << " = &dick, ";
      cout << &harry << " = &harry\n";
      remote_access();
      // cin.get();
      system("pause");
      return 0;
  }
  ```

  ```c++
  // twofile2.cpp -- variables with internal and external linkage
  #include <iostream>
  extern int tom;       // tom defined elsewhere
  static int dick = 10; // overrides external dick
  int harry = 200;      // external variable definition,
                        // no conflict with twofile1 harry

  void remote_access()
  {
      using namespace std;

      cout << "remote_access() reports the following addresses:\n";
      cout << &tom << " = &tom, " << &dick << " = &dick, ";
      cout << &harry << " = &harry\n";
  }
  ```

  ```cmd
  main() reports the following addresses:
  0x403010 = &tom, 0x403014 = &dick, 0x403018 = &harry
  remote_access() reports the following addresses:
  0x403010 = &tom, 0x403020 = &dick, 0x403024 = &harry
  ```

- static

  - 局部静态变量

  ```c++
  // static.cpp -- using a static local variable
  #include <iostream>
  // constants
  const int ArSize = 10;

  // function prototype
  void strcount(const char *str);

  int main()
  {
      using namespace std;
      char input[ArSize];
      char next;

      cout << "Enter a line:\n";
      cin.get(input, ArSize);
      while (cin)
      {
          cin.get(next);
          while (next != '\n') // string didn't fit!
              cin.get(next);   // dispose of remainder
          strcount(input);
          cout << "Enter next line (empty line to quit):\n";
          cin.get(input, ArSize);
      }
      cout << "Bye\n";
      // code to keep window open for MSVC++
      /*
  cin.clear();
      while (cin.get() != '\n')
          continue;
      cin.get();
  */
      system("pause");
      return 0;
  }

  void strcount(const char *str)
  {
      using namespace std;
      static int total = 0; // static local variable
      int count = 0;        // automatic local variable

      cout << "\"" << str << "\" contains ";
      while (*str++) // go to end of string
          count++;
      total += count;
      cout << count << " characters\n";
      cout << total << " characters total\n";
  }
  ```

  ```cmd
  Enter a line:
  efvdssdvc
  "efvdssdvc" contains 9 characters
  9 characters total
  Enter next line (empty line to quit):
  dsss
  "dsss" contains 4 characters
  13 characters total
  Enter next line (empty line to quit):
  ewfdsf sd.
  "ewfdsf sd" contains 9 characters
  22 characters total
  Enter next line (empty line to quit):

  Bye
  ```

- newpalce

  - new和new[]

    - new将调用

      ```c++
      void * operator new(std::size_t);
      ```

    - new []将调用

      ```c++
      void * operator new[](std::size_t);
      ```

  - delete和delete[]

    - delete将调用

      ```c++
      void operator delete(void *);
      ```

    - delete[]将调用

      ```c++
      void operator delete[](void *);
      ```

  从以上，发现

  ```c++
  int * pi = new int;
  ```

  可以转换成

  ```c++
  int * pi = new(sizeof(int));
  ```

  而

  ```c++
  int * pa = new int[40];
  ```

  可以传换成

  ```c++
  int * pa = new(40 * sizeof(int));
  ```

  ```c++
  // newplace.cpp -- using placement new
  #include <iostream>
  #include <new> // for placement new
  const int BUF = 512;
  const int N = 5;
  char buffer[BUF]; // chunk of memory
  int main()
  {
      using namespace std;

      double *pd1, *pd2;
      int i;
      cout << "Calling new and placement new:\n";
      pd1 = new double[N];          // use heap
      pd2 = new (buffer) double[N]; // use buffer array
      for (i = 0; i < N; i++)
          pd2[i] = pd1[i] = 1000 + 20.0 * i;
      cout << "Memory addresses:\n"
           << "  heap: " << pd1
           << "  static: " << (void *)buffer << endl;
      cout << "Memory contents:\n";
      for (i = 0; i < N; i++)
      {
          cout << pd1[i] << " at " << &pd1[i] << "; ";
          cout << pd2[i] << " at " << &pd2[i] << endl;
      }

      cout << "\nCalling new and placement new a second time:\n";
      double *pd3, *pd4;
      pd3 = new double[N];          // find new address
      pd4 = new (buffer) double[N]; // overwrite old data
      for (i = 0; i < N; i++)
          pd4[i] = pd3[i] = 1000 + 40.0 * i;
      cout << "Memory contents:\n";
      for (i = 0; i < N; i++)
      {
          cout << pd3[i] << " at " << &pd3[i] << "; ";
          cout << pd4[i] << " at " << &pd4[i] << endl;
      }

      cout << "\nCalling new and placement new a third time:\n";
      delete[] pd1;
      pd1 = new double[N];
      pd2 = new (buffer + N * sizeof(double)) double[N];
      for (i = 0; i < N; i++)
          pd2[i] = pd1[i] = 1000 + 60.0 * i;
      cout << "Memory contents:\n";
      for (i = 0; i < N; i++)
      {
          cout << pd1[i] << " at " << &pd1[i] << "; ";
          cout << pd2[i] << " at " << &pd2[i] << endl;
      }
      delete[] pd1;
      delete[] pd3;
      // cin.get();
      system("pause");
      return 0;
  }
  ```

  ```cmd
  Calling new and placement new:
  Memory addresses:
    heap: 0x1913c0  static: 0x408040
  Memory contents:
  1000 at 0x1913c0; 1000 at 0x408040
  1020 at 0x1913c8; 1020 at 0x408048
  1040 at 0x1913d0; 1040 at 0x408050
  1060 at 0x1913d8; 1060 at 0x408058
  1080 at 0x1913e0; 1080 at 0x408060

  Calling new and placement new a second time:
  Memory contents:
  1000 at 0x1917f0; 1000 at 0x408040
  1040 at 0x1917f8; 1040 at 0x408048
  1080 at 0x191800; 1080 at 0x408050
  1120 at 0x191808; 1120 at 0x408058
  1160 at 0x191810; 1160 at 0x408060

  Calling new and placement new a third time:
  Memory contents:
  1000 at 0x1913c0; 1000 at 0x408068
  1060 at 0x1913c8; 1060 at 0x408070
  1120 at 0x1913d0; 1120 at 0x408078
  1180 at 0x1913d8; 1180 at 0x408080
  1240 at 0x1913e0; 1240 at 0x408088
  ```

  注意到

  ```c++
  pd2 = new (buffer) double[N];
  ```

  确实将pd2数组放到了buffer中，但是他们的类型不同，buffer是char*，pd2是double指针。

  在第二次使用

  ```c++
  pd2 = new (buffer) double[N];
  ```

  地址依旧不变，在第三次时，给了buffer偏移量，致使pd2分配到了新的内存

  值得注意的是，不能使用

  ```c++
  delete [] pd2;
  ```

  因为pd2创建的实际上是静态地址

- namesp-usenmsp

  - 头文件定义两个名称空间

    ```c++
    // namesp.h
    #include <string>
    // create the pers and debts namespaces
    namespace pers
    {
        struct Person
        {
            std::string fname;
            std::string lname;
        };
        void getPerson(Person &);
        void showPerson(const Person &);
    } // namespace pers

    namespace debts
    {
        using namespace pers;
        struct Debt
        {
            Person name;
            double amount;
        };

        void getDebt(Debt &);
        void showDebt(const Debt &);
        double sumDebts(const Debt ar[], int n);
    } // namespace debts
    ```

  - 源文件提供对头文件函数的定义

    ```c++
    // namesp.cpp -- namespaces
    #include <iostream>
    #include "namesp.h"

    namespace pers
    {
        using std::cin;
        using std::cout;
        void getPerson(Person &rp)
        {
            cout << "Enter first name: ";
            cin >> rp.fname;
            cout << "Enter last name: ";
            cin >> rp.lname;
        }

        void showPerson(const Person &rp)
        {
            std::cout << rp.lname << ", " << rp.fname;
        }
    } // namespace pers

    namespace debts
    {
        void getDebt(Debt &rd)
        {
            getPerson(rd.name);
            std::cout << "Enter debt: ";
            std::cin >> rd.amount;
        }

        void showDebt(const Debt &rd)
        {
            showPerson(rd.name);
            std::cout << ": $" << rd.amount << std::endl;
        }

        double sumDebts(const Debt ar[], int n)
        {
            double total = 0;
            for (int i = 0; i < n; i++)
                total += ar[i].amount;
            return total;
        }
    } // namespace debts
    ```

  - 使用名称空间中声明和定义的结构和函数

    - 导入函数名称，如果函数被重载，将导入所有函数

    ```c++
    // usenmsp.cpp -- using namespaces
    #include <iostream>
    #include "namesp.h"

    void other(void);
    void another(void);
    int main(void)
    {
        using debts::Debt;
        using debts::showDebt;
        Debt golf = {{"Benny", "Goatsniff"}, 120.0};
        showDebt(golf);
        other();
        another();
        // std::cin.get();
        // std::cin.get();
        system("pause");
        return 0;
    }

    void other(void)
    {
        using std::cout;
        using std::endl;
        using namespace debts;
        Person dg = {"Doodles", "Glister"};
        showPerson(dg);
        cout << endl;
        Debt zippy[3];
        int i;

        for (i = 0; i < 3; i++)
            getDebt(zippy[i]);

        for (i = 0; i < 3; i++)
            showDebt(zippy[i]);
        cout << "Total debt: $" << sumDebts(zippy, 3) << endl;

        return;
    }

    void another(void)
    {
        using pers::Person;
        ;

        Person collector = {"Milo", "Rightshift"};
        pers::showPerson(collector);
        std::cout << std::endl;
    }
    ```

    值得注意的几点

    - 如果开发一个函数库或类库，将其放到一个名称空间中
    - 不要在头文件使用using编译指令。
