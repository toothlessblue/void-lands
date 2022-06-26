//
// Created by ellis on 24/06/2022.
//

#pragma once
#include <math.h>
#include <vector>
#include "Utils/Random.h"

class PoissonGenerator {
public:
    static const int MAX_SAMPLES = 1;

    struct Point {
        float x;
        float y;

        Point(float x, float y);
    };

    std::vector<Point> points;

    PoissonGenerator(float minDistance, float minDelta, float maxDelta);

private:
    int** grid;
    float cellSize;
    float gridSize;
    int cellCount;
    float offset;

    float minDistance;
    float minDistance2;

    float distance2(float x1, float y1, float x2, float y2);

    bool checkPoint(Point* point);

    Point randomPoint(float minX, float maxX, float minY, float maxY);

    void generatePoints();
};

