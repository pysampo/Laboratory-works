#include <iostream>
#include <ostream>
#include <cstring>
#include <cmath>
#include <vector>
#define uc unsigned char
class bVcomponent;
class bVector
{
    int lenV, charBytes;
    unsigned char* bv;
    public:
    bVector(int nn = 0, int mm =1);
    bVector(const char *,int length = 0);
    ~bVector() { delete [] bv; }
    bool Set_1(int index);
    bVector(const bVector& tempVector);
    friend class bVcomponent;
    int CreateVector(const char* str, int cChar, int current_len, int current_i);
    bool Set_0(int index);
    bool InverstionSet(int index);
    void SetAll_1();
    void SetAll_0();
    int WeightOfVector();
    bool SetWithRange_1(int bits, int  index);
    bool SetWithRange_0(int bits, int  index);

    bVector & operator = (const bVector & tempV);
    bVector operator & (bVector & tempV);
    bVector & operator &= (bVector & tempV);

    bVector operator ^ (bVector & tempV);
    bVector & operator ^= ( bVector & tempV);

    bVector operator |(bVector & tempV);
    bVector & operator |= (bVector & tempV);
    bVector operator ~ ();
    bVector operator >> (int integer);
    bVector operator << (int integer);
    bVector &operator <<= (int integer);
    bVector &operator >>= (int integer);
    int Size();
    bVcomponent operator [] (int index);
    friend std::ostream&operator <<(std::ostream & out, bVector& tempV);
    friend std::istream&operator <<(std::istream & in, bVector &tempV);
    bool operator == (int);
    bool operator != (int);
    bool operator < (int);
    bool operator > (int);
    bool operator >= (int);
    bool operator <= (int);
    operator int();
    bool InverstionWithRange(int bits, int index);
    long Result();
};

class bVcomponent
{
private:
    uc mask = 1;
    uc * cpy;
public:
    bVcomponent(uc* cpy_, int index_);
    void operator = (bool integer);
    operator int();
    friend std::ostream & operator << (std::ostream & out, bVcomponent & temp);
};

bVcomponent::operator int()
{
    return (*cpy & mask);
}

void bVcomponent::operator=(bool integer)
{
    if (integer)
        *cpy |=  mask;
    else
        *cpy &= ~mask;
}

bVcomponent::bVcomponent(uc * cpy_ , int index_)
{
    mask <<= index_ % 8;
    cpy = cpy_;
}

bVcomponent bVector::operator[](int index)
{
    if (index < lenV && index >= 0)
    {
        bVcomponent temp(&bv[charBytes - 1 - index / 8], index);
        return temp;
    }
    bVcomponent teddy(&bv[charBytes-1], 0);
    return teddy;
}

std::ostream & operator << (std::ostream & out, bVcomponent & temp)
{
    out << (*(temp.cpy) & temp.mask); // output value bv[index];
    return out;
}

bVector::operator int()
{
    int ted = this->Result();
    return ted;
}
long bVector::Result()
{
    long result = 0;
    int eq = 0;
    for (int j = charBytes-1; j >= 0; --j)
        for (int i = 0; i < 8; ++i, ++eq)
        {
            if (bv[j] & (1 << i ))
                result += (1 << eq);
        }
    return result;
}
bVector:: bVector(int nn, int mm)
{
    charBytes = (mm == 0 ? 1 : (mm < 0 ? -mm : mm));
    lenV = (nn < 0 ? 0 : nn);
    if (nn > 8*mm) {
        charBytes = (lenV + 7) / 8;
    }
    bv = new uc [charBytes];
    SetAll_0();
}
std::ostream & operator <<(std::ostream & out, bVector& t)
{
 /*   for (int j = 0; j < tempV.charBytes; ++j){
        for (int i = 0; i < 8; ++i) {
         out << ((tempV.bv[j] & (1 << (7- i)) ? 1 : 0));
        }
    }
    return out;
    */
    bool value;
    for (int i = 0; i < t.lenV; ++i)
    {
        int byte = t.charBytes - 1 - i / 8;
        if((t.bv[byte] & (1 << i)))
            out << '1';
        else 
            out << '0';
     }
    return out;

}

