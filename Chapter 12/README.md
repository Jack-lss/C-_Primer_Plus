# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**
- **使用vs2019编译部分代码**

----

## chapter 12

- strngbad-vegnews

  - strngbad.h

  ```c++
  // strngbad.h -- flawed string class definition
  #include <iostream>
  #ifndef STRNGBAD_H_
  #define STRNGBAD_H_
  class StringBad
  {
  private:
      char *str;              // pointer to string
      int len;                // length of string
      static int num_strings; // number of objects
  public:
      StringBad(const char *s); // constructor
      StringBad();              // default constructor
      ~StringBad();             // destructor
                                // friend function
      friend std::ostream &operator<<(std::ostream &os,
                                      const StringBad &st);
  };
  #endif
  ```

  - strngbad.cpp

  ```c++
  // strngbad.cpp -- StringBad class methods
  #include <cstring> // string.h for some
  #include "strngbad.h"
  using std::cout;

  // initializing static class member
  int StringBad::num_strings = 0;

  // class methods

  // construct StringBad from C string
  StringBad::StringBad(const char *s)
  {
      len = std::strlen(s);    // set size
      str = new char[len + 1]; // allot storage
      std::strcpy(str, s);     // initialize pointer
      num_strings++;           // set object count
      cout << num_strings << ": \"" << str
           << "\" object created\n"; // For Your Information
  }

  StringBad::StringBad() // default constructor
  {
      len = 4;
      str = new char[4];
      std::strcpy(str, "C++"); // default string
      num_strings++;
      cout << num_strings << ": \"" << str
           << "\" default object created\n"; // FYI
  }

  StringBad::~StringBad() // necessary destructor
  {
      cout << "\"" << str << "\" object deleted, "; // FYI
      --num_strings;                                // required
      cout << num_strings << " left\n";             // FYI
      delete[] str;                                 // required
  }

  std::ostream &operator<<(std::ostream &os, const StringBad &st)
  {
      os << st.str;
      return os;
  }
  ```

  - vegnews

    调用

    ```c++
    cout << "Starting an inner block.\n";
    StringBad headline1("Celery Stalks at Midnight");
    StringBad headline2("Lettuce Prey");
    StringBad sports("Spinach Leaves Bowl for Dollars");
    cout << "headline1: " << headline1 << endl;
    cout << "headline2: " << headline2 << endl;
    cout << "sports: " << sports << endl;
    ```

    - 构造函数初始化headline1、headline2、sports

      num_strings记录调用构造函数和析构函数次数

      ```cmd
      Starting an inner block.
      1: "Celery Stalks at Midnight" object created
      2: "Lettuce Prey" object created
      3: "Spinach Leaves Bowl for Dollars" object created
      ```

    - 调用友元重载<<函数

      ```cmd
      headline1: Celery Stalks at Midnight
      headline2: Lettuce Prey
      sports: Spinach Leaves Bowl for Dollars
      ```

    ```c++
    void callme1(StringBad &); // pass by reference
    void callme2(StringBad);   // pass by value
    ...
    void callme1(StringBad &rsb)
    {
        cout << "String passed by reference:\n";
        cout << "    \"" << rsb << "\"\n";
    }

    void callme2(StringBad sb)
    {
        cout << "String passed by value:\n";
        cout << "    \"" << sb << "\"\n";
    }
    ```

    - 引用传递进callme1

      ```c++
      callme1(headline1);
      cout << "headline1: " << headline1 << endl;
      ```

      ```cmd
      String passed by reference:
          "Celery Stalks at Midnight"
      headline1: Celery Stalks at Midnight
      ```

    - 值传递进callme2

      ```c++
      callme2(headline2);
      cout << "headline2: " << headline2 << endl;
      ```

      ```cmd
      String passed by value:
          "Lettuce Prey"
      "Lettuce Prey" object deleted, 2 left
      headline2: 葺葺葺葺葺葺葺葺轀
      ```

      **注意**这里调用了析构函数，这是因为headline2作为函数参数来传递。

      虽然函数按值传递能保证原始数据不会被更改，但实际上函数已使原始字符串无法识别，导致了显示非标准字符

    - 类赋值，另一个构造函数

      ```c++
      StringBad sailor = sports;
      cout << "sailor: " << sailor << endl;
      cout << "Assign one object to another:\n";
      StringBad knot;
      knot = headline1;
      cout << "knot: " << knot << endl;
      ```

      ```cmd
      Initialize one object to another:
      sailor: Spinach Leaves Bowl for Dollars
      Assign one object to another:
      3: "C++" default object created
      knot: Celery Stalks at Midnight
      ```

    - 而后结束代码调用析构函数

      ```c++
          cout << "Exiting the block.\n";
      }
      ```

      ```cmd
      Exiting the block.
      "Celery Stalks at Midnight" object deleted, 2 left
      "Spinach Leaves Bowl for Dollars" object deleted, 1 left
      "葺葺葺葺葺葺葺葺葺葺葺葺葺葺葺葺葺葺a" object deleted, 0 left
      ```

      因为自动储存对象被删除的顺序与创建顺序相反，所以最先删除的是sports、sailor、knot，删除knot、sailor时是正确的，但是删除sports时字符串异常，这是

      ```c++
      StringBad sailor = sports;
      ```

      这步的问题，因为它调用了默认赋值构造函数，以上编译器会默认

      ```c++
      StringBad sailor = StringBad(sports);
      ```

      相应的构造函数为

      ```c++
      StringBad(const StringBad &);
      ```

      将会被调用，而num_string不会改变，因为它是默认的

      - 新建一个对象并将其初始化为同类对象时，赋值构造函数将会被调用

        以下声明都将调用复制构造函数

        ```c++
        StringBad ditto(motto);
        StringBad metto = motto;
        StringBad also = StringBad(motto);
        String * pStringBad = new StringBad(motto);
        ```

      - 当函数按值传递对象或函数返回对象时，也将调用复制构造函数

      上方乱码的形成是因为，默认赋值构造函数

      ```c++
      StringBad sailor = sports;
      ```

      等效于

      ```c++
      StringBad sailor;
      sailor.str = sports.str;
      sailor.len = sports.len;
      ```

      只是由于私有成员无法访问，因此上方代码无法通过编译。而这些赋值是传递的字符串的指针，而不是字符串，所以当前一个sports析构函数调用时，后一个sailor中str，len指向的内容将被重置，那显示的就是乱码。

