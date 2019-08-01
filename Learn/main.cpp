#include <Utils.hpp>

#include <iostream>

namespace {

static constexpr auto g_usage = R"(
noprysk, 2019

Usage:
    ./Learn file.txt learning_rate
)";

}

int main(const int argc, const char** argv)
{
    try{
        if (argc != 3)
            throw std::out_of_range("");
        const auto normaliser = Utils::Normaliser(Utils::parse(argv[1]));
        const auto data = normaliser.normalise();
        const auto learning_rate = std::stod(argv[2]);
        auto result = Utils::Result();
        while (auto opt_result = Utils::update(data, result, learning_rate))
            result = *opt_result;
        Utils::save(normaliser.unnormalise(result));
    }
    catch (...){
        std::cout << g_usage << std::endl;
    }
}
