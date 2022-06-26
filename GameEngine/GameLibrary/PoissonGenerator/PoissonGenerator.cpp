//
// Created by ellis on 24/06/2022.
//

#include "PoissonGenerator.h"

PoissonGenerator::Point::Point(float x, float y) {
    this->x = x;
    this->y = y;
}

PoissonGenerator::PoissonGenerator(float minDistance, float minDelta, float maxDelta) {
    this->gridSize = maxDelta - minDelta;
    this->cellSize = sqrt(minDistance / 2);
    this->cellCount = floor(this->gridSize / this->cellSize);
    this->offset = remainder(this->gridSize, this->cellSize) / 2;

    this->minDistance = minDistance;
    this->minDistance2 = this->minDistance * this->minDistance;

    this->grid[this->cellCount][this->cellCount];

    for (int x = 0; x < this->cellCount; x++) {
        for (int y = 0; y < this->cellCount; y++) {
            this->grid[x][y] = -1;
        }
    }

    this->generatePoints();
}

float PoissonGenerator::distance2(float x1, float y1, float x2, float y2) {
    float dx = abs(x1 - x2);
    float dy = abs(y1 - y2);

    return (dx * dx) + (dy * dy);
}

bool PoissonGenerator::checkPoint(PoissonGenerator::Point* point) {
    int gridX = floor(point->x / this->cellSize);
    int gridY = floor(point->y / this->cellSize);

    for (int dx = -2; dx <= 2; dx++) {
        for (int dy = -2; dy <= 2; dy++) {
            if (gridX + dx < 0) continue;
            if (gridY + dy < 0) continue;

            int pointIndex = this->grid[gridX + dx][gridY + dy];

            if (!pointIndex) continue;
            if (pointIndex == -1) continue; // grid cell does not contain a point

            Point other = this->points[pointIndex];

            if (this->distance2(other.x, other.y, point->x, point->y) < minDistance2) {
                return false;
            }
        }
    }

    return true;
}

PoissonGenerator::Point PoissonGenerator::randomPoint(float minX, float maxX, float minY, float maxY) {
    return {
        Random::randomFloat(minX, maxX),
        Random::randomFloat(minY, maxY),
    };
}

void PoissonGenerator::generatePoints() {
    for (int x = 0; x < this->gridSize; x++) {
        for (int y = 0; y < this->gridSize; y++) {
            Point point = {0, 0};
            bool valid = false;
            int samples = 0;

            while (!valid && samples < PoissonGenerator::MAX_SAMPLES) {
                point = this->randomPoint(cellSize * x, cellSize * (x + 1), cellSize * y, cellSize * (y + 1));
                valid = checkPoint(&point);
                samples++;
            }

            if (valid) {
                grid[x][y] = points.size();
                this->points.push_back({
                    point.x + offset,
                    point.y + offset
                });
            }
        }
    }
}
