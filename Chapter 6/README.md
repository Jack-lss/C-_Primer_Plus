# C++ Primer Plus

## use vscode

- **来源于《C++ Primer Plus》，这里给出中文代码整理**
- **以下整理并不代表源程序，只着重标记**

----

## Chapter 6

- and

  - &&符号的使用

    ```c++
    const int ArSize = 6;
    main()
    {
        using namespace std;
        float naaq[ArSize];
        cout << "Enter the NAAQs (New Age Awareness Quotients) "
             << "of\nyour neighbors. Program terminates "
             << "when you make\n"
             << ArSize << " entries "
             << "or enter a negative value.\n";

        int i = 0;
        float temp;
        cout << "First value: ";
        cin >> temp;
        while (i < ArSize && temp >= 0) // 2 quitting criteria
        {
            naaq[i] = temp;
            ++i;
            if (i < ArSize) // room left in the array,
            {
                cout << "Next value: ";
                cin >> temp; // so get next value
            }
        }
        if (i == 0)
            cout << "No data--bye\n";
        else
        {
            cout << "Enter your NAAQ: ";
            float you;
            cin >> you;
            int count = 0;
            for (int j = 0; j < i; j++)
                if (naaq[j] > you)
                    ++count;
            cout << count;
            cout << " of your neighbors have greater awareness of\n"
                 << "the New Age than you do.\n";
        }
    }
    ```

    ```cmd
    Enter the NAAQs (New Age Awareness Quotients) of
    your neighbors. Program terminates when you make
    6 entries or enter a negative value.
    First value: 0
    Next value: 9
    Next value: 8
    Next value: -7
    Enter your NAAQ: 5
    2 of your neighbors have greater awareness of
    the New Age than you do.
    ```

- cctypes

  - \<cctype\>的函数使用

    - isalpha

      如果参数是字母，返回true

    - isspace

      如果参数是标准空白字符，如空格、换行符、水平或垂直制表符，函数返回true

    - isdigit

      如果参数是数字（0－9），函数返回true

    - ispunct

      如果参数是标点符号，函数返回true

  ```c++
  cout << "Enter text for analysis, and type @"
          " to terminate input.\n";
  char ch;
  int whitespace = 0;
  int digits = 0;
  int chars = 0;
  int punct = 0;
  int others = 0;

  cin.get(ch);      // get first character
  while (ch != '@') // test for sentinel
  {
      if (isalpha(ch)) // is it an alphabetic character?
          chars++;
      else if (isspace(ch)) // is it a whitespace character?
          whitespace++;
      else if (isdigit(ch)) // is it a digit?
          digits++;
      else if (ispunct(ch)) // is it punctuation?
          punct++;
      else
          others++;
      cin.get(ch); // get next character
  }
  cout << chars << " letters, " << whitespace << " whitespace, " << digits << " digits, "
       << punct << " punctuations, " << others << " others.\n";
  ```

  ```cmd
  Enter text for analysis, and type @ to terminate input.
  32ew,<"^Zdd#$^%
  dd#$^%
  @
  4 letters, 1 whitespace, 2 digits, 7 punctuations, 1 others.
  ```

  - \<cctype\>其他函数

    - isalnum()

      如果参数是字母数字，即字母或者数字，函数返回true

    - iscntrl()

      如果参数是控制字符，函数返回true

    - isgraph()

      如果参数是除空格之外的打印字符，函数返回true

    - islower()

      如果参数是小写字母，函数返回true

    - isprint()

      如果参数是打印字符（包括空格），函数返回true

    - isupper()

      如果参数是大写字母，函数返回true

    - isxdigit()

      如果参数是十六进制数字，即0－9、a－f、A－F，函数返回true

    - tolower()

      如果参数是大写字符，返回其小写，否则返回该参数

    - toupper()

      如果参数是小写字符，返回其大写，否则返回该参数

- cinfish

  - &&的规则

    a&&b，先看a是不是真，

    若a真再看b是不是真，若b也真，就真；

    若a假就不用判断b，直接假

    ```c++
    const int Max = 5;
    main()
    {
        using namespace std;
        // get data
        double fish[Max];
        cout << "Please enter the weights of your fish.\n";
        cout << "You may enter up to " << Max << " fish <q to terminate>.\n";
        cout << "fish #1: ";
        int i = 0;
        while (i < Max && cin >> fish[i])
        {
            if (++i < Max)
                cout << "fish #" << i + 1 << ": ";
        }
        // calculate average
        double total = 0.0;
        for (int j = 0; j < i; j++)
            total += fish[j];
        // report results
        if (i == 0)
            cout << "No fish\n";
        else
            cout << total / i << " = average weight of " << i << " fish\n";
        cout << "Done.\n";
    }
    ```

    ```cmd
    Please enter the weights of your fish.
    You may enter up to 5 fish <q to terminate>.
    fish #1: 3
    fish #2: 4
    fish #3: 2
    fish #4: 1
    fish #5: 5
    3 = average weight of 5 fish
    Done.
    ```

