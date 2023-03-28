#include "Value.h"
#include <algorithm>
#include <functional>

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
    bool gradRequired = that.requireGrad || other.requireGrad; 
    Value *out = new Value(out_data, gradRequired);
    Backward<Value> *backward_func = new MulBackward<Value>(out, &that, &other);
    out->prev = prev;
    out->backward_func = backward_func;
    return *out;
}

Value add(Value &that, Value &other)
{
    float out_data = that.data + other.data;
    std::vector<Value> *prev = new std::vector<Value>(&that, &other);
    bool gradRequired = that.requireGrad || other.requireGrad; 
    Value *out = new Value(out_data, gradRequired);
    Backward<Value> *backward_func = new AddBackward<Value>(out, &that, &other);
    out->prev = prev;
    out->backward_func = backward_func;
    return *out;
}

bool operator==(const Value &l, const Value &r)
{
    if (&l == &r) return true;
    return (l.data == r.data) && (l.grad == r.grad); 
}

bool operator==(Value &l, Value &r)
{
    if (&l == &r) return true;
    return (l.data == r.data) && (l.grad == r.grad); 
}

Value Value::operator*(const float v)
{
    Value *num = new Value(v);
    float out_data = this -> data * v;
    std::vector<Value> *prev = new std::vector<Value>({this, num});
    bool gradRequired = this->requireGrad;
    Value *out = new Value(out_data, gradRequired);
    Backward<Value> *backward_func = new MulBackward<Value>(out, this, num);
    out->prev = prev;
    out->backward_func = backward_func;
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
    bool gradRequired = this->requireGrad;
    Value *out = new Value(out_data, gradRequired);
    Backward<Value> *backward_func = new PowBackward<Value>(out, this, power);
    out->prev = prev;
    out->backward_func = backward_func;
    return *out;
}

Value Value::sigmoid()
{
    float out_data = 1.f / (1.f + std::exp(-(this->data)));
    std::vector<Value> *prev = new std::vector<Value>({*this});
    bool gradRequired = this->requireGrad;
    Value *out = new Value(out_data, gradRequired);
    Backward<Value> *backward_func = new SigmoidBackward<Value>(out, this);
    out->prev = prev;
    out->backward_func = backward_func;
    return *out;
}

Value Value::relu()
{
    float out_data = (this->data > 0)? this->data : 0;
    std::vector<Value> *prev = new std::vector<Value>({*this});
    bool gradRequired = this->requireGrad;
    Value *out = new Value(out_data, gradRequired);
    Backward<Value> *backward_func = new ReLUBackward<Value>(out, this);
    out->prev = prev;
    out->backward_func = backward_func;
    return *out;
}

void Value::backward(float grad)
{   
    std::vector<Value> topo(0);
    std::function<void(Value)> build_topo = [this, topo, build_topo](Value v)mutable->void{
        bool result = std::find(topo.begin(), topo.end(), v) == topo.end();
        if (result){
            topo.push_back(v);
        }
    };
    build_topo(*this);
    this->grad = 0;
    std::cout<<"GO";
    for(auto v:topo){
        std::cout<<v<<" ";
        (*v.backward_func)();
    }

}

float Value::getGrad()
{
    return this->grad;
}

std::ostream &operator<<(std::ostream &stream, const Value &value)
{
    stream<<value.data;
    return stream;
}
