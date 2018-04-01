#ifndef MESHDATA_H
#define MESHDATA_H

#include <vector>
#include <inttypes.h>

const std::vector<float> quadXYVertices {
    -1.0f, +1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    +1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    +1.0f, +1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
};
const std::vector<uint32_t> quadXYIndices {
    0,1,2, 2,3,0
};

const std::vector<float> blockVertices {

};
const std::vector<uint32_t> blockIndices {

};

#endif // MESHDATA_H
