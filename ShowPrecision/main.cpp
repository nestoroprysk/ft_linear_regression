#include <Utils.hpp>

#include <iostream>

int main()
{
    try{
        using namespace Utils;
        const auto [a, b] = getCoefficients();
        const auto p = precision(a, b);
        std::cout << "cost for a = [" << a <<
            "] and b = [" << b << "] is [" <<
                p << ']' << std::endl;
    }
    catch (const std::logic_error& e){
        std::cout << "Unable to show the precision" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << "Call to ./Learn expected" << std::endl;
    }
    catch (...){
        std::cout << "Unable to show the precision" << std::endl;
        std::cout << "Call to ./Learn expected" << std::endl;
    }
}
