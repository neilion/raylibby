#ifndef RAYLIBBY_GRIDLINES3D_H
#define RAYLIBBY_GRIDLINES3D_H

#include <vector>
#include "raylib.h"

namespace plotObjects {

    class gridLines3D {
    public:
        gridLines3D();

        void setExtents(const Vector3 &min, const Vector3 &max);
        void computeActiveGridPlanes(const Vector3 &cameraOrigin, const Vector3 &viewVector);
        void setNumLines(size_t numLinesIn);
        void setLineColor(const Color &lineColorIn);

    private:
        size_t numLines;
        Color lineColor;

        bool positivePlaneActive[3];

        float xMin;
        float xMax;
        float yMin;
        float yMax;
        float zMin;
        float zMax;



    };

} // plotObjects

#endif //RAYLIBBY_GRIDLINES3D_H
