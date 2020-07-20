# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapter 10

- stock00-usestok0

  - 创建类
    - 注意到函数set_tot()定义在类声明中，这使得这个函数成为内联函数

  ```c++
  // stock00.h -- Stock class interface
  // version 00
  #ifndef STOCK00_H_
  #define STOCK00_H_

  #include <string>

  class Stock // class declaration
  {
  private:
      std::string company;
      long shares;
      double share_val;
      double total_val;
      void set_tot() { total_val = shares * share_val; }

  public:
      void acquire(const std::string &co, long n, double pr);
      void buy(long num, double price);
      void sell(long num, double price);
      void update(double price);
      void show();
  }; // note semicolon at the end

  #endif
  ```

  - 创建对象

  ```c++
  Stock sally;
  ```

  - 类对象默认访问控制

    ```c++
    class World
    {
        // private by default
        float mass;
        char name[20];
    public:
        void tellall(void);
        ...
    };
    ```

    - 类的默认访问权限为private
    - 结构的默认访问权限为public

  - 类的成员函数
    - 定义成员函数时，需要使用作用域（::）来标识函数所属的类
    - 类方法可以访问类的private组件

  - 定义类的成员函数

  ```c++
  // stock00.cpp -- implementing the Stock class
  // version 00
  #include <iostream>
  #include "stock00.h"

  void Stock::acquire(const std::string &co, long n, double pr)
  {
      company = co;
      if (n < 0)
      {
          std::cout << "Number of shares can't be negative; "
                    << company << " shares set to 0.\n";
          shares = 0;
      }
      else
          shares = n;
      share_val = pr;
      set_tot();
  }

  void Stock::buy(long num, double price)
  {
      if (num < 0)
      {
          std::cout << "Number of shares purchased can't be negative. "
                    << "Transaction is aborted.\n";
      }
      else
      {
          shares += num;
          share_val = price;
          set_tot();
      }
  }

  void Stock::sell(long num, double price)
  {
      using std::cout;
      if (num < 0)
      {
          cout << "Number of shares sold can't be negative. "
               << "Transaction is aborted.\n";
      }
      else if (num > shares)
      {
          cout << "You can't sell more than you have! "
               << "Transaction is aborted.\n";
      }
      else
      {
          shares -= num;
          share_val = price;
          set_tot();
      }
  }

  void Stock::update(double price)
  {
      share_val = price;
      set_tot();
  }

  void Stock::show()
  {
      std::cout << "Company: " << company
                << "  Shares: " << shares << '\n'
                << "  Share Price: $" << share_val
                << "  Total Worth: $" << total_val << '\n';
  }
  ```

  - 类外定义内联函数

    - 只需在内外定义是类型前加上inline

    - 为确保内联函数的特殊规则（每个使用他们的文件都需要对其进行定义），最简便的方法是将内联定义放在头文件中（智能链接程序允许将内联定义放到独立的实现文件）

  - 使用类

    ```c++
    // usestok0.cpp -- the client program
    // compile with stock.cpp
    #include <iostream>
    #include "stock00.h"

    int main()
    {
        Stock fluffy_the_cat;
        fluffy_the_cat.acquire("NanoSmart", 20, 12.50);
        fluffy_the_cat.show();
        fluffy_the_cat.buy(15, 18.125);
        fluffy_the_cat.show();
        fluffy_the_cat.sell(400, 20.00);
        fluffy_the_cat.show();
        fluffy_the_cat.buy(300000, 40.125);
        fluffy_the_cat.show();
        fluffy_the_cat.sell(300000, 0.125);
        fluffy_the_cat.show();
        // std::cin.get();
        system("pause");
        return 0;
    }
    ```

    ```cmd
    Company: NanoSmart  Shares: 20
      Share Price: $12.5  Total Worth: $250
    Company: NanoSmart  Shares: 35
      Share Price: $18.125  Total Worth: $634.375
    You can't sell more than you have! Transaction is aborted.
    Company: NanoSmart  Shares: 35
      Share Price: $18.125  Total Worth: $634.375
    Company: NanoSmart  Shares: 300035
      Share Price: $40.125  Total Worth: $1.20389e+007
    Company: NanoSmart  Shares: 35
      Share Price: $0.125  Total Worth: $4.375
    ```

