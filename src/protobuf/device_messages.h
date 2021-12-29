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

template<uint32_t Payload_LENGTH>
class LoraReceive final: public ::EmbeddedProto::MessageInterface
{
  public:
    LoraReceive() = default;
    LoraReceive(const LoraReceive& rhs )
    {
      set_Size(rhs.get_Size());
      set_Rssi(rhs.get_Rssi());
      set_Snr(rhs.get_Snr());
      set_SequenceNumber(rhs.get_SequenceNumber());
      set_IsMeasurementFragment(rhs.get_IsMeasurementFragment());
      set_Success(rhs.get_Success());
      set_Payload(rhs.get_Payload());
    }

    LoraReceive(const LoraReceive&& rhs ) noexcept
    {
      set_Size(rhs.get_Size());
      set_Rssi(rhs.get_Rssi());
      set_Snr(rhs.get_Snr());
      set_SequenceNumber(rhs.get_SequenceNumber());
      set_IsMeasurementFragment(rhs.get_IsMeasurementFragment());
      set_Success(rhs.get_Success());
      set_Payload(rhs.get_Payload());
    }

    ~LoraReceive() override = default;

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

    LoraReceive& operator=(const LoraReceive& rhs)
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

    LoraReceive& operator=(const LoraReceive&& rhs) noexcept
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
    inline void set_Rssi(const EmbeddedProto::uint32& value) { Rssi_ = value; }
    inline void set_Rssi(const EmbeddedProto::uint32&& value) { Rssi_ = value; }
    inline EmbeddedProto::uint32& mutable_Rssi() { return Rssi_; }
    inline const EmbeddedProto::uint32& get_Rssi() const { return Rssi_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Rssi() const { return Rssi_.get(); }

    inline void clear_Snr() { Snr_.clear(); }
    inline void set_Snr(const EmbeddedProto::uint32& value) { Snr_ = value; }
    inline void set_Snr(const EmbeddedProto::uint32&& value) { Snr_ = value; }
    inline EmbeddedProto::uint32& mutable_Snr() { return Snr_; }
    inline const EmbeddedProto::uint32& get_Snr() const { return Snr_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Snr() const { return Snr_.get(); }

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

      if((0U != Rssi_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Rssi_.serialize_with_id(static_cast<uint32_t>(id::RSSI), buffer, false);
      }

      if((0U != Snr_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
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
      EmbeddedProto::uint32 Rssi_ = 0U;
      EmbeddedProto::uint32 Snr_ = 0U;
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

class AckMessage final: public ::EmbeddedProto::MessageInterface
{
  public:
    AckMessage() = default;
    AckMessage(const AckMessage& rhs )
    {
      set_SequenceNumber(rhs.get_SequenceNumber());
    }

    AckMessage(const AckMessage&& rhs ) noexcept
    {
      set_SequenceNumber(rhs.get_SequenceNumber());
    }

    ~AckMessage() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SEQUENCENUMBER = 1
    };

    AckMessage& operator=(const AckMessage& rhs)
    {
      set_SequenceNumber(rhs.get_SequenceNumber());
      return *this;
    }

    AckMessage& operator=(const AckMessage&& rhs) noexcept
    {
      set_SequenceNumber(rhs.get_SequenceNumber());
      return *this;
    }

    inline void clear_SequenceNumber() { SequenceNumber_.clear(); }
    inline void set_SequenceNumber(const EmbeddedProto::uint32& value) { SequenceNumber_ = value; }
    inline void set_SequenceNumber(const EmbeddedProto::uint32&& value) { SequenceNumber_ = value; }
    inline EmbeddedProto::uint32& mutable_SequenceNumber() { return SequenceNumber_; }
    inline const EmbeddedProto::uint32& get_SequenceNumber() const { return SequenceNumber_; }
    inline EmbeddedProto::uint32::FIELD_TYPE SequenceNumber() const { return SequenceNumber_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != SequenceNumber_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = SequenceNumber_.serialize_with_id(static_cast<uint32_t>(id::SEQUENCENUMBER), buffer, false);
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
          case id::SEQUENCENUMBER:
            return_value = SequenceNumber_.deserialize_check_type(buffer, wire_type);
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
      clear_SequenceNumber();

    }

    private:


      EmbeddedProto::uint32 SequenceNumber_ = 0U;

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
uint32_t loraReceiveMessage_Payload_LENGTH, 
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

        case id::LORARECEIVEMESSAGE:
          set_loraReceiveMessage(rhs.get_loraReceiveMessage());
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

        case id::LORARECEIVEMESSAGE:
          set_loraReceiveMessage(rhs.get_loraReceiveMessage());
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
      LORARECEIVEMESSAGE = 3,
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

        case id::LORARECEIVEMESSAGE:
          set_loraReceiveMessage(rhs.get_loraReceiveMessage());
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

        case id::LORARECEIVEMESSAGE:
          set_loraReceiveMessage(rhs.get_loraReceiveMessage());
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

    inline bool has_loraReceiveMessage() const
    {
      return id::LORARECEIVEMESSAGE == which_Body_;
    }
    inline void clear_loraReceiveMessage()
    {
      if(id::LORARECEIVEMESSAGE == which_Body_)
      {
        which_Body_ = id::NOT_SET;
        Body_.loraReceiveMessage_.~LoraReceive<loraReceiveMessage_Payload_LENGTH>();
      }
    }
    inline void set_loraReceiveMessage(const LoraReceive<loraReceiveMessage_Payload_LENGTH>& value)
    {
      if(id::LORARECEIVEMESSAGE != which_Body_)
      {
        init_Body(id::LORARECEIVEMESSAGE);
      }
      Body_.loraReceiveMessage_ = value;
    }
    inline void set_loraReceiveMessage(const LoraReceive<loraReceiveMessage_Payload_LENGTH>&& value)
    {
      if(id::LORARECEIVEMESSAGE != which_Body_)
      {
        init_Body(id::LORARECEIVEMESSAGE);
      }
      Body_.loraReceiveMessage_ = value;
    }
    inline LoraReceive<loraReceiveMessage_Payload_LENGTH>& mutable_loraReceiveMessage()
    {
      if(id::LORARECEIVEMESSAGE != which_Body_)
      {
        init_Body(id::LORARECEIVEMESSAGE);
      }
      return Body_.loraReceiveMessage_;
    }
    inline const LoraReceive<loraReceiveMessage_Payload_LENGTH>& get_loraReceiveMessage() const { return Body_.loraReceiveMessage_; }
    inline const LoraReceive<loraReceiveMessage_Payload_LENGTH>& loraReceiveMessage() const { return Body_.loraReceiveMessage_; }

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

        case id::LORARECEIVEMESSAGE:
          if(has_loraReceiveMessage() && (::EmbeddedProto::Error::NO_ERRORS == return_value))
          {
            return_value = Body_.loraReceiveMessage_.serialize_with_id(static_cast<uint32_t>(id::LORARECEIVEMESSAGE), buffer, true);
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

          case id::LORARECEIVEMESSAGE:
            return_value = deserialize_Body(id::LORARECEIVEMESSAGE, Body_.loraReceiveMessage_, buffer, wire_type);

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
        LoraReceive<loraReceiveMessage_Payload_LENGTH> loraReceiveMessage_;
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

          case id::LORARECEIVEMESSAGE:
            new(&Body_.loraReceiveMessage_) LoraReceive<loraReceiveMessage_Payload_LENGTH>;
            which_Body_ = id::LORARECEIVEMESSAGE;
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
          case id::LORARECEIVEMESSAGE:
            Body_.loraReceiveMessage_.~LoraReceive<loraReceiveMessage_Payload_LENGTH>(); // NOSONAR Unions require this.
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

class SpreadingFactorConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    SpreadingFactorConfig() = default;
    SpreadingFactorConfig(const SpreadingFactorConfig& rhs )
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
    }

    SpreadingFactorConfig(const SpreadingFactorConfig&& rhs ) noexcept
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
    }

    ~SpreadingFactorConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      SPREADINGFACTORRX = 1,
      SPREADINGFACTORTX = 2
    };

    SpreadingFactorConfig& operator=(const SpreadingFactorConfig& rhs)
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
      return *this;
    }

    SpreadingFactorConfig& operator=(const SpreadingFactorConfig&& rhs) noexcept
    {
      set_spreadingFactorRx(rhs.get_spreadingFactorRx());
      set_spreadingFactorTx(rhs.get_spreadingFactorTx());
      return *this;
    }

    inline void clear_spreadingFactorRx() { spreadingFactorRx_.clear(); }
    inline void set_spreadingFactorRx(const EmbeddedProto::uint32& value) { spreadingFactorRx_ = value; }
    inline void set_spreadingFactorRx(const EmbeddedProto::uint32&& value) { spreadingFactorRx_ = value; }
    inline EmbeddedProto::uint32& mutable_spreadingFactorRx() { return spreadingFactorRx_; }
    inline const EmbeddedProto::uint32& get_spreadingFactorRx() const { return spreadingFactorRx_; }
    inline EmbeddedProto::uint32::FIELD_TYPE spreadingFactorRx() const { return spreadingFactorRx_.get(); }

    inline void clear_spreadingFactorTx() { spreadingFactorTx_.clear(); }
    inline void set_spreadingFactorTx(const EmbeddedProto::uint32& value) { spreadingFactorTx_ = value; }
    inline void set_spreadingFactorTx(const EmbeddedProto::uint32&& value) { spreadingFactorTx_ = value; }
    inline EmbeddedProto::uint32& mutable_spreadingFactorTx() { return spreadingFactorTx_; }
    inline const EmbeddedProto::uint32& get_spreadingFactorTx() const { return spreadingFactorTx_; }
    inline EmbeddedProto::uint32::FIELD_TYPE spreadingFactorTx() const { return spreadingFactorTx_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != spreadingFactorRx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = spreadingFactorRx_.serialize_with_id(static_cast<uint32_t>(id::SPREADINGFACTORRX), buffer, false);
      }

      if((0U != spreadingFactorTx_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = spreadingFactorTx_.serialize_with_id(static_cast<uint32_t>(id::SPREADINGFACTORTX), buffer, false);
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
          case id::SPREADINGFACTORRX:
            return_value = spreadingFactorRx_.deserialize_check_type(buffer, wire_type);
            break;

          case id::SPREADINGFACTORTX:
            return_value = spreadingFactorTx_.deserialize_check_type(buffer, wire_type);
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
      clear_spreadingFactorRx();
      clear_spreadingFactorTx();

    }

    private:


      EmbeddedProto::uint32 spreadingFactorRx_ = 0U;
      EmbeddedProto::uint32 spreadingFactorTx_ = 0U;

};

class SequenceRequestConfig final: public ::EmbeddedProto::MessageInterface
{
  public:
    SequenceRequestConfig() = default;
    SequenceRequestConfig(const SequenceRequestConfig& rhs )
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
    }

    SequenceRequestConfig(const SequenceRequestConfig&& rhs ) noexcept
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
    }

    ~SequenceRequestConfig() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      MESSAGECOUNT = 1,
      INTERVAL = 2,
      DEVICEID = 3
    };

