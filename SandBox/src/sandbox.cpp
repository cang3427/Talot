#include "sandbox.h"

#include "transform.h"

#include <numbers>

#include <iostream>

#include <utility>

#include <optional>

namespace sandbox {
    namespace {
        using Vector = std::array<float, 3>;
		using OptionalVector = std::optional<std::array<float, 3>>;

        void printMatrix(const talot::Transform& mat) {
            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++)
                    std::cout << mat(i, j) << " ";
                std::cout << "\n";
            }
        }

        
    }

	Sandbox::Sandbox(app::ApplicationSpecification specification) : app::Application(specification) {
        createRotateXCommand();
	}

    void Sandbox::createRotateXCommand() {
        constexpr app::CommandArgSpecification<float> angleArg = { .name = "angle", .description = "Rotation angle about the x-axis in degrees" };
        constexpr app::CommandArgSpecification<std::optional<std::array<float, 3>>> centerArg = { .name = "--center", .description = "Transform center" };
        constexpr app::CommandSpecification command = { .name = "rotateX", .description = "Rotate about the x-axis", .argSpecifications = std::make_tuple(angleArg, centerArg) };
        constexpr auto callback = [this] (float angle, OptionalVector center) {
            const float radians = angle * std::numbers::pi_v<float> / 180.0f;
            talot::Vector centerVec;
            if (center.has_value()) {
				centerVec = { center->at(0), center->at(1), center->at(2) };
			}
			const talot::Transform transform = talot::Transform::RotateX(radians, centerVec);
            m_transform = std::move(transform) * std::move(m_transform);
		};

		pushCommand(command, callback);
    }
}