::
::   __________ ____  
::  |__  / ____|  _ \ 
::    / /|  _| | | | |
::   / /_| |___| |_| |
::  /____|_____|____/ 
:: Copyright (C) 2020 - 2021
::
:: License:  Revised BSD License, see LICENSE.TXT file included in the project
:: Authors:  David Zwart (ZED)
:: Version: 1.0.0
:: Date 2 Feb 2022
::
:: Description:
::  Fetch flash sector 128k of st-link

.\\stlink\\stlink-1.7.0-x86_64-w64-mingw32\\bin\\st-flash.exe read .\\data\\nucleo 0x08020000 131072
