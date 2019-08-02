#include <Utils.hpp>

#include <iostream>

int main()
{
    try{
        using namespace Utils;
        const auto [a, b] = getCoefficients();
        const auto data = normalise(parse(getDataFileFullName()));
        std::cout << "cost for a = [" << a <<
            "] and b = [" << b << "] is [" <<
                cost(data, a, b) << ']' << std::endl;
    }
    catch (const std::logic_error& e){
        std::cout << e.what() << std::endl;
    }
    catch (...){
        std::cout << "Unable to show the precision" << std::endl;
    }
}
