#include "talot.h"

#include <numbers>

#include <iostream>

int main() {
	std::array<std::array<float, 4>, 4> transform = talot::translate({0.3f, 2.3f, -1.1f});
	for (const auto& row : transform) {
		for (const auto& value : row) {
			std::cout << value << " ";
		}
		std::cout << std::endl;
	}
}