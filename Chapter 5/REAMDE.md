# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## Chapter 5

- bigstep

  - 空语句

  - for循环的使用

    ```c++
    ;
    cout << "Enter an integer: ";
    int by;
    cin >> by;
    cout << "Counting by " << by << "s:\n";
    for (int i = 0; i < 100; i = i + by)
        cout << i << endl;
    ```

    ```cmd
    Enter an integer: 33
    Counting by 33s:
    0
    33
    66
    99
    ```

- block

  - for循环输入

    ```c++
    cout << "The Amazing Accounto will sum and average " << "five numbers for you.\n";
    cout << "Please enter five values:\n";
    double number;
    double sum = 0.0;
    for (int i = 1; i <= 5; i++)
    { // block starts here
        cout << "Value " << i << ": ";
        cin >> number;
        sum += number;
    } // block ends here
    cout << "Five exquisite choices indeed! " << "They sum to " << sum << endl;
    cout << "and average to " << sum / 5 << ".\n";
    cout << "The Amazing Accounto bids you adieu!\n";
    ```

    ```cmd
    The Amazing Accounto will sum and average five numbers for you.
    Please enter five values:
    Value 1: 2
    Value 2: 3
    Value 3: 4
    Value 4: 5
    Value 5: 6
    Five exquisite choices indeed! They sum to 20
    and average to 4.
    The Amazing Accounto bids you adieu!
    ```

- compstr1

  - strcmp的使用

    基本形式为strcmp(str1,str2)，若str1=str2，则返回零；若str1<str2，则返回负数；若str1>str2，则返回正数。

  - for循环识别字符串

    当判断语句为False就退出

    ```c++
    char word[5] = "?ate";

    for (char ch = 'z'; strcmp(word, "mate"); ch--)
    {
        cout << word << endl;
        word[0] = ch;
    }
    cout << "After loop ends, word is " << word << endl;
    ```

    ```cmd
    ?ate
    zate
    yate
    xate
    wate
    vate
    uate
    tate
    sate
    rate
    qate
    pate
    oate
    nate
    After loop ends, word is mate
    ```

- compstr2

  - string的$\neq$可以进行字符串的比较

    ```c++
    string word = "?ate";

    for (char ch = 'a'; word != "mate"; ch++)
    {
        cout << word << endl;
        word[0] = ch;
    }
    cout << "After loop ends, word is " << word << endl;
    ```

    ```cmd
    ?ate
    aate
    bate
    cate
    date
    eate
    fate
    gate
    hate
    iate
    jate
    kate
    late
    After loop ends, word is mate
    ```

- dowhile

  - do-while的使用

    先走循环体语句，再while判断，flase就退出

    ```c++
    int n;

    cout << "Enter numbers in the range 1-10 to find ";
    cout << "my favorite number\n";
    do
    {
        cin >> n;     // execute body
    } while (n != 7); // then test
    cout << "Yes, 7 is my favorite.\n";
    ```

    ```cmd
    Enter numbers in the range 1-10 to find my favorite number
    2
    35
    8
    9
    7
    Yes, 7 is my favorite.
    ```

    可以看到超过10的数字也会通过

- equal

  - ==和=的区别

    ```c++
    int quizscores[10] =
        {20, 20, 20, 20, 20, 19, 20, 18, 20, 20};

    cout << "Doing it right:\n";
    int i;
    for (i = 0; quizscores[i] == 20; i++)
        cout << "quiz " << i << " is a 20\n";
    // Warning: you may prefer reading about this program
    // to actually running it.
    cout << "Doing it dangerously wrong:\n";
    for (i = 0; quizscores[i] = 20; i++)
        cout << "quiz " << i << " is a 20\n";
    ```

    ```cmd
    Doing it right:
    quiz 0 is a 20
    quiz 1 is a 20
    quiz 2 is a 20
    quiz 3 is a 20
    quiz 4 is a 20
    ```

    **注意**：这是前面一个for循环的结果，第二个for循环在有的机器上报错，因为它是死循环

- express

  - ios_base::boolalpha的使用

    ```c++
    int x;

    cout << "The expression x = 100 has the value ";
    cout << (x = 100) << endl;
    cout << "Now x = " << x << endl;
    cout << "The expression x < 3 has the value ";
    cout << (x < 3) << endl;
    cout << "The expression x > 3 has the value ";
    cout << (x > 3) << endl;
    cout.setf(ios_base::boolalpha); //a newer C++ feature
    cout << "The expression x < 3 has the value ";
    cout << (x < 3) << endl;
    cout << "The expression x > 3 has the value ";
    cout << (x > 3) << endl;
    ```

    cout.setf(ios_base::boolalpha);用于设置格式，讲bool的0，1替换成false，true

    cout.setf(ios_base::unboolalpha);用于设置格式，讲bool的false，true替换成0，1

    ```cmd
    The expression x = 100 has the value 100
    Now x = 100
    The expression x < 3 has the value 0
    The expression x > 3 has the value 1
    The expression x < 3 has the value false
    The expression x > 3 has the value true
    ```

