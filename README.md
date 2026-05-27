# C++ Serialization — Companion Examples

Runnable code accompanying the lecture *Serialization & Save Systems*
(C++17/20). One folder per chapter, each producing a standalone
executable.

## Layout

| Folder                      | Lecture chapter                          | Executable               |
|-----------------------------|------------------------------------------|--------------------------|
| `01_invariant/`             | Partie 1 — The save/load symmetry         | `01_invariant`           |
| `02_use_cases/`             | Partie 2 — Save (time) vs transmit (space)| `02_use_cases`           |
| `03_text_vs_binary/`        | Partie 3 — Text vs binary + endianness    | `03_text_vs_binary`      |
| `04_raw_memory/`            | Partie 4 — `reinterpret_cast` for PODs    | `04_raw_memory`          |
| `05_boost/` *(optional)*    | Partie 5 — Boost.Serialization            | `05_boost` (if Boost found) |
| `06_visitor/`               | Partie 6 — The Visitor pattern (Writer/Reader) | `06_visitor`        |
| `07_exercise_tilemap/`      | Exercice — Magic + versioned tilemap save | `07_exercise_tilemap`    |

## Requirements

- A C++20 compiler (MSVC 19.3x, GCC 11+, Clang 14+)
- CMake ≥ 3.20
- *Optional:* Boost.Serialization for chapter 5
  - vcpkg (manifest mode): `vcpkg install` from the repo root —
    picks up `vcpkg.json` and pulls only `boost-serialization`
  - vcpkg (classic): `vcpkg install boost-serialization`
  - Debian/Ubuntu: `sudo apt install libboost-serialization-dev`
  - Homebrew: `brew install boost`

## Build (CLI)

```bash
cmake -S . -B build
cmake --build build
```

Run any example:

```bash
./build/01_invariant
./build/06_visitor
./build/07_exercise_tilemap
```

## Build (CLion)

1. **File → Open…** and pick this folder.
2. CLion auto-detects the top-level `CMakeLists.txt`.
3. Pick a target (e.g. `06_visitor`) in the run configuration dropdown.
4. Hit ▶ Run.

Every chapter is a separate target, so you can jump straight to the one
you care about without building the rest.

## Notes

- Chapter 5 (`05_boost`) is built only if CMake finds Boost. Otherwise
  it is silently skipped with a status message — no broken build.
- Endianness conversion in chapter 3 is done by hand (no
  `<winsock2.h>` / `<arpa/inet.h>`) to keep the example portable.
- Chapter 7 uses `std::filesystem::temp_directory_path()` for its
  artifacts — nothing is written to the repo.
