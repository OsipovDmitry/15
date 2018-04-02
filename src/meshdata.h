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
	-0.5f, 0.0f, -0.5f, -1.0f, -1.0f, -1.0f, -0.25f, -0.25f,
	+0.5f, 0.0f, -0.5f, +1.0f, -1.0f, -1.0f, 1.25f, -0.25f,
	+0.5f, 0.0f, +0.5f, +1.0f, -1.0f, +1.0f, 1.25f, 1.25f,
	-0.5f, 0.0f, +0.5f, -1.0f, -1.0f, +1.0f, -0.25f, 1.25f,
	-0.5f, 0.25f, -0.5f, -1.0f, +1.0f, -1.0f, 0.0f, 0.0f,
	+0.5f, 0.25f, -0.5f, +1.0f, +1.0f, -1.0f, 1.0f, 0.0f,
	+0.5f, 0.25f, +0.5f, +1.0f, +1.0f, +1.0f, 1.0f, 1.0f,
	-0.5f, 0.25f, +0.5f, -1.0f, +1.0f, +1.0f, 0.0f, 1.0f,
};
const std::vector<uint32_t> blockIndices {
	4,7,6, 6,5,4,
	7,3,2, 2,6,7,
	6,2,1, 1,5,6,
	5,1,0, 0,4,5,
	4,0,3, 3,7,4,
};

#endif // MESHDATA_H
