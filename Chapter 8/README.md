# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapter 8

- inline

  - 常规函数

    简单解释：常规函数调用使程序跳到另一个地址（函数地址），并在函数结束时返回。

    详细解释：执行到函数调用指令时，程序将在函数调用后立即储存该该指令的**内存地址**，并将函数参数复制到堆栈（为此保留的内存块），跳到标记**函数起点**的内存单元，执行函数代码（也许还需将返回值放入到寄存器中），然后跳回到地址被保存的指令处。**来回跳跃并记录跳跃位置意味着以前使用函数时， 需要一定的开销。**

  - 内联函数

    简单解释：编译器将使用相应的函数代码替换函数调用

    对比常规函数的跳来跳去，内联函数虽然占据更多的内存空间，但是运行速度相较而言稍快

    **应有选择的使用内联函数**：

    - 如果执行函数代码的时间比处理函数调用机制的时间长，则节省的时间将只占整个过程的很小一部分。推荐**常规函数**
    - 如果代码执行时间很短，则内联调用就可以节省非内联调用使用的大部分时间。推荐**内联函数**

  ```c++
  // an inline function definition
  inline double square(double x) { return x * x; }
  int main()
  {
      using namespace std;
      double a, b;
      double c = 13.0;

      a = square(5.0);
      b = square(4.5 + 7.5); // can pass expressions
      cout << "a = " << a << ", b = " << b << "\n";
      cout << "c = " << c;
      cout << ", c squared = " << square(c++) << "\n";
      cout << "Now c = " << c << "\n";
      // cin.get();
      system("pause");
      return 0;
  }
  ```

  ```cmd
  a = 25, b = 144
  c = 13, c squared = 169
  Now c = 14
  ```

  - 关于内敛与宏替换

    inline工具是c++新增的特性，c语言用预处理语句#define来提供宏。

    - 宏

      ```c
      #define SQUARE(X) X*X
      ```

      这并不是通过传递参数实现的，而是通过文本替换来实现的，以下

      ```c
      a = SQUARE(5.0);
      b = SQUARE(4.5 + 4.5);
      c = SQUARE(c++);
      ```

      以上只用第一个能正常工作。

      为解决第二个，可以这样定义宏

      ```c
      #define SQUARE(X) (X)*(X)
      ```

      但是第三个问题实在不能解决，因为c将被加两次。

- firstref

  ```c++
  int main()
  {
      using namespace std;
      int rats = 101;
      int &rodents = rats; // rodents is a reference

      cout << "rats = " << rats;
      cout << ", rodents = " << rodents << endl;
      rodents++;
      cout << "rats = " << rats;
      cout << ", rodents = " << rodents << endl;

      // some implementations require type casting the following
      // addresses to type unsigned
      cout << "rats address = " << &rats;
      cout << ", rodents address = " << &rodents << endl;
      // cin.get();
      system("pause");
      return 0;
  }
  ```

  ```cmd
  rats = 101, rodents = 101
  rats = 102, rodents = 102
  rats address = 0x61fe14, rodents address = 0x61fe14
  ```

  - C++引用

    ```c++
    int rats = 101;
    int &rodents = rats;
    ```

    &将使rodents指向与rats相同的值和内存空间，非是取地址

    - 引用必须在声明引用变量时进行初始化

      像以下的代码将造成编译错误

      ```c++
      int rat;
      int & rodent;
      rodent = rat;
      ```

    - 引用更接近const表示

      ```c++
      int &rodents = rats;
      ```

      实际上是下述代码的伪装表示：

      ```c++
      int * const pr = &rats;
      ```

      其中rodents扮演的角色与*pr相同

