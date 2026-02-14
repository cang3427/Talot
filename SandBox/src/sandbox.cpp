#include "sandbox.h"

#include "transform.h"

#include <numbers>
#include <iostream>
#include <utility>
#include <optional>

namespace sandbox {
    namespace {
        using ArrayVector = std::array<float, 3>;

		constexpr ArrayVector s_zeroArrayVector = {0.0f, 0.0f, 0.0f};

        void printMatrix(const talot::Transform& mat) {
            for (size_t i = 0; i < 4; i++) {
                for (size_t j = 0; j < 4; j++)
                    std::cout << mat(i, j) << " ";
                std::cout << "\n";
            }
        }

        talot::Vector toTalotVector(const ArrayVector& arr) {
            return {.x = arr[0], .y = arr[1], .z = arr[2]};
		}
    }

	Sandbox::Sandbox(app::ApplicationSpecification specification) : app::Application(specification) {
        createRotateCommand();
        createRotateXCommand();
        createRotateYCommand();
        createRotateZCommand();
        
        createScaleCommand();
        createScaleXCommand();
        createScaleYCommand();
        createScaleZCommand();

        createTranslateCommand();
        createTranslateXCommand();
        createTranslateYCommand();
        createTranslateZCommand();

        createInvertCommand();
	}

    void Sandbox::run() {
        app::Application::run();
		if (m_transform.has_value()) {
            printMatrix(*m_transform);
        }
    }

    void Sandbox::applyTransform(const talot::Transform& transform) {
        if (m_transform.has_value()) {
            m_transform->transform(transform);
        } else {
            m_transform = transform;
        }
	}

