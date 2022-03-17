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

class DecodingResult final: public ::EmbeddedProto::MessageInterface
{
  public:
    DecodingResult() = default;
    DecodingResult(const DecodingResult& rhs )
    {
      set_Success(rhs.get_Success());
      set_MatrixRank(rhs.get_MatrixRank());
      set_FirstDecodedNumber(rhs.get_FirstDecodedNumber());
      set_LastDecodedNumber(rhs.get_LastDecodedNumber());
    }

    DecodingResult(const DecodingResult&& rhs ) noexcept
    {
      set_Success(rhs.get_Success());
      set_MatrixRank(rhs.get_MatrixRank());
      set_FirstDecodedNumber(rhs.get_FirstDecodedNumber());
      set_LastDecodedNumber(rhs.get_LastDecodedNumber());
    }

    ~DecodingResult() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SUCCESS = 1,
      MATRIXRANK = 2,
      FIRSTDECODEDNUMBER = 3,
      LASTDECODEDNUMBER = 4
    };

    DecodingResult& operator=(const DecodingResult& rhs)
    {
      set_Success(rhs.get_Success());
      set_MatrixRank(rhs.get_MatrixRank());
      set_FirstDecodedNumber(rhs.get_FirstDecodedNumber());
      set_LastDecodedNumber(rhs.get_LastDecodedNumber());
      return *this;
    }

    DecodingResult& operator=(const DecodingResult&& rhs) noexcept
    {
      set_Success(rhs.get_Success());
      set_MatrixRank(rhs.get_MatrixRank());
      set_FirstDecodedNumber(rhs.get_FirstDecodedNumber());
      set_LastDecodedNumber(rhs.get_LastDecodedNumber());
      return *this;
    }

    inline void clear_Success() { Success_.clear(); }
    inline void set_Success(const EmbeddedProto::boolean& value) { Success_ = value; }
    inline void set_Success(const EmbeddedProto::boolean&& value) { Success_ = value; }
    inline EmbeddedProto::boolean& mutable_Success() { return Success_; }
    inline const EmbeddedProto::boolean& get_Success() const { return Success_; }
    inline EmbeddedProto::boolean::FIELD_TYPE Success() const { return Success_.get(); }

    inline void clear_MatrixRank() { MatrixRank_.clear(); }
    inline void set_MatrixRank(const EmbeddedProto::uint32& value) { MatrixRank_ = value; }
    inline void set_MatrixRank(const EmbeddedProto::uint32&& value) { MatrixRank_ = value; }
    inline EmbeddedProto::uint32& mutable_MatrixRank() { return MatrixRank_; }
    inline const EmbeddedProto::uint32& get_MatrixRank() const { return MatrixRank_; }
    inline EmbeddedProto::uint32::FIELD_TYPE MatrixRank() const { return MatrixRank_.get(); }

    inline void clear_FirstDecodedNumber() { FirstDecodedNumber_.clear(); }
    inline void set_FirstDecodedNumber(const EmbeddedProto::uint32& value) { FirstDecodedNumber_ = value; }
    inline void set_FirstDecodedNumber(const EmbeddedProto::uint32&& value) { FirstDecodedNumber_ = value; }
    inline EmbeddedProto::uint32& mutable_FirstDecodedNumber() { return FirstDecodedNumber_; }
    inline const EmbeddedProto::uint32& get_FirstDecodedNumber() const { return FirstDecodedNumber_; }
    inline EmbeddedProto::uint32::FIELD_TYPE FirstDecodedNumber() const { return FirstDecodedNumber_.get(); }

    inline void clear_LastDecodedNumber() { LastDecodedNumber_.clear(); }
    inline void set_LastDecodedNumber(const EmbeddedProto::uint32& value) { LastDecodedNumber_ = value; }
    inline void set_LastDecodedNumber(const EmbeddedProto::uint32&& value) { LastDecodedNumber_ = value; }
    inline EmbeddedProto::uint32& mutable_LastDecodedNumber() { return LastDecodedNumber_; }
    inline const EmbeddedProto::uint32& get_LastDecodedNumber() const { return LastDecodedNumber_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LastDecodedNumber() const { return LastDecodedNumber_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((false != Success_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Success_.serialize_with_id(static_cast<uint32_t>(id::SUCCESS), buffer, false);
      }

      if((0U != MatrixRank_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MatrixRank_.serialize_with_id(static_cast<uint32_t>(id::MATRIXRANK), buffer, false);
      }

      if((0U != FirstDecodedNumber_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FirstDecodedNumber_.serialize_with_id(static_cast<uint32_t>(id::FIRSTDECODEDNUMBER), buffer, false);
      }

      if((0U != LastDecodedNumber_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = LastDecodedNumber_.serialize_with_id(static_cast<uint32_t>(id::LASTDECODEDNUMBER), buffer, false);
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
          case id::SUCCESS:
            return_value = Success_.deserialize_check_type(buffer, wire_type);
            break;

          case id::MATRIXRANK:
            return_value = MatrixRank_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FIRSTDECODEDNUMBER:
            return_value = FirstDecodedNumber_.deserialize_check_type(buffer, wire_type);
            break;

          case id::LASTDECODEDNUMBER:
            return_value = LastDecodedNumber_.deserialize_check_type(buffer, wire_type);
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
      clear_Success();
      clear_MatrixRank();
      clear_FirstDecodedNumber();
      clear_LastDecodedNumber();

    }

    private:


      EmbeddedProto::boolean Success_ = false;
      EmbeddedProto::uint32 MatrixRank_ = 0U;
      EmbeddedProto::uint32 FirstDecodedNumber_ = 0U;
      EmbeddedProto::uint32 LastDecodedNumber_ = 0U;

};

class DecodingUpdate final: public ::EmbeddedProto::MessageInterface
{
  public:
    DecodingUpdate() = default;
    DecodingUpdate(const DecodingUpdate& rhs )
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_SecondRowCrc8(rhs.get_SecondRowCrc8());
      set_Rank(rhs.get_Rank());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
    }

    DecodingUpdate(const DecodingUpdate&& rhs ) noexcept
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_SecondRowCrc8(rhs.get_SecondRowCrc8());
      set_Rank(rhs.get_Rank());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
    }

    ~DecodingUpdate() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MATRIXCRC8 = 1,
      FIRSTROWCRC8 = 2,
      SECONDROWCRC8 = 3,
      RANK = 4,
      RECEIVEDFRAGMENTS = 5,
      CURRENTGENERATIONINDEX = 6,
      ISRUNNING = 7
    };

    DecodingUpdate& operator=(const DecodingUpdate& rhs)
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_SecondRowCrc8(rhs.get_SecondRowCrc8());
      set_Rank(rhs.get_Rank());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
      return *this;
    }

    DecodingUpdate& operator=(const DecodingUpdate&& rhs) noexcept
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_SecondRowCrc8(rhs.get_SecondRowCrc8());
      set_Rank(rhs.get_Rank());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
      return *this;
    }

    inline void clear_MatrixCrc8() { MatrixCrc8_.clear(); }
    inline void set_MatrixCrc8(const EmbeddedProto::uint32& value) { MatrixCrc8_ = value; }
    inline void set_MatrixCrc8(const EmbeddedProto::uint32&& value) { MatrixCrc8_ = value; }
    inline EmbeddedProto::uint32& mutable_MatrixCrc8() { return MatrixCrc8_; }
    inline const EmbeddedProto::uint32& get_MatrixCrc8() const { return MatrixCrc8_; }
    inline EmbeddedProto::uint32::FIELD_TYPE MatrixCrc8() const { return MatrixCrc8_.get(); }

    inline void clear_FirstRowCrc8() { FirstRowCrc8_.clear(); }
    inline void set_FirstRowCrc8(const EmbeddedProto::uint32& value) { FirstRowCrc8_ = value; }
    inline void set_FirstRowCrc8(const EmbeddedProto::uint32&& value) { FirstRowCrc8_ = value; }
    inline EmbeddedProto::uint32& mutable_FirstRowCrc8() { return FirstRowCrc8_; }
    inline const EmbeddedProto::uint32& get_FirstRowCrc8() const { return FirstRowCrc8_; }
    inline EmbeddedProto::uint32::FIELD_TYPE FirstRowCrc8() const { return FirstRowCrc8_.get(); }

    inline void clear_SecondRowCrc8() { SecondRowCrc8_.clear(); }
    inline void set_SecondRowCrc8(const EmbeddedProto::uint32& value) { SecondRowCrc8_ = value; }
    inline void set_SecondRowCrc8(const EmbeddedProto::uint32&& value) { SecondRowCrc8_ = value; }
    inline EmbeddedProto::uint32& mutable_SecondRowCrc8() { return SecondRowCrc8_; }
    inline const EmbeddedProto::uint32& get_SecondRowCrc8() const { return SecondRowCrc8_; }
    inline EmbeddedProto::uint32::FIELD_TYPE SecondRowCrc8() const { return SecondRowCrc8_.get(); }

    inline void clear_Rank() { Rank_.clear(); }
    inline void set_Rank(const EmbeddedProto::uint32& value) { Rank_ = value; }
    inline void set_Rank(const EmbeddedProto::uint32&& value) { Rank_ = value; }
    inline EmbeddedProto::uint32& mutable_Rank() { return Rank_; }
    inline const EmbeddedProto::uint32& get_Rank() const { return Rank_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Rank() const { return Rank_.get(); }

    inline void clear_ReceivedFragments() { ReceivedFragments_.clear(); }
    inline void set_ReceivedFragments(const EmbeddedProto::uint32& value) { ReceivedFragments_ = value; }
    inline void set_ReceivedFragments(const EmbeddedProto::uint32&& value) { ReceivedFragments_ = value; }
    inline EmbeddedProto::uint32& mutable_ReceivedFragments() { return ReceivedFragments_; }
    inline const EmbeddedProto::uint32& get_ReceivedFragments() const { return ReceivedFragments_; }
    inline EmbeddedProto::uint32::FIELD_TYPE ReceivedFragments() const { return ReceivedFragments_.get(); }

    inline void clear_CurrentGenerationIndex() { CurrentGenerationIndex_.clear(); }
    inline void set_CurrentGenerationIndex(const EmbeddedProto::uint32& value) { CurrentGenerationIndex_ = value; }
    inline void set_CurrentGenerationIndex(const EmbeddedProto::uint32&& value) { CurrentGenerationIndex_ = value; }
    inline EmbeddedProto::uint32& mutable_CurrentGenerationIndex() { return CurrentGenerationIndex_; }
    inline const EmbeddedProto::uint32& get_CurrentGenerationIndex() const { return CurrentGenerationIndex_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CurrentGenerationIndex() const { return CurrentGenerationIndex_.get(); }

    inline void clear_IsRunning() { IsRunning_.clear(); }
    inline void set_IsRunning(const EmbeddedProto::boolean& value) { IsRunning_ = value; }
    inline void set_IsRunning(const EmbeddedProto::boolean&& value) { IsRunning_ = value; }
    inline EmbeddedProto::boolean& mutable_IsRunning() { return IsRunning_; }
    inline const EmbeddedProto::boolean& get_IsRunning() const { return IsRunning_; }
    inline EmbeddedProto::boolean::FIELD_TYPE IsRunning() const { return IsRunning_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != MatrixCrc8_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MatrixCrc8_.serialize_with_id(static_cast<uint32_t>(id::MATRIXCRC8), buffer, false);
      }

      if((0U != FirstRowCrc8_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FirstRowCrc8_.serialize_with_id(static_cast<uint32_t>(id::FIRSTROWCRC8), buffer, false);
      }

      if((0U != SecondRowCrc8_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SecondRowCrc8_.serialize_with_id(static_cast<uint32_t>(id::SECONDROWCRC8), buffer, false);
      }

      if((0U != Rank_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Rank_.serialize_with_id(static_cast<uint32_t>(id::RANK), buffer, false);
      }

      if((0U != ReceivedFragments_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = ReceivedFragments_.serialize_with_id(static_cast<uint32_t>(id::RECEIVEDFRAGMENTS), buffer, false);
      }

      if((0U != CurrentGenerationIndex_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentGenerationIndex_.serialize_with_id(static_cast<uint32_t>(id::CURRENTGENERATIONINDEX), buffer, false);
      }

      if((false != IsRunning_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = IsRunning_.serialize_with_id(static_cast<uint32_t>(id::ISRUNNING), buffer, false);
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
          case id::MATRIXCRC8:
            return_value = MatrixCrc8_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FIRSTROWCRC8:
            return_value = FirstRowCrc8_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SECONDROWCRC8:
            return_value = SecondRowCrc8_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RANK:
            return_value = Rank_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RECEIVEDFRAGMENTS:
            return_value = ReceivedFragments_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTGENERATIONINDEX:
            return_value = CurrentGenerationIndex_.deserialize_check_type(buffer, wire_type);
            break;

          case id::ISRUNNING:
            return_value = IsRunning_.deserialize_check_type(buffer, wire_type);
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
      clear_MatrixCrc8();
      clear_FirstRowCrc8();
      clear_SecondRowCrc8();
      clear_Rank();
      clear_ReceivedFragments();
      clear_CurrentGenerationIndex();
      clear_IsRunning();

    }

    private:


      EmbeddedProto::uint32 MatrixCrc8_ = 0U;
      EmbeddedProto::uint32 FirstRowCrc8_ = 0U;
      EmbeddedProto::uint32 SecondRowCrc8_ = 0U;
      EmbeddedProto::uint32 Rank_ = 0U;
      EmbeddedProto::uint32 ReceivedFragments_ = 0U;
      EmbeddedProto::uint32 CurrentGenerationIndex_ = 0U;
      EmbeddedProto::boolean IsRunning_ = false;

};

#endif // SHARED_EXPERIMENT_CONFIG_H