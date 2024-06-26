/** @file
 * @brief convert a string to UTF-8 encoding.
 */
/* Copyright (C) 2006,2021,2023 Olly Betts
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 */

#ifndef OMEGA_INCLUDED_UTF8CONVERT_H
#define OMEGA_INCLUDED_UTF8CONVERT_H

#include <string>
#include <string_view>

// Internal helper.
bool convert_to_utf8_(std::string_view text, const std::string& charset,
		      std::string& output);

// Convert in-place (avoids copy if already UTF-8).
inline void convert_to_utf8(std::string& text, const std::string& charset)
{
    (void)convert_to_utf8_(text, charset, text);
}

inline void convert_to_utf8(std::string_view text, const std::string& charset,
			    std::string& output)
{
    if (!convert_to_utf8_(text, charset, output))
	output = text;
}

#endif // OMEGA_INCLUDED_UTF8CONVERT_H
