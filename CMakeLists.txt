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

# add_subdirectory(src)

set(SRCS
        main.cpp
        src/Properties.cpp
        src/App.cpp

        src/cryptosystem/KeyGeneration.cpp
        src/cryptosystem/Encryption.cpp
        src/cryptosystem/Combiner.cpp
        src/cryptosystem/CryptoServer.cpp
        
        src/Prover.cpp
        src/Verifier.cpp  
        
        src/authorities/LocalAuthority.cpp
        src/authorities/RegionalAuthority.cpp
        src/authorities/NationalAuthority.cpp
        src/authorities/BulletinBoard.cpp

        src/bulletins/LocalBulletin.cpp
        src/bulletins/RegionalBulletin.cpp
        src/bulletins/NationalBulletin.cpp

        src/cryptosystem/sha256.cpp
        src/Client.cpp
    )

set(HEADERS 
        src/Properties.hpp
        src/App.hpp

        src/cryptosystem/CryptoUtils.hpp
        src/cryptosystem/KeyGeneration.hpp
        src/cryptosystem/Encryption.hpp
        src/cryptosystem/Combiner.hpp
        src/cryptosystem/CryptoServer.hpp

        src/Prover.hpp
        src/Verifier.hpp

        src/authorities/Center.hpp
        src/authorities/LocalAuthority.hpp
        src/authorities/RegionalAuthority.hpp
        src/authorities/NationalAuthority.hpp
        src/authorities/BulletinBoard.hpp

        src/bulletins/Bulletin.hpp
        src/bulletins/LocalBulletin.hpp
        src/bulletins/RegionalBulletin.hpp
        src/bulletins/NationalBulletin.hpp

        src/cryptosystem/sha256.hpp
        src/Client.hpp
    )


add_compile_options(-Wall -g -O3 -lboost_random)

add_subdirectory(nlohmann_json)

# include_directories(src/)
# include_directories(src/bulletins)
# include_directories(src/authorities)

# Ajoutez une source à l'exécutable de ce projet.
add_executable (${PROJECT_NAME}  ${SRCS} ${HEADERS})

# find_package(boost REQUIRED)
find_package(Boost 1.71 COMPONENTS random REQUIRED)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS}) 
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json ${Boost_LIBRARIES})
