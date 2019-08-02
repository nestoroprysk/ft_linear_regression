#include <Utils.hpp>

#include <iostream>

namespace {

static constexpr auto g_learning_rate = double(0.1);

const auto run = [](const auto& i_data){
    auto result = Utils::Result();
    while (auto opt_result = update(i_data, result, g_learning_rate))
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
        const auto result = run(normalise(parse(fileFullName)));
        save(result);
        std::cout << "a: [" << result.a << ']' << std::endl;
        std::cout << "b: [" << result.b << ']' << std::endl;
    }
    catch (const std::logic_error& e){
        std::cout << e.what() << std::endl;
    }
    catch (...){
        std::cout << "Unable to learn from the given data" << std::endl;
    }
}
