#include <Utils.hpp>

#include <iostream>
#include <fstream>

namespace {

const auto getData = []{
    const auto dataFile = Utils::getFullPathToRootDir("data.txt");
    return Utils::parse(dataFile);
};

const auto getCoefficients = []{
    auto lineFile = std::ifstream(Utils::getFullPathToBuildDir("line.txt"));
    std::string line; std::getline(lineFile, line);
    return Utils::parseLine(line);
};

};

int main()
{
    try{
        const auto [a, b] = getCoefficients();
        std::cout << "cost for a = [" << a <<
            "] and b = [" << b << "] is [" <<
                Utils::cost(getData(), a, b) << ']' << std::endl;
    }
    catch (...){
        std::cout << "Unable to assess" << std::endl;
    }
}
