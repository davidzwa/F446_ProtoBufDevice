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
#ifndef DEVICE_MESSAGES_H
#define DEVICE_MESSAGES_H

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
#include <shared/firmware.h>


template<uint32_t Payload_LENGTH>
class LoraMeasurement final: public ::EmbeddedProto::MessageInterface
{
  public:
    LoraMeasurement() = default;
    LoraMeasurement(const LoraMeasurement& rhs )
    {
      set_Size(rhs.get_Size());
      set_Rssi(rhs.get_Rssi());
      set_Snr(rhs.get_Snr());
      set_SequenceNumber(rhs.get_SequenceNumber());
      set_IsMeasurementFragment(rhs.get_IsMeasurementFragment());
      set_Success(rhs.get_Success());
      set_Payload(rhs.get_Payload());
    }

    LoraMeasurement(const LoraMeasurement&& rhs ) noexcept
    {
      set_Size(rhs.get_Size());
      set_Rssi(rhs.get_Rssi());
      set_Snr(rhs.get_Snr());
      set_SequenceNumber(rhs.get_SequenceNumber());
      set_IsMeasurementFragment(rhs.get_IsMeasurementFragment());
      set_Success(rhs.get_Success());
      set_Payload(rhs.get_Payload());
    }

    ~LoraMeasurement() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SIZE = 1,
      RSSI = 2,
      SNR = 3,
      SEQUENCENUMBER = 4,
      ISMEASUREMENTFRAGMENT = 5,
      SUCCESS = 6,
      PAYLOAD = 7
    };

    LoraMeasurement& operator=(const LoraMeasurement& rhs)
    {
      set_Size(rhs.get_Size());
      set_Rssi(rhs.get_Rssi());
      set_Snr(rhs.get_Snr());
      set_SequenceNumber(rhs.get_SequenceNumber());
      set_IsMeasurementFragment(rhs.get_IsMeasurementFragment());
      set_Success(rhs.get_Success());
      set_Payload(rhs.get_Payload());
      return *this;
    }

    LoraMeasurement& operator=(const LoraMeasurement&& rhs) noexcept
    {
      set_Size(rhs.get_Size());
      set_Rssi(rhs.get_Rssi());
      set_Snr(rhs.get_Snr());
      set_SequenceNumber(rhs.get_SequenceNumber());
      set_IsMeasurementFragment(rhs.get_IsMeasurementFragment());
      set_Success(rhs.get_Success());
      set_Payload(rhs.get_Payload());
      return *this;
    }

    inline void clear_Size() { Size_.clear(); }
    inline void set_Size(const EmbeddedProto::uint32& value) { Size_ = value; }
    inline void set_Size(const EmbeddedProto::uint32&& value) { Size_ = value; }
    inline EmbeddedProto::uint32& mutable_Size() { return Size_; }
    inline const EmbeddedProto::uint32& get_Size() const { return Size_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Size() const { return Size_.get(); }

    inline void clear_Rssi() { Rssi_.clear(); }
    inline void set_Rssi(const EmbeddedProto::int32& value) { Rssi_ = value; }
    inline void set_Rssi(const EmbeddedProto::int32&& value) { Rssi_ = value; }
    inline EmbeddedProto::int32& mutable_Rssi() { return Rssi_; }
    inline const EmbeddedProto::int32& get_Rssi() const { return Rssi_; }
    inline EmbeddedProto::int32::FIELD_TYPE Rssi() const { return Rssi_.get(); }

    inline void clear_Snr() { Snr_.clear(); }
    inline void set_Snr(const EmbeddedProto::int32& value) { Snr_ = value; }
    inline void set_Snr(const EmbeddedProto::int32&& value) { Snr_ = value; }
    inline EmbeddedProto::int32& mutable_Snr() { return Snr_; }
    inline const EmbeddedProto::int32& get_Snr() const { return Snr_; }
    inline EmbeddedProto::int32::FIELD_TYPE Snr() const { return Snr_.get(); }

    inline void clear_SequenceNumber() { SequenceNumber_.clear(); }
    inline void set_SequenceNumber(const EmbeddedProto::uint32& value) { SequenceNumber_ = value; }
    inline void set_SequenceNumber(const EmbeddedProto::uint32&& value) { SequenceNumber_ = value; }
    inline EmbeddedProto::uint32& mutable_SequenceNumber() { return SequenceNumber_; }
    inline const EmbeddedProto::uint32& get_SequenceNumber() const { return SequenceNumber_; }
    inline EmbeddedProto::uint32::FIELD_TYPE SequenceNumber() const { return SequenceNumber_.get(); }

    inline bool has_IsMeasurementFragment() const
    {
      return 0 != (presence::mask(presence::fields::ISMEASUREMENTFRAGMENT) & presence_[presence::index(presence::fields::ISMEASUREMENTFRAGMENT)]);
    }
    inline void clear_IsMeasurementFragment()
    {
      presence_[presence::index(presence::fields::ISMEASUREMENTFRAGMENT)] &= ~(presence::mask(presence::fields::ISMEASUREMENTFRAGMENT));
      IsMeasurementFragment_.clear();
    }
    inline void set_IsMeasurementFragment(const EmbeddedProto::boolean& value)
    {
      presence_[presence::index(presence::fields::ISMEASUREMENTFRAGMENT)] |= presence::mask(presence::fields::ISMEASUREMENTFRAGMENT);
      IsMeasurementFragment_ = value;
    }
    inline void set_IsMeasurementFragment(const EmbeddedProto::boolean&& value)
    {
      presence_[presence::index(presence::fields::ISMEASUREMENTFRAGMENT)] |= presence::mask(presence::fields::ISMEASUREMENTFRAGMENT);
      IsMeasurementFragment_ = value;
    }
    inline EmbeddedProto::boolean& mutable_IsMeasurementFragment()
    {
      presence_[presence::index(presence::fields::ISMEASUREMENTFRAGMENT)] |= presence::mask(presence::fields::ISMEASUREMENTFRAGMENT);
      return IsMeasurementFragment_;
    }
    inline const EmbeddedProto::boolean& get_IsMeasurementFragment() const { return IsMeasurementFragment_; }
    inline EmbeddedProto::boolean::FIELD_TYPE IsMeasurementFragment() const { return IsMeasurementFragment_.get(); }

    inline void clear_Success() { Success_.clear(); }
    inline void set_Success(const EmbeddedProto::boolean& value) { Success_ = value; }
    inline void set_Success(const EmbeddedProto::boolean&& value) { Success_ = value; }
    inline EmbeddedProto::boolean& mutable_Success() { return Success_; }
    inline const EmbeddedProto::boolean& get_Success() const { return Success_; }
    inline EmbeddedProto::boolean::FIELD_TYPE Success() const { return Success_.get(); }

    inline void clear_Payload() { Payload_.clear(); }
    inline ::EmbeddedProto::FieldBytes<Payload_LENGTH>& mutable_Payload() { return Payload_; }
    inline void set_Payload(const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& rhs) { Payload_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& get_Payload() const { return Payload_; }
    inline const uint8_t* Payload() const { return Payload_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != Size_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Size_.serialize_with_id(static_cast<uint32_t>(id::SIZE), buffer, false);
      }

      if((0 != Rssi_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Rssi_.serialize_with_id(static_cast<uint32_t>(id::RSSI), buffer, false);
      }

      if((0 != Snr_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Snr_.serialize_with_id(static_cast<uint32_t>(id::SNR), buffer, false);
      }

      if((0U != SequenceNumber_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SequenceNumber_.serialize_with_id(static_cast<uint32_t>(id::SEQUENCENUMBER), buffer, false);
      }

      if(has_IsMeasurementFragment() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = IsMeasurementFragment_.serialize_with_id(static_cast<uint32_t>(id::ISMEASUREMENTFRAGMENT), buffer, true);
      }

      if((false != Success_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Success_.serialize_with_id(static_cast<uint32_t>(id::SUCCESS), buffer, false);
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
          case id::SIZE:
            return_value = Size_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RSSI:
            return_value = Rssi_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SNR:
            return_value = Snr_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SEQUENCENUMBER:
            return_value = SequenceNumber_.deserialize_check_type(buffer, wire_type);
            break;

          case id::ISMEASUREMENTFRAGMENT:
            presence_[presence::index(presence::fields::ISMEASUREMENTFRAGMENT)] |= presence::mask(presence::fields::ISMEASUREMENTFRAGMENT);
            return_value = IsMeasurementFragment_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SUCCESS:
            return_value = Success_.deserialize_check_type(buffer, wire_type);
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
      clear_Size();
      clear_Rssi();
      clear_Snr();
      clear_SequenceNumber();
      clear_IsMeasurementFragment();
      clear_Success();
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
          ISMEASUREMENTFRAGMENT
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

      EmbeddedProto::uint32 Size_ = 0U;
      EmbeddedProto::int32 Rssi_ = 0;
      EmbeddedProto::int32 Snr_ = 0;
      EmbeddedProto::uint32 SequenceNumber_ = 0U;
      EmbeddedProto::boolean IsMeasurementFragment_ = false;
      EmbeddedProto::boolean Success_ = false;
      ::EmbeddedProto::FieldBytes<Payload_LENGTH> Payload_;

};

template<uint32_t AppName_LENGTH>
class BootMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    BootMessage() = default;
    BootMessage(const BootMessage& rhs )
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_AppName(rhs.get_AppName());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
    }

    BootMessage(const BootMessage&& rhs ) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_AppName(rhs.get_AppName());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
    }

    ~BootMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      DEVICEIDENTIFIER = 1,
      FIRMWAREVERSION = 2,
      APPNAME = 3,
      MEASUREMENTCOUNT = 4,
      MEASUREMENTSDISABLED = 5
    };

    BootMessage& operator=(const BootMessage& rhs)
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_AppName(rhs.get_AppName());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      return *this;
    }

    BootMessage& operator=(const BootMessage&& rhs) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_AppName(rhs.get_AppName());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      return *this;
    }

    inline void clear_DeviceIdentifier() { DeviceIdentifier_.clear(); }
    inline void set_DeviceIdentifier(const DeviceId& value) { DeviceIdentifier_ = value; }
    inline void set_DeviceIdentifier(const DeviceId&& value) { DeviceIdentifier_ = value; }
    inline DeviceId& mutable_DeviceIdentifier() { return DeviceIdentifier_; }
    inline const DeviceId& get_DeviceIdentifier() const { return DeviceIdentifier_; }
    inline const DeviceId& DeviceIdentifier() const { return DeviceIdentifier_; }

    inline void clear_FirmwareVersion() { FirmwareVersion_.clear(); }
    inline void set_FirmwareVersion(const Version& value) { FirmwareVersion_ = value; }
    inline void set_FirmwareVersion(const Version&& value) { FirmwareVersion_ = value; }
    inline Version& mutable_FirmwareVersion() { return FirmwareVersion_; }
    inline const Version& get_FirmwareVersion() const { return FirmwareVersion_; }
    inline const Version& FirmwareVersion() const { return FirmwareVersion_; }

    inline void clear_AppName() { AppName_.clear(); }
    inline ::EmbeddedProto::FieldString<AppName_LENGTH>& mutable_AppName() { return AppName_; }
    inline void set_AppName(const ::EmbeddedProto::FieldString<AppName_LENGTH>& rhs) { AppName_.set(rhs); }
    inline const ::EmbeddedProto::FieldString<AppName_LENGTH>& get_AppName() const { return AppName_; }
    inline const char* AppName() const { return AppName_.get_const(); }

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


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = DeviceIdentifier_.serialize_with_id(static_cast<uint32_t>(id::DEVICEIDENTIFIER), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = FirmwareVersion_.serialize_with_id(static_cast<uint32_t>(id::FIRMWAREVERSION), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = AppName_.serialize_with_id(static_cast<uint32_t>(id::APPNAME), buffer, false);
      }

      if((0U != MeasurementCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MeasurementCount_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTCOUNT), buffer, false);
      }

      if((false != MeasurementsDisabled_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MeasurementsDisabled_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTSDISABLED), buffer, false);
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
          case id::DEVICEIDENTIFIER:
            return_value = DeviceIdentifier_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FIRMWAREVERSION:
            return_value = FirmwareVersion_.deserialize_check_type(buffer, wire_type);
            break;

          case id::APPNAME:
            return_value = AppName_.deserialize_check_type(buffer, wire_type);
            break;

          case id::MEASUREMENTCOUNT:
            return_value = MeasurementCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::MEASUREMENTSDISABLED:
            return_value = MeasurementsDisabled_.deserialize_check_type(buffer, wire_type);
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
      clear_DeviceIdentifier();
      clear_FirmwareVersion();
      clear_AppName();
      clear_MeasurementCount();
      clear_MeasurementsDisabled();

    }

    private:


      DeviceId DeviceIdentifier_;
      Version FirmwareVersion_;
      ::EmbeddedProto::FieldString<AppName_LENGTH> AppName_;
      EmbeddedProto::uint32 MeasurementCount_ = 0U;
      EmbeddedProto::boolean MeasurementsDisabled_ = false;

};

class AckMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    AckMessage() = default;
    AckMessage(const AckMessage& rhs )
    {
      set_Code(rhs.get_Code());
    }

    AckMessage(const AckMessage&& rhs ) noexcept
    {
      set_Code(rhs.get_Code());
    }

    ~AckMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      CODE = 1
    };

    AckMessage& operator=(const AckMessage& rhs)
    {
      set_Code(rhs.get_Code());
      return *this;
    }

    AckMessage& operator=(const AckMessage&& rhs) noexcept
    {
      set_Code(rhs.get_Code());
      return *this;
    }

    inline void clear_Code() { Code_.clear(); }
    inline void set_Code(const EmbeddedProto::uint32& value) { Code_ = value; }
    inline void set_Code(const EmbeddedProto::uint32&& value) { Code_ = value; }
    inline EmbeddedProto::uint32& mutable_Code() { return Code_; }
    inline const EmbeddedProto::uint32& get_Code() const { return Code_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Code() const { return Code_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != Code_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Code_.serialize_with_id(static_cast<uint32_t>(id::CODE), buffer, false);
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
          case id::CODE:
            return_value = Code_.deserialize_check_type(buffer, wire_type);
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
      clear_Code();

    }

    private:


      EmbeddedProto::uint32 Code_ = 0U;

};

