# Contributing to Withland-Core-Rebuild 🏛️

First off — thank you for considering contributing to Withland-Core-Rebuild! 🎉  
Your help makes this project better.

By participating, you agree to follow our [Code of Conduct](CODE_OF_CONDUCT.md).

---

## 📑 Table of Contents

- [How Can I Contribute?](#-how-can-i-contribute)
- [Code Style](#-code-style)
- [Development Setup](#-development-setup)
- [Commit Messages](#-commit-messages)
- [License](#-license)
- [Contact](#-contact)

---

## 🤝 How Can I Contribute?

### Reporting Bugs 🐛

Open an issue on GitHub with:

- A clear title and description
- Steps to reproduce
- Expected vs. actual behavior
- Your OS (Windows / macOS / Linux) and compiler version
- CMake version (`cmake --version`)
- A minimal code snippet, if possible

### Suggesting Features 💡

Feature requests are welcome. Open an issue and describe:

- What you want to add
- Why it is useful
- How it should behave (if you already have ideas)

### Pull Requests 🔧

`main` is protected. All changes go through a pull request.

1. Fork the repository (or create a branch, if you have write access):

   ```bash
   git checkout -b feature/your-feature-name
   ```

2. Make your changes.
3. Build and test locally on your OS (see [Development Setup](#-development-setup)).
4. Commit with a clear message (see [Commit Messages](#-commit-messages)).
5. Push your branch:

   ```bash
   git push origin feature/your-feature-name
   ```

6. Open a Pull Request against `main`.

The maintainer **squash-merges** approved PRs. Merge commits are not allowed — `main` keeps a linear history.

---

## 🎨 Code Style

### Language and standard

- **C++17**, standard library only — no third-party dependencies in the core.
- Headers: `.hpp`. Sources: `.cpp`.
- Headers use `#pragma once` (no include guards).
- No `using namespace std;` in headers or sources.

### Naming conventions

| Element | Style | Example |
|---|---|---|
| Namespace | `lowercase` | `withland`, `withland::core` |
| Class / struct / enum | `PascalCase` | `Colonist`, `Gender`, `Profession` |
| Public function / method | `PascalCase` | `UpdateDay()`, `GetName()` |
| Class member | **`name_`** (trailing underscore) | `name_`, `age_`, `health_` |
| Class member (alternative) | **`m_name`** (m_ prefix) | `m_name`, `m_age`, `m_health` |
| Local variable / parameter | `snake_case` | `new_name`, `max_age` |
| Constant | `kPascalCase` | `kMaxAge`, `kMaxStat` |
| Enum value | `PascalCase` | `Gender::Male`, `Profession::Farmer` |

> ⚠️ **Pick one member style per class and stay consistent.**
> Do **not** mix `name_` and `m_name` in the same class.

### Includes

Order: own header first, then project headers, then STL.

```cpp
// Colonist.cpp
#include "withland/core/Colonist.hpp"   // 1. own header
#include "withland/core/Colony.hpp"     // 2. project headers
#include <string>                       // 3. STL
#include <vector>
```

Include paths use angle brackets for project headers:

```cpp
#include <withland/core/Colonist.hpp>
```

### Memory

- No raw owning pointers. No `new` / `delete` in user code.
- Use `std::unique_ptr`, `std::make_unique`, or containers.
- Prefer value semantics over pointers where possible.
- For non-owning references use `T*` or `T&` (document lifetime).

### Example

```cpp
#pragma once

#include <string>
#include <cstdint>

namespace withland {

class Colonist {
public:
    Colonist(std::string name, unsigned age);

    const std::string& GetName() const noexcept;
    unsigned           GetAge()  const noexcept;

    void UpdateDay();

private:
    static constexpr unsigned kMaxAge = 120;

    std::string name_;      // or m_name — pick one, stay consistent
    unsigned    age_{0};
    unsigned    health_{100};
};

} // namespace withland
```

---

## ⚙️ Development Setup

### Prerequisites

- **CMake** ≥ 3.21
- **Ninja** ≥ 1.11 (recommended; presets use it)
- **C++17 compiler**:
  - Windows — MSVC 2019+ (from Visual Studio)
  - macOS — AppleClang (Xcode Command Line Tools)
  - Linux — GCC 9+ or Clang 12+
- **Git**

Install Ninja if you don't have it:

```bash
# Windows
winget install Ninja-build.Ninja

# macOS
brew install ninja

# Linux (Debian/Ubuntu)
sudo apt install ninja-build

# Linux (Fedora)
sudo dnf install ninja-build
```

### Clone & build

```bash
git clone https://github.com/Sharzhukov/Withland-Core-Rebuild.git
cd Withland-Core-Rebuild
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

### Build options

Options exposed by the project CMake (if defined in `CMakeLists.txt`):

| Option | Default | Description |
|---|---|---|
| `WITHLAND_CORE_BUILD_LIBRARY` | ON | Build the core library |
| `WITHLAND_CORE_BUILD_APP` | ON | Build the main executable |
| `WITHLAND_CORE_BUILD_SANDBOX` | ON | Build the sandbox executable |
| `WITHLAND_CORE_BUILD_TESTS` | ON | Build tests |
| `WITHLAND_CORE_WARNINGS_AS_ERRORS` | OFF | Treat warnings as errors |

Example override:

```bash
cmake --preset linux-debug -DWITHLAND_CORE_BUILD_TESTS=OFF
```

### Testing

```bash
ctest --preset windows-debug    # Windows
ctest --preset macos-debug      # macOS
ctest --preset linux-debug      # Linux
```

Or run the test binary directly:

```
build/<preset>/tests/withland_core_tests       # Windows / Linux
build/<preset>/tests/withland_core_tests.exe   # Windows (alternative)
```

---

## 📝 Commit Messages

This project follows [Conventional Commits](https://www.conventionalcommits.org/).

Format:

```
<type>(<scope>): <short description>

[optional body]

[optional footer]
```

Common types:

| Type | Use for |
|---|---|
| `feat` | New feature |
| `fix` | Bug fix |
| `refactor` | Code change without behavior change |
| `test` | Adding or fixing tests |
| `docs` | Documentation only |
| `style` | Formatting, no code change |
| `chore` | Build, CI, tooling |
| `perf` | Performance improvement |

Examples:

```
feat(core): add Colony::Tick()
fix(colonist): prevent self-marriage
refactor(core): replace raw pointers with unique_ptr
test(colony): cover AddColonist edge cases
docs(readme): fix CMake version mismatch
```

---

## 📄 License

By contributing, you agree that your contributions are licensed under the
**GNU General Public License v3.0** — see [LICENSE](LICENSE) for the full text.

---

## 📬 Contact

- **Website:** [sharzhukov.com](https://sharzhukov.com)
- **GitHub:** [@Sharzhukov](https://github.com/Sharzhukov)
- **Email:** [admin@sharzhukov.com](mailto:admin@sharzhukov.com)