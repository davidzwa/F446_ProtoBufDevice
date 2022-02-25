##
##   __________ ____  
##  |__  / ____|  _ \ 
##    / /|  _| | | | |
##   / /_| |___| |_| |
##  /____|_____|____/ 
## Copyright (C) 2020 - 2022
##
## License:  Revised BSD License, see LICENSE.TXT file included in the project
## Authors:  David Zwart (ZED), Niels Hokke (ZED)
## Version: 0.1.1
## Date 21 Sept 2021
##
## Description:
##  Intended to provide a template for overriding cmake variables locally

# Get the path of this module
set(CURRENT_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})
set(DOT_VSCODE_FOLDER ${CMAKE_SOURCE_DIR}/.vscode)
set(LOCAL_SETTINGS_JSON_VSCODE_TEMPLATE ${CURRENT_MODULE_DIR}/cmake-settings.local.json.in)
set(LOCAL_SETTINGS_JSON_VSCODE ${DOT_VSCODE_FOLDER}/cmake-settings.local.json)
set(LOCAL_SETTINGS_CMAKE_VSCODE_TEMPLATE ${CURRENT_MODULE_DIR}/cmake-settings.local.cmake.in)
set(LOCAL_SETTINGS_CMAKE_VSCODE ${DOT_VSCODE_FOLDER}/cmake-settings.local.cmake)
set(JSON_MACRO_FILE ${CURRENT_MODULE_DIR}/json-macro.cmake)

## Save the templated file
if (NOT EXISTS ${LOCAL_SETTINGS_JSON_VSCODE})
    configure_file(${LOCAL_SETTINGS_JSON_VSCODE_TEMPLATE} ${LOCAL_SETTINGS_JSON_VSCODE} @ONLY)
endif()
if (NOT EXISTS ${LOCAL_SETTINGS_CMAKE_VSCODE})
    configure_file(${LOCAL_SETTINGS_CMAKE_VSCODE_TEMPLATE} ${LOCAL_SETTINGS_CMAKE_VSCODE} @ONLY)
endif()

# Load cmake file with local json loading inside (using macros)
include(${JSON_MACRO_FILE})

# Trigger the local overrides in the .vscode folder 
include(${LOCAL_SETTINGS_CMAKE_VSCODE})
