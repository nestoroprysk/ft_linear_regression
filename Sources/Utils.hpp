#pragma once

#include <string>
#include <vector>
#include <optional>

using List = std::vector<double>;
using Pair = std::pair<double, double>;

namespace Utils{

// static consts
static constexpr auto e = 0.00001;

// global files manipulators
std::string getFullPathToBuildDir(const std::string& i_file_name);
std::string getFullPathToVisualizeDir(const std::string& i_file_name);
std::string getFullPathToRootDir(const std::string& i_file_name);
std::string getFullPathToDataDir(const std::string& i_file_name);
Pair getCoefficients();
std::string getDataFileFullName();
std::string getLineFileFullName();
void save(const Pair& i_result);
void save(const std::string& i_file_name);

// parsers
std::pair<List, List> parse(const std::string& i_file_name);
Pair parseLine(const std::string& line);

// linear regression helpers
double h(const double x, const double a, const double b);
double cost(const List& i_xs, const List& i_ys, const double a, const double b);
double costDerivativeA(const List& i_xs, const List& i_ys,const Pair& i_result);
double constDerivativeB(const List& i_xs, const List& i_ys, const Pair& i_result);
std::optional<Pair> update(const List& i_xs, const List& i_ys,
        const Pair& i_result, const double i_learning_rate);

// functions which use global files
double assess(const double x);
double precision(const double a, const double b);

// general functions
bool eq(const double a, const double b);
double abs(const double a);
double max(const List& i_data);
double min(const List& i_data);

// normalisers
List normalise(const List& i_data);
double normalise(const List& i_prior_data, const double n);
double unnormalise(const List& i_prior_data, const double n);

}
