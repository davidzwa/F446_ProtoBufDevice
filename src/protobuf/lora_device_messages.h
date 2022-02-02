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
#include <shared/lora_config.h>


template<uint32_t payload_LENGTH>
class LoRaMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    LoRaMessage() = default;
    LoRaMessage(const LoRaMessage& rhs )
    {
      set_command(rhs.get_command());
      set_SequenceNumber(rhs.get_SequenceNumber());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::SPREADINGFACTORCONFIG:
          set_spreadingFactorConfig(rhs.get_spreadingFactorConfig());
          break;

        case id::SEQUENCEREQUESTCONFIG:
          set_sequenceRequestConfig(rhs.get_sequenceRequestConfig());
          break;

        case id::PAYLOAD:
          set_payload(rhs.get_payload());
          break;

        default:
          break;
      }

    }

    LoRaMessage(const LoRaMessage&& rhs ) noexcept
    {
      set_command(rhs.get_command());
      set_SequenceNumber(rhs.get_SequenceNumber());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::SPREADINGFACTORCONFIG:
          set_spreadingFactorConfig(rhs.get_spreadingFactorConfig());
          break;

        case id::SEQUENCEREQUESTCONFIG:
          set_sequenceRequestConfig(rhs.get_sequenceRequestConfig());
          break;

        case id::PAYLOAD:
          set_payload(rhs.get_payload());
          break;

        default:
          break;
      }

    }

    ~LoRaMessage() override = default;

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

    enum class id : uint32_t
    {
      NOT_SET = 0,
      COMMAND = 1,
      SEQUENCENUMBER = 2,
      SPREADINGFACTORCONFIG = 3,
      SEQUENCEREQUESTCONFIG = 4,
      PAYLOAD = 5
    };

    LoRaMessage& operator=(const LoRaMessage& rhs)
    {
      set_command(rhs.get_command());
      set_SequenceNumber(rhs.get_SequenceNumber());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::SPREADINGFACTORCONFIG:
          set_spreadingFactorConfig(rhs.get_spreadingFactorConfig());
          break;

        case id::SEQUENCEREQUESTCONFIG:
          set_sequenceRequestConfig(rhs.get_sequenceRequestConfig());
          break;

        case id::PAYLOAD:
          set_payload(rhs.get_payload());
          break;

        default:
          break;
      }

      return *this;
    }

    LoRaMessage& operator=(const LoRaMessage&& rhs) noexcept
    {
      set_command(rhs.get_command());
      set_SequenceNumber(rhs.get_SequenceNumber());
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::SPREADINGFACTORCONFIG:
          set_spreadingFactorConfig(rhs.get_spreadingFactorConfig());
          break;

        case id::SEQUENCEREQUESTCONFIG:
          set_sequenceRequestConfig(rhs.get_sequenceRequestConfig());
          break;

        case id::PAYLOAD:
          set_payload(rhs.get_payload());
          break;

        default:
          break;
      }

      return *this;
    }

    inline void clear_command() { command_ = static_cast<CommandType>(0); }
    inline void set_command(const CommandType& value) { command_ = value; }
    inline void set_command(const CommandType&& value) { command_ = value; }
    inline const CommandType& get_command() const { return command_; }
    inline CommandType command() const { return command_; }

    inline void clear_SequenceNumber() { SequenceNumber_.clear(); }
    inline void set_SequenceNumber(const EmbeddedProto::uint32& value) { SequenceNumber_ = value; }
    inline void set_SequenceNumber(const EmbeddedProto::uint32&& value) { SequenceNumber_ = value; }
    inline EmbeddedProto::uint32& mutable_SequenceNumber() { return SequenceNumber_; }
    inline const EmbeddedProto::uint32& get_SequenceNumber() const { return SequenceNumber_; }
    inline EmbeddedProto::uint32::FIELD_TYPE SequenceNumber() const { return SequenceNumber_.get(); }

    id get_which_Body() const { return which_Body_; }

    inline bool has_spreadingFactorConfig() const
    {
      return id::SPREADINGFACTORCONFIG == which_Body_;
    }
    inline void clear_spreadingFactorConfig()
    {
      if(id::SPREADINGFACTORCONFIG == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.spreadingFactorConfig_.~SpreadingFactorConfig();
      }
    }
    inline void set_spreadingFactorConfig(const SpreadingFactorConfig& value)
    {
      if(id::SPREADINGFACTORCONFIG != which_Body_)
      {
        init_Body(id::SPREADINGFACTORCONFIG);
      }
      Body_.spreadingFactorConfig_ = value;
    }
    inline void set_spreadingFactorConfig(const SpreadingFactorConfig&& value)
    {
      if(id::SPREADINGFACTORCONFIG != which_Body_)
      {
        init_Body(id::SPREADINGFACTORCONFIG);
      }
      Body_.spreadingFactorConfig_ = value;
    }
    inline SpreadingFactorConfig& mutable_spreadingFactorConfig()
    {
      if(id::SPREADINGFACTORCONFIG != which_Body_)
      {
        init_Body(id::SPREADINGFACTORCONFIG);
      }
      return Body_.spreadingFactorConfig_;
    }
    inline const SpreadingFactorConfig& get_spreadingFactorConfig() const { return Body_.spreadingFactorConfig_; }
    inline const SpreadingFactorConfig& spreadingFactorConfig() const { return Body_.spreadingFactorConfig_; }

    inline bool has_sequenceRequestConfig() const
    {
      return id::SEQUENCEREQUESTCONFIG == which_Body_;
    }
    inline void clear_sequenceRequestConfig()
    {
      if(id::SEQUENCEREQUESTCONFIG == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.sequenceRequestConfig_.~SequenceRequestConfig();
      }
    }
    inline void set_sequenceRequestConfig(const SequenceRequestConfig& value)
    {
      if(id::SEQUENCEREQUESTCONFIG != which_Body_)
      {
        init_Body(id::SEQUENCEREQUESTCONFIG);
      }
      Body_.sequenceRequestConfig_ = value;
    }
    inline void set_sequenceRequestConfig(const SequenceRequestConfig&& value)
    {
      if(id::SEQUENCEREQUESTCONFIG != which_Body_)
      {
        init_Body(id::SEQUENCEREQUESTCONFIG);
      }
      Body_.sequenceRequestConfig_ = value;
    }
    inline SequenceRequestConfig& mutable_sequenceRequestConfig()
    {
      if(id::SEQUENCEREQUESTCONFIG != which_Body_)
      {
        init_Body(id::SEQUENCEREQUESTCONFIG);
      }
      return Body_.sequenceRequestConfig_;
    }
    inline const SequenceRequestConfig& get_sequenceRequestConfig() const { return Body_.sequenceRequestConfig_; }
    inline const SequenceRequestConfig& sequenceRequestConfig() const { return Body_.sequenceRequestConfig_; }

    inline bool has_payload() const
    {
      return id::PAYLOAD == which_Body_;
    }
    inline void clear_payload()
    {
      if(id::PAYLOAD == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.payload_.~FieldBytes();
      }
    }
    inline ::EmbeddedProto::FieldBytes<payload_LENGTH>& mutable_payload()
    {
      if(id::PAYLOAD != which_Body_)
      {
        init_Body(id::PAYLOAD);
      }
      return Body_.payload_;
    }
    inline void set_payload(const ::EmbeddedProto::FieldBytes<payload_LENGTH>& rhs)
    {
      if(id::PAYLOAD != which_Body_)
      {
        init_Body(id::PAYLOAD);
      }
      Body_.payload_.set(rhs);
    }
    inline const ::EmbeddedProto::FieldBytes<payload_LENGTH>& get_payload() const { return Body_.payload_; }
    inline const uint8_t* payload() const { return Body_.payload_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<CommandType>(0) != command_) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(command_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::COMMAND), buffer, false);
      }

      if((0U != SequenceNumber_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SequenceNumber_.serialize_with_id(static_cast<uint32_t>(id::SEQUENCENUMBER), buffer, false);
      }

      switch(which_Body_)
      {
        case id::SPREADINGFACTORCONFIG:
          if(has_spreadingFactorConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.spreadingFactorConfig_.serialize_with_id(static_cast<uint32_t>(id::SPREADINGFACTORCONFIG), buffer, true);
          }
          break;

        case id::SEQUENCEREQUESTCONFIG:
          if(has_sequenceRequestConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.sequenceRequestConfig_.serialize_with_id(static_cast<uint32_t>(id::SEQUENCEREQUESTCONFIG), buffer, true);
          }
          break;

        case id::PAYLOAD:
          if(::EmbeddedProto::Error::NO_ERRORS == return_value)
          {
            return_value = Body_.payload_.serialize_with_id(static_cast<uint32_t>(id::PAYLOAD), buffer, true);
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
          case id::COMMAND:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_command(static_cast<CommandType>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
            break;

          case id::SEQUENCENUMBER:
            return_value = SequenceNumber_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SPREADINGFACTORCONFIG:
            return_value = deserialize_Body(id::SPREADINGFACTORCONFIG, Body_.spreadingFactorConfig_, buffer, wire_type);

            break;

          case id::SEQUENCEREQUESTCONFIG:
            return_value = deserialize_Body(id::SEQUENCEREQUESTCONFIG, Body_.sequenceRequestConfig_, buffer, wire_type);

            break;

          case id::PAYLOAD:
            return_value = deserialize_Body(id::PAYLOAD, Body_.payload_, buffer, wire_type);
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
      clear_command();
      clear_SequenceNumber();
      clear_Body();

    }

    private:


      CommandType command_ = static_cast<CommandType>(0);
      EmbeddedProto::uint32 SequenceNumber_ = 0U;

      id which_Body_ = id::NOT_SET;
      union Body
      {
        Body() {}
        ~Body() {}
        SpreadingFactorConfig spreadingFactorConfig_;
        SequenceRequestConfig sequenceRequestConfig_;
        ::EmbeddedProto::FieldBytes<payload_LENGTH> payload_;
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
          case id::SPREADINGFACTORCONFIG:
            new(&Body_.spreadingFactorConfig_) SpreadingFactorConfig;
            which_Body_ = id::SPREADINGFACTORCONFIG;
            break;

          case id::SEQUENCEREQUESTCONFIG:
            new(&Body_.sequenceRequestConfig_) SequenceRequestConfig;
            which_Body_ = id::SEQUENCEREQUESTCONFIG;
            break;

          case id::PAYLOAD:
            new(&Body_.payload_) ::EmbeddedProto::FieldBytes<payload_LENGTH>;
            which_Body_ = id::PAYLOAD;
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
          case id::SPREADINGFACTORCONFIG:
            Body_.spreadingFactorConfig_.~SpreadingFactorConfig(); // NOSONAR Unions require this.
            break;
          case id::SEQUENCEREQUESTCONFIG:
            Body_.sequenceRequestConfig_.~SequenceRequestConfig(); // NOSONAR Unions require this.
            break;
          case id::PAYLOAD:
            Body_.payload_.~FieldBytes(); // NOSONAR Unions require this.
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