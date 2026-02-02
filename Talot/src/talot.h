#pragma once

#include <array>

namespace talot {
	using TransformMatrix = std::array<std::array<float, 4>, 4>;
	using Vector = std::array<float, 3>;

	inline constexpr Vector g_origin = {0.0f, 0.0f, 0.0f}; 

	TransformMatrix rotate(float angle, Vector axis, Vector rotationCenter = g_origin);
	TransformMatrix rotateX(float angle, Vector rotationCenter = g_origin);
	TransformMatrix rotateY(float angle, Vector rotationCenter = g_origin);
	TransformMatrix rotateZ(float angle, Vector rotationCenter = g_origin);

	TransformMatrix scale(float scale, Vector scaleCenter = g_origin);
	TransformMatrix scale(Vector scaleVector, Vector scaleCenter = g_origin);
	TransformMatrix scaleX(float scale, Vector scaleCenter = g_origin);
	TransformMatrix scaleY(float scale, Vector scaleCenter = g_origin);
	TransformMatrix scaleZ(float scale, Vector scaleCenter = g_origin);

	TransformMatrix translate(Vector translationVector); 
	TransformMatrix translateX(float translation);
	TransformMatrix translateY(float translation);
	TransformMatrix translateZ(float translation);
}
