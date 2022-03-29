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
#ifndef SHARED_FIRMWARE_H
#define SHARED_FIRMWARE_H

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


class Version final: public ::EmbeddedProto::MessageInterface
{
  public:
    Version() = default;
    Version(const Version& rhs )
    {
      set_Major(rhs.get_Major());
      set_Minor(rhs.get_Minor());
      set_Patch(rhs.get_Patch());
      set_Revision(rhs.get_Revision());
    }

    Version(const Version&& rhs ) noexcept
    {
      set_Major(rhs.get_Major());
      set_Minor(rhs.get_Minor());
      set_Patch(rhs.get_Patch());
      set_Revision(rhs.get_Revision());
    }

    ~Version() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MAJOR = 1,
      MINOR = 2,
      PATCH = 3,
      REVISION = 4
    };

    Version& operator=(const Version& rhs)
    {
      set_Major(rhs.get_Major());
      set_Minor(rhs.get_Minor());
      set_Patch(rhs.get_Patch());
      set_Revision(rhs.get_Revision());
      return *this;
    }

    Version& operator=(const Version&& rhs) noexcept
    {
      set_Major(rhs.get_Major());
      set_Minor(rhs.get_Minor());
      set_Patch(rhs.get_Patch());
      set_Revision(rhs.get_Revision());
      return *this;
    }

    inline void clear_Major() { Major_.clear(); }
    inline void set_Major(const EmbeddedProto::uint32& value) { Major_ = value; }
    inline void set_Major(const EmbeddedProto::uint32&& value) { Major_ = value; }
    inline EmbeddedProto::uint32& mutable_Major() { return Major_; }
    inline const EmbeddedProto::uint32& get_Major() const { return Major_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Major() const { return Major_.get(); }

    inline void clear_Minor() { Minor_.clear(); }
    inline void set_Minor(const EmbeddedProto::uint32& value) { Minor_ = value; }
    inline void set_Minor(const EmbeddedProto::uint32&& value) { Minor_ = value; }
    inline EmbeddedProto::uint32& mutable_Minor() { return Minor_; }
    inline const EmbeddedProto::uint32& get_Minor() const { return Minor_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Minor() const { return Minor_.get(); }

    inline void clear_Patch() { Patch_.clear(); }
    inline void set_Patch(const EmbeddedProto::uint32& value) { Patch_ = value; }
    inline void set_Patch(const EmbeddedProto::uint32&& value) { Patch_ = value; }
    inline EmbeddedProto::uint32& mutable_Patch() { return Patch_; }
    inline const EmbeddedProto::uint32& get_Patch() const { return Patch_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Patch() const { return Patch_.get(); }

    inline void clear_Revision() { Revision_.clear(); }
    inline void set_Revision(const EmbeddedProto::uint32& value) { Revision_ = value; }
    inline void set_Revision(const EmbeddedProto::uint32&& value) { Revision_ = value; }
    inline EmbeddedProto::uint32& mutable_Revision() { return Revision_; }
    inline const EmbeddedProto::uint32& get_Revision() const { return Revision_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Revision() const { return Revision_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != Major_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Major_.serialize_with_id(static_cast<uint32_t>(id::MAJOR), buffer, false);
      }

      if((0U != Minor_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Minor_.serialize_with_id(static_cast<uint32_t>(id::MINOR), buffer, false);
      }

      if((0U != Patch_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Patch_.serialize_with_id(static_cast<uint32_t>(id::PATCH), buffer, false);
      }

      if((0U != Revision_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Revision_.serialize_with_id(static_cast<uint32_t>(id::REVISION), buffer, false);
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
          case id::MAJOR:
            return_value = Major_.deserialize_check_type(buffer, wire_type);
            break;

          case id::MINOR:
            return_value = Minor_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PATCH:
            return_value = Patch_.deserialize_check_type(buffer, wire_type);
            break;

          case id::REVISION:
            return_value = Revision_.deserialize_check_type(buffer, wire_type);
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
      clear_Major();
      clear_Minor();
      clear_Patch();
      clear_Revision();

    }

    private:


      EmbeddedProto::uint32 Major_ = 0U;
      EmbeddedProto::uint32 Minor_ = 0U;
      EmbeddedProto::uint32 Patch_ = 0U;
      EmbeddedProto::uint32 Revision_ = 0U;

};

class DeviceId final: public ::EmbeddedProto::MessageInterface
{
  public:
    DeviceId() = default;
    DeviceId(const DeviceId& rhs )
    {
      set_Id0(rhs.get_Id0());
      set_Id1(rhs.get_Id1());
      set_Id2(rhs.get_Id2());
    }

    DeviceId(const DeviceId&& rhs ) noexcept
    {
      set_Id0(rhs.get_Id0());
      set_Id1(rhs.get_Id1());
      set_Id2(rhs.get_Id2());
    }

    ~DeviceId() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      ID0 = 1,
      ID1 = 2,
      ID2 = 3
    };

    DeviceId& operator=(const DeviceId& rhs)
    {
      set_Id0(rhs.get_Id0());
      set_Id1(rhs.get_Id1());
      set_Id2(rhs.get_Id2());
      return *this;
    }

    DeviceId& operator=(const DeviceId&& rhs) noexcept
    {
      set_Id0(rhs.get_Id0());
      set_Id1(rhs.get_Id1());
      set_Id2(rhs.get_Id2());
      return *this;
    }

    inline void clear_Id0() { Id0_.clear(); }
    inline void set_Id0(const EmbeddedProto::uint32& value) { Id0_ = value; }
    inline void set_Id0(const EmbeddedProto::uint32&& value) { Id0_ = value; }
    inline EmbeddedProto::uint32& mutable_Id0() { return Id0_; }
    inline const EmbeddedProto::uint32& get_Id0() const { return Id0_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Id0() const { return Id0_.get(); }

    inline void clear_Id1() { Id1_.clear(); }
    inline void set_Id1(const EmbeddedProto::uint32& value) { Id1_ = value; }
    inline void set_Id1(const EmbeddedProto::uint32&& value) { Id1_ = value; }
    inline EmbeddedProto::uint32& mutable_Id1() { return Id1_; }
    inline const EmbeddedProto::uint32& get_Id1() const { return Id1_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Id1() const { return Id1_.get(); }

    inline void clear_Id2() { Id2_.clear(); }
    inline void set_Id2(const EmbeddedProto::uint32& value) { Id2_ = value; }
    inline void set_Id2(const EmbeddedProto::uint32&& value) { Id2_ = value; }
    inline EmbeddedProto::uint32& mutable_Id2() { return Id2_; }
    inline const EmbeddedProto::uint32& get_Id2() const { return Id2_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Id2() const { return Id2_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != Id0_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Id0_.serialize_with_id(static_cast<uint32_t>(id::ID0), buffer, false);
      }

      if((0U != Id1_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Id1_.serialize_with_id(static_cast<uint32_t>(id::ID1), buffer, false);
      }

      if((0U != Id2_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Id2_.serialize_with_id(static_cast<uint32_t>(id::ID2), buffer, false);
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
          case id::ID0:
            return_value = Id0_.deserialize_check_type(buffer, wire_type);
            break;

          case id::ID1:
            return_value = Id1_.deserialize_check_type(buffer, wire_type);
            break;

          case id::ID2:
            return_value = Id2_.deserialize_check_type(buffer, wire_type);
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
      clear_Id0();
      clear_Id1();
      clear_Id2();

    }

    private:


      EmbeddedProto::uint32 Id0_ = 0U;
      EmbeddedProto::uint32 Id1_ = 0U;
      EmbeddedProto::uint32 Id2_ = 0U;

};

class BootMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    BootMessage() = default;
    BootMessage(const BootMessage& rhs )
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
    }

    BootMessage(const BootMessage&& rhs ) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
    }

    ~BootMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      DEVICEIDENTIFIER = 1,
      FIRMWAREVERSION = 2,
      MEASUREMENTCOUNT = 3,
      MEASUREMENTSDISABLED = 4,
      RLNCFLASHSTATE = 5,
      RLNCSESSIONSTATE = 6
    };

    BootMessage& operator=(const BootMessage& rhs)
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
      return *this;
    }

    BootMessage& operator=(const BootMessage&& rhs) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
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

    inline void clear_RlncFlashState() { RlncFlashState_.clear(); }
    inline void set_RlncFlashState(const EmbeddedProto::uint32& value) { RlncFlashState_ = value; }
    inline void set_RlncFlashState(const EmbeddedProto::uint32&& value) { RlncFlashState_ = value; }
    inline EmbeddedProto::uint32& mutable_RlncFlashState() { return RlncFlashState_; }
    inline const EmbeddedProto::uint32& get_RlncFlashState() const { return RlncFlashState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE RlncFlashState() const { return RlncFlashState_.get(); }

    inline void clear_RlncSessionState() { RlncSessionState_.clear(); }
    inline void set_RlncSessionState(const EmbeddedProto::uint32& value) { RlncSessionState_ = value; }
    inline void set_RlncSessionState(const EmbeddedProto::uint32&& value) { RlncSessionState_ = value; }
    inline EmbeddedProto::uint32& mutable_RlncSessionState() { return RlncSessionState_; }
    inline const EmbeddedProto::uint32& get_RlncSessionState() const { return RlncSessionState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE RlncSessionState() const { return RlncSessionState_.get(); }


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

      if((0U != MeasurementCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MeasurementCount_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTCOUNT), buffer, false);
      }

      if((false != MeasurementsDisabled_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MeasurementsDisabled_.serialize_with_id(static_cast<uint32_t>(id::MEASUREMENTSDISABLED), buffer, false);
      }

      if((0U != RlncFlashState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = RlncFlashState_.serialize_with_id(static_cast<uint32_t>(id::RLNCFLASHSTATE), buffer, false);
      }

      if((0U != RlncSessionState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = RlncSessionState_.serialize_with_id(static_cast<uint32_t>(id::RLNCSESSIONSTATE), buffer, false);
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

          case id::MEASUREMENTCOUNT:
            return_value = MeasurementCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::MEASUREMENTSDISABLED:
            return_value = MeasurementsDisabled_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RLNCFLASHSTATE:
            return_value = RlncFlashState_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RLNCSESSIONSTATE:
            return_value = RlncSessionState_.deserialize_check_type(buffer, wire_type);
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
      clear_MeasurementCount();
      clear_MeasurementsDisabled();
      clear_RlncFlashState();
      clear_RlncSessionState();

    }

    private:


      DeviceId DeviceIdentifier_;
      Version FirmwareVersion_;
      EmbeddedProto::uint32 MeasurementCount_ = 0U;
      EmbeddedProto::boolean MeasurementsDisabled_ = false;
      EmbeddedProto::uint32 RlncFlashState_ = 0U;
      EmbeddedProto::uint32 RlncSessionState_ = 0U;

};

class RlncRemoteFlashStartCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncRemoteFlashStartCommand() = default;
    RlncRemoteFlashStartCommand(const RlncRemoteFlashStartCommand& rhs )
    {
      set_transmitConfiguration(rhs.get_transmitConfiguration());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
      set_TimerDelay(rhs.get_TimerDelay());
      set_SetIsMulticast(rhs.get_SetIsMulticast());
      set_DeviceId0(rhs.get_DeviceId0());
    }

    RlncRemoteFlashStartCommand(const RlncRemoteFlashStartCommand&& rhs ) noexcept
    {
      set_transmitConfiguration(rhs.get_transmitConfiguration());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
      set_TimerDelay(rhs.get_TimerDelay());
      set_SetIsMulticast(rhs.get_SetIsMulticast());
      set_DeviceId0(rhs.get_DeviceId0());
    }

    ~RlncRemoteFlashStartCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      TRANSMITCONFIGURATION = 2,
      RECEPTIONRATECONFIG = 3,
      TIMERDELAY = 4,
      SETISMULTICAST = 5,
      DEVICEID0 = 6
    };

    RlncRemoteFlashStartCommand& operator=(const RlncRemoteFlashStartCommand& rhs)
    {
      set_transmitConfiguration(rhs.get_transmitConfiguration());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
      set_TimerDelay(rhs.get_TimerDelay());
      set_SetIsMulticast(rhs.get_SetIsMulticast());
      set_DeviceId0(rhs.get_DeviceId0());
      return *this;
    }

    RlncRemoteFlashStartCommand& operator=(const RlncRemoteFlashStartCommand&& rhs) noexcept
    {
      set_transmitConfiguration(rhs.get_transmitConfiguration());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
      set_TimerDelay(rhs.get_TimerDelay());
      set_SetIsMulticast(rhs.get_SetIsMulticast());
      set_DeviceId0(rhs.get_DeviceId0());
      return *this;
    }

    inline void clear_transmitConfiguration() { transmitConfiguration_.clear(); }
    inline void set_transmitConfiguration(const TransmitConfiguration& value) { transmitConfiguration_ = value; }
    inline void set_transmitConfiguration(const TransmitConfiguration&& value) { transmitConfiguration_ = value; }
    inline TransmitConfiguration& mutable_transmitConfiguration() { return transmitConfiguration_; }
    inline const TransmitConfiguration& get_transmitConfiguration() const { return transmitConfiguration_; }
    inline const TransmitConfiguration& transmitConfiguration() const { return transmitConfiguration_; }

    inline void clear_receptionRateConfig() { receptionRateConfig_.clear(); }
    inline void set_receptionRateConfig(const ReceptionRateConfig& value) { receptionRateConfig_ = value; }
    inline void set_receptionRateConfig(const ReceptionRateConfig&& value) { receptionRateConfig_ = value; }
    inline ReceptionRateConfig& mutable_receptionRateConfig() { return receptionRateConfig_; }
    inline const ReceptionRateConfig& get_receptionRateConfig() const { return receptionRateConfig_; }
    inline const ReceptionRateConfig& receptionRateConfig() const { return receptionRateConfig_; }

    inline void clear_TimerDelay() { TimerDelay_.clear(); }
    inline void set_TimerDelay(const EmbeddedProto::uint32& value) { TimerDelay_ = value; }
    inline void set_TimerDelay(const EmbeddedProto::uint32&& value) { TimerDelay_ = value; }
    inline EmbeddedProto::uint32& mutable_TimerDelay() { return TimerDelay_; }
    inline const EmbeddedProto::uint32& get_TimerDelay() const { return TimerDelay_; }
    inline EmbeddedProto::uint32::FIELD_TYPE TimerDelay() const { return TimerDelay_.get(); }

    inline void clear_SetIsMulticast() { SetIsMulticast_.clear(); }
    inline void set_SetIsMulticast(const EmbeddedProto::boolean& value) { SetIsMulticast_ = value; }
    inline void set_SetIsMulticast(const EmbeddedProto::boolean&& value) { SetIsMulticast_ = value; }
    inline EmbeddedProto::boolean& mutable_SetIsMulticast() { return SetIsMulticast_; }
    inline const EmbeddedProto::boolean& get_SetIsMulticast() const { return SetIsMulticast_; }
    inline EmbeddedProto::boolean::FIELD_TYPE SetIsMulticast() const { return SetIsMulticast_.get(); }

    inline void clear_DeviceId0() { DeviceId0_.clear(); }
    inline void set_DeviceId0(const EmbeddedProto::uint32& value) { DeviceId0_ = value; }
    inline void set_DeviceId0(const EmbeddedProto::uint32&& value) { DeviceId0_ = value; }
    inline EmbeddedProto::uint32& mutable_DeviceId0() { return DeviceId0_; }
    inline const EmbeddedProto::uint32& get_DeviceId0() const { return DeviceId0_; }
    inline EmbeddedProto::uint32::FIELD_TYPE DeviceId0() const { return DeviceId0_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = transmitConfiguration_.serialize_with_id(static_cast<uint32_t>(id::TRANSMITCONFIGURATION), buffer, false);
      }

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = receptionRateConfig_.serialize_with_id(static_cast<uint32_t>(id::RECEPTIONRATECONFIG), buffer, false);
      }

      if((0U != TimerDelay_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = TimerDelay_.serialize_with_id(static_cast<uint32_t>(id::TIMERDELAY), buffer, false);
      }

      if((false != SetIsMulticast_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SetIsMulticast_.serialize_with_id(static_cast<uint32_t>(id::SETISMULTICAST), buffer, false);
      }

      if((0U != DeviceId0_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DeviceId0_.serialize_with_id(static_cast<uint32_t>(id::DEVICEID0), buffer, false);
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
          case id::TRANSMITCONFIGURATION:
            return_value = transmitConfiguration_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RECEPTIONRATECONFIG:
            return_value = receptionRateConfig_.deserialize_check_type(buffer, wire_type);
            break;

          case id::TIMERDELAY:
            return_value = TimerDelay_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SETISMULTICAST:
            return_value = SetIsMulticast_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DEVICEID0:
            return_value = DeviceId0_.deserialize_check_type(buffer, wire_type);
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
      clear_transmitConfiguration();
      clear_receptionRateConfig();
      clear_TimerDelay();
      clear_SetIsMulticast();
      clear_DeviceId0();

    }

    private:


      TransmitConfiguration transmitConfiguration_;
      ReceptionRateConfig receptionRateConfig_;
      EmbeddedProto::uint32 TimerDelay_ = 0U;
      EmbeddedProto::boolean SetIsMulticast_ = false;
      EmbeddedProto::uint32 DeviceId0_ = 0U;

};

class RlncRemoteFlashStopCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncRemoteFlashStopCommand() = default;
    RlncRemoteFlashStopCommand(const RlncRemoteFlashStopCommand& rhs )
    {
    }

    RlncRemoteFlashStopCommand(const RlncRemoteFlashStopCommand&& rhs ) noexcept
    {
    }

    ~RlncRemoteFlashStopCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
    };

    RlncRemoteFlashStopCommand& operator=(const RlncRemoteFlashStopCommand& rhs)
    {
      return *this;
    }

    RlncRemoteFlashStopCommand& operator=(const RlncRemoteFlashStopCommand&& rhs) noexcept
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

class RlncQueryRemoteFlashState final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncQueryRemoteFlashState() = default;
    RlncQueryRemoteFlashState(const RlncQueryRemoteFlashState& rhs )
    {
    }

    RlncQueryRemoteFlashState(const RlncQueryRemoteFlashState&& rhs ) noexcept
    {
    }

    ~RlncQueryRemoteFlashState() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
    };

    RlncQueryRemoteFlashState& operator=(const RlncQueryRemoteFlashState& rhs)
    {
      return *this;
    }

    RlncQueryRemoteFlashState& operator=(const RlncQueryRemoteFlashState&& rhs) noexcept
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

class RlncRemoteFlashResponse final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncRemoteFlashResponse() = default;
    RlncRemoteFlashResponse(const RlncRemoteFlashResponse& rhs )
    {
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
      set_CurrentTxPower(rhs.get_CurrentTxPower());
      set_CurrentTxBandwidth(rhs.get_CurrentTxBandwidth());
      set_CurrentTxDataRate(rhs.get_CurrentTxDataRate());
      set_CurrentTimerDelay(rhs.get_CurrentTimerDelay());
      set_CurrentSetIsMulticast(rhs.get_CurrentSetIsMulticast());
      set_CurrentDeviceId0(rhs.get_CurrentDeviceId0());
    }

    RlncRemoteFlashResponse(const RlncRemoteFlashResponse&& rhs ) noexcept
    {
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
      set_CurrentTxPower(rhs.get_CurrentTxPower());
      set_CurrentTxBandwidth(rhs.get_CurrentTxBandwidth());
      set_CurrentTxDataRate(rhs.get_CurrentTxDataRate());
      set_CurrentTimerDelay(rhs.get_CurrentTimerDelay());
      set_CurrentSetIsMulticast(rhs.get_CurrentSetIsMulticast());
      set_CurrentDeviceId0(rhs.get_CurrentDeviceId0());
    }

    ~RlncRemoteFlashResponse() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      RLNCFLASHSTATE = 1,
      RLNCSESSIONSTATE = 2,
      CURRENTTXPOWER = 3,
      CURRENTTXBANDWIDTH = 4,
      CURRENTTXDATARATE = 5,
      CURRENTTIMERDELAY = 6,
      CURRENTSETISMULTICAST = 7,
      CURRENTDEVICEID0 = 8
    };

    RlncRemoteFlashResponse& operator=(const RlncRemoteFlashResponse& rhs)
    {
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
      set_CurrentTxPower(rhs.get_CurrentTxPower());
      set_CurrentTxBandwidth(rhs.get_CurrentTxBandwidth());
      set_CurrentTxDataRate(rhs.get_CurrentTxDataRate());
      set_CurrentTimerDelay(rhs.get_CurrentTimerDelay());
      set_CurrentSetIsMulticast(rhs.get_CurrentSetIsMulticast());
      set_CurrentDeviceId0(rhs.get_CurrentDeviceId0());
      return *this;
    }

    RlncRemoteFlashResponse& operator=(const RlncRemoteFlashResponse&& rhs) noexcept
    {
      set_RlncFlashState(rhs.get_RlncFlashState());
      set_RlncSessionState(rhs.get_RlncSessionState());
      set_CurrentTxPower(rhs.get_CurrentTxPower());
      set_CurrentTxBandwidth(rhs.get_CurrentTxBandwidth());
      set_CurrentTxDataRate(rhs.get_CurrentTxDataRate());
      set_CurrentTimerDelay(rhs.get_CurrentTimerDelay());
      set_CurrentSetIsMulticast(rhs.get_CurrentSetIsMulticast());
      set_CurrentDeviceId0(rhs.get_CurrentDeviceId0());
      return *this;
    }

    inline void clear_RlncFlashState() { RlncFlashState_.clear(); }
    inline void set_RlncFlashState(const EmbeddedProto::uint32& value) { RlncFlashState_ = value; }
    inline void set_RlncFlashState(const EmbeddedProto::uint32&& value) { RlncFlashState_ = value; }
    inline EmbeddedProto::uint32& mutable_RlncFlashState() { return RlncFlashState_; }
    inline const EmbeddedProto::uint32& get_RlncFlashState() const { return RlncFlashState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE RlncFlashState() const { return RlncFlashState_.get(); }

    inline void clear_RlncSessionState() { RlncSessionState_.clear(); }
    inline void set_RlncSessionState(const EmbeddedProto::uint32& value) { RlncSessionState_ = value; }
    inline void set_RlncSessionState(const EmbeddedProto::uint32&& value) { RlncSessionState_ = value; }
    inline EmbeddedProto::uint32& mutable_RlncSessionState() { return RlncSessionState_; }
    inline const EmbeddedProto::uint32& get_RlncSessionState() const { return RlncSessionState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE RlncSessionState() const { return RlncSessionState_.get(); }

    inline void clear_CurrentTxPower() { CurrentTxPower_.clear(); }
    inline void set_CurrentTxPower(const EmbeddedProto::int32& value) { CurrentTxPower_ = value; }
    inline void set_CurrentTxPower(const EmbeddedProto::int32&& value) { CurrentTxPower_ = value; }
    inline EmbeddedProto::int32& mutable_CurrentTxPower() { return CurrentTxPower_; }
    inline const EmbeddedProto::int32& get_CurrentTxPower() const { return CurrentTxPower_; }
    inline EmbeddedProto::int32::FIELD_TYPE CurrentTxPower() const { return CurrentTxPower_.get(); }

    inline void clear_CurrentTxBandwidth() { CurrentTxBandwidth_.clear(); }
    inline void set_CurrentTxBandwidth(const EmbeddedProto::uint32& value) { CurrentTxBandwidth_ = value; }
    inline void set_CurrentTxBandwidth(const EmbeddedProto::uint32&& value) { CurrentTxBandwidth_ = value; }
    inline EmbeddedProto::uint32& mutable_CurrentTxBandwidth() { return CurrentTxBandwidth_; }
    inline const EmbeddedProto::uint32& get_CurrentTxBandwidth() const { return CurrentTxBandwidth_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CurrentTxBandwidth() const { return CurrentTxBandwidth_.get(); }

    inline void clear_CurrentTxDataRate() { CurrentTxDataRate_.clear(); }
    inline void set_CurrentTxDataRate(const EmbeddedProto::uint32& value) { CurrentTxDataRate_ = value; }
    inline void set_CurrentTxDataRate(const EmbeddedProto::uint32&& value) { CurrentTxDataRate_ = value; }
    inline EmbeddedProto::uint32& mutable_CurrentTxDataRate() { return CurrentTxDataRate_; }
    inline const EmbeddedProto::uint32& get_CurrentTxDataRate() const { return CurrentTxDataRate_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CurrentTxDataRate() const { return CurrentTxDataRate_.get(); }

    inline void clear_CurrentTimerDelay() { CurrentTimerDelay_.clear(); }
    inline void set_CurrentTimerDelay(const EmbeddedProto::uint32& value) { CurrentTimerDelay_ = value; }
    inline void set_CurrentTimerDelay(const EmbeddedProto::uint32&& value) { CurrentTimerDelay_ = value; }
    inline EmbeddedProto::uint32& mutable_CurrentTimerDelay() { return CurrentTimerDelay_; }
    inline const EmbeddedProto::uint32& get_CurrentTimerDelay() const { return CurrentTimerDelay_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CurrentTimerDelay() const { return CurrentTimerDelay_.get(); }

    inline void clear_CurrentSetIsMulticast() { CurrentSetIsMulticast_.clear(); }
    inline void set_CurrentSetIsMulticast(const EmbeddedProto::boolean& value) { CurrentSetIsMulticast_ = value; }
    inline void set_CurrentSetIsMulticast(const EmbeddedProto::boolean&& value) { CurrentSetIsMulticast_ = value; }
    inline EmbeddedProto::boolean& mutable_CurrentSetIsMulticast() { return CurrentSetIsMulticast_; }
    inline const EmbeddedProto::boolean& get_CurrentSetIsMulticast() const { return CurrentSetIsMulticast_; }
    inline EmbeddedProto::boolean::FIELD_TYPE CurrentSetIsMulticast() const { return CurrentSetIsMulticast_.get(); }

    inline void clear_CurrentDeviceId0() { CurrentDeviceId0_.clear(); }
    inline void set_CurrentDeviceId0(const EmbeddedProto::uint32& value) { CurrentDeviceId0_ = value; }
    inline void set_CurrentDeviceId0(const EmbeddedProto::uint32&& value) { CurrentDeviceId0_ = value; }
    inline EmbeddedProto::uint32& mutable_CurrentDeviceId0() { return CurrentDeviceId0_; }
    inline const EmbeddedProto::uint32& get_CurrentDeviceId0() const { return CurrentDeviceId0_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CurrentDeviceId0() const { return CurrentDeviceId0_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != RlncFlashState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = RlncFlashState_.serialize_with_id(static_cast<uint32_t>(id::RLNCFLASHSTATE), buffer, false);
      }

      if((0U != RlncSessionState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = RlncSessionState_.serialize_with_id(static_cast<uint32_t>(id::RLNCSESSIONSTATE), buffer, false);
      }

      if((0 != CurrentTxPower_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentTxPower_.serialize_with_id(static_cast<uint32_t>(id::CURRENTTXPOWER), buffer, false);
      }

      if((0U != CurrentTxBandwidth_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentTxBandwidth_.serialize_with_id(static_cast<uint32_t>(id::CURRENTTXBANDWIDTH), buffer, false);
      }

      if((0U != CurrentTxDataRate_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentTxDataRate_.serialize_with_id(static_cast<uint32_t>(id::CURRENTTXDATARATE), buffer, false);
      }

      if((0U != CurrentTimerDelay_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentTimerDelay_.serialize_with_id(static_cast<uint32_t>(id::CURRENTTIMERDELAY), buffer, false);
      }

      if((false != CurrentSetIsMulticast_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentSetIsMulticast_.serialize_with_id(static_cast<uint32_t>(id::CURRENTSETISMULTICAST), buffer, false);
      }

      if((0U != CurrentDeviceId0_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentDeviceId0_.serialize_with_id(static_cast<uint32_t>(id::CURRENTDEVICEID0), buffer, false);
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
          case id::RLNCFLASHSTATE:
            return_value = RlncFlashState_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RLNCSESSIONSTATE:
            return_value = RlncSessionState_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTTXPOWER:
            return_value = CurrentTxPower_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTTXBANDWIDTH:
            return_value = CurrentTxBandwidth_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTTXDATARATE:
            return_value = CurrentTxDataRate_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTTIMERDELAY:
            return_value = CurrentTimerDelay_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTSETISMULTICAST:
            return_value = CurrentSetIsMulticast_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTDEVICEID0:
            return_value = CurrentDeviceId0_.deserialize_check_type(buffer, wire_type);
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
      clear_RlncFlashState();
      clear_RlncSessionState();
      clear_CurrentTxPower();
      clear_CurrentTxBandwidth();
      clear_CurrentTxDataRate();
      clear_CurrentTimerDelay();
      clear_CurrentSetIsMulticast();
      clear_CurrentDeviceId0();

    }

    private:


      EmbeddedProto::uint32 RlncFlashState_ = 0U;
      EmbeddedProto::uint32 RlncSessionState_ = 0U;
      EmbeddedProto::int32 CurrentTxPower_ = 0;
      EmbeddedProto::uint32 CurrentTxBandwidth_ = 0U;
      EmbeddedProto::uint32 CurrentTxDataRate_ = 0U;
      EmbeddedProto::uint32 CurrentTimerDelay_ = 0U;
      EmbeddedProto::boolean CurrentSetIsMulticast_ = false;
      EmbeddedProto::uint32 CurrentDeviceId0_ = 0U;

};

class RlncInitConfigCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncInitConfigCommand() = default;
    RlncInitConfigCommand(const RlncInitConfigCommand& rhs )
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationRedundancySize(rhs.get_GenerationRedundancySize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
      set_DebugMatrixUart(rhs.get_DebugMatrixUart());
      set_DebugFragmentUart(rhs.get_DebugFragmentUart());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
    }

    RlncInitConfigCommand(const RlncInitConfigCommand&& rhs ) noexcept
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationRedundancySize(rhs.get_GenerationRedundancySize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
      set_DebugMatrixUart(rhs.get_DebugMatrixUart());
      set_DebugFragmentUart(rhs.get_DebugFragmentUart());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
    }

    ~RlncInitConfigCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      GENERATIONSIZE = 1,
      GENERATIONREDUNDANCYSIZE = 2,
      GENERATIONCOUNT = 3,
      FRAMESIZE = 4,
      TOTALFRAMECOUNT = 5,
      FIELDDEGREE = 6,
      FIELDPOLY = 7,
      LFSRSEED = 8,
      LFSRPOLY = 9,
      DEBUGMATRIXUART = 10,
      DEBUGFRAGMENTUART = 11,
      RECEPTIONRATECONFIG = 12
    };

    RlncInitConfigCommand& operator=(const RlncInitConfigCommand& rhs)
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationRedundancySize(rhs.get_GenerationRedundancySize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
      set_DebugMatrixUart(rhs.get_DebugMatrixUart());
      set_DebugFragmentUart(rhs.get_DebugFragmentUart());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
      return *this;
    }

    RlncInitConfigCommand& operator=(const RlncInitConfigCommand&& rhs) noexcept
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationRedundancySize(rhs.get_GenerationRedundancySize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
      set_DebugMatrixUart(rhs.get_DebugMatrixUart());
      set_DebugFragmentUart(rhs.get_DebugFragmentUart());
      set_receptionRateConfig(rhs.get_receptionRateConfig());
      return *this;
    }

    inline void clear_GenerationSize() { GenerationSize_.clear(); }
    inline void set_GenerationSize(const EmbeddedProto::uint32& value) { GenerationSize_ = value; }
    inline void set_GenerationSize(const EmbeddedProto::uint32&& value) { GenerationSize_ = value; }
    inline EmbeddedProto::uint32& mutable_GenerationSize() { return GenerationSize_; }
    inline const EmbeddedProto::uint32& get_GenerationSize() const { return GenerationSize_; }
    inline EmbeddedProto::uint32::FIELD_TYPE GenerationSize() const { return GenerationSize_.get(); }

    inline void clear_GenerationRedundancySize() { GenerationRedundancySize_.clear(); }
    inline void set_GenerationRedundancySize(const EmbeddedProto::uint32& value) { GenerationRedundancySize_ = value; }
    inline void set_GenerationRedundancySize(const EmbeddedProto::uint32&& value) { GenerationRedundancySize_ = value; }
    inline EmbeddedProto::uint32& mutable_GenerationRedundancySize() { return GenerationRedundancySize_; }
    inline const EmbeddedProto::uint32& get_GenerationRedundancySize() const { return GenerationRedundancySize_; }
    inline EmbeddedProto::uint32::FIELD_TYPE GenerationRedundancySize() const { return GenerationRedundancySize_.get(); }

    inline void clear_GenerationCount() { GenerationCount_.clear(); }
    inline void set_GenerationCount(const EmbeddedProto::uint32& value) { GenerationCount_ = value; }
    inline void set_GenerationCount(const EmbeddedProto::uint32&& value) { GenerationCount_ = value; }
    inline EmbeddedProto::uint32& mutable_GenerationCount() { return GenerationCount_; }
    inline const EmbeddedProto::uint32& get_GenerationCount() const { return GenerationCount_; }
    inline EmbeddedProto::uint32::FIELD_TYPE GenerationCount() const { return GenerationCount_.get(); }

    inline void clear_FrameSize() { FrameSize_.clear(); }
    inline void set_FrameSize(const EmbeddedProto::uint32& value) { FrameSize_ = value; }
    inline void set_FrameSize(const EmbeddedProto::uint32&& value) { FrameSize_ = value; }
    inline EmbeddedProto::uint32& mutable_FrameSize() { return FrameSize_; }
    inline const EmbeddedProto::uint32& get_FrameSize() const { return FrameSize_; }
    inline EmbeddedProto::uint32::FIELD_TYPE FrameSize() const { return FrameSize_.get(); }

    inline void clear_TotalFrameCount() { TotalFrameCount_.clear(); }
    inline void set_TotalFrameCount(const EmbeddedProto::uint32& value) { TotalFrameCount_ = value; }
    inline void set_TotalFrameCount(const EmbeddedProto::uint32&& value) { TotalFrameCount_ = value; }
    inline EmbeddedProto::uint32& mutable_TotalFrameCount() { return TotalFrameCount_; }
    inline const EmbeddedProto::uint32& get_TotalFrameCount() const { return TotalFrameCount_; }
    inline EmbeddedProto::uint32::FIELD_TYPE TotalFrameCount() const { return TotalFrameCount_.get(); }

    inline void clear_FieldDegree() { FieldDegree_.clear(); }
    inline void set_FieldDegree(const EmbeddedProto::uint32& value) { FieldDegree_ = value; }
    inline void set_FieldDegree(const EmbeddedProto::uint32&& value) { FieldDegree_ = value; }
    inline EmbeddedProto::uint32& mutable_FieldDegree() { return FieldDegree_; }
    inline const EmbeddedProto::uint32& get_FieldDegree() const { return FieldDegree_; }
    inline EmbeddedProto::uint32::FIELD_TYPE FieldDegree() const { return FieldDegree_.get(); }

    inline void clear_FieldPoly() { FieldPoly_.clear(); }
    inline void set_FieldPoly(const EmbeddedProto::uint32& value) { FieldPoly_ = value; }
    inline void set_FieldPoly(const EmbeddedProto::uint32&& value) { FieldPoly_ = value; }
    inline EmbeddedProto::uint32& mutable_FieldPoly() { return FieldPoly_; }
    inline const EmbeddedProto::uint32& get_FieldPoly() const { return FieldPoly_; }
    inline EmbeddedProto::uint32::FIELD_TYPE FieldPoly() const { return FieldPoly_.get(); }

    inline void clear_LfsrSeed() { LfsrSeed_.clear(); }
    inline void set_LfsrSeed(const EmbeddedProto::uint32& value) { LfsrSeed_ = value; }
    inline void set_LfsrSeed(const EmbeddedProto::uint32&& value) { LfsrSeed_ = value; }
    inline EmbeddedProto::uint32& mutable_LfsrSeed() { return LfsrSeed_; }
    inline const EmbeddedProto::uint32& get_LfsrSeed() const { return LfsrSeed_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LfsrSeed() const { return LfsrSeed_.get(); }

    inline void clear_LfsrPoly() { LfsrPoly_.clear(); }
    inline void set_LfsrPoly(const EmbeddedProto::uint32& value) { LfsrPoly_ = value; }
    inline void set_LfsrPoly(const EmbeddedProto::uint32&& value) { LfsrPoly_ = value; }
    inline EmbeddedProto::uint32& mutable_LfsrPoly() { return LfsrPoly_; }
    inline const EmbeddedProto::uint32& get_LfsrPoly() const { return LfsrPoly_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LfsrPoly() const { return LfsrPoly_.get(); }

    inline void clear_DebugMatrixUart() { DebugMatrixUart_.clear(); }
    inline void set_DebugMatrixUart(const EmbeddedProto::boolean& value) { DebugMatrixUart_ = value; }
    inline void set_DebugMatrixUart(const EmbeddedProto::boolean&& value) { DebugMatrixUart_ = value; }
    inline EmbeddedProto::boolean& mutable_DebugMatrixUart() { return DebugMatrixUart_; }
    inline const EmbeddedProto::boolean& get_DebugMatrixUart() const { return DebugMatrixUart_; }
    inline EmbeddedProto::boolean::FIELD_TYPE DebugMatrixUart() const { return DebugMatrixUart_.get(); }

    inline void clear_DebugFragmentUart() { DebugFragmentUart_.clear(); }
    inline void set_DebugFragmentUart(const EmbeddedProto::boolean& value) { DebugFragmentUart_ = value; }
    inline void set_DebugFragmentUart(const EmbeddedProto::boolean&& value) { DebugFragmentUart_ = value; }
    inline EmbeddedProto::boolean& mutable_DebugFragmentUart() { return DebugFragmentUart_; }
    inline const EmbeddedProto::boolean& get_DebugFragmentUart() const { return DebugFragmentUart_; }
    inline EmbeddedProto::boolean::FIELD_TYPE DebugFragmentUart() const { return DebugFragmentUart_.get(); }

    inline bool has_receptionRateConfig() const
    {
      return 0 != (presence::mask(presence::fields::RECEPTIONRATECONFIG) & presence_[presence::index(presence::fields::RECEPTIONRATECONFIG)]);
    }
    inline void clear_receptionRateConfig()
    {
      presence_[presence::index(presence::fields::RECEPTIONRATECONFIG)] &= ~(presence::mask(presence::fields::RECEPTIONRATECONFIG));
      receptionRateConfig_.clear();
    }
    inline void set_receptionRateConfig(const ReceptionRateConfig& value)
    {
      presence_[presence::index(presence::fields::RECEPTIONRATECONFIG)] |= presence::mask(presence::fields::RECEPTIONRATECONFIG);
      receptionRateConfig_ = value;
    }
    inline void set_receptionRateConfig(const ReceptionRateConfig&& value)
    {
      presence_[presence::index(presence::fields::RECEPTIONRATECONFIG)] |= presence::mask(presence::fields::RECEPTIONRATECONFIG);
      receptionRateConfig_ = value;
    }
    inline ReceptionRateConfig& mutable_receptionRateConfig()
    {
      presence_[presence::index(presence::fields::RECEPTIONRATECONFIG)] |= presence::mask(presence::fields::RECEPTIONRATECONFIG);
      return receptionRateConfig_;
    }
    inline const ReceptionRateConfig& get_receptionRateConfig() const { return receptionRateConfig_; }
    inline const ReceptionRateConfig& receptionRateConfig() const { return receptionRateConfig_; }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != GenerationSize_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = GenerationSize_.serialize_with_id(static_cast<uint32_t>(id::GENERATIONSIZE), buffer, false);
      }

      if((0U != GenerationRedundancySize_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = GenerationRedundancySize_.serialize_with_id(static_cast<uint32_t>(id::GENERATIONREDUNDANCYSIZE), buffer, false);
      }

      if((0U != GenerationCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = GenerationCount_.serialize_with_id(static_cast<uint32_t>(id::GENERATIONCOUNT), buffer, false);
      }

      if((0U != FrameSize_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FrameSize_.serialize_with_id(static_cast<uint32_t>(id::FRAMESIZE), buffer, false);
      }

      if((0U != TotalFrameCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = TotalFrameCount_.serialize_with_id(static_cast<uint32_t>(id::TOTALFRAMECOUNT), buffer, false);
      }

      if((0U != FieldDegree_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FieldDegree_.serialize_with_id(static_cast<uint32_t>(id::FIELDDEGREE), buffer, false);
      }

      if((0U != FieldPoly_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = FieldPoly_.serialize_with_id(static_cast<uint32_t>(id::FIELDPOLY), buffer, false);
      }

      if((0U != LfsrSeed_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = LfsrSeed_.serialize_with_id(static_cast<uint32_t>(id::LFSRSEED), buffer, false);
      }

      if((0U != LfsrPoly_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = LfsrPoly_.serialize_with_id(static_cast<uint32_t>(id::LFSRPOLY), buffer, false);
      }

      if((false != DebugMatrixUart_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DebugMatrixUart_.serialize_with_id(static_cast<uint32_t>(id::DEBUGMATRIXUART), buffer, false);
      }

      if((false != DebugFragmentUart_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DebugFragmentUart_.serialize_with_id(static_cast<uint32_t>(id::DEBUGFRAGMENTUART), buffer, false);
      }

      if(has_receptionRateConfig() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = receptionRateConfig_.serialize_with_id(static_cast<uint32_t>(id::RECEPTIONRATECONFIG), buffer, true);
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
          case id::GENERATIONSIZE:
            return_value = GenerationSize_.deserialize_check_type(buffer, wire_type);
            break;

          case id::GENERATIONREDUNDANCYSIZE:
            return_value = GenerationRedundancySize_.deserialize_check_type(buffer, wire_type);
            break;

          case id::GENERATIONCOUNT:
            return_value = GenerationCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FRAMESIZE:
            return_value = FrameSize_.deserialize_check_type(buffer, wire_type);
            break;

          case id::TOTALFRAMECOUNT:
            return_value = TotalFrameCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FIELDDEGREE:
            return_value = FieldDegree_.deserialize_check_type(buffer, wire_type);
            break;

          case id::FIELDPOLY:
            return_value = FieldPoly_.deserialize_check_type(buffer, wire_type);
            break;

          case id::LFSRSEED:
            return_value = LfsrSeed_.deserialize_check_type(buffer, wire_type);
            break;

          case id::LFSRPOLY:
            return_value = LfsrPoly_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DEBUGMATRIXUART:
            return_value = DebugMatrixUart_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DEBUGFRAGMENTUART:
            return_value = DebugFragmentUart_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RECEPTIONRATECONFIG:
            presence_[presence::index(presence::fields::RECEPTIONRATECONFIG)] |= presence::mask(presence::fields::RECEPTIONRATECONFIG);
            return_value = receptionRateConfig_.deserialize_check_type(buffer, wire_type);
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
      clear_GenerationSize();
      clear_GenerationRedundancySize();
      clear_GenerationCount();
      clear_FrameSize();
      clear_TotalFrameCount();
      clear_FieldDegree();
      clear_FieldPoly();
      clear_LfsrSeed();
      clear_LfsrPoly();
      clear_DebugMatrixUart();
      clear_DebugFragmentUart();
      clear_receptionRateConfig();

    }

    private:

      // Define constants for tracking the presence of fields.
      // Use a struct to scope the variables from user fields as namespaces are not allowed within classes.
      struct presence
      {
        // An enumeration with all the fields for which presence has to be tracked.
        enum class fields : uint32_t
        {
          RECEPTIONRATECONFIG
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

      EmbeddedProto::uint32 GenerationSize_ = 0U;
      EmbeddedProto::uint32 GenerationRedundancySize_ = 0U;
      EmbeddedProto::uint32 GenerationCount_ = 0U;
      EmbeddedProto::uint32 FrameSize_ = 0U;
      EmbeddedProto::uint32 TotalFrameCount_ = 0U;
      EmbeddedProto::uint32 FieldDegree_ = 0U;
      EmbeddedProto::uint32 FieldPoly_ = 0U;
      EmbeddedProto::uint32 LfsrSeed_ = 0U;
      EmbeddedProto::uint32 LfsrPoly_ = 0U;
      EmbeddedProto::boolean DebugMatrixUart_ = false;
      EmbeddedProto::boolean DebugFragmentUart_ = false;
      ReceptionRateConfig receptionRateConfig_;

};

class RlncEncodedFragment final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncEncodedFragment() = default;
    RlncEncodedFragment(const RlncEncodedFragment& rhs )
    {
      set_LfsrState(rhs.get_LfsrState());
    }

    RlncEncodedFragment(const RlncEncodedFragment&& rhs ) noexcept
    {
      set_LfsrState(rhs.get_LfsrState());
    }

    ~RlncEncodedFragment() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      LFSRSTATE = 1
    };

    RlncEncodedFragment& operator=(const RlncEncodedFragment& rhs)
    {
      set_LfsrState(rhs.get_LfsrState());
      return *this;
    }

    RlncEncodedFragment& operator=(const RlncEncodedFragment&& rhs) noexcept
    {
      set_LfsrState(rhs.get_LfsrState());
      return *this;
    }

    inline void clear_LfsrState() { LfsrState_.clear(); }
    inline void set_LfsrState(const EmbeddedProto::uint32& value) { LfsrState_ = value; }
    inline void set_LfsrState(const EmbeddedProto::uint32&& value) { LfsrState_ = value; }
    inline EmbeddedProto::uint32& mutable_LfsrState() { return LfsrState_; }
    inline const EmbeddedProto::uint32& get_LfsrState() const { return LfsrState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LfsrState() const { return LfsrState_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != LfsrState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = LfsrState_.serialize_with_id(static_cast<uint32_t>(id::LFSRSTATE), buffer, false);
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
          case id::LFSRSTATE:
            return_value = LfsrState_.deserialize_check_type(buffer, wire_type);
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
      clear_LfsrState();

    }

    private:


      EmbeddedProto::uint32 LfsrState_ = 0U;

};

template<uint32_t Meta_LENGTH, 
uint32_t Payload_LENGTH>
class RlncFlashEncodedFragment final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncFlashEncodedFragment() = default;
    RlncFlashEncodedFragment(const RlncFlashEncodedFragment& rhs )
    {
      set_Meta(rhs.get_Meta());
      set_Payload(rhs.get_Payload());
    }

    RlncFlashEncodedFragment(const RlncFlashEncodedFragment&& rhs ) noexcept
    {
      set_Meta(rhs.get_Meta());
      set_Payload(rhs.get_Payload());
    }

    ~RlncFlashEncodedFragment() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      META = 1,
      PAYLOAD = 2
    };

    RlncFlashEncodedFragment& operator=(const RlncFlashEncodedFragment& rhs)
    {
      set_Meta(rhs.get_Meta());
      set_Payload(rhs.get_Payload());
      return *this;
    }

    RlncFlashEncodedFragment& operator=(const RlncFlashEncodedFragment&& rhs) noexcept
    {
      set_Meta(rhs.get_Meta());
      set_Payload(rhs.get_Payload());
      return *this;
    }

    inline void clear_Meta() { Meta_.clear(); }
    inline ::EmbeddedProto::FieldBytes<Meta_LENGTH>& mutable_Meta() { return Meta_; }
    inline void set_Meta(const ::EmbeddedProto::FieldBytes<Meta_LENGTH>& rhs) { Meta_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<Meta_LENGTH>& get_Meta() const { return Meta_; }
    inline const uint8_t* Meta() const { return Meta_.get_const(); }

    inline void clear_Payload() { Payload_.clear(); }
    inline ::EmbeddedProto::FieldBytes<Payload_LENGTH>& mutable_Payload() { return Payload_; }
    inline void set_Payload(const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& rhs) { Payload_.set(rhs); }
    inline const ::EmbeddedProto::FieldBytes<Payload_LENGTH>& get_Payload() const { return Payload_; }
    inline const uint8_t* Payload() const { return Payload_.get_const(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if(::EmbeddedProto::Error::NO_ERRORS == return_value)
      {
        return_value = Meta_.serialize_with_id(static_cast<uint32_t>(id::META), buffer, false);
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
          case id::META:
            return_value = Meta_.deserialize_check_type(buffer, wire_type);
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
      clear_Meta();
      clear_Payload();

    }

    private:


      ::EmbeddedProto::FieldBytes<Meta_LENGTH> Meta_;
      ::EmbeddedProto::FieldBytes<Payload_LENGTH> Payload_;

};

class RlncStateUpdate final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncStateUpdate() = default;
    RlncStateUpdate(const RlncStateUpdate& rhs )
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
    }

    RlncStateUpdate(const RlncStateUpdate&& rhs ) noexcept
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
    }

    ~RlncStateUpdate() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      GENERATIONINDEX = 1
    };

    RlncStateUpdate& operator=(const RlncStateUpdate& rhs)
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
      return *this;
    }

    RlncStateUpdate& operator=(const RlncStateUpdate&& rhs) noexcept
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
      return *this;
    }

    inline void clear_GenerationIndex() { GenerationIndex_.clear(); }
    inline void set_GenerationIndex(const EmbeddedProto::uint32& value) { GenerationIndex_ = value; }
    inline void set_GenerationIndex(const EmbeddedProto::uint32&& value) { GenerationIndex_ = value; }
    inline EmbeddedProto::uint32& mutable_GenerationIndex() { return GenerationIndex_; }
    inline const EmbeddedProto::uint32& get_GenerationIndex() const { return GenerationIndex_; }
    inline EmbeddedProto::uint32::FIELD_TYPE GenerationIndex() const { return GenerationIndex_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != GenerationIndex_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = GenerationIndex_.serialize_with_id(static_cast<uint32_t>(id::GENERATIONINDEX), buffer, false);
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
          case id::GENERATIONINDEX:
            return_value = GenerationIndex_.deserialize_check_type(buffer, wire_type);
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
      clear_GenerationIndex();

    }

    private:


      EmbeddedProto::uint32 GenerationIndex_ = 0U;

};

class RlncTerminationCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncTerminationCommand() = default;
    RlncTerminationCommand(const RlncTerminationCommand& rhs )
    {
    }

    RlncTerminationCommand(const RlncTerminationCommand&& rhs ) noexcept
    {
    }

    ~RlncTerminationCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
    };

    RlncTerminationCommand& operator=(const RlncTerminationCommand& rhs)
    {
      return *this;
    }

    RlncTerminationCommand& operator=(const RlncTerminationCommand&& rhs) noexcept
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

class DecodingMatrix final: public ::EmbeddedProto::MessageInterface
{
  public:
    DecodingMatrix() = default;
    DecodingMatrix(const DecodingMatrix& rhs )
    {
      set_Cols(rhs.get_Cols());
      set_Rows(rhs.get_Rows());
    }

    DecodingMatrix(const DecodingMatrix&& rhs ) noexcept
    {
      set_Cols(rhs.get_Cols());
      set_Rows(rhs.get_Rows());
    }

    ~DecodingMatrix() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      COLS = 1,
      ROWS = 2
    };

    DecodingMatrix& operator=(const DecodingMatrix& rhs)
    {
      set_Cols(rhs.get_Cols());
      set_Rows(rhs.get_Rows());
      return *this;
    }

    DecodingMatrix& operator=(const DecodingMatrix&& rhs) noexcept
    {
      set_Cols(rhs.get_Cols());
      set_Rows(rhs.get_Rows());
      return *this;
    }

    inline void clear_Cols() { Cols_.clear(); }
    inline void set_Cols(const EmbeddedProto::uint32& value) { Cols_ = value; }
    inline void set_Cols(const EmbeddedProto::uint32&& value) { Cols_ = value; }
    inline EmbeddedProto::uint32& mutable_Cols() { return Cols_; }
    inline const EmbeddedProto::uint32& get_Cols() const { return Cols_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Cols() const { return Cols_.get(); }

    inline void clear_Rows() { Rows_.clear(); }
    inline void set_Rows(const EmbeddedProto::uint32& value) { Rows_ = value; }
    inline void set_Rows(const EmbeddedProto::uint32&& value) { Rows_ = value; }
    inline EmbeddedProto::uint32& mutable_Rows() { return Rows_; }
    inline const EmbeddedProto::uint32& get_Rows() const { return Rows_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Rows() const { return Rows_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != Cols_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Cols_.serialize_with_id(static_cast<uint32_t>(id::COLS), buffer, false);
      }

      if((0U != Rows_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Rows_.serialize_with_id(static_cast<uint32_t>(id::ROWS), buffer, false);
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
          case id::COLS:
            return_value = Cols_.deserialize_check_type(buffer, wire_type);
            break;

          case id::ROWS:
            return_value = Rows_.deserialize_check_type(buffer, wire_type);
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
      clear_Cols();
      clear_Rows();

    }

    private:


      EmbeddedProto::uint32 Cols_ = 0U;
      EmbeddedProto::uint32 Rows_ = 0U;

};

class DecodingUpdate final: public ::EmbeddedProto::MessageInterface
{
  public:
    DecodingUpdate() = default;
    DecodingUpdate(const DecodingUpdate& rhs )
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_LastRowCrc8(rhs.get_LastRowCrc8());
      set_LastRowIndex(rhs.get_LastRowIndex());
      set_RankProgress(rhs.get_RankProgress());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
      set_UsedLfsrState(rhs.get_UsedLfsrState());
      set_CurrentLfsrState(rhs.get_CurrentLfsrState());
    }

    DecodingUpdate(const DecodingUpdate&& rhs ) noexcept
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_LastRowCrc8(rhs.get_LastRowCrc8());
      set_LastRowIndex(rhs.get_LastRowIndex());
      set_RankProgress(rhs.get_RankProgress());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
      set_UsedLfsrState(rhs.get_UsedLfsrState());
      set_CurrentLfsrState(rhs.get_CurrentLfsrState());
    }

    ~DecodingUpdate() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MATRIXCRC8 = 1,
      FIRSTROWCRC8 = 2,
      LASTROWCRC8 = 3,
      LASTROWINDEX = 4,
      RANKPROGRESS = 5,
      RECEIVEDFRAGMENTS = 6,
      CURRENTGENERATIONINDEX = 7,
      ISRUNNING = 8,
      USEDLFSRSTATE = 9,
      CURRENTLFSRSTATE = 10
    };

    DecodingUpdate& operator=(const DecodingUpdate& rhs)
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_LastRowCrc8(rhs.get_LastRowCrc8());
      set_LastRowIndex(rhs.get_LastRowIndex());
      set_RankProgress(rhs.get_RankProgress());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
      set_UsedLfsrState(rhs.get_UsedLfsrState());
      set_CurrentLfsrState(rhs.get_CurrentLfsrState());
      return *this;
    }

    DecodingUpdate& operator=(const DecodingUpdate&& rhs) noexcept
    {
      set_MatrixCrc8(rhs.get_MatrixCrc8());
      set_FirstRowCrc8(rhs.get_FirstRowCrc8());
      set_LastRowCrc8(rhs.get_LastRowCrc8());
      set_LastRowIndex(rhs.get_LastRowIndex());
      set_RankProgress(rhs.get_RankProgress());
      set_ReceivedFragments(rhs.get_ReceivedFragments());
      set_CurrentGenerationIndex(rhs.get_CurrentGenerationIndex());
      set_IsRunning(rhs.get_IsRunning());
      set_UsedLfsrState(rhs.get_UsedLfsrState());
      set_CurrentLfsrState(rhs.get_CurrentLfsrState());
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

    inline void clear_LastRowCrc8() { LastRowCrc8_.clear(); }
    inline void set_LastRowCrc8(const EmbeddedProto::uint32& value) { LastRowCrc8_ = value; }
    inline void set_LastRowCrc8(const EmbeddedProto::uint32&& value) { LastRowCrc8_ = value; }
    inline EmbeddedProto::uint32& mutable_LastRowCrc8() { return LastRowCrc8_; }
    inline const EmbeddedProto::uint32& get_LastRowCrc8() const { return LastRowCrc8_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LastRowCrc8() const { return LastRowCrc8_.get(); }

    inline void clear_LastRowIndex() { LastRowIndex_.clear(); }
    inline void set_LastRowIndex(const EmbeddedProto::uint32& value) { LastRowIndex_ = value; }
    inline void set_LastRowIndex(const EmbeddedProto::uint32&& value) { LastRowIndex_ = value; }
    inline EmbeddedProto::uint32& mutable_LastRowIndex() { return LastRowIndex_; }
    inline const EmbeddedProto::uint32& get_LastRowIndex() const { return LastRowIndex_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LastRowIndex() const { return LastRowIndex_.get(); }

    inline void clear_RankProgress() { RankProgress_.clear(); }
    inline void set_RankProgress(const EmbeddedProto::uint32& value) { RankProgress_ = value; }
    inline void set_RankProgress(const EmbeddedProto::uint32&& value) { RankProgress_ = value; }
    inline EmbeddedProto::uint32& mutable_RankProgress() { return RankProgress_; }
    inline const EmbeddedProto::uint32& get_RankProgress() const { return RankProgress_; }
    inline EmbeddedProto::uint32::FIELD_TYPE RankProgress() const { return RankProgress_.get(); }

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

    inline void clear_UsedLfsrState() { UsedLfsrState_.clear(); }
    inline void set_UsedLfsrState(const EmbeddedProto::uint32& value) { UsedLfsrState_ = value; }
    inline void set_UsedLfsrState(const EmbeddedProto::uint32&& value) { UsedLfsrState_ = value; }
    inline EmbeddedProto::uint32& mutable_UsedLfsrState() { return UsedLfsrState_; }
    inline const EmbeddedProto::uint32& get_UsedLfsrState() const { return UsedLfsrState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE UsedLfsrState() const { return UsedLfsrState_.get(); }

    inline void clear_CurrentLfsrState() { CurrentLfsrState_.clear(); }
    inline void set_CurrentLfsrState(const EmbeddedProto::uint32& value) { CurrentLfsrState_ = value; }
    inline void set_CurrentLfsrState(const EmbeddedProto::uint32&& value) { CurrentLfsrState_ = value; }
    inline EmbeddedProto::uint32& mutable_CurrentLfsrState() { return CurrentLfsrState_; }
    inline const EmbeddedProto::uint32& get_CurrentLfsrState() const { return CurrentLfsrState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE CurrentLfsrState() const { return CurrentLfsrState_.get(); }


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

      if((0U != LastRowCrc8_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = LastRowCrc8_.serialize_with_id(static_cast<uint32_t>(id::LASTROWCRC8), buffer, false);
      }

      if((0U != LastRowIndex_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = LastRowIndex_.serialize_with_id(static_cast<uint32_t>(id::LASTROWINDEX), buffer, false);
      }

      if((0U != RankProgress_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = RankProgress_.serialize_with_id(static_cast<uint32_t>(id::RANKPROGRESS), buffer, false);
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

      if((0U != UsedLfsrState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = UsedLfsrState_.serialize_with_id(static_cast<uint32_t>(id::USEDLFSRSTATE), buffer, false);
      }

      if((0U != CurrentLfsrState_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = CurrentLfsrState_.serialize_with_id(static_cast<uint32_t>(id::CURRENTLFSRSTATE), buffer, false);
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

          case id::LASTROWCRC8:
            return_value = LastRowCrc8_.deserialize_check_type(buffer, wire_type);
            break;

          case id::LASTROWINDEX:
            return_value = LastRowIndex_.deserialize_check_type(buffer, wire_type);
            break;

          case id::RANKPROGRESS:
            return_value = RankProgress_.deserialize_check_type(buffer, wire_type);
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

          case id::USEDLFSRSTATE:
            return_value = UsedLfsrState_.deserialize_check_type(buffer, wire_type);
            break;

          case id::CURRENTLFSRSTATE:
            return_value = CurrentLfsrState_.deserialize_check_type(buffer, wire_type);
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
      clear_LastRowCrc8();
      clear_LastRowIndex();
      clear_RankProgress();
      clear_ReceivedFragments();
      clear_CurrentGenerationIndex();
      clear_IsRunning();
      clear_UsedLfsrState();
      clear_CurrentLfsrState();

    }

    private:


      EmbeddedProto::uint32 MatrixCrc8_ = 0U;
      EmbeddedProto::uint32 FirstRowCrc8_ = 0U;
      EmbeddedProto::uint32 LastRowCrc8_ = 0U;
      EmbeddedProto::uint32 LastRowIndex_ = 0U;
      EmbeddedProto::uint32 RankProgress_ = 0U;
      EmbeddedProto::uint32 ReceivedFragments_ = 0U;
      EmbeddedProto::uint32 CurrentGenerationIndex_ = 0U;
      EmbeddedProto::boolean IsRunning_ = false;
      EmbeddedProto::uint32 UsedLfsrState_ = 0U;
      EmbeddedProto::uint32 CurrentLfsrState_ = 0U;

};

#endif // SHARED_FIRMWARE_H