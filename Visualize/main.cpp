#include <Utils.hpp>

#include <array>

namespace {

template <typename... Args>
std::string collect(Args&&... args)
{
    const auto array = std::array<std::string, sizeof...(args)>{ std::forward<Args>(args)... };
    auto result = std::string();
    for (const auto s : array)
        result += s + ' ';
    return result;
}

}

int main()
{
    const auto python = std::string("python");
    const auto visualizer = Utils::getFullPathToVisualizeDir("plot.py");
    const auto dataFile = Utils::getFullPathToRootDir("data.txt");
    const auto lineFile = Utils::getFullPathToBuildDir("line.txt");
    system(collect(python, visualizer, dataFile, lineFile).c_str());
}
