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


#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>
#include <map>

#include "defines.h"
#include "Value.h"

// warning C4251: 'config::Config::sections' : class 'std::map<_Kty,_Ty>' needs to have dll-interface
// to be used by clients of class 'config::Config'
#pragma warning(disable: 4251)

namespace config
{
    /**
     * Configuration
     **/
    class CONFIG_EXPORT Config 
    {
    public:            
        
        /**
         * Check if a given value is defined.
         **/
        bool has_value(const std::string& section, const std::string& key) const;
        
        /**
         * Get a value from the configuration.
         **/
        const Value& get_value(const std::string& section, const std::string& key) const;
        
        /**
         * Set a configuration value.
         **/
        void set_value(const std::string& section, const std::string& key, const Value& value);
        
        /**
         * Read a file.
         **/
        void read_file(const std::string& filename);
        
        /**
         * Write a file.
         **/
        void write_file(const std::string& filename) const;
                
    private:    
        struct Section
        {
            std::map<std::string, Value> values;
        };
    
        std::map<std::string, Section> sections;     
    };
    
    /**
     * Get the version string the program was linked to.
     *
     * @return
     * The version of the library.
     *
     * @see 
     * LIBCONFIG_VERSION
     **/
    CONFIG_EXPORT std::string get_version();
}

#endif
