// delete.cpp -- using the delete operator
#include <iostream>
#include <cstring> // or string.h
using namespace std;
char *getname(void); // function prototype
int main()
{
    char *name; // create pointer but no storage
    char *name1;

    name = getname(); // assign address of string to name
    cout << name << " at " << (int *)name << "\n";
    delete[] name; // memory freed

    name1 = getname(); // reuse freed memory
    cout << name1 << " at " << (int *)name1 << "\n";
    delete[] name1; // memory freed again
    // cin.get();
    // cin.get();
    system("pause");
    return 0;
}

char *getname() // return pointer to new string
{
    char temp[80]; // temporary storage
    cout << "Enter last name: ";
    cin >> temp;
    char *pn = new char[strlen(temp) + 1];
    strcpy(pn, temp); // copy string into smaller space

    return pn; // temp lost when function ends
}
