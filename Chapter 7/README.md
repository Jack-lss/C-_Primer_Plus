# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## Chapter 7

- calling

  - void()函数的简单使用

    ```c++
    main() will call the simple() function:
    I'm but a simple function.
    main() is finished with the simple() function.
    ```

- protos

  ```c++
  void cheers(int);      // prototype: no return value
  double cube(double x); // prototype: returns a double
  int main()
  {
      using namespace std;
      cheers(5); // function call
      cout << "Give me a number: ";
      double side;
      cin >> side;
      double volume = cube(side); // function call
      cout << "A " << side << "-foot cube has a volume of ";
      cout << volume << " cubic feet.\n";
      cheers(cube(2)); // prototype protection at work
      // cin.get();
      // cin.get();
      system("pause");
      return 0;
  }

  void cheers(int n)
  {
      using namespace std;
      for (int i = 0; i < n; i++)
          cout << "Cheers! ";
      cout << endl;
  }

  double cube(double x)
  {
      return x * x * x;
  }
  ```

  - 函数原型(声明)语法
    1. **函数声明所带参数，可以只需要类型，而不需要名**
    2. **函数定义所带参数，必须要类型和名**
    3. **函数声明和定义中的变量名不需要一致**

  - 参数类型转换
    1. 当有意义时，外部传给函数的参数类型，将转换为相应的函数参数类型
    2. 当有意义时，函数内部返回值类型，将转换为函数类型

  ```cmd
  Cheers! Cheers! Cheers! Cheers! Cheers!
  Give me a number: 5
  A 5-foot cube has a volume of 125 cubic feet.
  Cheers! Cheers! Cheers! Cheers! Cheers! Cheers! Cheers! Cheers!
  ```

- twoarg

  ```c++
  void n_chars(char, int);
  int main()
  {
      int times;
      char ch;

      cout << "Enter a character: ";
      cin >> ch;
      while (ch != 'q') // q to quit
      {
          cout << "Enter an integer: ";
          cin >> times;
          n_chars(ch, times); // function with two arguments
          cout << "\nEnter another character or press the"
                  " q-key to quit: ";
          cin >> ch;
      }
      cout << "The value of times is " << times << ".\n";
      cout << "Bye\n";
      // cin.get();
      // cin.get();
      system("pause");
      return 0;
  }

  void n_chars(char c, int n) // displays c n times
  {
      while (n-- > 0) // continue until n reaches 0
          cout << c;
  }
  ```

  ```cmd
  Enter a character: d
  Enter an integer: 2
  dd
  Enter another character or press the q-key to quit: d
  Enter an integer: 3
  ddd
  Enter another character or press the q-key to quit: q
  The value of times is 3.
  Bye
  ```

  不用cin.get()是因为它读换行符

- lotto

  ```c++
  long double probability(unsigned numbers, unsigned picks);
  int main()
  {
      using namespace std;
      double total, choices;
      cout << "Enter the total number of choices on the game card and\n"
              "the number of picks allowed:\n";
      while ((cin >> total >> choices) && choices <= total)
      {
          cout << "You have one chance in ";
          cout << probability(total, choices); // compute the odds
          cout << " of winning.\n";
          cout << "Next two numbers (q to quit): ";
      }
      cout << "bye\n";
      // cin.get();
      // cin.get();
      system("pause");
      return 0;
  }

  // the following function calculates the probability of picking picks
  // numbers correctly from numbers choices
  long double probability(unsigned numbers, unsigned picks)
  {
      long double result = 1.0; // here come some local variables
      long double n;
      unsigned p;

      for (n = numbers, p = picks; p > 0; n--, p--)
          result = result * n / p;
      return result;
  }
  ```

  $$
  \mathbf{R} = \mathbf{C}_{numbers}^{picks}
  $$

  ```cmd
  Enter the total number of choices on the game card and
  the number of picks allowed:
  49 6
  You have one chance in 1.39838e+007 of winning.
  Next two numbers (q to quit): 51 6
  You have one chance in 1.80095e+007 of winning.
  Next two numbers (q to quit): 38 6
  You have one chance in 2.76068e+006 of winning.
  Next two numbers (q to quit): q
  bye
  ```

