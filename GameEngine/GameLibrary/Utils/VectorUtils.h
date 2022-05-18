//
// Created by ellis on 20/03/2022.
//

#pragma once
#include <vector>

class Transform;

namespace Utils {
    namespace Vector
    {
        template <typename T> T remove(std::vector<T> vector, T value);
    }
}