#pragma once

#include "application.h"

#include "transform.h"

namespace sandbox {
	class Sandbox : public app::Application {
	public:
		explicit Sandbox(app::ApplicationSpecification specification);

		void run() override;

	private:
		std::optional<talot::Transform> m_transform;

		void applyTransform(const talot::Transform& transform);
		
		void createRotateCommand();
		void createRotateXCommand();
		void createRotateYCommand();
		void createRotateZCommand();

		void createScaleCommand();
		void createScaleXCommand();
		void createScaleYCommand();
		void createScaleZCommand();

		void createTranslateCommand();
		void createTranslateXCommand();
	    void createTranslateYCommand();
		void createTranslateZCommand();

	    void createInvertCommand();

	};
} // namespace sandbox