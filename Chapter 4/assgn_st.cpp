// assgn_st.cpp -- assigning structures
#include <iostream>
struct inflatable
{
    char name[20];
    float volume;
    double price;
};
int main()
{
    using namespace std;
    inflatable bouquet = {"sunflowers", 0.20, 12.49};
    inflatable choice;
    cout << "bouquet: " << bouquet.name << " for $" << bouquet.price << endl;

    choice = bouquet; // assign one structure to another
    cout << "choice: " << choice.name << " for $" << choice.price << endl;
    // cin.get();
    system("pause");
    return 0;
}
