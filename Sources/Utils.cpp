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

double newA(const std::vector<std::pair<double, double>>& i_data,
                                const std::pair<double, double>& i_result, const double i_learning_rate)
{
    return i_result.first - i_learning_rate * Utils::costDerivativeA(i_data, i_result);
}

double newB(const std::vector<std::pair<double, double>>& i_data,
                                const std::pair<double, double>& i_result, const double i_learning_rate)
{
    return i_result.second - i_learning_rate * Utils::constDerivativeB(i_data, i_result);
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

std::pair<double, double> Utils::getCoefficients()
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

void Utils::save(const std::pair<double, double>& i_result)
{
    auto file = std::ofstream(getLineFileFullName());
    if (!file)
        throw std::logic_error("Cannot open the file [" + std::string(getFileToSaveDataFilePathName()) +
                " for writing");
    file << i_result.first << ',' << i_result.second << std::endl;
}

void Utils::save(const std::string& i_file_name)
{
    auto file = std::ofstream(getFileToSaveDataFilePathName());
    if (!file)
        throw std::logic_error("Cannot open [" + std::string(getFileToSaveDataFilePathName())
            + "] for writing");
    file << i_file_name << std::endl;
}


std::vector<std::pair<double, double>> Utils::parse(const std::string& i_file_name)
{
    auto result = std::vector<std::pair<double, double>>();
    auto file = std::ifstream(i_file_name);
    if (!file)
        throw std::logic_error("Cannot open the file [" + i_file_name + ']');
    { std::string s; std::getline(file, s); }
    for (std::string line; std::getline(file, line);)
        result.emplace_back(parseLine(line));
    return result;
}

std::pair<double, double> Utils::parseLine(const std::string& line)
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
double Utils::cost(const std::vector<std::pair<double, double>>& i_data, const double a, const double b)
{
    return (1.0 / (2.0 * i_data.size())) * 
        std::accumulate(i_data.cbegin(), i_data.cend(), double(0),
            [&](const auto init, const auto d)
                { return init + std::pow(h(d.first, a, b) - d.second, 2); } );
}

double Utils::costDerivativeA(const std::vector<std::pair<double, double>>& i_data, const std::pair<double, double>& i_result)
{
    return (1.0 / i_data.size()) *
        std::accumulate(i_data.cbegin(), i_data.cend(), double(0),
            [&](const auto init, const auto d)
                { return init + h(d.first, i_result.first, i_result.second) - d.second; } );
}

double Utils::constDerivativeB(const std::vector<std::pair<double, double>>& i_data, const std::pair<double, double>& i_result)
{
    return (1.0 / i_data.size()) *
        std::accumulate(i_data.cbegin(), i_data.cend(), double(0),
            [&](const auto init, const auto d)
                { return init + (h(d.first, i_result.first, i_result.second) - d.second) * d.first; } );
}

std::optional<std::pair<double, double>> Utils::update(const std::vector<std::pair<double, double>>& i_data,
                                            const std::pair<double, double>& i_result, const double i_learning_rate)
{
    if (std::isinf(i_result.first) || std::isinf(i_result.second))
        return {};
    if (std::isnan(i_result.first) || std::isnan(i_result.second))
        return {};
    const auto a = newA(i_data, i_result, i_learning_rate);
    const auto b = newB(i_data, i_result, i_learning_rate);
    if (eq(a, i_result.first) && eq(b, i_result.second))
        return {};
    return std::pair<double, double>{a, b};
}

bool Utils::eq(const double a, const double b)
{
    return abs(a - b) < e || abs(b - a) < e;
}

double Utils::abs(const double a)
{
    return a < 0.0 ? -a : a;
}

std::vector<std::pair<double, double>> Utils::normalise(const std::vector<std::pair<double, double>>& i_data)
{
    const auto minX = min(i_data, [](const auto& d){return d.first;});
    const auto maxX = max(i_data, [](const auto& d){return d.first;});
    const auto minY = min(i_data, [](const auto& d){return d.second;});
    const auto maxY = max(i_data, [](const auto& d){return d.second;});
    auto result = std::vector<std::pair<double, double>>();
    for (const auto& d : i_data){
        const auto x = (d.first - minX) / (maxX - minX);
        const auto y = (d.second - minY) / (maxY - minY);
        result.emplace_back(x, y);
    }
    return result;
}

double Utils::normalise(const std::vector<std::pair<double, double>>& i_prior_data, const double x)
{
    const auto minX = min(i_prior_data, [](const auto& d){return d.first;});
    const auto maxX = max(i_prior_data, [](const auto& d){return d.first;});
    return (x - minX) / (maxX - minX);
}

double Utils::unnormalise(const std::vector<std::pair<double, double>>& i_prior_data, const double y)
{
    const auto minY = min(i_prior_data, [](const auto& d){return d.second;});
    const auto maxY = max(i_prior_data, [](const auto& d){return d.second;});
    return y * (maxY - minY) + minY;
}

double Utils::assess(const double x)
{
    const auto prior_data = parse(getDataFileFullName());
    const auto [a, b] = getCoefficients();
    const auto normalised_y = h(normalise(prior_data, x), a, b);
    return unnormalise(prior_data, normalised_y);
}

double Utils::max(const std::vector<std::pair<double, double>>& i_data, const std::function<double(const std::pair<double, double>&)>& i_get)
{
    return std::accumulate(i_data.cbegin(), i_data.cend(), std::numeric_limits<double>::min(),
        [&](const auto init, const auto& d){ return std::max(init, i_get(d));
    });
};

double Utils::min(const std::vector<std::pair<double, double>>& i_data, const std::function<double(const std::pair<double, double>&)>& i_get)
{
    return std::accumulate(i_data.cbegin(), i_data.cend(), std::numeric_limits<double>::max(),
        [&](const auto init, const auto& d){ return std::min(init, i_get(d));
    });
};

double Utils::precision(const double a, const double b)
{
    const auto normalised_data = normalise(parse(getDataFileFullName()));
    return cost(normalised_data, a, b);
}
