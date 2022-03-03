::
::   __________ ____  
::  |__  / ____|  _ \ 
::    / /|  _| | | | |
::   / /_| |___| |_| |
::  /____|_____|____/ 
:: Copyright (C) 2020 - 2022
::
:: License:  Revised BSD License, see LICENSE.TXT file included in the project
:: Authors:  David Zwart (ZED)
:: Version: 1.0.0
:: Date 7 Nov 2021
::
:: Description:
::  Setup the protobuf protocol based on EmbeddedProto

:: This script will perform various actions to setup everything to get you started with this example

:: Setup the submodule embedded proto
cd EmbeddedProto
call setup.bat
cd ..

:: Setup the virtual environment for the desktop Python script.
cd tools/GatewayController
python -m venv venv
call .\venv\Scripts\activate.bat & pip install -r requirements.txt & call .\venv\Scripts\deactivate.bat
cd ../..

:: Generate the source code based on the *.proto files.
call generate_source_files.bat
