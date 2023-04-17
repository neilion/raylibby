#include <cmath>
#include "extensionsVector3.h"

Vector3 operator+(const Vector3 &a, const Vector3 &b) {
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 operator-(const Vector3 &a, const Vector3 &b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 operator*(const Vector3 &a, float s) {
    return {s * a.x, s * a.y, s * a.z};
}

Vector3 operator*(float s, const Vector3 &a) {
    return {s * a.x, s * a.y, s * a.z};
}

float dot(const Vector3 &a, const Vector3 &b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

Vector3 cross(const Vector3 &a, const Vector3 &b) {
    Vector3 tmp;
    tmp.x = a.y * b.z - a.z * b.y;
    tmp.y = a.z * b.x - a.x * b.z;
    tmp.z = a.x * b.y - a.y * b.x;

    return tmp;
}

Vector3 operator+(const Vector3 &a, float s) {
    return {a.x + s, a.y + s, a.z + s};
}

Vector3 operator+(float s, const Vector3 &a) {
    return {a.x + s, a.y + s, a.z + s};
}

Vector3 operator-(const Vector3 &a, float s) {
    return {a.x - s, a.y - s, a.z - s};
}

Vector3 operator-(float s, const Vector3 &a) {

    return {s - a.x, s - a.y, s - a.z};
}



Vector3 elementWiseMin(const Vector3 &v1, const Vector3 &v2) {
    return  {fminf(v1.x, v2.x), fminf(v1.y, v2.y), fminf(v1.z, v2.z)};
}

Vector3 elementWiseMax(const Vector3 &v1, const Vector3 &v2) {
    return  {fmaxf(v1.x, v2.x), fmaxf(v1.y, v2.y), fmaxf(v1.z, v2.z)};
}