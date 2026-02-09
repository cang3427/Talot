#pragma once

#include <CLI/CLI.hpp>

#include <string>
#include <vector>

#include "command.h"

namespace app {

struct ApplicationCommandLineArgs {
  int count = 0;
  char **args = nullptr;

  const char *operator[](int index) const { return args[index]; }
};

struct ApplicationSpecification {
  std::string name;
  ApplicationCommandLineArgs commandLineArgs;
  std::vector<Command> commands;
};

class Application {
public:
  Application(const ApplicationSpecification &specification);

  void run();

private:
  ApplicationSpecification m_specification;
  CLI::App m_app;

  void registerCommand(const Command &command);
};
} // namespace app