#pragma once

#include <string>
#include <vector>
#include <optional>

namespace Utils{

static constexpr auto e = 0.00001;

struct Data{ double x = 0; double y = 0; };
struct Result{ double a = 0; double b = 0; };

void printSmiley();
std::string getFullPathToBuildDir(const std::string& i_file_name);
std::string getFullPathToVisualizeDir(const std::string& i_file_name);
std::string getFullPathToRootDir(const std::string& i_file_name);
bool eq(const double a, const double b);
double h(const double x, const double a, const double b);
double cost(const std::vector<Data>& i_data, const double a, const double b);
double costDerivativeA(const std::vector<Data>& i_data, const Result& i_result);
double constDerivativeB(const std::vector<Data>& i_data, const Result& i_result);
std::vector<Data> parse(const std::string& i_file_name);
std::optional<Result> update(const std::vector<Data>& i_data,
                                const Result& i_result, const double i_learning_rate);
double abs(const double a);
void save(const Result& i_result);

class Normaliser
{
public:
    Normaliser(std::vector<Data> i_data);
    std::vector<Data> normalise() const;
    Result unnormalise(const Result& i_result) const;
private:
    const std::vector<Data> m_data;
    const double m_coefficient;
};

}
