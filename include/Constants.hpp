#pragma once

#include "Vector.hpp"

namespace bd {

constexpr unsigned int kWindowSizeX = 880;
constexpr float kWindowSizeY = 880.f;

constexpr unsigned int kWindowPadding = 20;

constexpr int kPlayAreaX = 725;
constexpr int kPlayAreaY = kWindowSizeY - (2 * kWindowPadding);

constexpr unsigned int kBallRadius = 10;
constexpr int kBallStartPosX = kPlayAreaX / 2;
constexpr int kBallStartPosY = kPlayAreaY - (kBallRadius * 2);

constexpr float kLaunchRayWidth = 5.f;
} // namespace bd
