cmake_minimum_required(VERSION 3.0)

project("bulletins")

set(SRCS
        LocalBulletin.cpp
        RegionalBulletin.cpp
        NationalBulletin.cpp
    )
    
set(HEADERS
        Bulletin.hpp
        LocalBulletin.hpp
        RegionalBulletin.hpp
        NationalBulletin.hpp
    )

add_library("bulletins" ${SRCS} ${HEADERS})
