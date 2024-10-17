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
using Blocks = std::vector<Block>;

class BlockManager {
public:
  struct Indices {
    int row;
    int column;
  };

  BlockManager(int blockSize, int MaxRowHeight, int blockRowWidth);

  void reset();

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

  Block getBlockAtIndices(const Indices&) const;

  std::vector<BlockRow> mBlockRows;

  int mBlockSize;
  int mBlockRowWidth;
  int mMaxRowHeight;

  // this value is used as the score
  int mRunningRowCount;
};
} // namespace bd
