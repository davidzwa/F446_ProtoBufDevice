# F446_ProtoBufDevice
STM32 F446RE firmware repository hard forked from on https://github.com/Lora-net/LoRaMac-node by SemTech.
Please refer to that repository for issues concerning the CMake setup.

## LoRaWAN end-device firmware update stack using Random Linear Network Coding

The aim of this project is to show an example of an end-device LoRaWAN stack implementation for a novel way to do Firmware-Updates Over-The-Air (FUOTA). This code is a Firmware Update testbed for evaluation of Random Linear Network Coding (RLNC).

## Introduction

RLNC is a different coding method than Low-Density Parity Checks (LDPC) currently suggested for use with FUOTA. RLNC has higher decoding efficiency and it is more flexible to adjust redundancy thresholds in case of packet loss. This could be even made dynamic using feedback MAC commands.
For more info on RLNC we advice you to look up this expired draft IETF specification:
https://tools.ietf.org/id/draft-heide-nwcrg-rlnc-03.html

The following alternatives exist:
- Sliding-window RLNC decoder
- (Adaptive) Fulcrum decoder
- IDNC ([Instantly Decodable Network Coding](https://www.researchgate.net/publication/277722795_Performance_Characterization_and_Transmission_Schemes_for_Instantly_Decodable_Network_Coding_in_Wireless_Broadcast))
- LTNC (Luby-Transform Network Code)
- LDPC (Low-Density Parity Checks)

We selected RLNC because it shows some very interesting properties. A Fulcrum decoder reduces the computational complexity, but with the low data rate of FUOTA and RLNC this is note a stringent issue at all. Also, LDPC clearly has lower decoding efficiency of about 2%. Using GF(256) RLNC has a near-perfect decoding efficiency: no extra information needs to be received to be able to decode.

This repository provides research performed during my MSc thesis at the Technical University of Delft. 
The structure is as follows:
- `src` firmware implementation using compiled EmbeddedProto files
- `proto` protobuf files for EmbeddedProto (find this library here: https://github.com/Embedded-AMS/EmbeddedProto)
- `tools/rlnc_prob` time-discrete simulations, models amd many plots for evaluating RLNC configurations 
- `tools/GatewayController` outdated Python gateway implementation
- `tools/*` lots of stlink scripts to dump the flash contents or write Flash Replay binaries to the F446 device
- `rlnc_replays` (outdated) experimental RLNC Flash Replay (control plane replay command) binaries compiled using EmbeddedProto serialization and a custom structure

For an updated gateway in C# and updated RLNC Flash Replay binaries we refer you to https://github.com/davidzwa/LoRaConfigurator instead!

## Background 

This project provides implementations for ClassA, ClassB and ClassC end-device classes, but these have been detached from the PHY layer for direct evaluation of the decoding method.

Furthremore, it also provides SX1272/73, SX1276/77/78/79, SX1261/2 and LR1110 radio drivers. The SX1261 is configured right now.

For each currently supported platform example applications are provided.
* **ping-pong**: Main RLNC application stack.
**Note**: *The LoRaWAN stack API documentation can be found at: http://stackforce.github.io/LoRaMac-doc/*

## Supported platforms

This project currently only provides support for the STM32 Nucleo64 F446RE.  
This project can be ported to other platforms using different MCU than the ones currently supported.  
The [Porting Guide](https://stackforce.github.io/LoRaMac-doc/LoRaMac-doc-v4.5.1/_p_o_r_t_i_n_g__g_u_i_d_e.html) document provides guide lines on how to port the project to other platforms.

* STM32 Nucleo64 F446RE datasheet
  * [https://www.st.com/resource/en/datasheet/stm32f446re.pdf]

## Getting Started

### Prerequisites

Please follow instructions provided by [Development environment](doc/development-environment.md) document.

### Cloning the repository

Clone the repository from GitHub

```bash
$ git clone https://github.com/lora-net/loramac-node.git loramac-node
```

LoRaMac-node project contains Git submodules that must be initialized

```bash
$ cd loramac-node
$ git submodule update --init
```

### Building Process

#### Command line

**ping-pong** example using LoRa modulation for NucleoL476 platform with LR1110MB1DIS MBED shield

```bash
$ mkdir build
$ cd build
$ cmake -DCMAKE_BUILD_TYPE=Release \
        -DTOOLCHAIN_PREFIX="<replace by toolchain path>" \
        -DCMAKE_TOOLCHAIN_FILE="../cmake/toolchain-arm-none-eabi.cmake" \
        -DAPPLICATION="ping-pong" \
        -DMODULATION:"LORA" \
        -DREGION_EU868="ON" \
        -DREGION_US915="OFF" \
        -DREGION_CN779="OFF" \
        -DREGION_EU433="OFF" \
        -DREGION_AU915="OFF" \
        -DREGION_AS923="OFF" \
        -DREGION_CN470="OFF" \
        -DREGION_KR920="OFF" \
        -DREGION_IN865="OFF" \
        -DREGION_RU864="OFF" \
        -DBOARD="NucleoL476" \
        -DMBED_RADIO_SHIELD="LR1110MB1XXS" \
        -DUSE_RADIO_DEBUG="ON" ..
$ make
```

#### VSCode

**ping-pong** example using LoRa modulation for NucleoL476 platform with LR1110MB1DIS MBED shield

* Please edit .vscode/settings.json file

<details>
  <summary>Click to expand!</summary>
<p>

```json
// Place your settings in this file to overwrite default and user settings.
{
    "cmake.configureSettings": {

        // In case your GNU ARM-Toolchain is not installed under the default
        // path:
        //     Windows : No default path. Specify the path where the
        //               toolchain is installed. i.e:
        //               "C:/PROGRA~2/GNUTOO~1/92019-~1".
        //     Linux   : /usr
        //     OSX     : /usr/local
        // It is required to uncomment and to fill the following line.
        "TOOLCHAIN_PREFIX":"/path/to/toolchain",

        // In case your OpenOCD is not installed under the default path:
        //     Windows : C:/openocd/bin/openocd.exe
        //     Linux   : /usr/bin/openocd
        //     OSX     : /usr/local/bin/openocd
        // Please uncomment the following line and fill it accordingly.
        //"OPENOCD_BIN":"C:/openocd/bin/openocd.exe",

        // Specifies the path to the CMAKE toolchain file.
        "CMAKE_TOOLCHAIN_FILE":"cmake/toolchain-arm-none-eabi.cmake",

        // Determines the application. You can choose between:
        // LoRaMac (Default), ping-pong, rx-sensi, tx-cw.
        "APPLICATION":"ping-pong",

        // Select LoRaMac sub project. You can choose between:
        // periodic-uplink-lpp, fuota-test-01.
        "SUB_PROJECT":"periodic-uplink-lpp",

        // Switch for Class B support of LoRaMac:
        "CLASSB_ENABLED":"ON",

        // Select the active region for which the stack will be initialized.
        // You can choose between:
        // LORAMAC_REGION_EU868, LORAMAC_REGION_US915, ..
        "ACTIVE_REGION":"LORAMAC_REGION_EU868",

        // Select the type of modulation, applicable to the ping-pong or
        // rx-sensi applications. You can choose between:
        // LORA or FSK
        "MODULATION":"LORA",

        // Target board, the following boards are supported:
        // NAMote72, NucleoL073 (Default), NucleoL152, NucleoL476, SAMR34, SKiM880B, SKiM980A, SKiM881AXL, B-L072Z-LRWAN1.
        "BOARD":"NucleoL476",

        // MBED Radio shield selection. (Applies only to Nucleo platforms)
        // The following shields are supported:
        // SX1272MB2DAS, SX1276MB1LAS, SX1276MB1MAS, SX1261MBXBAS(Default), SX1262MBXCAS, SX1262MBXDAS, LR1110MB1XXS.
        "MBED_RADIO_SHIELD":"SX1261MBXBAS",

        // Secure element type selection the following are supported
        // SOFT_SE(Default), LR1110_SE, ATECC608A_TNGLORA_SE
        "SECURE_ELEMENT":"SOFT_SE",

        // Secure element is pre-provisioned
        "SECURE_ELEMENT_PRE_PROVISIONED":"ON",

        // Region support activation, Select the ones you want to support.
        // By default only REGION_EU868 support is enabled.
        "REGION_EU868":"ON",
        "REGION_US915":"OFF",
        "REGION_CN779":"OFF",
        "REGION_EU433":"OFF",
        "REGION_AU915":"OFF",
        "REGION_AS923":"OFF",
        "REGION_CN470":"OFF",
        "REGION_KR920":"OFF",
        "REGION_IN865":"OFF",
        "REGION_RU864":"OFF",
        "USE_RADIO_DEBUG":"ON"
    }
}
```
</p>
</details>

## Acknowledgments

* This repository was forked from [LoRaMac-node](https://github.com/Lora-net/LoRaMac-node/tree/master)
* It makes good use of Efficient UART and Flash serialization interface using [EmbeddedProto](https://github.com/Embedded-AMS/EmbeddedProto) by the company Embedded AMS
* The mbed (https://mbed.org/) project was used at the beginning as source of
inspiration.
* This program uses the AES algorithm implementation (http://www.gladman.me.uk/) by Brian Gladman.
* This program uses the CMAC algorithm implementation
(http://www.cse.chalmers.se/research/group/dcs/masters/contikisec/) by Lander Casado, Philippas Tsigas.
* [The Things Industries](https://www.thethingsindustries.com/) for providing
 Microchip/Atmel SAMR34 platform and ATECC608A-TNGLORA secure-element support.
* Tencent Blade Team for security breach findings and solving propositions.
