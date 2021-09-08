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
if(TSL_2561)
    file(GLOB ${PROJECT_NAME}_SOURCES "*.cpp" "tsl2561_/*.cpp")
    message(STATUS "Added ZED tsl2561 I2C peripheral (C++)")
else()
    message(STATUS "Did not add ZED tsl2561 I2C peripheral (C++)")
endif()

if(BME_68X) 
    file(GLOB ${PROJECT_NAME}_SOURCES "*.cpp" "bme68x/*.cpp")
    message(STATUS "Added ZED bme68x I2C peripheral (C++)")
else()
    message(STATUS "Did not add ZED bme68x I2C peripheral (C++)")    
endif()

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

if(TSL_2561)
    target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/tsl2561_)    
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_TSL_2561)
endif()

if(BME_68X) 
    target_include_directories( ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bme68x)    
    target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_BME_68X)
endif()

target_include_directories( ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    $<TARGET_PROPERTY:board,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:system,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:mac,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:radio,INTERFACE_INCLUDE_DIRECTORIES>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
