#include <iostream>
#include <ctime>
#include <climits>
#include <algorithm> 
#include <array>
#include <typeinfo>
#include <cassert>
template <class T> 
class Array
{
private:
	T* array;
	int memory, nElements;
public:
	~Array() {
          delete[] array;
    }

    Array(const Array <T> &);
    Array(const int m_ = 1, const int n_ = 0);
    
    Array<T> & operator += (const Array<T> & tempArray);
    Array<T> & operator += (const T temp);
    
    Array<T> & operator - (const T key);
    Array<T> & operator -= (const int position);

    Array <T>operator + (const Array<T> & tempArray);
    Array<T> operator + (const T integer);
    Array<T> & operator = (const Array<T> & tempArray);
    
    bool operator == (const Array <T> & tempArray);
    bool operator != (const Array <T> & tempArray);
        
    int FindElem(const T key);
    bool DeleteElem(const T key);
    void SortArray();
    void DisplayArray();
    void FillArray();

    bool DeleteIndex(const int position);
    bool InsertIndex(const int position, const T key);
    void ShiftArray(int position, const int count, const int direction = 0);
  
    T & operator[](const int position);
    T FindMax();
    T FindMin(); 

    template <class U>
    friend std::ostream & operator <<(std::ostream &os, const Array<U> & t);
    template <class U>
    friend std::istream & operator >> (std::istream & is, Array<U> & t);
};


