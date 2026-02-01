#pragma once

#include <array>

namespace talot {
	std::array<std::array<float, 4>, 4> getRotationTransform(float rotationX = 0.0f, float rotationY = 0.0f, float rotationZ = 0.0f, std::array<float, 3> rotationCenter = {0.0f, 0.0f, 0.0f});
}
