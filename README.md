# WithlandCore-Rebuild

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![CMake](https://img.shields.io/badge/CMake-3.21%2B-green.svg)](https://cmake.org/)
[![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey.svg)](#-build)
[![License](https://img.shields.io/badge/license-GPL--3.0-yellow.svg)](LICENSE)

> **WithLand** - Behind every survivor is a choice: the land remembers those who stayed.
> **WithlandCore-Rebuild** is its domain core, rewritten from scratch in pure C++17 — with a focus on clean architecture, testability, and separation of concerns.

The core handles colonists, resources, events, marriages, diseases, and daily simulation ticks. UI (console and raylib-based) lives in separate layers and depends on the core, not the other way around.

---

## ✨ Features

- **Domain logic** — `Colonist`, `Colony`, `Wedding`, `Event`, `Profession`
- **Deterministic simulation** — one tick = one in-game day
- **Layered architecture** — core has zero dependencies on UI or file I/O
- **RAII-first** — no raw owning pointers, no manual `new`/`delete`
- **Cross-platform** — Windows, macOS, Linux

> 🚧 Tests, presets and CI are being set up. See [Roadmap](#-roadmap).

---

## 📁 Project structure

```
WithlandCore-Rebuild/
├── include/withland/
│   ├── common/          # common types, utilities, helpers
│   └── core/            # domain logic (Colony, Colonist, Event, ...)
├── src/                 # implementations of the core
├── app/                 # application entry point (withland)
├── sandbox/             # manual debugging executable
├── tests/               # automated tests (CTest)
├── docs/                # documentation (Doxygen)
├── CMakeLists.txt       # root CMake
└── LICENSE              # GPL-3.0
```

---

## 🛠 Requirements

| Tool | Minimum version | Notes |
|---|---|---|
| CMake | **3.21** | Required for `CMakePresets.json` v3 (when added) |
| C++ compiler | MSVC 2019+, Clang 12+, GCC 9+ | C++17 required |
| Ninja | 1.11+ | *Recommended* |
| Git | any | For cloning |

---

## 🚀 Build

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

Once `CMakePresets.json` lands, this will be replaced with presets (`cmake --preset linux-debug` etc.).

---

## 🧪 Tests

> 🚧 Coming soon.

When ready, tests will run via:

```bash
ctest --test-dir build --output-on-failure
```

---

## 🗺 Roadmap

- [x] Base classes: `Colonist`, `Colony`, `Event`, `Wedding`
- [x] CMake build
- [ ] CTest integration
- [ ] CMake presets (`windows/macos/linux`)
- [ ] Event system (weighted random events)
- [ ] Save / load (binary + JSON)
- [ ] `SimulationEngine` — explicit tick pipeline
- [ ] Multithreaded simulation tick
- [ ] Console UI
- [ ] raylib GUI (`WithLand` app)
- [ ] CI/CD on GitHub Actions (all 3 platforms)

---

## 🤝 Contributing

Contributions are welcome.

- Fork → feature branch → Pull Request.
- Commit style: [Conventional Commits](https://www.conventionalcommits.org/).
- Code style: `.clang-format` (LLVM-based) — will be added alongside CI.

---

## 📄 License

**GNU General Public License v3.0** — see [LICENSE](LICENSE).

```
Copyright (C) 2026 Alexander Sharzhukov
```

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

---

**Author:** Alexander Sharzhukov · [sharzhukov.ru](https://sharzhukov.ru) · [GitHub](https://github.com/Sharzhukov)