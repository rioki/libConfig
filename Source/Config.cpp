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


#include "Config.h"

#include <string>
#include <fstream>
#include <sstream>

#include "ConfigLexer.h"
#include "ConfigParser.hpp"
#include "utils.h"

namespace config
{    
//-----------------------------------------------------------------------------
    bool Config::has_value(const std::string& section, const std::string& key) const
    {
        std::map<std::string, Section>::const_iterator sec_iter = sections.find(section);
        if (sec_iter != sections.end())
        {
            const Section& sec = sec_iter->second;
            
            std::map<std::string, Value>::const_iterator val_iter = sec.values.find(key);
            if (val_iter != sec.values.end())
            {
                return true;
            }
            else
            {
                throw false;
            }
        }
        else
        {
            return false;
        }
    }

//-----------------------------------------------------------------------------
    const Value& Config::get_value(const std::string& section, const std::string& key) const
    {        
        std::map<std::string, Section>::const_iterator sec_iter = sections.find(section);
        if (sec_iter != sections.end())
        {
            const Section& sec = sec_iter->second;
            
            std::map<std::string, Value>::const_iterator val_iter = sec.values.find(key);
            if (val_iter != sec.values.end())
            {
                return val_iter->second;
            }
            else
            {
                throw std::logic_error(compose("Key %1 not defined in section %0.", section, key));
            }
        }
        else
        {
            throw std::logic_error(compose("Section %0 not defined in config.", section));
        }
    }

//-----------------------------------------------------------------------------    
    void Config::set_value(const std::string& section, const std::string& key, const Value& value)
    {
        sections[section].values[key] = value;
    }

//-----------------------------------------------------------------------------    
    void Config::read_file(const std::string& filename)
    {
        
        std::ifstream input(filename.c_str());
        std::stringstream error;
        ConfigLexer lexer(input, error);
        yy::ConfigParser parser(lexer, error, *this, filename);
        // TODO check result fo parser()
        if (parser.parse() == 1)
        {
            throw std::runtime_error(error.str());
        }
    }

//-----------------------------------------------------------------------------    
    void Config::write_file(const std::string& filename) const
    {
        std::ofstream output(filename.c_str());
        if (output.bad())
        {
            throw std::runtime_error(compose("Failed to open %0 for reading.", filename));
        }
    
        std::map<std::string, Section>::const_iterator sec_iter = sections.begin();
        while (sec_iter != sections.end())    
        {
            const Section& section = sec_iter->second;
            
            output << "[" << sec_iter->first << "]" << std::endl;
            output << std::endl;
            
            std::map<std::string, Value>::const_iterator val_iter = section.values.begin();
            while (val_iter != section.values.end())
            {
                output << val_iter->first << " = " << val_iter->second << std::endl;
            
                val_iter++;
            }
            
            output << std::endl;
            
            sec_iter++;
        }        
    }

//-----------------------------------------------------------------------------    
    CONFIG_EXPORT std::string get_version()
    {
        return LIBCONFIG_VERSION;
    }
}
