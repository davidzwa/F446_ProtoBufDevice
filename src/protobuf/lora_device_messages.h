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
#ifndef LORA_DEVICE_MESSAGES_H
#define LORA_DEVICE_MESSAGES_H

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
#include <shared/experiment_config.h>
#include <shared/firmware.h>


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

class DeviceConfiguration final: public ::EmbeddedProto::MessageInterface
{
  public:
    DeviceConfiguration() = default;
    DeviceConfiguration(const DeviceConfiguration& rhs )
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_transmitConfiguration(rhs.get_transmitConfiguration());
    }

    DeviceConfiguration(const DeviceConfiguration&& rhs ) noexcept
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_transmitConfiguration(rhs.get_transmitConfiguration());
    }

    ~DeviceConfiguration() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ENABLEALWAYSSEND = 1,
      ALWAYSSENDPERIOD = 2,
      LIMITEDSENDCOUNT = 3,
      TRANSMITCONFIGURATION = 4
    };

    DeviceConfiguration& operator=(const DeviceConfiguration& rhs)
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_transmitConfiguration(rhs.get_transmitConfiguration());
      return *this;
    }

    DeviceConfiguration& operator=(const DeviceConfiguration&& rhs) noexcept
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_transmitConfiguration(rhs.get_transmitConfiguration());
      return *this;
    }

    inline void clear_EnableAlwaysSend() { EnableAlwaysSend_.clear(); }
    inline void set_EnableAlwaysSend(const EmbeddedProto::boolean& value) { EnableAlwaysSend_ = value; }
    inline void set_EnableAlwaysSend(const EmbeddedProto::boolean&& value) { EnableAlwaysSend_ = value; }
    inline EmbeddedProto::boolean& mutable_EnableAlwaysSend() { return EnableAlwaysSend_; }
    inline const EmbeddedProto::boolean& get_EnableAlwaysSend() const { return EnableAlwaysSend_; }
    inline EmbeddedProto::boolean::FIELD_TYPE EnableAlwaysSend() const { return EnableAlwaysSend_.get(); }

    inline void clear_AlwaysSendPeriod() { AlwaysSendPeriod_.clear(); }
    inline void set_AlwaysSendPeriod(const EmbeddedProto::uint32& value) { AlwaysSendPeriod_ = value; }
    inline void set_AlwaysSendPeriod(const EmbeddedProto::uint32&& value) { AlwaysSendPeriod_ = value; }
    inline EmbeddedProto::uint32& mutable_AlwaysSendPeriod() { return AlwaysSendPeriod_; }
    inline const EmbeddedProto::uint32& get_AlwaysSendPeriod() const { return AlwaysSendPeriod_; }
    inline EmbeddedProto::uint32::FIELD_TYPE AlwaysSendPeriod() const { return AlwaysSendPeriod_.get(); }

    inline void clear_LimitedSendCount() { LimitedSendCount_.clear(); }
    inline void set_LimitedSendCount(const EmbeddedProto::uint32& value) { LimitedSendCount_ = value; }
    inline void set_LimitedSendCount(const EmbeddedProto::uint32&& value) { LimitedSendCount_ = value; }
    inline EmbeddedProto::uint32& mutable_LimitedSendCount() { return LimitedSendCount_; }
    inline const EmbeddedProto::uint32& get_LimitedSendCount() const { return LimitedSendCount_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LimitedSendCount() const { return LimitedSendCount_.get(); }

    inline void clear_transmitConfiguration() { transmitConfiguration_.clear(); }
    inline void set_transmitConfiguration(const TransmitConfiguration& value) { transmitConfiguration_ = value; }
    inline void set_transmitConfiguration(const TransmitConfiguration&& value) { transmitConfiguration_ = value; }
    inline TransmitConfiguration& mutable_transmitConfiguration() { return transmitConfiguration_; }
    inline const TransmitConfiguration& get_transmitConfiguration() const { return transmitConfiguration_; }
    inline const TransmitConfiguration& transmitConfiguration() const { return transmitConfiguration_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != EnableAlwaysSend_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = EnableAlwaysSend_.serialize_with_id(static_cast<uint32_t>(id::ENABLEALWAYSSEND), buffer, false);
      }

      if((0U != AlwaysSendPeriod_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = AlwaysSendPeriod_.serialize_with_id(static_cast<uint32_t>(id::ALWAYSSENDPERIOD), buffer, false);
      }

      if((0U != LimitedSendCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = LimitedSendCount_.serialize_with_id(static_cast<uint32_t>(id::LIMITEDSENDCOUNT), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = transmitConfiguration_.serialize_with_id(static_cast<uint32_t>(id::TRANSMITCONFIGURATION), buffer, false);
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
          case id::ENABLEALWAYSSEND:
            return_value = EnableAlwaysSend_.deserialize_check_type(buffer, wire_type);
            break;

          case id::ALWAYSSENDPERIOD:
            return_value = AlwaysSendPeriod_.deserialize_check_type(buffer, wire_type);
            break;

          case id::LIMITEDSENDCOUNT:
            return_value = LimitedSendCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::TRANSMITCONFIGURATION:
            return_value = transmitConfiguration_.deserialize_check_type(buffer, wire_type);
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
      clear_EnableAlwaysSend();
      clear_AlwaysSendPeriod();
      clear_LimitedSendCount();
      clear_transmitConfiguration();

    }

    private:


      EmbeddedProto::boolean EnableAlwaysSend_ = false;
      EmbeddedProto::uint32 AlwaysSendPeriod_ = 0U;
      EmbeddedProto::uint32 LimitedSendCount_ = 0U;
      TransmitConfiguration transmitConfiguration_;

};

class LoRaReset final: public ::EmbeddedProto::MessageInterface
{
  public:
    LoRaReset() = default;
    LoRaReset(const LoRaReset& rhs )
    {
    }

    LoRaReset(const LoRaReset&& rhs ) noexcept
    {
    }

    ~LoRaReset() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
    };

    LoRaReset& operator=(const LoRaReset& rhs)
    {
      return *this;
    }

    LoRaReset& operator=(const LoRaReset&& rhs) noexcept
    {
      return *this;
    }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

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

    }

    private:



};

class LoRaAck final: public ::EmbeddedProto::MessageInterface
{
  public:
    LoRaAck() = default;
    LoRaAck(const LoRaAck& rhs )
    {
      set_DeviceId(rhs.get_DeviceId());
    }

    LoRaAck(const LoRaAck&& rhs ) noexcept
    {
      set_DeviceId(rhs.get_DeviceId());
    }

    ~LoRaAck() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      DEVICEID = 1
    };

    LoRaAck& operator=(const LoRaAck& rhs)
    {
      set_DeviceId(rhs.get_DeviceId());
      return *this;
    }

    LoRaAck& operator=(const LoRaAck&& rhs) noexcept
    {
      set_DeviceId(rhs.get_DeviceId());
      return *this;
    }

    inline void clear_DeviceId() { DeviceId_.clear(); }
    inline void set_DeviceId(const EmbeddedProto::uint32& value) { DeviceId_ = value; }
    inline void set_DeviceId(const EmbeddedProto::uint32&& value) { DeviceId_ = value; }
    inline EmbeddedProto::uint32& mutable_DeviceId() { return DeviceId_; }
    inline const EmbeddedProto::uint32& get_DeviceId() const { return DeviceId_; }
    inline EmbeddedProto::uint32::FIELD_TYPE DeviceId() const { return DeviceId_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

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
      clear_DeviceId();

    }

    private:


      EmbeddedProto::uint32 DeviceId_ = 0U;

};

