#include "matrix4.h"

Matrix4 *Matrix4::s_zero;
Matrix4 *Matrix4::s_identity;

Matrix4::Matrix4(const float arr[16])
{
    memcpy(this->arr, arr, sizeof(float) * 16);
}

float *Matrix4::toArray()
{
    return arr;
}

void Matrix4::print() const
{
}

Matrix4 *Matrix4::zero()
{
    if (s_zero == NULL)
    {
        float temp[16] = {};

        s_zero = new Matrix4(temp);
    }
    return s_zero;
}

Matrix4 *Matrix4::identity()
{
    if (s_identity == NULL)
    {
        float temp[16] = {};

        temp[0] = 1;
        temp[5] = 1;
        temp[10] = 1;
        temp[15] = 1;

        s_identity = new Matrix4(temp);
    }
    return s_identity;
}

Matrix4 *Matrix4::copy()
{
    float temp[16] = {};
    for (size_t i = 0; i < 16; i++)
    {
        temp[i] = arr[i];
    }
    return new Matrix4(temp);
}
void Matrix4::multiply(const Matrix4 &other)
{
    float temp[16];
    temp[0] = arr[0] * other.arr[0] + arr[1] * other.arr[4] + arr[2] * other.arr[8] + arr[3] * other.arr[12];
    temp[1] = arr[0] * other.arr[1] + arr[1] * other.arr[5] + arr[2] * other.arr[9] + arr[3] * other.arr[13];
    temp[2] = arr[0] * other.arr[2] + arr[1] * other.arr[6] + arr[2] * other.arr[10] + arr[3] * other.arr[14];
    temp[3] = arr[0] * other.arr[3] + arr[1] * other.arr[7] + arr[2] * other.arr[11] + arr[3] * other.arr[15];
    temp[4] = arr[4] * other.arr[0] + arr[5] * other.arr[4] + arr[6] * other.arr[8] + arr[7] * other.arr[12];
    temp[5] = arr[4] * other.arr[1] + arr[5] * other.arr[5] + arr[6] * other.arr[9] + arr[7] * other.arr[13];
    temp[6] = arr[4] * other.arr[2] + arr[5] * other.arr[6] + arr[6] * other.arr[10] + arr[7] * other.arr[14];
    temp[7] = arr[4] * other.arr[3] + arr[5] * other.arr[7] + arr[6] * other.arr[11] + arr[7] * other.arr[15];
    temp[8] = arr[8] * other.arr[0] + arr[9] * other.arr[4] + arr[10] * other.arr[8] + arr[11] * other.arr[12];
    temp[9] = arr[8] * other.arr[1] + arr[9] * other.arr[5] + arr[10] * other.arr[9] + arr[11] * other.arr[13];
    temp[10] = arr[8] * other.arr[2] + arr[9] * other.arr[6] + arr[10] * other.arr[10] + arr[11] * other.arr[14];
    temp[11] = arr[8] * other.arr[3] + arr[9] * other.arr[7] + arr[10] * other.arr[11] + arr[11] * other.arr[15];
    temp[12] = arr[12] * other.arr[0] + arr[13] * other.arr[4] + arr[14] * other.arr[8] + arr[15] * other.arr[12];
    temp[13] = arr[12] * other.arr[1] + arr[13] * other.arr[5] + arr[14] * other.arr[9] + arr[15] * other.arr[13];
    temp[14] = arr[12] * other.arr[2] + arr[13] * other.arr[6] + arr[14] * other.arr[10] + arr[15] * other.arr[14];
    temp[15] = arr[12] * other.arr[3] + arr[13] * other.arr[7] + arr[14] * other.arr[11] + arr[15] * other.arr[15];
    memcpy(arr, temp, sizeof(float) * 16);
}
Matrix4 *Matrix4::multiply(const Matrix4 &m1, const Matrix4 &m2)
{
    float temp[16];
    temp[0] = m1.arr[0] * m2.arr[0] + m1.arr[1] * m2.arr[4] + m1.arr[2] * m2.arr[8] + m1.arr[3] * m2.arr[12];
    temp[1] = m1.arr[0] * m2.arr[1] + m1.arr[1] * m2.arr[5] + m1.arr[2] * m2.arr[9] + m1.arr[3] * m2.arr[13];
    temp[2] = m1.arr[0] * m2.arr[2] + m1.arr[1] * m2.arr[6] + m1.arr[2] * m2.arr[10] + m1.arr[3] * m2.arr[14];
    temp[3] = m1.arr[0] * m2.arr[3] + m1.arr[1] * m2.arr[7] + m1.arr[2] * m2.arr[11] + m1.arr[3] * m2.arr[15];
    temp[4] = m1.arr[4] * m2.arr[0] + m1.arr[5] * m2.arr[4] + m1.arr[6] * m2.arr[8] + m1.arr[7] * m2.arr[12];
    temp[5] = m1.arr[4] * m2.arr[1] + m1.arr[5] * m2.arr[5] + m1.arr[6] * m2.arr[9] + m1.arr[7] * m2.arr[13];
    temp[6] = m1.arr[4] * m2.arr[2] + m1.arr[5] * m2.arr[6] + m1.arr[6] * m2.arr[10] + m1.arr[7] * m2.arr[14];
    temp[7] = m1.arr[4] * m2.arr[3] + m1.arr[5] * m2.arr[7] + m1.arr[6] * m2.arr[11] + m1.arr[7] * m2.arr[15];
    temp[8] = m1.arr[8] * m2.arr[0] + m1.arr[9] * m2.arr[4] + m1.arr[10] * m2.arr[8] + m1.arr[11] * m2.arr[12];
    temp[9] = m1.arr[8] * m2.arr[1] + m1.arr[9] * m2.arr[5] + m1.arr[10] * m2.arr[9] + m1.arr[11] * m2.arr[13];
    temp[10] = m1.arr[8] * m2.arr[2] + m1.arr[9] * m2.arr[6] + m1.arr[10] * m2.arr[10] + m1.arr[11] * m2.arr[14];
    temp[11] = m1.arr[8] * m2.arr[3] + m1.arr[9] * m2.arr[7] + m1.arr[10] * m2.arr[11] + m1.arr[11] * m2.arr[15];
    temp[12] = m1.arr[12] * m2.arr[0] + m1.arr[13] * m2.arr[4] + m1.arr[14] * m2.arr[8] + m1.arr[15] * m2.arr[12];
    temp[13] = m1.arr[12] * m2.arr[1] + m1.arr[13] * m2.arr[5] + m1.arr[14] * m2.arr[9] + m1.arr[15] * m2.arr[13];
    temp[14] = m1.arr[12] * m2.arr[2] + m1.arr[13] * m2.arr[6] + m1.arr[14] * m2.arr[10] + m1.arr[15] * m2.arr[14];
    temp[15] = m1.arr[12] * m2.arr[3] + m1.arr[13] * m2.arr[7] + m1.arr[14] * m2.arr[11] + m1.arr[15] * m2.arr[15];
    return new Matrix4(temp);
}
Vector4 Matrix4::multiply(const Matrix4 &m, const Vector4 &v)
{
    float x = m.arr[0] * v.arr[0] + m.arr[4] * v.arr[1] + m.arr[8] * v.arr[2] + m.arr[12] * v.arr[3];
    float y = m.arr[1] * v.arr[0] + m.arr[5] * v.arr[1] + m.arr[9] * v.arr[2] + m.arr[13] * v.arr[3];
    float z = m.arr[2] * v.arr[0] + m.arr[6] * v.arr[1] + m.arr[10] * v.arr[2] + m.arr[14] * v.arr[3];
    float w = m.arr[3] * v.arr[0] + m.arr[7] * v.arr[1] + m.arr[11] * v.arr[2] + m.arr[15] * v.arr[3];
    return Vector4(x, y, z, w);
}