- arrfun1

  - 函数调用

  ```c++
  int sum = sum_arr(cookies, ArSize);
  ```

- arrfun2

  - 对数组使用sizeof

    ```c++
    int sum_arr(int arr[], int n){...}
    std::cout << sizeof arr << " = sizeof arr\n";
    ```

    这里返回的是指针的长度

    ```c++
    int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};
    std::cout << sizeof cookies << " = sizeof cookies\n";
    ```

    这里返回的是数组的长度

  - 不要试图在函数参数中直接给出数组的大小

    ```c++
    int sum_arr(int arr[], int n);
    ```

    这样的数组传递比较好

- arrfun3

  - const保护内容

    c++将声明const double ar[]解释为const double *ar;

    ```c++
    void show_array(const double ar[], int n);
    ```

    这样将不允许函数内改变ar数组的值，比如这样是会报错的：

    ```c++
    ar[0] += 1.2;
    ```

- arrfun4

  ```c++
  const int ArSize = 8;
  int sum_arr(const int *begin, const int *end);
  int main()
  {
      using namespace std;
      int cookies[ArSize] = {1, 2, 4, 8, 16, 32, 64, 128};
      //  some systems require preceding int with static to
      //  enable array initialization

      int sum = sum_arr(cookies, cookies + ArSize);
      cout << "Total cookies eaten: " << sum << endl;
      sum = sum_arr(cookies, cookies + 3); // first 3 elements
      cout << "First three eaters ate " << sum << " cookies.\n";
      sum = sum_arr(cookies + 4, cookies + 8); // last 4 elements
      cout << "Last four eaters ate " << sum << " cookies.\n";
      // cin.get();
      system("pause");
      return 0;
  }

  // return the sum of an integer array
  int sum_arr(const int *begin, const int *end)
  {
      const int *pt;
      int total = 0;

      for (pt = begin; pt != end; pt++)
          total = total + *pt;
      return total;
  }
  ```

  ```cmd
  Total cookies eaten: 255
  First three eaters ate 7 cookies.
  Last four eaters ate 240 cookies.
  ```

  1. 可改变地址

  ```c++
  const int *pt;
  ```

  2. 可改变值

  ```c++
  int *const pt
  ```

  3. 地址和值都不可改变

  ```c++
  const int * const pt;
  ```

  - const将指针本身声明为常量

    ```c++
    int age = 39;
    const int * pt = &age;
    ```

    该声明指出，pt指向一个const int，因此不能使用pt来修改这个值。

    但age不是常量，所以可以

    ```c++
    age = 20;
    ```

    但不能

    ```c++
    *pt = 20;
    ```

  - 不能将const的地址赋给常规地址

    可行的：

    ```c++
    const float g_earth = 9.80;
    const float * pe =&g_earth;
    ```

    不可行的：

    ```c++
    const float g_moom = 1.63;
    float *pm = &g_moom;
    ```

  - 对于二级间接关系，不能将非const指针赋给const指针

    对于一级间接关系，能将非const指针赋给const指针：

    ```c++
    int age = 39; // age++可行
    int * pd = &age; // *pd = 41; 可行
    const int * pt = pd; // *pt = 42；不可行
    ```

    不能这样：

    ```c++
    const int **pp2;
    int *p1;
    const int n = 13;
    pp2 = &p1;
    *pp2 = &n;
    *p1 = 10;
    ```

    这里相当于使用p1来修改const的数据

- strgfun

  ```c++
  unsigned int c_in_str(const char *str, char ch);
  int main()
  {
      using namespace std;
      char mmm[15] = "minimum"; // string in an array
                                // some systems require preceding char with static to
                                // enable array initialization

      char *wail = "ululate"; // wail points to string

      unsigned int ms = c_in_str(mmm, 'm');
      unsigned int us = c_in_str(wail, 'u');
      cout << ms << " m characters in " << mmm << endl;
      cout << us << " u characters in " << wail << endl;
      // cin.get();
      system("pause");
      return 0;
  }

  // this function counts the number of ch characters
  // in the string str
  unsigned int c_in_str(const char *str, char ch)
  {
      unsigned int count = 0;

      while (*str) // quit when *str is '\0'
      {
          if (*str == ch)
              count++;
          str++; // move pointer to next char
      }
      return count;
  }
  ```

  当*str指向空时，为0，否则非0

  ```cmd
  3 m characters in minimum
  2 u characters in ululate
  ```

