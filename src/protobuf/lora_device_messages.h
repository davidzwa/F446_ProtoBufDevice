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
        case id::SEQUENCECONFIG:
          set_sequenceConfig(rhs.get_sequenceConfig());
          break;

        case id::FORWARDRADIOCONFIGUPDATE:
          set_forwardRadioConfigUpdate(rhs.get_forwardRadioConfigUpdate());
          break;

        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
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
        case id::SEQUENCECONFIG:
          set_sequenceConfig(rhs.get_sequenceConfig());
          break;

        case id::FORWARDRADIOCONFIGUPDATE:
          set_forwardRadioConfigUpdate(rhs.get_forwardRadioConfigUpdate());
          break;

        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
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
      SEQUENCECONFIG = 5,
      FORWARDRADIOCONFIGUPDATE = 6,
      FORWARDEXPERIMENTCOMMAND = 7,
      MEASUREMENTSTREAMREQUEST = 8,
      MEASUREMENTSTREAMFRAGMENT = 9
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
        case id::SEQUENCECONFIG:
          set_sequenceConfig(rhs.get_sequenceConfig());
          break;

        case id::FORWARDRADIOCONFIGUPDATE:
          set_forwardRadioConfigUpdate(rhs.get_forwardRadioConfigUpdate());
          break;

        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
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
        case id::SEQUENCECONFIG:
          set_sequenceConfig(rhs.get_sequenceConfig());
          break;

        case id::FORWARDRADIOCONFIGUPDATE:
          set_forwardRadioConfigUpdate(rhs.get_forwardRadioConfigUpdate());
          break;

        case id::FORWARDEXPERIMENTCOMMAND:
          set_forwardExperimentCommand(rhs.get_forwardExperimentCommand());
          break;

        case id::MEASUREMENTSTREAMREQUEST:
          set_measurementStreamRequest(rhs.get_measurementStreamRequest());
          break;

        case id::MEASUREMENTSTREAMFRAGMENT:
          set_measurementStreamFragment(rhs.get_measurementStreamFragment());
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

    inline bool has_sequenceConfig() const
    {
      return id::SEQUENCECONFIG == which_Body_;
    }
    inline void clear_sequenceConfig()
    {
      if(id::SEQUENCECONFIG == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.sequenceConfig_.~ForwardSequenceConfig();
      }
    }
    inline void set_sequenceConfig(const ForwardSequenceConfig& value)
    {
      if(id::SEQUENCECONFIG != which_Body_)
      {
        init_Body(id::SEQUENCECONFIG);
      }
      Body_.sequenceConfig_ = value;
    }
    inline void set_sequenceConfig(const ForwardSequenceConfig&& value)
    {
      if(id::SEQUENCECONFIG != which_Body_)
      {
        init_Body(id::SEQUENCECONFIG);
      }
      Body_.sequenceConfig_ = value;
    }
    inline ForwardSequenceConfig& mutable_sequenceConfig()
    {
      if(id::SEQUENCECONFIG != which_Body_)
      {
        init_Body(id::SEQUENCECONFIG);
      }
      return Body_.sequenceConfig_;
    }
    inline const ForwardSequenceConfig& get_sequenceConfig() const { return Body_.sequenceConfig_; }
    inline const ForwardSequenceConfig& sequenceConfig() const { return Body_.sequenceConfig_; }

    inline bool has_forwardRadioConfigUpdate() const
    {
      return id::FORWARDRADIOCONFIGUPDATE == which_Body_;
    }
    inline void clear_forwardRadioConfigUpdate()
    {
      if(id::FORWARDRADIOCONFIGUPDATE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.forwardRadioConfigUpdate_.~ForwardRadioConfigUpdate();
      }
    }
    inline void set_forwardRadioConfigUpdate(const ForwardRadioConfigUpdate& value)
    {
      if(id::FORWARDRADIOCONFIGUPDATE != which_Body_)
      {
        init_Body(id::FORWARDRADIOCONFIGUPDATE);
      }
      Body_.forwardRadioConfigUpdate_ = value;
    }
    inline void set_forwardRadioConfigUpdate(const ForwardRadioConfigUpdate&& value)
    {
      if(id::FORWARDRADIOCONFIGUPDATE != which_Body_)
      {
        init_Body(id::FORWARDRADIOCONFIGUPDATE);
      }
      Body_.forwardRadioConfigUpdate_ = value;
    }
    inline ForwardRadioConfigUpdate& mutable_forwardRadioConfigUpdate()
    {
      if(id::FORWARDRADIOCONFIGUPDATE != which_Body_)
      {
        init_Body(id::FORWARDRADIOCONFIGUPDATE);
      }
      return Body_.forwardRadioConfigUpdate_;
    }
    inline const ForwardRadioConfigUpdate& get_forwardRadioConfigUpdate() const { return Body_.forwardRadioConfigUpdate_; }
    inline const ForwardRadioConfigUpdate& forwardRadioConfigUpdate() const { return Body_.forwardRadioConfigUpdate_; }

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
        case id::SEQUENCECONFIG:
          if(has_sequenceConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.sequenceConfig_.serialize_with_id(static_cast<uint32_t>(id::SEQUENCECONFIG), buffer, true);
          }
          break;

        case id::FORWARDRADIOCONFIGUPDATE:
          if(has_forwardRadioConfigUpdate() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.forwardRadioConfigUpdate_.serialize_with_id(static_cast<uint32_t>(id::FORWARDRADIOCONFIGUPDATE), buffer, true);
          }
          break;

        case id::FORWARDEXPERIMENTCOMMAND:
          if(has_forwardExperimentCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.forwardExperimentCommand_.serialize_with_id(static_cast<uint32_t>(id::FORWARDEXPERIMENTCOMMAND), buffer, true);
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

          case id::SEQUENCECONFIG:
            return_value = deserialize_Body(id::SEQUENCECONFIG, Body_.sequenceConfig_, buffer, wire_type);

            break;

          case id::FORWARDRADIOCONFIGUPDATE:
            return_value = deserialize_Body(id::FORWARDRADIOCONFIGUPDATE, Body_.forwardRadioConfigUpdate_, buffer, wire_type);

            break;

          case id::FORWARDEXPERIMENTCOMMAND:
            return_value = deserialize_Body(id::FORWARDEXPERIMENTCOMMAND, Body_.forwardExperimentCommand_, buffer, wire_type);

            break;

          case id::MEASUREMENTSTREAMREQUEST:
            return_value = deserialize_Body(id::MEASUREMENTSTREAMREQUEST, Body_.measurementStreamRequest_, buffer, wire_type);

            break;

          case id::MEASUREMENTSTREAMFRAGMENT:
            return_value = deserialize_Body(id::MEASUREMENTSTREAMFRAGMENT, Body_.measurementStreamFragment_, buffer, wire_type);

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
        ForwardSequenceConfig sequenceConfig_;
        ForwardRadioConfigUpdate forwardRadioConfigUpdate_;
        ForwardExperimentCommand forwardExperimentCommand_;
        MeasurementStreamRequest measurementStreamRequest_;
        MeasurementStreamFragment measurementStreamFragment_;
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
          case id::SEQUENCECONFIG:
            new(&Body_.sequenceConfig_) ForwardSequenceConfig;
            which_Body_ = id::SEQUENCECONFIG;
            break;

          case id::FORWARDRADIOCONFIGUPDATE:
            new(&Body_.forwardRadioConfigUpdate_) ForwardRadioConfigUpdate;
            which_Body_ = id::FORWARDRADIOCONFIGUPDATE;
            break;

          case id::FORWARDEXPERIMENTCOMMAND:
            new(&Body_.forwardExperimentCommand_) ForwardExperimentCommand;
            which_Body_ = id::FORWARDEXPERIMENTCOMMAND;
            break;

          case id::MEASUREMENTSTREAMREQUEST:
            new(&Body_.measurementStreamRequest_) MeasurementStreamRequest;
            which_Body_ = id::MEASUREMENTSTREAMREQUEST;
            break;

          case id::MEASUREMENTSTREAMFRAGMENT:
            new(&Body_.measurementStreamFragment_) MeasurementStreamFragment;
            which_Body_ = id::MEASUREMENTSTREAMFRAGMENT;
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
          case id::SEQUENCECONFIG:
            Body_.sequenceConfig_.~ForwardSequenceConfig(); // NOSONAR Unions require this.
            break;
          case id::FORWARDRADIOCONFIGUPDATE:
            Body_.forwardRadioConfigUpdate_.~ForwardRadioConfigUpdate(); // NOSONAR Unions require this.
            break;
          case id::FORWARDEXPERIMENTCOMMAND:
            Body_.forwardExperimentCommand_.~ForwardExperimentCommand(); // NOSONAR Unions require this.
            break;
          case id::MEASUREMENTSTREAMREQUEST:
            Body_.measurementStreamRequest_.~MeasurementStreamRequest(); // NOSONAR Unions require this.
            break;
          case id::MEASUREMENTSTREAMFRAGMENT:
            Body_.measurementStreamFragment_.~MeasurementStreamFragment(); // NOSONAR Unions require this.
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