#include "radio_config.h"

#include "delay.h"
#include "lora_phy.h"

RadioRxConfig rxConf;
RadioTxConfig txConf;

void InitRadioTxConfigLoRa() {
    txConf.set_Modem(RadioModems::MODEM_LORA);
    txConf.set_Power(TX_OUTPUT_POWER);
    txConf.set_Fdev(0);
    txConf.set_Bandwidth(LORA_BANDWIDTH);
    txConf.set_DataRate(LORA_SPREADING_FACTOR);
    txConf.set_CodeRate(LORA_CODINGRATE);
    txConf.set_PreambleLen(LORA_PREAMBLE_LENGTH);
    txConf.set_FixLen(LORA_FIX_LENGTH_PAYLOAD_ON);
    txConf.set_CrcOn(LORA_CRC_ON);
    txConf.set_FreqHopOn(0);
    txConf.set_HopPeriod(0);
    txConf.set_IqInverted(LORA_IQ_INVERSION_ON);
    txConf.set_Timeout(RX_TIMEOUT_VALUE);
}

void InitRadioRxConfigLoRa() {
    rxConf.set_Modem(RadioModems::MODEM_LORA);
    rxConf.set_Bandwidth(LORA_BANDWIDTH);
    rxConf.set_DataRate(LORA_SPREADING_FACTOR);
    rxConf.set_CodeRate(LORA_CODINGRATE);
    rxConf.set_BandwidthAfc(0);
    rxConf.set_PreambleLen(LORA_PREAMBLE_LENGTH);
    rxConf.set_FixLen(LORA_FIX_LENGTH_PAYLOAD_ON);
    rxConf.set_PayloadLen(0);
    rxConf.set_CrcOn(LORA_CRC_ON);
    rxConf.set_FreqHopOn(0);
    rxConf.set_HopPeriod(0);
    rxConf.set_IqInverted(LORA_IQ_INVERSION_ON);
    rxConf.set_RxContinuous(LORA_CONT_LISTEN);
}

int32_t GetTxPower() {
    return txConf.get_Power();
}

uint32_t GetTxDataRate() {
    return txConf.get_DataRate();
}

uint32_t GetTxBandwidth() {
    return txConf.get_Bandwidth();
}

void SetTxPower(int8_t power) {
    Radio.Standby();
    txConf.set_Power(power);
    Radio.Rx(0);
}

void SetTxRxConfig(const TransmitReceiveConfiguration& config, bool listenAfter) {
    Radio.Standby();

    if (config.get_SetRx()) {
        rxConf.set_Bandwidth(config.get_TxRxBandwidth());
        rxConf.set_DataRate(config.get_TxRxDataRate());
        ApplyRadioRxConfig();
    }

    if (config.get_SetTx()) {
        txConf.set_Power(config.get_TxPower());
        txConf.set_DataRate(config.get_TxRxDataRate());
        txConf.set_Bandwidth(config.get_TxRxBandwidth());
        ApplyRadioTxConfig();
    }

    if (listenAfter) {
        DelayMs(2);
        Radio.Rx(0);
    }
}

void ApplyRadioTxConfig() {
    Radio.SetTxConfig(
        (RadioModems_t)txConf.Modem(), txConf.Power(), txConf.Fdev(), txConf.Bandwidth(),
        txConf.DataRate(), txConf.CodeRate(),
        txConf.PreambleLen(), txConf.FixLen(),
        txConf.CrcOn(), txConf.FreqHopOn(), txConf.HopPeriod(), txConf.IqInverted(), txConf.Timeout());
}

void ApplyRadioRxConfig() {
    Radio.SetRxConfig(
        (RadioModems_t)rxConf.Modem(), rxConf.Bandwidth(),
        rxConf.DataRate(), rxConf.CodeRate(),
        rxConf.BandwidthAfc(), rxConf.PreambleLen(),
        rxConf.SymbTimeout(), rxConf.FixLen(), rxConf.PayloadLen(),
        rxConf.CrcOn(), rxConf.FreqHopOn(), rxConf.HopPeriod(), rxConf.IqInverted(), rxConf.RxContinuous());
}