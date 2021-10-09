This project indicates how we can connected 2 objects using different connection types such as
AutoConnection
DirectConnection
QueuedConnection

Basically we use queued connection when source object and destination object are on different threads.
So we are making cross thread calls. 
We should not use DirectConnection during cross thread calls because direct connection is like callling function directly. 