- sceref

  ```c++
  int main()
  {
      using namespace std;
      int rats = 101;
      int &rodents = rats; // rodents is a reference

      cout << "rats = " << rats;
      cout << ", rodents = " << rodents << endl;

      cout << "rats address = " << &rats;
      cout << ", rodents address = " << &rodents << endl;

      int bunnies = 50;
      rodents = bunnies; // can we change the reference?
      cout << "bunnies = " << bunnies;
      cout << ", rats = " << rats;
      cout << ", rodents = " << rodents << endl;

      cout << "bunnies address = " << &bunnies;
      cout << ", rodents address = " << &rodents << endl;
      // cin.get();
      system("pause");
      return 0;
  }
  ```

  ```cmd
  rats = 101, rodents = 101
  rats address = 0x61fe14, rodents address = 0x61fe14
  bunnies = 50, rats = 50, rodents = 50
  bunnies address = 0x61fe10, rodents address = 0x61fe14
  ```

  可以看到

  ```c++
  int bunnies = 50;
  rodents = bunnies;
  ```

  并不能将rodents当作bunnies的引用，因为rodents的地址还是rats的地址。

- swaps

  - 引用的使用

  ```c++
  void swapr(int &a, int &b); // a, b are aliases for ints
  void swapp(int *p, int *q); // p, q are addresses of ints
  void swapv(int a, int b);   // a, b are new variables
  int main()
  {
      using namespace std;
      int wallet1 = 300;
      int wallet2 = 350;

      cout << "wallet1 = $" << wallet1 << " wallet2 = $" << wallet2 << endl;

      cout << "Using references to swap contents:\n";
      swapr(wallet1, wallet2); // pass variables
      cout << "wallet1 = $" << wallet1 << " wallet2 = $" << wallet2 << endl;

      cout << "Using pointers to swap contents again:\n";
      swapp(&wallet1, &wallet2); // pass addresses of variables
      cout << "wallet1 = $" << wallet1 << " wallet2 = $" << wallet2 << endl;

      cout << "Trying to use passing by value:\n";
      swapv(wallet1, wallet2); // pass values of variables
      cout << "wallet1 = $" << wallet1 << " wallet2 = $" << wallet2 << endl;
      // cin.get();
      system("pause");
      return 0;
  }

  void swapr(int &a, int &b) // use references
  {
      int temp;

      temp = a; // use a, b for values of variables
      a = b;
      b = temp;
  }

  void swapp(int *p, int *q) // use pointers
  {
      int temp;

      temp = *p; // use *p, *q for values of variables
      *p = *q;
      *q = temp;
  }

  void swapv(int a, int b) // try using values
  {
      int temp;

      temp = a; // use a, b for values of variables
      a = b;
      b = temp;
  }
  ```

  ```cmd
  wallet1 = $300 wallet2 = $350
  Using references to swap contents:
  wallet1 = $350 wallet2 = $300
  Using pointers to swap contents again:
  wallet1 = $300 wallet2 = $350
  Trying to use passing by value:
  wallet1 = $300 wallet2 = $350
  ```

