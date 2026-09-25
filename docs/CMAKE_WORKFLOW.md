# WithlandCore-Rebuild — CMake Workflow

Сборка ядра на трёх ОС: **Windows (MSVC)**, **macOS (AppleClang)**, **Linux (GCC/Clang)**.

Ядро — **чистый C++17** на стандартной библиотеке. Никаких внешних зависимостей.

---

## 1. Что собирается

| Цель | Тип | Назначение | Install |
|---|---|---|---|
| `WithlandCore` | static lib | Ядро. Потребители линкуются через `Withland::Core` | ✅ |
| `withland` | exe | Точка входа приложения | ✅ |
| `withland_sandbox` | exe | Песочница для ручной отладки | ❌ |
| `withland_core_tests` | exe | Автотесты через CTest | ❌ |

---

## 2. Опции

| Опция | По умолчанию | Что делает |
|---|---|---|
| `WITHLAND_CORE_BUILD_LIBRARY` | `ON` | Собрать `WithlandCore` |
| `WITHLAND_CORE_BUILD_APP` | `ON` | Собрать `withland` |
| `WITHLAND_CORE_BUILD_SANDBOX` | `ON` | Собрать `withland_sandbox` |
| `WITHLAND_CORE_BUILD_TESTS` | `ON` | Собрать тесты |
| `WITHLAND_CORE_WARNINGS_AS_ERRORS` | `OFF` | `-Werror` / `/WX` |

---

## 3. Структура

```
WithlandCore-Rebuild/
├── CMakeLists.txt
├── CMakePresets.json
├── cmake/
│   └── WithlandCoreConfig.cmake.in
├── include/withland/{common,core}/
├── src/{common,core}/  и  src/*.cpp
├── app/
├── sandbox/
├── tests/
└── docs/
```

---

## 4. Пресеты

| Платформа | Debug | Release |
|---|---|---|
| macOS | `macos-debug` | `macos-release` (universal) |
| Linux | `linux-debug`, `linux-debug-clang` | `linux-release` |
| Windows | `windows-debug` | `windows-release` |

Использование одинаково:

```bash
cmake --preset <name>
cmake --build --preset <name>
ctest --preset <name>
```

---

## 5. Windows (MSVC)

**Терминал:** Developer PowerShell for Visual Studio (Start Menu).

```powershell
cd D:\Developer\WithLand\WithlandCore-Rebuild
Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue

cmake --preset windows-debug
cmake --build --preset windows-debug
ctest --preset windows-debug
```

Результат:
```
build\Debug\WithlandCore.lib
build\app\Debug\withland.exe
build\sandbox\Debug\withland_sandbox.exe
build\tests\Debug\withland_core_tests.exe
```

---

## 6. macOS

```bash
cd ~/Developer/WithLand/WithlandCore-Rebuild
rm -rf build

cmake --preset macos-debug
cmake --build --preset macos-debug
ctest --preset macos-debug
```

Результат:
```
build/libWithlandCore.a
build/app/withland
build/sandbox/withland_sandbox
build/tests/withland_core_tests
```

Universal binary (Intel + Apple Silicon):

```bash
cmake --preset macos-release
cmake --build --preset macos-release
lipo -info build/app/withland
```

---

## 7. Linux

```bash
# Ubuntu/Debian
sudo apt install build-essential cmake ninja-build git

# Fedora
sudo dnf install gcc-c++ cmake ninja-build git
```

```bash
cd ~/Developer/WithLand/WithlandCore-Rebuild
rm -rf build

cmake --preset linux-debug
cmake --build --preset linux-debug
ctest --preset linux-debug
```

Clang:

```bash
cmake --preset linux-debug-clang
cmake --build --preset linux-debug-clang
```

---

## 8. Сборка одной цели

```bash
cmake --build build --target WithlandCore     # только ядро
cmake --build build --target withland         # только главный exe
cmake --build build --target withland_core_tests
```

На MSVC добавьте `--config Debug`.

---

## 9. Установка

```
<prefix>/
├── bin/withland[.exe]
├── include/withland/...
└── lib/
    ├── WithlandCore.lib | libWithlandCore.a
    └── cmake/WithlandCore/...
```

```bash
cmake --install build --config Release --prefix C:/withland-install    # Windows
cmake --install build --prefix ~/withland-install                      # macOS/Linux
```

Использование в другом проекте:

```cmake
find_package(WithlandCore REQUIRED)
target_link_libraries(myapp PRIVATE Withland::Core)
```

---

## 10. Добавление нового `.cpp`

1. Положить в `src/core/` или `src/common/`.
2. Добавить в группу в `CMakeLists.txt`:

   ```cmake
   set(WITHLAND_CORE_MODULE_SOURCES
       src/core/Colony.cpp
       src/core/Colonist.cpp
       src/core/NewFile.cpp     # ← добавили
   )
   ```

3. Удалить блок `if(NOT WITHLAND_CORE_SOURCES) ... endif()`, если он ещё есть.
4. Пересобрать.

---

## 11. Политика предупреждений

**MSVC:** `/W4 /permissive- /utf-8 /EHsc`
**Clang/GCC:** `-Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual`

Включить `-Werror`:

```bash
cmake -S . -B build -DWITHLAND_CORE_WARNINGS_AS_ERRORS=ON
```

---

## 12. Частые ошибки

| Симптом | Фикс |
|---|---|
| `LNK2001 unresolved external` | Статический член без определения, или `.cpp` не в списке |
| `file INSTALL cannot find .../Release/*.lib` | Нет `--config Release` |
| `Cannot find source file: main.cpp` | Файл не создан или путь в `CMakeLists.txt` не тот |
| `C4018 signed/unsigned mismatch` | `int` vs `size_t` |
| Кириллица ломает MSVC | Нужен `/utf-8` (уже включён) |
| `Ninja not found` | `winget/brew/apt install ninja` |
| Меняю опцию — ничего не меняется | Удалить `build/` |

---

## 13. Быстрая шпаргалка

```bash
# Windows
cmake --preset windows-debug
cmake --build --preset windows-debug
ctest --preset windows-debug

# macOS
cmake --preset macos-debug
cmake --build --preset macos-debug
ctest --preset macos-debug

# Linux
cmake --preset linux-debug
cmake --build --preset linux-debug
ctest --preset linux-debug
```