int bVector::CreateVector(const char* str, int cChar, int current_len, int current_i)
{
    bv[cChar] = 0;
    for (int i = 0; i < current_len; ++i)
    {
        bv[cChar] <<= 1;
        if (str[current_i] == '1')
            ++bv[cChar];
        ++current_i;
    }
    return current_i;
}

std::istream & operator>>(std::istream & in, bVector & tempV)
{
    int Range;
    in >> Range;
    char* str = new char[Range];
    in >> str;
    bVector temp(str);
    delete [] str;
    tempV = temp;
    return in;
}
bVector::bVector(const char* str, int length)
{
    int lenStr = strlen(str);
    lenV = (length == 0) ? lenStr : (length > lenStr ? lenStr : length);
    charBytes = (lenV + 7) / 8;
    bv = new uc[charBytes];
    int cChar = 0;
    int current_i = 0;
    if (lenV % 8)
    {
        current_i = CreateVector(str, cChar, lenV % 8, current_i);
        ++cChar;
    }
    while(current_i < lenV)
    {
        current_i = CreateVector(str, cChar, 8, current_i);
        ++cChar;
    }
}
bVector::bVector(const bVector& tempVector)
{
    lenV = tempVector.lenV;
    charBytes = tempVector.charBytes;
    bv = new unsigned char [charBytes];
    for (int i = 0; i < charBytes; ++i)
        bv[i] = tempVector.bv[i];
}

bVector bVector::operator & (bVector &tempV)
{
    bVector ted = *this;
    ted &= tempV;
    return ted;
}

bVector bVector::operator ^ (bVector & tempV)
{
    bVector ted = *this;
    ted ^= tempV;
    return ted;
}

bVector bVector::operator | (bVector & tempV)
{
    bVector ted = *this;
    ted |= tempV;
    return ted;
}

bVector & bVector::operator &= (bVector &tempV)
{
     int length = lenV > tempV.lenV ? lenV : tempV.lenV;
     bVector ted (length);
     int i, j, z;
     for (i = charBytes - 1, j = tempV.charBytes - 1, z = ted.charBytes - 1;
             i >= 0 && j >= 0; --i, --j, --z)
         ted.bv[z] = bv[i] & tempV.bv[j];
     *this = ted;
     return *this;
}

bVector &bVector::operator ^= (bVector & tempV)
{
    int length = lenV > tempV.lenV ? lenV : tempV.lenV;
    bVector ted ( length );
    int i, j, z;
    for (i = charBytes - 1, j = tempV.charBytes - 1, z = ted.charBytes - 1;
            i >= 0 && j >= 0; --i, --j, --z)
        ted.bv[z] = bv[i] ^ tempV.bv[j];

    while (z >= 0 && i >= 0)
    {
        ted.bv[z] ^= bv[z];
        --z;
    }
    while (z >= 0 && j >= 0 )
    {
        ted.bv[z] ^= tempV.bv[z];
        --z;
    }
    *this = ted;
    return *this;
}

bVector &bVector::operator |= (bVector & tempV)
{
    int length = lenV > tempV.lenV ? lenV : tempV.lenV;
    bVector ted (length);
    int i, j, z;
    for (i = charBytes - 1, j = tempV.charBytes - 1, z = ted.charBytes - 1;
            i >= 0 && j >= 0; --i, --j, --z)
        ted.bv[z] = bv[i] | tempV.bv[j];

    while (z >= 0 && i >= 0)
    {
        ted.bv[z] |= bv[z];
        --z;
    }
    while (z >= 0 && j >= 0 )
    {
        ted.bv[z] |= tempV.bv[z];
        --z;
    }
    *this = ted;
    return *this;

}

