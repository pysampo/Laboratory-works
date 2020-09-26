#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

void DisplaySymbols(std::string, int*, int);
std::vector<int> Search(std::string str, std::string subStr, int* ArrayOfSymbols);
void DoArray(std::string, int*, int);
const int N = 256;

int main(void)
{

    std::string str;
    std::string subStr;
    std::cout << "First string: " << std::endl;
    getline(std::cin, str);
    std::cout << "Finding string: " << std::endl;
    getline(std::cin, subStr);

    int len = subStr.length();
    int ArrayOfSymbols[N];

    std::fill_n(ArrayOfSymbols, N, len);

    DoArray(subStr, ArrayOfSymbols, len);
    DisplaySymbols(subStr, ArrayOfSymbols, len);

    std::vector<int> indexes = Search(str,subStr,ArrayOfSymbols);
    
    if (indexes.empty())
        std::cout << "Nothing was found!" << std::endl;
    else
    {
       for (int i  = 0; i < indexes.size(); ++i)
            std::cout << indexes[i] << " ";         
        std::cout << std::endl;
    }

    
    return 0;
}

void DisplaySymbols(std::string subStr, int* ArrayOfSymbols, int len)
{
    for (int i = 0; i < len; ++i)
    {
       std::cout << subStr[i] << " = "
        <<  ArrayOfSymbols[subStr[i]]  << std::endl;
    }
}

void DoArray(std::string subStr, int* ArrayOfSymbols, int len)
{
    bool a;

    for (int i = 0; i < len - 1; ++i)
    {
        if (subStr[i] == subStr[len])
        {
            ArrayOfSymbols[subStr[len]] = len - 1 - i;
            a = false;
        }
        ArrayOfSymbols[subStr[i]] = len - 1 - i;
    }

    if (a)
        ArrayOfSymbols[subStr[len]] = len;

}

std::vector<int> Search(std::string str, std::string subStr, int* ArrayOfSymbols)
{

    int n = str.length();
    int m = subStr.length();
    
    int i, j, k;

    std::vector<int> indexes;
    
    for (i = m - 1; i < n; i += ArrayOfSymbols[str[i]])
    {
        for (k = i, j = m - 1; j >= 0 && str[k] == subStr[j] ; j--, k--)
        {

            if (j == 0) {
               
                indexes.push_back(i+1-m);
            }
        }
    }
    return indexes;
}
    