- cubes

  ```c++
  double cube(double a);
  double refcube(double &ra);
  int main()
  {
      using namespace std;
      double x = 3.0;

      cout << cube(x);
      cout << " = cube of " << x << endl;
      cout << refcube(x);
      cout << " = cube of " << x << endl;
      // cin.get();
      system("pause");
      return 0;
  }

  double cube(double a)
  {
      a *= a * a;
      return a;
  }

  double refcube(double &ra)
  {
      ra *= ra * ra;
      return ra;
  }
  ```

  ```cmd
  27 = cube of 3
  27 = cube of 27
  ```

  对于recube考虑有参数是const的调用方法：

  ```c++
  double recube(const double &ra)
  {
      return ra * ra * ra;
  }
  ```

  考虑

  ```c++
  double side = 3.0;
  double * pd = &side;
  double & rd = side;
  long edge = 5L;
  double lens[4] = { 2.0, 5.0, 10.0, 12.0 };
  double c1 = refcube(side);
  double c2 = refcube(len[2]);
  double c3 = refcube(rd);
  double c4 = refcube(*pd);
  double c5 = refcube(edge);
  double c6 = refcube(7.0);
  double c7 = refcube(side + 10.0);
  ```

  side,lens[2],rd,*pd都是有名称的、都变了类型的数据对象，因此可以为其创建以用，而不需要临时变量。

  然而edge虽然是变量，但是类型不符，double引用不能指向long。

  另外参数7.0和side+10.0的类型都正确，但没有名称，在这些情况下，编译器都将生成一个临时匿名变量，并让ra指向它。

  - const规则

    对于形参为const引用的c++函数，如果实参不匹配，则其行为类似按值传递，为确保原始数据不被修改，将创建临时变量来储存值。

    应尽可能使用const

    - 使用const可以避免无意中修改数据的编程错误
    - 使用const使函数能够处理const的非const实参，否则只能接受非const数据（一维）
    - 使用const引用使函数能够正确生成并使用临时变量

    c++11之后新增了右值引用——&&：

    ```c++
    double && rref = std::sqrt(36.00);
    double j = 15.0;
    double && jref = 2.0 * j + 18.5;
    std::cout << rref << '\n';
    std::cout << jref << '\n';
    ```

    直接引用常量，可用于实现移动语义；

- strtref

  - 结构引用

  ```c++
  struct free_throws
  {
      std::string name;
      int made;
      int attempts;
      float percent;
  };

  void display(const free_throws &ft);
  void set_pc(free_throws &ft);
  free_throws &accumulate(free_throws &target, const free_throws &source);

  int main()
  {
      free_throws one = {"Ifelsa Branch", 13, 14};
      free_throws two = {"Andor Knott", 10, 16};
      free_throws three = {"Minnie Max", 7, 9};
      free_throws four = {"Whily Looper", 5, 9};
      free_throws five = {"Long Long", 6, 14};
      free_throws team = {"Throwgoods", 0, 0};
      free_throws dup;
      set_pc(one);
      display(one);
      accumulate(team, one);
      display(team);
      // use return value as argument
      display(accumulate(team, two));
      accumulate(accumulate(team, three), four);
      display(team);
      // use return value in assignment
      dup = accumulate(team, five);
      std::cout << "Displaying team:\n";
      display(team);
      std::cout << "Displaying dup after assignment:\n";
      display(dup);
      set_pc(four);
      // ill-advised assignment
      accumulate(dup, five) = four;
      std::cout << "Displaying dup after ill-advised assignment:\n";
      display(dup);
      // std::cin.get();
      system("pause");
      return 0;
  }

  void display(const free_throws &ft)
  {
      using std::cout;
      cout << "Name: " << ft.name << '\n';
      cout << "  Made: " << ft.made << '\t';
      cout << "Attempts: " << ft.attempts << '\t';
      cout << "Percent: " << ft.percent << '\n';
  }
  void set_pc(free_throws &ft)
  {
      if (ft.attempts != 0)
          ft.percent = 100.0f * float(ft.made) / float(ft.attempts);
      else
          ft.percent = 0;
  }

  free_throws &accumulate(free_throws &target, const free_throws &source)
  {
      target.attempts += source.attempts;
      target.made += source.made;
      set_pc(target);
      return target;
  }
  ```

  ```cmd
  Name: Ifelsa Branch
    Made: 13      Attempts: 14    Percent: 92.8571
  Name: Throwgoods
    Made: 13      Attempts: 14    Percent: 92.8571
  Name: Throwgoods
    Made: 23      Attempts: 30    Percent: 76.6667
  Name: Throwgoods
    Made: 35      Attempts: 48    Percent: 72.9167
  Displaying team:
  Name: Throwgoods
    Made: 41      Attempts: 62    Percent: 66.129
  Displaying dup after assignment:
  Name: Throwgoods
    Made: 41      Attempts: 62    Percent: 66.129
  Displaying dup after ill-advised assignment:
  Name: Whily Looper
    Made: 5       Attempts: 9     Percent: 55.5556
  ```

  - 为什么要返回引用

    ```c++
    dup = accumulate(team, five);
    ```

    如果accmulate返回一个结构，而不是指向结构的引用，将把整个结构复制到临时位置，再将这个拷贝给dup。但在返回值为引用时，将直接把team复制到dup，其效率更高。

    - 返回引用的注意点

      1. 不要返回指向临时变量的引用，因为函数结束时，这个临时变量将不复存在，并且在执行时直接崩溃；

      2. 避免返回指向临时变量的指针，因为会忘记释放变量。

  - 将const用于引用返回类型

    注意到上面一行代码

    ```c++
    accumulate(dup, five) = four;
    ```

    这是c++语法所允许的，为了不允许这样做，可以使用const定义

    ```c++
    const free_throws &accumulate(free_throws &target, const free_throws &source);
    ```

    但是上述程序需要改的地方有：

    set_pc调用和accumulate的多重调用，从此看来

    - 通过省略const，可以编写更简短的代码，但是代码会模糊不清
    - 但是有时候省略const也有好处，比如重载<<运算符

