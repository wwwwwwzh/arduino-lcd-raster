#include "fixed.h"
#include "matrix4.h"
#include <arduino.h>
#include <bb_spi_lcd.h>

#define MESH_VIEW

using namespace numeric;
typedef FixedFloat<16, 16> fixed_t;

#define Z_BUFFER_T int
#define SCREEN_BUFFER_T uint16_t
#define COLOR_T SCREEN_BUFFER_T
#define LOW_MEM_INT_T int16_t
#define INT_MAX 2147483647

#ifndef _swap_int16_t
#define _swap_int16_t(a, b) \
  {                         \
    uint16_t t = a;         \
    a = b;                  \
    b = t;                  \
  }
#endif

extern Matrix4 tsMatrixForEfficiency;

// uint16_t swapRGB565(uint16_t src) {
//   uint16_t a = src & 0xff00 >> 8;
//   uint16_t b = src & 0x00ff;
//   _swap_int16_t(a, b);
//   return a + (b << 8);
// }

namespace SoftEngine
{
  class Camera
  {
  public:
    Vector3 position;
    Vector3 target;

    Camera(const Vector3 &position, const Vector3 &target) : position(position), target(target) {}
    Camera()
    {
      position = Vector3();
      target = Vector3();
    }
  };

  class Light
  {
  public:
    Vector3 position;
    Light(const Vector3 &position) : position(position){};
  };

  struct Face
  {
    int A;
    int B;
    int C;
    Vector3 normal;

    Face(int A = 0, int B = 0, int C = 0) : A(A), B(B), C(C) {}
  };

  struct Vertex
  {
    Vector3 position;
    uint16_t diffuse;
    Vertex(const Vector3 &position, const uint16_t diffuse) : position(position), diffuse(diffuse) {}
    Vertex()
    {
      diffuse = 0xffff;
    }
  };

  struct Vertex1P1D1N
  {
    Vector3 position;
    uint16_t diffuse;
    Vector3 faceNormal;
    Vertex1P1D1N(const Vector3 &position, const uint16_t diffuse, const Vector3 &faceNormal) : position(position), diffuse(diffuse), faceNormal(faceNormal) {}
  };

  class Mesh
  {
  public:
    int id;
    int vertexCount;
    int faceCount;
    Vertex *vertices;
    Face *faces;
    Vector3 position;
    Vector3 rotation;

    Mesh(int id, int vertexCount, int faceCount, Vertex &vertices, Face &faces, Vector3 &position, Vector3 &rotation) : id(id), vertexCount(vertexCount), faceCount(faceCount), vertices(&vertices), faces(&faces), position(position), rotation(rotation) {}
    Mesh(int id, int vertexCount, int faceCount, Vertex &vertices, Face &faces) : id(id), vertexCount(vertexCount), faceCount(faceCount), vertices(&vertices), faces(&faces)
    {
      position = Vector3();
      rotation = Vector3();
    }
  };

  class Device
  {
  private:
    SPILCD *lcd;
    Z_BUFFER_T zBuffer[12800];
    SCREEN_BUFFER_T screenBuffer[12800];
    COLOR_T currentTriangleBuffer;
    bool isCurrentTriangleShadingCalculated = false; 
    

    inline void resetZBuffer()
    {
      for (size_t i = 0; i < 12800; i++)
      {
        zBuffer[i] = INT_MAX;
      }
    }

    inline void resetScreenBuffer()
    {
//      for (size_t i = 0; i < 12800; i++)
//      {
//        screenBuffer[i] = 0b0010000100000100;
//      }
      memset(screenBuffer, 255, 12800 * sizeof(SCREEN_BUFFER_T));
    }

  public:
    LOW_MEM_INT_T width, height;

    Device(LOW_MEM_INT_T width, LOW_MEM_INT_T height, SPILCD *lcd) : width(width), height(height), lcd(lcd)
    {
      spilcdInit(lcd, LCD_ST7735S, FLAGS_SWAP_RB, 40000000, 10, 8, 9, A0, -1, -1, -1);
      clearBuffer();
      spilcdAllocBackbuffer(lcd);
      // lcd->setAntialias(1);
    }

    inline void clear()
    {
      // lcd->fillScreen(TFT_BLACK);
      resetZBuffer();
      resetScreenBuffer();
      display();
    }

    inline void clearBuffer()
    {
      resetZBuffer();
      resetScreenBuffer();
    }

    inline void display()
    {
      spilcdSetBuffer(lcd, screenBuffer);
      spilcdShowBuffer(lcd, 0, 0, width, height, DRAW_TO_LCD);
    }

