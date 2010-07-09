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

#include "ValueType.h"

#include <iostream>
#include <stdexcept>

namespace config
{
//-----------------------------------------------------------------------------
    CONFIG_EXPORT std::ostream& operator << (std::ostream& os, ValueType vt)
    {
        switch (vt)
        {
            case VT_EMPTY:
                os << "VT_EMPTY";                
                break;
            case VT_BOOL:
                os << "VT_BOOL";
                break;
            case VT_INT:
                os << "VT_INT";
                break;
            case VT_UNSIGNED_INT:
                os << "VT_UNSIGNED_INT";
                break;
            case VT_FLOAT:
                os << "VT_FLOAT";
                break;
            case VT_DOUBLE:
                os << "VT_DOUBLE";
                break;
            case VT_STRING:
                os << "VT_STRING";
                break;
            default:
                os << static_cast<unsigned int>(vt);
                break;
        }
        return os;
    }
}
   