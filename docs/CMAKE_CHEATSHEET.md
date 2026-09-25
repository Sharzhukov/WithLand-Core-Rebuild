# CMake Cheatsheet — WithlandCore-Rebuild

Краткая шпаргалка. Полное описание — в `CMAKE_WORKFLOW.md`.

## Команды

| Задача | Команда |
|---|---|
| Конфигурация через пресет | `cmake --preset <name>` |
| Пересборка | `cmake --build --preset <name>` |
| Одна цель | `cmake --build build --target withland` |
| Тесты | `ctest --preset <name>` |
| Установка | `cmake --install build --prefix <path>` |
| Установка (MSVC) | `cmake --install build --config Release --prefix <path>` |
| Список пресетов | `cmake --list-presets` |
| Полная очистка | удалить `build/` |

## Опции

| Опция | По умолчанию |
|---|---|
| `WITHLAND_CORE_BUILD_LIBRARY` | `ON` |
| `WITHLAND_CORE_BUILD_APP` | `ON` |
| `WITHLAND_CORE_BUILD_SANDBOX` | `ON` |
| `WITHLAND_CORE_BUILD_TESTS` | `ON` |
| `WITHLAND_CORE_WARNINGS_AS_ERRORS` | `OFF` |

## Цели

| Цель | Тип |
|---|---|
| `WithlandCore` | static lib |
| `Withland::Core` | alias |
| `withland` | exe |
| `withland_sandbox` | exe |
| `withland_core_tests` | exe |

## Переменные CMake

| Переменная | Что делает |
|---|---|
| `CMAKE_BUILD_TYPE` | `Debug` / `Release` (macOS/Linux) |
| `CMAKE_OSX_ARCHITECTURES` | `arm64`, `x86_64`, `arm64;x86_64` |
| `CMAKE_OSX_DEPLOYMENT_TARGET` | минимальная версия macOS |
| `CMAKE_PREFIX_PATH` | где искать установленные пакеты |
| `CMAKE_CXX_COMPILER` | `clang++`, `g++` |

## Пресеты

| Платформа | Debug | Release |
|---|---|---|
| macOS | `macos-debug` | `macos-release` |
| Linux | `linux-debug` | `linux-release` |
| Windows | `windows-debug` | `windows-release` |