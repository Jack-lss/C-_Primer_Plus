// instr1.cpp -- reading more than one string
#include <iostream>
#include <string>
int main()
{
    using namespace std;
    const int ArSize = 20;
    char name[ArSize];
    char dessert[ArSize];

    cout << "Enter your name:\n";
    cin >> name;
    // cin.get(); // 被忽略
    cout << "Enter your favorite dessert:\n";
    cin >> dessert;
    cout << "I have some delicious " << dessert << " for you, " << name << ".\n";
    // cin.get();
    cin.get();

    string ds;
    getline(cin, ds);
    system("pause");
    return 0;
}
