#include "transform.h"

#include <CLI/CLI.hpp>
#include <array>
#include <iostream>
#include <cmath>
#include <numbers>

void printMatrix(const talot::Transform& mat) {
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++)
            std::cout << mat(i, j) << " ";
        std::cout << "\n";
    }
}

int main(int argc, char** argv) {
    std::cout << "Interactive Transform CLI. Type 'exit' to quit.\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break; // EOF
        if (line == "exit") break;

        // Split the line into argv-style
        std::istringstream iss(line);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) tokens.push_back(token);

        if (tokens.empty()) continue;

        // Build CLI11 app for this command
        CLI::App app{ "Transform CLI" };

        auto* rotateXCmd = app.add_subcommand("rotateX", "Rotate about X axis");
        float angle = 0.0f;
        std::array<float, 3> center = { 0.0f, 0.0f, 0.0f };

        rotateXCmd->add_option("angle", angle, "Rotation angle in radians")->required();
        rotateXCmd->add_option("--center", center, "Optional rotation center x y z (default 0 0 0)");

        rotateXCmd->callback([&]() {
			talot::Vector rotationCenter = {center[0], center[1], center[2]};

            auto mat = talot::Transform::RotateX(angle * std::numbers::pi_v<float> / 180.0f, rotationCenter);
            std::cout << "Resulting rotation matrix:\n";
            printMatrix(mat);
            });

        // Parse this line
        try {
            std::vector<char*> argv_cstr;
            argv_cstr.push_back((char*)"cli"); // argv[0] placeholder
            for (auto& s : tokens) argv_cstr.push_back(&s[0]);
            app.parse(argv_cstr.size(), argv_cstr.data());
        }
        catch (const CLI::ParseError& e) {
            std::cerr << e.what() << "\n";
        }
    }

    std::cout << "Exiting CLI.\n";
}