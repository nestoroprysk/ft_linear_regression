#include "catch.hpp"

#include <Utils.hpp>

#include <iostream>

//parsers

TEST_CASE("<parseLine><empty>")
{
    const auto test = "";
    REQUIRE_THROWS(Utils::parseLine(test));
}

TEST_CASE("<parseLine><single>")
{
    const auto test = "12.0";
    REQUIRE_THROWS(Utils::parseLine(test));
}

TEST_CASE("<parseLine><valid>")
{
    const auto test = "12.0,13.0";
    REQUIRE_NOTHROW(Utils::parseLine(test));
    const auto [x, y] = Utils::parseLine(test);
    REQUIRE(Utils::eq(x, 12));
    REQUIRE(Utils::eq(y, 13));
}

// linear regression helpers

TEST_CASE("<h>")
{
    REQUIRE(Utils::eq(106, Utils::h(2, 100, 3)));
    REQUIRE(Utils::eq(94, Utils::h(-2, 100, 3)));
}

// linear regression helpers

TEST_CASE("<cost><zero>")
{
    const auto xs = std::vector<double>{0};
    const auto ys = std::vector<double>{0};
    const auto a = 0;
    const auto b = 0;
    REQUIRE(Utils::eq(0, Utils::cost(xs, ys, a, b)));
}

TEST_CASE("<cost><x=y><perfect>")
{
    const auto xs = std::vector<double>{0,1,2,3};
    const auto ys = std::vector<double>{0,1,2,3};
    const auto a = 0;
    const auto b = 1;
    REQUIRE(Utils::eq(0, Utils::cost(xs, ys, a, b)));
}

TEST_CASE("<cost><x=const><perfect>")
{
    const auto xs = std::vector<double>{0,1,2,3};
    const auto ys = std::vector<double>{1,1,1,1};
    const auto a = 1;
    const auto b = 0;
    REQUIRE(Utils::eq(0, Utils::cost(xs, ys, a, b)));
}

TEST_CASE("<cost><x=const><imperfect>")
{
    const auto xs = std::vector<double>{0,1,2,3};
    const auto ys = std::vector<double>{1,1,1,1};
    const auto a = 0;
    const auto b = 0;
    REQUIRE(Utils::eq(0.5, Utils::cost(xs, ys, a, b)));
}

TEST_CASE("<cost><x=const><imperfect><two>")
{
    const auto xs = std::vector<double>{0,1,2,3};
    const auto ys = std::vector<double>{2,2,2,2};
    const auto a = 0;
    const auto b = 0;
    REQUIRE(Utils::eq(2, Utils::cost(xs, ys, a, b)));
}

// general functions

TEST_CASE("<eq>")
{
    REQUIRE(Utils::eq(0, 0));
    REQUIRE(Utils::eq(0, 0.000001));
    REQUIRE(!Utils::eq(0, 0.00001));
    REQUIRE(!Utils::eq(0.00001, 0));
}

TEST_CASE("<abs>")
{
    REQUIRE(Utils::eq(1, Utils::abs(1)));
    REQUIRE(Utils::eq(1, Utils::abs(-1)));
    REQUIRE(Utils::eq(0, Utils::abs(0)));
    REQUIRE(Utils::eq(0, Utils::abs(-0)));
}

TEST_CASE("<min>")
{
    REQUIRE(Utils::eq(std::numeric_limits<double>::max(), Utils::min({})));
    REQUIRE(Utils::eq(1, Utils::min({1, 2, 3})));
    REQUIRE(Utils::eq(1, Utils::min({3, 2, 1})));
    REQUIRE(Utils::eq(-2, Utils::min({0, -1, -2})));
    REQUIRE(Utils::eq(-2, Utils::min({-2, -1, 0})));
}

TEST_CASE("<max>")
{
    REQUIRE(Utils::eq(std::numeric_limits<double>::min(), Utils::max({})));
    REQUIRE(Utils::eq(3, Utils::max({1, 2, 3})));
    REQUIRE(Utils::eq(2, Utils::max({2, 1, 0})));
    REQUIRE(Utils::eq(0,  Utils::max({0, -1, -2})));
    REQUIRE(Utils::eq(0, Utils::max({-2, -1, 0})));
}

// normalisers

TEST_CASE("<normalise><list>")
{
    const auto input = List{-1000, 0, 10000, 123123131, 1, 20, -20};
    REQUIRE_NOTHROW(Utils::normalise(input));
    const auto result = Utils::normalise(input);
    REQUIRE(std::all_of(result.cbegin(), result.cend(), [](const auto n){
        return n >= 0 && n <= 1;
    }));
}

TEST_CASE("<normalise><number>")
{
    const auto n = 10;
    const auto input = List{-1000, 0, 10000, 123123131, 1, 20, -20};
    REQUIRE(Utils::eq(n, Utils::unnormalise(input, Utils::normalise(input, n))));
}

TEST_CASE("<normalise><zero>")
{
    const auto n = 0;
    const auto input = List{-1000, 0, 10000, 123123131, 1, 20, -20};
    REQUIRE(Utils::eq(n, Utils::unnormalise(input, Utils::normalise(input, n))));
}

TEST_CASE("<normalise><bigNumber>")
{
    const auto n = 11111111111;
    const auto input = List{-1000, 0, 10000, 123123131, 1, 20, -20};
    REQUIRE(Utils::eq(n, Utils::unnormalise(input, Utils::normalise(input, n))));
}

TEST_CASE("<normalise><smallNumber>")
{
    const auto n = -11111111111;
    const auto input = List{-1000, 0, 10000, 123123131, 1, 20, -20};
    REQUIRE(Utils::eq(n, Utils::unnormalise(input, Utils::normalise(input, n))));
}
