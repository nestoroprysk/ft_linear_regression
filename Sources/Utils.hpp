#pragma once

#include <string>
#include <vector>
#include <optional>

namespace Utils{

static constexpr auto e = 0.00001;

std::string getFullPathToBuildDir(const std::string& i_file_name);
std::string getFullPathToVisualizeDir(const std::string& i_file_name);
std::string getFullPathToRootDir(const std::string& i_file_name);
std::string getFullPathToDataDir(const std::string& i_file_name);
std::pair<double, double> getCoefficients();
std::string getDataFileFullName();
std::string getLineFileFullName();
void save(const std::pair<double, double>& i_result);
void save(const std::string& i_file_name);

std::pair<std::vector<double>, std::vector<double>> parse(const std::string& i_file_name);
std::pair<double, double> parseLine(const std::string& line);

double h(const double x, const double a, const double b);
double cost(const std::vector<double>& i_xs, const std::vector<double>& i_ys, const double a, const double b);
double costDerivativeA(const std::vector<double>& i_xs, const std::vector<double>& i_ys, const std::pair<double, double>& i_result);
double constDerivativeB(const std::vector<double>& i_xs, const std::vector<double>& i_ys, const std::pair<double, double>& i_result);
std::optional<std::pair<double, double>> update(const std::vector<double>& i_xs, const std::vector<double>& i_ys,
                                const std::pair<double, double>& i_result, const double i_learning_rate);

bool eq(const double a, const double b);
double abs(const double a);

std::vector<double> normalise(const std::vector<double>& i_data);
double normalise(const std::vector<double>& i_prior_data, const double n);
double unnormalise(const std::vector<double>& i_prior_data, const double n);

double assess(const double x);

double max(const std::vector<double>& i_data);
double min(const std::vector<double>& i_data);

double precision(const double a, const double b);

}
