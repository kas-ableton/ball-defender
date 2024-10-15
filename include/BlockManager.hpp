#pragma once

#include "Constants.hpp"
#include "Rect.hpp"
#include "Vector.hpp"

#include <array>
#include <optional>
#include <vector>

namespace bd {
class Ball;

struct Block {
  Point position;
  int hitCount;
};

class BlockManager {
public:
  using Blocks = std::vector<Block>;
  struct Indices {
    int row;
    int column;
  };

  BlockManager(int blockSize, int MaxRowHeight);

  // for drawing
  // NOTE: positions are relative to the Play Area
  Blocks blocks() const;

  // operations for collision detection
  struct BlockCollision {
    BlockCollision(Indices&& indices, std::vector<Vector::Axis>&& axes)
        : blockIndices(std::move(indices)), sides(std::move(axes)) {}
    Indices blockIndices;
    std::vector<Vector::Axis> sides;
  };
  std::optional<std::vector<BlockManager::BlockCollision>>
  blockCollisions(Point&& ballPos);

  // decrements HC, removes block row when empty
  void decrementBlockHitCount(const Indices& indices);

  // adding a new row
  void addNewRow();

  // tracking score
  int runningRowCount() const;

  // detecting game over
  bool atMaxRowHeight() const;

private:
  struct BlockRow {
    using hitCount = int;
    Rect area;
    std::array<hitCount, bd::kBlockRowCount> blocks;
  };

  void advanceBlockRows();

  void addNewRow(BlockRow&&);

  Block getBlockAtIndices(const Indices&) const;

  std::vector<BlockRow> mBlockRows;

  int mBlockSize;
  int mMaxRowHeight;
  int mRunningRowCount;
};
} // namespace bd