- cingolf

  - \>>操作参数

    一般读取成功返回1，遇到EOF返回0

  - cin.clear()的使用

    清空缓冲区

    ```c++
    const int Max = 5;
    main()
    {
        using namespace std;
        // get data
        int golf[Max];
        cout << "Please enter your golf scores.\n";
        cout << "You must enter " << Max << " rounds.\n";
        int i;
        for (i = 0; i < Max; i++)
        {
            cout << "round #" << i + 1 << ": ";
            while (!(cin >> golf[i]))
            {
                cin.clear(); // reset input
                while (cin.get() != '\n')
                    continue; // get rid of bad input
                cout << "Please enter a number: ";
            }
        }
        // calculate average
        double total = 0.0;
        for (i = 0; i < Max; i++)
            total += golf[i];
        // report results
        cout << total / Max << " = average score " << Max << " rounds\n";
    }
    ```

    ```cmd
    Please enter your golf scores.
    You must enter 5 rounds.
    round #1: e
    Please enter a number: eee
    Please enter a number: 1
    round #2: 2
    round #3: 3
    round #4: 4
    round #5: 5
    3 = average score 5 rounds
    ```

- condit

  - cin连续输入

    ```c++
    cin >> a >> b
    ```

    当输入a后回车，cin不读，再输入b

  - ..?..:..表达式的使用

    ```c++
    a ? x : y
    ```

    若a真，则x，否则y

    ```c++
    int a, b;
    cout << "Enter two integers: ";
    cin >> a >> b;
    cout << "The larger of " << a << " and " << b;
    int c = a > b ? a : b; // c = a if a > b, else c = b
    cout << " is " << c << endl;
    ```

    ```cmd
    Enter two integers: 23
    23
    The larger of 23 and 23 is 23
    ```

- enum

  - 枚举的使用

    - 将枚举赋值需要强制转换

      例：

      ```c++
      enum Weekday{SUN,MON,TUE,WED,THU,FRI,SAT};//定义枚举类型weekday
      SUN=0;//SUN是枚举元素，不能赋值，此语句非法
      SUN=(Weekday)7;//正确
      ```

      枚举变量依次从0开始，否则无赋值的跟随前面的值加1

    ```c++
    enum
    {
        red,// 0
        orange,
        yellow,
        green,
        blue,
        violet,
        indigo
    };
    main()
    {
        using namespace std;
        cout << "Enter color code (0-6): ";
        int code;
        cin >> code;
        while (code >= red && code <= indigo)
        {
            switch (code)
            {
            case red:
                cout << "Her lips were red.\n";
                break;
            case orange:
                cout << "Her hair was orange.\n";
                break;
            case yellow:
                cout << "Her shoes were yellow.\n";
                break;
            case green:
                cout << "Her nails were green.\n";
                break;
            case blue:
                cout << "Her sweatsuit was blue.\n";
                break;
            case violet:
                cout << "Her eyes were violet.\n";
                break;
            case indigo:
                cout << "Her mood was indigo.\n";
                break;
            }
            cout << "Enter color code (0-6): ";
            cin >> code;
        }
        cout << "Bye\n";
    }
    ```

    ```cmd
    Enter color code (0-6): 0
    Her lips were red.
    Enter color code (0-6): 3
    Her nails were green.
    Enter color code (0-6): 1
    Her hair was orange.
    Enter color code (0-6): 2
    Her shoes were yellow.
    Enter color code (0-6): 4
    Her sweatsuit was blue.
    Enter color code (0-6): 5
    Her eyes were violet.
    Enter color code (0-6): 6
    Her mood was indigo.
    Enter color code (0-6): 7
    Bye
    ```

- if

  - if语句的使用

  ```c++
  char ch;
  int spaces = 0;
  int total = 0;
  cin.get(ch);
  while (ch != '.') // quit at end of sentence
  {
      if (ch == ' ') // check if ch is a space
          ++spaces;
      ++total; // done every time
      cin.get(ch);
  }
  cout << spaces << " spaces, " << total << " characters total in sentence\n";
  ```

  ```cmd
  ef ef sd csd wer.
  4 spaces, 16 characters total in sentence
  ```

- ifelse

  - if-else语句的使用

  ```c++
  char ch;
  std::cout << "Type, and I shall repeat.\n";
  std::cin.get(ch);
  while (ch != '.')
  {
      if (ch == '\n')
          std::cout << ch; // done if newline
      else
          std::cout << ++ch; // done otherwise
      std::cin.get(ch);
  }
  // try ch + 1 instead of ++ch for interesting effect
  std::cout << "\nPlease excuse the slight confusion.\n";
  ```

  ```cmd
  Type, and I shall repeat.
  dsf sdv sdf
  etg!tew!teg
  sdf dsfv dsf.
  teg!etgw!etg
  Please excuse the slight confusion.
  ```

