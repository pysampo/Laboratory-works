#include <iostream>
#include <fstream>
#include <chrono>
#include <iterator>

void FillArray(int* array, int Range);
void DisplayArray(int* array, int Range);
void swap(int&, int&);
bool isSort(int* a, int Range);
void CheckList();
int maxBIT(int *a, int Range);
double radixSort(int*a, int Range); int solve(int*a, int l, int r, int max);
int minBIT(int*a, int Range);
int solveNegative(int*a, int r, int max);
void radixRecursion(int* a, int left, int right, int k);
const int INT_BITS = sizeof(int) * 8;

int main()
{
    CheckList();
    // Разновидность обменной сортировки
    // 8, 7, 18, 64, 1, 4, 25
    // ищем старший значащий бит у  чисел
    // * в левую часть переносятся все числа, для которых значение в разряде k равняется 0, в правую часть: k = 1
    // далее, повторяем алгоритм * для двух фрагментов с k - 1, пока k >= 0 и l < r                                           
    // 8 -> 0001000  0001000   0001000    0001000     0001000   0001000    0001000i  0000100   0000100 (0 > r(-1)) 0000100 !  0000100 !  0000100 !4 
    // 7 -> 0000111  0000111   0000111    0000111     0000111   0000111    0000111   0000111j  0000111             0000111 !  0000111 !  0000111 !7
    // 18-> 0010010  0010010   0010010    0010010     0010010i  0000100j   0000100j  0001000i      ^               0001000 !  0001000 !  0001000 !8       
    // 64-> 1000000i 0011001   0011001    0011001     0011001   0011001i      ^                                    0011001    0010010 !  0010010 !18               
    // 65-> 1000001  1000001i  0000100j   0000100j    0000100j  0010010                                            0010010    0011001 !  0011001 !25
    // 4->  0000100  0000100j  1000001i    ^     i      ^                                                             ^       1000001    1000000 !64
    // 25-> 0011001j 1000000   1000000                                                                                        1000000    1000001 !65
    //      ^                                                                                                                  ^ 
    //
}

void swap(int& left, int& right){
    int temp = right;
    right = left;
    left = temp;
}

void radixRecursion(int* a, int left, int right, int k)
{
    if (left < right && k >= 0) {
        int index = solve(a, left, right, k);
        radixRecursion(a, left, index, k-1);
        radixRecursion(a, index + 1, right, k-1);
    }
}

double radixSort(int*a, int Range)
{   //radixsort with negative numbers
    if(!isSort(a, Range)) {
       std::cout << "Not sorted yet" << std::endl;
       auto t2 = std::chrono::high_resolution_clock::now();
       int maxbit = maxBIT(a, Range);
       int index_for_negative = solveNegative(a,Range-1, INT_BITS - 1); //change positions of negative & positive numbers. Negative are ahead
       //return index of last negative integer
       radixRecursion(a, 0, index_for_negative, INT_BITS - 2); //send part of negative numbers & sort it with radix
       //can use minBIT(function to find the highest bit of minimum value) for the 3rd argument, but probably many chances that it'll be the 30st bit
       radixRecursion(a, index_for_negative + 1, Range-1, maxbit); //send part of positive numbers & sort it with radix
       auto t1 = std::chrono::high_resolution_clock::now();
       std::chrono::duration<double,std::micro> elapsed = t1 - t2;
       std::cout << elapsed.count() / 1000000 << " sec. " << std::endl;
       std::cout << "Sorted :" << isSort(a, Range) << std::endl;
       return elapsed.count(); 
   }
   std::cout << "Already sorted" << std::endl;
   return 0;
}

int maxBIT(int *a, int Range)
{
    int weight = 0;
    int max = a[0];
    for (int i = 1; i < Range; ++i)
    {
        if (max <a[i])
        max = a[i];
    }
    while (max) {
        ++weight;
        max >>= 1;
    }
    return weight;
}
int solve(int*a, int l, int r, int max)
{
    int mask = 1;
    mask <<= max;
    int i = l;
    int j = r;
    while (i <= j) {
        while (i <= j && ((mask & a[i]) == 0))++i;
        while (i <= j && ((mask & a[j]))) --j;
        if (i < j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    return j;
}


int solveNegative(int*a, int r, int max)
{
    int i = 0;
    int j = r;
    int mask = 1;
    mask <<= max;
    while (i <= j) {
        while (i <= j && ((mask & a[i])))++i; //only these two line differ from solve function
        while (i <= j && ((mask & a[j]))== 0) --j;
        if (i < j) {
            swap(a[i], a[j]);
            ++i;
            --j;
        }
    }
    return j;
}

bool isSort(int* array, int Range)
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
        array[i] = -50000 + rand() %100000;
}
void CheckList()
{
    int Range;
    std::cin >> Range;
    int* a = new int[Range];
    for (int i = 0; i < Range; ++i)
        std::cin >> a[i];
    DisplayArray(a, Range);
    radixSort(a,Range);
    DisplayArray(a,Range);
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
    out.open("Res_for_radix.txt");
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

        sum += radixSort(array, Range);
        sum += radixSort(array_1, Range);
        sum += radixSort(array_2, Range);

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
    sum += radixSort(a, Range);
    delete [] a;
    std::cout << sum << std::endl;
    */
}
int minBIT(int* a, int Range){

    int min = a[0];
    for (int i = 0; i < Range; ++i) 
    {
        if (min > a[i])
            min = a[i];
    }
    signed mask = 1;
    min &= ~(mask << 31);
    int weight = 0;
    while (min)
    {
        ++weight;
        min >>= 1;
        
    } 
    return weight;
}
void DisplayArray(int* array, int Range)
{
    for (int i = 0; i < Range; ++i)
        std::cout << array[i] << "  ";
    std::cout << std::endl;
}
