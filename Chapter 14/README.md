# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapter 14

- studentc-use_stuc

  - explicit的使用

    ```c++
    class Student
    {
    private:
        ...
    public:
        ...
        explicit Student(const std::string& s): name(s), scores() {}
        explicit Student(int n) : name("Nully"), scores(n) {}

        Student(const std::string& s, int n): name(s), scores(n) {}
    }
    ```

    explicit可以阻止隐式转换的发生

    **注意**：当类的声明和定义分别在两个文件中时，explicit只能写在在声明中，不能写在定义中。

    如果没有使用explicit关键字，

    ```c++
    Student doh("Homer", 10);
    doh = 5;
    ```

    将隐式调用Student(5)将5转换为一个临时的Student对象，并用"Nully"来设置成员name的值，因此复制操作将使用临时对象来替代原来的doh的值。**使用explicit后，编译器将认为上述赋值运算符是错误的。**

- studentci-use_stuci

  - 私有继承,访问基类方法

    ```c++
    class Student : private std::string, private std::valarray<double>
    {
    private:
        ...
    public:
        ...
        explicit Student(const std::string & s): std::string(s), ArrayDb() {}
        explicit Student(int n) : std::string("Nully"), ArrayDb(n) {}

        Student(const char * str, const double * pd, int n): std::string(str), ArrayDb(pd, n) {}
    }
    ```

    私有继承std::string,std::valarryay<double>提供了两个无名称的子对象成员，即隐式地继承组件而不是成员对象，并且派生类私有继承基类，将导致基类私有成员被隐藏，因此不能使用name和scores来描述对象了。

    并且私有继承和公有继承不同，私有继承使得能够使用类名地作用域解析运算符来调用基类地方法，而公有继承将使用对象名来调用方法：

    - 私有继承，调用基类公有方法

    ```c++
    double Student::Average() const
    {
        if (ArrayDb::size() > 0)
            return ArrayDb::sum()/ArrayDb::size();
        else
            return 0;
    }
    ```

    - 公有继承，调用基类公有方法

    ```c++
    double Student::Average() const
    {
        if (scores.size() > 0)
            return scores.sum()/scores.size();
        else
            return 0;
    }
    ```

  - 访问基类对象

    因为string对象没得名称，只能使用强制类型转换。因为Student是通过string类派生而来，所以可以通过强制类型转换，来将Student转换为string对象；返回为继承而来地string对象：

    ```c++
    const string & Student::Name() const
    {
        return (const string &) *this;
    }
    ```

    指针this指向用来调用方法地对象，因此\*this为用来调用方法地对象，为避免调用构造函数创建新地对象，可以使用强制类型转换来创建一个引用(const string &)，**这里返回指向用于调用该方法地Student对象中地继承而来地string对象地引用**

  - 访问基类友元函数

    友元不属于类，因此不能通过类名调用，但是可以通过显示地转换为基类来调用正确地友元

    ```c++
    ostream & operator<<(ostream & os, const Student & stu)
    {
        os << "Scores for " << (const string &) stu  << ":\n";
        ...
    }
    ```

    代码

    ```c++
    os << "Scores for " << (const string &) stu  << ":\n";
    ```

    显示地将stu转换为string对象引用，进而调用函数operator<<(ostream &, const String &)。

    引用stu不会自动转换为string 引用。根本原因在于，在私有继承中，在不进行显式类型转换的情况下，不能将指向派生类的引用或指针赋给基类引用或指针。
    然而，即使这个例子是公有继承，也应当使用显示类型转换。因为如果不使用类型转换，下面代码将递归调用友元

    ```c++
    os << stu;
    ```

    并且，这个例子是多继承，如果不显示调用，那么会产生二义性。

