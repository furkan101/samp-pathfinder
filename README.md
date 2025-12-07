# samp-pathfinder (Work in Progress)

**[EN]** A high-performance, multi-threaded A* (A-Star) Pathfinding plugin for SA-MP, aiming to bring smart NPC navigation and NavMesh capabilities.
**[TR]** SA-MP için geliştirilen, yüksek performanslı, çok iş parçacıklı (multi-threaded) A* Yol Bulma ve NavMesh eklentisi.

> ⚠️ **Status:** Under Development (Foundation Phase)

## 🎯 Project Goals
The goal of this project is to solve the static NPC movement problem in SA-MP by providing a dynamic pathfinding engine.

* **Dynamic Pathfinding:** Calculate the shortest path between A and B in real-time.
* **A* Algorithm:** Efficient mathematical calculation for grids and nodes.
* **Thread-Safe:** Calculations run on background threads to prevent server lag.
* **3D Support:** Fully compatible with SA-MP's 3D coordinates (x, y, z).

## 🗺️ Roadmap
- [x] **Core:** Project skeleton and CMake setup.
- [x] **Memory Model:** Node and Vector3 structures defined.
- [ ] **Algorithm:** Implementation of A* (A-Star) logic.
- [ ] **Threading:** Worker thread integration for async calculations.
- [ ] **API:** Natives for Pawn (`PF_FindPath`, `PF_AddNode`...).
- [ ] **NavMesh:** Automatic grid generation (Future Goal).

## 🛠️ Build Requirements
* Visual Studio 2022 (C++17)
* CMake 3.15+

## License
MIT License