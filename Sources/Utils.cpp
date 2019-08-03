#include "Utils.hpp"

#include <numeric>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <array>

namespace {

std::string getFileToSaveDataFilePathName()
{
    static constexpr auto g_file_to_save_path_to_data = "subjectDataPath.txt";
    return Utils::getFullPathToBuildDir(g_file_to_save_path_to_data);
}

double newA(const List& i_xs, const List& i_ys,
                                const Pair& i_result, const double i_learning_rate)
{
    return i_result.first - i_learning_rate * Utils::costDerivativeA(i_xs, i_ys, i_result);
}

double newB(const List& i_xs, const List& i_ys,
                                const Pair& i_result, const double i_learning_rate)
{
    return i_result.second - i_learning_rate * Utils::constDerivativeB(i_xs, i_ys, i_result);
}

}

std::string Utils::getFullPathToBuildDir(const std::string& i_file_name)
{
    return std::string(PATH_TO_BUILD_DIR) + '/' + i_file_name;
}

std::string Utils::getFullPathToVisualizeDir(const std::string& i_file_name)
{
    return std::string(PATH_TO_VISUALIZE_DIR) + '/' + i_file_name;
}

std::string Utils::getFullPathToRootDir(const std::string& i_file_name)
{
    return std::string(PATH_TO_ROOT_DIR) + '/' + i_file_name;
}

std::string Utils::getFullPathToDataDir(const std::string& i_file_name)
{
    return std::string(PATH_TO_DATA_DIR) + '/' + i_file_name;
}

Pair Utils::getCoefficients()
{
    auto lineFile = std::ifstream(getLineFileFullName());
    std::string line; std::getline(lineFile, line);
    const auto [a, b] = Utils::parseLine(line);
    return { a, b };
}

std::string Utils::getDataFileFullName()
{
    auto file = std::ifstream(getFileToSaveDataFilePathName());
    if (!file)
        throw std::logic_error("Cannot open file [" +
            getFileToSaveDataFilePathName() + ']');
    std::string s; std::getline(file, s);
    return s;
}

std::string Utils::getLineFileFullName()
{
    static constexpr auto g_file_to_save_line_to = "line.txt";
    return  Utils::getFullPathToBuildDir(g_file_to_save_line_to);
}

void Utils::save(const Pair& i_result)
{
    auto file = std::ofstream(getLineFileFullName());
    if (!file)
        throw std::logic_error("Cannot open the file [" +
            std::string(getFileToSaveDataFilePathName()) +
                " for writing");
    file << i_result.first << ',' << i_result.second << std::endl;
}

void Utils::save(const std::string& i_file_name)
{
    auto file = std::ofstream(getFileToSaveDataFilePathName());
    if (!file)
        throw std::logic_error("Cannot open [" +
            std::string(getFileToSaveDataFilePathName())
                + "] for writing");
    file << i_file_name << std::endl;
}


std::pair<List, List> Utils::parse(const std::string& i_file_name)
{
    auto result = std::pair<List, List>();
    auto file = std::ifstream(i_file_name);
    if (!file)
        throw std::logic_error("Cannot open the file [" + i_file_name + ']');
    { std::string s; std::getline(file, s); }
    auto xs = List();
    auto ys = List();
    for (std::string line; std::getline(file, line);){
        const auto [x, y] = parseLine(line);
        xs.emplace_back(x);
        ys.emplace_back(y);
    }
    return { std::move(xs), std::move(ys) };
}

Pair Utils::parseLine(const std::string& line)
{
    return { std::stod(std::string(line.cbegin(),
                std::find(line.cbegin(), line.cend(), ','))),
             std::stod(std::string(std::next(std::find(line.cbegin(),
                line.cend(), ',')), line.cend()))
    };
}

double Utils::h(const double x, const double a, const double b)
{
    return a + b * x;
}

double Utils::cost(const List& i_xs, const List& i_ys, const double a, const double b)
{
    auto result = double(0);
    const auto size = i_xs.size();
    for (std::size_t i = 0; i < size; ++i)
        result += std::pow(h(i_xs[i], a, b) - i_ys[i], 2);
    return (1.0 / (2.0 * size)) * result;
}

double Utils::costDerivativeA(const List& i_xs, const List& i_ys, const Pair& i_result)
{
    auto result = double(0);
    const auto size = i_xs.size();
    for (std::size_t i = 0; i < size; ++i)
        result += h(i_xs[i], i_result.first, i_result.second) - i_ys[i];
    return (1.0 / size) * result;
}

double Utils::constDerivativeB(const List& i_xs, const List& i_ys, const Pair& i_result)
{
    auto result = double(0);
    const auto size = i_xs.size();
    for (std::size_t i = 0; i < size; ++i)
        result += (h(i_xs[i], i_result.first, i_result.second) - i_ys[i]) * i_xs[i];
    return (1.0 / size) * result;
}

std::optional<Pair> Utils::update(const List& i_xs, const List& i_ys,
                                    const Pair& i_result, const double i_learning_rate)
{
    if (std::isinf(i_result.first) || std::isinf(i_result.second))
        return {};
    if (std::isnan(i_result.first) || std::isnan(i_result.second))
        return {};
    const auto a = newA(i_xs, i_ys, i_result, i_learning_rate);
    const auto b = newB(i_xs, i_ys, i_result, i_learning_rate);
    if (eq(a, i_result.first) && eq(b, i_result.second))
        return {};
    return Pair{a, b};
}

double Utils::assess(const double x)
{
    const auto [xs, ys] = parse(getDataFileFullName());
    const auto [a, b] = getCoefficients();
    const auto normalised_y = h(normalise(xs, x), a, b);
    return unnormalise(ys, normalised_y);
}

double Utils::precision(const double a, const double b)
{
    const auto [xs, ys] = parse(getDataFileFullName());
    return cost(normalise(xs), normalise(ys), a, b);
}

bool Utils::eq(const double a, const double b)
{
    return abs(a - b) < e || abs(b - a) < e;
}

double Utils::abs(const double a)
{
    return a < 0.0 ? -a : a;
}

double Utils::max(const List& i_data)
{
    return std::accumulate(i_data.cbegin(), i_data.cend(),
        std::numeric_limits<double>::min(),
        [](const auto init, const auto& d){ return std::max(init, d);
    });
}

double Utils::min(const List& i_data)
{
    return std::accumulate(i_data.cbegin(), i_data.cend(),
        std::numeric_limits<double>::max(),
        [](const auto init, const auto& d){ return std::min(init, d);
    });
}

List Utils::normalise(const List& i_data)
{
    const auto minimum = min(i_data);
    const auto maximum = max(i_data);
    auto result = List();
    for (const auto& n : i_data)
        result.emplace_back((n - minimum) / (maximum - minimum));
    return result;
}

double Utils::normalise(const List& i_prior_data, const double n)
{
    const auto minimum = min(i_prior_data);
    const auto maximum = max(i_prior_data);
    return (n - minimum) / (maximum - minimum);
}

double Utils::unnormalise(const List& i_prior_data, const double n)
{
    const auto minimum = min(i_prior_data);
    const auto maximum = max(i_prior_data);
    return n * (maximum - minimum) + minimum;
}