- ifelseif

  - if-else if的使用

    ```c++
    const int Fave = 27;
    main()
    {
        using namespace std;
        int n;

        cout << "Enter a number in the range 1-100 to find ";
        cout << "my favorite number: ";
        do
        {
            cin >> n;
            if (n < Fave)
                cout << "Too low -- guess again: ";
            else if (n > Fave)
                cout << "Too high -- guess again: ";
            else
                cout << Fave << " is right!\n";
        } while (n != Fave);
    }
    ```

    ```cmd
    Enter a number in the range 1-100 to find my favorite number: 25
    Too low -- guess again: 28
    Too high -- guess again: 26
    Too low -- guess again: 27
    27 is right!
    ```

- jump

  - for循环和if语句结合使用

    ```c++
    const int ArSize = 80;
    main()
    {
        using namespace std;
        char line[ArSize];
        int spaces = 0;

        cout << "Enter a line of text:\n";
        cin.get(line, ArSize);
        cout << "Complete line:\n"
             << line << endl;
        cout << "Line through first period:\n";
        for (int i = 0; line[i] != '\0'; i++)
        {
            cout << line[i];    // display character
            if (line[i] == '.') // quit if it's a period
                break;
            if (line[i] != ' ') // skip rest of loop
                continue;
            spaces++;
        }
        cout << "\n"
             << spaces << " spaces\n";
        cout << "Done.\n";
    }
    ```

    ```cmd
    Enter a line of text:
    sdf df vcs.
    Complete line:
    sdf df vcs.
    Line through first period:
    sdf df vcs.
    2 spaces
    Done.
    ```

- more_and

  - 指针数组的调用

  - if-else if的使用

    ```c++
    const char *qualify[4] = // an array of pointers*/
        {                    // to strings
            "10,000-meter race.\n",
            "mud tug-of-war.\n",
            "masters canoe jousting.\n",
            "pie-throwing festival.\n"};
    main()
    {
        using namespace std;
        int age;
        cout << "Enter your age in years: ";
        cin >> age;
        int index;

        if (age > 17 && age < 35)
            index = 0;
        else if (age >= 35 && age < 50)
            index = 1;
        else if (age >= 50 && age < 65)
            index = 2;
        else
            index = 3;

        cout << "You qualify for the " << qualify[index];
    }
    ```

    ```cmd
    Enter your age in years: 20
    You qualify for the 10,000-meter race.
    ```

- not

  - 函数的定义调用

  - if-else语句的使用

    ```c++
    bool is_int(double);
    main()
    {
        using namespace std;
        double num;

        cout << "Yo, dude! Enter an integer value: ";
        cin >> num;
        while (!is_int(num)) // continue while num is not int-able
        {
            cout << "Out of range -- please try again: ";
            cin >> num;
        }
        int val = int(num); // type cast
        cout << "You've entered the integer " << val << "\nBye\n";
    }
    bool is_int(double x)
    {
        if (x <= INT_MAX && x >= INT_MIN) // use climits values
            return true;
        else
            return false;
    }
    ```

    ```cmd
    Yo, dude! Enter an integer value: 324324234234234234523423423523423
    Out of range -- please try again: 234234232
    You've entered the integer 234234232
    Bye
    ```

- or

  - if-else if的应用

    ```c++
    cout << "This program may reformat your hard disk\n"
            "and destroy all your data.\n"
            "Do you wish to continue? <y/n> ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') // y or Y
        cout << "You were warned!\a\a\n";
    else if (ch == 'n' || ch == 'N') // n or N
        cout << "A wise choice ... bye\n";
    else
        cout << "That wasn't a y or n! Apparently you "
                "can't follow\ninstructions, so "
                "I'll trash your disk anyway.\a\a\a\n";
    ```

    ```cmd
    This program may reformat your hard disk
    and destroy all your data.
    Do you wish to continue? <y/n> y
    You were warned!
    ```

- outfile

  - 写文件

    - 创建输出文件流

      ```c++
      #include <fstream>
      ofstream outFile;
      ```

    - 打开文件

      没有文件会自动创建

      ```c++
      outFile.open("carinfo.txt")
      ```

    - 写进文件

      相当于将数据输入到outFile流，使用<<即可

      ```c++
      outFile << fixed;
      outFile.precision(2);
      outFile.setf(ios_base::showpoint);
      outFile << "Make and model: " << automobile << endl;
      outFile << "Year: " << year << endl;
      outFile << "Was asking $" << a_price << endl;
      outFile << "Now asking $" << d_price << endl;
      ```

    - 关闭文件

      ```c++
      outFile.close()
      ```

  - 设置流格式

    - 浮点数输出

      ```c++
      cout << fixed; // 以浮点数输出，而不是以科学计数法输出
      ```

    - 配合浮点数，设置保留几位小数

      ```c++
      cout.precision(2);
      ```

    - 配合浮点数，显示保留位数的0

      ```c++
      cout.setf(ios_base::showpoint);
      ```

