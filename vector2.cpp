//#include "vector2.h"
//#include "math.h"
//
//Vector2::Vector2(float x, float y) : x(x), y(y) {}
//
//Vector2::Vector2() : x(0), y(0) {}
//
//float Vector2::length() const
//{
//    return sqrt(x * x + y * y);
//}
//
//unsigned char Vector2::equals(const Vector2 *other)
//{
//    return x == other->x && y == other->y;
//}
//
//Vector2 *Vector2::normalize(const Vector2 *v)
//{
//    float len = v->length();
//    if (len == 0)
//    {
//        return new Vector2();
//    }
//    float num = 1.0 / len;
//    float x = num * v->x;
//    float y = num * v->y;
//    return new Vector2(x, y);
//}
//
//Vector2 *Vector2::subtract(const Vector2 *v1, const Vector2 *v2)
//{
//    float x = v1->x - v2->x;
//    float y = v1->y - v2->y;
//    return new Vector2(x, y);
//}
//
//float Vector2::dot(const Vector2 *v1, const Vector2 *v2)
//{
//    return v1->x * v2->x + v1->y * v2->y;
//}
