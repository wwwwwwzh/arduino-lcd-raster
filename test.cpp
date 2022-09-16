// #include <iostream>
// #include "fixed.h"
// using namespace std;
// using namespace numeric;
// #define fixed_t FixedFloat<16, 16>

// fixed_t f1(123.1333);
// fixed_t f2(3.2332);
// fixed_t f3 = f1 * f2;

// class Vector3
// {
// public:
//     union
//     {
//         float arr[3];
//         struct
//         {
//             float x;
//             float y;
//             float z;
//         };
//     };

//     Vector3(const float arr[3])
//     {
//         memcpy(this->arr, arr, sizeof(float) * 3);
//         delete arr;
//     };
//     Vector3(float x, float y, float z) : x(x), y(y), z(z){};
//     Vector3() : Vector3(0, 0, 0){};
// };

// // struct v
// // {
// //     union
// //     { // anonymous union
// //         struct
// //         {
// //             int i, j;
// //         }; // anonymous structure
// //         struct
// //         {
// //             long k, l;
// //         } w;
// //     };
// //     int m;
// // } v1;
// // struct Vector3
// // {
// //     union
// //     {
// //         int arr[3];
// //         struct
// //         {
// //             int x;
// //             int y;
// //             int z;
// //         };
// //     };

// //     Vector3(const int arr[3])
// //     {
// //         memcpy(this->arr, arr, sizeof(int) * 3);
// //         delete arr;
// //     }
// //     Vector3(int x, int y, int z) : x(x), y(y), z(z)
// //     {
// //     }
// //     Vector3()
// //     {
// //     }
// // };

// int main(int argc, char const *argv[])
// {
//     // Vector3 v31(1, 2, 3);
//     // Vector3 v32(4, 5, 6);

//     // Vector3 *rv1 = &v31;
//     // Vector3 *rv2 = &v32;
//     // Vector3 *temp = rv1;
//     // rv1 = rv2;
//     // rv2 = temp;

//     // printf("%d-%d-%d-%d", v31.x, rv1->x, v32.x, rv2->x);
//     Vector3 v = {1, 2, 4};
//     printf("%f-%f-%f", v.x, v.y, v.z);
//     return 0;
// }
//
// uint16_t interpolateRGB565(uint16_t min, uint16_t max, float gradient)
//{
//    uint8_t rmin = (min & 0b1111100000000000) >> 11;
//    uint8_t rmax = (max & 0b1111100000000000) >> 11;
//    uint8_t gmin = (min & 0b0000011111100000) >> 5;
//    uint8_t gmax = (max & 0b0000011111100000) >> 5;
//    uint8_t bmin = (min & 0b0000000000011111);
//    uint8_t bmax = (max & 0b0000000000011111);
//
//    uint16_t r = rmin + (rmax - rmin) * gradient;
//    uint16_t g = gmin + (gmax - gmin) * gradient;
//    uint16_t b = bmin + (bmax - bmin) * gradient;
//
//    return ((r << 11) + (g << 5) + b);
//}
//
// int main(int argc, char const *argv[])
// {

//     printf("%f", f3.to_float());

//     return 0;
// }