    SequenceRequestConfig& operator=(const SequenceRequestConfig& rhs)
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
      return *this;
    }

    SequenceRequestConfig& operator=(const SequenceRequestConfig&& rhs) noexcept
    {
      set_MessageCount(rhs.get_MessageCount());
      set_Interval(rhs.get_Interval());
      set_DeviceId(rhs.get_DeviceId());
      return *this;
    }

    inline void clear_MessageCount() { MessageCount_.clear(); }
    inline void set_MessageCount(const EmbeddedProto::uint32& value) { MessageCount_ = value; }
    inline void set_MessageCount(const EmbeddedProto::uint32&& value) { MessageCount_ = value; }
    inline EmbeddedProto::uint32& mutable_MessageCount() { return MessageCount_; }
    inline const EmbeddedProto::uint32& get_MessageCount() const { return MessageCount_; }
    inline EmbeddedProto::uint32::FIELD_TYPE MessageCount() const { return MessageCount_.get(); }

    inline void clear_Interval() { Interval_.clear(); }
    inline void set_Interval(const EmbeddedProto::uint32& value) { Interval_ = value; }
    inline void set_Interval(const EmbeddedProto::uint32&& value) { Interval_ = value; }
    inline EmbeddedProto::uint32& mutable_Interval() { return Interval_; }
    inline const EmbeddedProto::uint32& get_Interval() const { return Interval_; }
    inline EmbeddedProto::uint32::FIELD_TYPE Interval() const { return Interval_.get(); }

    inline void clear_DeviceId() { DeviceId_.clear(); }
    inline void set_DeviceId(const EmbeddedProto::uint32& value) { DeviceId_ = value; }
    inline void set_DeviceId(const EmbeddedProto::uint32&& value) { DeviceId_ = value; }
    inline EmbeddedProto::uint32& mutable_DeviceId() { return DeviceId_; }
    inline const EmbeddedProto::uint32& get_DeviceId() const { return DeviceId_; }
    inline EmbeddedProto::uint32::FIELD_TYPE DeviceId() const { return DeviceId_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0U != MessageCount_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = MessageCount_.serialize_with_id(static_cast<uint32_t>(id::MESSAGECOUNT), buffer, false);
      }

      if((0U != Interval_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = Interval_.serialize_with_id(static_cast<uint32_t>(id::INTERVAL), buffer, false);
      }

      if((0U != DeviceId_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = DeviceId_.serialize_with_id(static_cast<uint32_t>(id::DEVICEID), buffer, false);
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
          case id::MESSAGECOUNT:
            return_value = MessageCount_.deserialize_check_type(buffer, wire_type);
            break;

          case id::INTERVAL:
            return_value = Interval_.deserialize_check_type(buffer, wire_type);
            break;

          case id::DEVICEID:
            return_value = DeviceId_.deserialize_check_type(buffer, wire_type);
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
      clear_MessageCount();
      clear_Interval();
      clear_DeviceId();

    }

    private:


      EmbeddedProto::uint32 MessageCount_ = 0U;
      EmbeddedProto::uint32 Interval_ = 0U;
      EmbeddedProto::uint32 DeviceId_ = 0U;

};

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

#endif // DEVICE_MESSAGES_H