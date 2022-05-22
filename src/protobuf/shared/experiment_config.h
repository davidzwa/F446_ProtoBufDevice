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


enum class PRngImplementation : uint32_t
{
  LFSR_32 = 0,
  XoShiRo_32 = 1
};

class ForwardExperimentCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    ForwardExperimentCommand() = default;
    ForwardExperimentCommand(const ForwardExperimentCommand& rhs )
    {
      set_slaveCommand(rhs.get_slaveCommand());
    }

    ForwardExperimentCommand(const ForwardExperimentCommand&& rhs ) noexcept
    {
      set_slaveCommand(rhs.get_slaveCommand());
    }

    ~ForwardExperimentCommand() override = default;

    enum class SlaveCommand : uint32_t
    {
      ClearFlash = 0,
      QueryFlash = 1,
      StreamFlashContents = 2
    };

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SLAVECOMMAND = 2
    };

    ForwardExperimentCommand& operator=(const ForwardExperimentCommand& rhs)
    {
      set_slaveCommand(rhs.get_slaveCommand());
      return *this;
    }

    ForwardExperimentCommand& operator=(const ForwardExperimentCommand&& rhs) noexcept
    {
      set_slaveCommand(rhs.get_slaveCommand());
      return *this;
    }

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
          SLAVECOMMAND
        };

        // The number of fields for which presence has to be tracked.
        static constexpr uint32_t N_FIELDS = 1;

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

      SlaveCommand slaveCommand_ = static_cast<SlaveCommand>(0);

};

class ExperimentResponse final: public ::EmbeddedProto::MessageInterface
{
  public:
    ExperimentResponse() = default;
    ExperimentResponse(const ExperimentResponse& rhs )
    {
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_WasCleared(rhs.get_WasCleared());
    }

    ExperimentResponse(const ExperimentResponse&& rhs ) noexcept
    {
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_WasCleared(rhs.get_WasCleared());
    }

