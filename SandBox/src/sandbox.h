#pragma once

#include "application.h"

namespace sandbox {
	class Sandbox : public app::Application {
	public:
		explicit Sandbox(app::ApplicationSpecification specification);
	};
} // namespace sandbox