template<uint32_t payload_LENGTH>
class DebugMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    DebugMessage() = default;
    DebugMessage(const DebugMessage& rhs )
    {
      set_payload(rhs.get_payload());
    }

    DebugMessage(const DebugMessage&& rhs ) noexcept
    {
      set_payload(rhs.get_payload());
    }

    ~DebugMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      PAYLOAD = 1
    };

    DebugMessage& operator=(const DebugMessage& rhs)
    {
      set_payload(rhs.get_payload());
      return *this;
    }

    DebugMessage& operator=(const DebugMessage&& rhs) noexcept
    {
      set_payload(rhs.get_payload());
      return *this;
    }

    inline void clear_payload() { payload_.clear(); }
    inline ::EmbeddedProto::FieldBytes<payload_LENGTH>& mutable_payload() { return payload_; }
    inline void set_payload(const ::EmbeddedProto::FieldBytes<payload_LENGTH>& rhs) { payload_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<payload_LENGTH>& get_payload() const { return payload_; }
    inline const uint8_t* payload() const { return payload_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = payload_.serialize_with_id(static_cast<uint32_t>(id::PAYLOAD), buffer, false);
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
          case id::PAYLOAD:
            return_value = payload_.deserialize_check_type(buffer, wire_type);
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
      clear_payload();

    }

    private:


      ::EmbeddedProto::FieldBytes<payload_LENGTH> payload_;

};

