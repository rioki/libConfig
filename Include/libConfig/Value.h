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

#ifndef _LIBCONFIG_VALUE_H_
#define _LIBCONFIG_VALUE_H_

#include <string>
#include <iosfwd>

#include "defines.h"
#include "ValueType.h"

namespace config
{
    /**
     * Generic Polymorphic Value
     *
     * A Value object can be used to hold all sorts of POD types. 
     * It is used when defining concrete types or strings just
     * is not practicable.
     **/
    class CONFIG_EXPORT Value 
    {
    public:
        /**
         * Create a empty value.
         **/
        Value();                
        
        /**
         * Create a int value.
         **/
        Value(bool value);
        
        /**
         * Create a int value.
         **/
        Value(int value);
        
        /**
         * Create a unsigned int value.
         **/
        Value(unsigned int value);
        
        /**
         * Create a float value.
         **/
        Value(float value);
        
        /**
         * Create a double value.
         **/
        Value(double value);
        
        /**
         * Create a string value.
         **/
        Value(const std::string& value);
        Value(const char* value);
        
        /**
         * Copy Constructor
         **/
        Value(const Value& orig);
        
        /**
         * Destructor
         **/
        ~Value();
        
        /**
         * Assignment operator.
         **/
        const Value& operator = (const Value& orig);
        
        /**
         * Get the type of the value.
         **/
        ValueType get_type() const;
        
        /**
         * Cast to bool.
         **/
        operator bool () const;
        
        /**
         * Cast to long.
         **/
        operator int () const;
        
        /**
         * Cast to unsigned long.
         **/
        operator unsigned int () const;   
        
        /**
         * Cast to float.
         **/
        operator float () const;   
        
        /**
         * Cast to double.
         **/
        operator double () const;  
        
        /**
         * Cast to string.
         **/
        operator std::string () const;       
        
        /**
         * Convert value to string.
         **/
        std::string to_string() const;   
        
        /**
         * Read string.
         **/
        void from_string(const std::string& str);
        
    private:
        ValueType type;
        
        union
        {   
            bool bool_value;
            int int_value;
            unsigned int unsigned_int_value;            
            float float_value;
            double double_value;
            char* string_value;
        };        
        
        void clear();
        void copy(const Value& orig);
    };
    
    CONFIG_EXPORT std::ostream& operator << (std::ostream& os, const Value& value);
}

#endif
