#include "BlockManager.hpp"

#include "Ball.hpp"
#include "CollisionConstants.hpp"

#include <random>

namespace bd {

constexpr int kBlockGapSize = 5;

BlockManager::BlockManager(int blockSize, int max, int blockRowWidth)
    : mBlockSize(blockSize), mMaxRowHeight(max), mBlockRowWidth(blockRowWidth) {
}

void BlockManager::reset() {
  mBlockRows.clear();
  mRunningRowCount = 0;
}

int BlockManager::runningRowCount() const { return mRunningRowCount; }

void BlockManager::advanceBlockRows() {
  std::for_each(mBlockRows.begin(), mBlockRows.end(), [this](auto& blockRow) {
    blockRow.area.shiftY(mBlockSize + bd::kBlockGapSize);
  });
}

auto BlockManager::makeBlockRowData() const -> BlockRowData {
  auto data = BlockRowData{};

  std::fill(data.begin(), data.end(), 0);

  std::random_device rd;
  std::uniform_int_distribution<int> dist(0, bd::kBlockRowCount - 1);

  for (auto i = 0; i < bd::kBlockRowCount / 2; ++i) {
    auto idx = dist(rd);
    data[idx] = makeBlockHitCount();
  }

  return data;
}

int BlockManager::makeBlockHitCount() const {
  int lowest = 0;
  int highest = 0;

  if (mRunningRowCount < 5) {
    lowest = 1;
    highest = 1;
  } else if (mRunningRowCount < 10) {
    lowest = 1;
    highest = 2;
  } else if (mRunningRowCount < 20) {
    lowest = 1;
    highest = 4;
  } else if (mRunningRowCount < 30) {
    lowest = 2;
    highest = 7;
  } else if (mRunningRowCount < 40) {
    lowest = 3;
    highest = 10;
  } else if (mRunningRowCount < 50) {
    lowest = 5;
    highest = 15;
  } else if (mRunningRowCount < 70) {
    lowest = 8;
    highest = 20;
  } else {
    lowest = 10;
    highest = 25;
  }

  if (lowest == highest) {
    return lowest;
  }

  std::random_device rd;
  std::uniform_int_distribution<int> dist(lowest, highest);

  return dist(rd);
}

auto BlockManager::makeBlockRow(Point&& topLeft) -> BlockRow {
  return {Rect{std::move(topLeft), mBlockSize, mBlockRowWidth},
          makeBlockRowData()};
}

void BlockManager::addNewRow() {
  advanceBlockRows();

  auto newBlockRow = makeBlockRow(Point{0, 0});

  mBlockRows.emplace_back(std::move(newBlockRow));

  mRunningRowCount++;
}

bool BlockManager::atMaxRowHeight() const {
  if (mBlockRows.empty()) {
    return false;
  }

  return mBlockRows.front().area.bottom() >= mMaxRowHeight;
}

Block BlockManager::getBlockAtIndices(const Indices& indices) const {
  auto blockRow = mBlockRows.at(indices.column);
  auto y = blockRow.area.top() + bd::kBlockGapSize;
  auto x = indices.row * mBlockSize +
           ((indices.row + 1) * bd::kBlockGapSize);

  return {Point{x, y}, blockRow.blocks[indices.row]};
}

// return the collision normal
std::optional<std::vector<BlockManager::BlockCollision>>
BlockManager::blockCollisions(const Ball& ball, int ballDiameter) {
  auto ballRect = Rect{ball.position(), ballDiameter};

  auto result = std::vector<BlockCollision>{};

  for (int m = 0; m < mBlockRows.size(); ++m) {
    if (mBlockRows[m].area.intersects(ballRect)) {
      for (int n = 0; n < mBlockRows[m].blocks.size(); ++n) {
        if (mBlockRows[m].blocks[n]) {
          auto block = getBlockAtIndices({n, m});
          auto blockRect = Rect{block.position, mBlockSize};

          if (const auto overlap = blockRect.overlap(ballRect)) {
            auto sides = std::vector<Vector::Axis>{};
            Vector collisionNormal;
            if (overlap->height() < overlap->width()) {
              collisionNormal =
                  ball.vector().y > 0.0 ? kOverSideNormal : kBottomSideNormal;
            } else if (overlap->width() < overlap->height()) {
              collisionNormal =
                  ball.vector().x > 0.0 ? kLeftSideNormal : kRightSideNormal;
            }
            result.emplace_back(Indices{n, m}, std::move(collisionNormal));
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
