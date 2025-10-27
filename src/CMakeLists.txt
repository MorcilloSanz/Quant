project(Quant)

# --- Exe ---
set(HEADERS 
    window/window.h
    gui/styles.h
    gui/gui.h
    gui/views/view.h
    gui/views/generalview.h
    gui/views/candlestickview.h
    gui/views/sdeview.h
    gui/views/indicatorview.h
    ticker/tickerdata.h
    util/csv.h
    util/split.h
)

set(SOURCES
    main.cpp
    window/window.cpp
    gui/styles.cpp
    gui/gui.cpp
    gui/views/generalview.cpp
    gui/views/candlestickview.cpp
    gui/views/sdeview.cpp
    gui/views/indicatorview.cpp
    ticker/tickerdata.cpp
)

add_executable(Quant ${SOURCES} ${HEADERS})

# --- Link libraries ---
target_link_libraries(Quant PRIVATE glfw glew_s imgui)

if (WIN32)
    target_link_libraries(Quant PRIVATE opengl32 glfw glew_s imgui)
endif()

target_include_directories(Quant PRIVATE
    ${glew_SOURCE_DIR}/include
)