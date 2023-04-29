//
// Created by neilm on 4/18/2023.
//

#include "gridLines3D.h"
#include "extensionsVector3.h"
#include <cmath>

enum AxisOrder {
    X = 0,
    Y = 1,
    Z = 2
};

namespace plotObjects {

    gridLines3D::gridLines3D() {
        numLines = 5;
        lineColor = LIGHTGRAY;
        positivePlaneActive[0] = false;
        positivePlaneActive[1] = false;
        positivePlaneActive[2] = false;

        Vector3 minCorner{-1, -1 , -1};
        Vector3 maxCorner = -1 * minCorner;

        xMin = 0;
        xMax = 0;
        yMin = 0;
        yMax = 0;
        zMin = 0;
        zMax = 0;
        setExtents(minCorner, maxCorner);
    }


    void gridLines3D::setExtents(const Vector3 &min, const Vector3 &max) {
        xMin = min.x;
        xMax = max.x;
        yMin = min.y;
        yMax = max.y;
        zMin = min.z;
        zMax = max.z;
    }


    void gridLines3D::computeActiveGridPlanes(const Vector3 &cameraOrigin, const Vector3 &viewVector) {
        // Determine if the camera view vector intersects the positive (greater) or negative (lesser) frame last.
        positivePlaneActive[X] = viewVector.x <= 0;
        positivePlaneActive[Y] = viewVector.y <= 0;
        positivePlaneActive[Z] = viewVector.z <= 0;
    }

    void gridLines3D::setNumLines(size_t numLinesIn) {
        numLinesIn = fmax(numLinesIn, 2u);
        this->numLines = numLinesIn;
    }

    void gridLines3D::setLineColor(const Color &lineColorIn) {
        this->lineColor = lineColorIn;
    }

    void gridLines3D::plot() {

        dx = (xMax - xMin) / ((float)(numLines - 1u));
        dy = (yMax - yMin) / ((float)(numLines - 1u));
        dz = (zMax - zMin) / ((float)(numLines - 1u));

        drawXYLines();
        drawXZLines();
        drawYXLines();
        drawYZLines();
        drawZXLines();
        drawZYLines();
    }

    void gridLines3D::drawXYLines() {
        // Find the start and end points of the x lines
        float xPlaneCoord = positivePlaneActive[X] ? xMax : xMin;
        for (int i = 0; i < numLines; ++i) {
            // Get Y values in this loop
            float yPlaneCoord = yMin + static_cast<float>(i) * dy;
            // Lines of constant xz
            for (int j = 0; j < numLines; ++j) {
                Vector3 p1 {xPlaneCoord, yPlaneCoord, zMin};
                Vector3 p2 {xPlaneCoord, yPlaneCoord, zMax};
                DrawLine3D(p1, p2, lineColor);
            }
        }
    }

    void gridLines3D::drawXZLines() {
        float xPlaneCoord = positivePlaneActive[X] ? xMax : xMin;
        for (int i = 0; i < numLines; ++i) {
            // Get Y values in this loop
            float zPlaneCoord = zMin + static_cast<float>(i) * dz;
            // Lines of constant xz
            for (int j = 0; j < numLines; ++j) {
                Vector3 p1 {xPlaneCoord, yMin, zPlaneCoord};
                Vector3 p2 {xPlaneCoord, yMax, zPlaneCoord};
                DrawLine3D(p1, p2, lineColor);
            }
        }
    }

    void gridLines3D::drawYXLines() {
        float yPlaneCoord = positivePlaneActive[Y] ? yMax : yMin;
        for (int i = 0; i < numLines; ++i) {
            // Get X values in this loop
            float xPlaneCoord = xMin + static_cast<float>(i) * dx;
            // Lines of constant yx
            for (int j = 0; j < numLines; ++j) {
                Vector3 p1 {xPlaneCoord, yPlaneCoord, zMin};
                Vector3 p2 {xPlaneCoord, yPlaneCoord, zMax};
                DrawLine3D(p1, p2, lineColor);
            }
        }
    }

    void gridLines3D::drawYZLines() {
        float yPlaneCoord = positivePlaneActive[Y] ? yMax : yMin;
        for (int i = 0; i < numLines; ++i) {
            // Get Z values in this loop
            float zPlaneCoord = zMin + static_cast<float>(i) * dz;
            // Lines of constant yz
            for (int j = 0; j < numLines; ++j) {
                Vector3 p1 {xMin, yPlaneCoord, zPlaneCoord};
                Vector3 p2 {xMax, yPlaneCoord, zPlaneCoord};
                DrawLine3D(p1, p2, lineColor);
            }
        }
    }

    void gridLines3D::drawZXLines() {
        float zPlaneCoord = positivePlaneActive[Z] ? zMax : zMin;
        for (int i = 0; i < numLines; ++i) {
            // Get Z values in this loop
            float xPlaneCoord = xMin + static_cast<float>(i) * dx;
            // Lines of constant zx
            for (int j = 0; j < numLines; ++j) {
                Vector3 p1 {xPlaneCoord, yMin, zPlaneCoord};
                Vector3 p2 {xPlaneCoord, yMax, zPlaneCoord};
                DrawLine3D(p1, p2, lineColor);
            }
        }
    }

    void gridLines3D::drawZYLines() {
        float zPlaneCoord = positivePlaneActive[Z] ? zMax : zMin;
        for (int i = 0; i < numLines; ++i) {
            // Get Z values in this loop
            float yPlaneCoord = yMin + static_cast<float>(i) * dy;
            // Lines of constant zy
            for (int j = 0; j < numLines; ++j) {
                Vector3 p1 {xMin, yPlaneCoord, zPlaneCoord};
                Vector3 p2 {xMax, yPlaneCoord, zPlaneCoord};
                DrawLine3D(p1, p2, lineColor);
            }
        }
    }


} // plotObjects
