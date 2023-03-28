#ifndef VALUEVECTOR_H_
#define VALUEVECTOR_H_

#include <iostream>
#include <string>
#include <exception>
#include <system_error>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include "Value.h"

class Matrix;

class Vector{
public:
    Vector();
    Vector(const Vector& elements);
    Vector(size_t p_size);
    size_t GetSize() const;
    
    //--------------------------------------------//
    //-----------ПЕРЕГРУЗКА ОПЕРАТОРОВ------------//
    //--------------------------------------------//
    
    friend std::ostream& operator<<(std::ostream& output, const Vector& v);
    Vector& operator+= (Vector&);
    friend Vector operator+ (Vector&, Vector&);
    Vector& operator= (const Vector&); //
    Value& operator[] (const size_t);
    friend Value operator* (Vector&, Vector&);
    friend Vector operator* (Vector&, const float);
    friend Vector operator* (const float, Vector&);
    Vector operator*(Matrix&);
    
    //--------------------------------------------//
    //-----------КОНЕЦ БЛОКА ПЕРЕГРУЗОК-----------//
    //--------------------------------------------//
    void push_back(Value&);
private:
    std::vector<Value> vec;
    size_t size;
};


#endif // !VALUEVECTOR_H_
