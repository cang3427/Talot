#include "talot.h"

#include <numbers>

#include <iostream>

int main() {
	std::array<std::array<float, 4>, 4> transform = talot::getRotationTransform(std::numbers::pi_v<float> / 2, 0.0f, 0.0f);
	for (const auto& row : transform) {
		for (const auto& value : row) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}