- strng1-saying1

  - string1.h

    ```c++
    // string1.h -- fixed and augmented string class definition

    #ifndef STRING1_H_
    #define STRING1_H_
    #include <iostream>
    using std::ostream;
    using std::istream;

    class String
    {
    private:
        char * str;             // pointer to string
        int len;                // length of string
        static int num_strings; // number of objects
        static const int CINLIM = 80;  // cin input limit
    public:
    // constructors and other methods
        String(const char * s); // constructor
        String();               // default constructor
        String(const String &); // copy constructor
        ~String();              // destructor
        int length () const { return len; }
    // overloaded operator methods
        String & operator=(const String &);
        String & operator=(const char *);
        char & operator[](int i);
        const char & operator[](int i) const;
    // overloaded operator friends
        friend bool operator<(const String &st, const String &st2);
        friend bool operator>(const String &st1, const String &st2);
        friend bool operator==(const String &st, const String &st2);
        friend ostream & operator<<(ostream & os, const String & st);
        friend istream & operator>>(istream & is, String & st);
    // static function
        static int HowMany();
    };
    #endif
    ```

  - string1.cpp

    ```c++
    // string1.cpp -- String class methods
    #include <cstring>                 // string.h for some
    #include "string1.h"               // includes <iostream>
    using std::cin;
    using std::cout;

    // initializing static class member

    int String::num_strings = 0;

    // static method
    int String::HowMany()
    {
        return num_strings;
    }

    // class methods
    String::String(const char * s)     // construct String from C string
    {
        len = std::strlen(s);          // set size
        str = new char[len + 1];       // allot storage
        std::strcpy(str, s);           // initialize pointer
        num_strings++;                 // set object count
    }

    String::String()                   // default constructor
    {
        len = 4;
        str = new char[1];
        str[0] = '\0';                 // default string
        num_strings++;
    }

    String::String(const String & st)
    {
        num_strings++;             // handle static member update
        len = st.len;              // same length
        str = new char [len + 1];  // allot space
        std::strcpy(str, st.str);  // copy string to new location
    }

    String::~String()                     // necessary destructor
    {
        --num_strings;                    // required
        delete [] str;                    // required
    }

    // overloaded operator methods

        // assign a String to a String
    String & String::operator=(const String & st)
    {
        if (this == &st)
            return *this;
        delete [] str;
        len = st.len;
        str = new char[len + 1];
        std::strcpy(str, st.str);
        return *this;
    }

        // assign a C string to a String
    String & String::operator=(const char * s)
    {
        delete [] str;
        len = std::strlen(s);
        str = new char[len + 1];
        std::strcpy(str, s);
        return *this;
    }

        // read-write char access for non-const String
    char & String::operator[](int i)
    {
        return str[i];
    }

        // read-only char access for const String
    const char & String::operator[](int i) const
    {
        return str[i];
    }

    // overloaded operator friends

    bool operator<(const String &st1, const String &st2)
    {
        return (std::strcmp(st1.str, st2.str) < 0);
    }

    bool operator>(const String &st1, const String &st2)
    {
        return st2 < st1;
    }

    bool operator==(const String &st1, const String &st2)
    {
        return (std::strcmp(st1.str, st2.str) == 0);
    }

        // simple String output
    ostream & operator<<(ostream & os, const String & st)
    {
        os << st.str;
        return os;
    }

        // quick and dirty String input
    istream & operator>>(istream & is, String & st)
    {
        char temp[String::CINLIM];
        is.get(temp, String::CINLIM);
        if (is)
            st = temp;
        while (is && is.get() != '\n')
            continue;
        return is;
    }
    ```

  - saying1.cpp

    ```c++
    // sayings1.cpp -- using expanded String class
    // compile with string1.cpp
    #include <iostream>
    #include "string1.h"
    const int ArSize = 10;
    const int MaxLen =81;
    int main()
    {
        using std::cout;
        using std::cin;
        using std::endl;
        String name;
        cout <<"Hi, what's your name?\n>> ";
        cin >> name;

        cout << name << ", please enter up to " << ArSize
             << " short sayings <empty line to quit>:\n";
        String sayings[ArSize];     // array of objects
        char temp[MaxLen];          // temporary string storage
        int i;
        for (i = 0; i < ArSize; i++)
        {
            cout << i+1 << ": ";
            cin.get(temp, MaxLen);
            while (cin && cin.get() != '\n')
                continue;
            if (!cin || temp[0] == '\0')    // empty line?
                break;              // i not incremented
            else
                sayings[i] = temp;  // overloaded assignment
        }
        int total = i;              // total # of lines read

        if ( total > 0)
        {
            cout << "Here are your sayings:\n";
            for (i = 0; i < total; i++)
                cout << sayings[i][0] << ": " << sayings[i] << endl;

            int shortest = 0;
            int first = 0;
            for (i = 1; i < total; i++)
            {
                if (sayings[i].length() < sayings[shortest].length())
                    shortest = i;
                if (sayings[i] < sayings[first])
                    first = i;
            }
            cout << "Shortest saying:\n" << sayings[shortest] << endl;;
            cout << "First alphabetically:\n" << sayings[first] << endl;
            cout << "This program used "<< String::HowMany()
                 << " String objects. Bye.\n";
        }
        else
            cout << "No input! Bye.\n";
    // keep window open
    /*    if (!cin)
            cin.clear();
        while (cin.get() != '\n')
            continue; */
       return 0;
    }
    ```

  - cmd

    ```cmd
    Hi, what's your name?
    >> Jack Liu
    Jack Liu, please enter up to 10 short sayings <empty line to quit>:
    1: wsegrgf
    2: gerweq
    3: ggwergw.
    4: ewwg.wseg
    5: eggse
    6: seg
    7: seg.seg
    8: segg.
    9: fgdh.
    10: sadf.
    Here are your sayings:
    w: wsegrgf
    g: gerweq
    g: ggwergw.
    e: ewwg.wseg
    e: eggse
    s: seg
    s: seg.seg
    s: segg.
    f: fgdh.
    s: sadf.
    Shortest saying:
    seg
    First alphabetically:
    eggse
    This program used 11 String objects. Bye.
    ```

