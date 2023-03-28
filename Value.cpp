#include "Value.h"

Value::Value() : Value(0.f)
{}

Value::Value(float data, bool requireGrad, Backward<Value> *backward_func, std::vector<Value> *prev) : data(data),
                                                                                                         requireGrad(requireGrad),
                                                                                                         grad(0),
                                                                                                         backward_func(backward_func),
                                                                                                         prev(prev)
{}

Value::Value(const Value &other)
{
    data = other.data;
    backward_func = other.backward_func;
    requireGrad = other.requireGrad;
    prev = other.prev;
}

void Value::setRequireGrad(bool requireGrad)
{
    this->requireGrad = requireGrad;
}

bool Value::isRequireGrad()
{
    return this->requireGrad;
}

Value operator+(Value &that, Value &other)
{
    return add(that, other);
}

Value operator*(Value &that, Value &other)
{
    return mul(that, other);
}

Value mul(Value &that, Value &other)
{
    float out_data = that.data * other.data;
    std::vector<Value> *prev = new std::vector<Value>(&that, &other);
    Backward<Value> *backward_func = new MulBackward<Value>(&that, &other);
    Value *out = new Value(out_data, that.isRequireGrad(), backward_func, prev);
    return *out;
}

Value add(Value &that, Value &other)
{
    float out_data = that.data + other.data;
    std::vector<Value> *prev = new std::vector<Value>(&that, &other);
    Backward<Value> *backward_func = new AddBackward<Value>(&that, &other);
    Value out = Value(out_data, that.isRequireGrad(), backward_func, prev);
    return out;
}

Value Value::operator*(const float v)
{
    Value *num = new Value(v);
    float out_data = this -> data * v;
    std::vector<Value> *prev = new std::vector<Value>({this, num});
    Backward<Value> *backward_func = new MulBackward<Value>({this, num});
    Value *out = new Value(out_data, this->isRequireGrad(), backward_func, prev);
    return *out;
}

Value Value::operator+=(Value &other)
{
    *this = *this + other;
    return *this;
}

Value Value::pow(float power)
{
    float out_data = std::pow(this->data, power);
    std::vector<Value> *prev = new std::vector<Value>({*this});
    Backward<Value> *backward_func = new PowBackward<Value>(this, power);
    Value *out = new Value(out_data, requireGrad=this->requireGrad, backward_func=backward_func, prev=prev);
    return *out;
}

Value Value::sigmoid()
{
    float out_data = 1.f / (1.f + std::exp(-(this->data)));
    std::vector<Value> *prev = new std::vector<Value>({*this});
    Backward<Value> *backward_func = new SigmoidBackward<Value>(this);
    Value *out = new Value(out_data, requireGrad=this->requireGrad, backward_func=backward_func, prev=prev);
    return *out;
}

Value Value::relu()
{
    float out_data = (this->data > 0)? this->data : 0;
    std::vector<Value> *prev = new std::vector<Value>({*this});
    Backward<Value> *backward_func = new ReLUBackward<Value>(this);
    Value out = Value(out_data, this->requireGrad, backward_func, prev);
    return out;
}

void Value::backward()
{
    data -= grad;
}

std::ostream &operator<<(std::ostream &stream, const Value &value)
{
    stream<<value.data;
    return stream;
}
