#include "Vector.h"
#include "Matrix.h"
#include <cmath>
#include <stdexcept>

Vector::Vector():size(0), vec(0){
//    cout<<"\nСообщение конструктора: создан объект  класса Vector\n";
}


Vector::Vector(const Vector& elements){ // Копирующий конструктор
 //   cout<<"\nСообщение конструктора: копирование начато\n";
    size=elements.size;
    if(elements.size != 0){
        vec = std::vector<Value>(size);
        for(size_t it = 0; it<elements.size; ++it){
            vec[it] = elements.vec[it];
        }
    } else {
        vec = {0};
    }
  //  cout<<"Сообщение конструктора: копирование завершено\n";
}


Vector::Vector(const size_t p_size){  // Если знаем только размер
    size = p_size;
//    cout<<"\nСообщение конструктора: вызван конструктор по размеру "<<size<<endl;
    vec = std::vector<Value>(size);
    for(size_t i = 0; i<size; ++i){
        vec[i] = Value(0);
    }
 //   cout<<"Сообщение конструктора: конец работы конструктора"<<endl;
}


size_t Vector::GetSize() const { // Длина "Вектора"
    return size;
}


//--------------------------------------------//
//-----------ПЕРЕГРУЗКА ОПЕРАТОРОВ------------//
//--------------------------------------------//
std::ostream& operator<<(std::ostream& output, const Vector& v){
    output<<'[';
    for(size_t i = 0; i<v.GetSize() - 1; ++i){
        output<<v.vec[i]<<", ";
    }
    output<<v.vec[v.GetSize() - 1]<<']';
    return output;
}

Vector& Vector::operator+=(Vector& p_vec){
    if(size!=p_vec.size) throw std::invalid_argument("Несоответствующие размерности");
    for(size_t i = 0; i<size; i++){
         vec[i] += p_vec.vec[i];
    }
    return *this;
}


Vector operator+ (Vector& lhs, Vector& rhs){
    if(lhs.size == rhs.size == 0){
        throw std::invalid_argument("размерность вектора не может быть == 0");
    }
    if(lhs.GetSize() != rhs.GetSize()){
        throw std::invalid_argument("Несоответствующие размерности");
    }
    Vector result(lhs.GetSize());
    for(size_t i = 0; i<lhs.size; ++i){
        result.vec[i] = lhs.vec[i] + rhs.vec[i];
    }
    return result;
}


Vector& Vector::operator= (const Vector& rhs){
    if (this == &rhs)
        return (*this);
    if(size != rhs.size){
        size = rhs.size;
        vec = std::vector<Value>(size);
        for (int i = 0; i<size; i++){
            vec[i] = rhs.vec[i];
        }
    }
    for (size_t i = 0; i < size; i++)
        vec[i] = rhs.vec[i];
    return (*this);
}


Value& Vector::operator[] (const size_t index){
    if((index < 0)||(index >= size)){
        throw std::invalid_argument("Ошибка индексации");
    }
    return vec[index];
}


Vector operator* (Vector &v, const float num){
    Vector result(v.GetSize());
    for(size_t i = 0; i<result.size; ++i){
        result.vec[i] = v.vec[i] * num;
    }
    return result;
}


Vector operator* (const float num, Vector &v){
    return v*num;
}


Value operator*(Vector  &a, Vector &b){
    if(a.GetSize() != b.GetSize()){
        throw std::invalid_argument("Несоответствующие размерности");
    }
    Value result = Value(0.f);
    for(size_t i = 0; i<a.GetSize(); ++i){
        Value e1 = a.vec[i];
        Value e2 = b.vec[i];
        Value res = e1 * e2;
        result += res;

    }
    return result;
}


Vector Vector::operator*(Matrix &m)
{
    if (size != m.getRows()) throw std::invalid_argument("Не соответствующие размерности");
    Vector *result = new Vector();
    for (int c = 0; c < m.getColumns(); ++c){
        Value tmp = {0.f};
        for (int r = 0; r < size; ++r){
            Value e1 = vec[r];
            Value e2 = m[c][r];
            Value res = e1 * e2;
            tmp += res;
        }
        result->push_back(tmp);
    }
    return *result;
}

void Vector::push_back(Value &value)
{
    vec.push_back(value);
}

//--------------------------------------------//
//-----------КОНЕЦ БЛОКА ПЕРЕГРУЗОК-----------//
//--------------------------------------------//
