## Packets
Packets are up to 1024 bytes in size and contain a number of
indicator bytes, followed by the data they indicate.

The actual value of the indicator is defined within code, and shared between the client
and Server

| Indicator   | Description                           | Size of data                   |
|-------------|---------------------------------------|--------------------------------|
| Ping        | A request for a pong                  | no data, 0                     |
| Pong        | A reply to a ping                     | no data, 0                     |
| ConnectToWorld     | Size of world ID, and world ID        | 1 byte + number of chars in ID |
| Position    | X,Z of new player                     | 8 bytes, 2 floats              |
| Place       | Item ID to place, X, Z of placement   | 4 bytes, int                   |
| PickUp      | Entity ID to pick up                  | 4 bytes, int                   |
| Craft       | Item ID to craft                      | 2 bytes, shot int              |
| BeginEntity | Signals the start of an entity update | 4 bytes for entity ID as int   |
| EndEntity   | Signals the end of an entity update   | no data, 0                     |

These indicators may only appear after a BeginEntity, and before an EndEntity

| Indicator | Description                                                      | Size              |
|-----------|------------------------------------------------------------------|-------------------|
| Position  | X, Z position of the entity                                      | 8 bytes, 2 floats |
| Type      | Type ID of entity, mandatory if entity ID is not known to client | 4 bytes, int      |
| Destroy   | Command client to destroy entity                                 | 0 bytes           |
| Health    | Max damage of the entity                                         | 4 bytes, float    |
| Damage    | Damage taken by the entity                                       | 4 bytes, float    |