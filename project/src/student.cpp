// student.cpp
#include "student.h"

std::ostream &operator<<(std::ostream &os,
                                  const Student &s) noexcept
{
    os << std::setw(10) << std::right << s.name_
       << " : " << std::setw(3) << s.score_;
    return os;
}
int Random::random_score() noexcept { return distrib_(gen_); }