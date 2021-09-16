#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "Here are you arguments:" << std::endl;

    for (int i = 1; i < argc; i++) {
        std::cout << argv[i] << std::endl;
    }
    

    return 0;
}