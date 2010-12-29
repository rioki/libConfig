//
// libConfig
// Copyright 2010 Sean Farrell
//
// This file is part of libConfig.
//
// libConfig is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// libConfig is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with libConfig. If not, see <http://www.gnu.org/licenses/>.
//

#include "Value.h"

#include <cstdlib>
#include <cstring>
#include <cassert>
#include <memory>

#include "utils.h"

namespace config
{
//-----------------------------------------------------------------------------
    Value::Value()
    : type(VT_EMPTY) {}

//-----------------------------------------------------------------------------
    Value::Value(bool value)
    : type(VT_BOOL), bool_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(short value)
    : type(VT_INT), int_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(unsigned short value)
    : type(VT_UNSIGNED_INT), unsigned_int_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(int value)
    : type(VT_INT), int_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(unsigned int value)
    : type(VT_UNSIGNED_INT), unsigned_int_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(long value)
    : type(VT_INT), int_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(unsigned long value)
    : type(VT_UNSIGNED_INT), unsigned_int_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(float value)
    : type(VT_FLOAT), float_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(double value)
    : type(VT_DOUBLE), double_value(value) {}

//-----------------------------------------------------------------------------
    Value::Value(const std::string& value)
    : type(VT_STRING), string_value(_strdup(value.c_str())) {}

//-----------------------------------------------------------------------------
    Value::Value(const char* value)
    : type(VT_STRING), string_value(_strdup(value)) {}

//-----------------------------------------------------------------------------
    Value::Value(const Value& orig)
    : type(VT_EMPTY)
    {
        copy(orig);
    }

//-----------------------------------------------------------------------------
    Value::~Value()
    {
        clear();
    }

//-----------------------------------------------------------------------------
    ValueType Value::get_type() const
    {
        return type;
    }

//-----------------------------------------------------------------------------
    const Value& Value::operator = (const Value& orig)
    {
        if (this != & orig)
        {
            copy(orig);
        }
        return *this;
    }

    // NOTE:
    // The exact match check for the type may be relaxed later,
    // when type conversion is implemented.

//-----------------------------------------------------------------------------
    Value::operator bool () const
    {
        assert(type == VT_BOOL);
        return bool_value;
    }

//-----------------------------------------------------------------------------
    Value::operator int () const
    {
        assert(type == VT_UNSIGNED_INT || type == VT_INT);
        if (VT_UNSIGNED_INT)
            return unsigned_int_value;
        else if (VT_INT)
            return int_value;
        else
            return 0;
    }

//-----------------------------------------------------------------------------
    Value::operator unsigned int () const
    {
        assert(type == VT_UNSIGNED_INT || type == VT_INT);
        if (VT_UNSIGNED_INT)
            return unsigned_int_value;
        else if (VT_INT)
            return int_value;
        else
            return 0;
    }

//-----------------------------------------------------------------------------
    Value::operator float () const
    {
        assert(type == VT_FLOAT || type == VT_DOUBLE);
        if (VT_FLOAT)
            return float_value;
        else if (VT_DOUBLE)
            return static_cast<float>(double_value);
        else
            return 0;
    }

//-----------------------------------------------------------------------------
    Value::operator double () const
    {
        assert(type == VT_FLOAT || type == VT_DOUBLE);
        if (VT_FLOAT)
            return float_value;
        else if (VT_DOUBLE)
            return double_value;
        else
            return 0;
    }

//-----------------------------------------------------------------------------
    Value::operator std::string () const
    {
        assert(type == VT_STRING);
        return string_value;
    }

//-----------------------------------------------------------------------------
    std::string Value::to_string() const
    {
        switch (type)
        {
            case VT_EMPTY:
                return "";
            case VT_BOOL:
                return ::config::to_string(bool_value);
            case VT_INT:
                return ::config::to_string(int_value);
            case VT_UNSIGNED_INT:
                return ::config::to_string(unsigned_int_value);
            case VT_FLOAT:
                return ::config::to_string(float_value);
            case VT_DOUBLE:
                return ::config::to_string(double_value);
            case VT_STRING:
                return compose("\"%0\"", string_value);
            default:
                throw std::invalid_argument(compose("unknown value type %0", type));
                return "";
        }
    }

//-----------------------------------------------------------------------------
    void Value::from_string(const std::string& str)
    {
        switch (type)
        {
            case VT_EMPTY:
                assert(str == "");
                break;
            case VT_BOOL:
                bool_value = ::config::from_string<bool>(str);
                break;
            case VT_INT:
                int_value = ::config::from_string<int>(str);
                break;
            case VT_UNSIGNED_INT:
                unsigned_int_value = ::config::from_string<unsigned int>(str);
                break;
            case VT_FLOAT:
                float_value = ::config::from_string<float>(str);
                break;
            case VT_DOUBLE:
                double_value = ::config::from_string<double>(str);
                break;
            case VT_STRING:
                assert(str[0] == '"');
                assert(str[str.size() - 1] == '"');
                string_value = _strdup(str.substr(1, str.size() - 2).c_str());
                break;
            default:
                throw std::invalid_argument(compose("unknown value type %0", type));
                break;
        }
    }

//-----------------------------------------------------------------------------
    void Value::clear()
    {
        if (type == VT_STRING)
        {
            std::free(string_value);
        }
        type = VT_EMPTY;
    }

//-----------------------------------------------------------------------------
    void Value::copy(const Value& orig)
    {
        assert(this != &orig);

        clear();

        switch (orig.type)
        {
            case VT_EMPTY:
                /* do nothing */
                break;
            case VT_BOOL:
                bool_value = orig.bool_value;
                break;
            case VT_INT:
                int_value = orig.int_value;
                break;
            case VT_UNSIGNED_INT:
                unsigned_int_value = orig.unsigned_int_value;
                break;
            case VT_FLOAT:
                float_value = orig.float_value;
                break;
            case VT_DOUBLE:
                double_value = orig.double_value;
                break;
            case VT_STRING:
                string_value = _strdup(orig.string_value);
                break;
            default:
                throw std::invalid_argument(compose("unknown value type %0", orig.type));
                break;
        }

        type = orig.type;
    }

//-----------------------------------------------------------------------------
    CONFIG_EXPORT std::ostream& operator << (std::ostream& os, const Value& value)
    {
        os << value.to_string();
        return os;
    }
}
