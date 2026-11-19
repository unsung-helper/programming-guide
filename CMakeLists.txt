cmake_minimum_required(VERSION 3.16)

project(custom VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -s USE_PTHREADS=1")
    set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS}   -pthread -s USE_PTHREADS=1")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread -s USE_PTHREADS=1 -s FETCH=1 --bind")
    set(LIB_SUFFIX "_wasm")
else()
    set(LIB_SUFFIX "")
endif()

add_definitions(-DEIGEN_INITIALIZE_MATRICES_BY_ZERO)

set(EXTERNALS_DIR ${CMAKE_CURRENT_LIST_DIR}/externals)
set(ENGINE_DIR    ${CMAKE_CURRENT_LIST_DIR}/engine)

foreach(LIB Clipper2 Clipper2Z freetype OpenMeshCore OpenMeshTools stb)
    add_library(${LIB} STATIC IMPORTED GLOBAL)
    set_target_properties(${LIB} PROPERTIES
        IMPORTED_LOCATION "${EXTERNALS_DIR}/lib/lib${LIB}${LIB_SUFFIX}.a"
    )
endforeach()

add_library(engine STATIC IMPORTED GLOBAL)
set_target_properties(engine PROPERTIES
    IMPORTED_LOCATION "${ENGINE_DIR}/lib/libengine${LIB_SUFFIX}.a"
    # Eigen headers install under externals/include/eigen3 and the engine's public
    # headers (Vec2.h/Vec3.h/Mesh.h) include "Eigen/Core", so that directory must
    # be on the include path too (matches cmake/pipeline/CMakeLists.txt).
    INTERFACE_INCLUDE_DIRECTORIES "${ENGINE_DIR}/include;${EXTERNALS_DIR}/include;${EXTERNALS_DIR}/include/eigen3"
    INTERFACE_LINK_LIBRARIES "Clipper2;Clipper2Z;freetype;OpenMeshCore;OpenMeshTools;stb"
)

add_subdirectory(engineConfigurator)
