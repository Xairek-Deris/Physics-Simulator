#include <iostream>
int x = 5;

namespace test
{
    int x = 6;
    int func()
    {
        return x;
    }
}

int main()
{
    std::cout << test::func() << std::endl;
    return 0;
}