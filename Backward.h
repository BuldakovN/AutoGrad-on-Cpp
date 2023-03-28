#ifndef BACKWARD_H_
#define BACKWARD_H_

#include <cmath>

template<typename T>
class Backward
{
    protected:
        T *o1, *o2;
    public:
        Backward(T *o1, T *o2 = nullptr): o1(o1), o2(o2){};
        virtual void operator()(float grad) = 0;
        
};

template<class T>
class AddBackward: public Backward<T>{
    public:
        AddBackward(T *o1, T *o2 = nullptr): Backward<T>(o1, o2){};
        void operator()(float grad) override{
            /*
                out = a+b
                d(out) / d(a) = 1
                d(out) / d(b) = 1
            */
            Backward<T>::o1->grad += grad;
            if (Backward<T>::o2 != nullptr) Backward<T>::o2->grad += grad;
        }
};

template<class T>
class MulBackward: public Backward<T>{
    public:
        MulBackward(T *o1, T *o2 = nullptr): Backward<T>(o1, o2){};
        void operator()(float grad) override{
            /*
                out = a*b
                d(out) / d(a) = b
                d(out) / d(b) = a
            */
            Backward<T>::o1->grad += grad * Backward<T>::o2->data;
            if (Backward<T>::o2 != nullptr) Backward<T>::o2->grad += grad * Backward<T>::o1->data;
        }
};

template<class T>
class ReLUBackward: public Backward<T>{
    public:
        ReLUBackward(T *o1): Backward<T>(o1){};
        void operator()(float grad) override{
            /*
                out = ReLU(a)
                                    a, if a>0
                d(out) / d(a) = {
                                    0, if a<=0
            */
            Backward<T>::o1->grad += grad * (Backward<T>::o1->data > 0? Backward<T>::o1->data : 0.f);
        }
};

template<class T>
class SigmoidBackward: public Backward<T>{
    private:
        float sigmoid(float x){
            return 1. / (1. + std::exp(-x));
        }
    public:
        SigmoidBackward(T *o1): Backward<T>(o1){};
        void operator()(float grad) override{
            /*
                out = sigmoid(a)
                d(out) / d(a) = sigmoid(a)*(1-sigmoid(a))
            */
           float out = sigmoid(Backward<T>::o1->data) * (1. - sigmoid(Backward<T>::o1->data));
           Backward<T>::o1->grad += grad * out;
        }
};


template<class T>
class PowBackward: public Backward<T>{
    private:
        float power;
    public:
        PowBackward(T *o1, float power): Backward<T>(o1){
            this->power = power;
        };
        void operator()(float grad) override{ 
            /*
                out = a ^ power
                d(out) / d(a) = power * a^(power-1)
            */
            Backward<T>::o1->grad += grad * power * std::pow(Backward<T>::o1->data, power-1.);
        }
};


#endif // !BACKWARD_H_