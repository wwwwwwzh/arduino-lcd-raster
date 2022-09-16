//#ifndef W_VECTOR_3_H
//#define W_VECTOR_3_H
//#include "vector4.h"
//#include <arduino.h>
//
//class Vector3
//{
//public:
//    union
//    {
//        float arr[3];
//        struct
//        {
//            float x;
//            float y;
//            float z;
//        };
//    };
//
//    static Vector3 *s_unitY;
//    static Vector3 *unitY();
//
//    Vector3(const float arr[3]);
//    Vector3(float x, float y, float z);
//    Vector3();
//
//    static Vector4 oneExtendedVector4(const Vector3 &v);
//    unsigned char equals(const Vector3 *other);
//    float length() const;
//    static Vector3 normalize(const Vector3 &v);
//    static Vector3 subtract(const Vector3 &v1, const Vector3 &v2);
//    static Vector3 cross(const Vector3 &v1, const Vector3 &v2);
//    static float dot(const Vector3 &v1, const Vector3 &v2);
//
//    Vector3 operator+(const Vector3 &v) const;
//    Vector3 operator-(const Vector3 &v) const;
//};
//
//#endif