template <class T>
bool Array<T>::operator != (const Array<T> & tempArray) {
    if (nElements != tempArray.nElements) {
        return true;
    }
    for (int i = 0; i < nElements; ++i) {
        if (array[i] != tempArray.array[i]) {
            return true;
        }
    }
    return false;
}
template <class T>
bool Array<T>::operator == (const Array<T> & tempArray) {
    if (nElements != tempArray.nElements) {
        return false;
    }
    for (int i = 0; i < nElements; ++i) {
        if (array[i] != tempArray.array[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
std::istream & operator >> (std::istream & is, Array<T> & t)
{
    assert((is >> t.nElements) || (t.nElements < 0));
    delete [] t.array;
    is >> t.memory;
    t.memory = (t.memory <= t.nElements ? (t.nElements == 0 ? 1: t.nElements) : t.memory);
    t.array = new T[t.memory];
   
    t.FillArray();
    return is;
}

template<class T>
Array<T>::Array(const int m_, const int n_)
{
    memory = (m_ == 0 ? 1 : (m_ < 0 ? -m_ : m_));
    nElements = (n_ < 0 ? 0 : n_);
    if (nElements > memory)
    {
        memory = nElements;
    }
    array = new T[memory];
}

template <class T>
std::ostream & operator << (std::ostream &os, const Array<T> &t)
{
    for (int i = 0; i < t.nElements; ++i)
        os << t.array[i] << "  ";
    return os;
}

template <class T>
T Array<T>::FindMax() {
    T max = array[0];
    for (int i = 0; i < nElements; ++i) {
        if (array[i] > max) {
            max = array[i];
        }
    }
    return max;
}

template <class T>
T Array<T>::FindMin() {
    T min = std::numeric_limits<T>::max();
    for (int i = 0; i < nElements; ++i) {
        if (array[i] < min) {
            min = array[i];
        }
    }
    return min;
}

template <class T>
T & Array<T>::operator[](const int position) {
    if (position < 0 && (position + nElements >= 0)) {
        return array[position + nElements];
    }
    if (position < nElements && position >= 0) {
        return array[position];
    }
    assert(false && "Error: index is not right.");
}

template <class T>
bool Array<T>::InsertIndex(const int position, const T key) {
    if (position < 0 || position > nElements) {
        std::cerr << "Error: index is not right! " <<
            std::endl;
        return -1;
    }
    nElements = nElements + 1;
    if (nElements > memory) {
        Array tempArray = *this;
        delete[] array;
        memory = memory + 1;
        array = new T [memory];
        for (int i = 0; i < nElements; ++i)
            array[i] = tempArray.array[i];
    }
    for (int i = nElements - 1; i > position; --i)
        array[i] = array[i - 1];
    array[position] = key;
    return 1;
}

template <class T>
bool Array<T>::DeleteIndex(const int position) {
    if (position < 0 || position > nElements) {
        std::cerr << "Error: index is not right! " <<
            std::endl;
        return -1;
    }
    nElements = nElements - 1;
    for (int i = position; i < nElements; ++i) {
        array[i] = array[i + 1];
    }
    return 1;
}

template <class T>
Array<T> & Array<T>::operator -= (const int position) {
    if (position < 0 || position > nElements) {
        std::cerr << "Error: index is not right! " <<
            std::endl;
        return *this;
    }
    nElements = nElements - 1;
    for (int i = position; i < nElements; ++i) {
        array[i] = array[i + 1];
    }
    return *this;
}

template <class T>
Array<T> & Array<T>::operator - (const T key) {
    for (int i = 0; i < nElements; ++i)
    {
            if (key == array[i]) {
                nElements = nElements - 1;
                for (int j = i; j < nElements; ++j) {
                    array[j] = array[j + 1];
                }
                return 1;
            }
            
    
    }
    std::cerr << "Nothing was found!" << std::endl;
    return *this;
}

template <class T>
void Array<T>::SortArray() {

    int Lt = 0;
    int R = 0;
    int L = nElements - 1;
    int Rt = nElements - 1;
    T b, c;
    while ((R != Rt) && (L != Lt)) {
        R = Rt;
        for (int i = Lt; i < R; i++) {
            if (array[i] > array[i + 1]) {
                b = array[i];
                array[i] = array[i + 1];
                array[i + 1] = b;
                Rt = i;
            }
        }
        if (R != Rt) {
            L = Lt;
            for (int i = Rt; i > L; i--)
                if (array[i] < array[i - 1]) {
                    c = array[i];
                    array[i] = array[i - 1];
                    array[i - 1] = c;
                    Lt = i;
                }
        }
    }
}
template <class T>
bool Array<T>::DeleteElem(const T key) {

    for (int i = 0; i < nElements; ++i)
        if (key == array[i])
        {
            nElements = nElements - 1;
            for (int j = i; j < nElements; ++j)
                array[j] = array[j+1];
            return 1;
        }

    return -1;
}
template <class T>
Array<T> Array<T>::operator + (const T temp) {
    Array tempArray;
    delete [] tempArray.array;
    if (memory == nElements) {
        tempArray.memory = memory;
        tempArray.nElements = nElements;
        tempArray.array = new T [tempArray.memory];
        for (int i = 0; i < nElements; ++i)
            tempArray.array[i] = array[i];

        delete[] array;
        memory = nElements + 1;
        array = new T[memory];
        for (int i = 0; i < nElements; ++i)
            array[i] = tempArray.array[i];
        delete[] tempArray.array;
    }
    tempArray.memory = memory;
    tempArray.array = new T[memory];
    tempArray.nElements = nElements + 1;
    for (int i = 0; i < nElements; ++i) {
        tempArray.array[i] = array[i];
    }
    tempArray.array[tempArray.nElements - 1] = temp;
    return tempArray;
}

template <class T> 
Array<T> & Array<T>::operator += (const T temp) 
{
    Array tempArray;
    delete [] tempArray.array;
    if (memory == nElements) {
        tempArray.memory = memory;
        tempArray.nElements = nElements;
        tempArray.array = new T [tempArray.memory];
        for (int i = 0; i < nElements; ++i)
            tempArray.array[i] = array[i];

        delete[] array;
        memory = nElements + 1;
        array = new T[memory];
        for (int i = 0; i < nElements; ++i)
            array[i] = tempArray.array[i];
        delete[] tempArray.array; //g
    }
    tempArray.memory = memory;
    tempArray.array = new T[tempArray.memory];
    tempArray.nElements = nElements + 1;
    for (int i = 0; i < nElements; ++i) {
        tempArray.array[i] = array[i];
    }
    tempArray.array[tempArray.nElements - 1] = temp;
    *this = tempArray;
    return *this;
}
template <class T>
int Array<T>::FindElem(const T key) {
      for (int i = 0; i < nElements; ++i)
        if (key == array[i])
            return i;
    return -1;
}

template <class T>
Array<T> & Array<T>::operator += (const Array & tempArray)
{   
   Array ted = *this;
   memory = ted.memory + tempArray.memory;
   nElements = ted.nElements + tempArray.nElements;
   delete [] array;
   array = new T [memory];
   for (int i = 0; i < ted.nElements; ++i)
       array[i] = ted.array[i];
   for (int i = ted.nElements, j = 0; i < nElements; ++j, ++i)
      array[i] = tempArray.array[j];
   return *this; 
}

template <class T>
Array <T> Array<T>::operator + (const Array<T> & tempArray)
{
    Array ted(memory+tempArray.memory,nElements+tempArray.nElements);
    for (int i = 0; i < nElements; ++i)
        ted.array[i] = array[i];
    for (int i = nElements, j = 0; i < ted.nElements; ++j, ++i)
        ted.array[i] = tempArray.array[j];
    return ted;
}

template<class T>
Array<T>::Array(const Array <T> & tempArray)
{
	memory = tempArray.memory;
    nElements = tempArray.nElements;
    array = new T [memory];
    for (int i = 0; i < nElements; ++i) {
        array[i] = tempArray.array[i];
    }
}
template <class T>
void Array<T>::ShiftArray(int position, const int count, const int direction) {
    if (direction) {
        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < position; ++j)
            {
                array[j] = array[j + 1];
            
            }
            array[position--] = 0;
        }
    } else {        
        for (int i = 0; i < count; ++i) {
            for (int j = nElements - 1; j > position; --j){
                array[j] = array[j - 1];
              
            }
           array[position++] = 0;
        }
    }
}

template <class T>
Array<T> & Array<T>::operator = (const Array<T> & tempArray)
{
    if (this != &tempArray) {
        delete[] array;
        memory = tempArray.memory;
        nElements = tempArray.nElements;
        array = new T[memory];
        for (int i = 0; i < nElements; ++i)
            array[i] = tempArray.array[i];
    }
    return *this;
}

template<class T>
void Array<T>::FillArray()
{
	for(int i = 0; i < nElements; ++i)
		std::cin >> array[i];
}

int main()
{

    
    return 0;
}
