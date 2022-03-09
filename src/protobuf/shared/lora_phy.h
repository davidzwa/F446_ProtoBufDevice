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
#ifndef SHARED_LORA_PHY_H
#define SHARED_LORA_PHY_H

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
    inline void set_Power(const EmbeddedProto::int32& value) { Power_ = value; }
    inline void set_Power(const EmbeddedProto::int32&& value) { Power_ = value; }
    inline EmbeddedProto::int32& mutable_Power() { return Power_; }
    inline const EmbeddedProto::int32& get_Power() const { return Power_; }
    inline EmbeddedProto::int32::FIELD_TYPE Power() const { return Power_.get(); }

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

      if((0 != Power_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
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
      EmbeddedProto::int32 Power_ = 0;
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

#endif // SHARED_LORA_PHY_H