- forloop

  - for循环初始化

    ```c++
    int i; // create a counter
           //   initialize; test ; update
    for (i = 0; i < 5; i++)
        cout << "C++ knows loops.\n";
    cout << "C++ knows when to stop.\n";
    ```

    ```cmd
    C++ knows loops.
    C++ knows loops.
    C++ knows loops.
    C++ knows loops.
    C++ knows loops.
    C++ knows when to stop.
    ```

- formore

  - 测试f(n)=n*f(n-1)的前16个数

    ```c++
    const int ArSize = 16; // example of external declaration
    main()
    {
        long long factorials[ArSize];
        factorials[1] = factorials[0] = 1LL;
        for (int i = 2; i < ArSize; i++)
            factorials[i] = i * factorials[i - 1];
        for (int i = 0; i < ArSize; i++)
            std::cout << i << "! = " << factorials[i] << std::endl;
    }
    ```

    ```cmd
    0! = 1
    1! = 1
    2! = 2
    3! = 6
    4! = 24
    5! = 120
    6! = 720
    7! = 5040
    8! = 40320
    9! = 362880
    10! = 3628800
    11! = 39916800
    12! = 479001600
    13! = 6227020800
    14! = 87178291200
    15! = 1307674368000
    ```

- forstr1

  - 用for循环和string实现显示回文

    ```c++
    cout << "Enter a word: ";
    string word;
    cin >> word;

    // display letters in reverse order
    for (int i = word.size() - 1; i >= 0; i--)
        cout << word[i];
    cout << "\nBye.\n";
    ```

    ```cmd
    Enter a word: jack
    kcaj
    Bye.
    ```

- forstr2

  - 用for循环和string实现回文

    ```c++
    cout << "Enter a word: ";
    string word;
    cin >> word;

    // physically modify string object
    char temp;
    int i, j;
    for (j = 0, i = word.size() - 1; j < i; --i, ++j)
    { // start block
        temp = word[i];
        word[i] = word[j];
        word[j] = temp;
    } // end block
    cout << word << "\nDone\n";
    ```

    ```cmd
    Enter a word: jack
    kcaj
    Done
    ```

- neted

  - for循环遍历指针数组和二维数组

    ```c++
    const int Cities = 5;
    const int Years = 4;
    main()
    {
        using namespace std;
        const char *cities[Cities] = // array of pointers
            {                        // to 5 strings
             "Gribble City",
             "Gribbletown",
             "New Gribble",
             "San Gribble",
             "Gribble Vista"};

        int maxtemps[Years][Cities] = // 2-D array
            {
                {96, 100, 87, 101, 105}, // values for maxtemps[0]
                {96, 98, 91, 107, 104},  // values for maxtemps[1]
                {97, 101, 93, 108, 107}, // values for maxtemps[2]
                {98, 103, 95, 109, 108}  // values for maxtemps[3]
            };

        cout << "Maximum temperatures for 2008 - 2011\n\n";
        for (int city = 0; city < Cities; ++city)
        {
            cout << cities[city] << ":\t";
            for (int year = 0; year < Years; ++year)
                cout << maxtemps[year][city] << "\t";
            cout << endl;
        }
    }
    ```

    ```cmd
    Maximum temperatures for 2008 - 2011

    Gribble City:   96      96      97      98
    Gribbletown:    100     98      101     103
    New Gribble:    87      91      93      95
    San Gribble:    101     107     108     109
    Gribble Vista:  105     104     107     108
    ```

- nestedcl

  - for循环遍历string数组、array二维数组

    以逗号是行与行之间区别的重要指标，和行内区分一样，c++独有

    ```c++
    const int Cities = 5;
    const int Years = 4;
    int main()
    {
        using namespace std;
        const string cities[Cities] = // array of pointers
            {                         // to 5 strings
             "Gribble City",
             "Gribbletown",
             "New Gribble",
             "San Gribble",
             "Gribble Vista"};

        array<array<int, Cities>, Years> maxtemps =
            /*   int maxtemps[Years][Cities] =   // 2-D array */
            {
                96, 100, 87, 101, 105, // values for maxtemps[0]
                96, 98, 91, 107, 104,  // values for maxtemps[1]
                97, 101, 93, 108, 107, // values for maxtemps[2]
                98, 103, 95, 109, 108  // values for maxtemps[3]
            };

        cout << "Maximum temperatures for 2008 - 2011\n\n";
        for (int city = 0; city < Cities; ++city)
        {
            cout << cities[city] << ":\t";
            for (int year = 0; year < Years; ++year)
                cout << maxtemps[year][city] << "\t";
            cout << endl;
        }
    }
    ```

    ```cmd
    Maximum temperatures for 2008 - 2011

    Gribble City:   96      96      97      98
    Gribbletown:    100     98      101     103
    New Gribble:    87      91      93      95
    San Gribble:    101     107     108     109
    Gribble Vista:  105     104     107     108
    ```

- num_test

  - cin和普通初始化

    ```c++
    cout << "Enter the starting countdown value: ";
    int limit;
    cin >> limit;
    int i;
    for (i = limit; i; i--) // quits when i is 0
        cout << "i = " << i << "\n";
    cout << "Done now that i = " << i << "\n";
    ```

    ```cmd
    Enter the starting countdown value: 5
    i = 5
    i = 4
    i = 3
    i = 2
    i = 1
    Done now that i = 0
    ```

