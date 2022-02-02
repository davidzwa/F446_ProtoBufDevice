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
#ifndef SHARED_EXPERIMENT_CONFIG_H
#define SHARED_EXPERIMENT_CONFIG_H

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


enum class CommandType : uint32_t
{
  Configuration = 0,
  MultiCast = 1,
  MultiCastAck = 2,
  UniCast = 3,
  UniCastAck = 4,
  MeasurementStreamRequest = 5,
  MeasurementStreamFragmentReply = 6,
  SequenceRequest = 7,
  SequenceResponse = 8
};

class SequenceRequestConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    SequenceRequestConfig() = default;
    SequenceRequestConfig(const SequenceRequestConfig& rhs )
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
    }

    SequenceRequestConfig(const SequenceRequestConfig&& rhs ) noexcept
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
    }

    ~SequenceRequestConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MESSAGECOUNT = 1,
      INTERVAL = 2,
      DEVICEID = 3
    };

    SequenceRequestConfig& operator=(const SequenceRequestConfig& rhs)
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
      return *this;
    }

    SequenceRequestConfig& operator=(const SequenceRequestConfig&& rhs) noexcept
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
      return *this;
    }

    inline void clear_MessageCount() { MessageCount_.clear(); }
    inline void set_MessageCount(const EmbeddedProto::uint32& value) { MessageCount_ = value; }
    inline void set_MessageCount(const EmbeddedProto::uint32&& value) { MessageCount_ = value; }
    inline EmbeddedProto::uint32& mutable_MessageCount() { return MessageCount_; }
    inline const EmbeddedProto::uint32& get_MessageCount() const { return MessageCount_; }
    inline EmbeddedProto::uint32::FIELD_TYPE MessageCount() const { return MessageCount_.get(); }

    inline void clear_Interval() { Interval_.clear(); }
    inline void set_Interval(const EmbeddedProto::uint32& value) { Interval_ = value; }
    inline void set_Interval(const EmbeddedProto::uint32&& value) { Interval_ = value; }
    inline EmbeddedProto::uint32& mutable_Interval() { return Interval_; }
    inline const EmbeddedProto::uint32& get_Interval() const { return Interval_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Interval() const { return Interval_.get(); }

    inline void clear_DeviceId() { DeviceId_.clear(); }
    inline void set_DeviceId(const EmbeddedProto::uint32& value) { DeviceId_ = value; }
    inline void set_DeviceId(const EmbeddedProto::uint32&& value) { DeviceId_ = value; }
    inline EmbeddedProto::uint32& mutable_DeviceId() { return DeviceId_; }
    inline const EmbeddedProto::uint32& get_DeviceId() const { return DeviceId_; }
    inline EmbeddedProto::uint32::FIELD_TYPE DeviceId() const { return DeviceId_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != MessageCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MessageCount_.serialize_with_id(static_cast<uint32_t>(id::MESSAGECOUNT), buffer, false);
      }

      if((0U != Interval_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Interval_.serialize_with_id(static_cast<uint32_t>(id::INTERVAL), buffer, false);
      }

      if((0U != DeviceId_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DeviceId_.serialize_with_id(static_cast<uint32_t>(id::DEVICEID), buffer, false);
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
          case id::MESSAGECOUNT:
            return_value = MessageCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::INTERVAL:
            return_value = Interval_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DEVICEID:
            return_value = DeviceId_.deserialize_check_type(buffer, wire_type);
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
      clear_MessageCount();
      clear_Interval();
      clear_DeviceId();

    }

    private:


      EmbeddedProto::uint32 MessageCount_ = 0U;
      EmbeddedProto::uint32 Interval_ = 0U;
      EmbeddedProto::uint32 DeviceId_ = 0U;

};

class SpreadingFactorConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    SpreadingFactorConfig() = default;
    SpreadingFactorConfig(const SpreadingFactorConfig& rhs )
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
    }

    SpreadingFactorConfig(const SpreadingFactorConfig&& rhs ) noexcept
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
    }

    ~SpreadingFactorConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SPREADINGFACTORRX = 1,
      SPREADINGFACTORTX = 2
    };

    SpreadingFactorConfig& operator=(const SpreadingFactorConfig& rhs)
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
      return *this;
    }

    SpreadingFactorConfig& operator=(const SpreadingFactorConfig&& rhs) noexcept
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
      return *this;
    }

    inline void clear_spreadingFactorRx() { spreadingFactorRx_.clear(); }
    inline void set_spreadingFactorRx(const EmbeddedProto::uint32& value) { spreadingFactorRx_ = value; }
    inline void set_spreadingFactorRx(const EmbeddedProto::uint32&& value) { spreadingFactorRx_ = value; }
    inline EmbeddedProto::uint32& mutable_spreadingFactorRx() { return spreadingFactorRx_; }
    inline const EmbeddedProto::uint32& get_spreadingFactorRx() const { return spreadingFactorRx_; }
    inline EmbeddedProto::uint32::FIELD_TYPE spreadingFactorRx() const { return spreadingFactorRx_.get(); }

    inline void clear_spreadingFactorTx() { spreadingFactorTx_.clear(); }
    inline void set_spreadingFactorTx(const EmbeddedProto::uint32& value) { spreadingFactorTx_ = value; }
    inline void set_spreadingFactorTx(const EmbeddedProto::uint32&& value) { spreadingFactorTx_ = value; }
    inline EmbeddedProto::uint32& mutable_spreadingFactorTx() { return spreadingFactorTx_; }
    inline const EmbeddedProto::uint32& get_spreadingFactorTx() const { return spreadingFactorTx_; }
    inline EmbeddedProto::uint32::FIELD_TYPE spreadingFactorTx() const { return spreadingFactorTx_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != spreadingFactorRx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = spreadingFactorRx_.serialize_with_id(static_cast<uint32_t>(id::SPREADINGFACTORRX), buffer, false);
      }

      if((0U != spreadingFactorTx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = spreadingFactorTx_.serialize_with_id(static_cast<uint32_t>(id::SPREADINGFACTORTX), buffer, false);
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
          case id::SPREADINGFACTORRX:
            return_value = spreadingFactorRx_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SPREADINGFACTORTX:
            return_value = spreadingFactorTx_.deserialize_check_type(buffer, wire_type);
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
      clear_spreadingFactorRx();
      clear_spreadingFactorTx();

    }

    private:


      EmbeddedProto::uint32 spreadingFactorRx_ = 0U;
      EmbeddedProto::uint32 spreadingFactorTx_ = 0U;

};

#endif // SHARED_EXPERIMENT_CONFIG_H