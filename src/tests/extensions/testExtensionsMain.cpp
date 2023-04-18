#include "extensionsVector3.h"
#include <iostream>

bool vectorEqual(const Vector3 &a, const Vector3 &b) {
    // Should likely do float compare here.
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

static bool additionTest() {
    bool allPassed = true;
    Vector3 a{1,2,3};
    Vector3 b{2,3,4};

    auto c = a + b;
    Vector3 cExpected{3,5,7};

    allPassed &= vectorEqual(c, cExpected);
    allPassed &= vectorEqual(b + a, cExpected);

    // Const tests
    const Vector3 ca{1,2,3};
    const Vector3 cb{2,3,4};
    allPassed &= vectorEqual(ca + cb, cExpected);
    allPassed &= vectorEqual(cb + ca, cExpected);


    // Self assignment test
    a = a + a;
    Vector3 aExpected{2,4,6};
    allPassed &= vectorEqual(a, aExpected);

    return allPassed;
}


static bool subtractionTest() {
    bool allPassed = true;
    Vector3 a{1,2,3};
    Vector3 b{2,3,4};

    Vector3 cExpected{-1,-1,-1};
    allPassed &= vectorEqual(a - b, cExpected);

    cExpected = {1,1,1};
    allPassed &= vectorEqual(b - a, cExpected);

    return allPassed;
}


static bool scalarMultiplicationTest() {
    bool allPassed = true;
    Vector3 a{1,2,3};

    float scalar = 2;
    Vector3 cExpected{2,4,6};
    allPassed &= vectorEqual(scalar * a, cExpected);
    allPassed &= vectorEqual(a * scalar, cExpected);

    return allPassed;
}

static bool scalarAdditionTest() {
    bool allPassed = true;
    Vector3 a{1,2,3};

    float scalar = 2;
    Vector3 cExpected{3,4,5};
    allPassed &= vectorEqual(scalar + a, cExpected);
    allPassed &= vectorEqual(a + scalar, cExpected);

    return allPassed;
}

int main() {
    std::cout << "Running vector3 tests\n";
    std::cout << "Vector Addition: " << (additionTest() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Vector Subtraction: " << (subtractionTest() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Vector / Scalar Addition: " << (scalarAdditionTest() ? "PASSED" : "FAILED") << "\n";
    std::cout << "Vector / Scalar Multiplication: " << (scalarMultiplicationTest() ? "PASSED" : "FAILED") << "\n";

    return 1;

}