Matrix4 *Matrix4::rotationX(float angle)
{
    float temp[16] = {};

    float s = sin(angle);
    float c = cos(angle);
    temp[0] = 1.0;
    temp[15] = 1.0;
    temp[5] = c;
    temp[10] = c;
    temp[9] = -s;
    temp[6] = s;
    return new Matrix4(temp);
}
Matrix4 *Matrix4::rotationY(float angle)
{
    float temp[16] = {};

    float s = sin(angle);
    float c = cos(angle);
    temp[5] = 1.0;
    temp[15] = 1.0;
    temp[0] = c;
    temp[2] = -s;
    temp[8] = s;
    temp[10] = c;
    return new Matrix4(temp);
}
Matrix4 *Matrix4::rotationZ(float angle)
{
    float temp[16] = {};

    float s = sin(angle);
    float c = cos(angle);
    temp[10] = 1.0;
    temp[15] = 1.0;
    temp[0] = c;
    temp[1] = s;
    temp[4] = -s;
    temp[5] = c;
    return new Matrix4(temp);
}
Matrix4 *Matrix4::rotationAxis(const Vector3 &axis, float angle)
{
    float s = sin(-angle);
    float c = cos(-angle);
    float c1 = 1 - c;
    Vector3 normAxis = Vector3::normalize(axis);
    float temp[16] = {};

    temp[0] = (normAxis.x * normAxis.x) * c1 + c;
    temp[1] = (normAxis.x * normAxis.y) * c1 - (normAxis.z * s);
    temp[2] = (normAxis.x * normAxis.z) * c1 + (normAxis.y * s);
    temp[3] = 0.0;
    temp[4] = (normAxis.y * normAxis.x) * c1 + (normAxis.z * s);
    temp[5] = (normAxis.y * normAxis.y) * c1 + c;
    temp[6] = (normAxis.y * normAxis.z) * c1 - (normAxis.x * s);
    temp[7] = 0.0;
    temp[8] = (normAxis.z * normAxis.x) * c1 - (normAxis.y * s);
    temp[9] = (normAxis.z * normAxis.y) * c1 + (normAxis.x * s);
    temp[10] = (normAxis.z * normAxis.z) * c1 + c;
    temp[11] = 0.0;
    temp[15] = 1.0;

    return new Matrix4(temp);
}
Matrix4 *Matrix4::rotationXYZ(float angleX, float angleY, float angleZ)
{
    Matrix4 *zMatrix = Matrix4::rotationZ(angleZ);
    Matrix4 *xMatrix = Matrix4::rotationX(angleX);
    Matrix4 *yMatrix = Matrix4::rotationY(angleY);
    zMatrix->multiply(*xMatrix);
    zMatrix->multiply(*yMatrix);
    delete xMatrix;
    delete yMatrix;
    return zMatrix;
}
Matrix4 *Matrix4::scaling(float scaleX, float scaleY, float scaleZ)
{
    float temp[16] = {};
    temp[0] = scaleX;
    temp[5] = scaleY;
    temp[10] = scaleZ;
    temp[15] = 1.0;
    return new Matrix4(temp);
}
Matrix4 *Matrix4::translation(float tX, float tY, float tZ)
{
    float temp[16] = {};

    temp[0] = 1;
    temp[5] = 1;
    temp[10] = 1;
    temp[15] = 1;
    temp[12] = tX;
    temp[13] = tY;
    temp[14] = tZ;
    return new Matrix4(temp);
}

