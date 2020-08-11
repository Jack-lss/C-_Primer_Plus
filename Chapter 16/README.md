# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## chapter 16

- string类

  - string类的构造函数

  |                           构造函数                           |                             描述                             |                             示例                             |
  | :----------------------------------------------------------: | :----------------------------------------------------------: | :----------------------------------------------------------: |
  |                   string(const char \* s)                    |       将string对象初始化为s指向的NBTS（传统的C字符串）       |                string one("Lottery Winner!");                |
  |                 string(size_type n, char c)                  | 创建一个包含n个元素的string对象，<br/>其中每个元素都被初始化为字符c |                    string two(20, '\$');                     |
  |                  string(const string & str)                  |    将一个string对象初始化为string对象str（复制构造函数）     |                      strig three(one);                       |
  |                           string()                           |      创建一个默认的string对象，长度为0（默认构造函数）       |                         string four;                         |
  |             string(const char \* s, size_type n)             | 将string对象初始化为s指向的NBTS的前n个字符，<br/>即使超过了NBTS的行尾 |                    string five(one, 10);                     |
  |    template\<class Iter\><br>string(Iter begin, Iter end)    | 将string对象初始化为区间[begin, end)内的字符，<br/>其中begin和end的行为就像指针，用于指定位置，<br/>范围包括begin在内，但不包括end |               string six(&five[6], &five[10])                |
  | string(const string & str, <br/>string size_type pos=0, size_type n=npos) | 将一个string对象初始化为对象str中从位置pos<br/>开始到结尾的字符，或从位置pos开始的n个字符 |                  stgring seven(one, 7, 16);                  |
  |                string(string && str) noexcept                | C++11新增的，它将一个string对象初始化为<br/>string对象str，并可以修改str（移动构造函数） |                  strig eight(one) noexcept;                  |
  |              string(initalizer_list\<char\> il)              | C++11新增的，它将一个string对象初始化<br/>为初始化列表i中的字符 | string man={'L', 'i', 's'};<br/>or string lang{'L', 'i', 's'}; |

  - string的输入
    - string的getline()将自动调整目标string对象的大小，使之刚好能够存储输入的字符

    ```c++
    char fname[10];
    string lname;
    cin >> fname;
    cin >> lname;
    cin.getline(fname, 10);
    getline(cin, fname);
    ```

    - string的getline()函数从输入中读取字符，并将其存储到目标string中，直到发生下列三种情况：

      1. 到达文件尾，在这种情况下，输入流的eofbit将被设置，这意味着方法fail()和eof()都将被返回true；
      2. 遇到分界字符（默认为\n），在这种情况下，将把分界字符从输入流中删除，但不存储它；
      3. 读取的字符数达到最大允许值（string::npos和可供分配的内存字节数中较小的一个），在这种情况下，将设置输入流的failbit，这意味着方法fail()和eof()都将被返回true。

      示例：strfile.cpp and strfile.exe

  - 使用字符串

    - 比较字符串

      1. 如果机器排列序列为ASCII码，则数字将小于大写字符，而大写字符小于小写字符。

      ```c++
      string snake2("cobra");
      string snake2("coral");
      char snake3[20] = "anaconda";
      if (snake1 < snake2)
          ...
      if (snake1 == snake2)
          ...
      if (snake1 != snake2)
          ...
      ```

      2. length()成员来自较早版本的string类，而size()则是为提供STL兼容性而添加的。
      3. 在字符串中搜索给行字符串或字符：

      |                           方法原型                           |                             描述                             |
      | :----------------------------------------------------------: | :----------------------------------------------------------: |
      | size_type find(const string & str, size_type pos = 0) const  | 从pos位置开始，查找子字符串str。如果找到，则返回该字符串首次出现时首字符的索引；否则，返回string::npos（string::npos是字符串可储存的最大字符数） |
      |   size_type find(const char \* s, size_type pos = 0) const   | 从pos位置开始，查找子字符串s。如果找到，则返回该字符串首次出现时首字符的索引；否则，返回string::npos |
      | size_type find(const char \* s, sizetype pos = 0, size_type n) | 从pos位置开始，查找s的前n个字符组成的子字符串，如果找到，则返回该字符串首次出现时首字符的索引;否则，返回string::npos |
      |       size_type find(char ch, size_type pos = 0) const       | 从pos位置开始，查找字符ch。如果找到，则返回该字符串首次出现时首字符的索引；否则，返回string::npos |

      string库还提供了相关的方法：rfind()、find_first_of()、find_last_of()、find_first_not_of()和find_last_not_of()，它们的重载函数特征标都与find()相同。

      - rfind()方法查找子字符串或字符最后一次出现的位置；
        1. find_first_of()方法在字符串中查找参数中任何一个字符首次出现的位置；
        2. find_last_of()方法在字符串中查找参数中任何一个字符最后一次出现的位置；
        3. find_first_not_of()方法在字符串中查找第一个不包含在参数中的字符；
        4. find_last_not_of()方法在字符串中查找最后一个不包含在参数中的字符。

