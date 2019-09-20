#pragma once
#include <vector>
typedef std::vector<int>* sortArray;

// √∞≈›
void bubble_sort(sortArray v);
//øÏ≈≈
void q_sort(sortArray v, int start, int end);

// ÷±Ω”≤Â»Î≈≈–Ú
void insert_sort(sortArray v);
// œ£∂˚≈≈–Ú
void shell_sort(sortArray v,int dk);

// ∂—≈≈–Ú
void heap_sort(sortArray v);
// —°‘Ò≈≈–Ú
void select_sort(sortArray v);
