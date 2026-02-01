#include <iostream>

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <algorithm>

namespace talot {
	namespace {
		std::array<std::array<float, 4>, 4> eigenToStlMatrix(const Eigen::Matrix4f& matrix) {
			std::array<std::array<float, 4>, 4> stlMatrix;
			Eigen::Matrix4f tmp = matrix.transpose().eval(); // transpose so rows become rows
			std::memcpy(stlMatrix.data(), tmp.data(), sizeof(stlMatrix));
			return stlMatrix;
		}
	}

	std::array<std::array<float, 4>, 4> getRotationTransform(float rotationX, float rotationY, float rotationZ, std::array<float, 3> rotationCenter) {
		auto rotation = Eigen::AngleAxisf(rotationX, Eigen::Vector3f::UnitX()) *
			Eigen::AngleAxisf(rotationY, Eigen::Vector3f::UnitY()) *
			Eigen::AngleAxisf(rotationZ, Eigen::Vector3f::UnitZ());
		if (std::ranges::all_of(rotationCenter, [](float v) { return v == 0.0f; })) {
			Eigen::Matrix4f transform = Eigen::Matrix4f::Identity();
			transform.block<3, 3>(0, 0) = rotation.toRotationMatrix();
			return eigenToStlMatrix(transform);
		}

		Eigen::Translation3f rotationCenterTranslation(rotationCenter[0], rotationCenter[1], rotationCenter[2]);
		Eigen::Matrix4f transform = (Eigen::Translation3f(rotationCenter[0], rotationCenter[1], rotationCenter[2]) * 
			rotation * 
			Eigen::Translation3f(-rotationCenter[0], -rotationCenter[1], -rotationCenter[2])).matrix();
		return eigenToStlMatrix(transform);
	}
}