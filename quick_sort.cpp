#include <iostream>
#include <fstream>
#include <chrono>
#include <iterator>

void FillArray(int* array, int Range);
void DisplayArray(int* array, int Range);
void swap(int&, int&);
void help_sort(int* a, int left, int right);
bool Is_sort(int* a, int Range);
int helpquick(int* a, int left, int right);
void quicksort(int* a, int left, int right);
double special_function(int* a, int Range);

int main()
{
    int Range;
    std::cin >> Range;
    int* a = new int [Range];
    FillArray(a, Range);
    DisplayArray(a, Range);
    quicksort(a,0, Range-1);
    DisplayArray(a, Range);

    /*
    char fileNames[9][100] = {
        "10000_1.txt",
        "10000_2.txt",
        "10000_3.txt" ,
        "100000_1.txt",
        "100000_2.txt",
        "100000_3.txt",
        "1000000_1.txt",
        "1000000_2.txt",
        "1000000_3.txt"
    };
    std::ifstream in;
    std::ofstream out;
    int Range;
    double sum = 0;
    std::string str;
    out.open("Res_for_pyramid.txt");
    for (int i = 0; i < 9; ++i) {
        std::cin >> Range;
        in.open(fileNames[i]);
        if (!in.is_open()) {
                    std::cerr << "Error" << std::endl; break;
        }
        std::cout << fileNames[i] << std::endl;

        int* array = new int[Range];
        int* array_1 = new int[Range];
        int* array_2 = new int[Range];
        for (int i = 0; i < Range; ++i) {
            in >> array[i];
            in >> array_1[i];
            in >> array_2[i];
        }

        sum += special_function(array, Range);
        sum += special_function(array_1, Range);
        sum += special_function(array_2, Range);

        delete [] array_1;
        delete [] array_2;
        delete [] array;
        in.close();
        sum /= 3;
        sum /= 1000000;
        out << sum << std::endl;

        sum = 0;
    }
    out.close();
    std::string str;
    int Range;
    std::cin >> Range;

    std::ifstream in;
    std::cin >> str;
    in.open(str);
    int* a = new int[Range];
    for (int i =0 ; i < Range; ++i)
        in >> a[i];
    double sum = 0;
    sum += special_function(a, Range);
    delete [] a;
    std::cout << sum << std::endl; */
    return 0;
}

double special_function(int* array, int Range)
{
    auto t2 = std::chrono::high_resolution_clock::now();
    quicksort(array, 0, Range-1);
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::micro> elapsed = t1 - t2;
    std::cout << elapsed.count() / 1000000 << " sec. " << std::endl;
    std::cout << "Sorted ? " << Is_sort(array, Range) << std::endl;
    std::cout << std::endl;
    return elapsed.count();
}

void swap(int& left, int& right)
{
    int temp = right;
    right = left;
    left = temp;
}

void quicksort(int* a, int left, int right)
{
    int i = 0; 
    if (left < right) {
        int index = helpquick(a, left, right);
        quicksort(a, left, index-1);
        quicksort(a, index, right);
    }
}

int helpquick(int* a, int left, int right)
{
    int i = left;
    int j = right;
    int pivot = a[(i + j)/2];
    while (i <= j) {
        while (a[i] < pivot)
            ++i;
        while (a[j] > pivot)
            --j;
        if (i <= j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    return i;
}

bool Is_sort(int* array, int Range)
{
    for (int i = 0; i < Range-1; ++i)
        if (array[i] > array[i + 1])
            return false;
    return true;
}

void FillArray(int* array, int Range)
{
    srand(time(NULL));
    for (int i = 0; i < Range; ++i)
        array[i] = rand() % 100 + 1;
}

void DisplayArray(int* array, int Range)
{
    for (int i = 0; i < Range; ++i)
        std::cout << array[i] << "  ";
    std::cout << std::endl;
}
