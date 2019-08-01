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

double newA(const std::vector<Utils::Data>& i_data,
                                const Utils::Result& i_result, const double i_learning_rate)
{
    return i_result.a - i_learning_rate * costDerivativeA(i_data, i_result);
}

double newB(const std::vector<Utils::Data>& i_data,
                                const Utils::Result& i_result, const double i_learning_rate)
{
    return i_result.b - i_learning_rate * constDerivativeB(i_data, i_result);
}

const auto max = [](const auto& i_data, const auto& i_get){
    return std::accumulate(i_data.cbegin(), i_data.cend(), double(0),
        [&](const auto init, const auto& d){ return std::max(init, i_get(d));
    });
};

const auto avg = [](auto... args)
{
    const auto array = std::array<double, sizeof...(args)>{args...};
    return std::accumulate(array.begin(), array.end(), double(0), 
        [](const auto a, const auto b){ return a + b; }
    ) / static_cast<double>(array.size());
};

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

void Utils::save(const Result& i_result)
{
    auto file = std::ofstream(getLineFileFullName());
    if (!file)
        throw std::logic_error("Cannot open the file [" + std::string(getFileToSaveDataFilePathName()) +
                " for writing");
    file << i_result.a << ',' << i_result.b << std::endl;
}

void Utils::save(const std::string& i_file_name)
{
    auto file = std::ofstream(getFileToSaveDataFilePathName());
    if (!file)
        throw std::logic_error("Cannot open [" + std::string(getFileToSaveDataFilePathName())
            + "] for writing");
    file << i_file_name << std::endl;
}


std::vector<Utils::Data> Utils::parse(const std::string& i_file_name)
{
    auto result = std::vector<Data>();
    auto file = std::ifstream(i_file_name);
    if (!file)
        throw std::logic_error("Cannot open the file [" + i_file_name + ']');
    { std::string s; std::getline(file, s); }
    for (std::string line; std::getline(file, line);)
        result.emplace_back(parseLine(line));
    return result;
}

Utils::Data Utils::parseLine(const std::string& line)
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
double Utils::cost(const std::vector<Data>& i_data, const double a, const double b)
{
    return (1.0 / (2.0 * i_data.size())) * 
        std::accumulate(i_data.cbegin(), i_data.cend(), double(0),
            [&](const auto init, const auto d)
                { return init + std::pow(h(d.x, a, b) - d.y, 2); } );
}

double Utils::costDerivativeA(const std::vector<Data>& i_data, const Result& i_result)
{
    return (1.0 / i_data.size()) *
        std::accumulate(i_data.cbegin(), i_data.cend(), double(0),
            [&](const auto init, const auto d)
                { return init + h(d.x, i_result.a, i_result.b) - d.y; } );
}

double Utils::constDerivativeB(const std::vector<Data>& i_data, const Result& i_result)
{
    return (1.0 / i_data.size()) *
        std::accumulate(i_data.cbegin(), i_data.cend(), double(0),
            [&](const auto init, const auto d)
                { return init + (h(d.x, i_result.a, i_result.b) - d.y) * d.x; } );
}

std::optional<Utils::Result> Utils::update(const std::vector<Utils::Data>& i_data,
                                            const Result& i_result, const double i_learning_rate)
{
    if (std::isinf(i_result.a) || std::isinf(i_result.b))
        return {};
    if (std::isnan(i_result.a) || std::isnan(i_result.b))
        return {};
    const auto a = newA(i_data, i_result, i_learning_rate);
    const auto b = newB(i_data, i_result, i_learning_rate);
    if (eq(a, i_result.a) && eq(b, i_result.b))
        return {};
    return Result{a, b};
}

bool Utils::eq(const double a, const double b)
{
    return abs(a - b) < e || abs(b - a) < e;
}

double Utils::abs(const double a)
{
    return a < 0.0 ? -a : a;
}

Utils::Normaliser::Normaliser(std::vector<Data> i_data)
    : m_data(std::move(i_data))
    , m_coefficient(avg(max(m_data, [](const auto& d){ return d.x;}), max(m_data, [](const auto& d){ return d.x;})))
{}

std::vector<Utils::Data> Utils::Normaliser::normalise() const
{
    auto result = std::vector<Data>();
    for (const auto& d : m_data)
        result.emplace_back(Data{d.x / m_coefficient, d.y / m_coefficient});
    return result;
}

Utils::Result Utils::Normaliser::unnormalise(const Result& i_result) const
{
    return { i_result.a * m_coefficient, i_result.b };
}
