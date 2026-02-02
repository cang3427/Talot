#include "talot.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <algorithm>

namespace talot {
	namespace {
		TransformMatrix convertEigenMatrix(const Eigen::Matrix4f& matrix) {
			TransformMatrix stlMatrix;
			const Eigen::Matrix4f tmp = matrix.transpose().eval();
			std::memcpy(stlMatrix.data(), tmp.data(), sizeof(stlMatrix));
			return stlMatrix;
		}

		template<typename TransformType>
		TransformMatrix transformAboutCenter(const TransformType& transform, const Vector& center) {
			const Eigen::Translation3f centerTranslation(center[0], center[1], center[2]);
			return convertEigenMatrix((centerTranslation * transform * centerTranslation.inverse()).matrix());
		}

		TransformMatrix rotate(float angle, Eigen::Vector3f axis, Vector rotationCenter) {
			return transformAboutCenter(Eigen::AngleAxisf(angle, axis), rotationCenter);
		}

		TransformMatrix scale(Eigen::AlignedScaling3f scaling, Vector scaleCenter) {
			return transformAboutCenter(scaling, scaleCenter);
		}
	}

	TransformMatrix rotate(float angle, Vector axis, Vector rotationCenter) {
		return rotate(angle, Eigen::Vector3f(axis[0], axis[1], axis[2]), rotationCenter);
	}

	TransformMatrix rotateX(float angle, Vector rotationCenter) {
		return rotate(angle, Eigen::Vector3f::UnitX(), rotationCenter);
	}

	TransformMatrix rotateY(float angle, Vector rotationCenter) {
		return rotate(angle, Eigen::Vector3f::UnitY(), rotationCenter);
	}

	TransformMatrix rotateZ(float angle, Vector rotationCenter) {
		return rotate(angle, Eigen::Vector3f::UnitZ(), rotationCenter);
	}

	TransformMatrix scale(float scale, Vector scaleCenter) {
		return transformAboutCenter(Eigen::UniformScaling<float>(scale), scaleCenter);
	}

	TransformMatrix scale(Vector scaleVector, Vector scaleCenter) {
		return transformAboutCenter(Eigen::AlignedScaling3f(scaleVector[0], scaleVector[1], scaleVector[2]), scaleCenter);
	}

	TransformMatrix scaleX(float scale, Vector scaleCenter) {
		return transformAboutCenter(Eigen::AlignedScaling3f(scale, 1.0f, 1.0f), scaleCenter);
	}

	TransformMatrix scaleY(float scale, Vector scaleCenter) {
		return transformAboutCenter(Eigen::AlignedScaling3f(1.0f, scale, 1.0f), scaleCenter);
	}

	TransformMatrix scaleZ(float scale, Vector scaleCenter) {
		return transformAboutCenter(Eigen::AlignedScaling3f(1.0f, 1.0f, scale), scaleCenter);
	}

	TransformMatrix translate(Vector translationVector) {
		Eigen::Matrix4f translationMatrix = Eigen::Matrix4f::Identity();
		translationMatrix.block<3, 1>(0, 3) = Eigen::Vector3f(translationVector[0], translationVector[1], translationVector[2]);
		return convertEigenMatrix(translationMatrix);
	}

	TransformMatrix translateX(float translation) { 
		return translate(Vector{translation, 0.0f, 0.0f}); 
	}
	TransformMatrix translateY(float translation) { 
		return translate(Vector{0.0f, translation, 0.0f}); 
	}
	TransformMatrix translateZ(float translation) { 
		return translate(Vector{0.0f, 0.0f, translation}); 
	}
}