#include <iostream>
#include <vector>
#include <algorithm>
#include "Value.h"

int main(int, char**) {
    Value a = Value(5.f, true);
    Value b = Value(4.f, true);
    Value c = a*b;
    std::cout<<"Start\n";
    c.backward();
    std::cout<<a.getGrad()<<" "<<b.getGrad()<<" "<<c.getGrad()<<"Stop\n";
}

