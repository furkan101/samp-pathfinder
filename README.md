# samp-pathfinder

A high-performance, multi-threaded **A* (A-Star) Pathfinding** plugin for SA-MP servers, written in C++17.

> **Current Status:** v0.2.0 (Alpha) - Functional Engine

## 🌟 Features
* **True Asynchronous:** Heavy pathfinding calculations run on a background thread.
* **A* Algorithm:** Finds the shortest path between 3D nodes efficiently.
* **Dynamic Graph:** Add nodes and connections via Pawn script.
* **Thread-Safe:** Mutex-locked task queue system prevents server crashes.
* **3D Support:** Fully compatible with SA-MP's (x, y, z) coordinate system.

## 🚀 Installation
1. Download **`samp-pathfinder.dll`** from Releases.
2. Place it in your `plugins/` folder.
3. Copy `samp-pathfinder.inc` to `pawno/include/`.
4. Add `plugins samp-pathfinder` to `server.cfg`.

## 📖 API Reference

### Graph Setup
| Function | Description |
|Cs|Cs|
| `PF_AddNode(id, x, y, z)` | Adds a navigation node to the memory. |
| `PF_ConnectNodes(id1, id2)` | Creates a two-way connection between nodes. |

### Pathfinding
| Function | Description |
|Cs|Cs|
| `PF_FindPath(start, end, cb[], playerid)` | Requests a path calculation (Async). |
| `PF_GetNodePos(id, &x, &y, &z)` | Gets the 3D coordinates of a specific node. |

### Result Handling
| Function | Description |
|Cs|Cs|
| `PF_PathFound(resultid)` | Returns 1 if a path was found. |
| `PF_PathNext(resultid)` | Iterates to the next node in the path. |
| `PF_GetPathNode(resultid)` | Returns the Node ID at the current step. |
| `PF_FreeResult(resultid)` | Frees the memory (Must be called!). |

## ⚡ Usage Example

```C++
#include <a_samp>
#include <samp-pathfinder>

main() {
    // 1. Setup Map (Simple Triangle)
    PF_AddNode(1, 0.0, 0.0, 5.0);
    PF_AddNode(2, 20.0, 0.0, 5.0);
    PF_AddNode(3, 20.0, 20.0, 5.0);

    PF_ConnectNodes(1, 2);
    PF_ConnectNodes(2, 3);
    
    // 2. Request Path
    PF_FindPath(1, 3, "OnPathCalculated");
}

forward OnPathCalculated(resultid, playerid);
public OnPathCalculated(resultid, playerid)
{
    if(PF_PathFound(resultid))
    {
        while(PF_PathNext(resultid))
        {
            new nodeID = PF_GetPathNode(resultid);
            new Float:x, Float:y, Float:z;
            
            PF_GetNodePos(nodeID, x, y, z);
            printf("Go to Node %d at %.2f, %.2f, %.2f", nodeID, x, y, z);
        }
    }
    PF_FreeResult(resultid);
    return 1;
}```