- plus_one

  - a++和++a的区别

    a++是在表达式完了之后再加1

    ++a是在++a表达式完了之后加1

    ```c++
    int a = 20;
    int b = 20;

    cout << "a   = " << a << ":   b = " << b << "\n";
    cout << "a++ = " << a++ << ": ++b = " << ++b << "\n";
    cout << "a   = " << a << ":   b = " << b << "\n";
    ```

    ```cmd
    a   = 20:   b = 20
    a++ = 20: ++b = 21
    a   = 21:   b = 21
    ```

- textin1

  - cin读单字符

  ```c++
  char ch;
  int count = 0; // use basic input
  cout << "Enter characters; enter # to quit:\n";
  cin >> ch;        // get a character
  while (ch != '#') // test the character
  {
      cout << ch; // echo the character
      ++count;    // count the character
      cin >> ch;  // get the next character
  }
  cout << endl
       << count << " characters read\n";
  // get rid of rest of line
  // while (cin.get() != '\n')
  // ;
  ```

  ```cmd
  Enter characters; enter # to quit:
  4
  45
  57
  78
  84
  43
  3#

  6 characters read
  ```

- textin2

  - cin.get(char)读一行

    ```c++
    char ch;
    int count = 0;

    cout << "Enter characters; enter # to quit:\n";
    cin.get(ch); // use the cin.get(ch) function
    while (ch != '#')
    {
        cout << ch;
        ++count;
        cin.get(ch); // use it again
    }
    cout << endl
         << count << " characters read\n";
    // get rid of rest of line
    // while (cin.get() != '\n')
    //    ;
    ```

    ```cmd
    Enter characters; enter # to quit:
    dsfdsf
    dsfdsf
    asdfv
    asdfv
    dsgew
    dsgew
    bvds
    bvds
    sdf#
    sdf
    27 characters read
    ```

- textin3

  - cin.get()用cin.fail()判断末尾

    ```c++
    char ch;
    int count = 0;
    cin.get(ch);                // attempt to read a char
    while (cin.fail() == false) // test for EOF
    {
        cout << ch; // echo character
        ++count;
        cin.get(ch); // attempt to read another char
    }
    cout << endl
         << count << " characters read\n";
    ```

    cin.fail()用于判断输入是否结束，结束符为(EOF)，这里的EOF表示错误输入或结束输入

    例如：

    ```txt
    int型的数据输入了char型的数据为错误输入
    ^Z表示结束(Windows)
    ```

    此外，使用了cin.fail()之后需要使用

    cin.clear()

    cin.ignore()

    来清除缓冲区，否则cin.fail()一直为true，也就是一直相当于错误输入

    ```cmd
    34
    34
    3213
    3213
    534
    534
    sad
    sad
    ^Z

    16 characters read
    ```

- textin4

  - int型输入，char型输出

    ```c++
    int ch; // should be int, not char
    int count = 0;

    while ((ch = cin.get()) != EOF) // test for end-of-file
    {
        cout.put(char(ch));
        ++count;
    }
    cout << endl
         << count << " characters read\n";
    ```

    ```cmd
    324
    324
    er
    er
    sd
    sd
    vs
    vs
    ^Z

    13 characters read
    ```

- waiting

  - \<ctime\>的clock()的使用

    clock()返回程序开始执行后到这一步所用的系统时间

    使用CLOCKS_PER_SEC乘以秒数可以返回系统时间单位

    ```c++
    cout << "Enter the delay time, in seconds: ";
    float secs;
    cin >> secs;
    // CLOCKS_PER_SEC，该常量等于每秒钟包含的系统时间单位数。
    // 因此，将系统时间除以这个值，就可以得到秒数。
    // 或者将秒数乘以CLOCKS_PER_SEC，就可以得到以系统时间单位为单位的时间。
    clock_t delay = secs * CLOCKS_PER_SEC; // convert to clock ticks
    cout << "starting\a\n";
    // 返回程序开始执行后到这一步所用的系统时间
    clock_t start = clock();
    // 检测当前系统时间和开始运行延迟函数的系统时间的差是否小于设定的延迟时间
    while (clock() - start < delay) // wait until time elapses
        ;                           // note the semicolon
    cout << "done \a\n";
    ```

    ```cmd
    Enter the delay time, in seconds: 43.5
    starting
    done
    ```

- while

  - 讲char使用ascii强制转换成int

    ```c++
    char name[ArSize];

    cout << "Your first name, please: ";
    cin >> name;
    cout << "Here is your name, verticalized and ASCIIized:\n";
    int i = 0;              // start at beginning of string
    while (name[i] != '\0') // process to end of string
    {
        cout << name[i] << ": " << int(name[i]) << endl;
        i++; // don't forget this step
    }
    ```

    ```cmd
    Your first name, please: jack
    Here is your name, verticalized and ASCIIized:
    j: 106
    a: 97
    c: 99
    k: 107
    ```
