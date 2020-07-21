# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapter 11

- mytime0-usetime0

  - 实现sum

  ```c++
  // mytime0.h -- Time class before operator overloading
  #ifndef MYTIME0_H_
  #define MYTIME0_H_

  class Time
  {
  private:
      int hours;
      int minutes;

  public:
      Time();
      Time(int h, int m = 0);
      void AddMin(int m);
      void AddHr(int h);
      void Reset(int h = 0, int m = 0);
      const Time Sum(const Time &t) const;
      void Show() const;
  };
  #endif
  ```

  ```c++
  // mytime0.cpp  -- implementing Time methods
  #include <iostream>
  #include "mytime0.h"

  Time::Time()
  {
      hours = minutes = 0;
  }

  Time::Time(int h, int m)
  {
      hours = h;
      minutes = m;
  }

  void Time::AddMin(int m)
  {
      minutes += m;
      hours += minutes / 60;
      minutes %= 60;
  }

  void Time::AddHr(int h)
  {
      hours += h;
  }

  void Time::Reset(int h, int m)
  {
      hours = h;
      minutes = m;
  }

  const Time Time::Sum(const Time &t) const
  {
      Time sum;
      sum.minutes = minutes + t.minutes;
      sum.hours = hours + t.hours + sum.minutes / 60;
      sum.minutes %= 60;
      return sum;
  }

  void Time::Show() const
  {
      std::cout << hours << " hours, " << minutes << " minutes";
  }
  ```

  ```c++
  // usetime0.cpp -- using the first draft of the Time class
  // compile usetime0.cpp and mytime0.cpp together
  #include <iostream>
  #include "mytime0.h"

  int main()
  {
    using std::cout;
    using std::endl;
    Time planning;
    Time coding(2, 40);
    Time fixing(5, 55);
    Time total;

    cout << "planning time = ";
    planning.Show();
    cout << endl;

    cout << "coding time = ";
    coding.Show();
    cout << endl;

    cout << "fixing time = ";
    fixing.Show();
    cout << endl;

    total = coding.Sum(fixing);
    cout << "coding.Sum(fixing) = ";
    total.Show();
    cout << endl;
    // std::cin.get();
    system("pause");
    return 0;
  }
  ```

  ```cmd
  planning time = 0 hours, 0 minutes
  coding time = 2 hours, 40 minutes
  fixing time = 5 hours, 55 minutes
  coding.Sum(fixing) = 8 hours, 35 minutes
  ```

- mytime1-usetime1

  - 重载运算符实现sum

    ```c++
    const Time Sum(const Time &t) const;
    ```

    ->

    ```c++
    Time operator+(const Time &t) const;
    ```

    它将第二个Time对象作为参数，并返回一个Time对象

    因此

    ```c++
    total = coding.Sum(fixing);
    ```

    ->

    ```c++
    total = coding.operator+(fixing);
    ```

    但还有一种更简单的方法：

    ```c++
    total = coding + fixing;
    ```

    运算符左边的对象是调用对象，右边的对象是被调用函数的参数

- mytime2-usetime2

  - 重载运算符实现+、-、*

    ```c++
    Time operator+(const Time &t) const;
    Time operator-(const Time &t) const;
    Time operator*(double n) const;
    ```

    ```c++
    Time Time::operator+(const Time &t) const
    {
        Time sum;
        sum.minutes = minutes + t.minutes;
        sum.hours = hours + t.hours + sum.minutes / 60;
        sum.minutes %= 60;
        return sum;
    }

    Time Time::operator-(const Time &t) const
    {
        Time diff;
        int tot1, tot2;
        tot1 = t.minutes + 60 * t.hours;
        tot2 = minutes + 60 * hours;
        diff.minutes = (tot2 - tot1) % 60;
        diff.hours = (tot2 - tot1) / 60;
        return diff;
    }

    Time Time::operator*(double mult) const
    {
        Time result;
        long totalminutes = hours * mult * 60 + minutes * mult;
        result.hours = totalminutes / 60;
        result.minutes = totalminutes % 60;
        return result;
    }
    ```

    ```c++
    // usetime2.cpp -- using the third draft of the Time class
    // compile usetime2.cpp and mytime2.cpp together
    #include <iostream>
    #include "mytime2.h"

    int main()
    {
        using std::cout;
        using std::endl;
        Time weeding(4, 35);
        Time waxing(2, 47);
        Time total;
        Time diff;
        Time adjusted;

        cout << "weeding time = ";
        weeding.Show();
        cout << endl;

        cout << "waxing time = ";
        waxing.Show();
        cout << endl;

        cout << "total work time = ";
        total = weeding + waxing; // use operator+()
        total.Show();
        cout << endl;

        diff = weeding - waxing; // use operator-()
        cout << "weeding time - waxing time = ";
        diff.Show();
        cout << endl;

        adjusted = total * 1.5; // use operator+()
        cout << "adjusted work time = ";
        adjusted.Show();
        cout << endl;
        // std::cin.get();
        system("pause");
        return 0;
    }
    ```

    ```cmd
    weeding time = 4 hours, 35 minutes
    waxing time = 2 hours, 47 minutes
    total work time = 7 hours, 22 minutes
    weeding time - waxing time = 1 hours, 48 minutes
    adjusted work time = 11 hours, 3 minutes
    ```

