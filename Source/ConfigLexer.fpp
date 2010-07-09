/*
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
*/

   
%option c++
%option 8bit
%option warn
%option yyclass="ConfigLexer" 
%option outfile="ConfigLexer.cpp"
%option nodefault


%{
#define _SKIP_YYFLEXLEXER_
#include "ConfigLexer.h"

#define YY_NO_UNISTD_H
#include "ConfigParser.hpp"

#define yyterminate() return token::END
#define YY_USER_ACTION  yylloc->columns(yyleng);

#include <cassert>

%}

nl              (\n)|(\r\n)|(\r)
ws              [ \t\v]*
comment         "#"[^\n\r]*

indentifier     [a-zA-Z_][a-zA-Z0-9_]*
string          \"([^\"\n\r]|(\\\"))*\"
dec_integer     ([1-9][0-9]*)|0
hex_integer     ("0x"|"0X")[0-9a-fA-F]+
oct_integer     0[0-7]+

%%

%{
yylloc->step();
%}

{comment}       /* skip */
{ws}            /* skip */
{nl}            yylloc->lines(1); yylloc->step();

"["             return token::LEFT_SQUARE_BRAKET;
"]"             return token::RIGHT_SQUARE_BRAKET;
"="             return token::EQUAL;

"true"          {
                    yylval->value = new config::Value(true);                    
                    return token::BOOLEAN;
                }

"false"         {
                    yylval->value = new config::Value(false);                    
                    return token::BOOLEAN;
                }

{indentifier}   {
                    yylval->string = new std::string(YYText());
                    return token::IDENTIFIER;
                }
                
{string}        {
                    std::string text = YYText();
                    assert(text.size() >= 2);
                    yylval->value = new config::Value(text.substr(1, text.size() - 2));
                    return token::STRING;
                }
                
{dec_integer}   {
                    yylval->value = new config::Value(strtol(YYText(), NULL, 10));                    
                    return token::INTEGER;
                }

{hex_integer}   {
                    yylval->value = new config::Value(strtol(YYText() + 2, NULL, 16));
                    return token::INTEGER;
                }
                
{oct_integer}   {
                    yylval->value = new config::Value(strtol(YYText() + 1, NULL, 8));                    
                    return token::INTEGER;
                }

%%

//-----------------------------------------------------------------------------
ConfigLexer::ConfigLexer(std::istream& input, std::ostream& e)
: yylval(NULL), yylloc(NULL), error(e)
{
    switch_streams(&input, NULL);
}

//-----------------------------------------------------------------------------        
int ConfigLexer::yylex(semantic_type* _yylval, location_type* _yylloc)
{
    this->yylval = _yylval;
    this->yylloc = _yylloc;
    return yylex();
}

//-----------------------------------------------------------------------------
int yyFlexLexer::yywrap()
{
    return 1;
}