#include "transform.h"

#include <Eigen/Core>
#include <Eigen/Geometry>

namespace talot {

    Vector s_axisX = {1.0f, 0.0f, 0.0f};
    Vector s_axisY = {0.0f, 1.0f, 0.0f};
    Vector s_axisZ = {0.0f, 0.0f, 1.0f};

    struct Transform::Impl {
        Eigen::Matrix4f matrix = Eigen::Matrix4f::Identity();
    };

    namespace {
		template<typename EigenTransformType>
		Eigen::Matrix4f transformAboutCenter(const EigenTransformType& transform, const Vector& center) {
			const Eigen::Translation3f centerTranslation(center.x, center.y, center.z);
			return (centerTranslation * transform * centerTranslation.inverse()).matrix();
		}

        Eigen::Vector3f toEigenVector3f(const Vector& vector) {
            return Eigen::Vector3f(vector.x, vector.y, vector.z);
        }
	}
    
    Transform::Transform() : m_impl(std::make_unique<Impl>()) {}

    Transform::~Transform() = default;

    Transform Transform::Rotate(float angle, Vector axis, Vector rotationCenter) {
        Transform transform;
        transform.m_impl->matrix = transformAboutCenter(Eigen::AngleAxisf(angle, toEigenVector3f(axis)), rotationCenter);
		return transform;
	}

	Transform Transform::RotateX(float angle, Vector rotationCenter) {
		return Rotate(angle, s_axisX, rotationCenter);
	}

	Transform Transform::RotateY(float angle, Vector rotationCenter) {
		return Rotate(angle, s_axisY, rotationCenter);
	}

	Transform Transform::RotateZ(float angle, Vector rotationCenter) {
		return Rotate(angle, s_axisZ, rotationCenter);
	}

	Transform Transform::Scale(float scale, Vector scaleCenter) {
        Transform transform;
        transform.m_impl->matrix = transformAboutCenter(Eigen::UniformScaling<float>(scale), scaleCenter);
		return transform;
	}

	Transform Transform::Scale(Vector scaleVector, Vector scaleCenter) {
        Transform transform;
        transform.m_impl->matrix = transformAboutCenter(Eigen::AlignedScaling3f(scaleVector.x, scaleVector.y, scaleVector.z), scaleCenter);
		return transform;
	}

	Transform Transform::ScaleX(float scale, Vector scaleCenter) {
        return Scale(s_axisX, scaleCenter);
	}

	Transform Transform::ScaleY(float scale, Vector scaleCenter) {
        return Scale(s_axisY, scaleCenter);
	}

	Transform Transform::ScaleZ(float scale, Vector scaleCenter) {
        return Scale(s_axisZ, scaleCenter);
	}
    
	Transform Transform::Translate(Vector translationVector) {
        Transform transform;
		transform.m_impl->matrix.block<3, 1>(0, 3) = toEigenVector3f(translationVector);
		return transform;
	}

	Transform Transform::TranslateX(float translation) { 
		return Translate({translation, 0.0f, 0.0f}); 
	}

	Transform Transform::TranslateY(float translation) { 
		return Translate({0.0f, translation, 0.0f}); 
	}

	Transform Transform::TranslateZ(float translation) { 
		return Translate({0.0f, 0.0f, translation}); 
	}

    Transform Transform::Invert(const Transform& transform) {
        Transform result;
        result.m_impl->matrix = transform.m_impl->matrix.inverse();
        return result;
    }

    const float *Transform::data() const {
        return m_impl->matrix.data();   
    }

    float Transform::operator()(size_t row, size_t col) const {
        return m_impl->matrix(row, col);
    }

    void Transform::operator*=(const Transform& other) {
        m_impl->matrix *= other.m_impl->matrix;
    }

    void Transform::transform(const Transform& transform) {
        Transform result = transform;
		result *= *this;
       
    }

    Transform operator*(Transform &&lhs,  Transform &&rhs) {
        Transform result(std::move(lhs));
        result *= rhs;
        return result;
    }
}