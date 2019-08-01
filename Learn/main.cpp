#include <Utils.hpp>

#include <iostream>

namespace {

static constexpr auto g_data_file_name = "data.txt";
static constexpr auto g_learning_rate = double(1.66624);

const auto run = [](const auto& normaliser){
    const auto data = normaliser.normalise();
    auto result = Utils::Result();
    while (auto opt_result = update(data, result, g_learning_rate))
        result = *opt_result;
    return normaliser.unnormalise(result);
};

}

int main()
{
    try{
        using namespace Utils;
        const auto normaliser = Normaliser(parse(getFullPathToRootDir(g_data_file_name)));
        const auto result = run(normaliser);
        save(result);
        std::cout << "a: [" << result.a << ']' << std::endl;
        std::cout << "b: [" << result.b << ']' << std::endl;
    }
    catch (const std::logic_error e){
        std::cout << e.what() << std::endl;
    }
    catch (...){
        std::cout << "Unable to learn from the given data" << std::endl;
    }
}
