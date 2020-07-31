# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapterm 15

- tv-use_tv

  - 友元类

    ```c++
    class Tv
    {
        ...
    public:
        friend class Remote;
    };
    class Remote
    {
        ...
    };
    ```

- tvfm

  - 友元成员函数

    避免不需要类成员为友元的方法，只将一部分类成员作为友元

    ```c++
    class Tv
    {
        friend void Remote::set_chan(Tv & t, int c);
        ...
    };
    ```

    然而这意味着Tv类需要知道Remote类和其成员，所以Remote的定义必须提到Tv定义的前面。但是Remote的方法提到了Tv对象，多以Tv的定义必须提到Remove定义的前面，这就造成矛盾。解决方法是前向声明类：

    ```c++
    class Tv;
    class Remote{...};
    class Tv
    {
        ...
        friend class Remote;
    };
    ```

    相反，这样是不被允许的

    ```c++
    class Remote;
    class Tv
    {
        ...
        friend class Remote;
    };
    class Remote{...};
    ```

    因为编译器在Tv中看到Remote的一个方法被声明为Tv类的友元之前，必须看到Remote类的声明和set_chan()方法的声明。

    前向声明应该还需要注意，如果Remote中的成员调用了Tv的方法，需要只声明而在Tv类之后进行定义。

    另外，让Remote类称为友元时，**不需要前向声明**，因为友元语句本身已经说明Remote是一个类。

- queuetp-nested

  - 模板中的嵌套

    ```c++
    template <class Item>
    class QueueTP
    {
    private:
        class Node
        {
        public:
            Item item;
            ...
        };
        ...
    };
    ```

- error1

  - 异常处理，使用abort()

    ```c++
    #include <cstdlib>
    ...
    double hmean(double a, double b)
    {
        if(a == -b)
        {
            cout << "untenable arguments to hmean()\n";
            abort();
        }
        return 2.0 * a * b / (a + b);
    }
    ```

    在hmean()中调用abort()函数将直接终止程序，而不是先返回到main()。一般而言，显示的程序异常终端信息随编译器而异。为了避免异常终止，程序应在调用hmean()之前检查x和y的值。

- error2

  - 异常处理，返回错误码

    ```c++
    #include <cfloat> //or float.h for DBL_MAX
    bool hmean(double a, double b, double * ans)
    {
        if(a == -b)
        {
            *ans = DBL_MAX;
            return flase;
        }
        else
        {
            *ans = 2.0 * a * b / (a + b);
            return true;
        }
    }
    ```

- error3

  - 异常处理，try块

    ```c++
    while(cin >> x >> y)
    {
        try{
            z = hmean(x, y);
        }
        catch (const char * s)
        {
            cout << s << endl;
            cout << "Enter a new pair of numbers; ";
            continue;
        }
        cout << "Harmonic mean of " << x << " and " << y
            << " is " << z << endl;
        cout << "Enter next set of numbers <q to quit>: ";
    }
    cout << "Bye!\n";
    ...
    double hmean(double a, double b)
    {
        if(a == -b)
            throw "bad hmean() arguments: a = -b not allowed";
        return 2.0 * a * b / (a + b);
    }
    ```

    走到

    ```c++
    try{
        z = hmean(x, y);
    }
    ```

    如果其中的某条语句导致异常被引发，则后面的catch块将对异常进行处理。引发的异常是字符串"bad hmean() arguments: a = -b not allowed"。异常类型可以是字符串或者其他C++类型：通常为类类型。

    执行throw语句类似执行返回语句没因为它也将终止函数的执行；但throw不是将控制权返回给调用程序，而是导致程序沿函数调用序列后退多步的例子。这里的例子中，throw将程序控制权返回给main()。程序将在main()中寻找与引发的异常类型匹配的异常处理程序（位于try块后面）。

    ```c++
    catch (const char * s)
    {
        cout << s << endl;
        cout << "Enter a new pair of numbers; ";
        continue;
    }
    ```

    catch块类似于函数定义，但不是函数定义。关键字catch表面这是一个处理程序，而char \* s则表明该处理程序与字符串异常匹配。s与函数参数定义极为类似，因为**匹配的引发将赋给s**。另外，当异常与该处理程序匹配时，程序将执行括号中的代码。

    执行完try块的语句后，如果没有引发任何异常，则程序跳过try块后面的catch块，直接执行处理程序后面的第一条语句。

