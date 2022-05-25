//
// Created by ellis on 02/04/2022.
//

#pragma once

namespace DataIndicatorByte {
    enum {  // 1 byte signals that might go to the Server or client            // Size of data
        Ping,            // Ping the opposite                                  // 0 bytes
        Pong,            // Reply to a ping                                    // 0 bytes
        ConnectToWorld,  // Contains initial WebsocketConnection information   // 1 byte length, X bytes WebsocketConnection data
        ConnectToClient, // Contains initial WebsocketConnection information   // 1 byte length, X bytes WebsocketConnection data
        Position,        // X,Z of new player position                         // 8 bytes
        Place,           // Item ID to place, X, Z of placement position       // 10 bytes
        PickUp,          // Entity ID to pick up                               // 10 bytes - length of ID
        Craft,           // Item ID to craft                                   // 2 bytes
        AddItem,         // Add an item to the clients inventory               // 2 bytes
        RemoveItem,      // Remove an item from the clients inventory          // 2 bytes
        DropItem,        // Drop an item from the clients inventory            // 2 bytes
        BeginEntity,     // Signals the start of an entity update              // 0 bytes
        EndEntity,       // Signals the end of an entity update                // 0 bytes
    };
}

namespace EntityDataIndicatorByte {
    enum {  // 1 byte signals what part of the entity to update
        Position,      // X, Z position of the entity                                         // 8 bytes
        Destroy,       // Command client to destroy entity                                    // 0 bytes
        Health,        // Float of entity damage                                              // 4 bytes
        Damage,        // Damage taken by this entity                                         // 4 bytes
    };
}