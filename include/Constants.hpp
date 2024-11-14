#pragma once

#include "Vector.hpp"

namespace bd {

constexpr inline Vector kLeftSideNormal{1.0, 0.0};
constexpr inline Vector kRightSideNormal{-1.0, 0.0};
constexpr inline Vector kBottomSideNormal{0.0, 1.0};
constexpr inline Vector kOverSideNormal{0.0, -1.0};

constexpr unsigned int kWindowSizeX = 880;
constexpr float kWindowSizeY = 880.f;

constexpr unsigned int kWindowPadding = 20;

constexpr int kPlayAreaX = 720;
constexpr int kPlayAreaY = kWindowSizeY - (2 * kWindowPadding);

constexpr unsigned int kBallRadius = 10;
constexpr int kBallStartPosX = kPlayAreaX / 2;
constexpr int kBallStartPosY = kPlayAreaY;

constexpr float kVelocity = 10.0f;

constexpr int kBlockSizeX = 45;
constexpr int kBlockSizeY = 45;
constexpr int kBlockHitCountTextSize = 20;

constexpr int kBlockRowCount = kPlayAreaX / kBlockSizeX;
} // namespace bd
