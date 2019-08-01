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
            throw std::out_of_range("");
        const auto x = std::stod(argv[1]);
        const auto [a, b] = Utils::getCoefficients();
        std::cout << "for [" << x << "] y is [" <<
            Utils::h(x, a, b) << ']' << std::endl; 
    }
    catch(...){
        std::cout << g_usage << std::endl;
    }
}
