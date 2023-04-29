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

        void plot();

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

        float dx;
        float dy;
        float dz;

        void drawXYLines();
        void drawXZLines();
        void drawYXLines();
        void drawYZLines();
        void drawZXLines();
        void drawZYLines();


        // What else does this class need? Num line and auto density is based on the extents... what else?




    };

} // plotObjects

#endif //RAYLIBBY_GRIDLINES3D_H
