#include <iostream>
#include <ostream>
#include <cstring>
#include <cmath>
#include <vector>
#define uc unsigned char

class bVector
{
    int lenV, charBytes;
    unsigned char* bv;

    public:
    bVector(int nn = 0, int mm =1);
    bVector(const char *);
    ~bVector() { delete [] bv; } 
    bool Set_1(int index);
    bVector(const bVector& tempVector);

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
    void operator ~ ();
    bVector operator >> (int integer);
    bVector operator << (int integer);
    bVector &operator <<= (int integer);
    bVector &operator >>= (int integer);
    int Size();
    int operator[] (int index);
    friend std::ostream&operator <<(std::ostream & out, bVector& tempV);
    friend std::istream&operator <<(std::istream & in, bVector &tempV);
    int Result();
    bool operator == (int);
    bool operator != (int);
    bool operator < (int);
    bool operator > (int);
    bool operator >= (int);
    bool operator <= (int);
};



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

std::ostream & operator <<(std::ostream & out, bVector& tempV)
{
    for (int j = 0; j < tempV.charBytes; ++j){
        for (int i = 0; i < 8; ++i) {
         out << ((tempV.bv[j] & (1 << (7- i)) ? 1 : 0));
        }
    }
    return out;
}

int bVector::operator[] (int index)
{
    if(index < lenV && index >= 0)
    {
        int cChar = charBytes - 1 - index / 8;
        if (bv[cChar] & (1 << index % 8))
        return 1;
    }
    return 0;
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

std::istream & operator >>(std::istream & in, bVector & tempV)
{
    char str[100];
    in.getline(str, 100);
    bVector temp(str);
    tempV = temp;
    return in;
}
bVector::bVector(const char* str)
{
    lenV = strlen(str);
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

bVector &bVector::operator ^= (bVector & tempV)
{
    *this = (*this ^ tempV);
    return *this;
}

bVector bVector::operator ^ (bVector & tempV)
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
    return ted;
}

bVector bVector::operator | (bVector & tempV)
{
    int length = lenV > tempV.lenV ? lenV : tempV.lenV;
    bVector ted ( length );
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
    return ted;
}
bVector &bVector::operator |= (bVector & tempV)
{
    *this = (*this | tempV);
    return *this;
}

bVector &bVector::operator &= (bVector & tempV)
{
    *this = (*this & tempV);
    return *this;
}
bVector bVector::operator & (bVector & tempV)
{
    int length = lenV > tempV.lenV ? lenV : tempV.lenV;
    bVector ted ( length );
    int i, j, z;
    for (i = charBytes - 1, j = tempV.charBytes - 1, z = ted.charBytes - 1;
            i >= 0 && j >= 0; --i, --j, --z)
        ted.bv[z] = bv[i] & tempV.bv[j];
    return ted;
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
    this->SetWithRange_1(lenV, 0);
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
int bVector::Result()
{
    int result = 0;
    int eq = 0;
    for (int j = charBytes-1; j >= 0; --j)
    for (int i = 0; i < 8; ++i, ++eq){
            if (bv[j] &(1<<i)) {result += pow(2,eq);
        
        }
    }
    return result;
}

void bVector::operator ~()
{
    for (int j = 0; j < charBytes; ++j)
        for (int i = 0; i < 8; ++i)
            InverstionSet(i);
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
    return charBytes * sizeof(char);
}

int main(void)
{
    bVector x = ("00100101");
    ~x;
    std::cout << x << std::endl;    
    return 0;
}