- strquote

  - 将引用用于类对象

    ```c++
    string version1(const string &s1, const string &s2);
    const string &version2(string &s1, const string &s2); // has side effect
    const string &version3(string &s1, const string &s2); // bad design

    int main()
    {
        string input;
        string copy;
        string result;

        cout << "Enter a string: ";
        getline(cin, input);
        copy = input;
        cout << "Your string as entered: " << input << endl;
        result = version1(input, "***");
        cout << "Your string enhanced: " << result << endl;
        cout << "Your original string: " << input << endl;

        result = version2(input, "###");
        cout << "Your string enhanced: " << result << endl;
        cout << "Your original string: " << input << endl;

        cout << "Resetting original string.\n";
        input = copy;
        result = version3(input, "@@@");
        cout << "Your string enhanced: " << result << endl;
        cout << "Your original string: " << input << endl;
        // cin.get();
        // cin.get();
        system("pause");
        return 0;
    }

    string version1(const string &s1, const string &s2)
    {
        string temp;

        temp = s2 + s1 + s2;
        return temp;
    }

    const string &version2(string &s1, const string &s2) // has side effect
    {
        s1 = s2 + s1 + s2;
        // safe to return reference passed to function
        return s1;
    }

    const string &version3(string &s1, const string &s2) // bad design
    {
        string temp;

        temp = s2 + s1 + s2;
        // unsafe to return reference to local variable
        return temp;
    }
    ```

    在使用result = version3(input, "@@@");时，执行崩溃，程序试图引用已经释放的内存。

