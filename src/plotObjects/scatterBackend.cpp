#include <iostream>


#include "scatterBackend.h"
#include "extensionsVector3.h"


#define DEFAULT_DATA_SIZE (size_t)4
static Vector3 origin{0, 0, 0};
static auto uninitColor = BEIGE;


static void printVec3(Vector3 &v) {
    std::cout << "   X:  " << v.x;
    std::cout << "   Y:  " << v.y;
    std::cout << "   Z:  " << v.z;
    std::cout << "\n";
}



namespace plotObjects {

    /*!
     * Default constructor.
     * Initialize the data and color vectors to the default size.
     * Default points to origin.
     * Default points to uninitColor.
     */
    scatterBackend::scatterBackend() {
        pointData.resize(DEFAULT_DATA_SIZE);
        color.resize(DEFAULT_DATA_SIZE);
        pointData.reserve(DEFAULT_DATA_SIZE);
        color.reserve(DEFAULT_DATA_SIZE);

        // Note this isn't an actual constructor, this is a struct initialization
        Vector3 origin{0, 0, 0};

        // Init the data vectors.
        std::fill(pointData.begin(), pointData.end(), origin);
        std::fill(color.begin(), color.end(), uninitColor);
        std::cout << "Called default scatter constructor\n\n\n\n";

    }


    scatterBackend::scatterBackend(std::vector<Vector3> &data) {
        pointData = data;

        // Set the color data color vector to match the size of the data.
        auto n = data.size();
        color.reserve(n);

        // Set to default color.
        std::fill(color.begin(), color.end(), uninitColor);
    }

    void scatterBackend::setData(std::vector<Vector3> &dataIN) {
        pointData = dataIN;

        // The data size may no longer match the color size. Resize the color data.
        // Set the color data color vector to match the size of the data.
        auto n = dataIN.size();
        color.resize(n);

        // Set to first elements color, can be updated with successive call to ::setColor
        std::fill(color.begin(), color.end(), color[0]);
    }


    void scatterBackend::setColor(std::vector<Color> &colorsIn) {
        // Ensure that the colors are the same size as the data
        auto nData = pointData.size();
        auto nColors = colorsIn.size();

        if (nData != nColors) {
            std::cout << "Data size and input color size is not the same size.\n";
            std::cout << "Data size is " << nData << "  , colors size is " << nColors << "\n";

        } else {
            color = colorsIn;
        }
    }

    void scatterBackend::setColorSingle(Color &c) {
        auto n = pointData.size();
        color.resize(n);
        std::fill(color.begin(), color.end(), c);
    }

    // For now, shove the front end in here as well. I suppose its already dependent on raylib, since its using its type.
    void scatterBackend::plot() {
        // Assume plot has already been set up.
        auto n = pointData.size();
        for (int i = 0; i < n; ++i) {
            DrawSphere(pointData[i], markerSize, color[i]);
        }
    }

    float scatterBackend::getMarkerSize() const {
        return this->markerSize;
    }

    void scatterBackend::setMarkerSize(float desiredMarkerSize) {
        this->markerSize = desiredMarkerSize;

    }

    std::pair<Vector3, Vector3> scatterBackend::getPlotExtents() {
        Vector3 min = pointData[0];
        Vector3 max = pointData[0];

        for (auto & p : pointData) {
            min = elementWiseMin(min, p);
            max = elementWiseMax(max, p);
        }

        return std::make_pair(min - markerSize , max + markerSize);
    }

    void scatterBackend::addPoint(const Vector3 &newPoint, const Color &newColor) {
        pointData.push_back(newPoint);
        color.push_back(newColor);

    }

} // plotObjects