bool bVector::InverstionWithRange(int bits, int index)
{
     if (bits < 0 || index < 0 || lenV < bits+index)
         return false;
     for (int i = 0; i < bits; ++i)
         InverstionSet(index++);
     return true;
}

bVector & bVector::operator = (const bVector & tempV)
{
    if (this != & tempV)
    {
        delete [] bv;
        charBytes = tempV.charBytes;
        lenV = tempV.lenV;
        bv = new uc[charBytes];
        for (int i = 0; i < lenV; ++i)
            bv[i] = tempV.bv[i];
    }
    return *this;
}

bool bVector::SetWithRange_0(int bits, int index)
{

    if (bits < 0 || index < 0 || lenV < bits+index)
        return false;
    for (int i = 0; i < bits; ++i)
        Set_0(index++);
    return true;
}
bool bVector::SetWithRange_1(int bits, int  index)
{
    if (bits < 0 || index < 0 || lenV < bits+index)
        return false;
    for (int i = 0; i < bits; ++i)
        Set_1(index++);
    return true;
}
int bVector::WeightOfVector()
{
    int count = 0;
    uc mask;
    for (int j = 0; j < charBytes; ++j)
    {
        mask = 1;
        do
        {
            if (mask & bv[j])
                ++count;
        } while(mask <<= 1);
    }
    return count;
}
void bVector::SetAll_0()
{
    for(int j = 0; j < charBytes; ++j)
            bv[j] = 0;
}
void bVector::SetAll_1()
{
     for (int j = 0; j < charBytes; ++j)
        bv[j] = 255;

}
bVector bVector::operator ~()
{
    bVector ted (lenV);
    for (int j = 0; j < charBytes; ++j)
        ted.bv[j] = ~bv[j];
    return ted;
}
bool bVector::Set_0(int index)
{
    if (index < charBytes*8 && index >= 0)
    {
        int cChar = charBytes - 1 - index / 8;
        bv[cChar] &= ~(1 << index % 8);
        return true;
    }
    return false;
}
bool bVector::Set_1(int index)
{
    if (index < charBytes*8 && index >= 0)
    {
        int cChar = charBytes - 1 - index / 8;
        bv[cChar] |= (1 << index % 8);
        return true;
    }
    return false;
}
bool  bVector::InverstionSet(int index)
{
    if (index < charBytes*8 && index >= 0)
    {
        int cChar = charBytes - 1 - index / 8;
        bv[cChar] ^= (1 << index % 8);
        return true;
    }
    return false;
}
bVector bVector::operator <<(int integer)
{
    bVector temp(*this);
    temp <<= integer;
    return temp;
}
bVector bVector::operator>>(int integer)
{
    bVector temp(*this);
    temp >>= integer;
    return temp;
}
bVector & bVector::operator >>= (int integer)
{
    for (int i = 0; i < integer; ++i) {
        for (int j = 0; j < charBytes*8-1; ++j)
        {
            if (this->operator[](j+1))
                Set_1(j);
            else
                Set_0(j);
            Set_0(j+1);
        }
    }
    return *this;
}
bVector & bVector::operator <<= (int integer)
{
    for (int i = 0; i < integer; ++i) {
        for (int j = charBytes*8 -1; j >= 0; --j)
        {
            if (this->operator[](j-1))
                Set_1(j);
            else
                Set_0(j);
            Set_0(j-1);
        }
    }
    std::cout << std::endl;
    return *this;
}
bool bVector::operator <= (int key)
{
    if (this->Result() <= key)
        return true;
    return false;
}
bool bVector::operator <(int key)
{
    if (this->Result() < key)
        return true;
    return false;
}
bool bVector::operator >= (int key)
{
    if (this->Result() >= key)
        return true;
    return false;
}
bool bVector::operator > (int key)
{
    if (this->Result() > key)
        return true;
    return false;
}
bool bVector::operator != (int key)
{
    if (this->Result() != key)
        return true;
    return false;
}
bool bVector::operator == (int key)
{
    if (this->Result() == key)
        return true;
    return false;
}
int bVector::Size()
{
    std::cout << charBytes << " " << lenV << std::endl;
    return charBytes * sizeof(char);
}