Matrix4 *Matrix4::lookAt(const Vector3 &cameraPosition, const Vector3 &targetPosition, const Vector3 &up)
{
    float temp[16] = {};
    Vector3 zAxis = targetPosition - cameraPosition;
    Vector3 zAxisNorm = Vector3::normalize(zAxis);
    Vector3 xAxis = Vector3::cross(up, zAxis);
    Vector3 xAxisNorm = Vector3::normalize(xAxis);
    Vector3 yAxis = Vector3::cross(zAxis, xAxis);
    Vector3 yAxisNorm = Vector3::normalize(yAxis);

    float ex = -Vector3::dot(xAxisNorm, cameraPosition);
    float ey = -Vector3::dot(yAxisNorm, cameraPosition);
    float ez = -Vector3::dot(zAxisNorm, cameraPosition);

    temp[0] = xAxisNorm.x;
    temp[1] = yAxisNorm.x;
    temp[2] = zAxisNorm.x;
    temp[4] = xAxisNorm.y;
    temp[5] = yAxisNorm.y;
    temp[6] = zAxisNorm.y;
    temp[8] = xAxisNorm.z;
    temp[9] = yAxisNorm.z;
    temp[10] = zAxisNorm.z;
    temp[12] = ex;
    temp[13] = ey;
    temp[14] = ez;
    temp[15] = 1;

    return new Matrix4(temp);
}

Matrix4 *Matrix4::perspective(float fov, float ratio, float zNear, float zFar)
{
    float temp[16] = {};
    float tangent = 1.0 / (tan(fov * 0.5));
    temp[0] = tangent / ratio;
    temp[5] = tangent;
    temp[10] = zFar / (zFar - zNear);
    temp[11] = 1.0;
    temp[14] = (zNear * zFar) / (zNear - zFar);
    return new Matrix4(temp);
}

Vector3 Matrix4::transformCoordinate(const Vector3 &coord, const Matrix4 &transform)
{
    float x = (coord.arr[0] * transform.arr[0]) + (coord.arr[1] * transform.arr[4]) + (coord.arr[2] * transform.arr[8]) + transform.arr[12];
    float y = (coord.arr[0] * transform.arr[1]) + (coord.arr[1] * transform.arr[5]) + (coord.arr[2] * transform.arr[9]) + transform.arr[13];
    float z = (coord.arr[0] * transform.arr[2]) + (coord.arr[1] * transform.arr[6]) + (coord.arr[2] * transform.arr[10]) + transform.arr[14];
    float w = (coord.arr[0] * transform.arr[3]) + (coord.arr[1] * transform.arr[7]) + (coord.arr[2] * transform.arr[11]) + transform.arr[15];
    return Vector3(x / w, y / w, z / w);
};

Matrix4 *Matrix4::transpose(const Matrix4 &m)
{
    float temp[16] = {};
    temp[0] = m.arr[0];
    temp[1] = m.arr[4];
    temp[2] = m.arr[8];
    temp[3] = m.arr[12];
    temp[4] = m.arr[1];
    temp[5] = m.arr[5];
    temp[6] = m.arr[9];
    temp[7] = m.arr[13];
    temp[8] = m.arr[2];
    temp[9] = m.arr[6];
    temp[10] = m.arr[10];
    temp[11] = m.arr[14];
    temp[12] = m.arr[3];
    temp[13] = m.arr[7];
    temp[14] = m.arr[11];
    temp[15] = m.arr[15];
    return new Matrix4(temp);
}
