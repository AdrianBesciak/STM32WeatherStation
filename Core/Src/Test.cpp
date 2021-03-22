//
// Created by Rivit on 21/03/2021.
//

#include "Test.h"

Test::Test() {
    x = 5;
}

void Test::test_func() {
    x = 1;
    int b = x;
    b++;
    x = b;
}