class bMatrix
{
    bVector * bm;
    int rows, lines;
public:
    bMatrix(const int rows_ = 1, const int lines_ = 0);
    bMatrix(char ** str, const int rows_, const int lines_);
    bMatrix(bMatrix & temp);
    ~bMatrix () { delete [] bm; }

    int WeightOfMatrix();
    int WeightOfLine(int line);
    bVector Conjuction_M();
    bVector Disjunction_M();
    bool InverstionSet_M(int index, int line);
    bool InverstionWithRange_M(int bits, int index, int line);
    bool Set_1_M(int index, int line);
    bool Set_0_M(int index, int line);
    bool SetWithRange_1_M(int bits, int index, int line);
    bool SetWithRange_0_M(int bits, int index, int line);

    bMatrix& operator = (const bMatrix & temp);
    bVector& operator [] (int line);
    bMatrix operator & (bMatrix & temp);
    bMatrix& operator &= (bMatrix & temp);
    bMatrix operator |  (bMatrix & temp);
    bMatrix& operator |= (bMatrix & temp);
    bMatrix operator ^ (bMatrix & temp);
    bMatrix& operator ^= (bMatrix & temp);
    bMatrix operator ~();
    std::vector<int> SortGraph();
    void SupportSort(std::vector<int> & v, bMatrix & copyGraph, bVector & temp);
    friend std::ostream & operator << (std::ostream & out, bMatrix & temp);
    friend std::istream & operator >> (std::istream & in, bMatrix & temp);
};

bVector bMatrix::Disjunction_M()
{
    bVector temp = bm[0];
    for (int i = 1; i < rows; ++i)
        temp |= bm[i];
    return temp;
}

bVector bMatrix::Conjuction_M()
{
    bVector temp = bm[0];
    for (int i = 1; i < rows; ++i)
        temp &= bm[i];
    return temp;
}

bVector& bMatrix::operator [] (int line)
{
    if (0 < line && line < lines)
        return bm[line];
    return bm[0];
}

bMatrix& bMatrix::operator = (const bMatrix & temp)
{
    if (this == &temp)
        return *this;
    delete [] bm;
    rows = temp.rows;
    lines = temp.lines;
    bm = new bVector[rows];
    for (int i = 0; i < rows; ++i)
        bm[i] = temp.bm[i];
    return *this;
}

std::istream& operator >> (std::istream & in, bMatrix & temp)
{
    int rows_, lines_;
    std::cin >> rows_ >> lines_;

    temp.rows = (rows_ == 0) ? 1 : (rows_ < 0 ? -rows_ : rows_ );
    temp.lines = (lines_ < 0) ? 0 : lines_;

    delete [] temp.bm;
    temp.bm = new bVector[temp.rows];
    char* str = new char[temp.lines];

    for (int i = 0; i < temp.rows; ++i)
    {
        in >> str;
        bVector teddy(str, temp.lines);
        temp.bm[i] = teddy;
    }
    delete [] str;

    return in;
}

std::ostream& operator << (std::ostream & out, bMatrix & temp)
{
    int i;
    for (i = 0; i < temp.rows - 1; ++i)
        out << temp.bm[i] << std::endl;
    out << temp.bm[i];
    return out;
}

bMatrix bMatrix::operator ~()
{
    bMatrix temp(rows, lines);
    for (int i = 0; i < rows; ++i)
        temp.bm[i] = ~bm[i];
    return temp;
}

bMatrix bMatrix::operator |  (bMatrix & temp)
{
    bMatrix teddy = *this;
    teddy |= temp;
    return teddy;
}