    void Sandbox::createRotateCommand() {
        constexpr app::CommandArgSpecification<float> angleArg = { .name = "angle", .description = "Rotation angle about the given axis in degrees", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> axisArg = { .name = "axis", .description = "Rotation axis", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Rotation center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "rotate", .description = "Rotate about an axis", .argSpecifications = std::make_tuple(angleArg, axisArg, centerArg) };
        const auto callback = [this](float angle, ArrayVector axis, ArrayVector center) {
            const float radians = angle * std::numbers::pi_v<float> / 180.0f;
            this->applyTransform(talot::Transform::Rotate(radians, toTalotVector(axis), toTalotVector(center)));
         };

        pushCommand(command, callback);
    }

    void Sandbox::createRotateXCommand() {
        constexpr app::CommandArgSpecification<float> angleArg = { .name = "angle", .description = "Rotation angle about the x-axis in degrees", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Rotation center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "rotateX", .description = "Rotate about the x-axis", .argSpecifications = std::make_tuple(angleArg, centerArg) };
        const auto callback = [this] (float angle, ArrayVector center) {
            const float radians = angle * std::numbers::pi_v<float> / 180.0f;
            this->applyTransform(talot::Transform::RotateX(radians, toTalotVector(center)));
		};

		pushCommand(command, callback);
    }

    void Sandbox::createRotateYCommand() {
        constexpr app::CommandArgSpecification<float> angleArg = { .name = "angle", .description = "Rotation angle about the y-axis in degrees", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Rotation center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "rotateY", .description = "Rotate about the y-axis", .argSpecifications = std::make_tuple(angleArg, centerArg) };
        const auto callback = [this](float angle, ArrayVector center) {
            const float radians = angle * std::numbers::pi_v<float> / 180.0f;
            this->applyTransform(talot::Transform::RotateY(radians, toTalotVector(center)));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createRotateZCommand() {
        constexpr app::CommandArgSpecification<float> angleArg = { .name = "angle", .description = "Rotation angle about the z-axis in degrees", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Rotation center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "rotateZ", .description = "Rotate about the z-axis", .argSpecifications = std::make_tuple(angleArg, centerArg) };
        const auto callback = [this](float angle, ArrayVector center) {
            const float radians = angle * std::numbers::pi_v<float> / 180.0f;
            this->applyTransform(talot::Transform::RotateZ(radians, toTalotVector(center)));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createScaleCommand() {
        constexpr app::CommandArgSpecification<float> factorArg = { .name = "factor", .description = "Scale factor", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Scale center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "scale", .description = "Scale uniformly", .argSpecifications = std::make_tuple(factorArg, centerArg) };
        const auto callback = [this](float factor, ArrayVector center) {
            this->applyTransform(talot::Transform::Scale(factor, toTalotVector(center)));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createScaleXCommand() {
        constexpr app::CommandArgSpecification<float> factorArg = { .name = "factor", .description = "Scale factor", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Scale center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "scaleX", .description = "Scale about the x-axis", .argSpecifications = std::make_tuple(factorArg, centerArg) };
        const auto callback = [this](float factor, ArrayVector center) {
            this->applyTransform(talot::Transform::ScaleX(factor, toTalotVector(center)));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createScaleYCommand() {
        constexpr app::CommandArgSpecification<float> factorArg = { .name = "factor", .description = "Scale factor", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Scale center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "scaleY", .description = "Scale about the y-axis", .argSpecifications = std::make_tuple(factorArg, centerArg) };
        const auto callback = [this](float factor, ArrayVector center) {
            this->applyTransform(talot::Transform::ScaleY(factor, toTalotVector(center)));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createScaleZCommand() {
        constexpr app::CommandArgSpecification<float> factorArg = { .name = "factor", .description = "Scale factor", .required = true };
        constexpr app::CommandArgSpecification<ArrayVector> centerArg = { .name = "--center", .description = "Scale center, defaults to (0, 0, 0)", .defaultValue = s_zeroArrayVector };
        constexpr app::CommandSpecification command = { .name = "scaleZ", .description = "Scale about the z-axis", .argSpecifications = std::make_tuple(factorArg, centerArg) };
        const auto callback = [this](float factor, ArrayVector center) {
            this->applyTransform(talot::Transform::ScaleZ(factor, toTalotVector(center)));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createTranslateCommand() {
        constexpr app::CommandArgSpecification<ArrayVector> translationArg = { .name = "translation", .description = "Translation vector", .required = true };
        constexpr app::CommandSpecification command = { .name = "translate", .description = "Translate by the vector", .argSpecifications = std::make_tuple(translationArg) };
        const auto callback = [this](ArrayVector translation) {
            this->applyTransform(talot::Transform::Translate(toTalotVector(translation)));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createTranslateXCommand() {
        constexpr app::CommandArgSpecification<float> translationArg = { .name = "translation", .description = "Translation amount along the x-axis", .required = true };
        constexpr app::CommandSpecification command = { .name = "translateX", .description = "Translate along the x-axis", .argSpecifications = std::make_tuple(translationArg) };
        const auto callback = [this](float translation) {
            this->applyTransform(talot::Transform::TranslateX(translation));
        };

        pushCommand(command, callback);
    }

    void Sandbox::createTranslateYCommand() {
        constexpr app::CommandArgSpecification<float> translationArg = { .name = "translation", .description = "Translation amount along the y-axis", .required = true };
        constexpr app::CommandSpecification command = { .name = "translateY", .description = "Translate along the y-axis", .argSpecifications = std::make_tuple(translationArg) };
        const auto callback = [this](float translation) {
            this->applyTransform(talot::Transform::TranslateY(translation));
            };

        pushCommand(command, callback);
    }

    void Sandbox::createTranslateZCommand() {
        constexpr app::CommandArgSpecification<float> translationArg = { .name = "translation", .description = "Translation amount along the z-axis", .required = true };
        constexpr app::CommandSpecification command = { .name = "translateZ", .description = "Translate along the z-axis", .argSpecifications = std::make_tuple(translationArg) };
        const auto callback = [this](float translation) {
            this->applyTransform(talot::Transform::TranslateZ(translation));
            };

        pushCommand(command, callback);
    }

    void Sandbox::createInvertCommand() {
        constexpr app::CommandSpecification command = { .name = "invert", .description = "Invert the transform" };
        const auto callback = [this]() {
            if (this->m_transform.has_value()) {
                this->m_transform->invert();
            }
        };

        pushCommand(command, callback);
    }

}