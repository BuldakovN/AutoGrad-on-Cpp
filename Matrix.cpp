#include "Matrix.h"
#include "Vector.h"



Matrix::Matrix(): rows(0), columns(0), mat(0)
{}


Matrix::Matrix(size_t p_rows, size_t p_columns): rows(p_rows), columns(p_columns)
{
    mat = std::vector<Vector>(p_rows);
    for (auto row:mat){
        row = Vector(p_columns);
    }
}


Matrix::Matrix(size_t p_rows, size_t p_columns, std::vector<Vector> mat): rows(p_rows), columns(p_columns), mat(mat)
{}


Matrix::Matrix(const Matrix& p_matrix){
    columns = p_matrix.columns;
    rows = p_matrix.rows;
    mat = p_matrix.mat;
}


Matrix::~Matrix(){}


size_t Matrix::GetRowsSize() const{
    return rows;
}


size_t Matrix::GetColumnsSize() const{
    return columns;
}


//--------------------------------------------//
//-----------ПЕРЕГРУЗКА ОПЕРАТОРОВ------------//
//--------------------------------------------//
std::ostream& operator<<(std::ostream& output, const Matrix& p_matrix){
    output<<"("<<p_matrix.rows<<", "<<p_matrix.columns<<")";
    return output;
}


Matrix operator* (Matrix& matrix, float num){
    Matrix result(matrix);
    for(auto it: result.mat){
        it = it * num;
    }
    return result;
}

Matrix operator*(float num, Matrix &m)
{
    return m * num;
}

Vector& Matrix::operator[](size_t i)
{
    return mat[i];
}

Vector Matrix::operator*(Vector &right)
{
    // M x V
    Vector result = Vector();
    for(Vector vec: mat){
        Value tmp = Value(vec*right);
        result.push_back(tmp);
    }
    return result;
}

Matrix &Matrix::operator=(const Matrix &matrix)
{
    if(&matrix == this){
        return *this;
    }
    rows = matrix.rows;
    columns = matrix.columns;
    mat = matrix.mat;
    return *this;
}

//--------------------------------------------//
//-----------КОНЕЦ БЛОКА ПЕРЕГРУЗОК-----------//
//--------------------------------------------//

size_t Matrix::getRows()
{
    return rows;
}

size_t Matrix::getColumns()
{
    return columns;
}