- filefunc

  ```c++
  void file_it(ostream &os, double fo, const double fe[], int n);
  const int LIMIT = 5;
  int main()
  {
      ofstream fout;
      const char *fn = "ep-data.txt";
      fout.open(fn);
      if (!fout.is_open())
      {
          cout << "Can't open " << fn << ". Bye.\n";
          exit(EXIT_FAILURE);
      }
      double objective;
      cout << "Enter the focal length of your "
              "telescope objective in mm: ";
      cin >> objective;
      double eps[LIMIT];
      cout << "Enter the focal lengths, in mm, of " << LIMIT
           << " eyepieces:\n";
      for (int i = 0; i < LIMIT; i++)
      {
          cout << "Eyepiece #" << i + 1 << ": ";
          cin >> eps[i];
      }
      file_it(fout, objective, eps, LIMIT);
      file_it(cout, objective, eps, LIMIT);
      cout << "Done\n";
      // cin.get();
      // cin.get();
      system("pause");
      return 0;
  }

  void file_it(ostream &os, double fo, const double fe[], int n)
  {
      // save initial formatting state
      ios_base::fmtflags initial;
      initial = os.setf(ios_base::fixed, ios_base::floatfield);
      std::streamsize sz = os.precision(0);
      os << "Focal length of objective: " << fo << " mm\n";
      os.precision(1);
      os.width(12);
      os << "f.l. eyepiece";
      os.width(15);
      os << "magnification" << endl;
      for (int i = 0; i < n; i++)
      {
          os.width(12);
          os << fe[i];
          os.width(15);
          os << int(fo / fe[i] + 0.5) << endl;
      }
      // restore initial formatting state
      os.setf(initial, ios_base::floatfield);
      os.precision(sz);
  }
  ```

  ```cmd
  Enter the focal length of your telescope objective in mm: 1800
  Enter the focal lengths, in mm, of 5 eyepieces:
  Eyepiece #1: 30
  Eyepiece #2: 19
  Eyepiece #3: 14
  Eyepiece #4: 8.8
  Eyepiece #5: 7.5
  Focal length of objective: 1800 mm
  f.l. eyepiece  magnification
          30.0             60
          19.0             95
          14.0            129
           8.8            205
           7.5            240
  Done
  ```

  - 对象，继承和引用

    - 继承

      ofstream可以使用ostream的方法。能够将特性从一个类传递到另一个类的语言特性称为继承。

    - ostream &可以指向ostream的对象，也可以指向ofstream对象

    - ostream类的格式方法

      ```c++
      ios_base::fmtflags initial;
      initial = os.setf(ios_base::fixed, ios_base::floatfield);
      os.setf(initial, ios_base::floatfield);
      ```

      方法setf()返回调用它之前有效的所有格式化设置。ios_base::fmtflags是储存这种信息所需的数据类型名称。因此，将返回值赋给initial将储存file_it()之前的格式化设置，然后便可以使用变量initial作为参数来调用setf()，将所有的格式化设置恢复到原来的值。

- left

  - 函数默认参数的使用
    - 调用时可以不如实参
    - 定义时，提供默认值的参数右边必须也要有默认值
    - 调用时，提供默认值的参数如果给了值，右边也必须都给值

  ```c++
  const int ArSize = 80;
  char *left(const char *str, int n = 1);
  int main()
  {
      using namespace std;
      char sample[ArSize];
      cout << "Enter a string:\n";
      cin.get(sample, ArSize);
      char *ps = left(sample, 4);
      cout << ps << endl;
      delete[] ps; // free old string
      ps = left(sample);
      cout << ps << endl;
      delete[] ps; // free new string
      // cin.get();
      // cin.get();
      system("pause");
      return 0;
  }
  // This function returns a pointer to a new string
  // consisting of the first n characters in the str string.
  char *left(const char *str, int n)
  {
      if (n < 0)
          n = 0;
      char *p = new char[n + 1];
      int i;
      for (i = 0; i < n && str[i]; i++)
          p[i] = str[i]; // copy characters
      while (i <= n)
          p[i++] = '\0'; // set rest of string to '\0'
      return p;
  }
  ```

  ```cmd
  Enter a string:
  sdfsdf
  sdfs
  s
  ```