- mytime3-usetime3

  - 友元函数

    - 友元函数的优点是调用对象不需要是类对象

    友元函数是非类成员函数，但是有权限调用类的私有数据，声明在普通成员函数前面加一个friend

    ```c++
    friend Time operator*(double m, const Time &t)
    {
        return t * m;
    } // inline definition
    friend std::ostream &operator<<(std::ostream &os, const Time &t);
    ```

    定义则不需要加friend

    - 注意<<的重载，返回ostream &，是由于cout<<后面还可以接流

    ```c++
    Time Time::operator*(double mult) const
    {
        Time result;
        long totalminutes = hours * mult * 60 + minutes * mult;
        result.hours = totalminutes / 60;
        result.minutes = totalminutes % 60;
        return result;
    }

    std::ostream &operator<<(std::ostream &os, const Time &t)
    {
        os << t.hours << " hours, " << t.minutes << " minutes";
        return os;
    }
    ```

    ```c++
    //usetime3.cpp -- using the fourth draft of the Time class
    // compile usetime3.cpp and mytime3.cpp together
    #include <iostream>
    #include "mytime3.h"

    int main()
    {
        using std::cout;
        using std::endl;
        Time aida(3, 35);
        Time tosca(2, 48);
        Time temp;

        cout << "Aida and Tosca:\n";
        cout << aida << "; " << tosca << endl;
        temp = aida + tosca; // operator+()
        cout << "Aida + Tosca: " << temp << endl;
        temp = aida * 1.17; // member operator*()
        cout << "Aida * 1.17: " << temp << endl;
        cout << "10.0 * Tosca: " << 10.0 * tosca << endl;
        // std::cin.get();
        system("pause");
        return 0;
    }
    ```

    ```cmd
    Aida and Tosca:
    3 hours, 35 minutes; 2 hours, 48 minutes
    Aida + Tosca: 6 hours, 23 minutes
    Aida * 1.17: 4 hours, 11 minutes
    10.0 * Tosca: 28 hours, 0 minutes
    ```

- vect-randwalk

  ```c++
  // stonewt.h -- definition for the Stonewt class
  #ifndef STONEWT_H_
  #define STONEWT_H_
  class Stonewt
  {
  private:
      enum
      {
          Lbs_per_stn = 14
      };               // pounds per stone
      int stone;       // whole stones
      double pds_left; // fractional pounds
      double pounds;   // entire weight in pounds
  public:
      Stonewt(double lbs);          // constructor for double pounds
      Stonewt(int stn, double lbs); // constructor for stone, lbs
      Stonewt();                    // default constructor
      ~Stonewt();
      void show_lbs() const; // show weight in pounds format
      void show_stn() const; // show weight in stone format
  };
  #endif
  ```

  ```c++
  // stonewt.cpp -- Stonewt methods
  #include <iostream>
  using std::cout;
  #include "stonewt.h"

  // construct Stonewt object from double value
  Stonewt::Stonewt(double lbs)
  {
      stone = int(lbs) / Lbs_per_stn; // integer division
      pds_left = int(lbs) % Lbs_per_stn + lbs - int(lbs);
      pounds = lbs;
  }

  // construct Stonewt object from stone, double values
  Stonewt::Stonewt(int stn, double lbs)
  {
      stone = stn;
      pds_left = lbs;
      pounds = stn * Lbs_per_stn + lbs;
  }

  Stonewt::Stonewt() // default constructor, wt = 0
  {
      stone = pounds = pds_left = 0;
  }

  Stonewt::~Stonewt() // destructor
  {
  }

  // show weight in stones
  void Stonewt::show_stn() const
  {
      cout << stone << " stone, " << pds_left << " pounds\n";
  }

  // show weight in pounds
  void Stonewt::show_lbs() const
  {
      cout << pounds << " pounds\n";
  }
  ```

  ```c++
  // stone.cpp -- user-defined conversions
  // compile with stonewt.cpp
  #include <iostream>
  using std::cout;
  #include "stonewt.h"
  void display(const Stonewt &st, int n);
  int main()
  {
      Stonewt incognito = 275; // uses constructor to initialize
      Stonewt wolfe(285.7);    // same as Stonewt wolfe = 285.7;
      Stonewt taft(21, 8);

      cout << "The celebrity weighed ";
      incognito.show_stn();
      cout << "The detective weighed ";
      wolfe.show_stn();
      cout << "The President weighed ";
      taft.show_lbs();
      incognito = 276.8; // uses constructor for conversion
      taft = 325;        // same as taft = Stonewt(325);
      cout << "After dinner, the celebrity weighed ";
      incognito.show_stn();
      cout << "After dinner, the President weighed ";
      taft.show_lbs();
      display(taft, 2);
      cout << "The wrestler weighed even more.\n";
      display(422, 2);
      cout << "No stone left unearned\n";
      // std::cin.get();
      system("pause");
      return 0;
  }

  void display(const Stonewt &st, int n)
  {
      for (int i = 0; i < n; i++)
      {
          cout << "Wow! ";
          st.show_stn();
      }
  }
  ```

  ```cmd
  The celebrity weighed 19 stone, 9 pounds
  The detective weighed 20 stone, 5.7 pounds
  The President weighed 302 pounds
  After dinner, the celebrity weighed 19 stone, 10.8 pounds
  After dinner, the President weighed 325 pounds
  Wow! 23 stone, 3 pounds
  Wow! 23 stone, 3 pounds
  The wrestler weighed even more.
  Wow! 30 stone, 2 pounds
  Wow! 30 stone, 2 pounds
  No stone left unearned
  ```

  - 随机函数

    ```c++
    #include <ctime> // srand()
    #include <cstdlib> // time()
    srand(time(0));
    ```

    - time(0)返回值设置种子点，返回值为当前时间

  - 重载写文件

    ```c++
    friend std::ostream &operator<<(std::ostream &os, const Vector &v);
    ```

    当调用

    ```c++
    #include <fstream>
    ...
    ofstream fout;
    fout.open(".txt")
    ```

    然后，在计算结果循环中加入类似代码：

    ```c++
    fout << result << endl;
    ```

    就可以将数据信息写入文件