- strng1-saying2

  - saying2

    使用指向对象的指针

    ```c++
    // sayings2.cpp -- using pointers to objects
    // compile with string1.cpp
    #include <iostream>
    #include <cstdlib>      // (or stdlib.h) for rand(), srand()
    #include <ctime>        // (or time.h) for time()
    #include "string1.h"
    const int ArSize = 10;
    const int MaxLen = 81;
    int main()
    {
        using namespace std;
        String name;
        cout <<"Hi, what's your name?\n>> ";
        cin >> name;

        cout << name << ", please enter up to " << ArSize
             << " short sayings <empty line to quit>:\n";
        String sayings[ArSize];
        char temp[MaxLen];               // temporary string storage
        int i;
        for (i = 0; i < ArSize; i++)
        {
            cout << i+1 << ": ";
            cin.get(temp, MaxLen);
            while (cin && cin.get() != '\n')
                continue;
            if (!cin || temp[0] == '\0') // empty line?
                break;                   // i not incremented
            else
                sayings[i] = temp;       // overloaded assignment
        }
        int total = i;                   // total # of lines read

        if (total > 0)
        {
            cout << "Here are your sayings:\n";
            for (i = 0; i < total; i++)
                cout << sayings[i] << "\n";

        // use pointers to keep track of shortest, first strings
            String * shortest = &sayings[0]; // initialize to first object
            String * first = &sayings[0];
            for (i = 1; i < total; i++)
            {
                if (sayings[i].length() < shortest->length())
                    shortest = &sayings[i];
                if (sayings[i] < *first)     // compare values
                    first = &sayings[i];     // assign address
            }
            cout << "Shortest saying:\n" << * shortest << endl;
            cout << "First alphabetically:\n" << * first << endl;

            srand(time(0));
            int choice = rand() % total; // pick index at random
        // use new to create, initialize new String object
            String * favorite = new String(sayings[choice]);
            cout << "My favorite saying:\n" << *favorite << endl;
            delete favorite;
        }
        else
            cout << "Not much to say, eh?\n";
        cout << "Bye.\n";
    // keep window open
    /*    if (!cin)
            cin.clear();
        while (cin.get() != '\n')
            continue;
        cin.get();
    */
        return 0;
    }
    ```

