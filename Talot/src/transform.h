#pragma once

#include <memory>

#include <span>

namespace talot {
    struct Vector {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    class Transform {
        public:
            Transform();

            ~Transform();
            Transform(const Transform& other) = delete;
            Transform& operator=(const Transform& other) = delete;
            Transform(Transform&& other) noexcept = default;
            Transform& operator=(Transform&& other) noexcept = default;

            static Transform Rotate(float angle, Vector axis, Vector rotationCenter = {});
            static Transform RotateX(float angle, Vector rotationCenter = {});
            static Transform RotateY(float angle, Vector rotationCenter = {});
            static Transform RotateZ(float angle, Vector rotationCenter = {});

            static Transform Scale(float scale, Vector scaleCenter = {});
            static Transform Scale(Vector scaleVector, Vector scaleCenter = {});
            static Transform ScaleX(float scale, Vector scaleCenter = {});
            static Transform ScaleY(float scale, Vector scaleCenter = {});
            static Transform ScaleZ(float scale, Vector scaleCenter = {});

            static Transform Translate(Vector translationVector); 
            static Transform TranslateX(float translation);
            static Transform TranslateY(float translation);
            static Transform TranslateZ(float translation);

            static Transform Invert(const Transform& transform);
            
            const float *data() const;

            void transform(const Transform& transform);

            void operator*=(const Transform& other);
            
            float operator()(size_t row, size_t col) const;


        private:
            struct Impl;
            std::unique_ptr<Impl> m_impl;
            
    };

    Transform operator*(Transform&& lhs, Transform&& rhs);
}
#pragma once

#include <memory>

#include <span>

namespace talot {
    struct Vector {
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
    };

    class Transform {
        public:
            Transform();

            ~Transform();
            Transform(const Transform& other) = delete;
            Transform& operator=(const Transform& other) = delete;
            Transform(Transform&& other) noexcept = default;
            Transform& operator=(Transform&& other) noexcept = default;

            static Transform Rotate(float angle, Vector axis, Vector rotationCenter = {});
            static Transform RotateX(float angle, Vector rotationCenter = {});
            static Transform RotateY(float angle, Vector rotationCenter = {});
            static Transform RotateZ(float angle, Vector rotationCenter = {});

            static Transform Scale(float scale, Vector scaleCenter = {});
            static Transform Scale(Vector scaleVector, Vector scaleCenter = {});
            static Transform ScaleX(float scale, Vector scaleCenter = {});
            static Transform ScaleY(float scale, Vector scaleCenter = {});
            static Transform ScaleZ(float scale, Vector scaleCenter = {});

            static Transform Translate(Vector translationVector); 
            static Transform TranslateX(float translation);
            static Transform TranslateY(float translation);
            static Transform TranslateZ(float translation);

            static Transform Invert(const Transform& transform);
            
            const float *data() const;

            void transform(const Transform& transform);

            void operator*=(const Transform& other);
            
            float operator()(size_t row, size_t col) const;


        private:
            struct Impl;
            std::unique_ptr<Impl> m_impl;
            
    };

    Transform operator*(Transform&& lhs, Transform&& rhs);
}