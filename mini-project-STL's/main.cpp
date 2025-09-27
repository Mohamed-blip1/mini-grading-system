#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>
#include <chrono>
#include <random>

struct Student
{
    std::string name_;
    int score_;

    friend std::ostream &operator<<(std::ostream &os,
                                    const Student &student)
    {
        os << std::setw(10) << std::right << student.name_
           << " : " << std::setw(3) << student.score_;
        return os;
    }
};

struct Time
{
    using steady_clock = std::chrono::steady_clock;
    using duration = std::chrono::duration<double, std::micro>;
    std::string name_;
    steady_clock::time_point tp_;

    Time(const std::string &st)
    {
        name_ = st;
        tp_ = steady_clock::now();
    };

    ~Time()
    {
        auto elapsed = steady_clock::now();
        std::cout << "time of '" << name_ << "': "
                  << duration(elapsed - tp_).count()
                  << "μs\n";
    };
};

constexpr int min_srore = 0;
constexpr int max_srore = 100;

struct Random
{
    std::mt19937 gen_{
        std::random_device{}()};

    std::uniform_int_distribution<> distrib_{
        min_srore, max_srore};

    Random() = default;

    int random_score() { return distrib_(gen_); }

    ~Random() = default;
};

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
    {
        constexpr int students_number = 100;

        Random ran;
        for (size_t i = 0; i < students_number; ++i)
        {
            students_.emplace_back("s" + std::to_string(i),
                                   ran.random_score());
        }
    }

    // Adding +10 bonus points to every student
    std::vector<Student> students_after_bonus_;
    {
        constexpr int bonus = 10;
        constexpr int cap_score = 100;

        Time time("transform");
        std::transform(students_.begin(), students_.end(),
                       std::back_inserter(students_after_bonus_),

                       [cap_score](Student student)
                       {
                           student.score_ =
                               std::min(student.score_ + bonus, cap_score);
                           return student;
                       });
    }

    // Adding +1 pointe to Alice
    {
        Time time("find_if");
        auto it = std::find_if(students_after_bonus_.begin(),
                               students_after_bonus_.end(),
                               [](const Student &student)
                               { return (student.name_ == "Alice"); });
        it->score_ += 1; // +1 point to Alice.
    }

    // Compute the class acerage

    double average;
    {
        int init = 0;
        Time time("accumulate");
        int total = std::accumulate(students_after_bonus_.begin(),
                                    students_after_bonus_.end(),
                                    init, [](int i, const Student &student)
                                    { return i + student.score_; });
        average = static_cast<double>(total) / students_after_bonus_.size();
    }

    std::vector<Student> above_average_students_;
    std::vector<Student> below_average_students_;
    {
        Time time("partition_copy");
        std::partition_copy(students_after_bonus_.begin(),
                            students_after_bonus_.end(),
                            std::back_inserter(above_average_students_),
                            std::back_inserter(below_average_students_),
                            [average](const Student &student)
                            { return student.score_ > average; });
    }

    // Sort
    auto sort_the = [](std::vector<Student> &vec_)
    {
        std::sort(vec_.begin(),
                  vec_.end(),
                  [](const Student &a, const Student &b)
                  { return a.score_ > b.score_; });
    };
    {
        Time time("sort");
        sort_the(above_average_students_);
        sort_the(below_average_students_);
    }

    // Partition
    std::vector<Student>::iterator mid;
    {
        Time time("stable_partition");
        mid = std::stable_partition(above_average_students_.begin(),
                                    above_average_students_.end(),
                                    [](const Student &student)
                                    { return student.score_ > 70; });
    }

    auto print_students =
        [](std::vector<Student>::iterator begin_,
           std::vector<Student>::iterator end_,
           const std::string &ui)
    {
        std::cout
            << ui << "\n";
        for (auto it = begin_; it != end_; ++it)
            std::cout << *it << "\n";
    };

    print_students(above_average_students_.begin(),
                   mid,
                   "Passing students:");
    std::cout << "\n";

    print_students(mid,
                   above_average_students_.end(),
                   "Borderline students:");
    std::cout << "\n";

    print_students(below_average_students_.begin(),
                   below_average_students_.end(),
                   "below average students:");
    std::cout << "\n";

    std::cout << "Class average: "
              << average << "\n";

    return 0;
}