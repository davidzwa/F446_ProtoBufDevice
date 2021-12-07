/*
 *  Copyright (C) 2020-2021 Embedded AMS B.V. - All Rights Reserved
 *
 *  This file is part of Embedded Proto.
 *
 *  Embedded Proto is open source software: you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License as published
 *  by the Free Software Foundation, version 3 of the license.
 *
 *  Embedded Proto  is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Embedded Proto. If not, see <https://www.gnu.org/licenses/>.
 *
 *  For commercial and closed source application please visit:
 *  <https://EmbeddedProto.com/license/>.
 *
 *  Embedded AMS B.V.
 *  Info:
 *    info at EmbeddedProto dot com
 *
 *  Postal address:
 *    Johan Huizingalaan 763a
 *    1066 VH, Amsterdam
 *    the Netherlands
 */

// This file is generated. Please do not edit!
#ifndef UART_MESSAGES_H
#define UART_MESSAGES_H

#include <cstdint>
#include <MessageInterface.h>
#include <WireFormatter.h>
#include <Fields.h>
#include <MessageSizeCalculator.h>
#include <ReadBufferSection.h>
#include <RepeatedFieldFixedSize.h>
#include <FieldStringBytes.h>
#include <Errors.h>
#include <limits>

// Include external proto definitions


enum class RadioModems : uint32_t
{
  MODEM_FSK = 0,
  MODEM_LORA = 1
};

class RadioRxConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    RadioRxConfig() = default;
    RadioRxConfig(const RadioRxConfig& rhs )
    {
      set_Modem(rhs.get_Modem());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_BandwidthAfc(rhs.get_BandwidthAfc());
      set_PreambleLen(rhs.get_PreambleLen());
      set_SymbTimeout(rhs.get_SymbTimeout());
      set_FixLen(rhs.get_FixLen());
      set_PayloadLen(rhs.get_PayloadLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_RxContinuous(rhs.get_RxContinuous());
    }

    RadioRxConfig(const RadioRxConfig&& rhs ) noexcept
    {
      set_Modem(rhs.get_Modem());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_BandwidthAfc(rhs.get_BandwidthAfc());
      set_PreambleLen(rhs.get_PreambleLen());
      set_SymbTimeout(rhs.get_SymbTimeout());
      set_FixLen(rhs.get_FixLen());
      set_PayloadLen(rhs.get_PayloadLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_RxContinuous(rhs.get_RxContinuous());
    }

    ~RadioRxConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MODEM = 1,
      BANDWIDTH = 2,
      DATARATE = 3,
      CODERATE = 4,
      BANDWIDTHAFC = 5,
      PREAMBLELEN = 6,
      SYMBTIMEOUT = 7,
      FIXLEN = 8,
      PAYLOADLEN = 9,
      CRCON = 10,
      FREQHOPON = 11,
      HOPPERIOD = 12,
      IQINVERTED = 13,
      RXCONTINUOUS = 14
    };

    RadioRxConfig& operator=(const RadioRxConfig& rhs)
    {
      set_Modem(rhs.get_Modem());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_BandwidthAfc(rhs.get_BandwidthAfc());
      set_PreambleLen(rhs.get_PreambleLen());
      set_SymbTimeout(rhs.get_SymbTimeout());
      set_FixLen(rhs.get_FixLen());
      set_PayloadLen(rhs.get_PayloadLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_RxContinuous(rhs.get_RxContinuous());
      return *this;
    }

    RadioRxConfig& operator=(const RadioRxConfig&& rhs) noexcept
    {
      set_Modem(rhs.get_Modem());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_BandwidthAfc(rhs.get_BandwidthAfc());
      set_PreambleLen(rhs.get_PreambleLen());
      set_SymbTimeout(rhs.get_SymbTimeout());
      set_FixLen(rhs.get_FixLen());
      set_PayloadLen(rhs.get_PayloadLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_RxContinuous(rhs.get_RxContinuous());
      return *this;
    }

    inline void clear_Modem() { Modem_ = static_cast<RadioModems>(0); }
    inline void set_Modem(const RadioModems& value) { Modem_ = value; }
    inline void set_Modem(const RadioModems&& value) { Modem_ = value; }
    inline const RadioModems& get_Modem() const { return Modem_; }
    inline RadioModems Modem() const { return Modem_; }

    inline void clear_Bandwidth() { Bandwidth_.clear(); }
    inline void set_Bandwidth(const EmbeddedProto::uint32& value) { Bandwidth_ = value; }
    inline void set_Bandwidth(const EmbeddedProto::uint32&& value) { Bandwidth_ = value; }
    inline EmbeddedProto::uint32& mutable_Bandwidth() { return Bandwidth_; }
    inline const EmbeddedProto::uint32& get_Bandwidth() const { return Bandwidth_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Bandwidth() const { return Bandwidth_.get(); }

    inline void clear_DataRate() { DataRate_.clear(); }
    inline void set_DataRate(const EmbeddedProto::uint32& value) { DataRate_ = value; }
    inline void set_DataRate(const EmbeddedProto::uint32&& value) { DataRate_ = value; }
    inline EmbeddedProto::uint32& mutable_DataRate() { return DataRate_; }
    inline const EmbeddedProto::uint32& get_DataRate() const { return DataRate_; }
    inline EmbeddedProto::uint32::FIELD_TYPE DataRate() const { return DataRate_.get(); }

    inline void clear_CodeRate() { CodeRate_.clear(); }
    inline void set_CodeRate(const EmbeddedProto::uint32& value) { CodeRate_ = value; }
    inline void set_CodeRate(const EmbeddedProto::uint32&& value) { CodeRate_ = value; }
    inline EmbeddedProto::uint32& mutable_CodeRate() { return CodeRate_; }
    inline const EmbeddedProto::uint32& get_CodeRate() const { return CodeRate_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CodeRate() const { return CodeRate_.get(); }

    inline void clear_BandwidthAfc() { BandwidthAfc_.clear(); }
    inline void set_BandwidthAfc(const EmbeddedProto::uint32& value) { BandwidthAfc_ = value; }
    inline void set_BandwidthAfc(const EmbeddedProto::uint32&& value) { BandwidthAfc_ = value; }
    inline EmbeddedProto::uint32& mutable_BandwidthAfc() { return BandwidthAfc_; }
    inline const EmbeddedProto::uint32& get_BandwidthAfc() const { return BandwidthAfc_; }
    inline EmbeddedProto::uint32::FIELD_TYPE BandwidthAfc() const { return BandwidthAfc_.get(); }

    inline void clear_PreambleLen() { PreambleLen_.clear(); }
    inline void set_PreambleLen(const EmbeddedProto::uint32& value) { PreambleLen_ = value; }
    inline void set_PreambleLen(const EmbeddedProto::uint32&& value) { PreambleLen_ = value; }
    inline EmbeddedProto::uint32& mutable_PreambleLen() { return PreambleLen_; }
    inline const EmbeddedProto::uint32& get_PreambleLen() const { return PreambleLen_; }
    inline EmbeddedProto::uint32::FIELD_TYPE PreambleLen() const { return PreambleLen_.get(); }

    inline void clear_SymbTimeout() { SymbTimeout_.clear(); }
    inline void set_SymbTimeout(const EmbeddedProto::uint32& value) { SymbTimeout_ = value; }
    inline void set_SymbTimeout(const EmbeddedProto::uint32&& value) { SymbTimeout_ = value; }
    inline EmbeddedProto::uint32& mutable_SymbTimeout() { return SymbTimeout_; }
    inline const EmbeddedProto::uint32& get_SymbTimeout() const { return SymbTimeout_; }
    inline EmbeddedProto::uint32::FIELD_TYPE SymbTimeout() const { return SymbTimeout_.get(); }

    inline void clear_FixLen() { FixLen_.clear(); }
    inline void set_FixLen(const EmbeddedProto::boolean& value) { FixLen_ = value; }
    inline void set_FixLen(const EmbeddedProto::boolean&& value) { FixLen_ = value; }
    inline EmbeddedProto::boolean& mutable_FixLen() { return FixLen_; }
    inline const EmbeddedProto::boolean& get_FixLen() const { return FixLen_; }
    inline EmbeddedProto::boolean::FIELD_TYPE FixLen() const { return FixLen_.get(); }

    inline void clear_PayloadLen() { PayloadLen_.clear(); }
    inline void set_PayloadLen(const EmbeddedProto::uint32& value) { PayloadLen_ = value; }
    inline void set_PayloadLen(const EmbeddedProto::uint32&& value) { PayloadLen_ = value; }
    inline EmbeddedProto::uint32& mutable_PayloadLen() { return PayloadLen_; }
    inline const EmbeddedProto::uint32& get_PayloadLen() const { return PayloadLen_; }
    inline EmbeddedProto::uint32::FIELD_TYPE PayloadLen() const { return PayloadLen_.get(); }

    inline void clear_CrcOn() { CrcOn_.clear(); }
    inline void set_CrcOn(const EmbeddedProto::boolean& value) { CrcOn_ = value; }
    inline void set_CrcOn(const EmbeddedProto::boolean&& value) { CrcOn_ = value; }
    inline EmbeddedProto::boolean& mutable_CrcOn() { return CrcOn_; }
    inline const EmbeddedProto::boolean& get_CrcOn() const { return CrcOn_; }
    inline EmbeddedProto::boolean::FIELD_TYPE CrcOn() const { return CrcOn_.get(); }

    inline void clear_FreqHopOn() { FreqHopOn_.clear(); }
    inline void set_FreqHopOn(const EmbeddedProto::boolean& value) { FreqHopOn_ = value; }
    inline void set_FreqHopOn(const EmbeddedProto::boolean&& value) { FreqHopOn_ = value; }
    inline EmbeddedProto::boolean& mutable_FreqHopOn() { return FreqHopOn_; }
    inline const EmbeddedProto::boolean& get_FreqHopOn() const { return FreqHopOn_; }
    inline EmbeddedProto::boolean::FIELD_TYPE FreqHopOn() const { return FreqHopOn_.get(); }

    inline void clear_HopPeriod() { HopPeriod_.clear(); }
    inline void set_HopPeriod(const EmbeddedProto::uint32& value) { HopPeriod_ = value; }
    inline void set_HopPeriod(const EmbeddedProto::uint32&& value) { HopPeriod_ = value; }
    inline EmbeddedProto::uint32& mutable_HopPeriod() { return HopPeriod_; }
    inline const EmbeddedProto::uint32& get_HopPeriod() const { return HopPeriod_; }
    inline EmbeddedProto::uint32::FIELD_TYPE HopPeriod() const { return HopPeriod_.get(); }

    inline void clear_IqInverted() { IqInverted_.clear(); }
    inline void set_IqInverted(const EmbeddedProto::boolean& value) { IqInverted_ = value; }
    inline void set_IqInverted(const EmbeddedProto::boolean&& value) { IqInverted_ = value; }
    inline EmbeddedProto::boolean& mutable_IqInverted() { return IqInverted_; }
    inline const EmbeddedProto::boolean& get_IqInverted() const { return IqInverted_; }
    inline EmbeddedProto::boolean::FIELD_TYPE IqInverted() const { return IqInverted_.get(); }

    inline void clear_RxContinuous() { RxContinuous_.clear(); }
    inline void set_RxContinuous(const EmbeddedProto::boolean& value) { RxContinuous_ = value; }
    inline void set_RxContinuous(const EmbeddedProto::boolean&& value) { RxContinuous_ = value; }
    inline EmbeddedProto::boolean& mutable_RxContinuous() { return RxContinuous_; }
    inline const EmbeddedProto::boolean& get_RxContinuous() const { return RxContinuous_; }
    inline EmbeddedProto::boolean::FIELD_TYPE RxContinuous() const { return RxContinuous_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<RadioModems>(0) != Modem_) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(Modem_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::MODEM), buffer, false);
      }

      if((0U != Bandwidth_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Bandwidth_.serialize_with_id(static_cast<uint32_t>(id::BANDWIDTH), buffer, false);
      }

      if((0U != DataRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DataRate_.serialize_with_id(static_cast<uint32_t>(id::DATARATE), buffer, false);
      }

      if((0U != CodeRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CodeRate_.serialize_with_id(static_cast<uint32_t>(id::CODERATE), buffer, false);
      }

      if((0U != BandwidthAfc_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = BandwidthAfc_.serialize_with_id(static_cast<uint32_t>(id::BANDWIDTHAFC), buffer, false);
      }

      if((0U != PreambleLen_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = PreambleLen_.serialize_with_id(static_cast<uint32_t>(id::PREAMBLELEN), buffer, false);
      }

      if((0U != SymbTimeout_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SymbTimeout_.serialize_with_id(static_cast<uint32_t>(id::SYMBTIMEOUT), buffer, false);
      }

      if((false != FixLen_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FixLen_.serialize_with_id(static_cast<uint32_t>(id::FIXLEN), buffer, false);
      }

      if((0U != PayloadLen_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = PayloadLen_.serialize_with_id(static_cast<uint32_t>(id::PAYLOADLEN), buffer, false);
      }

      if((false != CrcOn_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CrcOn_.serialize_with_id(static_cast<uint32_t>(id::CRCON), buffer, false);
      }

      if((false != FreqHopOn_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FreqHopOn_.serialize_with_id(static_cast<uint32_t>(id::FREQHOPON), buffer, false);
      }

      if((0U != HopPeriod_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = HopPeriod_.serialize_with_id(static_cast<uint32_t>(id::HOPPERIOD), buffer, false);
      }

      if((false != IqInverted_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = IqInverted_.serialize_with_id(static_cast<uint32_t>(id::IQINVERTED), buffer, false);
      }

      if((false != RxContinuous_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = RxContinuous_.serialize_with_id(static_cast<uint32_t>(id::RXCONTINUOUS), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::MODEM:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_Modem(static_cast<RadioModems>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
            break;

          case id::BANDWIDTH:
            return_value = Bandwidth_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DATARATE:
            return_value = DataRate_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CODERATE:
            return_value = CodeRate_.deserialize_check_type(buffer, wire_type);
            break;

          case id::BANDWIDTHAFC:
            return_value = BandwidthAfc_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PREAMBLELEN:
            return_value = PreambleLen_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SYMBTIMEOUT:
            return_value = SymbTimeout_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FIXLEN:
            return_value = FixLen_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PAYLOADLEN:
            return_value = PayloadLen_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CRCON:
            return_value = CrcOn_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FREQHOPON:
            return_value = FreqHopOn_.deserialize_check_type(buffer, wire_type);
            break;

          case id::HOPPERIOD:
            return_value = HopPeriod_.deserialize_check_type(buffer, wire_type);
            break;

          case id::IQINVERTED:
            return_value = IqInverted_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RXCONTINUOUS:
            return_value = RxContinuous_.deserialize_check_type(buffer, wire_type);
            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_Modem();
      clear_Bandwidth();
      clear_DataRate();
      clear_CodeRate();
      clear_BandwidthAfc();
      clear_PreambleLen();
      clear_SymbTimeout();
      clear_FixLen();
      clear_PayloadLen();
      clear_CrcOn();
      clear_FreqHopOn();
      clear_HopPeriod();
      clear_IqInverted();
      clear_RxContinuous();

    }

    private:


      RadioModems Modem_ = static_cast<RadioModems>(0);
      EmbeddedProto::uint32 Bandwidth_ = 0U;
      EmbeddedProto::uint32 DataRate_ = 0U;
      EmbeddedProto::uint32 CodeRate_ = 0U;
      EmbeddedProto::uint32 BandwidthAfc_ = 0U;
      EmbeddedProto::uint32 PreambleLen_ = 0U;
      EmbeddedProto::uint32 SymbTimeout_ = 0U;
      EmbeddedProto::boolean FixLen_ = false;
      EmbeddedProto::uint32 PayloadLen_ = 0U;
      EmbeddedProto::boolean CrcOn_ = false;
      EmbeddedProto::boolean FreqHopOn_ = false;
      EmbeddedProto::uint32 HopPeriod_ = 0U;
      EmbeddedProto::boolean IqInverted_ = false;
      EmbeddedProto::boolean RxContinuous_ = false;

};

class RadioTxConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    RadioTxConfig() = default;
    RadioTxConfig(const RadioTxConfig& rhs )
    {
      set_Modem(rhs.get_Modem());
      set_Power(rhs.get_Power());
      set_Fdev(rhs.get_Fdev());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_PreambleLen(rhs.get_PreambleLen());
      set_FixLen(rhs.get_FixLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_Timeout(rhs.get_Timeout());
    }

    RadioTxConfig(const RadioTxConfig&& rhs ) noexcept
    {
      set_Modem(rhs.get_Modem());
      set_Power(rhs.get_Power());
      set_Fdev(rhs.get_Fdev());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_PreambleLen(rhs.get_PreambleLen());
      set_FixLen(rhs.get_FixLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_Timeout(rhs.get_Timeout());
    }

    ~RadioTxConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MODEM = 1,
      POWER = 2,
      FDEV = 3,
      BANDWIDTH = 4,
      DATARATE = 5,
      CODERATE = 6,
      PREAMBLELEN = 7,
      FIXLEN = 8,
      CRCON = 9,
      FREQHOPON = 10,
      HOPPERIOD = 11,
      IQINVERTED = 12,
      TIMEOUT = 13
    };

    RadioTxConfig& operator=(const RadioTxConfig& rhs)
    {
      set_Modem(rhs.get_Modem());
      set_Power(rhs.get_Power());
      set_Fdev(rhs.get_Fdev());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_PreambleLen(rhs.get_PreambleLen());
      set_FixLen(rhs.get_FixLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_Timeout(rhs.get_Timeout());
      return *this;
    }

    RadioTxConfig& operator=(const RadioTxConfig&& rhs) noexcept
    {
      set_Modem(rhs.get_Modem());
      set_Power(rhs.get_Power());
      set_Fdev(rhs.get_Fdev());
      set_Bandwidth(rhs.get_Bandwidth());
      set_DataRate(rhs.get_DataRate());
      set_CodeRate(rhs.get_CodeRate());
      set_PreambleLen(rhs.get_PreambleLen());
      set_FixLen(rhs.get_FixLen());
      set_CrcOn(rhs.get_CrcOn());
      set_FreqHopOn(rhs.get_FreqHopOn());
      set_HopPeriod(rhs.get_HopPeriod());
      set_IqInverted(rhs.get_IqInverted());
      set_Timeout(rhs.get_Timeout());
      return *this;
    }

    inline void clear_Modem() { Modem_ = static_cast<RadioModems>(0); }
    inline void set_Modem(const RadioModems& value) { Modem_ = value; }
    inline void set_Modem(const RadioModems&& value) { Modem_ = value; }
    inline const RadioModems& get_Modem() const { return Modem_; }
    inline RadioModems Modem() const { return Modem_; }

    inline void clear_Power() { Power_.clear(); }
    inline void set_Power(const EmbeddedProto::uint32& value) { Power_ = value; }
    inline void set_Power(const EmbeddedProto::uint32&& value) { Power_ = value; }
    inline EmbeddedProto::uint32& mutable_Power() { return Power_; }
    inline const EmbeddedProto::uint32& get_Power() const { return Power_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Power() const { return Power_.get(); }

    inline void clear_Fdev() { Fdev_.clear(); }
    inline void set_Fdev(const EmbeddedProto::uint32& value) { Fdev_ = value; }
    inline void set_Fdev(const EmbeddedProto::uint32&& value) { Fdev_ = value; }
    inline EmbeddedProto::uint32& mutable_Fdev() { return Fdev_; }
    inline const EmbeddedProto::uint32& get_Fdev() const { return Fdev_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Fdev() const { return Fdev_.get(); }

    inline void clear_Bandwidth() { Bandwidth_.clear(); }
    inline void set_Bandwidth(const EmbeddedProto::uint32& value) { Bandwidth_ = value; }
    inline void set_Bandwidth(const EmbeddedProto::uint32&& value) { Bandwidth_ = value; }
    inline EmbeddedProto::uint32& mutable_Bandwidth() { return Bandwidth_; }
    inline const EmbeddedProto::uint32& get_Bandwidth() const { return Bandwidth_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Bandwidth() const { return Bandwidth_.get(); }

    inline void clear_DataRate() { DataRate_.clear(); }
    inline void set_DataRate(const EmbeddedProto::uint32& value) { DataRate_ = value; }
    inline void set_DataRate(const EmbeddedProto::uint32&& value) { DataRate_ = value; }
    inline EmbeddedProto::uint32& mutable_DataRate() { return DataRate_; }
    inline const EmbeddedProto::uint32& get_DataRate() const { return DataRate_; }
    inline EmbeddedProto::uint32::FIELD_TYPE DataRate() const { return DataRate_.get(); }

    inline void clear_CodeRate() { CodeRate_.clear(); }
    inline void set_CodeRate(const EmbeddedProto::uint32& value) { CodeRate_ = value; }
    inline void set_CodeRate(const EmbeddedProto::uint32&& value) { CodeRate_ = value; }
    inline EmbeddedProto::uint32& mutable_CodeRate() { return CodeRate_; }
    inline const EmbeddedProto::uint32& get_CodeRate() const { return CodeRate_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CodeRate() const { return CodeRate_.get(); }

    inline void clear_PreambleLen() { PreambleLen_.clear(); }
    inline void set_PreambleLen(const EmbeddedProto::uint32& value) { PreambleLen_ = value; }
    inline void set_PreambleLen(const EmbeddedProto::uint32&& value) { PreambleLen_ = value; }
    inline EmbeddedProto::uint32& mutable_PreambleLen() { return PreambleLen_; }
    inline const EmbeddedProto::uint32& get_PreambleLen() const { return PreambleLen_; }
    inline EmbeddedProto::uint32::FIELD_TYPE PreambleLen() const { return PreambleLen_.get(); }

    inline void clear_FixLen() { FixLen_.clear(); }
    inline void set_FixLen(const EmbeddedProto::boolean& value) { FixLen_ = value; }
    inline void set_FixLen(const EmbeddedProto::boolean&& value) { FixLen_ = value; }
    inline EmbeddedProto::boolean& mutable_FixLen() { return FixLen_; }
    inline const EmbeddedProto::boolean& get_FixLen() const { return FixLen_; }
    inline EmbeddedProto::boolean::FIELD_TYPE FixLen() const { return FixLen_.get(); }

    inline void clear_CrcOn() { CrcOn_.clear(); }
    inline void set_CrcOn(const EmbeddedProto::boolean& value) { CrcOn_ = value; }
    inline void set_CrcOn(const EmbeddedProto::boolean&& value) { CrcOn_ = value; }
    inline EmbeddedProto::boolean& mutable_CrcOn() { return CrcOn_; }
    inline const EmbeddedProto::boolean& get_CrcOn() const { return CrcOn_; }
    inline EmbeddedProto::boolean::FIELD_TYPE CrcOn() const { return CrcOn_.get(); }

    inline void clear_FreqHopOn() { FreqHopOn_.clear(); }
    inline void set_FreqHopOn(const EmbeddedProto::boolean& value) { FreqHopOn_ = value; }
    inline void set_FreqHopOn(const EmbeddedProto::boolean&& value) { FreqHopOn_ = value; }
    inline EmbeddedProto::boolean& mutable_FreqHopOn() { return FreqHopOn_; }
    inline const EmbeddedProto::boolean& get_FreqHopOn() const { return FreqHopOn_; }
    inline EmbeddedProto::boolean::FIELD_TYPE FreqHopOn() const { return FreqHopOn_.get(); }

    inline void clear_HopPeriod() { HopPeriod_.clear(); }
    inline void set_HopPeriod(const EmbeddedProto::uint32& value) { HopPeriod_ = value; }
    inline void set_HopPeriod(const EmbeddedProto::uint32&& value) { HopPeriod_ = value; }
    inline EmbeddedProto::uint32& mutable_HopPeriod() { return HopPeriod_; }
    inline const EmbeddedProto::uint32& get_HopPeriod() const { return HopPeriod_; }
    inline EmbeddedProto::uint32::FIELD_TYPE HopPeriod() const { return HopPeriod_.get(); }

    inline void clear_IqInverted() { IqInverted_.clear(); }
    inline void set_IqInverted(const EmbeddedProto::boolean& value) { IqInverted_ = value; }
    inline void set_IqInverted(const EmbeddedProto::boolean&& value) { IqInverted_ = value; }
    inline EmbeddedProto::boolean& mutable_IqInverted() { return IqInverted_; }
    inline const EmbeddedProto::boolean& get_IqInverted() const { return IqInverted_; }
    inline EmbeddedProto::boolean::FIELD_TYPE IqInverted() const { return IqInverted_.get(); }

    inline void clear_Timeout() { Timeout_.clear(); }
    inline void set_Timeout(const EmbeddedProto::uint32& value) { Timeout_ = value; }
    inline void set_Timeout(const EmbeddedProto::uint32&& value) { Timeout_ = value; }
    inline EmbeddedProto::uint32& mutable_Timeout() { return Timeout_; }
    inline const EmbeddedProto::uint32& get_Timeout() const { return Timeout_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Timeout() const { return Timeout_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<RadioModems>(0) != Modem_) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(Modem_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::MODEM), buffer, false);
      }

      if((0U != Power_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Power_.serialize_with_id(static_cast<uint32_t>(id::POWER), buffer, false);
      }

      if((0U != Fdev_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Fdev_.serialize_with_id(static_cast<uint32_t>(id::FDEV), buffer, false);
      }

      if((0U != Bandwidth_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Bandwidth_.serialize_with_id(static_cast<uint32_t>(id::BANDWIDTH), buffer, false);
      }

      if((0U != DataRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DataRate_.serialize_with_id(static_cast<uint32_t>(id::DATARATE), buffer, false);
      }

      if((0U != CodeRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CodeRate_.serialize_with_id(static_cast<uint32_t>(id::CODERATE), buffer, false);
      }

      if((0U != PreambleLen_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = PreambleLen_.serialize_with_id(static_cast<uint32_t>(id::PREAMBLELEN), buffer, false);
      }

      if((false != FixLen_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FixLen_.serialize_with_id(static_cast<uint32_t>(id::FIXLEN), buffer, false);
      }

      if((false != CrcOn_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CrcOn_.serialize_with_id(static_cast<uint32_t>(id::CRCON), buffer, false);
      }

      if((false != FreqHopOn_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FreqHopOn_.serialize_with_id(static_cast<uint32_t>(id::FREQHOPON), buffer, false);
      }

      if((0U != HopPeriod_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = HopPeriod_.serialize_with_id(static_cast<uint32_t>(id::HOPPERIOD), buffer, false);
      }

      if((false != IqInverted_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = IqInverted_.serialize_with_id(static_cast<uint32_t>(id::IQINVERTED), buffer, false);
      }

      if((0U != Timeout_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Timeout_.serialize_with_id(static_cast<uint32_t>(id::TIMEOUT), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::MODEM:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_Modem(static_cast<RadioModems>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
            break;

          case id::POWER:
            return_value = Power_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FDEV:
            return_value = Fdev_.deserialize_check_type(buffer, wire_type);
            break;

          case id::BANDWIDTH:
            return_value = Bandwidth_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DATARATE:
            return_value = DataRate_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CODERATE:
            return_value = CodeRate_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PREAMBLELEN:
            return_value = PreambleLen_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FIXLEN:
            return_value = FixLen_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CRCON:
            return_value = CrcOn_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FREQHOPON:
            return_value = FreqHopOn_.deserialize_check_type(buffer, wire_type);
            break;

          case id::HOPPERIOD:
            return_value = HopPeriod_.deserialize_check_type(buffer, wire_type);
            break;

          case id::IQINVERTED:
            return_value = IqInverted_.deserialize_check_type(buffer, wire_type);
            break;

          case id::TIMEOUT:
            return_value = Timeout_.deserialize_check_type(buffer, wire_type);
            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_Modem();
      clear_Power();
      clear_Fdev();
      clear_Bandwidth();
      clear_DataRate();
      clear_CodeRate();
      clear_PreambleLen();
      clear_FixLen();
      clear_CrcOn();
      clear_FreqHopOn();
      clear_HopPeriod();
      clear_IqInverted();
      clear_Timeout();

    }

    private:


      RadioModems Modem_ = static_cast<RadioModems>(0);
      EmbeddedProto::uint32 Power_ = 0U;
      EmbeddedProto::uint32 Fdev_ = 0U;
      EmbeddedProto::uint32 Bandwidth_ = 0U;
      EmbeddedProto::uint32 DataRate_ = 0U;
      EmbeddedProto::uint32 CodeRate_ = 0U;
      EmbeddedProto::uint32 PreambleLen_ = 0U;
      EmbeddedProto::boolean FixLen_ = false;
      EmbeddedProto::boolean CrcOn_ = false;
      EmbeddedProto::boolean FreqHopOn_ = false;
      EmbeddedProto::uint32 HopPeriod_ = 0U;
      EmbeddedProto::boolean IqInverted_ = false;
      EmbeddedProto::uint32 Timeout_ = 0U;

};

template<uint32_t Payload_LENGTH>
class TransmitCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    TransmitCommand() = default;
    TransmitCommand(const TransmitCommand& rhs )
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_Period(rhs.get_Period());
      set_MaxPacketCount(rhs.get_MaxPacketCount());
      set_Payload(rhs.get_Payload());
    }

    TransmitCommand(const TransmitCommand&& rhs ) noexcept
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_Period(rhs.get_Period());
      set_MaxPacketCount(rhs.get_MaxPacketCount());
      set_Payload(rhs.get_Payload());
    }

    ~TransmitCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ISMULTICAST = 1,
      DEVICEID = 2,
      PERIOD = 3,
      MAXPACKETCOUNT = 4,
      PAYLOAD = 5
    };

    TransmitCommand& operator=(const TransmitCommand& rhs)
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_Period(rhs.get_Period());
      set_MaxPacketCount(rhs.get_MaxPacketCount());
      set_Payload(rhs.get_Payload());
      return *this;
    }

    TransmitCommand& operator=(const TransmitCommand&& rhs) noexcept
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_Period(rhs.get_Period());
      set_MaxPacketCount(rhs.get_MaxPacketCount());
      set_Payload(rhs.get_Payload());
      return *this;
    }

    inline void clear_IsMulticast() { IsMulticast_.clear(); }
    inline void set_IsMulticast(const EmbeddedProto::boolean& value) { IsMulticast_ = value; }
    inline void set_IsMulticast(const EmbeddedProto::boolean&& value) { IsMulticast_ = value; }
    inline EmbeddedProto::boolean& mutable_IsMulticast() { return IsMulticast_; }
    inline const EmbeddedProto::boolean& get_IsMulticast() const { return IsMulticast_; }
    inline EmbeddedProto::boolean::FIELD_TYPE IsMulticast() const { return IsMulticast_.get(); }

    inline void clear_DeviceId() { DeviceId_.clear(); }
    inline void set_DeviceId(const EmbeddedProto::uint32& value) { DeviceId_ = value; }
    inline void set_DeviceId(const EmbeddedProto::uint32&& value) { DeviceId_ = value; }
    inline EmbeddedProto::uint32& mutable_DeviceId() { return DeviceId_; }
    inline const EmbeddedProto::uint32& get_DeviceId() const { return DeviceId_; }
    inline EmbeddedProto::uint32::FIELD_TYPE DeviceId() const { return DeviceId_.get(); }

    inline bool has_Period() const
    {
      return 0 != (presence::mask(presence::fields::PERIOD) & presence_[presence::index(presence::fields::PERIOD)]);
    }
    inline void clear_Period()
    {
      presence_[presence::index(presence::fields::PERIOD)] &= ~(presence::mask(presence::fields::PERIOD));
      Period_.clear();
    }
    inline void set_Period(const EmbeddedProto::uint32& value)
    {
      presence_[presence::index(presence::fields::PERIOD)] |= presence::mask(presence::fields::PERIOD);
      Period_ = value;
    }
    inline void set_Period(const EmbeddedProto::uint32&& value)
    {
      presence_[presence::index(presence::fields::PERIOD)] |= presence::mask(presence::fields::PERIOD);
      Period_ = value;
    }
    inline EmbeddedProto::uint32& mutable_Period()
    {
      presence_[presence::index(presence::fields::PERIOD)] |= presence::mask(presence::fields::PERIOD);
      return Period_;
    }
    inline const EmbeddedProto::uint32& get_Period() const { return Period_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Period() const { return Period_.get(); }

    inline bool has_MaxPacketCount() const
    {
      return 0 != (presence::mask(presence::fields::MAXPACKETCOUNT) & presence_[presence::index(presence::fields::MAXPACKETCOUNT)]);
    }
    inline void clear_MaxPacketCount()
    {
      presence_[presence::index(presence::fields::MAXPACKETCOUNT)] &= ~(presence::mask(presence::fields::MAXPACKETCOUNT));
      MaxPacketCount_.clear();
    }
    inline void set_MaxPacketCount(const EmbeddedProto::uint32& value)
    {
      presence_[presence::index(presence::fields::MAXPACKETCOUNT)] |= presence::mask(presence::fields::MAXPACKETCOUNT);
      MaxPacketCount_ = value;
    }
    inline void set_MaxPacketCount(const EmbeddedProto::uint32&& value)
    {
      presence_[presence::index(presence::fields::MAXPACKETCOUNT)] |= presence::mask(presence::fields::MAXPACKETCOUNT);
      MaxPacketCount_ = value;
    }
    inline EmbeddedProto::uint32& mutable_MaxPacketCount()
    {
      presence_[presence::index(presence::fields::MAXPACKETCOUNT)] |= presence::mask(presence::fields::MAXPACKETCOUNT);
      return MaxPacketCount_;
    }
    inline const EmbeddedProto::uint32& get_MaxPacketCount() const { return MaxPacketCount_; }
    inline EmbeddedProto::uint32::FIELD_TYPE MaxPacketCount() const { return MaxPacketCount_.get(); }

    inline void clear_Payload() { Payload_.clear(); }
    inline ::EmbeddedProto::FieldBytes<Payload_LENGTH>& mutable_Payload() { return Payload_; }
    inline void set_Payload(const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& rhs) { Payload_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& get_Payload() const { return Payload_; }
    inline const uint8_t* Payload() const { return Payload_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != IsMulticast_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = IsMulticast_.serialize_with_id(static_cast<uint32_t>(id::ISMULTICAST), buffer, false);
      }

      if((0U != DeviceId_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DeviceId_.serialize_with_id(static_cast<uint32_t>(id::DEVICEID), buffer, false);
      }

      if(has_Period() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Period_.serialize_with_id(static_cast<uint32_t>(id::PERIOD), buffer, true);
      }

      if(has_MaxPacketCount() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MaxPacketCount_.serialize_with_id(static_cast<uint32_t>(id::MAXPACKETCOUNT), buffer, true);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = Payload_.serialize_with_id(static_cast<uint32_t>(id::PAYLOAD), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::ISMULTICAST:
            return_value = IsMulticast_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DEVICEID:
            return_value = DeviceId_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PERIOD:
            presence_[presence::index(presence::fields::PERIOD)] |= presence::mask(presence::fields::PERIOD);
            return_value = Period_.deserialize_check_type(buffer, wire_type);
            break;

          case id::MAXPACKETCOUNT:
            presence_[presence::index(presence::fields::MAXPACKETCOUNT)] |= presence::mask(presence::fields::MAXPACKETCOUNT);
            return_value = MaxPacketCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PAYLOAD:
            return_value = Payload_.deserialize_check_type(buffer, wire_type);
            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_IsMulticast();
      clear_DeviceId();
      clear_Period();
      clear_MaxPacketCount();
      clear_Payload();

    }

    private:

      // Define constants for tracking the presence of fields.
      // Use a struct to scope the variables from user fields as namespaces are not allowed within classes.
      struct presence
      {
        // An enumeration with all the fields for which presence has to be tracked.
        enum class fields : uint32_t
        {
          PERIOD,
          MAXPACKETCOUNT
        };

        // The number of fields for which presence has to be tracked.
        static constexpr uint32_t N_FIELDS = 2;

        // Which type are we using to track presence.
        using TYPE = uint32_t;

        // How many bits are there in the presence type.
        static constexpr uint32_t N_BITS = std::numeric_limits<TYPE>::digits;

        // How many variables of TYPE do we need to bit mask all presence fields.
        static constexpr uint32_t SIZE = (N_FIELDS / N_BITS) + ((N_FIELDS % N_BITS) > 0 ? 1 : 0);

        // Obtain the index of a given field in the presence array.
        static constexpr uint32_t index(const fields& field) { return static_cast<uint32_t>(field) / N_BITS; }

        // Obtain the bit mask for the given field assuming we are at the correct index in the presence array.
        static constexpr TYPE mask(const fields& field)
        {
          return static_cast<uint32_t>(0x01) << (static_cast<uint32_t>(field) % N_BITS);
        }
      };

      // Create an array in which the presence flags are stored.
      typename presence::TYPE presence_[presence::SIZE] = {0};

      EmbeddedProto::boolean IsMulticast_ = false;
      EmbeddedProto::uint32 DeviceId_ = 0U;
      EmbeddedProto::uint32 Period_ = 0U;
      EmbeddedProto::uint32 MaxPacketCount_ = 0U;
      ::EmbeddedProto::FieldBytes<Payload_LENGTH> Payload_;

};

class RequestBootInfo final: public ::EmbeddedProto::MessageInterface
{
  public:
    RequestBootInfo() = default;
    RequestBootInfo(const RequestBootInfo& rhs )
    {
      set_Request(rhs.get_Request());
    }

    RequestBootInfo(const RequestBootInfo&& rhs ) noexcept
    {
      set_Request(rhs.get_Request());
    }

    ~RequestBootInfo() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      REQUEST = 1
    };

    RequestBootInfo& operator=(const RequestBootInfo& rhs)
    {
      set_Request(rhs.get_Request());
      return *this;
    }

    RequestBootInfo& operator=(const RequestBootInfo&& rhs) noexcept
    {
      set_Request(rhs.get_Request());
      return *this;
    }

    inline void clear_Request() { Request_.clear(); }
    inline void set_Request(const EmbeddedProto::boolean& value) { Request_ = value; }
    inline void set_Request(const EmbeddedProto::boolean&& value) { Request_ = value; }
    inline EmbeddedProto::boolean& mutable_Request() { return Request_; }
    inline const EmbeddedProto::boolean& get_Request() const { return Request_; }
    inline EmbeddedProto::boolean::FIELD_TYPE Request() const { return Request_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != Request_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Request_.serialize_with_id(static_cast<uint32_t>(id::REQUEST), buffer, false);
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::REQUEST:
            return_value = Request_.deserialize_check_type(buffer, wire_type);
            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_Request();

    }

    private:


      EmbeddedProto::boolean Request_ = false;

};

template<uint32_t transmitCommand_Payload_LENGTH>
class UartCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    UartCommand() = default;
    UartCommand(const UartCommand& rhs )
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::RXCONFIG:
          set_rxConfig(rhs.get_rxConfig());
          break;

        case id::TXCONFIG:
          set_txConfig(rhs.get_txConfig());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        default:
          break;
      }

    }

    UartCommand(const UartCommand&& rhs ) noexcept
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::RXCONFIG:
          set_rxConfig(rhs.get_rxConfig());
          break;

        case id::TXCONFIG:
          set_txConfig(rhs.get_txConfig());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        default:
          break;
      }

    }

    ~UartCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      RXCONFIG = 1,
      TXCONFIG = 2,
      TRANSMITCOMMAND = 3,
      REQUESTBOOTINFO = 4
    };

    UartCommand& operator=(const UartCommand& rhs)
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::RXCONFIG:
          set_rxConfig(rhs.get_rxConfig());
          break;

        case id::TXCONFIG:
          set_txConfig(rhs.get_txConfig());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        default:
          break;
      }

      return *this;
    }

    UartCommand& operator=(const UartCommand&& rhs) noexcept
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::RXCONFIG:
          set_rxConfig(rhs.get_rxConfig());
          break;

        case id::TXCONFIG:
          set_txConfig(rhs.get_txConfig());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        default:
          break;
      }

      return *this;
    }

    id get_which_Body() const { return which_Body_; }

    inline bool has_rxConfig() const
    {
      return id::RXCONFIG == which_Body_;
    }
    inline void clear_rxConfig()
    {
      if(id::RXCONFIG == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rxConfig_.~RadioRxConfig();
      }
    }
    inline void set_rxConfig(const RadioRxConfig& value)
    {
      if(id::RXCONFIG != which_Body_)
      {
        init_Body(id::RXCONFIG);
      }
      Body_.rxConfig_ = value;
    }
    inline void set_rxConfig(const RadioRxConfig&& value)
    {
      if(id::RXCONFIG != which_Body_)
      {
        init_Body(id::RXCONFIG);
      }
      Body_.rxConfig_ = value;
    }
    inline RadioRxConfig& mutable_rxConfig()
    {
      if(id::RXCONFIG != which_Body_)
      {
        init_Body(id::RXCONFIG);
      }
      return Body_.rxConfig_;
    }
    inline const RadioRxConfig& get_rxConfig() const { return Body_.rxConfig_; }
    inline const RadioRxConfig& rxConfig() const { return Body_.rxConfig_; }

    inline bool has_txConfig() const
    {
      return id::TXCONFIG == which_Body_;
    }
    inline void clear_txConfig()
    {
      if(id::TXCONFIG == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.txConfig_.~RadioTxConfig();
      }
    }
    inline void set_txConfig(const RadioTxConfig& value)
    {
      if(id::TXCONFIG != which_Body_)
      {
        init_Body(id::TXCONFIG);
      }
      Body_.txConfig_ = value;
    }
    inline void set_txConfig(const RadioTxConfig&& value)
    {
      if(id::TXCONFIG != which_Body_)
      {
        init_Body(id::TXCONFIG);
      }
      Body_.txConfig_ = value;
    }
    inline RadioTxConfig& mutable_txConfig()
    {
      if(id::TXCONFIG != which_Body_)
      {
        init_Body(id::TXCONFIG);
      }
      return Body_.txConfig_;
    }
    inline const RadioTxConfig& get_txConfig() const { return Body_.txConfig_; }
    inline const RadioTxConfig& txConfig() const { return Body_.txConfig_; }

    inline bool has_transmitCommand() const
    {
      return id::TRANSMITCOMMAND == which_Body_;
    }
    inline void clear_transmitCommand()
    {
      if(id::TRANSMITCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.transmitCommand_.~TransmitCommand<transmitCommand_Payload_LENGTH>();
      }
    }
    inline void set_transmitCommand(const TransmitCommand<transmitCommand_Payload_LENGTH>& value)
    {
      if(id::TRANSMITCOMMAND != which_Body_)
      {
        init_Body(id::TRANSMITCOMMAND);
      }
      Body_.transmitCommand_ = value;
    }
    inline void set_transmitCommand(const TransmitCommand<transmitCommand_Payload_LENGTH>&& value)
    {
      if(id::TRANSMITCOMMAND != which_Body_)
      {
        init_Body(id::TRANSMITCOMMAND);
      }
      Body_.transmitCommand_ = value;
    }
    inline TransmitCommand<transmitCommand_Payload_LENGTH>& mutable_transmitCommand()
    {
      if(id::TRANSMITCOMMAND != which_Body_)
      {
        init_Body(id::TRANSMITCOMMAND);
      }
      return Body_.transmitCommand_;
    }
    inline const TransmitCommand<transmitCommand_Payload_LENGTH>& get_transmitCommand() const { return Body_.transmitCommand_; }
    inline const TransmitCommand<transmitCommand_Payload_LENGTH>& transmitCommand() const { return Body_.transmitCommand_; }

    inline bool has_requestBootInfo() const
    {
      return id::REQUESTBOOTINFO == which_Body_;
    }
    inline void clear_requestBootInfo()
    {
      if(id::REQUESTBOOTINFO == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.requestBootInfo_.~RequestBootInfo();
      }
    }
    inline void set_requestBootInfo(const RequestBootInfo& value)
    {
      if(id::REQUESTBOOTINFO != which_Body_)
      {
        init_Body(id::REQUESTBOOTINFO);
      }
      Body_.requestBootInfo_ = value;
    }
    inline void set_requestBootInfo(const RequestBootInfo&& value)
    {
      if(id::REQUESTBOOTINFO != which_Body_)
      {
        init_Body(id::REQUESTBOOTINFO);
      }
      Body_.requestBootInfo_ = value;
    }
    inline RequestBootInfo& mutable_requestBootInfo()
    {
      if(id::REQUESTBOOTINFO != which_Body_)
      {
        init_Body(id::REQUESTBOOTINFO);
      }
      return Body_.requestBootInfo_;
    }
    inline const RequestBootInfo& get_requestBootInfo() const { return Body_.requestBootInfo_; }
    inline const RequestBootInfo& requestBootInfo() const { return Body_.requestBootInfo_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      switch(which_Body_)
      {
        case id::RXCONFIG:
          if(has_rxConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rxConfig_.serialize_with_id(static_cast<uint32_t>(id::RXCONFIG), buffer, true);
          }
          break;

        case id::TXCONFIG:
          if(has_txConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.txConfig_.serialize_with_id(static_cast<uint32_t>(id::TXCONFIG), buffer, true);
          }
          break;

        case id::TRANSMITCOMMAND:
          if(has_transmitCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.transmitCommand_.serialize_with_id(static_cast<uint32_t>(id::TRANSMITCOMMAND), buffer, true);
          }
          break;

        case id::REQUESTBOOTINFO:
          if(has_requestBootInfo() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.requestBootInfo_.serialize_with_id(static_cast<uint32_t>(id::REQUESTBOOTINFO), buffer, true);
          }
          break;

        default:
          break;
      }

      return return_value;
    };

    ::EmbeddedProto::Error deserialize(::EmbeddedProto::ReadBufferInterface& buffer) override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;
      ::EmbeddedProto::WireFormatter::WireType wire_type = ::EmbeddedProto::WireFormatter::WireType::VARINT;
      uint32_t id_number = 0;
      id id_tag = id::NOT_SET;

      ::EmbeddedProto::Error tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
      while((::EmbeddedProto::Error::NO_ERRORS == return_value) && (::EmbeddedProto::Error::NO_ERRORS == tag_value))
      {
        id_tag = static_cast<id>(id_number);
        switch(id_tag)
        {
          case id::RXCONFIG:
            return_value = deserialize_Body(id::RXCONFIG, Body_.rxConfig_, buffer, wire_type);

            break;

          case id::TXCONFIG:
            return_value = deserialize_Body(id::TXCONFIG, Body_.txConfig_, buffer, wire_type);

            break;

          case id::TRANSMITCOMMAND:
            return_value = deserialize_Body(id::TRANSMITCOMMAND, Body_.transmitCommand_, buffer, wire_type);

            break;

          case id::REQUESTBOOTINFO:
            return_value = deserialize_Body(id::REQUESTBOOTINFO, Body_.requestBootInfo_, buffer, wire_type);

            break;

          case id::NOT_SET:
            return_value = ::EmbeddedProto::Error::INVALID_FIELD_ID;
            break;

          default:
            return_value = skip_unknown_field(buffer, wire_type);
            break;
        }

        if(::EmbeddedProto::Error::NO_ERRORS == return_value)
        {
          // Read the next tag.
          tag_value = ::EmbeddedProto::WireFormatter::DeserializeTag(buffer, wire_type, id_number);
        }
      }

      // When an error was detect while reading the tag but no other errors where found, set it in the return value.
      if((::EmbeddedProto::Error::NO_ERRORS == return_value)
         && (::EmbeddedProto::Error::NO_ERRORS != tag_value)
         && (::EmbeddedProto::Error::END_OF_BUFFER != tag_value)) // The end of the buffer is not an array in this case.
      {
        return_value = tag_value;
      }

      return return_value;
    };

    void clear() override
    {
      clear_Body();

    }

    private:



      id which_Body_ = id::NOT_SET;
      union Body
      {
        Body() {}
        ~Body() {}
        RadioRxConfig rxConfig_;
        RadioTxConfig txConfig_;
        TransmitCommand<transmitCommand_Payload_LENGTH> transmitCommand_;
        RequestBootInfo requestBootInfo_;
      };
      Body Body_;

      void init_Body(const id field_id)
      {
        if(id::NOT_SET != which_Body_)
        {
          // First delete the old object in the oneof.
          clear_Body();
        }

        // C++11 unions only support nontrivial members when you explicitly call the placement new statement.
        switch(field_id)
        {
          case id::RXCONFIG:
            new(&Body_.rxConfig_) RadioRxConfig;
            which_Body_ = id::RXCONFIG;
            break;

          case id::TXCONFIG:
            new(&Body_.txConfig_) RadioTxConfig;
            which_Body_ = id::TXCONFIG;
            break;

          case id::TRANSMITCOMMAND:
            new(&Body_.transmitCommand_) TransmitCommand<transmitCommand_Payload_LENGTH>;
            which_Body_ = id::TRANSMITCOMMAND;
            break;

          case id::REQUESTBOOTINFO:
            new(&Body_.requestBootInfo_) RequestBootInfo;
            which_Body_ = id::REQUESTBOOTINFO;
            break;

          default:
            break;
         }

         which_Body_ = field_id;
      }

      void clear_Body()
      {
        switch(which_Body_)
        {
          case id::RXCONFIG:
            Body_.rxConfig_.~RadioRxConfig(); // NOSONAR Unions require this.
            break;
          case id::TXCONFIG:
            Body_.txConfig_.~RadioTxConfig(); // NOSONAR Unions require this.
            break;
          case id::TRANSMITCOMMAND:
            Body_.transmitCommand_.~TransmitCommand<transmitCommand_Payload_LENGTH>(); // NOSONAR Unions require this.
            break;
          case id::REQUESTBOOTINFO:
            Body_.requestBootInfo_.~RequestBootInfo(); // NOSONAR Unions require this.
            break;
          default:
            break;
        }
        which_Body_ = id::NOT_SET;
      }

      ::EmbeddedProto::Error deserialize_Body(const id field_id, ::EmbeddedProto::Field& field,
                                    ::EmbeddedProto::ReadBufferInterface& buffer,
                                    const ::EmbeddedProto::WireFormatter::WireType wire_type)
      {
        if(field_id != which_Body_)
        {
          init_Body(field_id);
        }
        ::EmbeddedProto::Error return_value = field.deserialize_check_type(buffer, wire_type);
        if(::EmbeddedProto::Error::NO_ERRORS != return_value)
        {
          clear_Body();
        }
        return return_value;
      }

};

#endif // UART_MESSAGES_H