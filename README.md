# 🎓 Student Performance Analyzer (STL Practice Project)

This C++ program simulates a class of students and processes their performance using STL algorithms and iterators.
It demonstrates practical use of modern C++ functional-style programming for data transformation and grouping.

---

## 🧩 Features
- Random student score generation using <random>
- Score transformation with bonus points (std::transform)
- Average score computation (std::accumulate)
- Separation of students based on performance (std::partition_copy, std::stable_partition)
- Removal of failing students (erase-remove_if)
- Sorting by score (std::sort)
- Random pairing of students for the next semester (std::shuffle)
- Compact, iterator-based code structure with no raw loops unless necessary
- More in the future (Inshallah/إن شاء الله)-

---

## 📘 Concepts Practiced
- Iterators & STL algorithms
- Lambda expressions
- Random number generation
- Functional decomposition
- Range partitioning and filtering
- Purpose: practicing STL algorithms + iterators.

---

## 🖥️ Example Output
```
Class average: 67.35

->Top students:
     Charlie : 100
         s22 : 100
         s41 : 99
         s83 : 98
         s57 : 97
```

## How to build/run: 

With make file:

```
make
```

Manually:

```
g++ -std=c++20 main.cpp -o main 
```
Then:

```
./main.exe # Windows
./main     # Linux
```
