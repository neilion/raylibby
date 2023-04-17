
#include "common3D.h"
#include "extensionsVector3.h"

namespace plotObjects {


    std::pair<Vector3, Vector3> getMostExtremeExtents(std::vector<common3D *> &v) {
        size_t n = v.size();
        if (n ==1) {
            return v[0]->getPlotExtents();
        } else {
            auto [min, max] = v[0]->getPlotExtents();
            for (auto & element : v) {
                auto [plotElementMin, plotElementMax] = element->getPlotExtents();
                min = elementWiseMin(min, plotElementMin);
                max = elementWiseMax(max, plotElementMax);
            }

            return std::make_pair(min, max);
        }

    }
} // plotObjects