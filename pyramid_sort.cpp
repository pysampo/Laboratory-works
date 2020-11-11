#include <iostream>
#include <fstream>
#include <chrono>
void FillArray(int* array, int Range);
void DisplayArray(int* array, int Range);
bool Is_sort(int* array, int Range);
void Sort_Selection_1(int* array, int Range);
void DownValue(int * array, int i, int Range);
double HeapSort(int * array, int Range);
int result(int Range);

int main(void)
{
    int Range;
    std::cin >> Range;
    int*  array = new int[Range];
    for (int i = 0; i < Range; ++i)
        std::cin >> array[i];
    DisplayArray(array, Range);
    HeapSort(array,Range);
    DisplayArray(array,Range);
    delete [] array;
    return 0;
}
void DownValue(int * array, int i, int Range)
{
    int value = array[i];
    int child;
    while (i <= Range/2-1)
    {
        child = 2 * i + 1;
        if (child + 1 < Range && (array[child] < array[child + 1]))
            ++child;
        if (value >= array[child]) break;
        array[i] = array[child]; 
        i = child;
    }
    array[i] = value;
}

double HeapSort(int * array, int Range)
{
    for (int i = Range/2-1; i >= 0; --i)
        DownValue(array,i, Range);
    int temp;
    auto t2 = std::chrono::high_resolution_clock::now();
    for (int i = Range-1; i > 0; --i)
    {
        temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        DownValue(array, 0, i);
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::micro> elapsed = t1 - t2;
    return elapsed.count();
        
}

bool Is_sort(int* array, int Range)
{
    for (int i = 0; i < Range-1; ++i)
        if (array[i] > array[i + 1])
            return false;
    return true;
}

void Sort_Selection_1(int* a, int Range)
{
    int k;
    int temp;
    for (int i = 0; i < Range - 1; ++i)
    {
        k = i;
        for (int j = i + 1; j < Range; ++j)
            if (a[j] < a[k])
                k = j;
        temp = a[i];
        a[i] = a[k];
        a[k] = temp;
    }
}

void FillArray(int* array, int Range)
{
srand(time(NULL));
for (int i = 0; i < Range; ++i)
    array[i] = rand() % 10000;
}

void DisplayArray(int* array, int Range)
{
    for (int i = 0; i < Range; ++i)
        std::cout << array[i] << "  ";
    std::cout << std::endl;
}
