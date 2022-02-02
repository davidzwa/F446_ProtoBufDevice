# 
#    __________ ____  
#   |__  / ____|  _ \ 
#     / /|  _| | | | |
#    / /_| |___| |_| |
#   /____|_____|____/ 
#  Copyright (C) 2020 - 2021
# 
#  License:  Revised BSD License, see LICENSE.TXT file included in the project
#  Authors:  David Zwart (ZED)
#  Version: 1.0.0
#  Date 7 Nov 2021
# 
#  Description:
#   Generate protobuf files for an embedded device

#  Generate the embedded source code.

$SRC=".\src\protobuf"
$SRC_REL_EAMS=".\src\protobuf"
$OUT_PYTHON=".\tools\GatewayController\protobuf"
$OUT_CSHARP="..\LoraGateway\Protobuf"
$DIR_REL_EAMS=".\proto"
$DIR=".\proto"
$PROTO_DESKTOP_FILES="proto\uart_messages.proto"
$PROTO_EMBEDDED_FILES= ${PROTO_DESKTOP_FILES} + " proto\lora_device_messages.proto"

$SRC="proto"
$PLUGIN=".\EmbeddedProto\protoc-gen-eams.bat"
$OUT_CPP="src\protobuf"
$OUT_PYTHON=".\tools\GatewayController\protobuf"
$OUT_CSHARP="..\LoraGateway\Protobuf"

echo "Ensuring output folders exist (C++, Python, C#)"
mkdir ${OUT_CPP} -ErrorAction SilentlyContinue
mkdir ${OUT_PYTHON} -ErrorAction SilentlyContinue
mkdir ${OUT_CSHARP} -ErrorAction SilentlyContinue
mkdir ${OUT_CSHARP}\shared -ErrorAction SilentlyContinue

echo "Calling protoc (C++, Python, C#) in $PWD"
protoc --proto_path=$SRC --eams_out=$OUT_CPP ./$SRC/*.proto --plugin=protoc-gen-eams=${PLUGIN}
protoc --proto_path=$SRC --csharp_out=$OUT_CSHARP\shared ./$SRC/shared/**.proto
protoc --proto_path=$SRC --csharp_out=$OUT_CSHARP ./$SRC/**.proto
