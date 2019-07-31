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

static constexpr auto e = 0.00001;
const auto eq = [](const auto a, const auto b)
{ return std::abs(a - b) < e || std::abs(b - a) < e;
};

const auto h = [](const Mileage m, const auto a, const auto b) -> Cost
{ return a + b * m; };

// Unused: derA and derB are the derivitives of the function
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

double g_learning_rate = 0.1;

const auto derA = []
{ return (1.0 / g_data.size()) *
  std::accumulate(g_data.cbegin(), g_data.cend(), double(0),
  [&](const auto init, const auto d)
  { return init + h(d.x, g_result.a, g_result.b) - d.y; } );
};

const auto derB = []
{ return (1.0 / g_data.size()) *
  std::accumulate(g_data.cbegin(), g_data.cend(), double(0),
  [&](const auto init, const auto d)
  { return init + (h(d.x, g_result.a, g_result.b) - d.y) * d.x; } );
};

const auto newA = []
{ return g_result.a - g_learning_rate * derA();
};

const auto newB = []
{ return g_result.b - g_learning_rate * derB();
};

const auto update = []
{ const auto temp_a = newA();
  const auto temp_b = newB();
  if (eq(temp_a, g_result.a) && eq(temp_b, g_result.b))
    return false;
  g_result.a = temp_a;
  g_result.b = temp_b;
  return true;
};

int main()
{ auto d = std::ifstream("data.txt");
  {std::string s; std::getline(d, s);}
  for (std::string line; std::getline(d, line);)
    g_data.emplace_back(parse(line));
  while (update());
  auto o = std::ofstream("line.txt");
  o << unnormalize(g_result.a) << ',' << g_result.b << std::endl;
}