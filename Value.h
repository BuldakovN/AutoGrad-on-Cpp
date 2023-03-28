#ifndef VALUE_H_
#define VALUE_H_

#include <iostream>
#include "Backward.h"
#include <vector>

class Value{
    friend class AddBackward<Value>;
    friend class MulBackward<Value>;
    friend class ReLUBackward<Value>;
    friend class SigmoidBackward<Value>;
    friend class PowBackward<Value>;
    private:
        float data;
        float grad;
        bool requireGrad;
        std::vector<Value> *prev;
        Backward<Value> *backward_func = nullptr;
    public:
        Value();
        Value(float, bool requireGrad=false, Backward<Value>* backward_func = nullptr, std::vector<Value>* prev = {0});
        Value(const Value &);
        void setRequireGrad(bool);
        bool isRequireGrad();
        friend Value operator*(Value&, Value&);
        friend Value mul(Value&, Value&);
        friend Value operator+(Value&, Value&);
        friend Value add(Value&, Value&);
        Value operator*(const float);
        Value operator+=(Value&);
        Value pow(float);
        Value sigmoid();
        Value relu();
        friend std::ostream& operator<<(std::ostream&, const Value&);

        ///////////
        void backward();
};

#endif // !VALUE_H_
