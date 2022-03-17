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
#ifndef UART_CONTROL_MESSAGES_H
#define UART_CONTROL_MESSAGES_H

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
#include <lora_device_messages.h>
#include <shared/lora_phy.h>


class ClearMeasurementsCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    ClearMeasurementsCommand() = default;
    ClearMeasurementsCommand(const ClearMeasurementsCommand& rhs )
    {
      set_SendBootAfter(rhs.get_SendBootAfter());
    }

    ClearMeasurementsCommand(const ClearMeasurementsCommand&& rhs ) noexcept
    {
      set_SendBootAfter(rhs.get_SendBootAfter());
    }

    ~ClearMeasurementsCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SENDBOOTAFTER = 1
    };

    ClearMeasurementsCommand& operator=(const ClearMeasurementsCommand& rhs)
    {
      set_SendBootAfter(rhs.get_SendBootAfter());
      return *this;
    }

    ClearMeasurementsCommand& operator=(const ClearMeasurementsCommand&& rhs) noexcept
    {
      set_SendBootAfter(rhs.get_SendBootAfter());
      return *this;
    }

    inline void clear_SendBootAfter() { SendBootAfter_.clear(); }
    inline void set_SendBootAfter(const EmbeddedProto::boolean& value) { SendBootAfter_ = value; }
    inline void set_SendBootAfter(const EmbeddedProto::boolean&& value) { SendBootAfter_ = value; }
    inline EmbeddedProto::boolean& mutable_SendBootAfter() { return SendBootAfter_; }
    inline const EmbeddedProto::boolean& get_SendBootAfter() const { return SendBootAfter_; }
    inline EmbeddedProto::boolean::FIELD_TYPE SendBootAfter() const { return SendBootAfter_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != SendBootAfter_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SendBootAfter_.serialize_with_id(static_cast<uint32_t>(id::SENDBOOTAFTER), buffer, false);
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
          case id::SENDBOOTAFTER:
            return_value = SendBootAfter_.deserialize_check_type(buffer, wire_type);
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
      clear_SendBootAfter();

    }

    private:


      EmbeddedProto::boolean SendBootAfter_ = false;

};

