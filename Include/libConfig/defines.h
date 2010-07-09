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

#ifndef _LIBCONFIG_DEFINES_H_
#define _LIBCONFIG_DEFINES_H_

/**
 * The verion of the library.
 **/
#define LIBCONFIG_VERSION "0.1.0"

#ifdef LIBCONFIG_EXPORTS
#define CONFIG_EXPORT __declspec(dllexport)
#else
#define CONFIG_EXPORT __declspec(dllimport)
#endif

#endif
