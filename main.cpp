#include <iostream>
#include "Lemmatizator.h"

int main()
{
    auto lemms = Lemmatizator::lemmatize("/home/vadim/coding/lemm/stest.txt");
    for (auto lemm : lemms)
    {
        std::wcout << "_" << lemm.first << "_" << " - " << lemm.second << '\n';
    }
    
    std::cout << "\n\n\n\n";
    
    return 0;
}