#ifndef W_MATRIX_4_H
#define W_MATRIX_4_H
#include <stdlib.h>
#include "vectors.h"
#include <arduino.h>

class Matrix4
{
public:
    float arr[16];
    static Matrix4 *s_zero;
    static Matrix4 *s_identity;

    Matrix4(const float arr[16]);
    unsigned char equals(const Matrix4 *other);
    float determinant();
    float *toArray();
    Matrix4 *copy();
    Matrix4 *invert();
    void print() const;
    void multiply(const Matrix4 &other);
    static Matrix4 *rotationX(float angle);
    static Matrix4 *rotationY(float angle);
    static Matrix4 *rotationZ(float angle);
    static Matrix4 *rotationAxis(const Vector3 &axis, float angle);
    static Matrix4 *rotationXYZ(float angleX, float angleY, float angleZ);
    static Matrix4 *scaling(float scaleX, float scaleY, float scaleZ);
    static Matrix4 *translation(float tX, float tY, float tZ);
    static Matrix4 *lookAt(const Vector3 &cameraPosition, const Vector3 &targetPosition, const Vector3 &up);
    static Matrix4 *perspective(float fov, float ratio, float zNear, float zFar);
    static Vector3 transformCoordinate(const Vector3 &coord, const Matrix4 &transform);
    static Matrix4 *transpose(const Matrix4 &m);
    static Matrix4 *multiply(const Matrix4 &m1, const Matrix4 &m2);
    static Vector4 multiply(const Matrix4 &m, const Vector4 &v);
    static Matrix4 *identity();
    static Matrix4 *zero();
};

#endif