- stock10-usestok1

  - 使用构造函数和析构函数创建类

    ```c++
    // stock10.h � Stock class declaration with constructors, destructor added
    #ifndef STOCK1_H_
    #define STOCK1_H_
    #include <string>
    class Stock
    {
    private:
        std::string company;
        long shares;
        double share_val;
        double total_val;
        void set_tot() { total_val = shares * share_val; }

    public:
        Stock(); // default constructor
        Stock(const std::string &co, long n = 0, double pr = 0.0);
        ~Stock(); // noisy destructor
        void buy(long num, double price);
        void sell(long num, double price);
        void update(double price);
        void show();
    };

    #endif

    ```

  - 定义类的构造和析构函数

    ```c++
    // stock1.cpp � Stock class implementation with constructors, destructor added
    #include <iostream>
    #include "stock10.h"

    // constructors (verbose versions)
    Stock::Stock() // default constructor
    {
        std::cout << "Default constructor called\n";
        company = "no name";
        shares = 0;
        share_val = 0.0;
        total_val = 0.0;
    }

    Stock::Stock(const std::string &co, long n, double pr)
    {
        std::cout << "Constructor using " << co << " called\n";
        company = co;

        if (n < 0)
        {
            std::cout << "Number of shares can't be negative; "
                      << company << " shares set to 0.\n";
            shares = 0;
        }
        else
            shares = n;
        share_val = pr;
        set_tot();
    }
    // class destructor
    Stock::~Stock() // verbose class destructor
    {
        std::cout << "Bye, " << company << "!\n";
    }

    // other methods
    void Stock::buy(long num, double price)
    {
        if (num < 0)
        {
            std::cout << "Number of shares purchased can't be negative. "
                      << "Transaction is aborted.\n";
        }
        else
        {
            shares += num;
            share_val = price;
            set_tot();
        }
    }

    void Stock::sell(long num, double price)
    {
        using std::cout;
        if (num < 0)
        {
            cout << "Number of shares sold can't be negative. "
                 << "Transaction is aborted.\n";
        }
        else if (num > shares)
        {
            cout << "You can't sell more than you have! "
                 << "Transaction is aborted.\n";
        }
        else
        {
            shares -= num;
            share_val = price;
            set_tot();
        }
    }

    void Stock::update(double price)
    {
        share_val = price;
        set_tot();
    }

    void Stock::show()
    {
        using std::cout;
        using std::ios_base;
        // set format to #.###
        ios_base::fmtflags orig =
            cout.setf(ios_base::fixed, ios_base::floatfield);
        std::streamsize prec = cout.precision(3);

        cout << "Company: " << company
             << "  Shares: " << shares << '\n';
        cout << "  Share Price: $" << share_val;
        // set format to #.##
        cout.precision(2);
        cout << "  Total Worth: $" << total_val << '\n';

        // restore original format
        cout.setf(orig, ios_base::floatfield);
        cout.precision(prec);
    }
    ```

  - 使用类（构造和析构版本）

    ```c++
    // usestok1.cpp -- using the Stock class
    // compile with stock10.cpp
    #include <iostream>
    #include "stock10.h"

    int main()
    {
      {
        using std::cout;
        cout << "Using constructors to create new objects\n";
        Stock stock1("NanoSmart", 12, 20.0); // syntax 1
        stock1.show();
        Stock stock2 = Stock("Boffo Objects", 2, 2.0); // syntax 2
        stock2.show();

        cout << "Assigning stock1 to stock2:\n";
        stock2 = stock1;
        cout << "Listing stock1 and stock2:\n";
        stock1.show();
        stock2.show();

        cout << "Using a constructor to reset an object\n";
        stock1 = Stock("Nifty Foods", 10, 50.0); // temp object
        cout << "Revised stock1:\n";
        stock1.show();
        cout << "Done\n";
      }
      // std::cin.get();
      system("pause");
      return 0;
    }
    ```

    ```cmd
    Using constructors to create new objects
    Constructor using NanoSmart called
    Company: NanoSmart  Shares: 12
      Share Price: $20.000  Total Worth: $240.00
    Constructor using Boffo Objects called
    Company: Boffo Objects  Shares: 2
      Share Price: $2.000  Total Worth: $4.00
    Assigning stock1 to stock2:
    Listing stock1 and stock2:
    Company: NanoSmart  Shares: 12
      Share Price: $20.000  Total Worth: $240.00
    Company: NanoSmart  Shares: 12
      Share Price: $20.000  Total Worth: $240.00
    Using a constructor to reset an object
    Constructor using Nifty Foods called
    Bye, Nifty Foods!
    Revised stock1:
    Company: Nifty Foods  Shares: 10
      Share Price: $50.000  Total Worth: $500.00
    Done
    Bye, NanoSmart!
    Bye, Nifty Foods!
    ```

    - 注意到main{}括号里还有括号{}

      这是代码块，即stock1，stock2等自动变量将在程序退出其定义所属代码块时消失

    - 创建实例的两种方式

      ```c++
      Stock stock1("NanoSmart", 12, 20.0);
      ```

      ```c++
      Stock stock2 = Stock("Boffo Objects", 2, 2.0);
      ```

      注意这里，有的编译器会立即删除创建的临时变量，也就会多出一行

      ```cmd
      Bye, Boffo Object!
      ```

    - 注意类对象赋值

      ```c++
      stock2 = stock1;
      ```

      默认情况下，给类对象赋值，将一个对象的成员赋值给另一个（所有内容）

    - 注意到构造函数的另一个作用

      ```c++
      stock1 = Stock("Nifty Foods", 10, 50.0);
      ```

      赋值以改变类内容，

      **注意**，如果既可以通过初始化，也可以通过赋值来设置对象的值，应该通过初始化来完成，这样更高效。

