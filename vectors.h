#ifndef W_VECTORS_H
#define W_VECTORS_H
#include <arduino.h>

class Vector2
{
public:
    float x;
    float y;

    Vector2(float x, float y);
    Vector2();

    unsigned char equals(const Vector2 *other);
    float length() const;
    static Vector2 *normalize(const Vector2 *v);
    static Vector2 *subtract(const Vector2 *v1, const Vector2 *v2);
    static float dot(const Vector2 *v1, const Vector2 *v2);
};

class Vector4;

class Vector3
{
public:
    union
    {
        float arr[3];
        struct
        {
            float x;
            float y;
            float z;
        };
    };

    static Vector3 *s_unitY;
    static Vector3 *unitY();

    Vector3(const float arr[3]);
    Vector3(float x, float y, float z);
    Vector3();

    static Vector4 oneExtendedVector4(const Vector3 &v);
    unsigned char equals(const Vector3 *other);
    float length() const;
    static Vector3 normalize(const Vector3 &v);
    static Vector3 subtract(const Vector3 &v1, const Vector3 &v2);
    static Vector3 cross(const Vector3 &v1, const Vector3 &v2);
    static float dot(const Vector3 &v1, const Vector3 &v2);

    Vector3 operator+(const Vector3 &v) const;
    Vector3 operator-(const Vector3 &v) const;
};

class Vector4
{
public:
    union
    {
        float arr[4];
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
    };

    Vector4(const float arr[4]);
    Vector4(float x, float y, float z, float w);
    Vector4();

    unsigned char equals(Vector4 *other);
    Vector3 toVector3();
};

#endif
