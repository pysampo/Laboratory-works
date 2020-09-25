#include <iostream>
#include <algorithm>
#include <cstring>
void DisplayArray(std::string, int*, int);
void Search(std::string str1, std::string str2, int* p);
void Array(std::string, int*, int);
const int N = 256;
int main(void)
{
    std::string str1;
    std::string str2;
    std::cout << "First string: " << std::endl;
    getline(std::cin, str1);
    std::cout << "Find search: " << std::endl;
    getline(std::cin, str2);
    int len = str2.length();
    int p[N];
    std::fill_n(p,N,len);
    Array(str2, p, len);
    DisplayArray(str2,p,len);
    Search(str1,str2,p);
    return 0;
}
void DisplayArray(std::string str2, int* p, int len)
{
    for (int i = 0; i < len; ++i)
    {
       std::cout << str2[i] << " = "
        <<  p[str2[i]]  << std::endl;
    }
}
void Search(std::string str1, std::string str2, int* p)
{
    int n = str1.length();
    int m = str2.length();
    int i,j,k;
    bool b = true;
    for (i = m - 1; i < n; i += p[str1[i]])
    {
        for (k = i, j = m - 1; j>=0 && str1[k] == str2[j] ; j--, k--)
        {
            if (j == 0) {
                b = false;
                std::cout << "Index is "  << i+1-m << std::endl;
            }
        }
    }
    if (b)
        std::cout << "Not found\n";
}
void Array(std::string str2, int* p, int len)
{
    bool a;
    for (int i = 0; i < len - 1; ++i)
    {
        if (str2[i] == str2[len])
        {
            p[str2[len]] = len - 1 - i;
            a = false;
        }
        p[str2[i]] = len - 1 - i;
    }
    if (a)
        p[str2[len]] = len;
}
