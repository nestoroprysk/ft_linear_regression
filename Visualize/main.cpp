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
    const auto prior_data = Utils::parse(dataFile);
    const auto min_x = Utils::min(prior_data, [](const auto& d){return d.x;});
    return { min_x, Utils::assess(min_x) };
};

const auto getSecondPoint = []()->std::pair<double, double>{
    const auto dataFile = Utils::getDataFileFullName();
    const auto prior_data = Utils::parse(dataFile);
    const auto max_x = Utils::max(prior_data, [](const auto& d){return d.x;});
    return { max_x, Utils::assess(max_x) };
};

}

int main()
{
    try{
        const auto python = std::string("python");
        const auto visualizer = Utils::getFullPathToVisualizeDir("plot.py");
        const auto dataFile = Utils::getDataFileFullName();
        const auto [minX, yMinX] = getFirstPoint();
        const auto [maxX, yMaxX] = getSecondPoint();
        system(collect(python, visualizer, dataFile,
            std::to_string(minX), std::to_string(yMinX),
            std::to_string(maxX), std::to_string(yMaxX)).c_str());
    }
    catch(...){
        std::cout << "Unable to visualize" << std::endl;
    }
}
