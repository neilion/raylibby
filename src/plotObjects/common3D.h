#ifndef RAYLIBBY_COMMON3D_H
#define RAYLIBBY_COMMON3D_H

#include <vector>
#include <utility>
#include "raylib.h"

namespace plotObjects {


    class common3D {
    public:
        virtual std::pair<Vector3, Vector3> getPlotExtents() = 0;
        virtual void plot() = 0;

    };


    /// Non class methods (operate on instances / containers of common3D derived classes).
    std::pair<Vector3, Vector3> getMostExtremeExtents(std::vector<common3D *> &v);

} // plotObjects

#endif //RAYLIBBY_COMMON3D_H