- exc_mean-error4

  - 异常处理，将对象用作异常类型

    ```c++
    class bad_hmean
    {
    private:
        double v1;
        double v2;
    public:
        bad_hmean(double a = 0, double b = 0) : v1(a), v2(b) {}
        void mesg();
    };
    inline void bad_hmean::mesg()
    {
        std::cout << "hmean(" << v1 << ", " << v2 << "): " << "invalid arguments: a = -b\n";
    }

    class bad_gmean
    {
    public:
        double v1;
        double v2;
        bad_gmean(double a = 0, double b = 0) : v1(a), v2(b) {}
        const char* mesg();
    };
    inline const char* bad_gmean::mesg()
    {
        return "gmean() arguments should be >= 0\n";
    }
    ```

    ```c++
    //error4.cpp ?using exception classes
    #include <iostream>
    #include <cmath> // or math.h, unix users may need -lm flag
    #include "exc_mean.h"
    // function prototypes
    double hmean(double a, double b);
    double gmean(double a, double b);
    int main()
    {
        using std::cout;
        using std::cin;
        using std::endl;

        double x, y, z;

        cout << "Enter two numbers: ";
        while (cin >> x >> y)
        {
            try {                  // start of try block
                z = hmean(x, y);
                cout << "Harmonic mean of " << x << " and " << y
                    << " is " << z << endl;
                cout << "Geometric mean of " << x << " and " << y
                    << " is " << gmean(x, y) << endl;
                cout << "Enter next set of numbers <q to quit>: ";
            }// end of try block
            catch (bad_hmean& bg)    // start of catch block
            {
                bg.mesg();
                cout << "Try again.\n";
                continue;
            }
            catch (bad_gmean& hg)
            {
                cout << hg.mesg();
                cout << "Values used: " << hg.v1 << ", "
                    << hg.v2 << endl;
                cout << "Sorry, you don't get to play any more.\n";
                break;
            } // end of catch block
        }
        cout << "Bye!\n";
        // cin.get();
        // cin.get();
        return 0;
    }
    double hmean(double a, double b)
    {
        if (a == -b)
            throw bad_hmean(a, b);
        return 2.0 * a * b / (a + b);
    }

    double gmean(double a, double b)
    {
        if (a < 0 || b < 0)
            throw bad_gmean(a, b);
        return std::sqrt(a * b);
    }
    ```

- exc_mean-error5

  - 栈解退

    程序进行栈解退以回到能够捕获异常的地方，并释放栈中自动储存型变量。如果变量是类对象，将为该对象调用析构函数。

- newexcp

  - 异常处理，new引发bad_alloc异常

    ```c++
    // newexcp.cpp -- the bad_alloc exception
    #include <iostream>
    #include <new>
    #include <cstdlib> // for exit(), EXIT_FAILURE
    using namespace std;

    struct Big
    {
        double stuff[20000];
    };

    int main()
    {
        Big *pb;
        try
        {
            cout << "Trying to get a big block of memory:\n";
            pb = new Big[10000]; // 1,600,000,000 bytes
            cout << "Got past the new request:\n";
        }
        catch (bad_alloc &ba)
        {
            cout << "Caught the exception!\n";
            cout << ba.what() << endl;
            system("pause");
            exit(EXIT_FAILURE);
        }
        cout << "Memory successfully allocated\n";
        pb[0].stuff[0] = 4;
        cout << pb[0].stuff[0] << endl;
        delete[] pb;
        // cin.get();
        system("pause");
        return 0;
    }
    ```

    ```cmd
    //pb = new Big[10000];

    Trying to get a big block of memory:
    Got past the new request:
    Memory successfully allocated
    4

    //pb = new Big[1000000];
    Trying to get a big block of memory:
    Caught the exception!
    std::bad_alloc
    ```

    - new引发runtime_error异常，头文件new包含bad_alloc类的声明，它是从exception类公有派生而来的。
    - 捕获异常后，程序将显示继承的what()方法返回的消息（该消息随实现而异），然后终止。

