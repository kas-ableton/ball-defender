#pragma once


namespace bd {
constexpr unsigned int kWindowSizeX = 1080;
constexpr unsigned int kWindowSizeY = 1080;

constexpr unsigned int kWindowPadding = 20;

constexpr int kPlayAreaX = 700;
constexpr int kPlayAreaY = kWindowSizeY - (2 * kWindowPadding);

constexpr unsigned int kBallRadius = 10;
constexpr int kBallStartPosX = kWindowPadding + kPlayAreaX / 2;
constexpr int kBallStartPosY = kPlayAreaY;

constexpr float kVelocity = 10.0f;
} // namespace bd
