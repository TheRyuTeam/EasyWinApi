cmake_minimum_required(VERSION 3.2)
project(EasyWinApi CXX)

set(LIBNAME ${PROJECT_NAME})

if(NOT CMAKE_C_STANDARD)
    set(CMAKE_C_STANDARD 14)
endif()
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_LIBRARY_PATH "C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.22621.0\\um\\x64")

find_library(WINMM WinMM REQUIRED)
set(LIBSOURCE
    include/ewa/ewa.hpp
    include/ewa/common/Color.hpp
    include/ewa/common/Pen.hpp
    include/ewa/common/Brush.hpp
    include/ewa/widgets/Widget.hpp
    include/ewa/widgets/Window.hpp
    include/ewa/common/Point.hpp
    include/ewa/paints/Canvas.hpp
    include/ewa/paints/BMPCanvas.hpp
    include/ewa/core/Event.hpp
    include/ewa/core/EventFilter.hpp
    include/ewa/paints/2d/Figure2d.hpp
    include/ewa/paints/2d/Scene2d.hpp
    include/ewa/paints/2d/Drawable.hpp
    include/ewa/common/Size.hpp
    include/ewa/common/Rect.hpp
    include/ewa/common/Bitmap.hpp
    include/ewa/core/Keyboard.hpp
    include/ewa/common/Key.hpp
    include/ewa/core/AudioPlayer.hpp

    src/common/Pen.cpp
    src/common/Brush.cpp
    src/core/CoreApplication.cpp
    src/widgets/Widget.cpp
    src/widgets/Window.cpp
    src/paints/Canvas.cpp
    src/paints/BMPCanvas.cpp
    src/core/EventFilter.cpp
    src/paints/2d/Figure2d.cpp
    src/paints/2d/Scene2d.cpp
    src/common/Rect.cpp
    src/common/Size.cpp
    src/common/Bitmap.cpp
    src/core/Keyboard.cpp
    src/core/AudioPlayer.cpp
)

add_library(${LIBNAME}md STATIC
    ${LIBSOURCE}
)
target_link_libraries(${LIBNAME}md
    PRIVATE PRIVATE ${WINMM}
)
set_target_properties(${LIBNAME}md
    PROPERTIES
        LINKER_LANGUAGE CXX
)
target_include_directories(${LIBNAME}md
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_compile_definitions(${LIBNAME}md
    PUBLIC
    EWA_STATIC
)

if(ENABLE_EXAMPLES)
    add_subdirectory("examples/Shooting shuttle")
endif()