template<uint32_t bootMessage_AppName_LENGTH, 
uint32_t loraMeasurement_Payload_LENGTH, 
uint32_t debugMessage_payload_LENGTH>
class UartResponse final: public ::EmbeddedProto::MessageInterface
{
  public:
    UartResponse() = default;
    UartResponse(const UartResponse& rhs )
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::ACKMESSAGE:
          set_ackMessage(rhs.get_ackMessage());
          break;

        case id::LORAMEASUREMENT:
          set_loraMeasurement(rhs.get_loraMeasurement());
          break;

        case id::DEBUGMESSAGE:
          set_debugMessage(rhs.get_debugMessage());
          break;

        default:
          break;
      }

    }

    UartResponse(const UartResponse&& rhs ) noexcept
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::ACKMESSAGE:
          set_ackMessage(rhs.get_ackMessage());
          break;

        case id::LORAMEASUREMENT:
          set_loraMeasurement(rhs.get_loraMeasurement());
          break;

        case id::DEBUGMESSAGE:
          set_debugMessage(rhs.get_debugMessage());
          break;

        default:
          break;
      }

    }

    ~UartResponse() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      BOOTMESSAGE = 1,
      ACKMESSAGE = 2,
      LORAMEASUREMENT = 3,
      DEBUGMESSAGE = 4
    };

    UartResponse& operator=(const UartResponse& rhs)
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::ACKMESSAGE:
          set_ackMessage(rhs.get_ackMessage());
          break;

        case id::LORAMEASUREMENT:
          set_loraMeasurement(rhs.get_loraMeasurement());
          break;

        case id::DEBUGMESSAGE:
          set_debugMessage(rhs.get_debugMessage());
          break;

        default:
          break;
      }

      return *this;
    }

    UartResponse& operator=(const UartResponse&& rhs) noexcept
    {
      if(rhs.get_which_Body() != which_Body_)
      {
        // First delete the old object in the oneof.
        clear_Body();
      }

      switch(rhs.get_which_Body())
      {
        case id::BOOTMESSAGE:
          set_bootMessage(rhs.get_bootMessage());
          break;

        case id::ACKMESSAGE:
          set_ackMessage(rhs.get_ackMessage());
          break;

        case id::LORAMEASUREMENT:
          set_loraMeasurement(rhs.get_loraMeasurement());
          break;

        case id::DEBUGMESSAGE:
          set_debugMessage(rhs.get_debugMessage());
          break;

        default:
          break;
      }

      return *this;
    }

    id get_which_Body() const { return which_Body_; }

    inline bool has_bootMessage() const
    {
      return id::BOOTMESSAGE == which_Body_;
    }
    inline void clear_bootMessage()
    {
      if(id::BOOTMESSAGE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.bootMessage_.~BootMessage<bootMessage_AppName_LENGTH>();
      }
    }
    inline void set_bootMessage(const BootMessage<bootMessage_AppName_LENGTH>& value)
    {
      if(id::BOOTMESSAGE != which_Body_)
      {
        init_Body(id::BOOTMESSAGE);
      }
      Body_.bootMessage_ = value;
    }
    inline void set_bootMessage(const BootMessage<bootMessage_AppName_LENGTH>&& value)
    {
      if(id::BOOTMESSAGE != which_Body_)
      {
        init_Body(id::BOOTMESSAGE);
      }
      Body_.bootMessage_ = value;
    }
    inline BootMessage<bootMessage_AppName_LENGTH>& mutable_bootMessage()
    {
      if(id::BOOTMESSAGE != which_Body_)
      {
        init_Body(id::BOOTMESSAGE);
      }
      return Body_.bootMessage_;
    }
    inline const BootMessage<bootMessage_AppName_LENGTH>& get_bootMessage() const { return Body_.bootMessage_; }
    inline const BootMessage<bootMessage_AppName_LENGTH>& bootMessage() const { return Body_.bootMessage_; }

    inline bool has_ackMessage() const
    {
      return id::ACKMESSAGE == which_Body_;
    }
    inline void clear_ackMessage()
    {
      if(id::ACKMESSAGE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.ackMessage_.~AckMessage();
      }
    }
    inline void set_ackMessage(const AckMessage& value)
    {
      if(id::ACKMESSAGE != which_Body_)
      {
        init_Body(id::ACKMESSAGE);
      }
      Body_.ackMessage_ = value;
    }
    inline void set_ackMessage(const AckMessage&& value)
    {
      if(id::ACKMESSAGE != which_Body_)
      {
        init_Body(id::ACKMESSAGE);
      }
      Body_.ackMessage_ = value;
    }
    inline AckMessage& mutable_ackMessage()
    {
      if(id::ACKMESSAGE != which_Body_)
      {
        init_Body(id::ACKMESSAGE);
      }
      return Body_.ackMessage_;
    }
    inline const AckMessage& get_ackMessage() const { return Body_.ackMessage_; }
    inline const AckMessage& ackMessage() const { return Body_.ackMessage_; }

    inline bool has_loraMeasurement() const
    {
      return id::LORAMEASUREMENT == which_Body_;
    }
    inline void clear_loraMeasurement()
    {
      if(id::LORAMEASUREMENT == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.loraMeasurement_.~LoraMeasurement<loraMeasurement_Payload_LENGTH>();
      }
    }
    inline void set_loraMeasurement(const LoraMeasurement<loraMeasurement_Payload_LENGTH>& value)
    {
      if(id::LORAMEASUREMENT != which_Body_)
      {
        init_Body(id::LORAMEASUREMENT);
      }
      Body_.loraMeasurement_ = value;
    }
    inline void set_loraMeasurement(const LoraMeasurement<loraMeasurement_Payload_LENGTH>&& value)
    {
      if(id::LORAMEASUREMENT != which_Body_)
      {
        init_Body(id::LORAMEASUREMENT);
      }
      Body_.loraMeasurement_ = value;
    }
    inline LoraMeasurement<loraMeasurement_Payload_LENGTH>& mutable_loraMeasurement()
    {
      if(id::LORAMEASUREMENT != which_Body_)
      {
        init_Body(id::LORAMEASUREMENT);
      }
      return Body_.loraMeasurement_;
    }
    inline const LoraMeasurement<loraMeasurement_Payload_LENGTH>& get_loraMeasurement() const { return Body_.loraMeasurement_; }
    inline const LoraMeasurement<loraMeasurement_Payload_LENGTH>& loraMeasurement() const { return Body_.loraMeasurement_; }

    inline bool has_debugMessage() const
    {
      return id::DEBUGMESSAGE == which_Body_;
    }
    inline void clear_debugMessage()
    {
      if(id::DEBUGMESSAGE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.debugMessage_.~DebugMessage<debugMessage_payload_LENGTH>();
      }
    }
    inline void set_debugMessage(const DebugMessage<debugMessage_payload_LENGTH>& value)
    {
      if(id::DEBUGMESSAGE != which_Body_)
      {
        init_Body(id::DEBUGMESSAGE);
      }
      Body_.debugMessage_ = value;
    }
    inline void set_debugMessage(const DebugMessage<debugMessage_payload_LENGTH>&& value)
    {
      if(id::DEBUGMESSAGE != which_Body_)
      {
        init_Body(id::DEBUGMESSAGE);
      }
      Body_.debugMessage_ = value;
    }
    inline DebugMessage<debugMessage_payload_LENGTH>& mutable_debugMessage()
    {
      if(id::DEBUGMESSAGE != which_Body_)
      {
        init_Body(id::DEBUGMESSAGE);
      }
      return Body_.debugMessage_;
    }
    inline const DebugMessage<debugMessage_payload_LENGTH>& get_debugMessage() const { return Body_.debugMessage_; }
    inline const DebugMessage<debugMessage_payload_LENGTH>& debugMessage() const { return Body_.debugMessage_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      switch(which_Body_)
      {
        case id::BOOTMESSAGE:
          if(has_bootMessage() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.bootMessage_.serialize_with_id(static_cast<uint32_t>(id::BOOTMESSAGE), buffer, true);
          }
          break;

        case id::ACKMESSAGE:
          if(has_ackMessage() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.ackMessage_.serialize_with_id(static_cast<uint32_t>(id::ACKMESSAGE), buffer, true);
          }
          break;

        case id::LORAMEASUREMENT:
          if(has_loraMeasurement() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.loraMeasurement_.serialize_with_id(static_cast<uint32_t>(id::LORAMEASUREMENT), buffer, true);
          }
          break;

        case id::DEBUGMESSAGE:
          if(has_debugMessage() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.debugMessage_.serialize_with_id(static_cast<uint32_t>(id::DEBUGMESSAGE), buffer, true);
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
          case id::BOOTMESSAGE:
            return_value = deserialize_Body(id::BOOTMESSAGE, Body_.bootMessage_, buffer, wire_type);

            break;

          case id::ACKMESSAGE:
            return_value = deserialize_Body(id::ACKMESSAGE, Body_.ackMessage_, buffer, wire_type);

            break;

          case id::LORAMEASUREMENT:
            return_value = deserialize_Body(id::LORAMEASUREMENT, Body_.loraMeasurement_, buffer, wire_type);

            break;

          case id::DEBUGMESSAGE:
            return_value = deserialize_Body(id::DEBUGMESSAGE, Body_.debugMessage_, buffer, wire_type);

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
        BootMessage<bootMessage_AppName_LENGTH> bootMessage_;
        AckMessage ackMessage_;
        LoraMeasurement<loraMeasurement_Payload_LENGTH> loraMeasurement_;
        DebugMessage<debugMessage_payload_LENGTH> debugMessage_;
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
          case id::BOOTMESSAGE:
            new(&Body_.bootMessage_) BootMessage<bootMessage_AppName_LENGTH>;
            which_Body_ = id::BOOTMESSAGE;
            break;

          case id::ACKMESSAGE:
            new(&Body_.ackMessage_) AckMessage;
            which_Body_ = id::ACKMESSAGE;
            break;

          case id::LORAMEASUREMENT:
            new(&Body_.loraMeasurement_) LoraMeasurement<loraMeasurement_Payload_LENGTH>;
            which_Body_ = id::LORAMEASUREMENT;
            break;

          case id::DEBUGMESSAGE:
            new(&Body_.debugMessage_) DebugMessage<debugMessage_payload_LENGTH>;
            which_Body_ = id::DEBUGMESSAGE;
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
          case id::BOOTMESSAGE:
            Body_.bootMessage_.~BootMessage<bootMessage_AppName_LENGTH>(); // NOSONAR Unions require this.
            break;
          case id::ACKMESSAGE:
            Body_.ackMessage_.~AckMessage(); // NOSONAR Unions require this.
            break;
          case id::LORAMEASUREMENT:
            Body_.loraMeasurement_.~LoraMeasurement<loraMeasurement_Payload_LENGTH>(); // NOSONAR Unions require this.
            break;
          case id::DEBUGMESSAGE:
            Body_.debugMessage_.~DebugMessage<debugMessage_payload_LENGTH>(); // NOSONAR Unions require this.
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

#endif // DEVICE_MESSAGES_H