# CT077-3-2-DSTR — Patient Management System (Array Implementation)

![Category](https://img.shields.io/badge/Category-Data%20Structures%20%26%20Algorithms-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)
![Structure](https://img.shields.io/badge/Structure-Custom%20Arrays%20(No%20STL)-green)

A C++ patient management system for a simulated hospital network, built entirely with self-implemented array-based data structures — no STL containers (`vector`, `list`, `array`, etc.) were used. Developed for the CT077-3-2-DSTR (Data Structures) coursework at Asia Pacific University.

---

## 📌 Project Overview

- **Component:** Array-based implementation (1 of 2 required programs)
- **Datasets:** 3 simulated hospital facilities (Facility A, B, C)
- **Core Structures:** Fixed-size array, dynamically resizing array, sorted-on-insert array
- **Sorting Algorithms:** Bubble Sort, Counting Sort, Insertion Sort, Merge Sort
- **Searching Algorithms:** Linear Search, Binary Search (including threshold-based search)
- **Performance Tracking:** Execution time measured via `<chrono>` for all sort/search operations

The system categorizes patients by age group, calculates and compares medical billing costs by care type, and benchmarks sorting/searching performance across three distinct array designs — demonstrating trade-offs between fixed allocation, dynamic resizing, and maintaining sorted order on insertion.