- placenew1

  - 定位new

    ```c++
    // placenew1.cpp  -- new, placement new, no delete
    #include <iostream>
    #include <string>
    #include <new>
    using namespace std;
    const int BUF = 512;

    class JustTesting
    {
    private:
        string words;
        int number;

    public:
        JustTesting(const string &s = "Just Testing", int n = 0)
        {
            words = s;
            number = n;
            cout << words << " constructed\n";
        }
        ~JustTesting() { cout << words << " destroyed\n"; }
        void Show() const { cout << words << ", " << number << endl; }
    };
    int main()
    {
        char *buffer = new char[BUF]; // get a block of memory

        JustTesting *pc1, *pc2;

        pc1 = new (buffer) JustTesting;     // place object in buffer
        pc2 = new JustTesting("Heap1", 20); // place object on heap

        cout << "Memory block addresses:\n"
             << "buffer: "
             << (void *)buffer << "    heap: " << pc2 << endl;
        cout << "Memory contents:\n";
        cout << pc1 << ": ";
        pc1->Show();
        cout << pc2 << ": ";
        pc2->Show();

        JustTesting *pc3, *pc4;
        pc3 = new (buffer) JustTesting("Bad Idea", 6);
        pc4 = new JustTesting("Heap2", 10);
        cout << "Memory contents:\n";
        cout << pc3 << ": ";
        pc3->Show();
        cout << pc4 << ": ";
        pc4->Show();

        delete pc2;      // free Heap1
        delete pc4;      // free Heap2
        delete[] buffer; // free buffer
        cout << "Done\n";
        // std::cin.get();
        system("pause");
        return 0;
    }
    ```

    ```cmd
    Just Testing constructed
    Heap1 constructed
    Memory block addresses:
    buffer: 0x1d1770    heap: 0x1d1340
    Memory contents:
    0x1d1770: Just Testing, 0
    0x1d1340: Heap1, 20
    Bad Idea constructed
    Heap2 constructed
    Memory contents:
    0x1d1770: Bad Idea, 6
    0x1d19a0: Heap2, 10
    Heap1 destroyed
    Heap2 destroyed
    Done
    ```

    - 注意到创建第二个对象

      ```c++
      pc1 = new (buffer) JustTesting;
      ```

      如果类动态的为数据成员分配空间，将引发问题

      而定位new析构的时候不是直接析构，而是从定位点析构

      ```c++
      delete[] buffer;
      ```