- stonewt-stone

  - 类的自动类型转换

    - 只能将其他类型转换成类类型

    - 隐式转换

    ```c++
    double a = 10; //int型转double
    ```

    下面的构造函数用于将double类型的值转换成Stonewt类型

    ```c++
    Stonewt(double lbs);
    ```

    即可以这样编写代码

    ```c++
    Stonewt myCat;
    myCat = 19.6;
    ```

    - 只有接受一个参数的构造函数才能作为转换函数

    - 使用explict在构造函数前，用于关闭隐式转换，但可以显示转换

      即可以

      ```c++
      Stonewt myCat;
      myCat = 19.6;
      myCat = Stonewt(19.6);
      myCat = (Stonewt)19.6;
      ```

    - 不使用关键字explict时，可以使用隐式转换：

      > - 将Stonewt对象初始化为double值时；
      >
      > - 将double值赋给Stonewt对象时；
      > - 将double值传递给接受Stonewt的参数的函数时；
      > - 返回值被声明为Stonewt的函数试图返回double值时；
      > - 在上述任意一种情况下，使用可转换为double类型的内置类型时（int、float...）

    - 注意到代码中display(422, 2);

      前一个参数将被隐式转换

- stonewt1-stone1

  - 转换函数

    格式：

    ```c++
    operator typeName();
    ```

    **注意**：

    1. 转换函数必须是类方法；
    2. 转换函数不能指定返回类型；
    3. 转换函数不能有参数。

    ```c++
    operator int() const;
    operator double() const;
    ```

    - int转换将四舍五入

    ```c++
    Stonewt::operator int() const
    {

        return int(pounds + 0.5);
    }

    Stonewt::operator double() const
    {
        return pounds;
    }
    ```

    ```cmd
    // stone1.cpp -- user-defined conversion functions
    // compile with stonewt1.cpp
    #include <iostream>
    #include "stonewt1.h"

    int main()
    {
        using std::cout;
        Stonewt poppins(9, 2.8); // 9 stone, 2.8 pounds
        double p_wt = poppins;   // implicit conversion
        cout << "Convert to double => ";
        cout << "Poppins: " << p_wt << " pounds.\n";
        cout << "Convert to int => ";
        cout << "Poppins: " << int(poppins) << " pounds.\n";
        // std::cin.get();
        system("pause");
        return 0;
    }
    ```

    - 如果不使用int强制转换

      编译器不知道该转向int还是double，将会引发二义性，而当只定义一种类型转换时，编译器会通过编译，因为只有一种转换格式

      赋值情况类似，如果

      ```c++
      long gone = poppins;
      ```

      也会报错，因为二义性

      但这样是可以的

      ```c++
      long gone = double(poppins);
      long gone = (int)poppins;
      ```

    - c++11之后可以使用explict用于显示转换
