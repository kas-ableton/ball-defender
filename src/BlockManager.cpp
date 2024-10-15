#include "BlockManager.hpp"

#include "Ball.hpp"

#include <random>

namespace bd {

BlockManager::BlockManager(int blockSize, int max)
    : mBlockSize(blockSize), mMaxRowHeight(max) {}

int BlockManager::runningRowCount() const { return mRunningRowCount; }

void BlockManager::advanceBlockRows() {
  std::for_each(mBlockRows.begin(), mBlockRows.end(),
                [](auto& blockRow) { blockRow.area.shiftY(bd::kBlockSizeY); });
}

void BlockManager::addNewRow(BlockRow&& newBlockRow) {
  mBlockRows.emplace_back(std::move(newBlockRow));
  mRunningRowCount++;
}

void BlockManager::addNewRow() {
  advanceBlockRows();

  auto newBlockRow =
      BlockRow{Rect{Point{0, 0}, mBlockSize, bd::kPlayAreaX}, {}};
  newBlockRow.blocks.fill(0);

  // TODO randomly create X new blocks
  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, bd::kBlockRowCount);
  const auto newIdx = dist(rd);

  const int hitCount = 1;
  newBlockRow.blocks[newIdx] = hitCount;

  addNewRow(std::move(newBlockRow));
}

bool BlockManager::atMaxRowHeight() const {
  if (mBlockRows.empty()) {
    return false;
  }

  return mBlockRows.front().area.bottom() >= mMaxRowHeight;
}

Block BlockManager::getBlockAtIndices(const Indices& indices) const {
  auto blockRow = mBlockRows.at(indices.column);
  auto y = blockRow.area.top();
  auto x = indices.row * mBlockSize;

  return {Point{x, y}, blockRow.blocks[indices.row]};
}

std::optional<std::vector<BlockManager::BlockCollision>>
BlockManager::blockCollisions(Point&& ballPos) {
  auto ballRect = Rect{ballPos, 2 * bd::kBallRadius};

  auto result = std::vector<BlockCollision>{};

  for (int m = 0; m < mBlockRows.size(); ++m) {
    if (mBlockRows[m].area.intersects(ballRect)) {
      for (int n = 0; n < mBlockRows[m].blocks.size(); ++n) {
        if (mBlockRows[m].blocks[n]) {
          auto block = getBlockAtIndices({n, m});
          auto blockRect = Rect{block.position, mBlockSize};

          if (const auto overlap = blockRect.overlap(ballRect))
          {
            auto sides = std::vector<Vector::Axis>{};
            if (overlap->height() < overlap->width()) {
              sides.push_back(Vector::Axis::Y);
            } else if (overlap->width() < overlap->height()) {
              sides.push_back(Vector::Axis::X);
            } else {
              sides.push_back(Vector::Axis::Y);
              sides.push_back(Vector::Axis::X);
            }
            result.emplace_back(Indices{n, m}, std::move(sides));
          }
        }
      }
    }
  }
  return result.empty() ? std::nullopt : std::make_optional(result);
}

void BlockManager::decrementBlockHitCount(const Indices& indices) {
  auto& blocks = mBlockRows[indices.column].blocks;
  blocks[indices.row]--;
  if (std::all_of(blocks.begin(), blocks.end(),
                  [](const auto& value) { return value == 0; })) {
    mBlockRows.erase(mBlockRows.begin() + indices.column);
  }
}

Blocks BlockManager::blocks() const {
  auto result = Blocks{};

  for (int m = 0; m < mBlockRows.size(); ++m) {
    for (int n = 0; n < mBlockRows[m].blocks.size(); ++n) {
      if (mBlockRows[m].blocks[n] > 0) {
        result.emplace_back(getBlockAtIndices({n, m}));
      }
    }
  }

  return result;
}

} // namespace bd
