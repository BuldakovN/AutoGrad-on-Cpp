#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <string>
#include <exception>
#include <system_error>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <vector>

class Vector;

class Matrix{
    
public:
    Matrix();
    Matrix(const Matrix&);
    Matrix(size_t, size_t);
    Matrix(size_t, size_t, std::vector<Vector>);
    ~Matrix();
    
    
    size_t GetRowsSize() const;
    size_t GetColumnsSize() const;
    
    //--------------------------------------------//
    //-----------ПЕРЕГРУЗКА ОПЕРАТОРОВ------------//
    //--------------------------------------------//
    friend std::ostream& operator<<(std::ostream&, const Matrix&);
    friend std::istream& operator>>(std::istream&, Matrix&);
    friend Matrix operator* (Matrix&, float);
    friend Matrix operator* (float, Matrix&);
    friend Matrix operator* (Matrix&, float);
    Vector& operator[](size_t);
    Vector operator* (Vector&);
    Matrix& operator= (const Matrix&);
    size_t getRows();
    size_t getColumns();
    //--------------------------------------------//
    //-----------КОНЕЦ БЛОКА ПЕРЕГРУЗОК-----------//
    //--------------------------------------------//
private:
    std::vector<Vector> mat;
    size_t rows;
    size_t columns;
};

#endif /* MATRIX_H_ */