    inline uint16_t calculateColor(Vertex1P1D1N &v1, Vertex1P1D1N &v2, Vertex1P1D1N &v3, uint16_t diffuse)
    {
      if (isCurrentTriangleShadingCalculated) {
        return currentTriangleBuffer;
      }
      Vector3 normal = v1.faceNormal;
      fixed_t normalX = normal.x;
      fixed_t normalY = normal.y;
      fixed_t normalZ = normal.z;

      // Vector3 light(-1, 0, 1);

      // light = Vector3::normalize(light);
      // fixed_t lightX = light.x;
      // fixed_t lightY = light.y;
      // fixed_t lightZ = light.z;

      // fixed_t lightIntensity = Vector3::dot(normal, light);
      fixed_t light = 0.70710678;
      fixed_t lightIntensity = -light * normalX + light * normalZ;
      
      if (lightIntensity < 0.01)
      {
        currentTriangleBuffer = 0b0001000010000010;
        isCurrentTriangleShadingCalculated = true;
        return 0b0001000010000010;
      }
      // Vector3 reflectDirection(normal.x * lightIntensity * 2 - light.x, normal.y * lightIntensity * 2 - light.y, normal.z * lightIntensity * 2 - light.z);
//      fixed_t reflectX = normalX * lightIntensity * 2 + light;
//      fixed_t reflectY = normalY * lightIntensity * 2;
      fixed_t reflectZ = normalZ * lightIntensity * 2 - light;

      // reflectDirection = Vector3::normalize(reflectDirection);
//      fixed_t denominatorF = reflectX * reflectX + reflectY * reflectY + reflectZ * reflectZ;
//      float denominator = denominatorF.to_float();
//      denominator = sqrt(denominator);
//      Serial.println(denominator);
      // reflectX = reflectX / denominator;
      // reflectY = reflectY / denominator;
//      reflectZ = reflectZ / (fixed_t)denominator;
      // Vector3 viewDirection(0,0,1);
      // Vector3::dot(viewDirection, reflectDirection);
      // fixed_t specularIntensity = reflectDirection.z;
      fixed_t specularIntensity = reflectZ;

      uint8_t dr = (diffuse & 0b1111100000000000) >> 11;
      uint8_t dg = (diffuse & 0b0000011111100000) >> 5;
      uint8_t db = (diffuse & 0b0000000000011111);

      fixed_t temp_dr;
      fixed_t temp_dg;
      fixed_t temp_db;
      if (dr > 1) {
        temp_dr = (fixed_t)dr * lightIntensity;
      }
      if (dg > 1) {
        temp_dg = (fixed_t)dg * lightIntensity;
      }
      if (db > 1) {
        temp_db = (fixed_t)db * lightIntensity;
      }

      uint16_t reconstructedRBGColor = 0;
      
      if (specularIntensity < 0.1) {
        reconstructedRBGColor = ((temp_dr.to_uint() << 11) + (temp_dg.to_uint() << 5) + temp_db.to_uint());
      } else {
        specularIntensity = specularIntensity * specularIntensity * specularIntensity;
        fixed_t specularXZ = specularIntensity * 31;
        fixed_t specularY = specularIntensity * 63;
        uint8_t r = (temp_dr.to_uint() + specularXZ.to_uint()) ;
        uint8_t g = (temp_dg.to_uint() + specularY.to_uint());
        uint8_t b = (temp_db.to_uint() + specularXZ.to_uint());
        if (r > 31) { r = 31; };
        if (g > 63) { g = 31; };
        if (b > 31) { b = 31; };
        reconstructedRBGColor = ((r << 11) + ( g << 5) + b);
      }
      // Serial.println(diffuse);

      currentTriangleBuffer = reconstructedRBGColor;
      isCurrentTriangleShadingCalculated = true;
      return reconstructedRBGColor;
    }

    void drawPoint(const Vector3 &point, Vertex1P1D1N &v1, Vertex1P1D1N &v2, Vertex1P1D1N &v3, uint16_t diffuse)
    {
      LOW_MEM_INT_T x = point.x;
      LOW_MEM_INT_T y = point.y;
      // Serial.println(x);
//      if (x < 0 || y < 0 || x >= width || y >= height)
//        return;

      Z_BUFFER_T z = point.z;

      int index = x + y * width;
      if (z > zBuffer[index])
      {
        return;
      }
      zBuffer[index] = z;
      uint16_t color = calculateColor(v1, v2, v3, diffuse);
      // Serial.println(color);
      // screenBuffer[index] = color;
      spilcdSetPixel(lcd, x, y, color, DRAW_TO_RAM);
    }

    fixed_t interpolate(fixed_t min, fixed_t max, fixed_t gradient)
    {
      return min + (max - min) * gradient;
    }

