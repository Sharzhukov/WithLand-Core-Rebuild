# WithlandCore-Rebuild — Git и GitHub

## Ежедневный цикл

```bash
git pull
git checkout -b feature/my-thing
# ...работа...
git add .
git commit -m "feat: my thing"
git push -u origin feature/my-thing
# PR → approve → squash merge
```

## Ветки

| Ветка | Назначение |
|---|---|
| `main` | Защищена, только через PR |
| `feature/<name>` | Новая функциональность |
| `fix/<name>` | Багфиксы |
| `docs/<name>` | Документация |
| `chore/<name>` | Рутина |

## Сообщения коммитов — Conventional Commits

```
feat: ...      новая функциональность
fix: ...       багфикс
docs: ...      документация
refactor: ...  переработка без изменения поведения
test: ...      тесты
build: ...     CMake, CI, зависимости
chore: ...     рутина
```

## Теги

```bash
git tag -a v0.1.0 -m "Release 0.1.0"
git push origin v0.1.0
git ls-remote --tags origin
```

Только **аннотированные** (`-a`). Версия тега синхронна с `project(VERSION)` в `CMakeLists.txt`.

## Релиз

1. Проверить, что `main` зелёный.
2. Поднять `VERSION` в `CMakeLists.txt`.
3. Коммит `build: bump version to X.Y.Z` → PR → merge.
4. `git tag -a vX.Y.Z -m "Release X.Y.Z" && git push origin vX.Y.Z`
5. GitHub → Releases → Draft new release → выбрать тег → Publish.

## Hotfix

```bash
git checkout main && git pull
git checkout -b fix/crash
# правка
git commit -m "fix: crash"
git push -u origin fix/crash
# PR → merge

git checkout main && git pull
git tag -a v0.2.1 -m "Hotfix"
git push origin v0.2.1
```

## Защита main

Правила Ruleset:

| Правило | Статус |
|---|---|
| Require a pull request before merging | ✅ |
| └ Require approvals: 1 | ✅ |
| └ Dismiss stale approvals | ✅ |
| └ Require conversation resolution | ✅ |
| Require linear history | ✅ |
| Do not allow bypassing | ✅ |
| Require status checks | ⏳ после CI |
| Allow force pushes | ❌ |
| Allow deletions | ❌ |

Настройки PR (Settings → General → Pull Requests):

- `Allow merge commits` — ❌
- `Allow squash merging` — ✅ (единственный способ)
- `Automatically delete head branches` — ✅

⚠️ GitHub не даёт approve'ить свой PR — нужен второй trusted reviewer.

## Что НЕ коммитить

- `build/`, `out/`, `cmake-build-*/`
- `.vs/`, `.vscode/`, `.idea/`, `*.user`
- `.DS_Store`, `._*`
- `CMakeCache.txt`, `CMakeFiles/`, `cmake_install.cmake`
- скомпилированные бинарники
- секреты и ключи

## Полезное

```bash
git log --oneline --graph --decorate --all
git show <hash>
git blame <file>
git stash / git stash pop
git restore --staged <file>      # убрать из индекса
git revert <hash>                # безопасный откат
```

## Быстрая шпаргалка

```bash
# Ежедневно
git pull && git checkout -b feature/x
git add . && git commit -m "feat: x"
git push -u origin feature/x

# После merge
git checkout main && git pull
git branch -d feature/x

# Релиз
git tag -a vX.Y.Z -m "Release X.Y.Z"
git push origin vX.Y.Z
```