#include <Utils.hpp>

#include <iostream>

int main()
{
    try{
        const auto [a, b] = Utils::getCoefficients();
        const auto data = Utils::parse(Utils::getDataFileFullName());
        std::cout << "cost for a = [" << a <<
            "] and b = [" << b << "] is [" <<
                Utils::cost(data, a, b) << ']' << std::endl;
    }
    catch (const std::logic_error& e){
        std::cout << e.what() << std::endl;
    }
    catch (...){
        std::cout << "Unable to show the precision" << std::endl;
    }
}