    uint16_t interpolateRGB565(uint16_t min, uint16_t max, float gradient)
    {
      uint8_t rmin = (min & 0b1111100000000000) >> 11;
      uint8_t rmax = (max & 0b1111100000000000) >> 11;
      uint8_t gmin = (min & 0b0000011111100000) >> 5;
      uint8_t gmax = (max & 0b0000011111100000) >> 5;
      uint8_t bmin = (min & 0b0000000000011111);
      uint8_t bmax = (max & 0b0000000000011111);

      uint16_t r = rmin + (rmax - rmin) * gradient;
      uint16_t g = gmin + (gmax - gmin) * gradient;
      uint16_t b = bmin + (bmax - bmin) * gradient;

      return ((r << 11) + (g << 5) + b);
    }

    void drawScanLine(LOW_MEM_INT_T y, Vertex1P1D1N &v1, Vertex1P1D1N &v2, Vertex1P1D1N &v3, Vertex1P1D1N &v4)
    {
      Vector3 point1 = v1.position;
      Vector3 point2 = v2.position;
      Vector3 point3 = v3.position;
      Vector3 point4 = v4.position;

      fixed_t gradient1 = point1.y != point2.y ? (y - point1.y) / (point2.y - point1.y) : 1;
      fixed_t gradient2 = point3.y != point4.y ? (y - point3.y) / (point4.y - point3.y) : 1;

      LOW_MEM_INT_T sx = interpolate(point1.x, point2.x, gradient1).to_uint();
      LOW_MEM_INT_T ex = interpolate(point3.x, point4.x, gradient2).to_uint();

      uint16_t sDiffuse = interpolateRGB565(v1.diffuse, v2.diffuse, gradient1.to_float());
      uint16_t eDiffuse = interpolateRGB565(v3.diffuse, v4.diffuse, gradient2.to_float());

      if (sx > ex)
      {
        LOW_MEM_INT_T temp = sx;
        sx = ex;
        ex = temp;
      }
      
      // starting Z & ending Z
      fixed_t z1 = interpolate(point1.z, point2.z, gradient1.to_float());
      fixed_t z2 = interpolate(point3.z, point4.z, gradient2.to_float());

      // use float or this: (x - sx) / lineLength will be an int
      fixed_t lineLength = ex - sx;
      for (int x = sx; x < ex; x++)
      {
        fixed_t gradient = (fixed_t)(x - sx) / lineLength;
        Z_BUFFER_T zPixel = interpolate(z1, z2, gradient).to_int();

        uint16_t diffuse = interpolateRGB565(sDiffuse, eDiffuse, gradient.to_float());

        // Serial.println(diffuse);
        drawPoint(Vector3(x, y, zPixel), v1, v2, v3, v1.diffuse);
      }
    }

    void drawTriangle(Vertex1P1D1N *v1, Vertex1P1D1N *v2, Vertex1P1D1N *v3)
    {
      // change order so p1 is at top and p3 at bottom

      if (v1->position.y > v2->position.y)
      {
        Vertex1P1D1N *temp = v2;
        v2 = v1;
        v1 = temp;
      }
      if (v2->position.y > v3->position.y)
      {
        Vertex1P1D1N *temp = v2;
        v2 = v3;
        v3 = temp;
      }
      if (v1->position.y > v2->position.y)
      {
        Vertex1P1D1N *temp = v2;
        v2 = v1;
        v1 = temp;
      }

      Vector3 *imageCoordinate1 = &v1->position;
      Vector3 *imageCoordinate2 = &v2->position;
      Vector3 *imageCoordinate3 = &v3->position;

      // inverse slopes
      float dP1P2;
      float dP1P3;

      // Computing slopes
      if (imageCoordinate2->y - imageCoordinate1->y > 0)
      {
        dP1P2 = (imageCoordinate2->x - imageCoordinate1->x) / (imageCoordinate2->y - imageCoordinate1->y);
      }
      else
      {
        dP1P2 = 0;
      }

      if (imageCoordinate3->y - imageCoordinate1->y > 0)
      {
        dP1P3 = (imageCoordinate3->x - imageCoordinate1->x) / (imageCoordinate3->y - imageCoordinate1->y);
      }
      else
      {
        dP1P3 = 0;
      }

      // P2 on the right
      if (dP1P2 > dP1P3)
      {
        for (int y = imageCoordinate1->y; y <= imageCoordinate3->y; y++)
        {
          if (y < imageCoordinate2->y)
          {
            drawScanLine(y, *v1, *v3, *v1, *v2);
          }
          else
          {
            drawScanLine(y, *v1, *v3, *v2, *v3);
          }
        }
      }
      // p2 on the left
      else
      {
        for (int y = imageCoordinate1->y; y <= imageCoordinate3->y; y++)
        {
          if (y < imageCoordinate2->y)
          {
            drawScanLine(y, *v1, *v2, *v1, *v3);
          }
          else
          {
            drawScanLine(y, *v2, *v3, *v1, *v3);
          }
        }
      }
    }