- 智能指针模板类

  智能指针模板（auto_ptr、unique_ptr和shared_ptr）都定义了类似指针的对象，可以将new获得的地址赋给这种对象。当指针过期时，其析构函数将使用delete来释放内存。因此，如果将new返回的地址赋给这些对象，将无需记住稍后释放这些内存：在智能指针过期时，这些内存将自动被释放。

  - 说明auto_ptr

    ```c++
    void demol()
    {
        double * pd = new double; // 1
        *pd = 25.5; // 2
        return; // 3
    }
    ```

    ```txt
    1.为pd和一个double值分配存储空间，保存地址：

      pd  [1000]    [   ]

    ​       <4000>    <10000>

    2.将值赋值到动态内存中：

      pd  [1000]    [25.5]

          <4000>    <10000>

    3.删除pd，值被保留在动态内存中：

                    [25.5]

                    <10000>
    ```

    ```c++
    #include<memory>
    void demo2()
    {
        auto_ptr<double> ap(new double);  // 1
        *ap = 25.5; // 2
        return; // 3
    }
    ```

    ```txt
     1.为ap和一个double值分配存储空间，保存地址：

      ap    [1000]    [   ]

            <6000>    <10000>

     2.将值赋值到动态内存中：

      ap    [1000]    [25.5]

            <6000>    <10000>

     3.删除ap，ap的析构函数释放动态内存。
    ```

  - unique_ptr和shared_ptr语法

    同样，unique_ptr和shared_ptr语法同auto_ptr一样

    ```c++
    #include<memory>
    unique_ptr<double> pdu(new double);
    shared_ptr<double> pss(new string);
    ```

  - 自定义类的动态申请存储空间

    smrtptrs.cpp and smrtptrs.exe

  - 智能指针的注意事项

    关于摈弃auto_ptr

    ```c++
    auto_ptr<string> ps (new string("I reigned lonely as a cloud."));
    auto_ptr<string> vocation;
    vocation = ps;
    ```

    上述语句试图删除同一个对象两次，避免这种问题，方法有多种：

    - 定义赋值运算符，使之执行深复制。
    - 建立所有权概念，对于特定的对象，只能有一个智能指针可拥有它，这样只有拥有对象的智能指针的析构函数会删除该对象。这是unique_ptr和auto_ptr策略，但是unique_ptr策略更严格。
    - 创建智能更高的指针，跟踪引用特定对象的智能指针数（引用计数指针）。——赋值时计数加1，指针过期时，计数减1，仅最后一个指针过期时才调用delete。这是shared_ptr策略。

    异常的示例：fowl.cpp and fowl.exe

- 标准模板库

  - 使用模板类vector

    - 创建对象，[]读取

      vect1.cpp and vect1.exe

    - size()、begin()、end()、push_back()、erase()

      vect2.cpp and vect2.exe

    - for_each()、random_shuffle()、sort()

      vect3.cpp and vect4.exe

  - 基于范围的for循环（C++11）

    ```c++
    double prices[5] = {4.99, 12.99, 3.23, 5.23};
    for (double x : prices)
        cout << x << std::endl;
    ```

