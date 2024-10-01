#pragma once

#include "Point.hpp"
#include "Vector.hpp"

#include <map>
#include <optional>
#include <tuple>
#include <vector>

namespace bd {
class Block {
public:
  Block(unsigned int hc, Point&& pos);

  /* Returns the axis value where @param pos intersects
   * returns null if @param pos doesn't intersect.
   */
  std::optional<Vector::Axis> impactSide(const Point& pos) const;
  Point position() const;
  void shift(Vector::Axis axis, int delta);

  bool operator<(const Block& rhs) { return mPosition.x() < rhs.position().x(); }
  friend Block& operator--(Block&);

private:
  unsigned int hitCount;
  Point mPosition;
};

class BlockRow {
public:
  BlockRow(std::tuple<int, int> range);

  void addBlock(Block&& block);
  std::tuple<int, int> range() const;
  const std::map<int, Block>& blocks() const;
  std::map<int, Block>& blocks();

private:
  std::tuple<int, int> mRange;
  std::map<int, Block> mBlocks;
};

class BlockManager {
public:
  BlockManager(unsigned int max, int blockSize);

  void addBlockRow();

  void advanceBlockRows();

  unsigned int rowDepth() const;

  bool atBlockRowMax() const;

  const std::vector<BlockRow>& blocks() const;

  std::optional<Block> blockAtPosition(const Point& position);

private:
  std::vector<BlockRow> mBlockRows;
  std::vector<Block> mBlocks;
  // how many rows have been added so far
  unsigned int mRowDepth = 0;
  unsigned int mMax;
  int mBlockSize;
};
} // namespace bd