    void project(Vertex1P1D1N *vertex, const Matrix4 &transMat)
    {
      Vector3 imageCoordinate = Matrix4::transformCoordinate(vertex->position, transMat);
      LOW_MEM_INT_T x = imageCoordinate.x * width + (width >> 1);
      LOW_MEM_INT_T y = -imageCoordinate.y * height + (height >> 1);
      Z_BUFFER_T z = imageCoordinate.z * INT_MAX;
      vertex->position = Vector3(x, y, z);
    }

    // The main method of the engine that re-compute each vertex projection
    // during each frame
    void render(const Camera &camera, const Mesh *meshes, const uint8_t meshCount, const Light *lights, const uint8_t lightCount)
    {
      // Serial.println("SD");
      Matrix4 *viewMatrix = Matrix4::lookAt(camera.position, camera.target, *Vector3::unitY());
      // viewMatrix->print();
      Matrix4 *projectionMatrix = Matrix4::perspective(0.78f, (float)width / height, 20, 100);
      // projectionMatrix->print();
      for (uint8_t mi = 0; mi < meshCount; mi++)
      {
        const Mesh &mesh = meshes[mi];
        // Beware to apply rotation before translation
        Matrix4 *worldRotationMatrix = Matrix4::rotationXYZ(mesh.rotation.x, mesh.rotation.y, mesh.rotation.z);
        // worldRotationMatrix->print();
        //        Matrix4 *worldTranslationMatrix = Matrix4::translation(mesh.position.x, mesh.position.y, mesh.position.z);
        //        Matrix4 *worldScalingMatrix = Matrix4::scaling(8, 8, 8);
        //        Matrix4 *worldMatrix = Matrix4::multiply(*worldRotationMatrix, *worldTranslationMatrix);
        //        worldMatrix = Matrix4::multiply(*worldMatrix, *worldScalingMatrix);
        // worldMatrix->print();

        Matrix4 *worldMatrix = Matrix4::multiply(*worldRotationMatrix, tsMatrixForEfficiency);

        Matrix4 *transformMatrix = worldMatrix;
        transformMatrix->multiply(*viewMatrix);
        transformMatrix->multiply(*projectionMatrix);
        // transformMatrix->print();

        for (int fi = 0; fi < mesh.faceCount; fi++)
        {
          const Face face = mesh.faces[fi];

          Vertex v1 = mesh.vertices[face.A];
          Vertex v2 = mesh.vertices[face.B];
          Vertex v3 = mesh.vertices[face.C];

          Vector3 normal = Vector3::cross(v2.position - v1.position, v3.position - v1.position);
          normal = Vector3::normalize(normal);

          Vector4 normalInWorldCoord = Matrix4::multiply(*worldRotationMatrix, Vector3::oneExtendedVector4(normal));
          // Serial.print("face:");
          //       Serial.println(fi);
          //                 Serial.print("x");
          //       Serial.println(normalInWorldCoord.x);
          //       Serial.print("y");
          //       Serial.println(normalInWorldCoord.y);
          //       Serial.print("z");
          //       Serial.println(normalInWorldCoord.z);

          Vertex1P1D1N v1P1D1N1(v1.position, v1.diffuse, normalInWorldCoord.toVector3());
          Vertex1P1D1N v1P1D1N2(v2.position, v2.diffuse, normalInWorldCoord.toVector3());
          Vertex1P1D1N v1P1D1N3(v3.position, v3.diffuse, normalInWorldCoord.toVector3());

          project(&v1P1D1N1, *transformMatrix);
          project(&v1P1D1N2, *transformMatrix);
          project(&v1P1D1N3, *transformMatrix);

          // now v1P1D1Nx contains vertex position in image coordinate, diffuse, and face normal
          #ifdef MESH_VIEW
          spilcdDrawLine(lcd, v1P1D1N1.position.x, v1P1D1N1.position.y, v1P1D1N2.position.x, v1P1D1N2.position.y, 0, DRAW_TO_RAM);
          spilcdDrawLine(lcd, v1P1D1N3.position.x, v1P1D1N3.position.y, v1P1D1N2.position.x, v1P1D1N2.position.y, 0, DRAW_TO_RAM);
          spilcdDrawLine(lcd, v1P1D1N1.position.x, v1P1D1N2.position.y, v1P1D1N3.position.x, v1P1D1N3.position.y, 0, DRAW_TO_RAM);
          #else
          isCurrentTriangleShadingCalculated = false;
          drawTriangle(&v1P1D1N1, &v1P1D1N2, &v1P1D1N3);
          #endif
        }
        delete worldRotationMatrix;
        //        delete worldScalingMatrix;
        //        delete worldTranslationMatrix;
        delete worldMatrix;
      }

      delete viewMatrix;
      delete projectionMatrix;
    }
  };
}
