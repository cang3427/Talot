#include "transform.h"

#include <array>
#include <iostream>
#include <numbers>

#include "command.h"

#include "src/application.h"

void printMatrix(const talot::Transform &mat) {
  for (size_t i = 0; i < 4; i++) {
    for (size_t j = 0; j < 4; j++)
      std::cout << mat(i, j) << " ";
    std::cout << "\n";
  }
}

int main(int argc, char **argv) {

  app::Application app({.name = "Transform CLI",
                        .commandLineArgs = {.count = argc, .args = argv}});

  app.run();

  // CLI::App app{ "Transform CLI" };

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

  // try {
  //     app.parse(argc, argv);
  // }
  // catch (const CLI::ParseError& e) {
  //     return app.exit(e);
  // }

  // return 0;
}
