#pragma once

#include "application.h"

#include "transform.h"

namespace sandbox {
	class Sandbox : public app::Application {
	public:
		explicit Sandbox(app::ApplicationSpecification specification);

	private:
		std::optional<talot::Transform> m_transform;

		void createRotateXCommand();
	};
} // namespace sandbox