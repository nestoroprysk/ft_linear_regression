#include <Utils.hpp>

#include <iostream>

namespace {

// experimentally induced
static constexpr auto g_learning_rate = double(0.0252);

const auto run = [](const auto& i_xs, const auto& i_ys){
    auto result = Pair(0, 0);
    while (auto opt_result = Utils::update(i_xs, i_ys, result, g_learning_rate))
        result = *opt_result;
    return result;
};

const auto getFileFullName = [](const auto argc, const auto** argv){
    static constexpr auto g_default_data_file_name = "subjectData.txt";
    if (argc != 2)
        return Utils::getFullPathToDataDir(g_default_data_file_name);
    return Utils::getFullPathToDataDir(argv[1]);
};

}

int main(const int argc, const char** argv)
{
    try{
        using namespace Utils;
        const auto fileFullName = getFileFullName(argc, argv);
        save(fileFullName);
        const auto [xs, ys] = parse(fileFullName);
        const auto result = run(normalise(xs), normalise(ys));
        save(result);
        std::cout << "a: [" << result.first << ']' << std::endl;
        std::cout << "b: [" << result.second << ']' << std::endl;
    }
    catch (const std::logic_error& e){
        std::cout << "Unable to learn from the given data" << std::endl;
        std::cout << e.what() << std::endl;
    }
    catch (...){
        std::cout << "Unable to learn from the given data" << std::endl;
    }
}
