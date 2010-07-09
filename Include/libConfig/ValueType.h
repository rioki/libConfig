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

#ifndef _LIBCONFIG_VALUE_TYPE_H_
#define _LIBCONFIG_VALUE_TYPE_H_

#include <iosfwd>

#include "defines.h"

namespace config
{
    /**
     * Value Type
     **/
    enum ValueType
    {
        VT_EMPTY,
        VT_BOOL,
        VT_INT,
        VT_UNSIGNED_INT,
        VT_FLOAT,
        VT_DOUBLE,
        VT_STRING
    };
    
    CONFIG_EXPORT std::ostream& operator << (std::ostream& os, ValueType vt);
}

#endif