bMatrix &bMatrix::operator |= (bMatrix & temp)
{
    if (rows != temp.rows)
        return *this;
    int length = (lines > temp.lines) ? lines : temp.lines;
    bMatrix teddy(rows, length);
    for (int i = 0; i < teddy.rows; ++i)
        teddy.bm[i] = bm[i] | temp.bm[i];
    *this = teddy;
    return *this;
}

bMatrix bMatrix::operator ^ (bMatrix & temp)
{
    bMatrix teddy = *this;
    teddy ^= temp;
    return teddy;
}

bMatrix &bMatrix::operator ^= (bMatrix & temp)
{
    if (rows != temp.rows)
        return *this;
    int length = (lines > temp.lines) ? lines : temp.lines;
    bMatrix teddy(rows, length);
    for (int i = 0; i < teddy.rows; ++i)
        teddy.bm[i] = bm[i] ^ temp.bm[i];
    *this = teddy;
    return *this;
}

bMatrix bMatrix::operator & (bMatrix & temp)
{
    bMatrix teddy = *this;
    teddy &= temp;
    return teddy;
}

bMatrix& bMatrix::operator &= (bMatrix & temp)
{
    if (rows != temp.rows)
        return *this;
    int length = (lines > temp.lines) ? lines : temp.lines;
    bMatrix teddy(rows, length);
    for (int i = 0; i < teddy.rows; ++i)
        teddy.bm[i] = bm[i] & temp.bm[i];
    *this = teddy;
    return *this;
}

bool bMatrix::SetWithRange_0_M(int bits, int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].SetWithRange_0(bits, index)))
         return true;
    return false;
}

bool bMatrix::SetWithRange_1_M(int bits, int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].SetWithRange_1(bits, index)))
        return true;
    return false;
}

bool bMatrix::Set_0_M(int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].Set_0(index)))
        return true;
    return false;
}

bool bMatrix::Set_1_M(int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].Set_1(index)))
            return true;
    return false;
}

bool bMatrix::InverstionWithRange_M(int bits, int index, int line)
{
    if ((0 <= line && line < lines) && (bm[line].InverstionWithRange(bits, index)))
            return true;
    return false;
}

bool bMatrix::InverstionSet_M(int index, int line)
{
    if ((0 <= line && line < lines) && (bm[index].InverstionSet(line)))
               return true;
    return false;
}

int bMatrix::WeightOfLine(int line)
{
    if (0 <= line && line < lines)
        return bm[line].WeightOfVector();
    return -1;
}

int bMatrix::WeightOfMatrix()
{
    int weight = 0;
    for (int i = 0; i < rows; ++i)
        weight += bm[i].WeightOfVector();
    return weight;
}

bMatrix:: bMatrix(bMatrix & temp)
{
    rows = temp.rows;
    lines = temp.lines;
    bm = new bVector[rows];
    for (int i = 0; i < rows; ++i)
        bm[i] = temp.bm[i];
}

bMatrix:: bMatrix(char ** str, const int rows_, const int lines_)
{
    rows = (rows_ == 0) ? 1 : (rows_ < 0) ? -rows_ : rows_ ;
    lines = (lines_ < 0) ? 0 : lines_;
    bm = new bVector[rows];
    for (int i = 0; i < rows; ++i)
    {
        bVector temp(str[i], lines);
        bm[i] = temp;
    }
}

bMatrix:: bMatrix(const int rows_, const int lines_)
{
    rows = (rows_ == 0) ? 1 : (rows_ < 0) ? -rows_ : rows_ ;
    lines = (lines_ < 0) ? 0 : lines_;
    bm = new bVector[rows];
    bVector temp(lines);
    for (int i = 0; i < rows; ++i)
        bm[i] = temp;

}

