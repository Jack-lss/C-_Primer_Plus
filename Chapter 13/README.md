# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapter 13

- tabtenn0-usett0

  - 初始刷列表和普通初始化的区别

    - 初始化列表

    ```c++
    TableTennisPlayer::TableTennisPlayer (const string & fn,
        const string & ln, bool ht) : firstname(fn),lastname(ln), hasTable(ht) {}
    ```

    直接使用string的复制构造函数将firstname初始化为fn。

    - 普通初始化

    ```c++
    TableTennisPlayer::TableTennisPlayer (const string & fn, const string & ln, bool ht)
    {
        firstname = fn;
        lastname = ln;
        hasTable = ht;
    }
    ```

    首先为firstname调用string的默认构造函数，再调用string的赋值运算符将firstname设置为fn。

- tabtenn1-usett1

  - 公有派生

    ```c++
    class RatedPlayer : public TableTennisPlayer
    {
      ...
    };
    ```

  - 派生类构造函数

    - 普通初始化派生类成员

    ```c++
    RatedPlayer::RatedPlayer(unsigned int r, const string & fn,
         const string & ln, bool ht) : TableTennisPlayer(fn, ln, ht)
    {
        rating = r;
    }
    ```

    使用初始化列表初始化基类成员（使用基类的构造函数初始化）。

    - 初始化列表初始化派生类成员

    ```c++
    RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer & tp)
        : TableTennisPlayer(tp), rating(r)
    {
    }
    ```

    和usett0一样的道理。

- brass-usebrass1

  - virtual的使用

    ```c++
    class Brass
    {
      ...
    public:
        virtual void Withdraw(double amt);
        virtual void ViewAcct() const;
        virtual ~Brass() {}
    };

    //Brass Plus Account Class
    class BrassPlus : public Brass
    {
      ...
    public:
        virtual void ViewAcct()const;
        virtual void Withdraw(double amt);
    };
    ```

    - 例，两个ViewAcct()原型将有2个独立的方法定义，基类版本的限定名为Brass::ViewAcct()，派生类版本的限定名为BrassPlus::ViewAcct()。程序将使用对象类型来确定使用哪个版本：

      ```c++
      Brass dom("Dominic Banker", 11224, 4183.45);
      BrassPlus dot("Dorothy Banker", 12118, 2592.00);
      dom.ViewAvvt(); //使用Brass::ViewAcct()
      dot.ViewAvvt(); //使用BrassPlus::ViewAcct()
      ```

      同样，Withdraw()也有2个版本，一个供Brass对象来使用，另一个供BrassPlus对象使用。

    - 使用virtual，如果方法是通过引用或指针而不是对象调用的

      1. 如果没有使用关键字virtual，程序将根据**引用类型或指针类型**选择方法；
      2. 如果使用关键字virtual，程序将根据**引用或指针指向的对象的类型**来选择方法。

      如果ViewAcct()不是虚的

      ```c++
      Brass dom("Dominic Banker", 11224, 4183.45);
      BrassPlus dot("Dorothy Banker", 12118, 2592.00);
      Brass & b1_ref = dom;
      Brass & b2_ref = dot;
      b1_ref.ViewAcct(); //使用Brass::ViewAcct()
      b1_ref.ViewAcct(); //使用Brass::ViewAcct()
      ```

      如果ViewAcct()是虚的

      ```c++
      Brass dom("Dominic Banker", 11224, 4183.45);
      BrassPlus dot("Dorothy Banker", 12118, 2592.00);
      Brass & b1_ref = dom;
      Brass & b2_ref = dot;
      b1_ref.ViewAcct(); //使用Brass::ViewAcct()
      b1_ref.ViewAcct(); //使用BrassPlus::ViewAcct()
      ```

    - 注意方法在基类中声明为virtual后，它在派生类中将自动成为虚方法，然而，在派生类声明中使用关键字virtual来指出那些函数为虚函数也是很正确的

    - 在基类中声明virtual的析构函数时，将按正确的顺序调用析构函数

    - 构造函数不能是虚函数；析构函数应当是虚函数，除非类不用做基类；友元不能是虚函数，但可以使用虚函数

    - 重定义的继承方法不是重载

    - 返回类型协变

      重定义继承方法应与原型完全相同，但如果返回类型是基类引用或指针，则可以修改为指向派生类的引用或指针。这种特性被称为返回类型协变，因为这样可以随着类型的变化而变化。

      ```c++
      class Dwelling
      {
      public:
          virtual Dwelling & build(int n);
      };
      class Hovel : public Dwelling
      {
      public:
          virtual Hocel & build(int n);
      };
      ```

      这种例外只适合返回值，而不适合参数

    - 如果基类声明被重载，则应该在派生类中重新定义所有的基类版本

      如果只想使用某些而不是全部基类的虚函数，应当为其他的虚函数在派生类增加定义：

      ```c++
      void Hovel::showperks() const {Dwelling::showperks();}
      ```

- acctabc-usebrass3

  - 抽象基类

    至少有一个函数是纯虚函数，纯虚函数可以不定义，抽象基类应当充当接口

- dma-usedma
  - 动态分配空间的继承机制
