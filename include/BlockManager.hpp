#pragma once

#include "Rect.hpp"
#include "Vector.hpp"

#include <array>
#include <optional>
#include <vector>

namespace bd {

constexpr int kBlockRowCount = 12;

class Ball;

struct Color {
  uint8_t R;
  uint8_t G;
  uint8_t B;
  uint8_t A = 255;

  Color invert(bool withAlpha = false) const {
    // need to construct 8-bit int because of integer promotion
    return {uint8_t(R ^ 0xFF), uint8_t(G ^ 0xFF), uint8_t(B ^ 0xFF),
            withAlpha ? uint8_t(A ^ 0xFF) : A};
  }
};

struct Block {
  Point position;
  Color color;
  int hitCount;
};
using Blocks = std::vector<Block>;

class BlockManager {
public:
  struct Indices {
    int row;
    int column;
  };

  BlockManager(int blockSize, int MaxRowHeight, int blockRowWidth);

  // clear blocks and row count
  void reset();

  void disable();

  // for drawing
  Blocks blocks() const;

  // operations for collision detection
  struct BlockCollision {
    BlockCollision(Indices&& indices, Vector&& collisionNormal)
        : blockIndices(std::move(indices)), normal(std::move(collisionNormal)) {
    }
    Indices blockIndices;
    Vector normal;
  };
  std::optional<std::vector<BlockManager::BlockCollision>>
  blockCollisions(const Ball& ball, int ballDiameter);

  // decrements HC, removes block row when empty
  void decrementBlockHitCount(const Indices& indices);

  // adding a new row
  void addNewRow();

  // tracking score
  int runningRowCount() const;

  // detecting game over
  bool atMaxRowHeight() const;

private:
  bool isDisabled = false;

  using hitCount = int;
  using BlockRowData = std::array<hitCount, bd::kBlockRowCount>;
  struct BlockRow {
    Rect area;
    BlockRowData blocks;
  };

  BlockRowData makeBlockRowData() const;
  int makeBlockHitCount() const;
  BlockRow makeBlockRow(Point&& topLeft);

  // Moves all existing rows down by the distance of one row height
  // New rows are added from the top of the play area
  void advanceBlockRows();

  Color getBlockColor(int hitCount) const;
  Block getBlockAtIndices(const Indices&) const;

  std::vector<BlockRow> mBlockRows;

  int mBlockSize;
  int mBlockRowWidth;
  int mMaxRowHeight;

  // this value is used as the score
  int mRunningRowCount;
};
} // namespace bd
