// main.cpp
#include "debug_time.h"
#include <algorithm>
#include "student.h"
#include <iostream>
#include <numeric>
#include <vector>
#include <chrono>

constexpr int point = 1;
constexpr int bonus = 10;
constexpr int cap_Borderline = 80;
constexpr int students_number = 100;
constexpr int bottom_Borderline = 50;

int main()
{
    std::cout << "\n";

    // Feed with Data{
    std::vector<Student> students_{
        {"Alice", 72},
        {"Bob", 45},
        {"Charlie", 95},
        {"Diana", 60},
        {"Eve", 30}};

    // Add 100 random students
    Random ran;
    for (size_t i = 1; i <= students_number; ++i)
        students_.emplace_back("s" + std::to_string(i),
                               ran.random_score());

    // Add +10 bonus (capped to 100)
    std::vector<Student> students_after_bonus_;
    {

#ifdef DEBUG
        Time time("transform");
#endif
        std::transform(students_.begin(), students_.end(),
                       std::back_inserter(students_after_bonus_),
                       [](Student s)
                       {
                           s.score_ =
                               std::min(s.score_ + bonus, max_score);
                           return s;
                       });
    }

    // Alice +1 point
    {
#ifdef DEBUG
        Time time("find_if");
#endif
        auto it = std::find_if(students_after_bonus_.begin(),
                               students_after_bonus_.end(),
                               [](const Student &s)
                               { return (s.name_ == "Alice"); });
        it->score_ += point;
    }

    // Compute average
    double avg;
    {
#ifdef DEBUG
        Time time("accumulate");
#endif
        int total = std::accumulate(students_after_bonus_.begin(),
                                    students_after_bonus_.end(),
                                    0, [](int n, const Student &s)
                                    { return n + s.score_; });
        avg = static_cast<double>(total) / students_after_bonus_.size();
        std::cout << "Class average: " << avg << "\n\n";
    }

    // Partition above/below average
    std::vector<Student> above;
    std::vector<Student> below;
    {
#ifdef DEBUG
        Time time("partition_copy");
#endif
        std::partition_copy(students_after_bonus_.begin(),
                            students_after_bonus_.end(),
                            std::back_inserter(above),
                            std::back_inserter(below),
                            [avg](const Student &s)
                            { return s.score_ > avg; });
    }

    auto sort_desc = [](std::vector<Student> &vec_)
    {
        std::sort(vec_.begin(),
                  vec_.end(),
                  [](const Student &a, const Student &b)
                  { return a.score_ > b.score_; });
    };
    {
#ifdef DEBUG
        Time time("sort");
#endif
        sort_desc(above);
        sort_desc(below);
    }

    // Remove failing students (<50)
    {
#ifdef DEBUG
        Time time("erase-remove_if:");
#endif
        below.erase(
            std::remove_if(below.begin(),
                           below.end(),
                           [](const Student &s)
                           { return s.score_ < bottom_Borderline; }),
            below.end());
    }

    // Stable partition: top / borderline
    std::vector<Student>::iterator borderline_it;
    {
#ifdef DEBUG
        Time time("stable_partition");
#endif
        borderline_it =
            std::stable_partition(above.begin(),
                                  above.end(),
                                  [](const Student &student)
                                  { return student.score_ > cap_Borderline; });
    }

    // Top 5 at least students
    std::vector<Student> top;
    auto proficient_it = above.begin();
    {
#ifdef DEBUG
        Time time("Top students");
#endif
        for (; proficient_it != borderline_it; ++proficient_it)
            if (top.size() < 5 || proficient_it->score_ == max_score)
                top.emplace_back(*proficient_it);
            else
                break;
    }

    // Combine passing students
    std::vector<Student> passed = above;
    std::copy(below.begin(),
              below.end(),
              std::back_inserter(passed));

    using students_pair_vec = std::vector<std::pair<Student, Student>>;

    students_pair_vec pairs;
    {
        Random ran;
#ifdef DEBUG
        Time time("Shuffle");
#endif
        std::shuffle(passed.begin(),
                     passed.end(), ran.gen_);

        bool solo = passed.size() % 2 != 0;
        Student last{};
        if (solo)
        {
            last = std::move(passed.back());
            passed.pop_back();
        }

        for (size_t i = 0; i < passed.size(); i += 2)
            pairs.emplace_back(passed[i],
                               (passed[i + 1]));

        if (solo)
            pairs.push_back({last, {}});
    }

    auto print_students =
        [](const std::vector<Student> &v,
           const std::string &title)
    {
        std::cout << title << "\n";
        for (const auto &s : v)
            std::cout << s << "\n";
        std::cout << "\n";
    };

    std::cout << "\n";

    std::cout << "Passing students:\n";
    print_students(top, "->Top students:");
    print_students(std::vector<Student>(proficient_it, borderline_it),
                   "->Proficient students:");
    print_students(std::vector<Student>(borderline_it, above.end()),
                   "->Borderline students:");
    print_students(below,
                   "->below avg students:");

    std::cout << "Students groups:\n";
    int n = 1;
    for (auto &[a, b] : pairs)
    {
        std::cout << "#" << n++ << "\n-" << a;
        if (!b.name_.empty())
            std::cout << "\n-" << b;
        std::cout << "\n";
    }

    return 0;
}