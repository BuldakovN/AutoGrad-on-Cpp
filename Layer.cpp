#include "Layer.h"

Linear::Linear(int inFeatures, int outFeatures) : inFeatures(inFeatures),
                                                outFeatures(outFeatures)
{
    std::vector<Value> result = std::vector<Value>();
    for (int i = 0; i < inFeatures; ++i){
        result.push_back(Value(outFeatures, true));
    }
    this->parametrs = result;
}

Vector Linear::operator()(Vector &X)
{
    if(parametrs[0].GetSize() != X.GetSize()) throw std::invalid_argument("Несоответствующие размерности");
    auto result = parametrs * X;
    return result;
}