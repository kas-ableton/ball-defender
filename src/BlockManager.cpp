#include "BlockManager.hpp"

#include "Constants.hpp"
#include "Point.hpp"

namespace bd {

/* Block */

Block& operator--(Block& lhs) {
  lhs.hitCount -= 1;
  return lhs;
}

Block::Block(unsigned int hc, Point&& pos) : hitCount(hc), mPosition(pos) {}

std::optional<Vector::Axis> Block::impactSide(const Point&) const { return {}; }

Point Block::position() const { return mPosition; }

void Block::shift(Vector::Axis axis, int delta) {
  if (axis == Vector::Axis::X) {
    mPosition.setX(mPosition.x() + delta);
  } else if (axis == Vector::Axis::Y) {
    mPosition.setY(mPosition.y() + delta);
  }
}

/* BlockRow */

BlockRow::BlockRow(std::tuple<int, int> range) : mRange(range) {}

void BlockRow::addBlock(Block&& block) {
  mBlocks.emplace(block.position().x(), std::move(block));
}

std::tuple<int, int> BlockRow::range() const { return mRange; }

const std::map<int, Block>& BlockRow::blocks() const { return mBlocks; }

std::map<int, Block>& BlockRow::blocks() { return mBlocks; }

/* BlockManager */

BlockManager::BlockManager(unsigned int max, int blockSize)
    : mMax(max), mBlockSize(blockSize) {}

void BlockManager::addBlockRow() {
  const auto startPos = static_cast<int>(kWindowPadding);
  const auto prevRange =
      mBlockRows.empty() ? std::tuple{0, 0}
                         : mBlockRows.back().range();

  auto newRow =
      BlockRow(std::make_tuple(std::get<1>(prevRange) + mBlockSize,
                               std::get<1>(prevRange) + 2*mBlockSize));

  // TODO
  // generate blocks
  // randomly generate positions
  // randomly generate hc using rowDepth

  auto hitCount = 1u;
  // Use `startPos` as Y-value because blocks are always added from the top
  auto position = Point{std::get<1>(prevRange) + mBlockSize, startPos};
  newRow.addBlock({hitCount, std::move(position)});

  mBlockRows.emplace_back(std::move(newRow));
  rowDepth++;
}

void BlockManager::advanceBlockRows() {
  for (auto& row : mBlockRows) {
    for (auto& [_, block] : row.blocks()) {
      block.shift(Vector::Axis::Y, mBlockSize);
    }
  }
}

bool BlockManager::atBlockRowMax() const {
  return static_cast<unsigned int>(
             mBlockRows.back().blocks().begin()->second.position().y()) == mMax;
}

const std::vector<BlockRow>& BlockManager::blocks() const { return mBlockRows; }

std::optional<Block> BlockManager::blockAtPosition(const Point&) { return {}; }

} // namespace bd
