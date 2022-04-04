cmake_minimum_required(VERSION 3.0)

project("EVote")

if (UNIX)
    set(CMAKE_TOOLCHAIN_FILE "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    # set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/vcpkg/installed/x64-linux/share")
endif (UNIX)
if (WIN32)
    # emplacement de VCPKG si nécessaire
endif (WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE})

add_subdirectory(src/authorities)
add_subdirectory(src/bulletins)

set(SRCS
        main.cpp
        src/Properties.cpp
        src/KeyGeneration.cpp
        src/Verifier.cpp     
    )

set(HEADERS 
        src/Properties.hpp
        src/CryptoUtils.hpp
        src/KeyGeneration.hpp
        src/Verifier.hpp
    )


add_compile_options(-Wall -g)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (${PROJECT_NAME}  ${SRCS} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE headers)

# find_package(boost REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)
