// mixtypes.cpp --some type combinations
#include <iostream>

struct antarctica_years_end
{
    int year;
    /* some really interesting data, etc. */
};

int main()
{
    antarctica_years_end s01, s02, s03;
    s01.year = 1998;
    antarctica_years_end *pa = &s02;
    pa->year = 1999;
    antarctica_years_end trio[3]; // array of 3 structures
    trio[0].year = 2003;
    std::cout << trio->year << std::endl;
    const antarctica_years_end *arp[3] = {&s01, &s02, &s03};

    const antarctica_years_end arp1[3] = {s01, s02, s03};
    const antarctica_years_end *arp2 = arp1;
    std::cout << arp2[1].year << std::endl;

    const antarctica_years_end(*arp3)[3] = &arp1;
    const antarctica_years_end arp4[][3] = {s01, s02, s03};
    std::cout << ((*arp3) + 1)->year << std::endl;
    std::cout << ((*arp4) + 1)->year << std::endl;

    std::cout << (*(arp + 1))->year << std::endl;
    const antarctica_years_end **ppa = arp;
    auto ppb = arp; // C++0x automatic type deduction
                    // or else use const antarctica_years_end ** ppb = arp;
    std::cout << (*ppa)->year << std::endl;
    std::cout << (*(ppb + 1))->year << std::endl;
    // std::cin.get();
    system("pause");
    return 0;
}