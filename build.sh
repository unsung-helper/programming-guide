#!/usr/bin/env bash
# Build the Unsung engineConfigurator libraries (always Release).
#
#   ./build.sh            same as 'export'
#   ./build.sh export     build both, then package unsung-configurator.zip for upload
#   ./build.sh all        build both native + WebAssembly
#   ./build.sh native     build only build_native/engineConfigurator/libengineConfigurator.a
#   ./build.sh wasm       build only build_wasm/engineConfigurator/libengineConfigurator_wasm.a
#
set -euo pipefail
cd "$(dirname "$0")"

NATIVE_LIB=build_native/engineConfigurator/libengineConfigurator.a
WASM_LIB=build_wasm/engineConfigurator/libengineConfigurator_wasm.a
EXPORT_ZIP=unsung-configurator.zip

build_native() {
    echo "==> native (Release)"
    cmake -B build_native -G Ninja -DCMAKE_BUILD_TYPE=Release
    cmake --build build_native
    echo "==> $NATIVE_LIB"
}

build_wasm() {
    echo "==> WebAssembly (Release)"
    set +u; source /opt/emsdk/emsdk_env.sh; set -u
    emcmake cmake -B build_wasm -G Ninja -DCMAKE_BUILD_TYPE=Release
    cmake --build build_wasm
    echo "==> $WASM_LIB"
}

build_export() {
    build_native
    build_wasm
    echo "==> packaging $EXPORT_ZIP"
    local root stage
    root="$PWD"
    stage="$(mktemp -d)"
    cp "$NATIVE_LIB" "$WASM_LIB" "$stage/"
    rm -f "$EXPORT_ZIP"
    ( cd "$stage" && cmake -E tar cf "$root/$EXPORT_ZIP" --format=zip -- \
        libengineConfigurator.a libengineConfigurator_wasm.a )
    rm -rf "$stage"
    echo
    echo "==> $EXPORT_ZIP"
    echo "    Upload this file via \"Upload SDK\" on the dashboard."
}

case "${1:-export}" in
    export) build_export ;;
    all)    build_native; build_wasm ;;
    native) build_native ;;
    wasm)   build_wasm ;;
    *) echo "usage: $0 [export|all|native|wasm]" >&2; exit 2 ;;
esac
