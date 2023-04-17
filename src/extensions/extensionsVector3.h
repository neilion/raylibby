#ifndef RAYLIBBY_EXTENSIONSVECTOR3_H
#define RAYLIBBY_EXTENSIONSVECTOR3_H

#include "raylib.h"

/*!
 * Add convenient vector operations to extend the vector 3D struct.
 * Define via "outside of class" style.
 * Write all of these to be safe to be called on self / self assigned.
*/

Vector3 operator+(const Vector3 &, const Vector3 &);
Vector3 operator-(const Vector3 &, const Vector3 &);

Vector3 operator+(const Vector3 &, float);
Vector3 operator+(float, const Vector3 &);

Vector3 operator-(const Vector3 &, float);
Vector3 operator-(float, const Vector3 &);

Vector3 operator*(const Vector3 &, float);
Vector3 operator*(float, const Vector3 &);

float dot(const Vector3 &, const Vector3 &);
Vector3 cross(const Vector3 &, const Vector3 &);

Vector3 elementWiseMin(const Vector3 &v1, const Vector3 &v2);

Vector3 elementWiseMax(const Vector3 &v1, const Vector3 &v2);


#endif //RAYLIBBY_EXTENSIONSVECTOR3_H
