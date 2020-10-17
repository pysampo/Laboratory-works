#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono> 
#include <vector>
#include <algorithm>

void Shell_Sort_basedbyKnuth(int* array, const int Range);
void Shell_Sort(int* array, const int Range);
void Insertion_Sort(int* array, const int Range);
void FillArray(int* array, const int Range);
void DisplayArray(int* array, const int Range);
void Shell_Sort_basedOnPratt(int* array, const int Range);
int FillArrayWithfile(int* array, int* array1, int* array2, int* array3,int* array4,const int Range);
int is_sorted(int* array, const int Range);
void Shell_Sort_1(int array[], int size);     
void Insertion_Sort(int* array, int Range, const std::vector<int> vStep);
void Shell_Sort_basedbySedgewick(int* array, const int Range);
void Shell_Sort_Tokuda(int* array, const int Range);


int main(void)
{
    int Range;
    for (int i = 0; i < 9; ++i)
    {
        std::cout << "Enter your range: ";
        std::cin >> Range;
        int* array = new int[Range];
        int* array1= new int[Range];
        int* array2= new int[Range];
        int* array3= new int[Range];
        int* array4 = new int[Range];
        /*
        for (int i = 0; i < Range; ++i)
        {
        	array[i] = rand() % 10;
        	array4[i]=array1[i] = array2[i] = array3[i] = array[i];
        }*/

       FillArrayWithfile(array,array1,array2,array3,array4,Range);

	    Shell_Sort_basedbyKnuth(array1,Range);
        std::cout << is_sorted(array1, Range)<< std::endl;
        delete [] array1;

        Shell_Sort_basedbySedgewick(array2,Range);
        std::cout << is_sorted(array2, Range)<< std::endl;
        delete [] array2;

        Shell_Sort_basedOnPratt(array3,Range);
        std::cout << is_sorted(array3, Range)<< std::endl;
        delete [] array3;        
        
        Shell_Sort_Tokuda(array4, Range);
        std::cout << is_sorted(array4, Range)<< std::endl;
        delete [] array4;	
	
        Shell_Sort(array, Range);
        std::cout << is_sorted(array, Range)<< std::endl;
        delete [] array;
    }

    return 0;
}

int FillArrayWithfile(int* array, int* array1, int* array2, int* array3, int* array4, const int Range)
{
    std::ifstream input;
    std::string str;
    std::cin >> str;
    input.open(str);
    if(!input.is_open()) {
            std::cerr << "Error." << std::endl;
            return -1;
    }
    for (int i = 0; i < Range; ++i)
    {
        input >> array[i];
        array1[i]=array2[i]=array3[i]=array4[i]=array[i];
    }
    input.close();
    return 1;
}

void Shell_Sort(int* array, const int Range)
{
    std::vector<int> vStep;
    std::cout << "Shell Step" << std::endl;
    for (int step = Range / 2;  step > 0; step /= 2) 
        vStep.push_back(step);
    std::reverse(vStep.begin(),vStep.end());
    Insertion_Sort(array, Range, vStep);
}
void Shell_Sort_basedOnPratt(int* array, const int Range)
{
    std::vector<int> vStep;
    std::cout << "Pratt Step" << std::endl;
    for(int step = 1, t = 1; step < Range/3; t++, step = (pow(3,t) - 1) / 2)
        vStep.push_back(step);
    Insertion_Sort(array, Range, vStep);
}
void Shell_Sort_basedbySedgewick(int* array, const int Range)
{
    std::vector<int> vStep;
    std::cout << "Sedgewick Step" << std::endl;
    for (int step = 1,t = 1; 3 * step < Range; t++,
        step = ((t % 2 == 0) ? (9*pow(2,t) - 9 * pow(2, t/2) + 1) : (8 * pow(2,t)- 6*pow(2,(t+1)/2) + 1)))
        vStep.push_back(step);
    Insertion_Sort(array, Range, vStep);
}
void Shell_Sort_basedbyKnuth(int* array, const int Range)
{
    std::vector<int> vStep;
    std::cout << "Knuth Step" << std::endl;
    for (int step = 1;  step < Range; step = 3*step+1) 
        vStep.push_back(step);
    Insertion_Sort(array, Range, vStep);
}
void Shell_Sort_Tokuda(int* array, const int Range)
{
    std::vector<int> vStep;
    std::cout << "Tokuda Step" << std::endl;
    for (int step = 1, t = 1; step < Range; step = (round((9*round(pow(9,t)/pow(4,t))-4)/5)), t++)
        vStep.push_back(step);
    Insertion_Sort(array, Range, vStep);
}

void FillArray(int* array, const int Range)
{
    srand(time(NULL));
    for (int i = 0; i < Range; ++i)
        array[i] = rand() % 10000;
}

void DisplayArray(int* array, const int Range)
{
    for (int i = 0; i < Range; ++i)
        std::cout << array[i] << "  ";
    std::cout << std::endl;
}

int is_sorted(int* array, const int Range)
{
    for(int i = 0; i < Range-1; ++i)
        if (array[i] > array[i+1])
            return 0;
    return 1;
}


void Insertion_Sort(int* array, int Range, const std::vector<int> vStep)
{
    int value, temp, j;
    int vSize = vStep.size();

    auto t2 = std::chrono::high_resolution_clock::now();
    while(vSize > 0)
    {
        value = vStep[--vSize];
        for(int i = value; i < Range; ++i)
        {
        	temp = array[i];
            for(j = i-value; j >= 0  && array[j] > temp; j-= value)
                array[j+value]= array[j];
            array[j+value] = temp;
        }
     
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double,std::micro> elapsed = t1 - t2;
    std::cout <<"Seconds: "  << elapsed.count() / 1000000 << std::endl;
    std::cout <<"Microseconds: "  <<elapsed.count() << std::endl;
}

