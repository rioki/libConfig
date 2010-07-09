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

#include <libConfig/Config.h>

#include <fstream>
#include <UnitTest++/UnitTest++.h>

SUITE(ConfigTest)
{
//-----------------------------------------------------------------------------
    std::string read_file(const std::string& filename)
    {
        std::string result;        
        std::ifstream input(filename.c_str());        
               
        char c = input.get();
        while (c != EOF)
        {
            result.push_back(c);
            c = input.get();
        }
        return result;
    }

//-----------------------------------------------------------------------------    
    void write_file(const std::string& filename, const std::string& contents)
    {
        std::ofstream output(filename.c_str());        
        output << contents;
    }

//-----------------------------------------------------------------------------
    TEST(version)
    {
        CHECK_EQUAL(LIBCONFIG_VERSION, config::get_version());
    }

//-----------------------------------------------------------------------------
    TEST(is_default_constructible)
    {
        config::Config conf;
    }

//-----------------------------------------------------------------------------    
    TEST(set_get_loop_string)
    {
        config::Config conf;
        
        conf.set_value("Graphic", "width", config::Value(800));
        
        CHECK(conf.has_value("Graphic", "width"));
        
        config::Value width = conf.get_value("Graphic", "width");                
        CHECK_EQUAL(config::VT_INT, width.get_type());
        CHECK_EQUAL(800, static_cast<int>(width));
    }

//-----------------------------------------------------------------------------
    TEST(write_config_file)
    {
        config::Config conf;
        
        conf.set_value("Graphic", "width", config::Value(800));
        conf.set_value("Graphic", "height", config::Value(600));        
        conf.set_value("Graphic", "fov", config::Value(90.0f));
        conf.set_value("Debug", "log", config::Value("Test.log"));
        conf.set_value("Debug", "verbose", config::Value(true));
        
        conf.write_file("write_config_file.conf");
        
        std::string config_file = read_file("write_config_file.conf");
        
        const char* ref =
            "[Debug]\n"
            "\n"
            "log = \"Test.log\"\n"
            "verbose = true\n"
            "\n"
            "[Graphic]\n"
            "\n"
            "fov = 90\n"
            "height = 600\n"
            "width = 800\n"
            "\n";
        
        CHECK_EQUAL(ref, config_file);
        
        std::remove("write_config_file.conf");
    }

//-----------------------------------------------------------------------------    
    TEST(read_int_values)
    {
        const char* conf_file =
            "[Debug]\n"
            "\n"
            "log = \"Test.log\"\n"
            "verbose = true\n"
            "\n"
            "[Graphic]\n"
            "\n"
            "fov = 90\n"
            "height = 600\n"
            "width = 800\n"
            "\n";
        write_file("read_int_values.conf", conf_file);
        
        config::Config conf;
        
        conf.read_file("read_int_values.conf");
        
        CHECK(conf.has_value("Graphic", "width"));
        CHECK(conf.has_value("Graphic", "height"));
        
        config::Value width = conf.get_value("Graphic", "width");
        config::Value height = conf.get_value("Graphic", "height");
        
        CHECK_EQUAL(config::VT_INT, width.get_type());
        CHECK_EQUAL(config::VT_INT, height.get_type());
        
        CHECK_EQUAL(800, static_cast<int>(width));
        CHECK_EQUAL(600, static_cast<int>(height));
                                
        std::remove("read_int_values.conf");
    }
}