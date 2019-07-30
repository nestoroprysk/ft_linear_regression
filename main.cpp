#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <numeric>

struct Result{ double a = 0; double b = 0; };

struct Data{ double x = 0; double y = 0; };

static Result g_result;
static std::vector<Data> g_data;

using Mileage = double;
using Cost = double;

const auto h = [](const Mileage m, const auto a, const auto b) -> Cost
{ return a + b * m; };

const auto courseCostFunction = [](const auto a, const auto b) -> Cost
{ return (1.0 / (2.0 * g_data.size())) * 
  std::accumulate(g_data.cbegin(), g_data.cend(), double(0),
  [&](const auto init, const auto d)
  { return init + std::pow(h(d.x, a, b) - d.y, 2); } );
};

// TODO: add norm finding strategy
static constexpr auto g_norm = 100000.0;
const auto normalize = [](const double n){ return n / g_norm; };
const auto unnormalize = [](const double n){ return n * g_norm; };

Data parse(const std::string& line)
{ return { normalize(std::stod(std::string(line.cbegin(),
  std::find(line.cbegin(), line.cend(), ',')))),
  normalize(std::stod(std::string(std::next(std::find(line.cbegin(),
  line.cend(), ',')), line.cend()))) };
}

double g_a = 0;
double g_b = 0;

const auto minX = []{return std::accumulate(g_data.cbegin(), g_data.cend(), double(0),
[](const auto init, const auto& d){ return std::min(init, unnormalize(d.x)); });};

const auto maxX = []{return std::accumulate(g_data.cbegin(), g_data.cend(), double(0),
[](const auto init, const auto& d){ return std::max(init, unnormalize(d.x)); });};

const auto minY = []{return std::accumulate(g_data.cbegin(), g_data.cend(), double(0),
[](const auto init, const auto& d){ return std::min(init, unnormalize(d.y)); });};

const auto maxY = []{return std::accumulate(g_data.cbegin(), g_data.cend(), double(0),
[](const auto init, const auto& d){ return std::max(init, unnormalize(d.y)); });};

const auto update = []{};

int main()
{ auto d = std::ifstream("data.txt");
  {std::string s; std::getline(d, s);}
  for (std::string line; std::getline(d, line);)
    g_data.emplace_back(parse(line));
  const auto nbIterations = 0;
  auto minCost = std::numeric_limits<double>::max();
  for (auto i = 0; i < nbIterations; ++i)
  { const auto c = courseCostFunction(g_a, g_b);
    g_result = c < minCost ? Result{ g_a, g_b } : g_result;
    minCost = std::min(minCost, c);
    update();
  }
  auto o = std::ofstream("line.txt");
  o << g_result.a << ',' << g_result.b << std::endl;
  return 0;
}
