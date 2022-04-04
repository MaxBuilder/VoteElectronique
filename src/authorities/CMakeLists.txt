cmake_minimum_required(VERSION 3.0)

project("authorities")

set(SRCS
        LocalAuthority.cpp
        RegionalAuthority.cpp
        NationalAuthority.cpp
        BulletinBoard.cpp
    )
    
set(HEADERS
        Center.hpp
        LocalAuthority.hpp
        RegionalAuthority.hpp
        NationalAuthority.hpp
        BulletinBoard.hpp
    )

add_library("authorities" ${SRCS} ${HEADERS})