- placenew2

  - 显示的使用定位new创建的对象调用析构函数

    ```c++
    // placenew2.cpp  -- new, placement new, no delete
    #include <iostream>
    #include <string>
    #include <new>
    using namespace std;
    const int BUF = 512;

    class JustTesting
    {
    private:
        string words;
        int number;

    public:
        JustTesting(const string &s = "Just Testing", int n = 0)
        {
            words = s;
            number = n;
            cout << words << " constructed\n";
        }
        ~JustTesting() { cout << words << " destroyed\n"; }
        void Show() const { cout << words << ", " << number << endl; }
    };
    int main()
    {
        char *buffer = new char[BUF]; // get a block of memory

        JustTesting *pc1, *pc2;

        pc1 = new (buffer) JustTesting;     // place object in buffer
        pc2 = new JustTesting("Heap1", 20); // place object on heap

        cout << "Memory block addresses:\n"
             << "buffer: "
             << (void *)buffer << "    heap: " << pc2 << endl;
        cout << "Memory contents:\n";
        cout << pc1 << ": ";
        pc1->Show();
        cout << pc2 << ": ";
        pc2->Show();

        JustTesting *pc3, *pc4;
        // fix placement new location
        pc3 = new (buffer + sizeof(JustTesting))
            JustTesting("Better Idea", 6);
        pc4 = new JustTesting("Heap2", 10);

        cout << "Memory contents:\n";
        cout << pc3 << ": ";
        pc3->Show();
        cout << pc4 << ": ";
        pc4->Show();

        delete pc2;          // free Heap1
        delete pc4;          // free Heap2
                             // explicitly destroy placement new objects
        pc3->~JustTesting(); // destroy object pointed to by pc3
        pc1->~JustTesting(); // destroy object pointed to by pc1
        delete[] buffer;     // free buffer
        // std::cin.get();
        system("pause");
        return 0;
    }
    ```

    ```cmd
    Just Testing constructed
    Heap1 constructed
    Memory block addresses:
    buffer: 0x1b1770    heap: 0x1b1340
    Memory contents:
    0x1b1770: Just Testing, 0
    0x1b1340: Heap1, 20
    Better Idea constructed
    Heap2 constructed
    Memory contents:
    0x1b1798: Better Idea, 6
    0x1b19a0: Heap2, 10
    Heap1 destroyed
    Heap2 destroyed
    Better Idea destroyed
    Just Testing destroyed
    ```

    - 注意到析构函数的调用

      ```c++
      pc3->~JustTesting(); // destroy object pointed to by pc3
      pc1->~JustTesting();
      ```

      首先，pc3的销毁早于pc1，因为pc1的创建早于pc3；

      其次，如果不这样销毁，将导致创建的JustTesting没有销毁，之前销毁char\*只是销毁char\*，并没有销毁JustTesting

- queue-bank
  - ATM模拟