- leftover

  - 函数重载

    ```c++
    unsigned long left(unsigned long num, unsigned ct);
    char *left(const char *str, int n = 1);

    int main()
    {
        using namespace std;
        char *trip = "Hawaii!!";    // test value
        unsigned long n = 12345678; // test value
        int i;
        char *temp;

        for (i = 1; i < 10; i++)
        {
            cout << left(n, i) << endl;
            temp = left(trip, i);
            cout << temp << endl;
            delete[] temp; // point to temporary storage
        }
        // cin.get();
        system("pause");
        return 0;
    }

    // This function returns the first ct digits of the number num.
    unsigned long left(unsigned long num, unsigned ct)
    {
        unsigned digits = 1;
        unsigned long n = num;

        if (ct == 0 || num == 0)
            return 0; // return 0 if no digits
        while (n /= 10)
            digits++;
        if (digits > ct)
        {
            ct = digits - ct;
            while (ct--)
                num /= 10;
            return num; // return left ct digits
        }
        else            // if ct >= number of digits
            return num; // return the whole number
    }

    // This function returns a pointer to a new string
    // consisting of the first n characters in the str string.
    char *left(const char *str, int n)
    {
        if (n < 0)
            n = 0;
        char *p = new char[n + 1];
        int i;
        for (i = 0; i < n && str[i]; i++)
            p[i] = str[i]; // copy characters
        while (i <= n)
            p[i++] = '\0'; // set rest of string to '\0'
        return p;
    }
    ```

    ```cmd
    1
    H
    12
    Ha
    123
    Haw
    1234
    Hawa
    12345
    Hawai
    123456
    Hawaii
    1234567
    Hawaii!
    12345678
    Hawaii!!
    12345678
    Hawaii!!
    ```

    - 如果有多钟重载方式中包含自动转换的，将报错

      ```c++
      void print(int i);
      void print(double j);
      void print(long l);
      ```

      以上情况调用print(year)时，c++将拒绝这种调用

      ```c++
      double cube(double x);
      double cube(double & x);
      ```

      以上从编译器角度看，编译器在检查函数特征标时，类型引用和类型将视为同一特征标，即两者不能共存

    - 是特征标，而不是函数类型使函数重载

      只有函数类型不同的两个函数不能重载，两者互斥

    - 重载引用参数

      ```c++
      void stove(double & r1);
      void stove(const double & r2);
      void stove(double && r3);
      ```

      调用时，将根据最匹配的版本调用：

      ```c++
      double x = 55.5;
      const double y = 32.0;
      stove(x); // stove(double &);
      stove(y); // stove(const double &);
      stove(x+y); // stove(double &&)
      ```

- funtemp

  - 函数模板的使用

  ```c++
  template <typename T> // or class T
  void Swap(T &a, T &b);

  int main()
  {
      using namespace std;
      int i = 10;
      int j = 20;
      cout << "i, j = " << i << ", " << j << ".\n";
      cout << "Using compiler-generated int swapper:\n";
      Swap(i, j); // generates void Swap(int &, int &)
      cout << "Now i, j = " << i << ", " << j << ".\n";

      double x = 24.5;
      double y = 81.7;
      cout << "x, y = " << x << ", " << y << ".\n";
      cout << "Using compiler-generated double swapper:\n";
      Swap(x, y); // generates void Swap(double &, double &)
      cout << "Now x, y = " << x << ", " << y << ".\n";
      // cin.get();
      system("pause");
      return 0;
  }

  // function template definition
  template <typename T> // or class T
  void Swap(T &a, T &b)
  {
      T temp; // temp a variable of type T
      temp = a;
      a = b;
      b = temp;
  }
  ```

  ```cmd
  i, j = 10, 20.
  Using compiler-generated int swapper:
  Now i, j = 20, 10.
  x, y = 24.5, 81.7.
  Using compiler-generated double swapper:
  Now x, y = 81.7, 24.5.
  ```

  函数模板不能缩短可执行程序。

  使用函数模板的好处是，它使得生成多个函数定义更简单、更可靠。

