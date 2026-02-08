#pragma once
#include <array>
#include <optional>
#include <string_view>
#include <tuple>


namespace app {

struct Co

    struct Command {

}

template <typename T>
struct CommandArg {
  std::string_view name;
  std::string_view description;
  T defaultValue{};
};

template <typename... Args> struct Command {
  std::string_view name;
  std::string_view description;
  std::tuple<CommandArg<Args>...> args;
};

// Aliases
using Vector = std::array<float, 3>;

constexpr Vector zeroVec{0.0f, 0.0f, 0.0f};
constexpr Vector oneVec{1.0f, 1.0f, 1.0f};
constexpr Vector zAxis{0.0f, 0.0f, 1.0f};

constexpr CommandArg<float> angle0{"angle", "Rotation angle (degrees)", 0.0f};
constexpr CommandArg<Vector> center0{"center", "Center vector", zeroVec};
constexpr CommandArg<Vector> axisZ{"axis", "Rotation axis vector", zAxis};
constexpr CommandArg<float> scale1{"scale", "Scale factor", 1.0f};
constexpr CommandArg<Vector> scaleVec1{"scale", "Scale vector", oneVec};
constexpr CommandArg<Vector> translation0{"translation", "Translation vector",
                                          zeroVec};
constexpr CommandArg<float> translation0f{"translation", "Translation distance",
                                          0.0f};

// -----------------------------
// Rotate commands
// -----------------------------

constexpr Command<float, Vector, Vector> rotateCmd{
    .name = "rotate",
    .description = "Rotate around an arbitrary axis",
    .args = {angle0, axisZ, center0}};

constexpr Command<float, Vector> rotateXCmd{.name = "rotateX",
                                            .description =
                                                "Rotate about X axis",
                                            .args = {angle0, center0}};

constexpr Command<float, Vector> rotateYCmd{.name = "rotateY",
                                            .description =
                                                "Rotate about Y axis",
                                            .args = {angle0, center0}};

constexpr Command<float, Vector> rotateZCmd{.name = "rotateZ",
                                            .description =
                                                "Rotate about Z axis",
                                            .args = {angle0, center0}};

// -----------------------------
// Scale commands
// -----------------------------

constexpr Command<float, Vector> scaleCmd{
    .name = "scale", .description = "Uniform scale", .args = {scale1, center0}};

constexpr Command<Vector, Vector> scaleVecCmd{.name = "scaleVec",
                                              .description =
                                                  "Non-uniform scale",
                                              .args = {scaleVec1, center0}};

constexpr Command<float, Vector> scaleXCmd{.name = "scaleX",
                                           .description = "Scale along X axis",
                                           .args = {scale1, center0}};

constexpr Command<float, Vector> scaleYCmd{.name = "scaleY",
                                           .description = "Scale along Y axis",
                                           .args = {scale1, center0}};

constexpr Command<float, Vector> scaleZCmd{.name = "scaleZ",
                                           .description = "Scale along Z axis",
                                           .args = {scale1, center0}};

// -----------------------------
// Translate commands
// -----------------------------

constexpr Command<Vector> translateCmd{.name = "translate",
                                       .description = "Translate by vector",
                                       .args = {translation0}};

constexpr Command<float> translateXCmd{.name = "translateX",
                                       .description = "Translate along X axis",
                                       .args = {translation0f}};

constexpr Command<float> translateYCmd{.name = "translateY",
                                       .description = "Translate along Y axis",
                                       .args = {translation0f}};

constexpr Command<float> translateZCmd{.name = "translateZ",
                                       .description = "Translate along Z axis",
                                       .args = {translation0f}};

// -----------------------------
// All commands tuple
// -----------------------------

constexpr auto allCommands = std::tuple{
    rotateCmd,     rotateXCmd,    rotateYCmd,   rotateZCmd, scaleCmd,
    scaleVecCmd,   scaleXCmd,     scaleYCmd,    scaleZCmd,  translateCmd,
    translateXCmd, translateYCmd, translateZCmd};
} // namespace app