void bMatrix::SupportSort(std::vector<int> &v, bMatrix & copyGraph, bVector & temp)
{
    uc mask;
    for (int j = 0; j < copyGraph.lines; ++j)
    {
        mask = 1;
        do
        {  if (mask & temp[j]) {
                copyGraph[j].SetAll_0(); //удаляем дуги, исходящие с истоков
               v.push_back(j+1);
            }
        } while (mask <<= 1);
    }
}
std::vector<int> bMatrix::SortGraph(){
//Топологическая сортировка - способ упорядочивания вершин ографа таким образом, 
//что каждое ребро ведёт из вершины с меньшим номером в вершину с большим номером
    std::vector<int> (v);
    bMatrix copyGraph = *this;
    bVector temp = copyGraph.Disjunction_M();
    temp = ~temp; //поиск истоков
    bVector forKeep = temp; //хранитель обработанных вершин
    bVector previousvertex;
    //std::cout <<"First Vector : "  <<temp << std::endl;
   // std::cout << "after ~:(forkeep too equal) = " << forKeep << std::endl;
   // Топологическая сортировка работает только для ациклических орграфов. Если
   // наткнёмся на цикл, то temp.WeightOfMatrix() == 0, т.к. истоков не будет
    while (temp.WeightOfVector()){ //пока имеются истоки
        SupportSort(v, copyGraph, temp); //очистка истоков + удаление исходящих дуг
        temp = copyGraph.Disjunction_M();// получение оставшихся вершин
     // std::cout <<"After SupportSort (1): "<<  temp << std::endl;
        previousvertex = ~temp; //для поиска истоков
       // std::cout <<"Previous vertex : " << previousvertex << std::endl;
         forKeep = ~forKeep; 
       // std::cout <<"After ~ forKeep : " << forKeep << std::endl;
        previousvertex &= forKeep; //пересечение вершин с необработанными вершинами 
        //std::cout << "Previous vertex: " << previousvertex << std::endl;
        forKeep = ~forKeep;// возвращаем хранитель
        forKeep|= previousvertex;//обновляем наш хранитель
        std::cout << forKeep << std::endl;
       // std::cout <<"After allforKeep : " << forKeep << std::endl;
        temp = previousvertex; //в темпе теперь хранятся нужные истоки
        std::cout << temp << std::endl;
    //    std::cout << "Position before delete str & rows "  << temp << std::endl;
    }
    if (v.size() !=  rows) { //кол-во истоков != исходному кол-ву вершин графа 
        std::cerr << "Loop in Graph. " << std::endl;
        v.clear();
        v.push_back(-1);
    }
    return v;
    //
 //  1 2 3 4 5   1 2 3 4 5  1 2 3 4 5  1 2 3 4 5  1 2 3 4 5 
 //1 0 1 1 1 1   0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  
 //2 0 0 0 0 0   0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0  
 //3 0 1 0 0 0   0 1 0 0 0  0 1 0 0 0  0 1 0 0 0  0 0 0 0 0
 //4 0 0 1 0 0   0 0 1 0 0  0 0 1 0 0  0 0 0 0 0  0 0 0 0 0
 //5 0 1 0 1 0   0 1 0 1 0  0 0 0 0 0  0 0 0 0 0  0 0 0 0 0
//  
//  1)Удалили вершину 1 и ее дуги.
//  2)Удалили вершину 5 и дуги.
//  3)Удалили вершину 4 и дугу.
//  4)Удалили вершину 3 и дугу.
//  5)Удалили вершину 2.
//  В итоге: 1 5 4 3 2
//  В графах могут быть несколько упорядоченных последовательностей.


}
int main(void)
{
    int Range;
    std::cin >> Range;
    bMatrix Graph(Range, Range);
    int from, to;
    while(std::cin >> from >> to) {
        if (( from <= 0|| from > Range) || (to <= 0|| to > Range)) {
            std::cout << "Reenter: " << std::endl;
            continue;
        }
        Graph[from-1][to-1] = 1;
    }
    std::vector<int> (v) = Graph.SortGraph();
    for (unsigned long i = 0; i < v.size(); ++i)
        std::cout << v[i] <<  " ";
    std::cout << std::endl;
    return 0;
}
