Client -> Relay -> Node -> World

Relay handles all outside communication and communicates with nodes

Nodes start threads for worlds

All client communication is proxied through the chain to the worlds.

Outer websocket port = 27141

Inner socket port = 27142