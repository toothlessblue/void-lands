//
// Created by ellis on 12/06/2022.
//

#pragma once
#include <unordered_map>
#include "EntityTypes/EntityTypes.h"
#include "NetworkTexture/NetworkTexture.h"

namespace EntityMetadata {
    std::unordered_map<int, NetworkTexture*> textures {
        { EntityTypes::Player, new NetworkTexture("/assets/images/test-image.dds", NetworkTexture::Type::DDS) },
        { EntityTypes::Tree, new NetworkTexture("/assets/images/tree.png", NetworkTexture::Type::PNG) },
        { EntityTypes::Rock, new NetworkTexture("/assets/images/test-image.dds", NetworkTexture::Type::DDS) },
    };

    std::unordered_map<int, glm::vec2> scales {
        { EntityTypes::Player, glm::vec2(1, 1) },
        { EntityTypes::Tree, glm::vec2(3, 3) },
        { EntityTypes::Rock, glm::vec2(3, 3) },
    };
}
