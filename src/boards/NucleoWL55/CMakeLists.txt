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
project(NucleoWL55)
cmake_minimum_required(VERSION 3.6)
enable_language(ASM)

#---------------------------------------------------------------------------------------
# Target
#---------------------------------------------------------------------------------------

list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/adc-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/board.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/delay-board.c"
    # "${CMAKE_CURRENT_SOURCE_DIR}/eeprom-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/gpio-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/i2c-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/lpm-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/rtc-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/spi-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/sysIrqHandlers.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/uart-board.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../stm32/utilities.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/CMSIS/Device/ST/STM32WLxx/Source/Templates/gcc/startup_stm32wl55xx_cm4.s"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/CMSIS/Device/ST/STM32WLxx/Source/Templates/system_stm32wlxx.c"

    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_adc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_adc_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_comp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_cortex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_crc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_crc_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_cryp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_cryp_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_dac.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_dac_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_dma.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_dma_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_exti.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_flash.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_flash_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_gpio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_gtzc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_hsem.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_i2c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_i2c_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_i2s.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_ipcc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_irda.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_iwdg.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_lptim.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_msp_template.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_pka.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_pwr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_pwr_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rcc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rcc_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rng.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rng_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rtc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_rtc_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_smartcard.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_smartcard_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_smbus.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_smbus_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_spi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_spi_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_subghz.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_tim.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_timebase_rtc_alarm_template.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_timebase_rtc_wakeup_template.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_timebase_tim_template.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_tim_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_uart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_uart_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_usart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_usart_ex.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_hal_wwdg.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_adc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_comp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_crc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_dac.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_dma.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_exti.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_gpio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_i2c.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_lptim.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_lpuart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_pka.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_pwr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_rcc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_rng.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_rtc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_spi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_tim.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_usart.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Src/stm32wlxx_ll_utils.c"
)

# if(MBED_RADIO_SHIELD STREQUAL SX1261MBXBAS)
#     list(APPEND ${PROJECT_NAME}_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/sx1261mbxbas-board.c")
# else()
#     message(STATUS " Please specify the MBED_RADIO_SHIELD !\nPossible values are: SX1261MBXBAS.")
# endif()

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

target_compile_definitions(${PROJECT_NAME} PUBLIC -DUSE_HAL_DRIVER -DSTM32WL55)

# Add define if debbuger support is enabled
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<BOOL:${USE_DEBUGGER}>:USE_DEBUGGER>)

# Add define if radio debug pins support is enabled
target_compile_definitions(${PROJECT_NAME} PUBLIC $<$<BOOL:${USE_RADIO_DEBUG}>:USE_RADIO_DEBUG>)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/STM32WLxx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../targets/STM32WL/Drivers/CMSIS/Device/ST/STM32WLxx/Include

    # ${CMAKE_CURRENT_SOURCE_DIR}/../stm32
    # ${CMAKE_CURRENT_SOURCE_DIR}/../stm32/cmsis
    # ${CMAKE_CURRENT_SOURCE_DIR}/../stm32/STM32F4xx_HAL_Driver/Inc
    # ${CMAKE_CURRENT_SOURCE_DIR}/../stm32/EEPROM_Emul/Core
    # ${CMAKE_CURRENT_SOURCE_DIR}/../stm32/EEPROM_Emul/Porting/STM32F4
    $<TARGET_PROPERTY:board,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:system,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:radio,INTERFACE_INCLUDE_DIRECTORIES>
    $<TARGET_PROPERTY:peripherals,INTERFACE_INCLUDE_DIRECTORIES>
)

set_property(TARGET ${PROJECT_NAME} PROPERTY C_STANDARD 11)
