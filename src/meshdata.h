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

inline std::vector<float> tableVertices(int32_t numBlocks) {
	std::vector<float> arr {
		-numBlocks/2.0f, 0, -numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-numBlocks/2.0f, 0, +numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		+numBlocks/2.0f, 0, +numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		+numBlocks/2.0f, 0, -numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		-numBlocks/2.0f, 0.35f, +numBlocks/2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-numBlocks/2.0f, 0.0f, +numBlocks/2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.3f,
		-numBlocks/2.0f, 0.0f, -numBlocks/2.0f, 1.0f, 0.0f, 0.0f, 0.3f, 0.3f,
		-numBlocks/2.0f, 0.35f, -numBlocks/2.0f, 1.0f, 0.0f, 0.0f, 0.3f, 0.0f,

		-numBlocks/2.0f-0.2f, 0.35f, +numBlocks/2.0f+0.2f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-numBlocks/2.0f-0.2f, 0.0f, +numBlocks/2.0f+0.2f, -1.0f, 0.0f, 0.0f, 0.0f, 0.3f,
		-numBlocks/2.0f-0.2f, 0.0f, -numBlocks/2.0f-0.2f, -1.0f, 0.0f, 0.0f, 0.3f, 0.3f,
		-numBlocks/2.0f-0.2f, 0.35f, -numBlocks/2.0f-0.2f, -1.0f, 0.0f, 0.0f, 0.3f, 0.0f,

		+numBlocks/2.0f, 0.35f, +numBlocks/2.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		+numBlocks/2.0f, 0.0f, +numBlocks/2.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.3f,
		+numBlocks/2.0f, 0.0f, -numBlocks/2.0f, -1.0f, 0.0f, 0.0f, 0.3f, 0.3f,
		+numBlocks/2.0f, 0.35f, -numBlocks/2.0f, -1.0f, 0.0f, 0.0f, 0.3f, 0.0f,

		+numBlocks/2.0f+0.2f, 0.35f, +numBlocks/2.0f+0.2f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		+numBlocks/2.0f+0.2f, 0.0f, +numBlocks/2.0f+0.2f, 1.0f, 0.0f, 0.0f, 0.0f, 0.3f,
		+numBlocks/2.0f+0.2f, 0.0f, -numBlocks/2.0f-0.2f, 1.0f, 0.0f, 0.0f, 0.3f, 0.3f,
		+numBlocks/2.0f+0.2f, 0.35f, -numBlocks/2.0f-0.2f, 1.0f, 0.0f, 0.0f, 0.3f, 0.0f,

		+numBlocks/2.0f, 0.35f, -numBlocks/2.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		+numBlocks/2.0f, 0.0f, -numBlocks/2.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.3f,
		-numBlocks/2.0f, 0.0f, -numBlocks/2.0f, 0.0f, 0.0f, -1.0f, 0.3f, 0.3f,
		-numBlocks/2.0f, 0.35f, -numBlocks/2.0f, 0.0f, 0.0f, -1.0f, 0.3f, 0.0f,

		+numBlocks/2.0f+0.2f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		+numBlocks/2.0f+0.2f, 0.0f, -numBlocks/2.0f-0.2f, 0.0f, 0.0f, 1.0f, 0.0f, 0.3f,
		-numBlocks/2.0f-0.2f, 0.0f, -numBlocks/2.0f-0.2f, 0.0f, 0.0f, 1.0f, 0.3f, 0.3f,
		-numBlocks/2.0f-0.2f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 0.0f, 1.0f, 0.3f, 0.0f,

		+numBlocks/2.0f, 0.35f, +numBlocks/2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		+numBlocks/2.0f, 0.0f, +numBlocks/2.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.3f,
		-numBlocks/2.0f, 0.0f, +numBlocks/2.0f, 0.0f, 0.0f, 1.0f, 0.3f, 0.3f,
		-numBlocks/2.0f, 0.35f, +numBlocks/2.0f, 0.0f, 0.0f, 1.0f, 0.3f, 0.0f,

		+numBlocks/2.0f+0.2f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		+numBlocks/2.0f+0.2f, 0.0f, +numBlocks/2.0f+0.2f, 0.0f, 0.0f, -1.0f, 0.0f, 0.3f,
		-numBlocks/2.0f-0.2f, 0.0f, +numBlocks/2.0f+0.2f, 0.0f, 0.0f, -1.0f, 0.3f, 0.3f,
		-numBlocks/2.0f-0.2f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 0.0f, -1.0f, 0.3f, 0.0f,

		-numBlocks/2.0f-0.2f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-numBlocks/2.0f-0.2f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		-numBlocks/2.0f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 1.0f, 0.0f, 0.3f, 1.0f,
		-numBlocks/2.0f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 1.0f, 0.0f, 0.3f, 0.0f,

		+numBlocks/2.0f+0.2f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		+numBlocks/2.0f+0.2f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		+numBlocks/2.0f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 1.0f, 0.0f, 0.3f, 1.0f,
		+numBlocks/2.0f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 1.0f, 0.0f, 0.3f, 0.0f,

		-numBlocks/2.0f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-numBlocks/2.0f, 0.35f, -numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.3f,
		+numBlocks/2.0f, 0.35f, -numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.3f,
		+numBlocks/2.0f, 0.35f, -numBlocks/2.0f-0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

		-numBlocks/2.0f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-numBlocks/2.0f, 0.35f, +numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.3f,
		+numBlocks/2.0f, 0.35f, +numBlocks/2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.3f,
		+numBlocks/2.0f, 0.35f, +numBlocks/2.0f+0.2f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,

	};
	return arr;
}
const std::vector<uint32_t> tableIndices {
	0,1,2, 2,3,0,
	4,5,6, 6,7,4,
	8,9,10, 10,11,8,
	12,13,14, 14,15,12,
	16,17,18, 18,19,16,
	20,21,22, 22,23,20,
	24,25,26, 26,27,24,
	28,29,30, 30,31,28,
	32,33,34, 34,35,32,
	36,37,38, 38,39,36,
	40,41,42, 42,43,40,
	44,45,46, 46,47,44,
	48,49,50, 50,51,48

};


#endif // MESHDATA_H