template<uint32_t Payload_LENGTH>
class LoRaMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    LoRaMessage() = default;
    LoRaMessage(const LoRaMessage& rhs )
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_CorrelationCode(rhs.get_CorrelationCode());
      set_Payload(rhs.get_Payload());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::EXPERIMENTRESPONSE:
          set_experimentResponse(rhs.get_experimentResponse());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
          break;

        case id::RLNCREMOTEFLASHSTARTCOMMAND:
          set_rlncRemoteFlashStartCommand(rhs.get_rlncRemoteFlashStartCommand());
          break;

        case id::RLNCREMOTEFLASHSTOPCOMMAND:
          set_rlncRemoteFlashStopCommand(rhs.get_rlncRemoteFlashStopCommand());
          break;

        case id::RLNCQUERYREMOTEFLASHCOMMAND:
          set_rlncQueryRemoteFlashCommand(rhs.get_rlncQueryRemoteFlashCommand());
          break;

        case id::RLNCREMOTEFLASHRESPONSE:
          set_rlncRemoteFlashResponse(rhs.get_rlncRemoteFlashResponse());
          break;

        case id::RLNCINITCONFIGCOMMAND:
          set_rlncInitConfigCommand(rhs.get_rlncInitConfigCommand());
          break;

        case id::RLNCENCODEDFRAGMENT:
          set_rlncEncodedFragment(rhs.get_rlncEncodedFragment());
          break;

        case id::RLNCSTATEUPDATE:
          set_rlncStateUpdate(rhs.get_rlncStateUpdate());
          break;

        case id::RLNCTERMINATIONCOMMAND:
          set_rlncTerminationCommand(rhs.get_rlncTerminationCommand());
          break;

        case id::DECODINGRESULT:
          set_decodingResult(rhs.get_decodingResult());
          break;

        case id::DECODINGUPDATE:
          set_decodingUpdate(rhs.get_decodingUpdate());
          break;

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::RESETRADIO:
          set_resetRadio(rhs.get_resetRadio());
          break;

        case id::ACK:
          set_ack(rhs.get_ack());
          break;

        default:
          break;
      }

    }

    LoRaMessage(const LoRaMessage&& rhs ) noexcept
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_CorrelationCode(rhs.get_CorrelationCode());
      set_Payload(rhs.get_Payload());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::EXPERIMENTRESPONSE:
          set_experimentResponse(rhs.get_experimentResponse());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
          break;

        case id::RLNCREMOTEFLASHSTARTCOMMAND:
          set_rlncRemoteFlashStartCommand(rhs.get_rlncRemoteFlashStartCommand());
          break;

        case id::RLNCREMOTEFLASHSTOPCOMMAND:
          set_rlncRemoteFlashStopCommand(rhs.get_rlncRemoteFlashStopCommand());
          break;

        case id::RLNCQUERYREMOTEFLASHCOMMAND:
          set_rlncQueryRemoteFlashCommand(rhs.get_rlncQueryRemoteFlashCommand());
          break;

        case id::RLNCREMOTEFLASHRESPONSE:
          set_rlncRemoteFlashResponse(rhs.get_rlncRemoteFlashResponse());
          break;

        case id::RLNCINITCONFIGCOMMAND:
          set_rlncInitConfigCommand(rhs.get_rlncInitConfigCommand());
          break;

        case id::RLNCENCODEDFRAGMENT:
          set_rlncEncodedFragment(rhs.get_rlncEncodedFragment());
          break;

        case id::RLNCSTATEUPDATE:
          set_rlncStateUpdate(rhs.get_rlncStateUpdate());
          break;

        case id::RLNCTERMINATIONCOMMAND:
          set_rlncTerminationCommand(rhs.get_rlncTerminationCommand());
          break;

        case id::DECODINGRESULT:
          set_decodingResult(rhs.get_decodingResult());
          break;

        case id::DECODINGUPDATE:
          set_decodingUpdate(rhs.get_decodingUpdate());
          break;

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::RESETRADIO:
          set_resetRadio(rhs.get_resetRadio());
          break;

        case id::ACK:
          set_ack(rhs.get_ack());
          break;

        default:
          break;
      }

    }

    ~LoRaMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ISMULTICAST = 1,
      DEVICEID = 2,
      CORRELATIONCODE = 3,
      PAYLOAD = 4,
      FORWARDEXPERIMENTCOMMAND = 5,
      EXPERIMENTRESPONSE = 6,
      MEASUREMENTSTREAMREQUEST = 7,
      MEASUREMENTSTREAMFRAGMENT = 8,
      RLNCREMOTEFLASHSTARTCOMMAND = 9,
      RLNCREMOTEFLASHSTOPCOMMAND = 10,
      RLNCQUERYREMOTEFLASHCOMMAND = 11,
      RLNCREMOTEFLASHRESPONSE = 12,
      RLNCINITCONFIGCOMMAND = 13,
      RLNCENCODEDFRAGMENT = 14,
      RLNCSTATEUPDATE = 15,
      RLNCTERMINATIONCOMMAND = 16,
      DECODINGRESULT = 17,
      DECODINGUPDATE = 18,
      DEVICECONFIGURATION = 19,
      REQUESTBOOTINFO = 20,
      BOOTMESSAGE = 21,
      RESETRADIO = 22,
      ACK = 23
    };

    LoRaMessage& operator=(const LoRaMessage& rhs)
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_CorrelationCode(rhs.get_CorrelationCode());
      set_Payload(rhs.get_Payload());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::EXPERIMENTRESPONSE:
          set_experimentResponse(rhs.get_experimentResponse());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
          break;

        case id::RLNCREMOTEFLASHSTARTCOMMAND:
          set_rlncRemoteFlashStartCommand(rhs.get_rlncRemoteFlashStartCommand());
          break;

        case id::RLNCREMOTEFLASHSTOPCOMMAND:
          set_rlncRemoteFlashStopCommand(rhs.get_rlncRemoteFlashStopCommand());
          break;

        case id::RLNCQUERYREMOTEFLASHCOMMAND:
          set_rlncQueryRemoteFlashCommand(rhs.get_rlncQueryRemoteFlashCommand());
          break;

        case id::RLNCREMOTEFLASHRESPONSE:
          set_rlncRemoteFlashResponse(rhs.get_rlncRemoteFlashResponse());
          break;

        case id::RLNCINITCONFIGCOMMAND:
          set_rlncInitConfigCommand(rhs.get_rlncInitConfigCommand());
          break;

        case id::RLNCENCODEDFRAGMENT:
          set_rlncEncodedFragment(rhs.get_rlncEncodedFragment());
          break;

        case id::RLNCSTATEUPDATE:
          set_rlncStateUpdate(rhs.get_rlncStateUpdate());
          break;

        case id::RLNCTERMINATIONCOMMAND:
          set_rlncTerminationCommand(rhs.get_rlncTerminationCommand());
          break;

        case id::DECODINGRESULT:
          set_decodingResult(rhs.get_decodingResult());
          break;

        case id::DECODINGUPDATE:
          set_decodingUpdate(rhs.get_decodingUpdate());
          break;

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::RESETRADIO:
          set_resetRadio(rhs.get_resetRadio());
          break;

        case id::ACK:
          set_ack(rhs.get_ack());
          break;

        default:
          break;
      }

      return *this;
    }

    LoRaMessage& operator=(const LoRaMessage&& rhs) noexcept
    {
      set_IsMulticast(rhs.get_IsMulticast());
      set_DeviceId(rhs.get_DeviceId());
      set_CorrelationCode(rhs.get_CorrelationCode());
      set_Payload(rhs.get_Payload());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::EXPERIMENTRESPONSE:
          set_experimentResponse(rhs.get_experimentResponse());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
          break;

        case id::RLNCREMOTEFLASHSTARTCOMMAND:
          set_rlncRemoteFlashStartCommand(rhs.get_rlncRemoteFlashStartCommand());
          break;

        case id::RLNCREMOTEFLASHSTOPCOMMAND:
          set_rlncRemoteFlashStopCommand(rhs.get_rlncRemoteFlashStopCommand());
          break;

        case id::RLNCQUERYREMOTEFLASHCOMMAND:
          set_rlncQueryRemoteFlashCommand(rhs.get_rlncQueryRemoteFlashCommand());
          break;

        case id::RLNCREMOTEFLASHRESPONSE:
          set_rlncRemoteFlashResponse(rhs.get_rlncRemoteFlashResponse());
          break;

        case id::RLNCINITCONFIGCOMMAND:
          set_rlncInitConfigCommand(rhs.get_rlncInitConfigCommand());
          break;

        case id::RLNCENCODEDFRAGMENT:
          set_rlncEncodedFragment(rhs.get_rlncEncodedFragment());
          break;

        case id::RLNCSTATEUPDATE:
          set_rlncStateUpdate(rhs.get_rlncStateUpdate());
          break;

        case id::RLNCTERMINATIONCOMMAND:
          set_rlncTerminationCommand(rhs.get_rlncTerminationCommand());
          break;

        case id::DECODINGRESULT:
          set_decodingResult(rhs.get_decodingResult());
          break;

        case id::DECODINGUPDATE:
          set_decodingUpdate(rhs.get_decodingUpdate());
          break;

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::RESETRADIO:
          set_resetRadio(rhs.get_resetRadio());
          break;

        case id::ACK:
          set_ack(rhs.get_ack());
          break;

        default:
          break;
      }

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

    inline void clear_CorrelationCode() { CorrelationCode_.clear(); }
    inline void set_CorrelationCode(const EmbeddedProto::uint32& value) { CorrelationCode_ = value; }
    inline void set_CorrelationCode(const EmbeddedProto::uint32&& value) { CorrelationCode_ = value; }
    inline EmbeddedProto::uint32& mutable_CorrelationCode() { return CorrelationCode_; }
    inline const EmbeddedProto::uint32& get_CorrelationCode() const { return CorrelationCode_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CorrelationCode() const { return CorrelationCode_.get(); }

    inline void clear_Payload() { Payload_.clear(); }
    inline ::EmbeddedProto::FieldBytes<Payload_LENGTH>& mutable_Payload() { return Payload_; }
    inline void set_Payload(const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& rhs) { Payload_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& get_Payload() const { return Payload_; }
    inline const uint8_t* Payload() const { return Payload_.get_const(); }

    id get_which_Body() const { return which_Body_; }

    inline bool has_forwardExperimentCommand() const
    {
      return id::FORWARDEXPERIMENTCOMMAND == which_Body_;
    }
    inline void clear_forwardExperimentCommand()
    {
      if(id::FORWARDEXPERIMENTCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.forwardExperimentCommand_.~ForwardExperimentCommand();
      }
    }
    inline void set_forwardExperimentCommand(const ForwardExperimentCommand& value)
    {
      if(id::FORWARDEXPERIMENTCOMMAND != which_Body_)
      {
        init_Body(id::FORWARDEXPERIMENTCOMMAND);
      }
      Body_.forwardExperimentCommand_ = value;
    }
    inline void set_forwardExperimentCommand(const ForwardExperimentCommand&& value)
    {
      if(id::FORWARDEXPERIMENTCOMMAND != which_Body_)
      {
        init_Body(id::FORWARDEXPERIMENTCOMMAND);
      }
      Body_.forwardExperimentCommand_ = value;
    }
    inline ForwardExperimentCommand& mutable_forwardExperimentCommand()
    {
      if(id::FORWARDEXPERIMENTCOMMAND != which_Body_)
      {
        init_Body(id::FORWARDEXPERIMENTCOMMAND);
      }
      return Body_.forwardExperimentCommand_;
    }
    inline const ForwardExperimentCommand& get_forwardExperimentCommand() const { return Body_.forwardExperimentCommand_; }
    inline const ForwardExperimentCommand& forwardExperimentCommand() const { return Body_.forwardExperimentCommand_; }

    inline bool has_experimentResponse() const
    {
      return id::EXPERIMENTRESPONSE == which_Body_;
    }
    inline void clear_experimentResponse()
    {
      if(id::EXPERIMENTRESPONSE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.experimentResponse_.~ExperimentResponse();
      }
    }
    inline void set_experimentResponse(const ExperimentResponse& value)
    {
      if(id::EXPERIMENTRESPONSE != which_Body_)
      {
        init_Body(id::EXPERIMENTRESPONSE);
      }
      Body_.experimentResponse_ = value;
    }
    inline void set_experimentResponse(const ExperimentResponse&& value)
    {
      if(id::EXPERIMENTRESPONSE != which_Body_)
      {
        init_Body(id::EXPERIMENTRESPONSE);
      }
      Body_.experimentResponse_ = value;
    }
    inline ExperimentResponse& mutable_experimentResponse()
    {
      if(id::EXPERIMENTRESPONSE != which_Body_)
      {
        init_Body(id::EXPERIMENTRESPONSE);
      }
      return Body_.experimentResponse_;
    }
    inline const ExperimentResponse& get_experimentResponse() const { return Body_.experimentResponse_; }
    inline const ExperimentResponse& experimentResponse() const { return Body_.experimentResponse_; }

    inline bool has_measurementStreamRequest() const
    {
      return id::MEASUREMENTSTREAMREQUEST == which_Body_;
    }
    inline void clear_measurementStreamRequest()
    {
      if(id::MEASUREMENTSTREAMREQUEST == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.measurementStreamRequest_.~MeasurementStreamRequest();
      }
    }
    inline void set_measurementStreamRequest(const MeasurementStreamRequest& value)
    {
      if(id::MEASUREMENTSTREAMREQUEST != which_Body_)
      {
        init_Body(id::MEASUREMENTSTREAMREQUEST);
      }
      Body_.measurementStreamRequest_ = value;
    }
    inline void set_measurementStreamRequest(const MeasurementStreamRequest&& value)
    {
      if(id::MEASUREMENTSTREAMREQUEST != which_Body_)
      {
        init_Body(id::MEASUREMENTSTREAMREQUEST);
      }
      Body_.measurementStreamRequest_ = value;
    }
    inline MeasurementStreamRequest& mutable_measurementStreamRequest()
    {
      if(id::MEASUREMENTSTREAMREQUEST != which_Body_)
      {
        init_Body(id::MEASUREMENTSTREAMREQUEST);
      }
      return Body_.measurementStreamRequest_;
    }
    inline const MeasurementStreamRequest& get_measurementStreamRequest() const { return Body_.measurementStreamRequest_; }
    inline const MeasurementStreamRequest& measurementStreamRequest() const { return Body_.measurementStreamRequest_; }

    inline bool has_measurementStreamFragment() const
    {
      return id::MEASUREMENTSTREAMFRAGMENT == which_Body_;
    }
    inline void clear_measurementStreamFragment()
    {
      if(id::MEASUREMENTSTREAMFRAGMENT == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.measurementStreamFragment_.~MeasurementStreamFragment();
      }
    }
    inline void set_measurementStreamFragment(const MeasurementStreamFragment& value)
    {
      if(id::MEASUREMENTSTREAMFRAGMENT != which_Body_)
      {
        init_Body(id::MEASUREMENTSTREAMFRAGMENT);
      }
      Body_.measurementStreamFragment_ = value;
    }
    inline void set_measurementStreamFragment(const MeasurementStreamFragment&& value)
    {
      if(id::MEASUREMENTSTREAMFRAGMENT != which_Body_)
      {
        init_Body(id::MEASUREMENTSTREAMFRAGMENT);
      }
      Body_.measurementStreamFragment_ = value;
    }
    inline MeasurementStreamFragment& mutable_measurementStreamFragment()
    {
      if(id::MEASUREMENTSTREAMFRAGMENT != which_Body_)
      {
        init_Body(id::MEASUREMENTSTREAMFRAGMENT);
      }
      return Body_.measurementStreamFragment_;
    }
    inline const MeasurementStreamFragment& get_measurementStreamFragment() const { return Body_.measurementStreamFragment_; }
    inline const MeasurementStreamFragment& measurementStreamFragment() const { return Body_.measurementStreamFragment_; }

    inline bool has_rlncRemoteFlashStartCommand() const
    {
      return id::RLNCREMOTEFLASHSTARTCOMMAND == which_Body_;
    }
    inline void clear_rlncRemoteFlashStartCommand()
    {
      if(id::RLNCREMOTEFLASHSTARTCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncRemoteFlashStartCommand_.~RlncRemoteFlashStartCommand();
      }
    }
    inline void set_rlncRemoteFlashStartCommand(const RlncRemoteFlashStartCommand& value)
    {
      if(id::RLNCREMOTEFLASHSTARTCOMMAND != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHSTARTCOMMAND);
      }
      Body_.rlncRemoteFlashStartCommand_ = value;
    }
    inline void set_rlncRemoteFlashStartCommand(const RlncRemoteFlashStartCommand&& value)
    {
      if(id::RLNCREMOTEFLASHSTARTCOMMAND != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHSTARTCOMMAND);
      }
      Body_.rlncRemoteFlashStartCommand_ = value;
    }
    inline RlncRemoteFlashStartCommand& mutable_rlncRemoteFlashStartCommand()
    {
      if(id::RLNCREMOTEFLASHSTARTCOMMAND != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHSTARTCOMMAND);
      }
      return Body_.rlncRemoteFlashStartCommand_;
    }
    inline const RlncRemoteFlashStartCommand& get_rlncRemoteFlashStartCommand() const { return Body_.rlncRemoteFlashStartCommand_; }
    inline const RlncRemoteFlashStartCommand& rlncRemoteFlashStartCommand() const { return Body_.rlncRemoteFlashStartCommand_; }

    inline bool has_rlncRemoteFlashStopCommand() const
    {
      return id::RLNCREMOTEFLASHSTOPCOMMAND == which_Body_;
    }
    inline void clear_rlncRemoteFlashStopCommand()
    {
      if(id::RLNCREMOTEFLASHSTOPCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncRemoteFlashStopCommand_.~RlncRemoteFlashStopCommand();
      }
    }
    inline void set_rlncRemoteFlashStopCommand(const RlncRemoteFlashStopCommand& value)
    {
      if(id::RLNCREMOTEFLASHSTOPCOMMAND != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHSTOPCOMMAND);
      }
      Body_.rlncRemoteFlashStopCommand_ = value;
    }
    inline void set_rlncRemoteFlashStopCommand(const RlncRemoteFlashStopCommand&& value)
    {
      if(id::RLNCREMOTEFLASHSTOPCOMMAND != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHSTOPCOMMAND);
      }
      Body_.rlncRemoteFlashStopCommand_ = value;
    }
    inline RlncRemoteFlashStopCommand& mutable_rlncRemoteFlashStopCommand()
    {
      if(id::RLNCREMOTEFLASHSTOPCOMMAND != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHSTOPCOMMAND);
      }
      return Body_.rlncRemoteFlashStopCommand_;
    }
    inline const RlncRemoteFlashStopCommand& get_rlncRemoteFlashStopCommand() const { return Body_.rlncRemoteFlashStopCommand_; }
    inline const RlncRemoteFlashStopCommand& rlncRemoteFlashStopCommand() const { return Body_.rlncRemoteFlashStopCommand_; }

    inline bool has_rlncQueryRemoteFlashCommand() const
    {
      return id::RLNCQUERYREMOTEFLASHCOMMAND == which_Body_;
    }
    inline void clear_rlncQueryRemoteFlashCommand()
    {
      if(id::RLNCQUERYREMOTEFLASHCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncQueryRemoteFlashCommand_.~RlncQueryRemoteFlashState();
      }
    }
    inline void set_rlncQueryRemoteFlashCommand(const RlncQueryRemoteFlashState& value)
    {
      if(id::RLNCQUERYREMOTEFLASHCOMMAND != which_Body_)
      {
        init_Body(id::RLNCQUERYREMOTEFLASHCOMMAND);
      }
      Body_.rlncQueryRemoteFlashCommand_ = value;
    }
    inline void set_rlncQueryRemoteFlashCommand(const RlncQueryRemoteFlashState&& value)
    {
      if(id::RLNCQUERYREMOTEFLASHCOMMAND != which_Body_)
      {
        init_Body(id::RLNCQUERYREMOTEFLASHCOMMAND);
      }
      Body_.rlncQueryRemoteFlashCommand_ = value;
    }
    inline RlncQueryRemoteFlashState& mutable_rlncQueryRemoteFlashCommand()
    {
      if(id::RLNCQUERYREMOTEFLASHCOMMAND != which_Body_)
      {
        init_Body(id::RLNCQUERYREMOTEFLASHCOMMAND);
      }
      return Body_.rlncQueryRemoteFlashCommand_;
    }
    inline const RlncQueryRemoteFlashState& get_rlncQueryRemoteFlashCommand() const { return Body_.rlncQueryRemoteFlashCommand_; }
    inline const RlncQueryRemoteFlashState& rlncQueryRemoteFlashCommand() const { return Body_.rlncQueryRemoteFlashCommand_; }

    inline bool has_rlncRemoteFlashResponse() const
    {
      return id::RLNCREMOTEFLASHRESPONSE == which_Body_;
    }
    inline void clear_rlncRemoteFlashResponse()
    {
      if(id::RLNCREMOTEFLASHRESPONSE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncRemoteFlashResponse_.~RlncRemoteFlashResponse();
      }
    }
    inline void set_rlncRemoteFlashResponse(const RlncRemoteFlashResponse& value)
    {
      if(id::RLNCREMOTEFLASHRESPONSE != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHRESPONSE);
      }
      Body_.rlncRemoteFlashResponse_ = value;
    }
    inline void set_rlncRemoteFlashResponse(const RlncRemoteFlashResponse&& value)
    {
      if(id::RLNCREMOTEFLASHRESPONSE != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHRESPONSE);
      }
      Body_.rlncRemoteFlashResponse_ = value;
    }
    inline RlncRemoteFlashResponse& mutable_rlncRemoteFlashResponse()
    {
      if(id::RLNCREMOTEFLASHRESPONSE != which_Body_)
      {
        init_Body(id::RLNCREMOTEFLASHRESPONSE);
      }
      return Body_.rlncRemoteFlashResponse_;
    }
    inline const RlncRemoteFlashResponse& get_rlncRemoteFlashResponse() const { return Body_.rlncRemoteFlashResponse_; }
    inline const RlncRemoteFlashResponse& rlncRemoteFlashResponse() const { return Body_.rlncRemoteFlashResponse_; }

    inline bool has_rlncInitConfigCommand() const
    {
      return id::RLNCINITCONFIGCOMMAND == which_Body_;
    }
    inline void clear_rlncInitConfigCommand()
    {
      if(id::RLNCINITCONFIGCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncInitConfigCommand_.~RlncInitConfigCommand();
      }
    }
    inline void set_rlncInitConfigCommand(const RlncInitConfigCommand& value)
    {
      if(id::RLNCINITCONFIGCOMMAND != which_Body_)
      {
        init_Body(id::RLNCINITCONFIGCOMMAND);
      }
      Body_.rlncInitConfigCommand_ = value;
    }
    inline void set_rlncInitConfigCommand(const RlncInitConfigCommand&& value)
    {
      if(id::RLNCINITCONFIGCOMMAND != which_Body_)
      {
        init_Body(id::RLNCINITCONFIGCOMMAND);
      }
      Body_.rlncInitConfigCommand_ = value;
    }
    inline RlncInitConfigCommand& mutable_rlncInitConfigCommand()
    {
      if(id::RLNCINITCONFIGCOMMAND != which_Body_)
      {
        init_Body(id::RLNCINITCONFIGCOMMAND);
      }
      return Body_.rlncInitConfigCommand_;
    }
    inline const RlncInitConfigCommand& get_rlncInitConfigCommand() const { return Body_.rlncInitConfigCommand_; }
    inline const RlncInitConfigCommand& rlncInitConfigCommand() const { return Body_.rlncInitConfigCommand_; }

    inline bool has_rlncEncodedFragment() const
    {
      return id::RLNCENCODEDFRAGMENT == which_Body_;
    }
    inline void clear_rlncEncodedFragment()
    {
      if(id::RLNCENCODEDFRAGMENT == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncEncodedFragment_.~RlncEncodedFragment();
      }
    }
    inline void set_rlncEncodedFragment(const RlncEncodedFragment& value)
    {
      if(id::RLNCENCODEDFRAGMENT != which_Body_)
      {
        init_Body(id::RLNCENCODEDFRAGMENT);
      }
      Body_.rlncEncodedFragment_ = value;
    }
    inline void set_rlncEncodedFragment(const RlncEncodedFragment&& value)
    {
      if(id::RLNCENCODEDFRAGMENT != which_Body_)
      {
        init_Body(id::RLNCENCODEDFRAGMENT);
      }
      Body_.rlncEncodedFragment_ = value;
    }
    inline RlncEncodedFragment& mutable_rlncEncodedFragment()
    {
      if(id::RLNCENCODEDFRAGMENT != which_Body_)
      {
        init_Body(id::RLNCENCODEDFRAGMENT);
      }
      return Body_.rlncEncodedFragment_;
    }
    inline const RlncEncodedFragment& get_rlncEncodedFragment() const { return Body_.rlncEncodedFragment_; }
    inline const RlncEncodedFragment& rlncEncodedFragment() const { return Body_.rlncEncodedFragment_; }

    inline bool has_rlncStateUpdate() const
    {
      return id::RLNCSTATEUPDATE == which_Body_;
    }
    inline void clear_rlncStateUpdate()
    {
      if(id::RLNCSTATEUPDATE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncStateUpdate_.~RlncStateUpdate();
      }
    }
    inline void set_rlncStateUpdate(const RlncStateUpdate& value)
    {
      if(id::RLNCSTATEUPDATE != which_Body_)
      {
        init_Body(id::RLNCSTATEUPDATE);
      }
      Body_.rlncStateUpdate_ = value;
    }
    inline void set_rlncStateUpdate(const RlncStateUpdate&& value)
    {
      if(id::RLNCSTATEUPDATE != which_Body_)
      {
        init_Body(id::RLNCSTATEUPDATE);
      }
      Body_.rlncStateUpdate_ = value;
    }
    inline RlncStateUpdate& mutable_rlncStateUpdate()
    {
      if(id::RLNCSTATEUPDATE != which_Body_)
      {
        init_Body(id::RLNCSTATEUPDATE);
      }
      return Body_.rlncStateUpdate_;
    }
    inline const RlncStateUpdate& get_rlncStateUpdate() const { return Body_.rlncStateUpdate_; }
    inline const RlncStateUpdate& rlncStateUpdate() const { return Body_.rlncStateUpdate_; }

    inline bool has_rlncTerminationCommand() const
    {
      return id::RLNCTERMINATIONCOMMAND == which_Body_;
    }
    inline void clear_rlncTerminationCommand()
    {
      if(id::RLNCTERMINATIONCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.rlncTerminationCommand_.~RlncTerminationCommand();
      }
    }
    inline void set_rlncTerminationCommand(const RlncTerminationCommand& value)
    {
      if(id::RLNCTERMINATIONCOMMAND != which_Body_)
      {
        init_Body(id::RLNCTERMINATIONCOMMAND);
      }
      Body_.rlncTerminationCommand_ = value;
    }
    inline void set_rlncTerminationCommand(const RlncTerminationCommand&& value)
    {
      if(id::RLNCTERMINATIONCOMMAND != which_Body_)
      {
        init_Body(id::RLNCTERMINATIONCOMMAND);
      }
      Body_.rlncTerminationCommand_ = value;
    }
    inline RlncTerminationCommand& mutable_rlncTerminationCommand()
    {
      if(id::RLNCTERMINATIONCOMMAND != which_Body_)
      {
        init_Body(id::RLNCTERMINATIONCOMMAND);
      }
      return Body_.rlncTerminationCommand_;
    }
    inline const RlncTerminationCommand& get_rlncTerminationCommand() const { return Body_.rlncTerminationCommand_; }
    inline const RlncTerminationCommand& rlncTerminationCommand() const { return Body_.rlncTerminationCommand_; }

    inline bool has_decodingResult() const
    {
      return id::DECODINGRESULT == which_Body_;
    }
    inline void clear_decodingResult()
    {
      if(id::DECODINGRESULT == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.decodingResult_.~DecodingResult();
      }
    }
    inline void set_decodingResult(const DecodingResult& value)
    {
      if(id::DECODINGRESULT != which_Body_)
      {
        init_Body(id::DECODINGRESULT);
      }
      Body_.decodingResult_ = value;
    }
    inline void set_decodingResult(const DecodingResult&& value)
    {
      if(id::DECODINGRESULT != which_Body_)
      {
        init_Body(id::DECODINGRESULT);
      }
      Body_.decodingResult_ = value;
    }
    inline DecodingResult& mutable_decodingResult()
    {
      if(id::DECODINGRESULT != which_Body_)
      {
        init_Body(id::DECODINGRESULT);
      }
      return Body_.decodingResult_;
    }
    inline const DecodingResult& get_decodingResult() const { return Body_.decodingResult_; }
    inline const DecodingResult& decodingResult() const { return Body_.decodingResult_; }

    inline bool has_decodingUpdate() const
    {
      return id::DECODINGUPDATE == which_Body_;
    }
    inline void clear_decodingUpdate()
    {
      if(id::DECODINGUPDATE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.decodingUpdate_.~DecodingUpdate();
      }
    }
    inline void set_decodingUpdate(const DecodingUpdate& value)
    {
      if(id::DECODINGUPDATE != which_Body_)
      {
        init_Body(id::DECODINGUPDATE);
      }
      Body_.decodingUpdate_ = value;
    }
    inline void set_decodingUpdate(const DecodingUpdate&& value)
    {
      if(id::DECODINGUPDATE != which_Body_)
      {
        init_Body(id::DECODINGUPDATE);
      }
      Body_.decodingUpdate_ = value;
    }
    inline DecodingUpdate& mutable_decodingUpdate()
    {
      if(id::DECODINGUPDATE != which_Body_)
      {
        init_Body(id::DECODINGUPDATE);
      }
      return Body_.decodingUpdate_;
    }
    inline const DecodingUpdate& get_decodingUpdate() const { return Body_.decodingUpdate_; }
    inline const DecodingUpdate& decodingUpdate() const { return Body_.decodingUpdate_; }

    inline bool has_deviceConfiguration() const
    {
      return id::DEVICECONFIGURATION == which_Body_;
    }
    inline void clear_deviceConfiguration()
    {
      if(id::DEVICECONFIGURATION == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.deviceConfiguration_.~DeviceConfiguration();
      }
    }
    inline void set_deviceConfiguration(const DeviceConfiguration& value)
    {
      if(id::DEVICECONFIGURATION != which_Body_)
      {
        init_Body(id::DEVICECONFIGURATION);
      }
      Body_.deviceConfiguration_ = value;
    }
    inline void set_deviceConfiguration(const DeviceConfiguration&& value)
    {
      if(id::DEVICECONFIGURATION != which_Body_)
      {
        init_Body(id::DEVICECONFIGURATION);
      }
      Body_.deviceConfiguration_ = value;
    }
    inline DeviceConfiguration& mutable_deviceConfiguration()
    {
      if(id::DEVICECONFIGURATION != which_Body_)
      {
        init_Body(id::DEVICECONFIGURATION);
      }
      return Body_.deviceConfiguration_;
    }
    inline const DeviceConfiguration& get_deviceConfiguration() const { return Body_.deviceConfiguration_; }
    inline const DeviceConfiguration& deviceConfiguration() const { return Body_.deviceConfiguration_; }

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

    inline bool has_bootMessage() const
    {
      return id::BOOTMESSAGE == which_Body_;
    }
    inline void clear_bootMessage()
    {
      if(id::BOOTMESSAGE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.bootMessage_.~BootMessage();
      }
    }
    inline void set_bootMessage(const BootMessage& value)
    {
      if(id::BOOTMESSAGE != which_Body_)
      {
        init_Body(id::BOOTMESSAGE);
      }
      Body_.bootMessage_ = value;
    }
    inline void set_bootMessage(const BootMessage&& value)
    {
      if(id::BOOTMESSAGE != which_Body_)
      {
        init_Body(id::BOOTMESSAGE);
      }
      Body_.bootMessage_ = value;
    }
    inline BootMessage& mutable_bootMessage()
    {
      if(id::BOOTMESSAGE != which_Body_)
      {
        init_Body(id::BOOTMESSAGE);
      }
      return Body_.bootMessage_;
    }
    inline const BootMessage& get_bootMessage() const { return Body_.bootMessage_; }
    inline const BootMessage& bootMessage() const { return Body_.bootMessage_; }

    inline bool has_resetRadio() const
    {
      return id::RESETRADIO == which_Body_;
    }
    inline void clear_resetRadio()
    {
      if(id::RESETRADIO == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.resetRadio_.~LoRaReset();
      }
    }
    inline void set_resetRadio(const LoRaReset& value)
    {
      if(id::RESETRADIO != which_Body_)
      {
        init_Body(id::RESETRADIO);
      }
      Body_.resetRadio_ = value;
    }
    inline void set_resetRadio(const LoRaReset&& value)
    {
      if(id::RESETRADIO != which_Body_)
      {
        init_Body(id::RESETRADIO);
      }
      Body_.resetRadio_ = value;
    }
    inline LoRaReset& mutable_resetRadio()
    {
      if(id::RESETRADIO != which_Body_)
      {
        init_Body(id::RESETRADIO);
      }
      return Body_.resetRadio_;
    }
    inline const LoRaReset& get_resetRadio() const { return Body_.resetRadio_; }
    inline const LoRaReset& resetRadio() const { return Body_.resetRadio_; }

    inline bool has_ack() const
    {
      return id::ACK == which_Body_;
    }
    inline void clear_ack()
    {
      if(id::ACK == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.ack_.~LoRaAck();
      }
    }
    inline void set_ack(const LoRaAck& value)
    {
      if(id::ACK != which_Body_)
      {
        init_Body(id::ACK);
      }
      Body_.ack_ = value;
    }
    inline void set_ack(const LoRaAck&& value)
    {
      if(id::ACK != which_Body_)
      {
        init_Body(id::ACK);
      }
      Body_.ack_ = value;
    }
    inline LoRaAck& mutable_ack()
    {
      if(id::ACK != which_Body_)
      {
        init_Body(id::ACK);
      }
      return Body_.ack_;
    }
    inline const LoRaAck& get_ack() const { return Body_.ack_; }
    inline const LoRaAck& ack() const { return Body_.ack_; }


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

      if((0U != CorrelationCode_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CorrelationCode_.serialize_with_id(static_cast<uint32_t>(id::CORRELATIONCODE), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = Payload_.serialize_with_id(static_cast<uint32_t>(id::PAYLOAD), buffer, false);
      }

      switch(which_Body_)
      {
        case id::FORWARDEXPERIMENTCOMMAND:
          if(has_forwardExperimentCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.forwardExperimentCommand_.serialize_with_id(static_cast<uint32_t>(id::FORWARDEXPERIMENTCOMMAND), buffer, true);
          }
          break;

        case id::EXPERIMENTRESPONSE:
          if(has_experimentResponse() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.experimentResponse_.serialize_with_id(static_cast<uint32_t>(id::EXPERIMENTRESPONSE), buffer, true);
          }
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          if(has_measurementStreamRequest() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.measurementStreamRequest_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTSTREAMREQUEST), buffer, true);
          }
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          if(has_measurementStreamFragment() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.measurementStreamFragment_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTSTREAMFRAGMENT), buffer, true);
          }
          break;

        case id::RLNCREMOTEFLASHSTARTCOMMAND:
          if(has_rlncRemoteFlashStartCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncRemoteFlashStartCommand_.serialize_with_id(static_cast<uint32_t>(id::RLNCREMOTEFLASHSTARTCOMMAND), buffer, true);
          }
          break;

        case id::RLNCREMOTEFLASHSTOPCOMMAND:
          if(has_rlncRemoteFlashStopCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncRemoteFlashStopCommand_.serialize_with_id(static_cast<uint32_t>(id::RLNCREMOTEFLASHSTOPCOMMAND), buffer, true);
          }
          break;

        case id::RLNCQUERYREMOTEFLASHCOMMAND:
          if(has_rlncQueryRemoteFlashCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncQueryRemoteFlashCommand_.serialize_with_id(static_cast<uint32_t>(id::RLNCQUERYREMOTEFLASHCOMMAND), buffer, true);
          }
          break;

        case id::RLNCREMOTEFLASHRESPONSE:
          if(has_rlncRemoteFlashResponse() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncRemoteFlashResponse_.serialize_with_id(static_cast<uint32_t>(id::RLNCREMOTEFLASHRESPONSE), buffer, true);
          }
          break;

        case id::RLNCINITCONFIGCOMMAND:
          if(has_rlncInitConfigCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncInitConfigCommand_.serialize_with_id(static_cast<uint32_t>(id::RLNCINITCONFIGCOMMAND), buffer, true);
          }
          break;

        case id::RLNCENCODEDFRAGMENT:
          if(has_rlncEncodedFragment() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncEncodedFragment_.serialize_with_id(static_cast<uint32_t>(id::RLNCENCODEDFRAGMENT), buffer, true);
          }
          break;

        case id::RLNCSTATEUPDATE:
          if(has_rlncStateUpdate() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncStateUpdate_.serialize_with_id(static_cast<uint32_t>(id::RLNCSTATEUPDATE), buffer, true);
          }
          break;

        case id::RLNCTERMINATIONCOMMAND:
          if(has_rlncTerminationCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.rlncTerminationCommand_.serialize_with_id(static_cast<uint32_t>(id::RLNCTERMINATIONCOMMAND), buffer, true);
          }
          break;

        case id::DECODINGRESULT:
          if(has_decodingResult() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.decodingResult_.serialize_with_id(static_cast<uint32_t>(id::DECODINGRESULT), buffer, true);
          }
          break;

        case id::DECODINGUPDATE:
          if(has_decodingUpdate() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.decodingUpdate_.serialize_with_id(static_cast<uint32_t>(id::DECODINGUPDATE), buffer, true);
          }
          break;

        case id::DEVICECONFIGURATION:
          if(has_deviceConfiguration() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.deviceConfiguration_.serialize_with_id(static_cast<uint32_t>(id::DEVICECONFIGURATION), buffer, true);
          }
          break;

        case id::REQUESTBOOTINFO:
          if(has_requestBootInfo() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.requestBootInfo_.serialize_with_id(static_cast<uint32_t>(id::REQUESTBOOTINFO), buffer, true);
          }
          break;

        case id::BOOTMESSAGE:
          if(has_bootMessage() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.bootMessage_.serialize_with_id(static_cast<uint32_t>(id::BOOTMESSAGE), buffer, true);
          }
          break;

        case id::RESETRADIO:
          if(has_resetRadio() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.resetRadio_.serialize_with_id(static_cast<uint32_t>(id::RESETRADIO), buffer, true);
          }
          break;

        case id::ACK:
          if(has_ack() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.ack_.serialize_with_id(static_cast<uint32_t>(id::ACK), buffer, true);
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
          case id::ISMULTICAST:
            return_value = IsMulticast_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DEVICEID:
            return_value = DeviceId_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CORRELATIONCODE:
            return_value = CorrelationCode_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PAYLOAD:
            return_value = Payload_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FORWARDEXPERIMENTCOMMAND:
            return_value = deserialize_Body(id::FORWARDEXPERIMENTCOMMAND, Body_.forwardExperimentCommand_, buffer, wire_type);

            break;

          case id::EXPERIMENTRESPONSE:
            return_value = deserialize_Body(id::EXPERIMENTRESPONSE, Body_.experimentResponse_, buffer, wire_type);

            break;

          case id::MEASUREMENTSTREAMREQUEST:
            return_value = deserialize_Body(id::MEASUREMENTSTREAMREQUEST, Body_.measurementStreamRequest_, buffer, wire_type);

            break;

          case id::MEASUREMENTSTREAMFRAGMENT:
            return_value = deserialize_Body(id::MEASUREMENTSTREAMFRAGMENT, Body_.measurementStreamFragment_, buffer, wire_type);

            break;

          case id::RLNCREMOTEFLASHSTARTCOMMAND:
            return_value = deserialize_Body(id::RLNCREMOTEFLASHSTARTCOMMAND, Body_.rlncRemoteFlashStartCommand_, buffer, wire_type);

            break;

          case id::RLNCREMOTEFLASHSTOPCOMMAND:
            return_value = deserialize_Body(id::RLNCREMOTEFLASHSTOPCOMMAND, Body_.rlncRemoteFlashStopCommand_, buffer, wire_type);

            break;

          case id::RLNCQUERYREMOTEFLASHCOMMAND:
            return_value = deserialize_Body(id::RLNCQUERYREMOTEFLASHCOMMAND, Body_.rlncQueryRemoteFlashCommand_, buffer, wire_type);

            break;

          case id::RLNCREMOTEFLASHRESPONSE:
            return_value = deserialize_Body(id::RLNCREMOTEFLASHRESPONSE, Body_.rlncRemoteFlashResponse_, buffer, wire_type);

            break;

          case id::RLNCINITCONFIGCOMMAND:
            return_value = deserialize_Body(id::RLNCINITCONFIGCOMMAND, Body_.rlncInitConfigCommand_, buffer, wire_type);

            break;

          case id::RLNCENCODEDFRAGMENT:
            return_value = deserialize_Body(id::RLNCENCODEDFRAGMENT, Body_.rlncEncodedFragment_, buffer, wire_type);

            break;

          case id::RLNCSTATEUPDATE:
            return_value = deserialize_Body(id::RLNCSTATEUPDATE, Body_.rlncStateUpdate_, buffer, wire_type);

            break;

          case id::RLNCTERMINATIONCOMMAND:
            return_value = deserialize_Body(id::RLNCTERMINATIONCOMMAND, Body_.rlncTerminationCommand_, buffer, wire_type);

            break;

          case id::DECODINGRESULT:
            return_value = deserialize_Body(id::DECODINGRESULT, Body_.decodingResult_, buffer, wire_type);

            break;

          case id::DECODINGUPDATE:
            return_value = deserialize_Body(id::DECODINGUPDATE, Body_.decodingUpdate_, buffer, wire_type);

            break;

          case id::DEVICECONFIGURATION:
            return_value = deserialize_Body(id::DEVICECONFIGURATION, Body_.deviceConfiguration_, buffer, wire_type);

            break;

          case id::REQUESTBOOTINFO:
            return_value = deserialize_Body(id::REQUESTBOOTINFO, Body_.requestBootInfo_, buffer, wire_type);

            break;

          case id::BOOTMESSAGE:
            return_value = deserialize_Body(id::BOOTMESSAGE, Body_.bootMessage_, buffer, wire_type);

            break;

          case id::RESETRADIO:
            return_value = deserialize_Body(id::RESETRADIO, Body_.resetRadio_, buffer, wire_type);

            break;

          case id::ACK:
            return_value = deserialize_Body(id::ACK, Body_.ack_, buffer, wire_type);

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
      clear_CorrelationCode();
      clear_Payload();
      clear_Body();

    }

    private:


      EmbeddedProto::boolean IsMulticast_ = false;
      EmbeddedProto::uint32 DeviceId_ = 0U;
      EmbeddedProto::uint32 CorrelationCode_ = 0U;
      ::EmbeddedProto::FieldBytes<Payload_LENGTH> Payload_;

      id which_Body_ = id::NOT_SET;
      union Body
      {
        Body() {}
        ~Body() {}
        ForwardExperimentCommand forwardExperimentCommand_;
        ExperimentResponse experimentResponse_;
        MeasurementStreamRequest measurementStreamRequest_;
        MeasurementStreamFragment measurementStreamFragment_;
        RlncRemoteFlashStartCommand rlncRemoteFlashStartCommand_;
        RlncRemoteFlashStopCommand rlncRemoteFlashStopCommand_;
        RlncQueryRemoteFlashState rlncQueryRemoteFlashCommand_;
        RlncRemoteFlashResponse rlncRemoteFlashResponse_;
        RlncInitConfigCommand rlncInitConfigCommand_;
        RlncEncodedFragment rlncEncodedFragment_;
        RlncStateUpdate rlncStateUpdate_;
        RlncTerminationCommand rlncTerminationCommand_;
        DecodingResult decodingResult_;
        DecodingUpdate decodingUpdate_;
        DeviceConfiguration deviceConfiguration_;
        RequestBootInfo requestBootInfo_;
        BootMessage bootMessage_;
        LoRaReset resetRadio_;
        LoRaAck ack_;
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
          case id::FORWARDEXPERIMENTCOMMAND:
            new(&Body_.forwardExperimentCommand_) ForwardExperimentCommand;
            which_Body_ = id::FORWARDEXPERIMENTCOMMAND;
            break;

          case id::EXPERIMENTRESPONSE:
            new(&Body_.experimentResponse_) ExperimentResponse;
            which_Body_ = id::EXPERIMENTRESPONSE;
            break;

          case id::MEASUREMENTSTREAMREQUEST:
            new(&Body_.measurementStreamRequest_) MeasurementStreamRequest;
            which_Body_ = id::MEASUREMENTSTREAMREQUEST;
            break;

          case id::MEASUREMENTSTREAMFRAGMENT:
            new(&Body_.measurementStreamFragment_) MeasurementStreamFragment;
            which_Body_ = id::MEASUREMENTSTREAMFRAGMENT;
            break;

          case id::RLNCREMOTEFLASHSTARTCOMMAND:
            new(&Body_.rlncRemoteFlashStartCommand_) RlncRemoteFlashStartCommand;
            which_Body_ = id::RLNCREMOTEFLASHSTARTCOMMAND;
            break;

          case id::RLNCREMOTEFLASHSTOPCOMMAND:
            new(&Body_.rlncRemoteFlashStopCommand_) RlncRemoteFlashStopCommand;
            which_Body_ = id::RLNCREMOTEFLASHSTOPCOMMAND;
            break;

          case id::RLNCQUERYREMOTEFLASHCOMMAND:
            new(&Body_.rlncQueryRemoteFlashCommand_) RlncQueryRemoteFlashState;
            which_Body_ = id::RLNCQUERYREMOTEFLASHCOMMAND;
            break;

          case id::RLNCREMOTEFLASHRESPONSE:
            new(&Body_.rlncRemoteFlashResponse_) RlncRemoteFlashResponse;
            which_Body_ = id::RLNCREMOTEFLASHRESPONSE;
            break;

          case id::RLNCINITCONFIGCOMMAND:
            new(&Body_.rlncInitConfigCommand_) RlncInitConfigCommand;
            which_Body_ = id::RLNCINITCONFIGCOMMAND;
            break;

          case id::RLNCENCODEDFRAGMENT:
            new(&Body_.rlncEncodedFragment_) RlncEncodedFragment;
            which_Body_ = id::RLNCENCODEDFRAGMENT;
            break;

          case id::RLNCSTATEUPDATE:
            new(&Body_.rlncStateUpdate_) RlncStateUpdate;
            which_Body_ = id::RLNCSTATEUPDATE;
            break;

          case id::RLNCTERMINATIONCOMMAND:
            new(&Body_.rlncTerminationCommand_) RlncTerminationCommand;
            which_Body_ = id::RLNCTERMINATIONCOMMAND;
            break;

          case id::DECODINGRESULT:
            new(&Body_.decodingResult_) DecodingResult;
            which_Body_ = id::DECODINGRESULT;
            break;

          case id::DECODINGUPDATE:
            new(&Body_.decodingUpdate_) DecodingUpdate;
            which_Body_ = id::DECODINGUPDATE;
            break;

          case id::DEVICECONFIGURATION:
            new(&Body_.deviceConfiguration_) DeviceConfiguration;
            which_Body_ = id::DEVICECONFIGURATION;
            break;

          case id::REQUESTBOOTINFO:
            new(&Body_.requestBootInfo_) RequestBootInfo;
            which_Body_ = id::REQUESTBOOTINFO;
            break;

          case id::BOOTMESSAGE:
            new(&Body_.bootMessage_) BootMessage;
            which_Body_ = id::BOOTMESSAGE;
            break;

          case id::RESETRADIO:
            new(&Body_.resetRadio_) LoRaReset;
            which_Body_ = id::RESETRADIO;
            break;

          case id::ACK:
            new(&Body_.ack_) LoRaAck;
            which_Body_ = id::ACK;
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
          case id::FORWARDEXPERIMENTCOMMAND:
            Body_.forwardExperimentCommand_.~ForwardExperimentCommand(); // NOSONAR Unions require this.
            break;
          case id::EXPERIMENTRESPONSE:
            Body_.experimentResponse_.~ExperimentResponse(); // NOSONAR Unions require this.
            break;
          case id::MEASUREMENTSTREAMREQUEST:
            Body_.measurementStreamRequest_.~MeasurementStreamRequest(); // NOSONAR Unions require this.
            break;
          case id::MEASUREMENTSTREAMFRAGMENT:
            Body_.measurementStreamFragment_.~MeasurementStreamFragment(); // NOSONAR Unions require this.
            break;
          case id::RLNCREMOTEFLASHSTARTCOMMAND:
            Body_.rlncRemoteFlashStartCommand_.~RlncRemoteFlashStartCommand(); // NOSONAR Unions require this.
            break;
          case id::RLNCREMOTEFLASHSTOPCOMMAND:
            Body_.rlncRemoteFlashStopCommand_.~RlncRemoteFlashStopCommand(); // NOSONAR Unions require this.
            break;
          case id::RLNCQUERYREMOTEFLASHCOMMAND:
            Body_.rlncQueryRemoteFlashCommand_.~RlncQueryRemoteFlashState(); // NOSONAR Unions require this.
            break;
          case id::RLNCREMOTEFLASHRESPONSE:
            Body_.rlncRemoteFlashResponse_.~RlncRemoteFlashResponse(); // NOSONAR Unions require this.
            break;
          case id::RLNCINITCONFIGCOMMAND:
            Body_.rlncInitConfigCommand_.~RlncInitConfigCommand(); // NOSONAR Unions require this.
            break;
          case id::RLNCENCODEDFRAGMENT:
            Body_.rlncEncodedFragment_.~RlncEncodedFragment(); // NOSONAR Unions require this.
            break;
          case id::RLNCSTATEUPDATE:
            Body_.rlncStateUpdate_.~RlncStateUpdate(); // NOSONAR Unions require this.
            break;
          case id::RLNCTERMINATIONCOMMAND:
            Body_.rlncTerminationCommand_.~RlncTerminationCommand(); // NOSONAR Unions require this.
            break;
          case id::DECODINGRESULT:
            Body_.decodingResult_.~DecodingResult(); // NOSONAR Unions require this.
            break;
          case id::DECODINGUPDATE:
            Body_.decodingUpdate_.~DecodingUpdate(); // NOSONAR Unions require this.
            break;
          case id::DEVICECONFIGURATION:
            Body_.deviceConfiguration_.~DeviceConfiguration(); // NOSONAR Unions require this.
            break;
          case id::REQUESTBOOTINFO:
            Body_.requestBootInfo_.~RequestBootInfo(); // NOSONAR Unions require this.
            break;
          case id::BOOTMESSAGE:
            Body_.bootMessage_.~BootMessage(); // NOSONAR Unions require this.
            break;
          case id::RESETRADIO:
            Body_.resetRadio_.~LoRaReset(); // NOSONAR Unions require this.
            break;
          case id::ACK:
            Body_.ack_.~LoRaAck(); // NOSONAR Unions require this.
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

#endif // LORA_DEVICE_MESSAGES_H