- twotemps

  - 模板重载

    ```c++
    template <typename T> // original template
    void Swap(T &a, T &b);

    template <typename T> // new template
    void Swap(T *a, T *b, int n);

    void Show(int a[]);
    const int Lim = 8;
    int main()
    {
        using namespace std;
        int i = 10, j = 20;
        cout << "i, j = " << i << ", " << j << ".\n";
        cout << "Using compiler-generated int swapper:\n";
        Swap(i, j); // matches original template
        cout << "Now i, j = " << i << ", " << j << ".\n";

        int d1[Lim] = {0, 7, 0, 4, 1, 7, 7, 6};
        int d2[Lim] = {0, 7, 2, 0, 1, 9, 6, 9};
        cout << "Original arrays:\n";
        Show(d1);
        Show(d2);
        Swap(d1, d2, Lim); // matches new template
        cout << "Swapped arrays:\n";
        Show(d1);
        Show(d2);
        // cin.get();
        system("pause");
        return 0;
    }

    template <typename T>
    void Swap(T &a, T &b)
    {
        T temp;
        temp = a;
        a = b;
        b = temp;
    }

    template <typename T>
    void Swap(T a[], T b[], int n)
    {
        T temp;
        for (int i = 0; i < n; i++)
        {
            temp = a[i];
            a[i] = b[i];
            b[i] = temp;
        }
    }

    void Show(int a[])
    {
        using namespace std;
        cout << a[0] << a[1] << "/";
        cout << a[2] << a[3] << "/";
        for (int i = 4; i < Lim; i++)
            cout << a[i];
        cout << endl;
    }
    ```

    ```cmd
    i, j = 10, 20.
    Using compiler-generated int swapper:
    Now i, j = 20, 10.
    Original arrays:
    07/04/1776
    07/20/1969
    Swapped arrays:
    07/20/1969
    07/04/1776
    ```

- twoswap

  - 模板的局限性-使用显示具体化克服

    ```c++
    template <typename T>
    void Swap(T &a, T &b);

    struct job
    {
        char name[40];
        double salary;
        int floor;
    };

    // explicit specialization
    template <>
    void Swap<job>(job &j1, job &j2);
    void Show(job &j);

    int main()
    {
        using namespace std;
        cout.precision(2);
        cout.setf(ios::fixed, ios::floatfield);
        int i = 10, j = 20;
        cout << "i, j = " << i << ", " << j << ".\n";
        cout << "Using compiler-generated int swapper:\n";
        Swap(i, j); // generates void Swap(int &, int &)
        cout << "Now i, j = " << i << ", " << j << ".\n";

        job sue = {"Susan Yaffee", 73000.60, 7};
        job sidney = {"Sidney Taffee", 78060.72, 9};
        cout << "Before job swapping:\n";
        Show(sue);
        Show(sidney);
        Swap(sue, sidney); // uses void Swap(job &, job &)
        cout << "After job swapping:\n";
        Show(sue);
        Show(sidney);
        // cin.get();
        system("pause");
        return 0;
    }

    template <typename T>
    void Swap(T &a, T &b) // general version
    {
        T temp;
        temp = a;
        a = b;
        b = temp;
    }

    // swaps just the salary and floor fields of a job structure

    template <>
    void Swap<job>(job &j1, job &j2) // specialization
    {
        double t1;
        int t2;
        t1 = j1.salary;
        j1.salary = j2.salary;
        j2.salary = t1;
        t2 = j1.floor;
        j1.floor = j2.floor;
        j2.floor = t2;
    }

    void Show(job &j)
    {
        using namespace std;
        cout << j.name << ": $" << j.salary
             << " on floor " << j.floor << endl;
    }
    ```

    ```cmd
    i, j = 10, 20.
    Using compiler-generated int swapper:
    Now i, j = 20, 10.
    Before job swapping:
    Susan Yaffee: $73000.60 on floor 7
    Sidney Taffee: $78060.72 on floor 9
    After job swapping:
    Susan Yaffee: $78060.72 on floor 9
    Sidney Taffee: $73000.60 on floor 7
    ```

    - 对于给定的函数名，可以有非模板函数、模板函数和显示具体化模板函数以及他们的重载版本
    - 显式具体化的原型和定义应以template<>打头，并通过名称来指定类型
    - 具体化优先于常规模板，而非模板函数优先于具体化和常规模板

  - 显示实例化

    ```c++
    template void Swap<int>(int,int);
    ```

    ```c++
    template <class T>
    T Add(T a, T b){
        return a + b;
    }
    ...
    int m = 6;
    double x = 10.2;
    cout << Add<double>(x, m) << endl;
    ```

    这里模板与函数Add(x, m)不匹配，因为该模板要求两个参数类型相同，而Add\<double\>(x, m)，可强制为double类型实例化，并将参数m将之转化为double类型，

