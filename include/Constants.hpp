#pragma once


namespace bd {
constexpr unsigned int kWindowSizeX = 880;
constexpr unsigned int kWindowSizeY = 880;

constexpr unsigned int kWindowPadding = 20;

constexpr int kPlayAreaX = 720;
constexpr int kPlayAreaY = kWindowSizeY - (2 * kWindowPadding);

constexpr unsigned int kBallRadius = 10;
constexpr int kBallStartPosX = kWindowPadding + kPlayAreaX / 2;
constexpr int kBallStartPosY = kPlayAreaY;

constexpr float kVelocity = 10.0f;

constexpr int kBlockSizeX = 30;
constexpr int kBlockSizeY = 30;

constexpr int kBlockRowCount = kPlayAreaX / kBlockSizeX;
} // namespace bd