- stock20-usestok2

  - 对象数组

  ```c++
  const int STKS = 4;
  Stock stocks[STKS] = {
      Stock("NanoSmart", 12, 20.0),
      Stock("Boffo Objects", 200, 2.0),
      Stock("Monolithic Obelisks", 130, 3.25),
      Stock("Fleep Enterprises", 60, 6.5)};
  ```

  - 指针访问

  ```c++
  const Stock *top = &stocks[0];
  for (st = 1; st < STKS; st++)
      top = &top->topval(stocks[st]);
  // now top points to the most valuable holding
  std::cout << "\nMost valuable holding:\n";
  top->show();
  ```

  - 数组访问

  ```c++
  int st;
  for (st = 0; st < STKS; st++)
      stocks[st].show();
  ```

- stack-stacker

  - 抽象数据类型-栈

    - 构造函数的使用

    - 传统枚举

    - const成员函数

      成员函数声明和定义之后使用const，说明将不修改函数隐式地访问的对象（隐式的是指使用类内数据成员）

  ```c++
  // stack.h -- class definition for the stack ADT
  #ifndef STACK_H_
  #define STACK_H_

  typedef unsigned long Item;

  class Stack
  {
  private:
      enum
      {
          MAX = 10
      };               // constant specific to class
      Item items[MAX]; // holds stack items
      int top;         // index for top stack item
  public:
      Stack();
      bool isempty() const;
      bool isfull() const;
      // push() returns false if stack already is full, true otherwise
      bool push(const Item &item); // add item to stack
      // pop() returns false if stack already is empty, true otherwise
      bool pop(Item &item); // pop top into item
  };
  #endif
  ```

  ```c++
  // stack.cpp -- Stack member functions
  #include "stack.h"
  Stack::Stack() // create an empty stack
  {
      top = 0;
  }

  bool Stack::isempty() const
  {
      return top == 0;
  }

  bool Stack::isfull() const
  {
      return top == MAX;
  }

  bool Stack::push(const Item &item)
  {
      if (top < MAX)
      {
          items[top++] = item;
          return true;
      }
      else
          return false;
  }

  bool Stack::pop(Item &item)
  {
      if (top > 0)
      {
          item = items[--top];
          return true;
      }
      else
          return false;
  }
  ```

  ```c++
  // stacker.cpp -- testing the Stack class
  #include <iostream>
  #include <cctype> // or ctype.h
  #include "stack.h"
  int main()
  {
      using namespace std;
      Stack st; // create an empty stack
      char ch;
      unsigned long po;
      cout << "Please enter A to add a purchase order,\n"
           << "P to process a PO, or Q to quit.\n";
      while (cin >> ch && toupper(ch) != 'Q')
      {
          while (cin.get() != '\n')
              continue;
          if (!isalpha(ch))
          {
              cout << '\a';
              continue;
          }
          switch (ch)
          {
          case 'A':
          case 'a':
              cout << "Enter a PO number to add: ";
              cin >> po;
              if (st.isfull())
                  cout << "stack already full\n";
              else
                  st.push(po);
              break;
          case 'P':
          case 'p':
              if (st.isempty())
                  cout << "stack already empty\n";
              else
              {
                  st.pop(po);
                  cout << "PO #" << po << " popped\n";
              }
              break;
          }
          cout << "Please enter A to add a purchase order,\n"
               << "P to process a PO, or Q to quit.\n";
      }
      cout << "Bye\n";
      system("pause");
      return 0;
  }
  ```

  ```cmd
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  A
  Enter a PO number to add: 123
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  P
  PO #123 popped
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  A
  Enter a PO number to add: 213
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  A
  Enter a PO number to add: 2143
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  P
  PO #2143 popped
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  A
  Enter a PO number to add: 4332
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  A
  Enter a PO number to add: 2345
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  P
  PO #2345 popped
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  P
  PO #4332 popped
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  P
  PO #213 popped
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  P
  stack already empty
  Please enter A to add a purchase order,
  P to process a PO, or Q to quit.
  Q
  Bye
  ```
