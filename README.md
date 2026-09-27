![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-green.svg)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey.svg)
![License](https://img.shields.io/badge/license-GNUv3-yellow.svg)

# WithlandCore-Rebuild

The core of the **WithLand** project. A complete rewrite from scratch in pure C++17.

## What's inside

- `include/withland/common/` — common types and utilities
- `include/withland/core/` — domain logic (colony, colonists, etc.)
- `src/` — implementations
- `app/` — application entry point (`withland`)
- `sandbox/` — exe for manual debugging
- `tests/` — automated tests via CTest
- `docs/` — documentation

## Requirements

- CMake ≥ 3.21
- C++17
- Compiler: MSVC 2019+, Clang 12+, GCC 9+
- Ninja ≥ 1.11

---

## Build

### Windows (Developer PowerShell for VS)
```powershell
cmake --preset windows-debug
cmake --build --preset windows-debug
ctest --preset windows-debug
```

### macOS

```bash
cmake --preset macos-debug
cmake --build --preset macos-debug
ctest --preset macos-debug
```

### Linux

```bash
cmake --preset linux-debug
cmake --build --preset linux-debug
ctest --preset linux-debug
```

## Installation

```bash
cmake --install build --config Release --prefix <path>    # Windows
cmake --install build --prefix <path>                     # macOS/Linux
```

---

## License

**GNU General Public License v3.0** — see [LICENSE](LICENSE).