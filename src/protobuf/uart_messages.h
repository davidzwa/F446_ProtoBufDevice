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
#ifndef UART_MESSAGES_H
#define UART_MESSAGES_H

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


class Command final: public ::EmbeddedProto::MessageInterface
{
  public:
    Command() = default;
    Command(const Command& rhs )
    {
      set_button(rhs.get_button());
      set_value(rhs.get_value());
    }

    Command(const Command&& rhs ) noexcept
    {
      set_button(rhs.get_button());
      set_value(rhs.get_value());
    }

    ~Command() override = default;

    enum class Buttons : uint32_t
    {
      DoNothing = 0,
      Up = 1,
      Down = 2,
      Right = 4,
      Left = 3,
      Grab = 5,
      Stop = 6
    };

    enum class id : uint32_t
    {
      NOT_SET = 0,
      BUTTON = 1,
      VALUE = 2
    };

    Command& operator=(const Command& rhs)
    {
      set_button(rhs.get_button());
      set_value(rhs.get_value());
      return *this;
    }

    Command& operator=(const Command&& rhs) noexcept
    {
      set_button(rhs.get_button());
      set_value(rhs.get_value());
      return *this;
    }

    inline void clear_button() { button_ = static_cast<Buttons>(0); }
    inline void set_button(const Buttons& value) { button_ = value; }
    inline void set_button(const Buttons&& value) { button_ = value; }
    inline const Buttons& get_button() const { return button_; }
    inline Buttons button() const { return button_; }

    inline void clear_value() { value_.clear(); }
    inline void set_value(const EmbeddedProto::uint32& value) { value_ = value; }
    inline void set_value(const EmbeddedProto::uint32&& value) { value_ = value; }
    inline EmbeddedProto::uint32& mutable_value() { return value_; }
    inline const EmbeddedProto::uint32& get_value() const { return value_; }
    inline EmbeddedProto::uint32::FIELD_TYPE value() const { return value_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((static_cast<Buttons>(0) != button_) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        EmbeddedProto::uint32 value = 0;
        value.set(static_cast<uint32_t>(button_));
        return_value = value.serialize_with_id(static_cast<uint32_t>(id::BUTTON), buffer, false);
      }

      if((0U != value_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = value_.serialize_with_id(static_cast<uint32_t>(id::VALUE), buffer, false);
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
          case id::BUTTON:
            if(::EmbeddedProto::WireFormatter::WireType::VARINT == wire_type)
            {
              uint32_t value = 0;
              return_value = ::EmbeddedProto::WireFormatter::DeserializeVarint(buffer, value);
              if(::EmbeddedProto::Error::NO_ERRORS == return_value)
              {
                set_button(static_cast<Buttons>(value));
              }
            }
            else
            {
              // Wire type does not match field.
              return_value = ::EmbeddedProto::Error::INVALID_WIRETYPE;
            }
            break;

          case id::VALUE:
            return_value = value_.deserialize_check_type(buffer, wire_type);
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
      clear_button();
      clear_value();

    }

    private:


      Buttons button_ = static_cast<Buttons>(0);
      EmbeddedProto::uint32 value_ = 0U;

};

class Reply final: public ::EmbeddedProto::MessageInterface
{
  public:
    Reply() = default;
    Reply(const Reply& rhs )
    {
      set_x_pos(rhs.get_x_pos());
      set_y_pos(rhs.get_y_pos());
      set_price(rhs.get_price());
    }

    Reply(const Reply&& rhs ) noexcept
    {
      set_x_pos(rhs.get_x_pos());
      set_y_pos(rhs.get_y_pos());
      set_price(rhs.get_price());
    }

    ~Reply() override = default;

    enum class id : uint32_t
    {
      NOT_SET = 0,
      X_POS = 1,
      Y_POS = 2,
      PRICE = 3
    };

    Reply& operator=(const Reply& rhs)
    {
      set_x_pos(rhs.get_x_pos());
      set_y_pos(rhs.get_y_pos());
      set_price(rhs.get_price());
      return *this;
    }

    Reply& operator=(const Reply&& rhs) noexcept
    {
      set_x_pos(rhs.get_x_pos());
      set_y_pos(rhs.get_y_pos());
      set_price(rhs.get_price());
      return *this;
    }

    inline void clear_x_pos() { x_pos_.clear(); }
    inline void set_x_pos(const EmbeddedProto::int32& value) { x_pos_ = value; }
    inline void set_x_pos(const EmbeddedProto::int32&& value) { x_pos_ = value; }
    inline EmbeddedProto::int32& mutable_x_pos() { return x_pos_; }
    inline const EmbeddedProto::int32& get_x_pos() const { return x_pos_; }
    inline EmbeddedProto::int32::FIELD_TYPE x_pos() const { return x_pos_.get(); }

    inline void clear_y_pos() { y_pos_.clear(); }
    inline void set_y_pos(const EmbeddedProto::int32& value) { y_pos_ = value; }
    inline void set_y_pos(const EmbeddedProto::int32&& value) { y_pos_ = value; }
    inline EmbeddedProto::int32& mutable_y_pos() { return y_pos_; }
    inline const EmbeddedProto::int32& get_y_pos() const { return y_pos_; }
    inline EmbeddedProto::int32::FIELD_TYPE y_pos() const { return y_pos_.get(); }

    inline void clear_price() { price_.clear(); }
    inline void set_price(const EmbeddedProto::boolean& value) { price_ = value; }
    inline void set_price(const EmbeddedProto::boolean&& value) { price_ = value; }
    inline EmbeddedProto::boolean& mutable_price() { return price_; }
    inline const EmbeddedProto::boolean& get_price() const { return price_; }
    inline EmbeddedProto::boolean::FIELD_TYPE price() const { return price_.get(); }


    ::EmbeddedProto::Error serialize(::EmbeddedProto::WriteBufferInterface& buffer) const override
    {
      ::EmbeddedProto::Error return_value = ::EmbeddedProto::Error::NO_ERRORS;

      if((0 != x_pos_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = x_pos_.serialize_with_id(static_cast<uint32_t>(id::X_POS), buffer, false);
      }

      if((0 != y_pos_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = y_pos_.serialize_with_id(static_cast<uint32_t>(id::Y_POS), buffer, false);
      }

      if((false != price_.get()) && (::EmbeddedProto::Error::NO_ERRORS == return_value))
      {
        return_value = price_.serialize_with_id(static_cast<uint32_t>(id::PRICE), buffer, false);
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
          case id::X_POS:
            return_value = x_pos_.deserialize_check_type(buffer, wire_type);
            break;

          case id::Y_POS:
            return_value = y_pos_.deserialize_check_type(buffer, wire_type);
            break;

          case id::PRICE:
            return_value = price_.deserialize_check_type(buffer, wire_type);
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
      clear_x_pos();
      clear_y_pos();
      clear_price();

    }

    private:


      EmbeddedProto::int32 x_pos_ = 0;
      EmbeddedProto::int32 y_pos_ = 0;
      EmbeddedProto::boolean price_ = false;

};

#endif // UART_MESSAGES_H