- 泛型编程

  **面向对象编程关注的是编程的数据方面，而泛型编程关注的是算法**。

  他们的共同点是抽象和创建可重用代码。

  - 迭代器

    **模板使得算法独立于存储的数据类型**，而**迭代器使算法独立于使用的容器类型**。

  - 迭代器类型

    |    迭代器功能    | 输入 | 输出 | 正向 | 双向 | 随机访问 |
    | :--------------: | :--: | :--: | :--: | :--: | :------: |
    |   解除引用读取   |  有  |  无  |  有  |  有  |    有    |
    |   解除引用写入   |  无  |  有  |  有  |  有  |    有    |
    | 固定和可重复排序 |  无  |  无  |  有  |  有  |    有    |
    |    ++i or i++    |  有  |  有  |  有  |  有  |    有    |
    |    --i or i--    |  无  |  无  |  无  |  有  |    有    |
    |       i[n]       |  无  |  无  |  无  |  无  |    有    |
    |      i + n       |  无  |  无  |  无  |  无  |    有    |
    |      i - n       |  无  |  无  |  无  |  无  |    有    |
    |      i += n      |  无  |  无  |  无  |  无  |    有    |
    |      i -= n      |  无  |  无  |  无  |  无  |    有    |

    1. 输入迭代器（InputIterator）

       - 输入迭代器解除引用将使程序能够读取容器中的值，但不一定能让程序修改值
       - 输入迭代器是单向迭代器，可以递增（++），但不能倒退
       - 不能保证输入迭代器遍历容器时，顺序不变
       - 输入迭代器不能对前面的迭代器值解除引用

    2. 输出迭代器（outputIterator）

       - 输出迭代器指将信息从程序传输给容器的迭代器正向迭代器
       - 输出迭代器解除引用将使程序能够修改容器中的值，但不能读取
       - 输出迭代器是单向迭代器，可以递增（++），但不能倒退
       - 不能保证输出迭代器遍历容器时，顺序不变
       - 输出迭代器不能对前面的迭代器值解除引用

    3. 正向迭代器

       - 正向迭代器是单向迭代器，可以递增（++），但不能倒退

       - 正向迭代器总时按相同的顺序遍历一系列值

       - 正向迭代器可以对前面的迭代器值解除引用（如果保存了它），并可以得到相同的值

       - 正向迭代器既可以使得能够读取和修改数据，也可以使得只能读取数据

         ```c++
         int * pirw;
         const int * pir;
         ```

    4. 双向迭代器

       - 双向迭代器具备正向迭代器所有特性
       - 双向迭代器支持递减运算符

    5. 随机访问迭代器（RandomAccessIterator）

       - 随机访问迭代器具备双向迭代器所有特性，还具备以下操作(a和b都是迭代器值，n是整数，r是随机迭代器变量或引用)

       | 表达式 |              描述              |
       | :----: | :----------------------------: |
       | a + n  |  指向a所指向的元素后第n个元素  |
       | n + a  |          与a + n相同           |
       | a - n  | 指向a所指向的元素前的第n个元素 |
       | r += n |        等价于r = r + n         |
       | r -= n |        等价于r = r - n         |
       |  a[n]  |        等价于\*(a + n)         |
       | b - a  |  结果为这样的n值，即b = a + n  |
       | a < b  |     如果b - a > 0，则为真      |
       | a > b  |     如果b - a < 0，则为真      |
       | a >= b |     如果 !(a < b)，则为真      |
       | a <= b |     如果 !(a > b)，则为真      |

  - copy()、istream()使用迭代器和反向迭代器

    copyit.cpp and copyit.exe

  - for_each()、back_insert_iterator 和 insert_iterator插入迭代器的使用

    inserts.cpp and inserts.exe

  - 容器种类

    - 容器概念

      概念是具有名称（如容器、序列容器、关联容器等）的通用类别

      - 一些基本的容器特征（X表示容器类型，a和b表示类型为X的值，r表示类型为X&的值，u表示类型为X的标识符（即如果X表示vector\<int\>，则u是一个vector\<int\>））

      |    表达式     |     返回类型      |                             说明                             | 时间复杂度 |
      | :-----------: | :---------------: | :----------------------------------------------------------: | :--------: |
      |  X::iterator  | 指向T的迭代器类型 |                满足正向迭代器要求的任何迭代器                |  编译时间  |
      | X::value_type |         T         |                           T的类型                            |  编译时间  |
      |     X u;      |                   |                    创建一个名为u的空容器                     |    固定    |
      |      X()      |                   |                     创建一个匿名的空容器                     |    固定    |
      |    X u(a);    |                   |                   调用复制构造函数后u == a                   |    线性    |
      |   X u = a;    |                   |                        作用同X u(a);                         |    线性    |
      |    r = a;     |        X&         |                    调用复制运算符后r == a                    |    线性    |
      |  (&a)->~X()   |       void        |                 对容器中每个元素应用析构函数                 |    线性    |
      |   a.begin()   |      迭代器       |                返回指向容器第一个元素的迭代器                |    固定    |
      |    a.end()    |      迭代器       |                       返回超尾值迭代器                       |    固定    |
      |   a.size()    |    无符号类型     |             返回元素个数等价于a.end()-a.begin()              |    固定    |
      |   a.swap(b)   |       void        |                        交换a和b的内容                        |    固定    |
      |    a == b     |   可转换为bool    | 如果a和b的长度相同，且a中每个元素都等于<br/>b中的元素，则为真 |    线性    |
      |    a != b     |   可转换为bool    |                        返回!(a == b)                         |    线性    |

      时间复杂度：快->慢——编译时间->固定时间->线性时间

      时间复杂度要求是STL特征，虽然实现的细节可以隐藏，但性能规格应公开，以便程序员能够知道完成特定操作的计算成本。

    - 容器类型

      容器类型是可用于创建具体容器对象的模板

      1. C++11前的11个容器类别分别是deque、list、queue、priority_queue、stack、vector、map、mutilmap、set和multiset

      2. C++11后新增的容器是forword_list、unordered_map、unordered_multimap、unordered_set和unordered_multiset

         - 其中unordered_map、unordered_multimap、unordered_set和unordered_multiset都是无需关联容器

           无序关联容器是基于数据结构哈希表的，关联容器是基于数结构的。这旨在提高添加和删除元素的速度以及提高查找算法的效率

    - C++11新增的容器要求

      |   表达式   |    返回类型    |                    说明                     | 复杂度 |
      | :--------: | :------------: | :-----------------------------------------: | :----: |
      |  X u(rv);  |                |  调用移动构造函数后，u的值与rv的原始值相同  |  线性  |
      | X u = rv;  |                |  调用移动构造函数后，u的值与rv的原始值相同  |        |
      |  a = rv;   |       X&       | 调用移动复制运算符后，u的值与rv的原始值相同 |  线性  |
      | a.cbegin() | const_iterator |   返回 指向容器在第一个元素的const迭代器    |  固定  |
      |  a.cend()  | const_iterator |            返回超尾值const迭代器            |  固定  |

      复制构造和复制赋值以及移动构造和移动赋值之间的差别在于，复制操作保留源对象，而移动操作可以修改源对象，还可以转让所有权，而不做任何复制。

    - 序列

      C++11之前的deque、list、queue、priority_queue、stack、vector和C++11新增的容器都是序列（sequeque）

      - 序列的要求

      |      表达式       | 返回类型 |                        说明                         |
      | :---------------: | :------: | :-------------------------------------------------: |
      |     X a(n, t)     |          |           声明一个名为a的由n个t组成的序列           |
      |      X(n, t)      |          |            创建一个由n个t组成的匿名序列             |
      |     X a(i, j)     |          | 声明一个名为a的序列，并将其初始化为区间[i, j)的内容 |
      |      X(i, j)      |          |  创建一个匿名序列，并将其初始化为区间[i, j)的内容   |
      |  a.insert(p. t)   |  迭代器  |                  将t插入到p的前面                   |
      | a.insert(p, n, t) |   void   |                 将n个t插入的p的前面                 |
      | a.insert(p, i, j) |   void   |          将区间[i, j)中的元素插入到p的前面          |
      |    a.erase(p)     |  迭代器  |                   删除p指向的元素                   |
      |   a.crase(p, q)   |  迭代器  |               删除区间[p, q)中的元素                |
      |     a.clear()     |   void   |             等价于erase(begin(), end())             |

      - C++11之前的deque、list、queue、priority_queue、stack、vector的时间复杂度都为固定时间，这6个模型还有以下其他操作

      |     表达式     | 返回类型 |          含义          |        容器         |
      | :------------: | :------: | :--------------------: | :-----------------: |
      |   a.front()    |    T&    |      \*a.begin()       | vector、list、deque |
      |    a.back()    |    T&    |      \*--a.end()       | vector、list、deque |
      | a.push_front() |   void   | a.insert(a.begin(), t) |     list、deque     |
      | a.push_back()  |   void   |   a.insert(a.end, t)   | vector、list、deque |
      | a.pop_front()  |   void   |  a.erase(a.begin(),)   |     list、deque     |
      |  a.pop_back()  |   void   |   a.erase(--a.end())   | vector、list、deque |
      |      a[n]      |    T&    |   \*(a.begin() + n)    |    vector、deque    |
      |    a.at(t)     |    T&    |   \*(a.begin() + n)    |    vector、deque    |

      - list的成员函数

      |                     函数                      |                             说明                             |
      | :-------------------------------------------: | :----------------------------------------------------------: |
      |       void merge(list\<T, Alloc\> & x)        | 将链表x与调用链表合并。两个链表必须已经排序。合并后的经过排序的链表保存在调用链表中，x为空。这个函数的时间复杂度为线性时间 |
      |          void remove(const T & val)           |  从链表中删除val的所有实例。这个函数的时间复杂度为线性时间   |
      |                  void sort()                  |      使用<运算符对链表进行排序：N个元素的复杂度为NlongN      |
      | void splice(iterator pos, list\<T, Alloc\> x) | 将链表x的内部插入到pos的前面，x将为空。这个函数的时间复杂度为固定时间 |
      |                 void unique()                 | 将连续的相同元素压缩为单个元素。这个函数的时间复杂度为线性时间 |

      list.cpp and list.exe演示这些方法和insert()方法

      - queue的成员函数

      |          方法          |                  说明                   |
      | :--------------------: | :-------------------------------------: |
      |   bool emty() const    | 如果队列为空，则返回true，否则返回false |
      | size_type size() const |         返回队列中的元素的数目          |
      |        T& front        |         返回指向队首元素的引用          |
      |       T& back()        |         返回指向队尾元素的引用          |
      | void push(xonst T& x)  |               在队尾插入x               |
      |       void pop()       |              删除队首元素               |

      - stack的成员函数

      |          方法          |                 说明                  |
      | :--------------------: | :-----------------------------------: |
      |   bool emty() const    | 如果栈为空，则返回true，否则返回false |
      | size_type size() const |         返回栈中的元素的数目          |
      |        T& top()        |        返回指向栈顶元素的引用         |
      | void push(xonst T& x)  |             在栈顶部插入x             |
      |       void pop()       |             删除栈顶元素              |

      - set的使用

        setops.cpp and setops.exe

      - mutimap的使用

        mutilmap.cpp and mutilmap.exe

  - 函数对象（函数符）

    - 函数符概念
      1. 生成器（generator）是不用参数就可以调用的函数符号。
      2. 一元函数（unary function）是用一个参数可以调用的函数符。
      3. 二元函数（binary function）是用两个参数可以调用的函数符。
      4. 返回bool值的一元函数是谓词（predicate）
      5. 返回bool值的二元函数是二元谓词（binary predicate）

    - 预定义的函数符

      STL定义了多个基本函数符它们执行诸如将两个值相加、比较两个值是否相等。**提供这些函数符是为了支持将函数作为参数的STL函数。**

      例如，考虑函数transform：

      ```c++
      const int LIM = 5;
      double arr1[LIM] = {36, 39, 42, 45, 48};
      vector<double> gr8(arr1, arr1 + LIM);
      ostream_iterator<double, char> out(cout , "");
      transform(gr8.begin(), gr8.end(), out, sqrt);
      ```

      transform的前两个参数是指定容器区间的迭代器，第三个参数是指定将结果复制到哪里的迭代器，最后一个参数是一个函数符，它将应用于区间中的每个元素，生成结果中的新元素。

      很明显sqrt函数符必须是接受单个参数的函数符。

      第二种可能，使用一个接受两个参数的函数，并将该函数用于两个区间中元素。它用另一个参数（即第三个参数）表示第二个区间的起始位置。例如，如果m8是另一个vector\<double\>对象，mean(double, double)返回两个值的平均值，则下面代码将输出来自gr8和m8的值的平均值：

      ```c++
      transform(gr8.begin(), gr8.end(), m8.begin(), out, mean);
      ```

      而为了将两个数相加，但是不能直接使用+运算符，因为它是内置的运算符，不是函数。然而可以定义一个两数相加的函数：

      ```c++
      double add(double x, double y){return x + y};
      ...
      transform(gr8.begin(), gr8.end(), m8.begin(), out, add);
      ```

      头文件functional定义了多个模板类函数符：

      | 运算符 | 相应的函数符  |
      | :----: | :-----------: |
      |   +    |     plus      |
      |   -    |     minus     |
      |   \*   |  multiplies   |
      |   /    |    divides    |
      |   %    |    modulus    |
      |   ~    |    nagate     |
      |   ==   |   equal_to    |
      |   !=   | not_equal_to  |
      |   >    |    greater    |
      |   <    |     less      |
      |   >=   | greater_equal |
      |   <=   |  less_equal   |
      |   &&   |  logical_and  |
      |  \|\|  |  logical_or   |
      |   !    |  logical_not  |

    - 自适应函数符和函数适配器

      上表列出的预定义函数符都是自适应的。

      STL的5个相关概念：

      1. 自适应生成器（adaptable generator）
      2. 自适应一元函数（adaptable unary function）
      3. 自适应二元函数（adaptable binary function）
      4. 自适应谓词（adaptable predicate）
      5. 自适应谓词（adaptable binary predicate）

      使用自适应的原因是，它携带了标识参数类型和返回类型的typedef成员。这些成员分别是result_type、first_argument和second_argument_type。例如，plus\<int\>对象的返回类型被标识为plus\<int\>::result_type，这是int的typedef。

      函数自适应的意义在于：**函数适配器对象可以使用函数符，并认为存在这些trpedef成员。**例如，接受一个自适应函数符参数的函数可以使用result_type成员来声明一个与函数的返回类型匹配的变量。

      STL提供了使用这些工具的函数适配器类。例如，假设要将矢量gr8的每个元素都增加2.5倍，则取要使用结构一个一元函数参数的transform()版本，就像前面的

      ```c++
      transform(gr8.begin(), gr8.end(), out, sqrt);
      ```

      然而，multiplies()函数符可以执行乘法运行，但它是二元函数。因此需要一个函数适配器，将接受两个参数的函数符传唤为接受一个参数的函数符。STL使用binder1st和binder2nd类自动完成这一过程，它们将自适应二元函数转换为自适应一元函数。

      - binder1st

        假设有一个自适应二元函数对象f2()，则可以创建一个binder1st对象，该对象与一个将被用作f2()的第一个参数的特定值(val)相关联：

        ```c++
        binder1st(f2, val) f1;
        ```

        这样，使用单个参数调用f1(x)时，返回的值与将val作为第一参数、将f1()的参数作为第二参数调用f2()返回的值相同。即f1(x)等价于f2(val, x)，只是前者是一元函数，而不是二元函数。f2()函数被适配。同样，仅当f2()是一个自适应函数时，这才能实现。

      - bind1st

        简化binder1st类的使用。可以向其提供用于构建binder1st对象的函数名称和值，它将返回一个这种类型的对象。例如，要将二元函数multiplies()转换为将参数乘以2.5的一员函数，则可以这样做：

        ```c++
        bind1st(multiplies<double>(), 2.5)
        ```

        因此将gr8中的每个元素与2.5相乘，并显示结果的代码如下：

        ```c++
        transform(gr8.begin(), gr8.end(), out, bind1st(multiplies<double>(), 2.5));
        ```

      funadap.cpp and funadap.exe实现函数符

  - 算法

    STL将算法库分成4组：

    1. 非修改式序列操作，对区间每个元素进行操作，但不能修改容器的内容。例如，find()和for_each().

    2. 修改式序列操作，对区间每个元素进行操作。然而，可以修改容器的内容，也可以修改值得排列顺序。transform()、random_shuffle()和copy()。

    3. 排序和相关操作，包括多个排序函数和其他各种函数，包括集合操作。

    4. 通用数字运算，将区间得内容累积、计算两个容器得内部乘积、计算小计、计算相邻对象差得函数。

    前三组在头文件algorithm中讲述，第四组是专用于数值数据的，有自己的头文件，成为numeric

    - 算法得通用特征

      STL使用迭代器和迭代器区间

      有些算法有两个版本：就地版本和复制版本。STL得约定是，复制版本得名称将以\_copy结尾。复制版本将接受一个额外得输出迭代器参数，该参数指定结果得放置位置。

    - STL和string类

      string类虽然不是STL得组成部分，但设计它时考虑到了STL。例如，它包含begin()、end()、rbegin()和rend()等成员，因此可以使用STL接口。

      strgst1.cpp and strgst2.exe使用next_permutation()算法

    - 函数和容器方法

      listrmv.cpp and listrmv.exe将演示使用STL方法和STL函数得区别

    - 使用STL

      STL是一个库，其组成部分被设计成协同工作。STL组件是工具，但也是创建其他工具得基本部件。

      usealgo.cpp and usealgo.exe

  - 其他库

    1. 头文件\<complex\>为复数提供了类模板complex，包含用于float、long和long double得具体化。这个类提供了标准得复数运算及能够处理复数的标准函数。

    2. C++11提供的头文件random提供了更多的随机数功能。
    3. 头文件\<valarray\>提供的模板类valarray。这个类模板被设计成用于表示数值，支持各种数值数组操作。valvect.cpp and valvect.exe演示；还有下标指定版本，其中一个slice类。vslice.cpp and vslice.exe演示
    4. 模板initializer_list(C++11)，头文件initializer_list包含，这个模板类包含成员函数begin()、end()和size()。ilist.cpp and ilist.exe演示
