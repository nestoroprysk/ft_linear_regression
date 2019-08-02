#pragma once

#include <string>
#include <vector>
#include <optional>

namespace Utils{

static constexpr auto e = 0.00001;

struct Data{ double x = 0; double y = 0; };
struct Result{ double a = 0; double b = 0; };

std::string getFullPathToBuildDir(const std::string& i_file_name);
std::string getFullPathToVisualizeDir(const std::string& i_file_name);
std::string getFullPathToRootDir(const std::string& i_file_name);
std::string getFullPathToDataDir(const std::string& i_file_name);
std::pair<double, double> getCoefficients();
std::string getDataFileFullName();
std::string getLineFileFullName();
void save(const Result& i_result);
void save(const std::string& i_file_name);

std::vector<Data> parse(const std::string& i_file_name);
Utils::Data parseLine(const std::string& line);

double h(const double x, const double a, const double b);
double cost(const std::vector<Data>& i_data, const double a, const double b);
double costDerivativeA(const std::vector<Data>& i_data, const Result& i_result);
double constDerivativeB(const std::vector<Data>& i_data, const Result& i_result);
std::optional<Result> update(const std::vector<Data>& i_data,
                                const Result& i_result, const double i_learning_rate);

bool eq(const double a, const double b);
double abs(const double a);

std::vector<Data> normalise(const std::vector<Data>& i_data);
double normalise(const std::vector<Data>& i_prior_data, const double x);
double unnormalise(const std::vector<Data>& i_prior_data, const double y);

double assess(const double x);

double max(const std::vector<Data>& i_data, const std::function<double(const Data&)>& i_get);
double min(const std::vector<Data>& i_data, const std::function<double(const Data&)>& i_get);

double precision(const double a, const double b);

}
