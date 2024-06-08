# ---------------------------------------------------
# CMakeLists.txt
#
# Author: Thomas Choquet <thomas.publique@icloud.com>
# Date: 2024/05/26 12:54:56
# ---------------------------------------------------

cmake_minimum_required(VERSION 3.23)

project(FdF LANGUAGES C CXX OBJC OBJCXX)

add_executable(FdF)

file(GLOB_RECURSE FDF_SOURCES
    "2DGraphics/*.c"      "2DGraphics/*.h"
    "3DGraphics/*.c"      "3DGraphics/*.h"
    "sources/*.c"         "includes/*.h"
    "Libft/*.c"           "Libft/*.h"
    "MiniLibXWrapper/*.c" "MiniLibXWrapper/*.h"
)
target_sources(FdF PRIVATE ${FDF_SOURCES})

target_include_directories(FdF PRIVATE 
    "2DGraphics/includes"
    "3DGraphics/includes"
    "includes"
    "Libft/includes"
    "MiniLibXWrapper/includes"
)

find_program(GIT_PATH git REQUIRED)
execute_process(COMMAND ${GIT_PATH} submodule update --init MinilibX WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory("MinilibX")

set_target_properties(mlx PROPERTIES FOLDER "dependencies")
if(TARGET MLX_MetalShaderLibrary)
    set_target_properties(MLX_MetalShaderLibrary PROPERTIES FOLDER "dependencies")
endif()

target_link_libraries(FdF mlx)

target_include_directories(FdF PRIVATE "MinilibX/include/mlx")