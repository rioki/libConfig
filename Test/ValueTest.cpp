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

#include <libConfig/Value.h>

#include <UnitTest++/UnitTest++.h>

SUITE(ValueTest)
{
//-----------------------------------------------------------------------------
    TEST(is_default_constructible)
    {
        config::Value value;
    }

//-----------------------------------------------------------------------------    
    TEST(build_empty)
    {
        config::Value value;
        CHECK_EQUAL(config::VT_EMPTY, value.get_type());
    }

//-----------------------------------------------------------------------------       
    TEST(build_int)
    {
        config::Value value(123);
        CHECK_EQUAL(config::VT_INT, value.get_type());
        
        int long_value = value;
        CHECK_EQUAL(123, long_value);
    }

//-----------------------------------------------------------------------------    
    TEST(build_unsigned_int)
    {
        config::Value value(123u);
        CHECK_EQUAL(config::VT_UNSIGNED_INT, value.get_type());
        
        unsigned int long_value = value;
        CHECK_EQUAL(123u, long_value);
    }  

//-----------------------------------------------------------------------------    
    TEST(build_float)
    {
        config::Value value(123.0f);
        CHECK_EQUAL(config::VT_FLOAT, value.get_type());
        
        float float_value = value;
        CHECK_EQUAL(123.0, float_value);
    }  

//-----------------------------------------------------------------------------    
    TEST(build_string)
    {        
        config::Value value("Hello World");
        CHECK_EQUAL(config::VT_STRING, value.get_type());
        
        std::string string_value = value;
        CHECK_EQUAL("Hello World", string_value);
    } 

//-----------------------------------------------------------------------------    
    TEST(build_bool)
    {
        config::Value value(true);
        CHECK_EQUAL(config::VT_BOOL, value.get_type());
        
        bool bool_value = value;
        CHECK_EQUAL(true, bool_value);
    } 
}