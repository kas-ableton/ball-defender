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

constexpr int kPlayAreaX = 725;
constexpr int kPlayAreaY = kWindowSizeY - (2 * kWindowPadding);

constexpr unsigned int kBallRadius = 10;
constexpr int kBallStartPosX = kPlayAreaX / 2;
constexpr int kBallStartPosY = kPlayAreaY - (kBallRadius * 2);
constexpr int kLaunchRayStartPosY = kBallStartPosY + kBallRadius;

// pixels per second
constexpr float kVelocity = 1440.0f;

constexpr int kBlockSizeX = 55;
constexpr int kBlockSizeY = 55;
constexpr int kBlockHitCountTextSize = 20;
constexpr int kBlockGapSize = 5;

constexpr int kBlockRowCount = 12;// kPlayAreaX / kBlockSizeX;

constexpr float kLaunchRayWidth = 5.f;
} // namespace bd
