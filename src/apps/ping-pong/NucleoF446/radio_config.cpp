#include "radio_config.h"

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

void SetTxPower(int8_t power) {
    Radio.Standby();

    txConf.set_Power(power);

    Radio.Rx(0);
}

void SetTxConfig(DeviceConfiguration& config) {
    Radio.Standby();

    txConf.set_Power(config.get_TxPower());
    txConf.set_Bandwidth(config.get_TxBandwidth());
    txConf.set_DataRate(config.get_TxDataRate());
    ApplyRadioTxConfig();

    Radio.Rx(0);
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

// void ApplyRadioConfig() {
//     Radio.Standby();

//     ApplyRadioTxConfig();
//     ApplyRadioRxConfig();

//     Radio.Rx(0);
// }

// void PrintSettings() {
//     printf("--RADIO SETTINGS--\nModem:%d\n\tPower:%ld\n\tFdev:%lu\n\tBandwidth:%lu\n\tDataRate:%lu\n\tCodeRate:%lu\n\tPreambleLen:%lu\n\tFixLen:%d\n\tCrCOn:%d\n\tFreqHopOn:%d\n\tHopPeriod:%lu\n\tIqInverted:%d\n\tTimeout:%lu\n--END OF RADIO SETTINGS--\n",
//            (int)txConf.Modem(), txConf.Power(), txConf.Fdev(), txConf.Bandwidth(), txConf.DataRate(), txConf.CodeRate(), txConf.PreambleLen(),
//            txConf.FixLen(), txConf.CrcOn(), txConf.FreqHopOn(), txConf.HopPeriod(), txConf.IqInverted(), txConf.Timeout());

//     // TODO RX settings
//     // , % ld, % ld, % d, % ld, % d, % d, % d, % d, % d, % d, % d, % d
//     // printf("", rxConfig.Modem, rxConfig.Bandwidth, rxConfig.DataRate, rxConfig.CodeRate, rxConfig.BandwidthAfc, rxConfig.PreambleLen, rxConfig.FixLen, rxConfig.PayloadLen, rxConfig.CrcOn, rxConfig.FreqHopOn, rxConfig.HopPeriod, rxConfig.IqInverted, rxConfig.RxContinuous);
// }

// void UpdateRadioSpreadingFactor(uint8_t spreadingFactorRx, uint8_t spreadingFactorTx, bool reconnect) {
//     txConf.set_DataRate(spreadingFactorTx);
//     rxConf.set_DataRate(spreadingFactorRx);

//     if (reconnect) {
//         ApplyRadioConfig();
//     }
// }

// void ApplyConfigIfPending() {
//     if (!pendingConfigChange)
//         return;
//     pendingConfigChange = false;
//     ApplyRadioConfig();
// }
