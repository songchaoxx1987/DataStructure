#pragma once
#include <vector>
typedef std::vector<int>* sortArray;

// ð��
void bubble_sort(sortArray v);
//����
void q_sort(sortArray v, int start, int end);

// ֱ�Ӳ�������
void insert_sort(sortArray v);
// ϣ������
void shell_sort(sortArray v,int dk);

// ������
void heap_sort(sortArray v);
// ѡ������
void select_sort(sortArray v);
