#include <Utils.hpp>

#include <iostream>

namespace {

static constexpr auto g_usage = R"(
Usage:
    ./Assess x

Note:
    call ./Learn so as to enable the assessment
)";

}

int main(const int argc, const char** argv)
{
    try{
        if (argc != 2)
            throw std::out_of_range("Single argument expected");
        const auto x = std::stod(argv[1]);
        const auto result = Utils::assess(x);
        std::cout << "for [" << x << "] y is [" <<
            result << ']' << std::endl; 
    }
    catch (const std::logic_error e){
        std::cout << "Unable to assess" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << g_usage << std::endl;
    }
    catch(...){
        std::cout << "Unable to assess" << std::endl;
        std::cout << g_usage << std::endl;
    }
}
