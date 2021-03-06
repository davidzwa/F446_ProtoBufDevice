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
## Date 20 Sept 2021
##
## Description:
##  Easily override known variables locally and programatically
##  Configure cmake to ensure the variables are cached

# LOCAL_SETTINGS_JSON_VSCODE is defined by 'apps/cmake/settings/settings-generator.cmake'
message("[.vscode/cmake-settings.local.cmake]")
readJsonFile(${LOCAL_SETTINGS_JSON_VSCODE} JSON_PARSED)
message("\tFile: " ${LOCAL_SETTINGS_JSON_VSCODE})

# Unpack the JSON 'JSON_PARSED.' prefix and set the variables for build

foreach(json_var ${JSON_PARSED})
    string(REPLACE "JSON_PARSED." "" property ${json_var})

    set(${property} ${${json_var}})
    unset(${json_var})
    message("\t${property} = ${${property}}")
endforeach()

# You can still set anything you want
# set(TOOLCHAIN_PREFIX "C:/Program Files (x86)/GNU Arm Embedded Toolchain/10 2020-q4-major")
# set(APPLICATION "wl55-subghz-phy")

# Clean up
unset(LOCAL_SETTINGS_JSON_VSCODE)
