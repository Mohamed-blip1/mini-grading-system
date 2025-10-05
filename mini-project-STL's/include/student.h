// student.h
#pragma once
#include <iostream>
#include <iomanip>
#include <random>

struct Student
{
    std::string name_;
    int score_;

    friend std::ostream &operator<<(std::ostream &os,
                                    const Student &s) noexcept
    {
        os << std::setw(10) << std::right << s.name_
           << " : " << std::setw(3) << s.score_;
        return os;
    }
};

constexpr int min_score = 0;
constexpr int max_score = 100;

struct Random
{
    std::mt19937 gen_{
        std::random_device{}()};

    std::uniform_int_distribution<> distrib_{
        min_score, max_score};

    int random_score() noexcept { return distrib_(gen_); }
};