- strback

  ```c++
  char *buildstr(char c, int n); // prototype
  int main()
  {
      using namespace std;
      int times;
      char ch;

      cout << "Enter a character: ";
      cin >> ch;
      cout << "Enter an integer: ";
      cin >> times;
      char *ps = buildstr(ch, times);
      cout << ps << endl;
      delete[] ps;            // free memory
      ps = buildstr('+', 20); // reuse pointer
      cout << ps << "-DONE-" << ps << endl;
      delete[] ps; // free memory
      // cin.get();
      // cin.get();
      system("pause");
      return 0;
  }

  // builds string made of n c characters
  char *buildstr(char c, int n)
  {
      char *pstr = new char[n + 1];
      pstr[n] = '\0'; // terminate string
      while (n-- > 0)
          pstr[n] = c; // fill rest of string
      return pstr;
  }
  ```

  ```cmd
  Enter a character: g
  Enter an integer: 46
  gggggggggggggggggggggggggggggggggggggggggggggg
  ++++++++++++++++++++-DONE-++++++++++++++++++++
  ```

  - cout输出char *

    ```c++
    char *ps = buildstr(ch, times);
    cout << ps << endl;
    ```

    这样可以直接输出字符串

  - 函数返回值类型

    这里的函数buildstr类型是char*，相当于地址，传给pa，所以正确

- travel

  - 传递和返回结构

    ```c++
    struct travel_time
    {
        int hours;
        int mins;
    };
    const int Mins_per_hr = 60;

    travel_time sum(travel_time t1, travel_time t2);
    void show_time(travel_time t);

    int main()
    {
        using namespace std;
        travel_time day1 = {5, 45}; // 5 hrs, 45 min
        travel_time day2 = {4, 55}; // 4 hrs, 55 min

        travel_time trip = sum(day1, day2);
        cout << "Two-day total: ";
        show_time(trip);

        travel_time day3 = {4, 32};
        cout << "Three-day total: ";
        show_time(sum(trip, day3));
        // cin.get();
        system("pause");
        return 0;
    }

    travel_time sum(travel_time t1, travel_time t2)
    {
        travel_time total;

        total.mins = (t1.mins + t2.mins) % Mins_per_hr;
        total.hours = t1.hours + t2.hours +
                      (t1.mins + t2.mins) / Mins_per_hr;
        return total;
    }

    void show_time(travel_time t)
    {
        using namespace std;
        cout << t.hours << " hours, "
             << t.mins << " minutes\n";
    }
    ```

    ```cmd
    Two-day total: 10 hours, 40 minutes
    Three-day total: 15 hours, 12 minutes
    ```

