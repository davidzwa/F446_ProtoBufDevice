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
:: Date 7 Nov 2021
::
:: Description:
::  Generate protobuf files for an embedded device

:: Generate the embedded source code.
mkdir .\src\protobuf

cd EmbeddedProto
protoc --plugin=protoc-gen-eams=protoc-gen-eams.bat -I..\proto --eams_out=..\src\protobuf ..\proto\uart_messages.proto
cd ..

:: Generate the desktop source code.
mkdir .\tools\GatewayController\protobuf
protoc -I.\proto --python_out=.\tools\GatewayController\protobuf .\proto\uart_messages.proto