- sales-use_sales

  - 异常、类和继承

    ```c++
    // sales.h  -- exceptions and inheritance
    #ifndef SALES_H
    #define SALES_H

    #include <stdexcept>
    #include <string>
    class Sales
    {
    public:
        enum { MONTHS = 12 };   // could be a static const
        class bad_index : public std::logic_error
        {
        private:
            int bi;  // bad index value
        public:
            explicit bad_index(int ix, const std::string& s = "Index error in Sales object\n");
            int bi_val() const { return bi; }
            virtual ~bad_index() throw() {}
        };
        explicit Sales(int yy = 0);
        Sales(int yy, const double* gr, int n);
        virtual ~Sales() { }
        int Year() const { return year; }
        virtual double operator[](int i) const;
        virtual double& operator[](int i);
    private:
        double gross[MONTHS];
        int year;
    };

    class LabeledSales : public Sales
    {
    public:
        class nbad_index : public Sales::bad_index
        {
        private:
            std::string lbl;
        public:
            nbad_index(const std::string& lb, int ix,
                const std::string& s = "Index error in LabeledSales object\n");
            const std::string& label_val() const { return lbl; }
            virtual ~nbad_index() throw() {}
        };
        explicit LabeledSales(const std::string& lb = "none", int yy = 0);
        LabeledSales(const std::string& lb, int yy, const double* gr, int n);
        virtual ~LabeledSales() { }
        const std::string& Label() const { return label; }
        virtual double operator[](int i) const;
        virtual double& operator[](int i);
    private:
        std::string label;
    };

    #endif // !SALES_H
    ```

    ```c++
    // sales.cpp -- Sales implementation
    #include "sales.h"
    using std::string;

    Sales::bad_index::bad_index(int ix, const string& s)
        : std::logic_error(s), bi(ix)
    {
    }

    Sales::Sales(int yy)
    {
        year = yy;
        for (int i = 0; i < MONTHS; ++i)
            gross[i] = 0;
    }

    Sales::Sales(int yy, const double* gr, int n)
    {
        year = yy;
        int lim = (n < MONTHS) ? n : MONTHS;
        int i;
        for (i = 0; i < lim; ++i)
            gross[i] = gr[i];
        // for i > n and i < MONTHS
        for (; i < MONTHS; ++i)
            gross[i] = 0;
    }

    double Sales::operator[](int i) const
    {
        if (i < 0 || i >= MONTHS)
            throw bad_index(i);
        return gross[i];
    }

    double& Sales::operator[](int i)
    {
        if (i < 0 || i >= MONTHS)
            throw bad_index(i);
        return gross[i];
    }

    LabeledSales::nbad_index::nbad_index(const string& lb, int ix,
        const string& s) : Sales::bad_index(ix, s)
    {
        lbl = lb;
    }

    LabeledSales::LabeledSales(const string& lb, int yy)
        : Sales(yy)
    {
        label = lb;
    }

    LabeledSales::LabeledSales(const string& lb, int yy, const double* gr, int n)
        : Sales(yy, gr, n)
    {
        label = lb;
    }

    double LabeledSales::operator[](int i) const
    {
        if (i < 0 || i >= MONTHS)
            throw nbad_index(Label(), i);
        return Sales::operator[](i);
    }

    double& LabeledSales::operator[](int i)
    {
        if (i < 0 || i >= MONTHS)
            throw nbad_index(Label(), i);
        return Sales::operator[](i);
    }
    ```

    ```c++
    // use_sales.cpp  -- nested exceptions
    #include <iostream>
    #include "sales.h"

    int main()
    {
        using std::cout;
        using std::cin;
        using std::endl;

        double vals1[12] =
        {
            1220, 1100, 1122, 2212, 1232, 2334,
            2884, 2393, 3302, 2922, 3002, 3544
        };

        double vals2[12] =
        {
            12, 11, 22, 21, 32, 34,
            28, 29, 33, 29, 32, 35
        };

        Sales sales1(2011, vals1, 12);
        LabeledSales sales2("Blogstar", 2012, vals2, 12);

        cout << "First try block:\n";
        try
        {
            int i;
            cout << "Year = " << sales1.Year() << endl;
            for (i = 0; i < 12; ++i)
            {

                cout << sales1[i] << ' ';
                if (i % 6 == 5)
                    cout << endl;
            }
            cout << "Year = " << sales2.Year() << endl;
            cout << "Label = " << sales2.Label() << endl;
            for (i = 0; i <= 12; ++i)
            {

                cout << sales2[i] << ' ';
                if (i % 6 == 5)
                    cout << endl;
            }
            cout << "End of try block 1.\n";
        }
        catch (LabeledSales::nbad_index& bad)
        {
            cout << bad.what();
            cout << "Company: " << bad.label_val() << endl;
            cout << "bad index: " << bad.bi_val() << endl;
        }
        catch (Sales::bad_index& bad)
        {
            cout << bad.what();
            cout << "bad index: " << bad.bi_val() << endl;
        }
        cout << "\nNext try block:\n";
        try
        {
            sales2[2] = 37.5;
            sales1[20] = 23345;
            cout << "End of try block 2.\n";
        }
        catch (LabeledSales::nbad_index& bad)
        {
            cout << bad.what();
            cout << "Company: " << bad.label_val() << endl;
            cout << "bad index: " << bad.bi_val() << endl;
        }
        catch (Sales::bad_index& bad)
        {
            cout << bad.what();
            cout << "bad index: " << bad.bi_val() << endl;
        }
        cout << "done\n";
        // std::cin.get();
        return 0;
    }
    ```

