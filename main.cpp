#include <iostream>
#include <vector>
#include <algorithm>
#include "Value.h"

int main(int, char**) {
    Value a = Value(5.f, true);
    Value b = Value(4.f);
    Value c = a*b;
}

