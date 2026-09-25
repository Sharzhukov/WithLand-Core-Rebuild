![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-green.svg)
![Platform](https://img.shields.io/badge/platform-macOS%20%7C%20Linux%20%7C%20Windows-lightgrey.svg)
![License](https://img.shields.io/badge/license-GNUv3-yellow.svg)

# WithlandCore-Rebuild

Ядро проекта **WithLand**. Полная переработка с нуля на чистом C++17.

## Что внутри

- `include/withland/common/` — общие типы и утилиты
- `include/withland/core/` — доменная логика (колония, колонисты и т.д.)
- `src/` — реализации
- `app/` — точка входа приложения (`withland`)
- `sandbox/` — exe для ручной отладки
- `tests/` — автотесты через CTest
- `docs/` — документация

## Требования

- CMake ≥ 3.21
- C++17
- Компилятор: MSVC 2019+, Clang 12+, GCC 9+
- Ninja ≥ 1.11

---

## Сборка

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

## Установка

```bash
cmake --install build --config Release --prefix <path>    # Windows
cmake --install build --prefix <path>                     # macOS/Linux
```

---

## Лицензия

**GNU General Public License v3.0** — см. [LICENSE](LICENSE).