- strctfun

  - 传递结构

    在函数中的形参不会改变实参

    ```c++
    // structure declarations
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

    int main()
    {
        using namespace std;
        rect rplace;
        polar pplace;

        cout << "Enter the x and y values: ";
        while (cin >> rplace.x >> rplace.y) // slick use of cin
        {
            pplace = rect_to_polar(rplace);
            show_polar(pplace);
            cout << "Next two numbers (q to quit): ";
        }
        cout << "Done.\n";
        system("pause");
        return 0;
    }

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

    ```cmd
    Enter the x and y values: 3 4
    distance = 5, angle = 53.1301 degrees
    Next two numbers (q to quit): 1
    3
    distance = 3.16228, angle = 71.5651 degrees
    Next two numbers (q to quit): q
    Done.
    ```

- strctptr

  - 传递结构的地址

    传递地址能确保，将要改变的不是副本

  - \<cmath\>的atan2的使用

    ```c++
    // structure templates
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
    void rect_to_polar(const rect *pxy, polar *pda);
    void show_polar(const polar *pda);

    int main()
    {
        using namespace std;
        rect rplace;
        polar pplace;

        cout << "Enter the x and y values: ";
        while (cin >> rplace.x >> rplace.y)
        {
            rect_to_polar(&rplace, &pplace); // pass addresses
            show_polar(&pplace);             // pass address
            cout << "Next two numbers (q to quit): ";
        }
        cout << "Done.\n";
        system("pause");
        return 0;
    }

    // show polar coordinates, converting angle to degrees
    void show_polar(const polar *pda)
    {
        using namespace std;
        const double Rad_to_deg = 57.29577951;

        cout << "distance = " << pda->distance;
        cout << ", angle = " << pda->angle * Rad_to_deg;
        cout << " degrees\n";
    }

    // convert rectangular to polar coordinates
    void rect_to_polar(const rect *pxy, polar *pda)
    {
        using namespace std;
        pda->distance =
            sqrt(pxy->x * pxy->x + pxy->y * pxy->y);
        pda->angle = atan2(pxy->y, pxy->x);
    }
    ```

    ```cmd
    Enter the x and y values: 3 4
    distance = 5, angle = 53.1301 degrees
    Next two numbers (q to quit): q
    Done.
    ```

- topfive

  - 函数和string

    ```c++
    const int SIZE = 5;
    void display(const string sa[], int n);
    int main()
    {
        string list[SIZE]; // an array holding 5 string object
        cout << "Enter your " << SIZE << " favorite astronomical sights:\n";
        for (int i = 0; i < SIZE; i++)
        {
            cout << i + 1 << ": ";
            getline(cin, list[i]);
        }

        cout << "Your list:\n";
        display(list, SIZE);
        // cin.get();
        system("pause");
        return 0;
    }

    void display(const string sa[], int n)
    {
        for (int i = 0; i < n; i++)
            cout << i + 1 << ": " << sa[i] << endl;
    }
    ```

    ```cmd
    Enter your 5 favorite astronomical sights:
    1: efdgerg dfds sd.
    2: sdf weg.
    3: werv dsev dse.
    4: sedf4rb sdwe dsve vr.
    5: regwe.
    Your list:
    1: efdgerg dfds sd.
    2: sdf weg.
    3: werv dsev dse.
    4: sedf4rb sdwe dsve vr.
    5: regwe.
    ```

- arrobj

  - array地址的传递

    ```c++
    const int Seasons = 4;
    const std::array<std::string, Seasons> Snames =
        {"Spring", "Summer", "Fall", "Winter"};

    void fill(std::array<double, Seasons> *pa);
    void show(std::array<double, Seasons> da);
    int main()
    {
        std::array<double, 4> expenses;
        fill(&expenses);
        show(expenses);
        // std::cin.get();
        // std::cin.get();
        system("pause");
        return 0;
    }

    void fill(std::array<double, Seasons> *pa)
    {
        for (int i = 0; i < Seasons; i++)
        {
            std::cout << "Enter " << Snames[i] << " expenses: ";
            std::cin >> (*pa)[i];
        }
    }

    void show(std::array<double, Seasons> da)
    {
        double total = 0.0;
        std::cout << "\nEXPENSES\n";
        for (int i = 0; i < Seasons; i++)
        {
            std::cout << Snames[i] << ": $" << da[i] << '\n';
            total += da[i];
        }
        std::cout << "Total: $" << total << '\n';
    }
    ```

    ```cmd
    Enter Spring expenses: 122
    Enter Summer expenses: 123
    Enter Fall expenses: 213
    Enter Winter expenses: 124
    EXPENSES
    Spring: $122
    Summer: $123
    Fall: $213
    Winter: $124
    Total: $582
    ```

    千万注意，不能把指针当成数组

- recur

  - 递归的使用

    函数调用自身

    ```c++
    void countdown(int n);

    int main()
    {
        countdown(4); // call the recursive function
        // std::cin.get();
        system("pause");
        return 0;
    }

    void countdown(int n)
    {
        using namespace std;
        cout << "Counting down ... " << n << endl;
        if (n > 0)
            countdown(n - 1); // function calls itself
        cout << n << ": Kaboom!\n";
    }
    ```

    ```cmd
    Counting down ... 4
    Counting down ... 3
    Counting down ... 2
    Counting down ... 1
    Counting down ... 0
    0: Kaboom!
    1: Kaboom!
    2: Kaboom!
    3: Kaboom!
    4: Kaboom!
    ```

- ruler

  - 包含多个递归调用的递归

    ```c++
    const int Len = 66;
    const int Divs = 6;
    void subdivide(char ar[], int low, int high, int level);
    int main()
    {
        char ruler[Len];
        int i;
        for (i = 1; i < Len - 2; i++)
            ruler[i] = ' ';
        ruler[Len - 1] = '\0';
        int max = Len - 2;
        int min = 0;
        ruler[min] = ruler[max] = '|';
        std::cout << ruler << std::endl;
        for (i = 1; i <= Divs; i++)
        {
            subdivide(ruler, min, max, i);
            std::cout << ruler << std::endl;
            for (int j = 1; j < Len - 2; j++)
                ruler[j] = ' '; // reset to blank ruler
        }
        // std::cin.get();
        system("pause");
        return 0;
    }

    void subdivide(char ar[], int low, int high, int level)
    {
        if (level == 0)
            return;
        int mid = (high + low) / 2;
        ar[mid] = '|';
        subdivide(ar, low, mid, level - 1);
        subdivide(ar, mid, high, level - 1);
    }
    ```

    ```cmd
    |                                                               |
    |                               |                               |
    |               |               |               |               |
    |       |       |       |       |       |       |       |       |
    |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
    | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | | |
    |||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
    ```

- fun_ptr

  - 函数指针

    先编写函数原型，然后使用(*pf)替换函数名，这样pf就是函数指针

    **c++允许函数调用使用函数指针**

    ```c++
    double betsy(int);
    double pam(int);

    // second argument is pointer to a type double function that
    // takes a type int argument
    void estimate(int lines, double (*pf)(int));

    int main()
    {
        using namespace std;
        int code;

        cout << "How many lines of code do you need? ";
        cin >> code;
        cout << "Here's Betsy's estimate:\n";
        estimate(code, betsy);
        cout << "Here's Pam's estimate:\n";
        estimate(code, pam);
        // cin.get();
        // cin.get();
        system("pause");
        return 0;
    }

    double betsy(int lns)
    {
        return 0.05 * lns;
    }

    double pam(int lns)
    {
        return 0.03 * lns + 0.0004 * lns * lns;
    }

    void estimate(int lines, double (*pf)(int))
    {
        using namespace std;
        cout << lines << " lines will take ";
        cout << pf(lines) << " hour(s)\n";
    }
    ```

    ```cmd
    How many lines of code do you need? 4
    Here's Betsy's estimate:
    4 lines will take 0.2 hour(s)
    Here's Pam's estimate:
    4 lines will take 0.1264 hour(s)
    ```

  - 指针函数

    就是返回指针的函数

- arfupt

  - 函数指针的使用

    1. 首先定义三个函数

    ```c++
    const double *f1(const double ar[], int n);
    const double *f2(const double[], int);
    const double *f3(const double *, int);
    ```

    2. 这是返回指针的函数指针函数

    ```c++
    const double *(*p1)(const double *, int) = f1;
    ```

    - 调用

      ```c++
      cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << endl;
      ```

    3. 这是返回指针的函数指针数组函数

    ```c++
    const double *(*pa[3])(const double *, int) = {f1, f2, f3};
    ```

    - 调用

      ```c++
      for (int i = 0; i < 3; i++)
          cout << pa[i](av, 3) << ": " << *pa[i](av, 3) << endl;
      ```

  - 自动判断类型

    ```c++
    auto p2 = f2;
    auto pb = pa;
    ```

  - 对函数指针取地址

    ```c++
    auto pc = &pa;
    const double *(*(*pd)[3])(const double *, int) = &pa;
    ```

    - 调用

      ```c++
      cout << (*pc)[0](av, 3) << ": " << *(*pc)[0](av, 3) << endl;
      cout << (*(*pd)[2])(av, 3) << ": " << *(*(*pd)[2])(av, 3) << endl;
      ```

- arfupt1

  - typedef的使用

    typedef不像#define，而是这样：

    ```c++
    typedef const double *(*p_fun)(const double *, int);
    p_fun p1 = f1;
    p_fun pa[3] = {f1, f2, f3};
    p_fun(*pd)[3] = &pa;
    ```
