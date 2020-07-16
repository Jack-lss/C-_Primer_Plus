// waiting.cpp -- using clock() in a time-delay loop
#include <iostream>
#include <ctime> // describes clock() function, clock_t type
int main()
{
    using namespace std;
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
    // cin.get();
    // cin.get();
    system("pause");
    return 0;
}