- rtti1

  - dynameic_cast运算符

    ```c++
    // rtti1.cpp -- using the RTTI dynamic_cast operator
    #include <iostream>
    #include <cstdlib>
    #include <ctime>

    using std::cout;

    class Grand
    {
    private:
        int hold;

    public:
        Grand(int h = 0) : hold(h) {}
        virtual void Speak() const { cout << "I am a grand class!\n"; }
        virtual int Value() const { return hold; }
    };

    class Superb : public Grand
    {
    public:
        Superb(int h = 0) : Grand(h) {}
        void Speak() const { cout << "I am a superb class!!\n"; }
        virtual void Say() const
        {
            cout << "I hold the superb value of " << Value() << "!\n";
        }
    };

    class Magnificent : public Superb
    {
    private:
        char ch;

    public:
        Magnificent(int h = 0, char c = 'A') : Superb(h), ch(c) {}
        void Speak() const { cout << "I am a magnificent class!!!\n"; }
        void Say() const { cout << "I hold the character " << ch << " and the integer " << Value() << "!\n"; }
    };

    Grand *GetOne();

    int main()
    {
        std::srand(std::time(0));
        Grand *pg;
        Superb *ps;
        for (int i = 0; i < 5; i++)
        {
            pg = GetOne();
            pg->Speak();
            if (ps = dynamic_cast<Superb *>(pg))
                ps->Say();
        }
        // std::cin.get();
        system("pause");
        return 0;
    }

    Grand *GetOne() // generate one of three kinds of objects randomly
    {
        Grand *p;
        switch (std::rand() % 3)
        {
        case 0:
            p = new Grand(std::rand() % 100);
            break;
        case 1:
            p = new Superb(std::rand() % 100);
            break;
        case 2:
            p = new Magnificent(std::rand() % 100, 'A' + std::rand() % 26);
            break;
        }
        return p;
    }
    ```

    ```cmd
    I am a magnificent class!!!
    I hold the character M and the integer 70!
    I am a magnificent class!!!
    I hold the character F and the integer 79!
    I am a grand class!
    I am a grand class!
    I am a grand class!
    ```

    其中

    ```c++
    ps = dynamic_cast<Superb *>(pg)
    ```

    pg指向一个对象，如果pg可以安全地转换为Superb \*，运算符将返回对象地地址，否则返回空指针。

    并且这里判断，如果pg可以安全地转换为Superb指针，返回true

    **如果指向地对象(\*pt)地类型为Type或者是从Type直接或间接派生而来地类型**，则下面地表达式将指针pt转换为Type类型地指针：

    ```c++
    dynamic_cast<Type *>(pt)
    ```

    否则结果为0，即空指针。

- rtti2

  - typeid运算符和type_info类

    ```c++
    typeid(Magnificent) == typeid(*pg)
    ```

    typeid运算符返回一个对type_info对象地引用，其中，type_info是在头文件typeinfo中定义地一个类。

    type_info类重载了==和!=运算符，以便可以使用这些运算符来对类型进行比较。

    以上代码，如果pg是一个空指针，程序将引发bad_typeid异常。该异常类型是从exception类派生而来的，是在头文件typeinfo中声明地。

    **type_info类包含一个name()成员，该函数返回一个随实现而异地字符串；通常是类地名称。**例如，下面地语句显示指针pg指向地对象所属的类定义的字符串：

    ```c++
    cout << typeid(*pg).name();
    ```

- constcast

  - constcast运算符

    ```c++
    const_cast <type-name> (expression)
    ```

    除了const或volatile特征，type_name和expression的类型必须相同。假设High和Low是两个类：

    ```c++
    High bar;
    const High * pbar = &bar;
    ...
    High * pb = const_cast<High *> (pbar);
    const Low * pl = const_cast<const Low *> (pbar);
    ```

    第一个类型转换使得\*pb成为一个可用于修改bar对象值得指针，它删除const标签。

    第二个类型转换是非法得，因为它尝试将const High \*改为const Low \*。

    ```c++
    // constcast.cpp -- using const_cast<>
    #include <iostream>
    using std::cout;
    using std::endl;

    void change(const int *pt, int n);

    int main()
    {
        int pop1 = 38383;
        const int pop2 = 2000;

        cout << "pop1, pop2: " << pop1 << ", " << pop2 << endl;
        change(&pop1, -103);
        change(&pop2, -103);
        cout << "pop1, pop2: " << pop1 << ", " << pop2 << endl;
        // std::cin.get();
        system("pause");
        return 0;
    }

    void change(const int *pt, int n)
    {
        int *pc;

        pc = const_cast<int *>(pt);
        *pc += n;
    }
    ```

    ```cmd
    pop1, pop2: 38383, 2000
    pop1, pop2: 38280, 2000
    ```

    注意到，只有原型不为const得值才能被更改。
