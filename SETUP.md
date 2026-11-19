# Unsung SDK — Setup Guide

This SDK lets you write a custom **EngineConfigurator** that defines your product's
node graph, and then upload the resulting library to the Unsung editor so it can be
used during editing and exported as a standalone WebAssembly module.

---

## What's included

| Path | Description |
|------|-------------|
`engineConfigurator/EngineConfigurator.cpp` | **Your starting point.** Implement `configure()` here. |
`engineConfigurator/EngineConfigurator.h` | Public interface — do not modify. |
`engine/` | Pre-compiled engine library + headers. |
`externals/` | Pre-compiled third-party libraries (OpenMesh, Clipper2, freetype, …). |
`.devcontainer/` | VS Code Dev Containers configuration (see below). |
`.vscode/tasks.json` | Build tasks — **"Export SDK (zip)"** is the default (`Ctrl+Shift+B`); all four also show as status-bar buttons. |
`.vscode/c_cpp_properties.json` | IntelliSense config (points at `build_native/compile_commands.json`). |
`build.sh` | Same thing from the terminal: `./build.sh [export\|all\|native\|wasm]`. |

---

## Quick start with VS Code Dev Containers (recommended)

This is the easiest approach and works identically on Linux, macOS, and Windows.
The container matches the exact build environment used by the Unsung backend,
so your library will be binary-compatible.

### Prerequisites

**Linux**
1. Install [Docker Engine](https://docs.docker.com/engine/install/)
   and add your user to the `docker` group:
   ```bash
   sudo usermod -aG docker $USER   # log out and back in afterwards
```
2. Install [Visual Studio Code](https://code.visualstudio.com/)
3. Install the **Dev Containers** extension
   (`ms-vscode-remote.remote-containers`) inside VS Code

**macOS**
1. Install [Docker Desktop for Mac](https://www.docker.com/products/docker-desktop/)
   and start it
2. Install [Visual Studio Code](https://code.visualstudio.com/)
3. Install the **Dev Containers** extension inside VS Code

**Windows**
1. Enable WSL 2 (run in PowerShell as Administrator):
   ```powershell
   wsl --install
```
   Reboot when prompted.
2. Install [Docker Desktop for Windows](https://www.docker.com/products/docker-desktop/)
   — in settings, enable **"Use the WSL 2 based engine"**
3. Install [Visual Studio Code](https://code.visualstudio.com/)
4. Install the **Dev Containers** extension inside VS Code

> **Tip (Windows):** For best performance, extract this zip inside the WSL 2
> filesystem (`\\wsl$\Ubuntu\home\<user>\`), not on the Windows C: drive.

### Open in container

1. Extract this zip to a folder of your choice
2. Open VS Code and choose **File → Open Folder…**, then select the extracted folder
3. VS Code will detect `.devcontainer/` and show a notification:
   **"Reopen in Container"** — click it
   (or open the Command Palette with `Ctrl+Shift+P` / `⌘+Shift+P`
   and run **"Dev Containers: Reopen in Container"**)
4. Docker will build the image the first time (~5–10 minutes depending on your
   internet connection). Subsequent opens are instant.
5. Once inside the container, open the integrated terminal
   (`Ctrl+` `` ` ``) and you are ready to build.

---

## Building & exporting

### The easy way (VS Code)

Just press `Ctrl+Shift+B`. That runs the default build task,
**"Export SDK (zip)"**, which builds **both** libraries in Release and packages
them into:

```
unsung-configurator.zip     ← upload this
```

(containing `libengineConfigurator.a` and `libengineConfigurator_wasm.a`).

**Building something else / changing the target.** There is no target picker —
each build is a task. Every task also has a **button on the left of the status
bar** (`⚙ native`, `wasm`, `Build all`, `Export SDK`); click one to run it.
You can also open **Terminal → Run Task…** (or `Ctrl+Shift+P` →
*Tasks: Run Task*):

| Task | Builds |
|------|--------|
| **Export SDK (zip)** | both, Release, + `unsung-configurator.zip` *(the `Ctrl+Shift+B` default)* |
| **Build all (Release)** | both, Release, no zip |
| **Build native (Release)** | `build_native/…/libengineConfigurator.a` — fastest while iterating |
| **Build WebAssembly (Release)** | `build_wasm/…/libengineConfigurator_wasm.a` |

To make a different task the `Ctrl+Shift+B` default, move
`"group": { "kind": "build", "isDefault": true }` onto it in
`.vscode/tasks.json`. Compiler errors land in the **Problems** panel.

> **Why no "CMake: Build" button?** The CMake Tools extension is intentionally
> left out — in this container the compilers are fixed and there are two
> toolchains (host GCC + Emscripten), so its "Select a Kit" / target prompts are
> just friction. The tasks above drive CMake directly, and the `actboy168.tasks`
> extension gives them status-bar buttons.

> Want the container to build once automatically right after it is created?
> Change `postCreateCommand` in `.devcontainer/devcontainer.json` to
> `bash build.sh`.

### From the terminal

```bash
./build.sh          # build both + package unsung-configurator.zip
./build.sh all      # build both, no zip
./build.sh native   # native only
./build.sh wasm     # WebAssembly only
```

### By hand

Run inside the dev container terminal:

```bash
# native
cmake -B build_native -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build_native

# WebAssembly
source /opt/emsdk/emsdk_env.sh    # a new dev-container terminal already has this
emcmake cmake -B build_wasm -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build_wasm

# package
cmake -E tar cf unsung-configurator.zip --format=zip -- \
    build_native/engineConfigurator/libengineConfigurator.a \
    build_wasm/engineConfigurator/libengineConfigurator_wasm.a
```

---

## Uploading to the editor

1. Open the Unsung **dashboard**
2. On your product's row, click **"Upload SDK"**
3. Select `unsung-configurator.zip` (produced by **Export SDK (zip)**)
4. The backend rebuilds the WASM editor with your library automatically —
   watch the progress bar on the dashboard. If it fails, use
   **"Download log"** to see why; your previous build stays in use.
5. Reopen your product — your custom nodes are now available

---

## Workflow

```
Edit EngineConfigurator.cpp
        │
        ▼
Run "Export SDK (zip)"   (Ctrl+Shift+B)   →  unsung-configurator.zip
        │
        ▼
Upload unsung-configurator.zip via "Upload SDK" on the dashboard
        │
        ▼
Reopen / reconnect to product in the editor
```

---

## Tips

- **IntelliSense**: driven by `build_native/compile_commands.json` via
  `.vscode/c_cpp_properties.json`. It is approximate until your first
  native build (**Build native (Release)**), then fully accurate. No CMake
  configure step needed.
- **Multiple products**: you can reuse the same SDK folder for multiple products.
  Just upload `unsung-configurator.zip` to the relevant product in the editor.
- **Iteration**: while you work, use **"Build native (Release)"** — only the
  native library is used during editing. Run **"Export SDK (zip)"** once you are
  ready to upload.
