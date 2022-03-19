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
    }

    BootMessage(const BootMessage&& rhs ) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
    }

    ~BootMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      DEVICEIDENTIFIER = 1,
      FIRMWAREVERSION = 2,
      MEASUREMENTCOUNT = 3,
      MEASUREMENTSDISABLED = 4
    };

    BootMessage& operator=(const BootMessage& rhs)
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_MeasurementCount(rhs.get_MeasurementCount());
      set_MeasurementsDisabled(rhs.get_MeasurementsDisabled());
      return *this;
    }

    BootMessage& operator=(const BootMessage&& rhs) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
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
      clear_MeasurementCount();
      clear_MeasurementsDisabled();

    }

    private:


      DeviceId DeviceIdentifier_;
      Version FirmwareVersion_;
      EmbeddedProto::uint32 MeasurementCount_ = 0U;
      EmbeddedProto::boolean MeasurementsDisabled_ = false;

};

class RlncInitConfigCommand final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncInitConfigCommand() = default;
    RlncInitConfigCommand(const RlncInitConfigCommand& rhs )
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
    }

    RlncInitConfigCommand(const RlncInitConfigCommand&& rhs ) noexcept
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
    }

    ~RlncInitConfigCommand() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      GENERATIONSIZE = 1,
      GENERATIONCOUNT = 2,
      FRAMESIZE = 3,
      TOTALFRAMECOUNT = 4,
      FIELDDEGREE = 5,
      FIELDPOLY = 6,
      LFSRSEED = 7,
      LFSRPOLY = 8
    };

    RlncInitConfigCommand& operator=(const RlncInitConfigCommand& rhs)
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
      return *this;
    }

    RlncInitConfigCommand& operator=(const RlncInitConfigCommand&& rhs) noexcept
    {
      set_GenerationSize(rhs.get_GenerationSize());
      set_GenerationCount(rhs.get_GenerationCount());
      set_FrameSize(rhs.get_FrameSize());
      set_TotalFrameCount(rhs.get_TotalFrameCount());
      set_FieldDegree(rhs.get_FieldDegree());
      set_FieldPoly(rhs.get_FieldPoly());
      set_LfsrSeed(rhs.get_LfsrSeed());
      set_LfsrPoly(rhs.get_LfsrPoly());
      return *this;
    }

    inline void clear_GenerationSize() { GenerationSize_.clear(); }
    inline void set_GenerationSize(const EmbeddedProto::uint32& value) { GenerationSize_ = value; }
    inline void set_GenerationSize(const EmbeddedProto::uint32&& value) { GenerationSize_ = value; }
    inline EmbeddedProto::uint32& mutable_GenerationSize() { return GenerationSize_; }
    inline const EmbeddedProto::uint32& get_GenerationSize() const { return GenerationSize_; }
    inline EmbeddedProto::uint32::FIELD_TYPE GenerationSize() const { return GenerationSize_.get(); }

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


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != GenerationSize_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = GenerationSize_.serialize_with_id(static_cast<uint32_t>(id::GENERATIONSIZE), buffer, false);
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
      clear_GenerationCount();
      clear_FrameSize();
      clear_TotalFrameCount();
      clear_FieldDegree();
      clear_FieldPoly();
      clear_LfsrSeed();
      clear_LfsrPoly();

    }

    private:


      EmbeddedProto::uint32 GenerationSize_ = 0U;
      EmbeddedProto::uint32 GenerationCount_ = 0U;
      EmbeddedProto::uint32 FrameSize_ = 0U;
      EmbeddedProto::uint32 TotalFrameCount_ = 0U;
      EmbeddedProto::uint32 FieldDegree_ = 0U;
      EmbeddedProto::uint32 FieldPoly_ = 0U;
      EmbeddedProto::uint32 LfsrSeed_ = 0U;
      EmbeddedProto::uint32 LfsrPoly_ = 0U;

};

class RlncEncodedFragment final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncEncodedFragment() = default;
    RlncEncodedFragment(const RlncEncodedFragment& rhs )
    {
    }

    RlncEncodedFragment(const RlncEncodedFragment&& rhs ) noexcept
    {
    }

    ~RlncEncodedFragment() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
    };

    RlncEncodedFragment& operator=(const RlncEncodedFragment& rhs)
    {
      return *this;
    }

    RlncEncodedFragment& operator=(const RlncEncodedFragment&& rhs) noexcept
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

class RlncStateUpdate final: public ::EmbeddedProto::MessageInterface
{
  public:
    RlncStateUpdate() = default;
    RlncStateUpdate(const RlncStateUpdate& rhs )
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
      set_LfsrState(rhs.get_LfsrState());
    }

    RlncStateUpdate(const RlncStateUpdate&& rhs ) noexcept
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
      set_LfsrState(rhs.get_LfsrState());
    }

    ~RlncStateUpdate() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      GENERATIONINDEX = 1,
      LFSRSTATE = 2
    };

    RlncStateUpdate& operator=(const RlncStateUpdate& rhs)
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
      set_LfsrState(rhs.get_LfsrState());
      return *this;
    }

    RlncStateUpdate& operator=(const RlncStateUpdate&& rhs) noexcept
    {
      set_GenerationIndex(rhs.get_GenerationIndex());
      set_LfsrState(rhs.get_LfsrState());
      return *this;
    }

    inline void clear_GenerationIndex() { GenerationIndex_.clear(); }
    inline void set_GenerationIndex(const EmbeddedProto::uint32& value) { GenerationIndex_ = value; }
    inline void set_GenerationIndex(const EmbeddedProto::uint32&& value) { GenerationIndex_ = value; }
    inline EmbeddedProto::uint32& mutable_GenerationIndex() { return GenerationIndex_; }
    inline const EmbeddedProto::uint32& get_GenerationIndex() const { return GenerationIndex_; }
    inline EmbeddedProto::uint32::FIELD_TYPE GenerationIndex() const { return GenerationIndex_.get(); }

    inline void clear_LfsrState() { LfsrState_.clear(); }
    inline void set_LfsrState(const EmbeddedProto::uint32& value) { LfsrState_ = value; }
    inline void set_LfsrState(const EmbeddedProto::uint32&& value) { LfsrState_ = value; }
    inline EmbeddedProto::uint32& mutable_LfsrState() { return LfsrState_; }
    inline const EmbeddedProto::uint32& get_LfsrState() const { return LfsrState_; }
    inline EmbeddedProto::uint32::FIELD_TYPE LfsrState() const { return LfsrState_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != GenerationIndex_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = GenerationIndex_.serialize_with_id(static_cast<uint32_t>(id::GENERATIONINDEX), buffer, false);
      }

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
          case id::GENERATIONINDEX:
            return_value = GenerationIndex_.deserialize_check_type(buffer, wire_type);
            break;

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
      clear_GenerationIndex();
      clear_LfsrState();

    }

    private:


      EmbeddedProto::uint32 GenerationIndex_ = 0U;
      EmbeddedProto::uint32 LfsrState_ = 0U;

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

#endif // SHARED_FIRMWARE_H