cmake_minimum_required(VERSION 3.8)

project("EVote")

if (UNIX)
    set(CMAKE_TOOLCHAIN_FILE "${PROJECT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")
    # set(CMAKE_PREFIX_PATH "${PROJECT_SOURCE_DIR}/vcpkg/installed/x64-linux/share")
endif (UNIX)
if (WIN32)
    # emplacement de VCPKG si nécessaire
endif (WIN32)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE})

set(SRCS	main.cpp
            src/Properties.cpp
            src/BulletinBoard.cpp
            src/LocalBulletin.cpp
            src/RegionalBulletin.cpp
            src/NationalBulletin.cpp

            src/Verifier.cpp

            src/LocalAuthority.cpp
            src/RegionalAuthority.cpp
            src/NationalAuthority.cpp
    )

set(HEADERS 
            headers/Properties.hpp
            headers/CryptoUtils.hpp
            headers/Bulletin.hpp
			headers/BulletinBoard.hpp
            headers/LocalBulletin.hpp
            headers/RegionalBulletin.hpp
            headers/NationalBulletin.hpp

            headers/Verifier.hpp

			headers/Center.hpp
            headers/LocalAuthority.hpp
            headers/RegionalAuthority.hpp
            headers/NationalAuthority.hpp
    )


add_compile_options(-Wall -g)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (${PROJECT_NAME}  ${SRCS} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE headers)

# find_package(boost REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_object jsoncpp_static JsonCpp::JsonCpp)
