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
#include <shared/lora_phy.h>


class ForwardSequenceConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    ForwardSequenceConfig() = default;
    ForwardSequenceConfig(const ForwardSequenceConfig& rhs )
    {
      set_Indefinite(rhs.get_Indefinite());
      set_SequenceCountLimit(rhs.get_SequenceCountLimit());
      set_Period(rhs.get_Period());
    }

    ForwardSequenceConfig(const ForwardSequenceConfig&& rhs ) noexcept
    {
      set_Indefinite(rhs.get_Indefinite());
      set_SequenceCountLimit(rhs.get_SequenceCountLimit());
      set_Period(rhs.get_Period());
    }

    ~ForwardSequenceConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      INDEFINITE = 1,
      SEQUENCECOUNTLIMIT = 2,
      PERIOD = 3
    };

    ForwardSequenceConfig& operator=(const ForwardSequenceConfig& rhs)
    {
      set_Indefinite(rhs.get_Indefinite());
      set_SequenceCountLimit(rhs.get_SequenceCountLimit());
      set_Period(rhs.get_Period());
      return *this;
    }

    ForwardSequenceConfig& operator=(const ForwardSequenceConfig&& rhs) noexcept
    {
      set_Indefinite(rhs.get_Indefinite());
      set_SequenceCountLimit(rhs.get_SequenceCountLimit());
      set_Period(rhs.get_Period());
      return *this;
    }

    inline void clear_Indefinite() { Indefinite_.clear(); }
    inline void set_Indefinite(const EmbeddedProto::boolean& value) { Indefinite_ = value; }
    inline void set_Indefinite(const EmbeddedProto::boolean&& value) { Indefinite_ = value; }
    inline EmbeddedProto::boolean& mutable_Indefinite() { return Indefinite_; }
    inline const EmbeddedProto::boolean& get_Indefinite() const { return Indefinite_; }
    inline EmbeddedProto::boolean::FIELD_TYPE Indefinite() const { return Indefinite_.get(); }

    inline void clear_SequenceCountLimit() { SequenceCountLimit_.clear(); }
    inline void set_SequenceCountLimit(const EmbeddedProto::uint32& value) { SequenceCountLimit_ = value; }
    inline void set_SequenceCountLimit(const EmbeddedProto::uint32&& value) { SequenceCountLimit_ = value; }
    inline EmbeddedProto::uint32& mutable_SequenceCountLimit() { return SequenceCountLimit_; }
    inline const EmbeddedProto::uint32& get_SequenceCountLimit() const { return SequenceCountLimit_; }
    inline EmbeddedProto::uint32::FIELD_TYPE SequenceCountLimit() const { return SequenceCountLimit_.get(); }

    inline void clear_Period() { Period_.clear(); }
    inline void set_Period(const EmbeddedProto::uint32& value) { Period_ = value; }
    inline void set_Period(const EmbeddedProto::uint32&& value) { Period_ = value; }
    inline EmbeddedProto::uint32& mutable_Period() { return Period_; }
    inline const EmbeddedProto::uint32& get_Period() const { return Period_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Period() const { return Period_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != Indefinite_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Indefinite_.serialize_with_id(static_cast<uint32_t>(id::INDEFINITE), buffer, false);
      }

      if((0U != SequenceCountLimit_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SequenceCountLimit_.serialize_with_id(static_cast<uint32_t>(id::SEQUENCECOUNTLIMIT), buffer, false);
      }

      if((0U != Period_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Period_.serialize_with_id(static_cast<uint32_t>(id::PERIOD), buffer, false);
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
          case id::INDEFINITE:
            return_value = Indefinite_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SEQUENCECOUNTLIMIT:
            return_value = SequenceCountLimit_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PERIOD:
            return_value = Period_.deserialize_check_type(buffer, wire_type);
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
      clear_Indefinite();
      clear_SequenceCountLimit();
      clear_Period();

    }

    private:


      EmbeddedProto::boolean Indefinite_ = false;
      EmbeddedProto::uint32 SequenceCountLimit_ = 0U;
      EmbeddedProto::uint32 Period_ = 0U;

};

class ForwardRadioConfigUpdate final: public ::EmbeddedProto::MessageInterface
{
  public:
    ForwardRadioConfigUpdate() = default;
    ForwardRadioConfigUpdate(const ForwardRadioConfigUpdate& rhs )
    {
      set_radioRxConfig(rhs.get_radioRxConfig());
      set_radioTxConfig(rhs.get_radioTxConfig());
      set_ResetRadio(rhs.get_ResetRadio());
    }

    ForwardRadioConfigUpdate(const ForwardRadioConfigUpdate&& rhs ) noexcept
    {
      set_radioRxConfig(rhs.get_radioRxConfig());
      set_radioTxConfig(rhs.get_radioTxConfig());
      set_ResetRadio(rhs.get_ResetRadio());
    }

    ~ForwardRadioConfigUpdate() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      RADIORXCONFIG = 1,
      RADIOTXCONFIG = 2,
      RESETRADIO = 3
    };

    ForwardRadioConfigUpdate& operator=(const ForwardRadioConfigUpdate& rhs)
    {
      set_radioRxConfig(rhs.get_radioRxConfig());
      set_radioTxConfig(rhs.get_radioTxConfig());
      set_ResetRadio(rhs.get_ResetRadio());
      return *this;
    }

    ForwardRadioConfigUpdate& operator=(const ForwardRadioConfigUpdate&& rhs) noexcept
    {
      set_radioRxConfig(rhs.get_radioRxConfig());
      set_radioTxConfig(rhs.get_radioTxConfig());
      set_ResetRadio(rhs.get_ResetRadio());
      return *this;
    }

    inline bool has_radioRxConfig() const
    {
      return 0 != (presence::mask(presence::fields::RADIORXCONFIG) & presence_[presence::index(presence::fields::RADIORXCONFIG)]);
    }
    inline void clear_radioRxConfig()
    {
      presence_[presence::index(presence::fields::RADIORXCONFIG)] &= ~(presence::mask(presence::fields::RADIORXCONFIG));
      radioRxConfig_.clear();
    }
    inline void set_radioRxConfig(const RadioRxConfig& value)
    {
      presence_[presence::index(presence::fields::RADIORXCONFIG)] |= presence::mask(presence::fields::RADIORXCONFIG);
      radioRxConfig_ = value;
    }
    inline void set_radioRxConfig(const RadioRxConfig&& value)
    {
      presence_[presence::index(presence::fields::RADIORXCONFIG)] |= presence::mask(presence::fields::RADIORXCONFIG);
      radioRxConfig_ = value;
    }
    inline RadioRxConfig& mutable_radioRxConfig()
    {
      presence_[presence::index(presence::fields::RADIORXCONFIG)] |= presence::mask(presence::fields::RADIORXCONFIG);
      return radioRxConfig_;
    }
    inline const RadioRxConfig& get_radioRxConfig() const { return radioRxConfig_; }
    inline const RadioRxConfig& radioRxConfig() const { return radioRxConfig_; }

    inline bool has_radioTxConfig() const
    {
      return 0 != (presence::mask(presence::fields::RADIOTXCONFIG) & presence_[presence::index(presence::fields::RADIOTXCONFIG)]);
    }
    inline void clear_radioTxConfig()
    {
      presence_[presence::index(presence::fields::RADIOTXCONFIG)] &= ~(presence::mask(presence::fields::RADIOTXCONFIG));
      radioTxConfig_.clear();
    }
    inline void set_radioTxConfig(const RadioTxConfig& value)
    {
      presence_[presence::index(presence::fields::RADIOTXCONFIG)] |= presence::mask(presence::fields::RADIOTXCONFIG);
      radioTxConfig_ = value;
    }
    inline void set_radioTxConfig(const RadioTxConfig&& value)
    {
      presence_[presence::index(presence::fields::RADIOTXCONFIG)] |= presence::mask(presence::fields::RADIOTXCONFIG);
      radioTxConfig_ = value;
    }
    inline RadioTxConfig& mutable_radioTxConfig()
    {
      presence_[presence::index(presence::fields::RADIOTXCONFIG)] |= presence::mask(presence::fields::RADIOTXCONFIG);
      return radioTxConfig_;
    }
    inline const RadioTxConfig& get_radioTxConfig() const { return radioTxConfig_; }
    inline const RadioTxConfig& radioTxConfig() const { return radioTxConfig_; }

    inline void clear_ResetRadio() { ResetRadio_.clear(); }
    inline void set_ResetRadio(const EmbeddedProto::boolean& value) { ResetRadio_ = value; }
    inline void set_ResetRadio(const EmbeddedProto::boolean&& value) { ResetRadio_ = value; }
    inline EmbeddedProto::boolean& mutable_ResetRadio() { return ResetRadio_; }
    inline const EmbeddedProto::boolean& get_ResetRadio() const { return ResetRadio_; }
    inline EmbeddedProto::boolean::FIELD_TYPE ResetRadio() const { return ResetRadio_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(has_radioRxConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = radioRxConfig_.serialize_with_id(static_cast<uint32_t>(id::RADIORXCONFIG), buffer, true);
      }

      if(has_radioTxConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = radioTxConfig_.serialize_with_id(static_cast<uint32_t>(id::RADIOTXCONFIG), buffer, true);
      }

      if((false != ResetRadio_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ResetRadio_.serialize_with_id(static_cast<uint32_t>(id::RESETRADIO), buffer, false);
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
          case id::RADIORXCONFIG:
            presence_[presence::index(presence::fields::RADIORXCONFIG)] |= presence::mask(presence::fields::RADIORXCONFIG);
            return_value = radioRxConfig_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RADIOTXCONFIG:
            presence_[presence::index(presence::fields::RADIOTXCONFIG)] |= presence::mask(presence::fields::RADIOTXCONFIG);
            return_value = radioTxConfig_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RESETRADIO:
            return_value = ResetRadio_.deserialize_check_type(buffer, wire_type);
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
      clear_radioRxConfig();
      clear_radioTxConfig();
      clear_ResetRadio();

    }

    private:

      // Define constants for tracking the presence of fields.
      // Use a struct to scope the variables from user fields as namespaces are not allowed within classes.
      struct presence
      {
        // An enumeration with all the fields for which presence has to be tracked.
        enum class fields : uint32_t
        {
          RADIORXCONFIG,
          RADIOTXCONFIG
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

      RadioRxConfig radioRxConfig_;
      RadioTxConfig radioTxConfig_;
      EmbeddedProto::boolean ResetRadio_ = false;

};

class ForwardExperimentCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    ForwardExperimentCommand() = default;
    ForwardExperimentCommand(const ForwardExperimentCommand& rhs )
    {
      set_isTransmitterGateway(rhs.get_isTransmitterGateway());
      set_gatewayCommand(rhs.get_gatewayCommand());
      set_slaveCommand(rhs.get_slaveCommand());
    }

    ForwardExperimentCommand(const ForwardExperimentCommand&& rhs ) noexcept
    {
      set_isTransmitterGateway(rhs.get_isTransmitterGateway());
      set_gatewayCommand(rhs.get_gatewayCommand());
      set_slaveCommand(rhs.get_slaveCommand());
    }

    ~ForwardExperimentCommand() override = default;

    enum class GatewayCommand : uint32_t
    {
      PauseTransmit = 0,
      ResumeTransmit = 1,
      ResetTransmit = 2
    };

    enum class SlaveCommand : uint32_t
    {
      ClearFlash = 0,
      QueryFlash = 1,
      StreamFlashContents = 2
    };

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ISTRANSMITTERGATEWAY = 1,
      GATEWAYCOMMAND = 2,
      SLAVECOMMAND = 3
    };

    ForwardExperimentCommand& operator=(const ForwardExperimentCommand& rhs)
    {
      set_isTransmitterGateway(rhs.get_isTransmitterGateway());
      set_gatewayCommand(rhs.get_gatewayCommand());
      set_slaveCommand(rhs.get_slaveCommand());
      return *this;
    }

    ForwardExperimentCommand& operator=(const ForwardExperimentCommand&& rhs) noexcept
    {
      set_isTransmitterGateway(rhs.get_isTransmitterGateway());
      set_gatewayCommand(rhs.get_gatewayCommand());
      set_slaveCommand(rhs.get_slaveCommand());
      return *this;
    }

    inline void clear_isTransmitterGateway() { isTransmitterGateway_.clear(); }
    inline void set_isTransmitterGateway(const EmbeddedProto::boolean& value) { isTransmitterGateway_ = value; }
    inline void set_isTransmitterGateway(const EmbeddedProto::boolean&& value) { isTransmitterGateway_ = value; }
    inline EmbeddedProto::boolean& mutable_isTransmitterGateway() { return isTransmitterGateway_; }
    inline const EmbeddedProto::boolean& get_isTransmitterGateway() const { return isTransmitterGateway_; }
    inline EmbeddedProto::boolean::FIELD_TYPE isTransmitterGateway() const { return isTransmitterGateway_.get(); }

    inline bool has_gatewayCommand() const
    {
      return 0 != (presence::mask(presence::fields::GATEWAYCOMMAND) & presence_[presence::index(presence::fields::GATEWAYCOMMAND)]);
    }
    inline void clear_gatewayCommand()
    {
      presence_[presence::index(presence::fields::GATEWAYCOMMAND)] &= ~(presence::mask(presence::fields::GATEWAYCOMMAND));
      gatewayCommand_ = static_cast<GatewayCommand>(0);
    }
    inline void set_gatewayCommand(const GatewayCommand& value)
    {
      presence_[presence::index(presence::fields::GATEWAYCOMMAND)] |= presence::mask(presence::fields::GATEWAYCOMMAND);
      gatewayCommand_ = value;
    }
    inline void set_gatewayCommand(const GatewayCommand&& value)
    {
      presence_[presence::index(presence::fields::GATEWAYCOMMAND)] |= presence::mask(presence::fields::GATEWAYCOMMAND);
      gatewayCommand_ = value;
    }
    inline const GatewayCommand& get_gatewayCommand() const { return gatewayCommand_; }
    inline GatewayCommand gatewayCommand() const { return gatewayCommand_; }

    inline bool has_slaveCommand() const
    {
      return 0 != (presence::mask(presence::fields::SLAVECOMMAND) & presence_[presence::index(presence::fields::SLAVECOMMAND)]);
    }
    inline void clear_slaveCommand()
    {
      presence_[presence::index(presence::fields::SLAVECOMMAND)] &= ~(presence::mask(presence::fields::SLAVECOMMAND));
      slaveCommand_ = static_cast<SlaveCommand>(0);
    }
    inline void set_slaveCommand(const SlaveCommand& value)
    {
      presence_[presence::index(presence::fields::SLAVECOMMAND)] |= presence::mask(presence::fields::SLAVECOMMAND);
      slaveCommand_ = value;
    }
    inline void set_slaveCommand(const SlaveCommand&& value)
    {
      presence_[presence::index(presence::fields::SLAVECOMMAND)] |= presence::mask(presence::fields::SLAVECOMMAND);
      slaveCommand_ = value;
    }
    inline const SlaveCommand& get_slaveCommand() const { return slaveCommand_; }
    inline SlaveCommand slaveCommand() const { return slaveCommand_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != isTransmitterGateway_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = isTransmitterGateway_.serialize_with_id(static_cast<uint32_t>(id::ISTRANSMITTERGATEWAY), buffer, false);
      }

      if(has_gatewayCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(gatewayCommand_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::GATEWAYCOMMAND), buffer, true);
      }

      if(has_slaveCommand() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(slaveCommand_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::SLAVECOMMAND), buffer, true);
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
          case id::ISTRANSMITTERGATEWAY:
            return_value = isTransmitterGateway_.deserialize_check_type(buffer, wire_type);
            break;

          case id::GATEWAYCOMMAND:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_gatewayCommand(static_cast<GatewayCommand>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
            break;

          case id::SLAVECOMMAND:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_slaveCommand(static_cast<SlaveCommand>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
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
      clear_isTransmitterGateway();
      clear_gatewayCommand();
      clear_slaveCommand();

    }

    private:

      // Define constants for tracking the presence of fields.
      // Use a struct to scope the variables from user fields as namespaces are not allowed within classes.
      struct presence
      {
        // An enumeration with all the fields for which presence has to be tracked.
        enum class fields : uint32_t
        {
          GATEWAYCOMMAND,
          SLAVECOMMAND
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

      EmbeddedProto::boolean isTransmitterGateway_ = false;
      GatewayCommand gatewayCommand_ = static_cast<GatewayCommand>(0);
      SlaveCommand slaveCommand_ = static_cast<SlaveCommand>(0);

};

class MeasurementStreamRequest final: public ::EmbeddedProto::MessageInterface
{
  public:
    MeasurementStreamRequest() = default;
    MeasurementStreamRequest(const MeasurementStreamRequest& rhs )
    {
      set_FragmentSizeMax(rhs.get_FragmentSizeMax());
    }

    MeasurementStreamRequest(const MeasurementStreamRequest&& rhs ) noexcept
    {
      set_FragmentSizeMax(rhs.get_FragmentSizeMax());
    }

    ~MeasurementStreamRequest() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      FRAGMENTSIZEMAX = 1
    };

    MeasurementStreamRequest& operator=(const MeasurementStreamRequest& rhs)
    {
      set_FragmentSizeMax(rhs.get_FragmentSizeMax());
      return *this;
    }

    MeasurementStreamRequest& operator=(const MeasurementStreamRequest&& rhs) noexcept
    {
      set_FragmentSizeMax(rhs.get_FragmentSizeMax());
      return *this;
    }

    inline void clear_FragmentSizeMax() { FragmentSizeMax_.clear(); }
    inline void set_FragmentSizeMax(const EmbeddedProto::uint32& value) { FragmentSizeMax_ = value; }
    inline void set_FragmentSizeMax(const EmbeddedProto::uint32&& value) { FragmentSizeMax_ = value; }
    inline EmbeddedProto::uint32& mutable_FragmentSizeMax() { return FragmentSizeMax_; }
    inline const EmbeddedProto::uint32& get_FragmentSizeMax() const { return FragmentSizeMax_; }
    inline EmbeddedProto::uint32::FIELD_TYPE FragmentSizeMax() const { return FragmentSizeMax_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != FragmentSizeMax_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FragmentSizeMax_.serialize_with_id(static_cast<uint32_t>(id::FRAGMENTSIZEMAX), buffer, false);
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
          case id::FRAGMENTSIZEMAX:
            return_value = FragmentSizeMax_.deserialize_check_type(buffer, wire_type);
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
      clear_FragmentSizeMax();

    }

    private:


      EmbeddedProto::uint32 FragmentSizeMax_ = 0U;

};

class MeasurementStreamFragment final: public ::EmbeddedProto::MessageInterface
{
  public:
    MeasurementStreamFragment() = default;
    MeasurementStreamFragment(const MeasurementStreamFragment& rhs )
    {
    }

    MeasurementStreamFragment(const MeasurementStreamFragment&& rhs ) noexcept
    {
    }

    ~MeasurementStreamFragment() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
    };

    MeasurementStreamFragment& operator=(const MeasurementStreamFragment& rhs)
    {
      return *this;
    }

    MeasurementStreamFragment& operator=(const MeasurementStreamFragment&& rhs) noexcept
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

#endif // SHARED_EXPERIMENT_CONFIG_H