- worker0-worktest

  - 多重继承

    ```c++
    class Worker
    {
        ...
    };
    class Waiter : public Woker
    {
        ...
    };
    class Singer : public Worker
    {
        ...
    };
    ```

    这里会有一个问题，假设首先就从Singer和Waiter公有派生出SingingWaiter：

    ```c++
    class SingingWaiter : public Singer, public Waiter
    {
        ...
    };
    ```

    因为Singer和Waiter都继承了一个Worker组件，因此SingingWaiter将包含两个Worker组件。这将产生问题，因为通常派生类对象地地址能赋给基类指针，但现在将出现二义性：

    ```c++
    SingingWaiter ed;
    Worker * pw = &ed;
    ```

    通常这种赋值将把基类指针设置为派生对象中地基类对象地地址。但ed中包含两个Worker对象，有两个地址可供选择，所以应使用类型转换来指定对象：

    ```c++
    Worker * pw1 = (Waiter *) &ed;
    Worker * pw2 = (Singer *) &ed;
    ```

    这使得使用基类指针引用不同的对象复杂化。

  - 虚基类

    虚基类解决了多重继承的问题，虚基类使得从多个类（基类相同）派生出的对象只继承一个基类对象。例如

    ```c++
    class Singer : virtual public Worker{...};
    class Waiter : public virtual Worker{...};
    ```

    然后，可以将SingingWaiter类定义为：

    ```c++
    class SingingWaiter : public Singer, public Waiter{...};
    ```

    现在，SingingWaiter对象将只包含Worker对象的一个副本。从本质上来说，继承的Singer和Waiter对象共享一个Worker对象。

    - 虚基类将使自动传递不起作用

      ```c++
      Singingwaiter(const worker& wk,int p = o,int v = Singer::other): waiter (wk,p), singer(wk,v) {...}
      ```

      以上，自动传递信息是，将通过两条不同的途径将wk传递给Worker对象。

      为了避免这种冲突，C++在基类是虚的时候，禁止消息通过中间类自动传递。

      因此，上述构造函数将初始化waiter的p和singer的v，但wk参数不会传递。

      然而，编译器必须在构造派生类对象之前构造基类对象组件；在上述情况下，编译器将使用Worker的默认构造函数。

      当然，也可以这样显示的调用所需的基类构造函数：

      ```c++
      Singingwaiter(const worker& wk,int p = o,int v = Singer::other)
          : Worker(wk), waiter (wk,p), singer(wk,v) {...}
      ```

      **注意**：对于虚基类，必须这样做；但对于非基类，则是非法的。

      **另外**：如果有间接虚基类，则除非只需使用该虚基类的默认构造函数，否则必须显示调用该虚基类的某个构造函数。

- workemi-workmi
  - 使用虚基类

- stacktp-stacktem
  - 类模板的使用

- stacktp-stkoptr1
  - 类模板实现new

- arraytp-twod

  - 容器类array

    ```c++
    template <class T, int n>
    class ArrayTP
    {
        ...
    };
    ```

    class和typename指出T为类型参数；n这种参数称为非类型或表达式参数。

    **表达式参数**有一些限制，表达式参数可以是整型、枚举、引用或指针。因此double m是不合法的，而double \* rm是合法的。另外，模板代码不能修改表达式参数的值。

    表达式参数方法的缺点是，每种数组大小都将生成自己的模板：

    ```c++
    ArrayTP<double, 12> egg;
    ArrayTP<double, 13> donuts;
    ```

    会生成两个独立的类声明，

    ```c++
    Stack<int> egg(12);
    Stack<int> dunkers(13);
    ```

    只生成一个类声明。

- pairs

  ```c++
  template <class T1, class T2>
  class Pair
  {
      ...
  public:
      ...
      T1 &first();
  };

  template <class T1, class T2>
  T1 &Pair<T1, T2>::first()
  {
      return a;
  }
  ```

  注意到，first名使用了Pair<T1, T2>::first，这是因为模板类类名是Pair<T1, T2>

  - 默认类型模板参数

    template <class T1, class T2 = int>在实例化时可以不提供T2的值

- tempmemb

  - 成员模板

  ```c++
  // tempmemb.cpp -- template members
  #include <iostream>
  using std::cout;
  using std::endl;

  template <typename T>
  class beta
  {
  private:
      template <typename V> // nested template class member
      class hold
      {
      private:
          V val;

      public:
          hold(V v = 0) : val(v) {}
          void show() const { cout << val << endl; }
          V Value() const { return val; }
      };
      hold<T> q;   // template object
      hold<int> n; // template object
  public:
      beta(T t, int i) : q(t), n(i) {}
      template <typename U> // template method
      U blab(U u, T t)
      {
          return (n.Value() + q.Value()) * u / t;
      }
      void Show() const
      {
          q.show();
          n.show();
      }
  };

  int main()
  {
      beta<double> guy(3.5, 3);
      cout << "T was set to double\n";
      guy.Show();
      cout << "V was set to T, which is double, then V was set to int\n";
      cout << guy.blab(10, 2.3) << endl;
      cout << "U was set to int\n";
      cout << guy.blab(10.0, 2.3) << endl;
      cout << "U was set to double\n";
      cout << "Done\n";
      // std::cin.get();
      system("pause");
      return 0;
  }
  ```

- temppam

  - 将模板用做参数

  ```c++
  template <template <typename T> class Thing>
  class Crab
  {
  private:
      Thing<int> s1;
      Thing<double> s2;
      ...
  };
  main(){
      ...
      Crab<Stack> nebula;
  }
  ```

  nebula声明将用Stack\<int\>替换Thing\<int\>，用Stack\<double\>替换Thing\<double\>

  也可以混合使用模板参数和常规参数:

  ```c++
  template <template <typename T> class Thing, typename U, typename V>
  class Crab
  {
  private:
      Thing<U> s1;
      Thing<V> s2;
      ...
  }
  ```

- frnd2tmp,tmp2tmp,manyfrnd

  - 模板类和友元

    模板类的友元：

    - 非模板友元frnd2tmp

      只有可能友元的参数时模板类实例

    - 约束模板友元tmp2tmp

      友元函数本身是模板函数或显示具体化，在外部定义定义实现，在类内部作为友元

    - 非约束模板友元manyfrnd

      直接把友元作为模板，即成员模板友元
