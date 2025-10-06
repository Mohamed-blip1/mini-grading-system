#pragma once
// student.h
#include <iostream>
#include <iomanip>
#include <random>

struct Student
{
    std::string name_;
    int score_;

    friend std::ostream &operator<<(std::ostream &os,
                                    const Student &s) noexcept;
};

constexpr int min_score = 0;
constexpr int max_score = 100;

struct Random
{
    std::mt19937 gen_{
        std::random_device{}()};

    std::uniform_int_distribution<> distrib_{
        min_score, max_score};

    int random_score() noexcept;
};