- tempover

  - 编译器决定哪个模板版本

    ```c++
    template <typename T> // template A
    void ShowArray(T arr[], int n);

    template <typename T> // template B
    void ShowArray(T *arr[], int n);

    struct debts
    {
        char name[50];
        double amount;
    };

    int main()
    {
        using namespace std;
        int things[6] = {13, 31, 103, 301, 310, 130};
        struct debts mr_E[3] =
            {
                {"Ima Wolfe", 2400.0},
                {"Ura Foxe", 1300.0},
                {"Iby Stout", 1800.0}};
        double *pd[3];

        // set pointers to the amount members of the structures in mr_E
        for (int i = 0; i < 3; i++)
            pd[i] = &mr_E[i].amount;

        cout << "Listing Mr. E's counts of things:\n";
        // things is an array of int
        ShowArray(things, 6); // uses template A
        cout << "Listing Mr. E's debts:\n";
        // pd is an array of pointers to double
        ShowArray(pd, 3); // uses template B (more specialized)
        // cin.get();
        system("pause");
        return 0;
    }

    template <typename T>
    void ShowArray(T arr[], int n)
    {
        using namespace std;
        cout << "template A\n";
        for (int i = 0; i < n; i++)
            cout << arr[i] << ' ';
        cout << endl;
    }

    template <typename T>
    void ShowArray(T *arr[], int n)
    {
        using namespace std;
        cout << "template B\n";
        for (int i = 0; i < n; i++)
            cout << *arr[i] << ' ';
        cout << endl;
    }
    ```

    ```cmd
    Listing Mr. E's counts of things:
    template A
    13 31 103 301 310 130
    Listing Mr. E's debts:
    template B
    2400 1300 1800
    ```

    如果将template B删除：

    ```cmd
    Listing Mr. E's counts of things:
    template A
    13 31 103 301 310 130
    Listing Mr. E's debts:
    template A
    0x61fd78 0x61fdb8 0x61fdf8
    ```

    - 重载解析将寻找最匹配的函数

- choices

  - 自定义选择模板

    ```c++
    template <class T>
    T lesser(T a, T b) // #1
    {
        return a < b ? a : b;
    }

    int lesser(int a, int b) // #2
    {
        a = a < 0 ? -a : a;
        b = b < 0 ? -b : b;
        return a < b ? a : b;
    }

    int main()
    {
        using namespace std;
        int m = 20;
        int n = -30;
        double x = 15.5;
        double y = 25.9;

        cout << lesser(m, n) << endl;      // use #2
        cout << lesser(x, y) << endl;      // use #1 with double
        cout << lesser<>(m, n) << endl;    // use #1 with int
        cout << lesser<int>(x, y) << endl; // use #1 with int

        // cin.get();
        system("pause");
        return 0;
    }
    ```

    ```cmd
    20
    15.5
    -30
    15
    ```

    注意到：

    ```c++
    cout << lesser<>(m, n) << endl;
    ```

    这是指定，编译器应选择模板函数

- decltype的使用
- 模板函数定义返回值类型

- arrtemp

  ```c++
  template <class T, size_t n>
  void display(const std::array<T, n> &ar);
  int main()
  {
    std::array<int, 5> ai = {1, 2, 3, 4, 5}; //,6,7,8,9,22};
    std::array<std::string, 5> as =
        {
            "string under construction",
            "stupid string indeed",
            "there's nothing to see",
            "nothing to do",
            "but enjoy all that is"};
    display(ai);
    display(as);
    // std::cin.get();
    system("pause");
    return 0;
  }
  template <class T, size_t n>
  void display(const std::array<T, n> &ar)
  {
    for (int i = 0; i < 5; i++)
        std::cout << ar[i] << std::endl;
  }
  ```

  ```cmd
  1
  2
  3
  4
  5
  string under construction
  stupid string indeed
  there's nothing to see
  nothing to do
  but enjoy all that is
  ```
