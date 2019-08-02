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

const auto getFirstPoint = []()->std::pair<double, double>{
    const auto dataFile = Utils::getDataFileFullName();
    const auto [xs, _] = Utils::parse(dataFile);
    const auto min_x = Utils::min(xs);
    return { min_x, Utils::assess(min_x) };
};

const auto getSecondPoint = []()->std::pair<double, double>{
    const auto dataFile = Utils::getDataFileFullName();
    const auto [xs, _] = Utils::parse(dataFile);
    const auto max_x = Utils::max(xs);
    return { max_x, Utils::assess(max_x) };
};

}

int main()
{
    try{
        const auto python = std::string("python");
        const auto visualizer = Utils::getFullPathToVisualizeDir("plot.py");
        const auto dataFile = Utils::getDataFileFullName();
        const auto [min_x, y_min_x] = getFirstPoint();
        const auto [max_x, y_max_x] = getSecondPoint();
        system(collect(python, visualizer, dataFile,
            std::to_string(min_x), std::to_string(y_min_x),
            std::to_string(max_x), std::to_string(y_max_x)).c_str());
    }
    catch(...){
        std::cout << "Unable to visualize" << std::endl;
    }
}
