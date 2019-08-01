#include <Utils.hpp>

#include <iostream>

namespace {

const auto getData = []{
    const auto dataFile = Utils::getFullPathToRootDir("data.txt");
    return Utils::parse(dataFile);
};

};

int main()
{
    try{
        const auto [a, b] = Utils::getCoefficients();
        std::cout << "cost for a = [" << a <<
            "] and b = [" << b << "] is [" <<
                Utils::cost(getData(), a, b) << ']' << std::endl;
    }
    catch (...){
        std::cout << "Unable to show the precision" << std::endl;
    }
}
