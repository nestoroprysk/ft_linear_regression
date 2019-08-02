#include <Utils.hpp>

#include <iostream>

namespace {

static constexpr auto g_usage = R"(
Usage:
    ./Assess x
)";

}

int main(const int argc, const char** argv)
{
    try{
        if (argc != 2)
            throw std::out_of_range("Single argument expected");
        using namespace Utils;
        const auto x = std::stod(argv[1]);
        const auto data = parse(getDataFileFullName());
        const auto [a, b] = getCoefficients();
        std::cout << "for [" << x << "] y is [" <<
            unnormalise(data, h(normalise(data, x), a, b)) << ']' << std::endl; 
    }
    catch (const std::logic_error e){
        std::cout << e.what() << std::endl;
        std::cout << g_usage << std::endl;
    }
    catch(...){
        std::cout << g_usage << std::endl;
    }
}