    ~ExperimentResponse() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MEASUREMENTCOUNT = 1,
      MEASUREMENTSDISABLED = 2,
      WASCLEARED = 3
    };

    ExperimentResponse& operator=(const ExperimentResponse& rhs)
    {
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_WasCleared(rhs.get_WasCleared());
      return *this;
    }

    ExperimentResponse& operator=(const ExperimentResponse&& rhs) noexcept
    {
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_WasCleared(rhs.get_WasCleared());
      return *this;
    }

    inline void clear_MeasurementCount() { MeasurementCount_.clear(); }
    inline void set_MeasurementCount(const EmbeddedProto::uint32& value) { MeasurementCount_ = value; }
    inline void set_MeasurementCount(const EmbeddedProto::uint32&& value) { MeasurementCount_ = value; }
    inline EmbeddedProto::uint32& mutable_MeasurementCount() { return MeasurementCount_; }
    inline const EmbeddedProto::uint32& get_MeasurementCount() const { return MeasurementCount_; }
    inline EmbeddedProto::uint32::FIELD_TYPE MeasurementCount() const { return MeasurementCount_.get(); }

    inline void clear_MeasurementsDisabled() { MeasurementsDisabled_.clear(); }
    inline void set_MeasurementsDisabled(const EmbeddedProto::boolean& value) { MeasurementsDisabled_ = value; }
    inline void set_MeasurementsDisabled(const EmbeddedProto::boolean&& value) { MeasurementsDisabled_ = value; }
    inline EmbeddedProto::boolean& mutable_MeasurementsDisabled() { return MeasurementsDisabled_; }
    inline const EmbeddedProto::boolean& get_MeasurementsDisabled() const { return MeasurementsDisabled_; }
    inline EmbeddedProto::boolean::FIELD_TYPE MeasurementsDisabled() const { return MeasurementsDisabled_.get(); }

    inline void clear_WasCleared() { WasCleared_.clear(); }
    inline void set_WasCleared(const EmbeddedProto::boolean& value) { WasCleared_ = value; }
    inline void set_WasCleared(const EmbeddedProto::boolean&& value) { WasCleared_ = value; }
    inline EmbeddedProto::boolean& mutable_WasCleared() { return WasCleared_; }
    inline const EmbeddedProto::boolean& get_WasCleared() const { return WasCleared_; }
    inline EmbeddedProto::boolean::FIELD_TYPE WasCleared() const { return WasCleared_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != MeasurementCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MeasurementCount_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTCOUNT), buffer, false);
      }

      if((false != MeasurementsDisabled_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MeasurementsDisabled_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTSDISABLED), buffer, false);
      }

      if((false != WasCleared_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = WasCleared_.serialize_with_id(static_cast<uint32_t>(id::WASCLEARED), buffer, false);
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
          case id::MEASUREMENTCOUNT:
            return_value = MeasurementCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::MEASUREMENTSDISABLED:
            return_value = MeasurementsDisabled_.deserialize_check_type(buffer, wire_type);
            break;

          case id::WASCLEARED:
            return_value = WasCleared_.deserialize_check_type(buffer, wire_type);
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
      clear_MeasurementCount();
      clear_MeasurementsDisabled();
      clear_WasCleared();

    }

    private:


      EmbeddedProto::uint32 MeasurementCount_ = 0U;
      EmbeddedProto::boolean MeasurementsDisabled_ = false;
      EmbeddedProto::boolean WasCleared_ = false;

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

class SequenceConfiguration final: public ::EmbeddedProto::MessageInterface
{
  public:
    SequenceConfiguration() = default;
    SequenceConfiguration(const SequenceConfiguration& rhs )
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_Delay(rhs.get_Delay());
    }

    SequenceConfiguration(const SequenceConfiguration&& rhs ) noexcept
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_Delay(rhs.get_Delay());
    }

    ~SequenceConfiguration() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ENABLEALWAYSSEND = 1,
      ALWAYSSENDPERIOD = 2,
      LIMITEDSENDCOUNT = 3,
      DELAY = 4
    };

    SequenceConfiguration& operator=(const SequenceConfiguration& rhs)
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_Delay(rhs.get_Delay());
      return *this;
    }

    SequenceConfiguration& operator=(const SequenceConfiguration&& rhs) noexcept
    {
      set_EnableAlwaysSend(rhs.get_EnableAlwaysSend());
      set_AlwaysSendPeriod(rhs.get_AlwaysSendPeriod());
      set_LimitedSendCount(rhs.get_LimitedSendCount());
      set_Delay(rhs.get_Delay());
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

    inline void clear_Delay() { Delay_.clear(); }
    inline void set_Delay(const EmbeddedProto::uint32& value) { Delay_ = value; }
    inline void set_Delay(const EmbeddedProto::uint32&& value) { Delay_ = value; }
    inline EmbeddedProto::uint32& mutable_Delay() { return Delay_; }
    inline const EmbeddedProto::uint32& get_Delay() const { return Delay_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Delay() const { return Delay_.get(); }


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

      if((0U != Delay_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Delay_.serialize_with_id(static_cast<uint32_t>(id::DELAY), buffer, false);
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

          case id::DELAY:
            return_value = Delay_.deserialize_check_type(buffer, wire_type);
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
      clear_Delay();

    }

    private:


      EmbeddedProto::boolean EnableAlwaysSend_ = false;
      EmbeddedProto::uint32 AlwaysSendPeriod_ = 0U;
      EmbeddedProto::uint32 LimitedSendCount_ = 0U;
      EmbeddedProto::uint32 Delay_ = 0U;

};

class TransmitReceiveConfiguration final: public ::EmbeddedProto::MessageInterface
{
  public:
    TransmitReceiveConfiguration() = default;
    TransmitReceiveConfiguration(const TransmitReceiveConfiguration& rhs )
    {
      set_TxPower(rhs.get_TxPower());
      set_TxRxBandwidth(rhs.get_TxRxBandwidth());
      set_TxRxDataRate(rhs.get_TxRxDataRate());
      set_SetRx(rhs.get_SetRx());
      set_SetTx(rhs.get_SetTx());
    }

    TransmitReceiveConfiguration(const TransmitReceiveConfiguration&& rhs ) noexcept
    {
      set_TxPower(rhs.get_TxPower());
      set_TxRxBandwidth(rhs.get_TxRxBandwidth());
      set_TxRxDataRate(rhs.get_TxRxDataRate());
      set_SetRx(rhs.get_SetRx());
      set_SetTx(rhs.get_SetTx());
    }

    ~TransmitReceiveConfiguration() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      TXPOWER = 1,
      TXRXBANDWIDTH = 2,
      TXRXDATARATE = 3,
      SETRX = 4,
      SETTX = 5
    };

    TransmitReceiveConfiguration& operator=(const TransmitReceiveConfiguration& rhs)
    {
      set_TxPower(rhs.get_TxPower());
      set_TxRxBandwidth(rhs.get_TxRxBandwidth());
      set_TxRxDataRate(rhs.get_TxRxDataRate());
      set_SetRx(rhs.get_SetRx());
      set_SetTx(rhs.get_SetTx());
      return *this;
    }

    TransmitReceiveConfiguration& operator=(const TransmitReceiveConfiguration&& rhs) noexcept
    {
      set_TxPower(rhs.get_TxPower());
      set_TxRxBandwidth(rhs.get_TxRxBandwidth());
      set_TxRxDataRate(rhs.get_TxRxDataRate());
      set_SetRx(rhs.get_SetRx());
      set_SetTx(rhs.get_SetTx());
      return *this;
    }

    inline void clear_TxPower() { TxPower_.clear(); }
    inline void set_TxPower(const EmbeddedProto::int32& value) { TxPower_ = value; }
    inline void set_TxPower(const EmbeddedProto::int32&& value) { TxPower_ = value; }
    inline EmbeddedProto::int32& mutable_TxPower() { return TxPower_; }
    inline const EmbeddedProto::int32& get_TxPower() const { return TxPower_; }
    inline EmbeddedProto::int32::FIELD_TYPE TxPower() const { return TxPower_.get(); }

    inline void clear_TxRxBandwidth() { TxRxBandwidth_.clear(); }
    inline void set_TxRxBandwidth(const EmbeddedProto::uint32& value) { TxRxBandwidth_ = value; }
    inline void set_TxRxBandwidth(const EmbeddedProto::uint32&& value) { TxRxBandwidth_ = value; }
    inline EmbeddedProto::uint32& mutable_TxRxBandwidth() { return TxRxBandwidth_; }
    inline const EmbeddedProto::uint32& get_TxRxBandwidth() const { return TxRxBandwidth_; }
    inline EmbeddedProto::uint32::FIELD_TYPE TxRxBandwidth() const { return TxRxBandwidth_.get(); }

    inline void clear_TxRxDataRate() { TxRxDataRate_.clear(); }
    inline void set_TxRxDataRate(const EmbeddedProto::uint32& value) { TxRxDataRate_ = value; }
    inline void set_TxRxDataRate(const EmbeddedProto::uint32&& value) { TxRxDataRate_ = value; }
    inline EmbeddedProto::uint32& mutable_TxRxDataRate() { return TxRxDataRate_; }
    inline const EmbeddedProto::uint32& get_TxRxDataRate() const { return TxRxDataRate_; }
    inline EmbeddedProto::uint32::FIELD_TYPE TxRxDataRate() const { return TxRxDataRate_.get(); }

    inline void clear_SetRx() { SetRx_.clear(); }
    inline void set_SetRx(const EmbeddedProto::boolean& value) { SetRx_ = value; }
    inline void set_SetRx(const EmbeddedProto::boolean&& value) { SetRx_ = value; }
    inline EmbeddedProto::boolean& mutable_SetRx() { return SetRx_; }
    inline const EmbeddedProto::boolean& get_SetRx() const { return SetRx_; }
    inline EmbeddedProto::boolean::FIELD_TYPE SetRx() const { return SetRx_.get(); }

    inline void clear_SetTx() { SetTx_.clear(); }
    inline void set_SetTx(const EmbeddedProto::boolean& value) { SetTx_ = value; }
    inline void set_SetTx(const EmbeddedProto::boolean&& value) { SetTx_ = value; }
    inline EmbeddedProto::boolean& mutable_SetTx() { return SetTx_; }
    inline const EmbeddedProto::boolean& get_SetTx() const { return SetTx_; }
    inline EmbeddedProto::boolean::FIELD_TYPE SetTx() const { return SetTx_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != TxPower_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = TxPower_.serialize_with_id(static_cast<uint32_t>(id::TXPOWER), buffer, false);
      }

      if((0U != TxRxBandwidth_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = TxRxBandwidth_.serialize_with_id(static_cast<uint32_t>(id::TXRXBANDWIDTH), buffer, false);
      }

      if((0U != TxRxDataRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = TxRxDataRate_.serialize_with_id(static_cast<uint32_t>(id::TXRXDATARATE), buffer, false);
      }

      if((false != SetRx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SetRx_.serialize_with_id(static_cast<uint32_t>(id::SETRX), buffer, false);
      }

      if((false != SetTx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SetTx_.serialize_with_id(static_cast<uint32_t>(id::SETTX), buffer, false);
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
          case id::TXPOWER:
            return_value = TxPower_.deserialize_check_type(buffer, wire_type);
            break;

          case id::TXRXBANDWIDTH:
            return_value = TxRxBandwidth_.deserialize_check_type(buffer, wire_type);
            break;

          case id::TXRXDATARATE:
            return_value = TxRxDataRate_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SETRX:
            return_value = SetRx_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SETTX:
            return_value = SetTx_.deserialize_check_type(buffer, wire_type);
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
      clear_TxPower();
      clear_TxRxBandwidth();
      clear_TxRxDataRate();
      clear_SetRx();
      clear_SetTx();

    }

    private:


      EmbeddedProto::int32 TxPower_ = 0;
      EmbeddedProto::uint32 TxRxBandwidth_ = 0U;
      EmbeddedProto::uint32 TxRxDataRate_ = 0U;
      EmbeddedProto::boolean SetRx_ = false;
      EmbeddedProto::boolean SetTx_ = false;

};

class ReceptionRateConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    ReceptionRateConfig() = default;
    ReceptionRateConfig(const ReceptionRateConfig& rhs )
    {
      set_PacketErrorRate(rhs.get_PacketErrorRate());
      set_OverrideSeed(rhs.get_OverrideSeed());
      set_Seed(rhs.get_Seed());
      set_DropUpdateCommands(rhs.get_DropUpdateCommands());
      set_UseBurstLoss(rhs.get_UseBurstLoss());
      set_InitState(rhs.get_InitState());
      set_ProbP(rhs.get_ProbP());
      set_ProbR(rhs.get_ProbR());
      set_ProbK(rhs.get_ProbK());
      set_ProbH(rhs.get_ProbH());
    }

    ReceptionRateConfig(const ReceptionRateConfig&& rhs ) noexcept
    {
      set_PacketErrorRate(rhs.get_PacketErrorRate());
      set_OverrideSeed(rhs.get_OverrideSeed());
      set_Seed(rhs.get_Seed());
      set_DropUpdateCommands(rhs.get_DropUpdateCommands());
      set_UseBurstLoss(rhs.get_UseBurstLoss());
      set_InitState(rhs.get_InitState());
      set_ProbP(rhs.get_ProbP());
      set_ProbR(rhs.get_ProbR());
      set_ProbK(rhs.get_ProbK());
      set_ProbH(rhs.get_ProbH());
    }

    ~ReceptionRateConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      PACKETERRORRATE = 1,
      OVERRIDESEED = 2,
      SEED = 3,
      DROPUPDATECOMMANDS = 4,
      USEBURSTLOSS = 5,
      INITSTATE = 6,
      PROBP = 7,
      PROBR = 8,
      PROBK = 9,
      PROBH = 10
    };

    ReceptionRateConfig& operator=(const ReceptionRateConfig& rhs)
    {
      set_PacketErrorRate(rhs.get_PacketErrorRate());
      set_OverrideSeed(rhs.get_OverrideSeed());
      set_Seed(rhs.get_Seed());
      set_DropUpdateCommands(rhs.get_DropUpdateCommands());
      set_UseBurstLoss(rhs.get_UseBurstLoss());
      set_InitState(rhs.get_InitState());
      set_ProbP(rhs.get_ProbP());
      set_ProbR(rhs.get_ProbR());
      set_ProbK(rhs.get_ProbK());
      set_ProbH(rhs.get_ProbH());
      return *this;
    }

    ReceptionRateConfig& operator=(const ReceptionRateConfig&& rhs) noexcept
    {
      set_PacketErrorRate(rhs.get_PacketErrorRate());
      set_OverrideSeed(rhs.get_OverrideSeed());
      set_Seed(rhs.get_Seed());
      set_DropUpdateCommands(rhs.get_DropUpdateCommands());
      set_UseBurstLoss(rhs.get_UseBurstLoss());
      set_InitState(rhs.get_InitState());
      set_ProbP(rhs.get_ProbP());
      set_ProbR(rhs.get_ProbR());
      set_ProbK(rhs.get_ProbK());
      set_ProbH(rhs.get_ProbH());
      return *this;
    }

    inline void clear_PacketErrorRate() { PacketErrorRate_.clear(); }
    inline void set_PacketErrorRate(const EmbeddedProto::floatfixed& value) { PacketErrorRate_ = value; }
    inline void set_PacketErrorRate(const EmbeddedProto::floatfixed&& value) { PacketErrorRate_ = value; }
    inline EmbeddedProto::floatfixed& mutable_PacketErrorRate() { return PacketErrorRate_; }
    inline const EmbeddedProto::floatfixed& get_PacketErrorRate() const { return PacketErrorRate_; }
    inline EmbeddedProto::floatfixed::FIELD_TYPE PacketErrorRate() const { return PacketErrorRate_.get(); }

    inline void clear_OverrideSeed() { OverrideSeed_.clear(); }
    inline void set_OverrideSeed(const EmbeddedProto::boolean& value) { OverrideSeed_ = value; }
    inline void set_OverrideSeed(const EmbeddedProto::boolean&& value) { OverrideSeed_ = value; }
    inline EmbeddedProto::boolean& mutable_OverrideSeed() { return OverrideSeed_; }
    inline const EmbeddedProto::boolean& get_OverrideSeed() const { return OverrideSeed_; }
    inline EmbeddedProto::boolean::FIELD_TYPE OverrideSeed() const { return OverrideSeed_.get(); }

    inline void clear_Seed() { Seed_.clear(); }
    inline void set_Seed(const EmbeddedProto::uint32& value) { Seed_ = value; }
    inline void set_Seed(const EmbeddedProto::uint32&& value) { Seed_ = value; }
    inline EmbeddedProto::uint32& mutable_Seed() { return Seed_; }
    inline const EmbeddedProto::uint32& get_Seed() const { return Seed_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Seed() const { return Seed_.get(); }

    inline void clear_DropUpdateCommands() { DropUpdateCommands_.clear(); }
    inline void set_DropUpdateCommands(const EmbeddedProto::boolean& value) { DropUpdateCommands_ = value; }
    inline void set_DropUpdateCommands(const EmbeddedProto::boolean&& value) { DropUpdateCommands_ = value; }
    inline EmbeddedProto::boolean& mutable_DropUpdateCommands() { return DropUpdateCommands_; }
    inline const EmbeddedProto::boolean& get_DropUpdateCommands() const { return DropUpdateCommands_; }
    inline EmbeddedProto::boolean::FIELD_TYPE DropUpdateCommands() const { return DropUpdateCommands_.get(); }

    inline void clear_UseBurstLoss() { UseBurstLoss_.clear(); }
    inline void set_UseBurstLoss(const EmbeddedProto::boolean& value) { UseBurstLoss_ = value; }
    inline void set_UseBurstLoss(const EmbeddedProto::boolean&& value) { UseBurstLoss_ = value; }
    inline EmbeddedProto::boolean& mutable_UseBurstLoss() { return UseBurstLoss_; }
    inline const EmbeddedProto::boolean& get_UseBurstLoss() const { return UseBurstLoss_; }
    inline EmbeddedProto::boolean::FIELD_TYPE UseBurstLoss() const { return UseBurstLoss_.get(); }

    inline void clear_InitState() { InitState_.clear(); }
    inline void set_InitState(const EmbeddedProto::uint32& value) { InitState_ = value; }
    inline void set_InitState(const EmbeddedProto::uint32&& value) { InitState_ = value; }
    inline EmbeddedProto::uint32& mutable_InitState() { return InitState_; }
    inline const EmbeddedProto::uint32& get_InitState() const { return InitState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE InitState() const { return InitState_.get(); }

    inline void clear_ProbP() { ProbP_.clear(); }
    inline void set_ProbP(const EmbeddedProto::floatfixed& value) { ProbP_ = value; }
    inline void set_ProbP(const EmbeddedProto::floatfixed&& value) { ProbP_ = value; }
    inline EmbeddedProto::floatfixed& mutable_ProbP() { return ProbP_; }
    inline const EmbeddedProto::floatfixed& get_ProbP() const { return ProbP_; }
    inline EmbeddedProto::floatfixed::FIELD_TYPE ProbP() const { return ProbP_.get(); }

    inline void clear_ProbR() { ProbR_.clear(); }
    inline void set_ProbR(const EmbeddedProto::floatfixed& value) { ProbR_ = value; }
    inline void set_ProbR(const EmbeddedProto::floatfixed&& value) { ProbR_ = value; }
    inline EmbeddedProto::floatfixed& mutable_ProbR() { return ProbR_; }
    inline const EmbeddedProto::floatfixed& get_ProbR() const { return ProbR_; }
    inline EmbeddedProto::floatfixed::FIELD_TYPE ProbR() const { return ProbR_.get(); }

    inline void clear_ProbK() { ProbK_.clear(); }
    inline void set_ProbK(const EmbeddedProto::floatfixed& value) { ProbK_ = value; }
    inline void set_ProbK(const EmbeddedProto::floatfixed&& value) { ProbK_ = value; }
    inline EmbeddedProto::floatfixed& mutable_ProbK() { return ProbK_; }
    inline const EmbeddedProto::floatfixed& get_ProbK() const { return ProbK_; }
    inline EmbeddedProto::floatfixed::FIELD_TYPE ProbK() const { return ProbK_.get(); }

    inline void clear_ProbH() { ProbH_.clear(); }
    inline void set_ProbH(const EmbeddedProto::floatfixed& value) { ProbH_ = value; }
    inline void set_ProbH(const EmbeddedProto::floatfixed&& value) { ProbH_ = value; }
    inline EmbeddedProto::floatfixed& mutable_ProbH() { return ProbH_; }
    inline const EmbeddedProto::floatfixed& get_ProbH() const { return ProbH_; }
    inline EmbeddedProto::floatfixed::FIELD_TYPE ProbH() const { return ProbH_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0.0 != PacketErrorRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = PacketErrorRate_.serialize_with_id(static_cast<uint32_t>(id::PACKETERRORRATE), buffer, false);
      }

      if((false != OverrideSeed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = OverrideSeed_.serialize_with_id(static_cast<uint32_t>(id::OVERRIDESEED), buffer, false);
      }

      if((0U != Seed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Seed_.serialize_with_id(static_cast<uint32_t>(id::SEED), buffer, false);
      }

      if((false != DropUpdateCommands_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DropUpdateCommands_.serialize_with_id(static_cast<uint32_t>(id::DROPUPDATECOMMANDS), buffer, false);
      }

      if((false != UseBurstLoss_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = UseBurstLoss_.serialize_with_id(static_cast<uint32_t>(id::USEBURSTLOSS), buffer, false);
      }

      if((0U != InitState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = InitState_.serialize_with_id(static_cast<uint32_t>(id::INITSTATE), buffer, false);
      }

      if((0.0 != ProbP_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ProbP_.serialize_with_id(static_cast<uint32_t>(id::PROBP), buffer, false);
      }

      if((0.0 != ProbR_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ProbR_.serialize_with_id(static_cast<uint32_t>(id::PROBR), buffer, false);
      }

      if((0.0 != ProbK_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ProbK_.serialize_with_id(static_cast<uint32_t>(id::PROBK), buffer, false);
      }

      if((0.0 != ProbH_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ProbH_.serialize_with_id(static_cast<uint32_t>(id::PROBH), buffer, false);
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
          case id::PACKETERRORRATE:
            return_value = PacketErrorRate_.deserialize_check_type(buffer, wire_type);
            break;

          case id::OVERRIDESEED:
            return_value = OverrideSeed_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SEED:
            return_value = Seed_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DROPUPDATECOMMANDS:
            return_value = DropUpdateCommands_.deserialize_check_type(buffer, wire_type);
            break;

          case id::USEBURSTLOSS:
            return_value = UseBurstLoss_.deserialize_check_type(buffer, wire_type);
            break;

          case id::INITSTATE:
            return_value = InitState_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PROBP:
            return_value = ProbP_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PROBR:
            return_value = ProbR_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PROBK:
            return_value = ProbK_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PROBH:
            return_value = ProbH_.deserialize_check_type(buffer, wire_type);
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
      clear_PacketErrorRate();
      clear_OverrideSeed();
      clear_Seed();
      clear_DropUpdateCommands();
      clear_UseBurstLoss();
      clear_InitState();
      clear_ProbP();
      clear_ProbR();
      clear_ProbK();
      clear_ProbH();

    }

    private:


      EmbeddedProto::floatfixed PacketErrorRate_ = 0.0;
      EmbeddedProto::boolean OverrideSeed_ = false;
      EmbeddedProto::uint32 Seed_ = 0U;
      EmbeddedProto::boolean DropUpdateCommands_ = false;
      EmbeddedProto::boolean UseBurstLoss_ = false;
      EmbeddedProto::uint32 InitState_ = 0U;
      EmbeddedProto::floatfixed ProbP_ = 0.0;
      EmbeddedProto::floatfixed ProbR_ = 0.0;
      EmbeddedProto::floatfixed ProbK_ = 0.0;
      EmbeddedProto::floatfixed ProbH_ = 0.0;

};

#endif // SHARED_EXPERIMENT_CONFIG_H