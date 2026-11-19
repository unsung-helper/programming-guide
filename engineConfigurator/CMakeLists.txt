add_library(engineConfigurator STATIC
    EngineConfigurator.cpp
    EngineConfigurator.h
    AngleParameter.cpp
    AngleParameter.h
    OFFReader.cpp
    OFFReader.h
    OFFWriter.cpp
    OFFWriter.h
    Twist.cpp
    Twist.h
    Degrees.cpp
    Degrees.h
    Radians.cpp
    Radians.h
)
target_link_libraries(engineConfigurator PUBLIC engine)
target_include_directories(engineConfigurator PUBLIC ${CMAKE_CURRENT_LIST_DIR})

if(EMSCRIPTEN)
    set_target_properties(engineConfigurator PROPERTIES OUTPUT_NAME engineConfigurator_wasm)
endif()
