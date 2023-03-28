#ifndef LAYER_H_
#define LAYER_H_

#include "Vector.h"
#include "Matrix.h"

class Module{
    public:
        virtual Vector operator()(Vector &) = 0;
        virtual Vector backward(Vector grad) = 0;
};

class Linear : public Module{
    Matrix parametrs;
    Vector B;
    int inFeatures, outFeatures;
    public:
        Linear(int, int);
        Vector operator()(Vector &X) override;
};

#endif // !LAYER_H_
