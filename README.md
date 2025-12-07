# samp-pathfinder

A high-performance, multi-threaded **A* (A-Star) Pathfinding** plugin for SA-MP servers, written in C++17.

## 🌟 Features
* **Asynchronous:** Heavy calculations run on a background thread. Zero server lag.
* **A* Algorithm:** Finds the shortest path between 3D coordinates efficiently.
* **Dynamic Graph:** Create nodes and connections on the fly via Pawn.
* **Thread-Safe:** robust task queue system prevents crashes.

## 🚀 Installation
1. Download `samp-pathfinder.dll` (Windows) or `.so` (Linux).
2. Place it in your `plugins/` folder.
3. Add `plugins samp-pathfinder` to your `server.cfg`.
4. Include `samp-pathfinder.inc` in your script.

## ⚡ Usage Example

### 1. Setup the Map (Graph)
Before finding paths, you must define the world nodes.
```C++
// Add Nodes (ID, x, y, z)
PF_AddNode(1, 0.0, 0.0, 0.0);
PF_AddNode(2, 10.0, 0.0, 0.0);
PF_AddNode(3, 20.0, 0.0, 0.0);

// Connect Nodes (Create roads)
PF_ConnectNodes(1, 2);
PF_ConnectNodes(2, 3);
```
### 2. Request a Path
Ask the plugin to calculate a route. This does NOT freeze the server.

```C++
// Find path from Node 1 to Node 3
PF_FindPath(1, 3, "OnPathCalculated");

forward OnPathCalculated(resultid, playerid);
public OnPathCalculated(resultid, playerid)
{
    if(PF_PathFound(resultid))
    {
        printf("Path Found!");
        while(PF_PathNext(resultid))
        {
            new nodeID = PF_GetPathNode(resultid);
            printf("Go to Node: %d", nodeID);
        }
    }
    PF_FreeResult(resultid); // Always free memory!
    return 1;
}
```
### 🛠️ Build
- Visual Studio 2022
- CMake 3.15+

> cmake -S . -B build -G "Visual Studio 17 2022" -A Win32
> cmake --build build --config Release

### License
MIT License