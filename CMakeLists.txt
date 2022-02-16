cmake_minimum_required(VERSION 3.8)

project("Electronic Vote")

# find_package(boost REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/${CMAKE_BUILD_TYPE})

set(SRCS	main.cpp
            src/LocalAuthority.cpp
            src/RegionalAuthority.cpp
            src/NationalAuthority.cpp
    )

set(HEADERS headers/CryptoUtils.hpp
            headers/Bulletin.hpp
			headers/BulletinBoard.hpp
            headers/LocalBulletin.hpp
            headers/RegionalBulletin.hpp
            headers/NationalBulletin.hpp

            headers/Verifier.hpp # ToDo : problème verifier / bulletinboard

			headers/Center.hpp
            headers/LocalAuthority.hpp
            headers/RegionalAuthority.hpp
            headers/NationalAuthority.hpp
    )

add_compile_options(-Wall -g)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (EVote  ${SRCS} ${HEADERS})

target_include_directories(EVote PRIVATE headers)
