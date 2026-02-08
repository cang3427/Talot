#include "application.h"

namespace app {

Application::Application(const ApplicationSpecification &specification)
    : m_specification(specification), m_app(specification.name) {}

void Application::run() {
  for (const auto &command : m_specification.commands) {
    registerCommand(command);
  }

  const ApplicationCommandLineArgs &args = m_specification.commandLineArgs;
  try {
    m_app.parse(args.count, args.args);
  } catch (const CLI::ParseError &e) {
    return m_app.exit(e);
  }
}

void Application::registerCommand(const Command &command) {
  auto *appCommand = m_app.add_subcommand(command.name, command.description);

  for (const auto &arg : command.args) {
    CLI::Option *option =
        appCommand->add_option(arg.name, arg.variable, arg.description);
    if (arg.required) {
      option->required();
    }
  }

  appCommand->callback(command.callback);

  // float angle = 0.0f;
  // std::array<float, 3> center{ 0.0f, 0.0f, 0.0f };

  // auto* rotateXCmd = app.add_subcommand("rotateX", "Rotate about X axis");

  // rotateXCmd->add_option("angle", angle, "Rotation angle in degrees")
  //     ->required();

  // rotateXCmd->add_option(
  //     "--center",
  //     center,
  //     "Optional rotation center x y z (default: 0 0 0)"
  // );

  // rotateXCmd->callback([&]() {
  //     talot::Vector rotationCenter{ center[0], center[1], center[2] };

  //     auto mat = talot::Transform::RotateX(
  //         angle * std::numbers::pi_v<float> / 180.0f,
  //         rotationCenter
  //     );

  //     std::cout << "Resulting rotation matrix:\n";
  //     printMatrix(mat);
  //     });
}
} // namespace app