- sumafile

  ```c++
  const int SIZE = 60;
  main()
  {
      using namespace std;
      char filename[SIZE];
      ifstream inFile; // object for handling file input

      cout << "Enter name of data file: ";
      cin.getline(filename, SIZE);
      inFile.open(filename); // associate inFile with a file
      if (!inFile.is_open()) // failed to open file
      {
          cout << "Could not open the file " << filename << endl;
          cout << "Program terminating.\n";
          // cin.get();    // keep window open
          exit(EXIT_FAILURE);
      }
      double value;
      double sum = 0.0;
      int count = 0; // number of items read

      inFile >> value;      // get first value
      while (inFile.good()) // while input good and not at EOF
      {
          ++count;         // one more item read
          sum += value;    // calculate running total
          inFile >> value; // get next value
      }
      if (inFile.eof())
          cout << "End of file reached.\n";
      else if (inFile.fail())
          cout << "Input terminated by data mismatch.\n";
      else
          cout << "Input terminated for unknown reason.\n";
      if (count == 0)
          cout << "No data processed.\n";
      else
      {
          cout << "Items read: " << count << endl;
          cout << "Sum: " << sum << endl;
          cout << "Average: " << sum / count << endl;
      }
      inFile.close();
  }
  ```

  ```cmd
  Enter name of data file: caroutfo.txt
  End of file reached.
  Items read: 2
  Sum: 2025
  Average: 1012.5
  ```

  ```txt
  2020
  05
  02
  ```

  - 读文件

    - 创建读文件流

      ```c++
      #include <fstream>
      ifstream inFile;
      ```

    - 打开文件

      ```c++
      inFile.open(filename);
      ```

    - 判断是否打开文件

      ```c++
      inFile.is_open() // 成功返回1，否则返回0
      ```

    - 判断文件是否异常

      ```c++
      inFile.good() // true表示文件正常，没有读写错误，也不是坏的，也没有结束, 否则false
      ```

    - 判断文件是否结束

      ```c++
      inFile.eof() // true表示文件结束
      ```

    - 判断读文件是否存在逻辑错误

      ```c++
      inFile.fail() // true表示存在逻辑错误
      ```

  - 异常处理

    ```c++
    #include <cstdlib>
    exit(1) // exit(1)和exit(-1)
    // exit(0)表示程序正常退出，非0表示非正常退出
    ```

- switch

  - switch的使用

    ```c++
    void showmenu(); // function prototypes
    void report();
    void comfort();
    main()
    {
        showmenu();
        int choice;
        cin >> choice;
        while (choice != 5)
        {
            switch (choice)
            {
            case 1:
                cout << "\a\n";
                break;
            case 2:
                report();
                break;
            case 3:
                cout << "The boss was in all day.\n";
                break;
            case 4:
                comfort();
                break;
            default:
                cout << "That's not a choice.\n";
            }
            showmenu();
            cin >> choice;
        }
        cout << "Bye!\n";
    }

    void showmenu()
    {
        cout << "Please enter 1, 2, 3, 4, or 5:\n"
                "1) alarm           2) report\n"
                "3) alibi           4) comfort\n"
                "5) quit\n";
    }
    void report()
    {
        cout << "It's been an excellent week for business.\n"
                "Sales are up 120%. Expenses are down 35%.\n";
    }
    void comfort()
    {
        cout << "Your employees think you are the finest CEO\n"
                "in the industry. The board of directors think\n"
                "you are the finest CEO in the industry.\n";
    }
    ```

    ```cmd
    Please enter 1, 2, 3, 4, or 5:
    1) alarm           2) report
    3) alibi           4) comfort
    5) quit
    1

    Please enter 1, 2, 3, 4, or 5:
    1) alarm           2) report
    3) alibi           4) comfort
    5) quit
    2
    It's been an excellent week for business.
    Sales are up 120%. Expenses are down 35%.
    Please enter 1, 2, 3, 4, or 5:
    1) alarm           2) report
    3) alibi           4) comfort
    5) quit
    3
    The boss was in all day.
    Please enter 1, 2, 3, 4, or 5:
    1) alarm           2) report
    3) alibi           4) comfort
    5) quit
    4
    Your employees think you are the finest CEO
    in the industry. The board of directors think
    you are the finest CEO in the industry.
    Please enter 1, 2, 3, 4, or 5:
    1) alarm           2) report
    3) alibi           4) comfort
    5) quit
    5
    Bye!
    ```
