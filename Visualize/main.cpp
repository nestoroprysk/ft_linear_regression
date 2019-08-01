#include <Utils.hpp>

#include <array>
#include <iostream>

namespace {

const auto collect = [](auto&&... args){
    const auto array = std::array<std::string, sizeof...(args)>{ std::forward<decltype(args)>(args)... };
    auto result = std::string();
    for (const auto s : array)
        result += s + ' ';
    return result;
};

}

int main()
{
    try{
        const auto python = std::string("python");
        const auto visualizer = Utils::getFullPathToVisualizeDir("plot.py");
        const auto dataFile = Utils::getDataFileFullName();
        const auto lineFile = Utils::getLineFileFullName();
        system(collect(python, visualizer, dataFile, lineFile).c_str());
    }
    catch(...){
        std::cout << "Unable to visualize" << std::endl;
    }
}
