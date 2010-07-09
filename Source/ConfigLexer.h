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

#ifndef _LIBCONFIG_CONFIG_LEXER_H_
#define _LIBCONFIG_CONFIG_LEXER_H_

#if ! defined(_SKIP_YYFLEXLEXER_)
#include "FlexLexer.h"
#endif

#include <iosfwd>
#include "ConfigParser.hpp"

class ConfigLexer : public yyFlexLexer
{
public:
    typedef yy::ConfigParser::token token;
    typedef yy::ConfigParser::token_type token_type;
    typedef yy::ConfigParser::semantic_type semantic_type;
    typedef yy::ConfigParser::location_type location_type;

    ConfigLexer(std::istream& input, std::ostream& error);    
        
    int yylex(semantic_type* yylval, location_type* yylloc);
    
    virtual int yylex();
            
private:
    semantic_type* yylval;
    location_type* yylloc;                
    
    std::ostream& error;
    
    ConfigLexer(const ConfigLexer&);
    const ConfigLexer& operator = (const ConfigLexer&);
};

#endif
