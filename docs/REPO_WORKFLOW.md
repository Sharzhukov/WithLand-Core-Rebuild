# WithlandCore-Rebuild — Workflow репозитория

## Назначение

`WithlandCore-Rebuild` — активный репозиторий ядра. Чистый C++17, без внешних зависимостей, три ОС.

Публикуется как `Withland::Core`. Потребители (Superbuild, GUI, TUI, модули) цепляют его через `FetchContent` **по тегу**.

## Ветки

- `main` — стабильное состояние, защищена
- `feature/*`, `fix/*`, `docs/*`, `chore/*` — временные

## Версионирование — SemVer

| Часть | Когда |
|---|---|
| MAJOR | Ломающее изменение API |
| MINOR | Новая обратно совместимая функциональность |
| PATCH | Багфикс без изменения API |

Версия синхронна в двух местах:

1. `CMakeLists.txt` → `project(WithlandCore VERSION x.y.z)`
2. Git-тег `vX.Y.Z`

## Теги — только аннотированные

```bash
git tag -a v0.1.0 -m "Release 0.1.0"
git push origin v0.1.0
```

Не переписывать после публикации. Плохой `v0.2.0` → выпускайте `v0.2.1`.

## Релиз

1. `main` зелёный (сборка + тесты на 3 ОС).
2. Bump `VERSION` в `CMakeLists.txt`.
3. PR → squash merge.
4. `git tag -a vX.Y.Z -m "..."` → push.
5. GitHub Releases → Draft new release → Publish.
6. Обновить потребителей: в Superbuild поменять `GIT_TAG v0.2.0`.

## CI — черновик

`.github/workflows/ci.yml`:

```yaml
name: CI

on:
  push:
    branches: [ main ]
  pull_request:
    branches: [ main ]

jobs:
  build:
    strategy:
      fail-fast: false
      matrix:
        os: [ ubuntu-latest, windows-latest, macos-latest ]
    runs-on: ${{ matrix.os }}

    steps:
      - uses: actions/checkout@v4

      - name: Install Ninja
        uses: seanmiddleditch/gha-setup-ninja@v4

      - name: Configure
        run: cmake -S . -B build -DWITHLAND_CORE_BUILD_TESTS=ON

      - name: Build
        run: cmake --build build --config Debug --parallel

      - name: Test
        run: ctest --test-dir build -C Debug --output-on-failure --timeout 30
```

## Правила

1. `main` — только зелёная сборка.
2. Нетривиальные правки — через ветку + PR.
3. Один релиз = один тег = один GitHub Release.
4. Версия в `CMakeLists.txt` = имя тега.
5. Опубликованный тег не переписывается.
6. Потребители ссылаются на **тег**, не на `main`.
7. Все три ОС должны собирать один коммит.

## Что дальше

- `.github/workflows/ci.yml` — когда появится CI.
- `.github/CODEOWNERS` — если команда расширится.
- `CHANGELOG.md` — если захочется вести историю релизов явно.