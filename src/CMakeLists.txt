project(Quant)

# --- Exe ---
add_executable(Quant main.cpp)

# --- Link libraries ---
target_link_libraries(Quant PRIVATE glfw glew_s)

if (WIN32)
    target_link_libraries(Quant PRIVATE opengl32 glfw glew_s)
endif()

target_include_directories(Quant PRIVATE
    ${glew_SOURCE_DIR}/include
)