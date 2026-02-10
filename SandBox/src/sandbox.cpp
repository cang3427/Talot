#include "sandbox.h"

#include "transform.h"

#include <numbers>

#include <iostream>

namespace sandbox {
    namespace {
        void printMatrix(const talot::Transform& mat) {
            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++)
                    std::cout << mat(i, j) << " ";
                std::cout << "\n";
            }
        }
    }

	Sandbox::Sandbox(app::ApplicationSpecification specification) : app::Application(specification) {
        constexpr app::CommandArgSpecification<float> angleArg = { .name = "angle", .description = "Rotation angle in degrees" };
        constexpr app::CommandArgSpecification<std::optional<std::array<float, 3>>> centerArg = { .name = "--center", .description = "Optional rotation center x y z (default: 0 0 0)" };
        constexpr app::CommandSpecification<float, std::optional<std::array<float, 3>>> commandSpecification = { .name = "rotateX", .description = "Rotate about X axis", .argSpecifications = std::make_tuple(angleArg, centerArg) };
        constexpr auto callback = [](float angle, std::optional<std::array<float, 3>> center) {
            talot::Vector rotationCenter;
            if (center.has_value()) {
                rotationCenter.x = center->at(0);
                rotationCenter.y = center->at(1);
                rotationCenter.z = center->at(2);
            }
            talot::Transform transform = talot::Transform::RotateX(angle * std::numbers::pi_v<float> / 180.0f, rotationCenter);
            printMatrix(transform);
            };
        const app::Command<float, std::optional<std::array<float, 3>>> command = { .specification = commandSpecification, .callback = callback };

        pushCommand(command);
	}
}