template<uint32_t transmitCommand_Payload_LENGTH>
class UartCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    UartCommand() = default;
    UartCommand(const UartCommand& rhs )
    {
      set_DoNotProxyCommand(rhs.get_DoNotProxyCommand());
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

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::CLEARMEASUREMENTSCOMMAND:
          set_clearMeasurementsCommand(rhs.get_clearMeasurementsCommand());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
          break;

        default:
          break;
      }

    }

    UartCommand(const UartCommand&& rhs ) noexcept
    {
      set_DoNotProxyCommand(rhs.get_DoNotProxyCommand());
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

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::CLEARMEASUREMENTSCOMMAND:
          set_clearMeasurementsCommand(rhs.get_clearMeasurementsCommand());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
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
      DEVICECONFIGURATION = 3,
      REQUESTBOOTINFO = 4,
      CLEARMEASUREMENTSCOMMAND = 5,
      TRANSMITCOMMAND = 6,
      DONOTPROXYCOMMAND = 8
    };

    UartCommand& operator=(const UartCommand& rhs)
    {
      set_DoNotProxyCommand(rhs.get_DoNotProxyCommand());
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

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::CLEARMEASUREMENTSCOMMAND:
          set_clearMeasurementsCommand(rhs.get_clearMeasurementsCommand());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
          break;

        default:
          break;
      }

      return *this;
    }

    UartCommand& operator=(const UartCommand&& rhs) noexcept
    {
      set_DoNotProxyCommand(rhs.get_DoNotProxyCommand());
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

        case id::DEVICECONFIGURATION:
          set_deviceConfiguration(rhs.get_deviceConfiguration());
          break;

        case id::REQUESTBOOTINFO:
          set_requestBootInfo(rhs.get_requestBootInfo());
          break;

        case id::CLEARMEASUREMENTSCOMMAND:
          set_clearMeasurementsCommand(rhs.get_clearMeasurementsCommand());
          break;

        case id::TRANSMITCOMMAND:
          set_transmitCommand(rhs.get_transmitCommand());
          break;

        default:
          break;
      }

      return *this;
    }

    inline void clear_DoNotProxyCommand() { DoNotProxyCommand_.clear(); }
    inline void set_DoNotProxyCommand(const EmbeddedProto::boolean& value) { DoNotProxyCommand_ = value; }
    inline void set_DoNotProxyCommand(const EmbeddedProto::boolean&& value) { DoNotProxyCommand_ = value; }
    inline EmbeddedProto::boolean& mutable_DoNotProxyCommand() { return DoNotProxyCommand_; }
    inline const EmbeddedProto::boolean& get_DoNotProxyCommand() const { return DoNotProxyCommand_; }
    inline EmbeddedProto::boolean::FIELD_TYPE DoNotProxyCommand() const { return DoNotProxyCommand_.get(); }

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

    inline bool has_clearMeasurementsCommand() const
    {
      return id::CLEARMEASUREMENTSCOMMAND == which_Body_;
    }
    inline void clear_clearMeasurementsCommand()
    {
      if(id::CLEARMEASUREMENTSCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.clearMeasurementsCommand_.~ClearMeasurementsCommand();
      }
    }
    inline void set_clearMeasurementsCommand(const ClearMeasurementsCommand& value)
    {
      if(id::CLEARMEASUREMENTSCOMMAND != which_Body_)
      {
        init_Body(id::CLEARMEASUREMENTSCOMMAND);
      }
      Body_.clearMeasurementsCommand_ = value;
    }
    inline void set_clearMeasurementsCommand(const ClearMeasurementsCommand&& value)
    {
      if(id::CLEARMEASUREMENTSCOMMAND != which_Body_)
      {
        init_Body(id::CLEARMEASUREMENTSCOMMAND);
      }
      Body_.clearMeasurementsCommand_ = value;
    }
    inline ClearMeasurementsCommand& mutable_clearMeasurementsCommand()
    {
      if(id::CLEARMEASUREMENTSCOMMAND != which_Body_)
      {
        init_Body(id::CLEARMEASUREMENTSCOMMAND);
      }
      return Body_.clearMeasurementsCommand_;
    }
    inline const ClearMeasurementsCommand& get_clearMeasurementsCommand() const { return Body_.clearMeasurementsCommand_; }
    inline const ClearMeasurementsCommand& clearMeasurementsCommand() const { return Body_.clearMeasurementsCommand_; }

    inline bool has_transmitCommand() const
    {
      return id::TRANSMITCOMMAND == which_Body_;
    }
    inline void clear_transmitCommand()
    {
      if(id::TRANSMITCOMMAND == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.transmitCommand_.~LoRaMessage<transmitCommand_Payload_LENGTH>();
      }
    }
    inline void set_transmitCommand(const LoRaMessage<transmitCommand_Payload_LENGTH>& value)
    {
      if(id::TRANSMITCOMMAND != which_Body_)
      {
        init_Body(id::TRANSMITCOMMAND);
      }
      Body_.transmitCommand_ = value;
    }
    inline void set_transmitCommand(const LoRaMessage<transmitCommand_Payload_LENGTH>&& value)
    {
      if(id::TRANSMITCOMMAND != which_Body_)
      {
        init_Body(id::TRANSMITCOMMAND);
      }
      Body_.transmitCommand_ = value;
    }
    inline LoRaMessage<transmitCommand_Payload_LENGTH>& mutable_transmitCommand()
    {
      if(id::TRANSMITCOMMAND != which_Body_)
      {
        init_Body(id::TRANSMITCOMMAND);
      }
      return Body_.transmitCommand_;
    }
    inline const LoRaMessage<transmitCommand_Payload_LENGTH>& get_transmitCommand() const { return Body_.transmitCommand_; }
    inline const LoRaMessage<transmitCommand_Payload_LENGTH>& transmitCommand() const { return Body_.transmitCommand_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != DoNotProxyCommand_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DoNotProxyCommand_.serialize_with_id(static_cast<uint32_t>(id::DONOTPROXYCOMMAND), buffer, false);
      }

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

        case id::CLEARMEASUREMENTSCOMMAND:
          if(has_clearMeasurementsCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.clearMeasurementsCommand_.serialize_with_id(static_cast<uint32_t>(id::CLEARMEASUREMENTSCOMMAND), buffer, true);
          }
          break;

        case id::TRANSMITCOMMAND:
          if(has_transmitCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.transmitCommand_.serialize_with_id(static_cast<uint32_t>(id::TRANSMITCOMMAND), buffer, true);
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
          case id::DONOTPROXYCOMMAND:
            return_value = DoNotProxyCommand_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RXCONFIG:
            return_value = deserialize_Body(id::RXCONFIG, Body_.rxConfig_, buffer, wire_type);

            break;

          case id::TXCONFIG:
            return_value = deserialize_Body(id::TXCONFIG, Body_.txConfig_, buffer, wire_type);

            break;

          case id::DEVICECONFIGURATION:
            return_value = deserialize_Body(id::DEVICECONFIGURATION, Body_.deviceConfiguration_, buffer, wire_type);

            break;

          case id::REQUESTBOOTINFO:
            return_value = deserialize_Body(id::REQUESTBOOTINFO, Body_.requestBootInfo_, buffer, wire_type);

            break;

          case id::CLEARMEASUREMENTSCOMMAND:
            return_value = deserialize_Body(id::CLEARMEASUREMENTSCOMMAND, Body_.clearMeasurementsCommand_, buffer, wire_type);

            break;

          case id::TRANSMITCOMMAND:
            return_value = deserialize_Body(id::TRANSMITCOMMAND, Body_.transmitCommand_, buffer, wire_type);

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
      clear_DoNotProxyCommand();
      clear_Body();

    }

    private:


      EmbeddedProto::boolean DoNotProxyCommand_ = false;

      id which_Body_ = id::NOT_SET;
      union Body
      {
        Body() {}
        ~Body() {}
        RadioRxConfig rxConfig_;
        RadioTxConfig txConfig_;
        DeviceConfiguration deviceConfiguration_;
        RequestBootInfo requestBootInfo_;
        ClearMeasurementsCommand clearMeasurementsCommand_;
        LoRaMessage<transmitCommand_Payload_LENGTH> transmitCommand_;
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

          case id::DEVICECONFIGURATION:
            new(&Body_.deviceConfiguration_) DeviceConfiguration;
            which_Body_ = id::DEVICECONFIGURATION;
            break;

          case id::REQUESTBOOTINFO:
            new(&Body_.requestBootInfo_) RequestBootInfo;
            which_Body_ = id::REQUESTBOOTINFO;
            break;

          case id::CLEARMEASUREMENTSCOMMAND:
            new(&Body_.clearMeasurementsCommand_) ClearMeasurementsCommand;
            which_Body_ = id::CLEARMEASUREMENTSCOMMAND;
            break;

          case id::TRANSMITCOMMAND:
            new(&Body_.transmitCommand_) LoRaMessage<transmitCommand_Payload_LENGTH>;
            which_Body_ = id::TRANSMITCOMMAND;
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
          case id::DEVICECONFIGURATION:
            Body_.deviceConfiguration_.~DeviceConfiguration(); // NOSONAR Unions require this.
            break;
          case id::REQUESTBOOTINFO:
            Body_.requestBootInfo_.~RequestBootInfo(); // NOSONAR Unions require this.
            break;
          case id::CLEARMEASUREMENTSCOMMAND:
            Body_.clearMeasurementsCommand_.~ClearMeasurementsCommand(); // NOSONAR Unions require this.
            break;
          case id::TRANSMITCOMMAND:
            Body_.transmitCommand_.~LoRaMessage<transmitCommand_Payload_LENGTH>(); // NOSONAR Unions require this.
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

#endif // UART_CONTROL_MESSAGES_H