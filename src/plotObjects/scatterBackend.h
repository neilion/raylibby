#ifndef RAYLIBBY_SCATTERBACKEND_H
#define RAYLIBBY_SCATTERBACKEND_H

#include <vector>

#include "raylib.h"
#include "raymath.h"
#include "common3D.h"

namespace plotObjects {

class scatterBackend : public common3D {
public:

    // Default constructor
    scatterBackend();

    // Data constructor
    explicit scatterBackend(std::vector<Vector3> &data);

    // Data update
    void setData(std::vector<Vector3> &dataIn);

    // Color update
    void setColor(std::vector<Color> &colorsIn);

    void setColorSingle(Color &c);

    // Adding a single point.
    void addPoint(const Vector3 &newPoint, const Color &newColor);


    [[nodiscard]] float getMarkerSize() const;
    void setMarkerSize(float desiredMarkerSize);

    std::pair<Vector3, Vector3> getPlotExtents() override;


    // Will likely want this to take in some sort of figure or axis handles. Not sure.
    void plot(void);


private:
    // Should the plot object own the plotted data?
    // Likely want it to, otherwise the scatter data is bound to s specific data instance.
    // Could be a pointer to a std::vector<Vector3>.

    std::vector<Vector3>    pointData;
    std::vector<Color>      color;

    // Size of the marker, un-normalized by figure window scale or distance.
    float markerSize = 1.0f;


};

} // plotObjects

#endif //RAYLIBBY_SCATTERBACKEND_H
