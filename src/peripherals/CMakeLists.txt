##
##   ______                              _
##  / _____)             _              | |
## ( (____  _____ ____ _| |_ _____  ____| |__
##  \____ \| ___ |    (_   _) ___ |/ ___)  _ \
##  _____) ) ____| | | || |_| ____( (___| | | |
## (______/|_____)_|_|_| \__)_____)\____)_| |_|
## (C)2013-2017 Semtech
##  ___ _____ _   ___ _  _____ ___  ___  ___ ___
## / __|_   _/_\ / __| |/ / __/ _ \| _ \/ __| __|
## \__ \ | |/ _ \ (__| ' <| _| (_) |   / (__| _|
## |___/ |_/_/ \_\___|_|\_\_| \___/|_|_\\___|___|
## embedded.connectivity.solutions.==============
##
## License:  Revised BSD License, see LICENSE.TXT file included in the project
## Authors:  Johannes Bruder (STACKFORCE), Miguel Luis (Semtech)
##
project(peripherals)
cmake_minimum_required(VERSION 3.6)

#---------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------
set(source_folders "*.cpp ")

if(BME_68X) 
    file (GLOB files "path/to/files/*")

    list(APPEND source_folders "bme68x/*.cpp ")
    # file(GLOB ${PROJECT_NAME}_SOURCES "*.cpp" "bme68x/*.cpp")
    message(STATUS "Added ZED bme68x I2C peripheral (C++)")
else()
    message(STATUS "Did not add ZED bme68x I2C peripheral (C++)")    
endif()

if(TSL_2561)
    file (GLOB files2 "path/to/files2*")
    list (APPEND files ${files2})
    list(APPEND source_folders "tsl2561/*.cpp ")
    message(STATUS "Added ZED tsl2561 I2C peripheral (C++)")
else()
    message(STATUS "Did not add ZED tsl2561 I2C peripheral (C++)")
endif()

file(GLOB ${PROJECT_NAME}_SOURCES ${source_folders})
add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

if(TSL_2561)
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tsl2561)
endif()

if(BME_68X) 
    target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bme68x)    
endif()

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<TARGET_PROPERTY:board,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:system,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:mac,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:radio,INTERFACE_INCLUDE_DIRECTORIES>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
