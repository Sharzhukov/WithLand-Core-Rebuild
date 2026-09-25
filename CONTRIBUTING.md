# Contributing to WithLand 🏛️

First off, thank you for considering contributing to WithLand! 🎉  
Your help is what makes this project better.

---

## How Can I Contribute?

### Reporting Bugs 🐛

If you find a bug, please open an issue on GitHub with:

- A clear title and description
- Steps to reproduce the issue
- Expected vs actual behavior
- Your OS (Windows / macOS / Linux) and compiler version
- CMake version (`cmake --version`)
- If possible, a minimal code example

### Suggesting Features 💡

Feature requests are welcome! Please open an issue and clearly describe:

- What you want to add
- Why it's useful
- How it should work (if you have ideas)

### Pull Requests 🔧

`main` is protected. All changes go through a pull request.

1. Fork the repository (or create a branch, if you have write access).
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Make your changes.

4. Build and test locally on your OS (see below).

5. Commit with a clear message:

```bash
git commit -m "feat: add your feature description"
```

6. Push to your fork / branch:

```bash
git push origin feature/your-feature-name
```

7. Open a Pull Request against main.

The maintainer squash-merges approved PRs. Merge commits are not allowed —
main keeps a linear history.

---

## Code Style

- C++17, standard library only — no external dependencies in the core.
- Files: .hpp for headers, .cpp for implementation.

- Naming:

   - Classes / enums — PascalCase (Colonist, Gender)

   - Functions & methods — PascalCase for public API (UpdateDay, GetName)

   - Local variables & parameters — snake_case (new_name, max_age)

   - Class members — trailing underscore (name_, age_) or m_ prefix — pick one per class, stay consistent

   - Constants — k prefix + PascalCase (kMaxAge, kMaxStat)

   - Namespaces — lowercase (withland, withland::core)

- Includes:

```cpp
#include <withland/core/Colonist.hpp>   // 1. own header first
#include <withland/core/Colony.hpp>     // 2. other project headers
#include <vector>                        // 3. STL
#include <cstdint>
```

- Headers: always #pragma once.

- No using namespace std; in headers or sources.

- No raw new/delete — use std::unique_ptr, std::make_unique, std::vector.

Example:

```cpp
#pragma once

#include <string>
#include <cstdint>

namespace withland {

class Colonist {
public:
    Colonist(std::string name, unsigned age);

    const std::string& Name() const noexcept;
    unsigned           Age()  const noexcept;

private:
    static constexpr unsigned kMaxAge = 120;

    std::string name_;
    unsigned    age_{0};
};

} // namespace withland
```

---

## Development Setup

### Prerequisites

- CMake ≥ 3.21

- Ninja ≥ 1.11

- C++17 compiler:

   - Windows — MSVC 2019+ (from Visual Studio)

   - macOS — AppleClang (Xcode Command Line Tools)

   - Linux — GCC 9+ or Clang 12+

- Git

Install Ninja:

```bash
# Windows
winget install Ninja-build.Ninja

# macOS
brew install ninja

# Linux
sudo apt install ninja-build      # Debian/Ubuntu
sudo dnf install ninja-build      # Fedora
```

### Clone & Build

```bash
git clone https://github.com/Sharzhukov/WithlandCore-Rebuild.git
cd WithlandCore-Rebuild
```

Then use a preset matching your OS:

```bash
# Windows (Developer PowerShell for VS)
cmake --preset windows-debug
cmake --build --preset windows-debug

# macOS
cmake --preset macos-debug
cmake --build --preset macos-debug

# Linux
cmake --preset linux-debug
cmake --build --preset linux-debug
```

### Build Options

| Option | Default | Description |
|--------|---------|-------------|
| `WITHLAND_CORE_BUILD_LIBRARY` | ON | Build the core library |
| `WITHLAND_CORE_BUILD_APP` | ON	| Build the main executable |
| `WITHLAND_CORE_BUILD_SANDBOX` | ON | Build the sandbox executable |
| `WITHLAND_CORE_BUILD_TESTS` | ON | Build tests |
| `WITHLAND_CORE_WARNINGS_AS_ERRORS` | OFF | Treat warnings as errors |

### Testing

```bash
ctest --preset windows-debug    # Windows
ctest --preset macos-debug      # macOS
ctest --preset linux-debug      # Linux
```

Or run the test binary directly:

```text
build/app/Debug/withland.exe            # Windows (main app)
build/sandbox/Debug/withland_sandbox.exe
build/tests/Debug/withland_core_tests.exe
```
---

## License
By contributing, you agree that your contributions will be licensed under the
**GNU General Public License v3.0** — see [LICENSE](LICENSE).

---

## Contact
- WebSite: [sharzhukov.com](https://sharzhukov.com)
- GitHub: [@Sharzhukov](https://github.com/Sharzhukov)
- Email: [admin@sharzhukov.com](mailto:admin@sharzhukov.com)