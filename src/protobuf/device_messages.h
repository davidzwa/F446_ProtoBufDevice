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
    }

    BootMessage(const BootMessage&& rhs ) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_AppName(rhs.get_AppName());
    }

    ~BootMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      DEVICEIDENTIFIER = 1,
      FIRMWAREVERSION = 2,
      APPNAME = 3
    };

    BootMessage& operator=(const BootMessage& rhs)
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_AppName(rhs.get_AppName());
      return *this;
    }

    BootMessage& operator=(const BootMessage&& rhs) noexcept
    {
      set_DeviceIdentifier(rhs.get_DeviceIdentifier());
      set_FirmwareVersion(rhs.get_FirmwareVersion());
      set_AppName(rhs.get_AppName());
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

    }

    private:


      DeviceId DeviceIdentifier_;
      Version FirmwareVersion_;
      ::EmbeddedProto::FieldString<AppName_LENGTH> AppName_;

};

template<uint32_t bootMessage_AppName_LENGTH>
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

        default:
          break;
      }

    }

    ~UartResponse() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      BOOTMESSAGE = 1
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