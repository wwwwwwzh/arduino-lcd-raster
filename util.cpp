#include "matrix4.h"
#include "vector2.h"

Vector3 wgeCalculateTriangleNormal(const Vector3 &point1, const Vector3 &point2, const Vector3 &point3)
{
    Vector3 line12 = point2 - point1;
    Vector3 line13 = point3 - point1;
}