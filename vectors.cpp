#include "vectors.h"
#include "math.h"

Vector2::Vector2(float x, float y) : x(x), y(y) {}

Vector2::Vector2() : x(0), y(0) {}

float Vector2::length() const
{
    return sqrt(x * x + y * y);
}

unsigned char Vector2::equals(const Vector2 *other)
{
    return x == other->x && y == other->y;
}

Vector2 *Vector2::normalize(const Vector2 *v)
{
    float len = v->length();
    if (len == 0)
    {
        return new Vector2();
    }
    float num = 1.0 / len;
    float x = num * v->x;
    float y = num * v->y;
    return new Vector2(x, y);
}

Vector2 *Vector2::subtract(const Vector2 *v1, const Vector2 *v2)
{
    float x = v1->x - v2->x;
    float y = v1->y - v2->y;
    return new Vector2(x, y);
}

float Vector2::dot(const Vector2 *v1, const Vector2 *v2)
{
    return v1->x * v2->x + v1->y * v2->y;
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------

Vector3 *Vector3::s_unitY;
Vector3::Vector3(const float arr[3])
{
    memcpy(this->arr, arr, sizeof(float) * 3);
}

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

Vector3::Vector3()
{
    memset(arr, 0, sizeof(float) * 3);
}

Vector3 *Vector3::unitY()
{
    if (s_unitY == NULL)
    {
        s_unitY = new Vector3(0, 1, 0);
    }
    return s_unitY;
}

Vector4 Vector3::oneExtendedVector4(const Vector3 &v)
{
    return Vector4(v.x, v.y, v.z, 1);
}

float Vector3::length() const
{
    return sqrt(arr[0] * arr[0] + arr[1] * arr[1] + arr[2] * arr[2]);
}

unsigned char Vector3::equals(const Vector3 *other)
{
    return other->arr[0] == this->arr[0] && other->arr[1] == this->arr[1] && other->arr[2] == this->arr[2];
}

Vector3 Vector3::normalize(const Vector3 &v)
{
    float len = v.length();
    if (len == 0)
    {
        return Vector3();
    }
    float num = 1.0 / len;
    float x = num * v.x;
    float y = num * v.y;
    float z = num * v.z;
    return Vector3(x, y, z);
}

Vector3 Vector3::subtract(const Vector3 &v1, const Vector3 &v2)
{
    float x = v1.x - v2.x;
    float y = v1.y - v2.y;
    float z = v1.z - v2.z;
    return Vector3(x, y, z);
}

Vector3 Vector3::cross(const Vector3 &v1, const Vector3 &v2)
{
    float x = v1.y * v2.z - v1.z * v2.y;
    float y = v1.z * v2.x - v1.x * v2.z;
    float z = v1.x * v2.y - v1.y * v2.x;
    return Vector3(x, y, z);
}

float Vector3::dot(const Vector3 &v1, const Vector3 &v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 Vector3::operator+(const Vector3 &v) const
{
    float x = v.x + this->x;
    float y = v.y + this->y;
    float z = v.z + this->z;
    return Vector3(x, y, z);
}

Vector3 Vector3::operator-(const Vector3 &v) const
{
    float x = this->x - v.x;
    float y = this->y - v.y;
    float z = this->z - v.z;
    return Vector3(x, y, z);
}

//------------------------------------------------------------------------
//------------------------------------------------------------------------
//------------------------------------------------------------------------

Vector4::Vector4(const float arr[4])
{
    memcpy(this->arr, arr, sizeof(float) * 4);
}

Vector4::Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

Vector4::Vector4()
{
    memset(arr, 0, sizeof(float) * 4);
}

class Vector3 Vector4::toVector3()
{
    return Vector3(x, y, z);
}
