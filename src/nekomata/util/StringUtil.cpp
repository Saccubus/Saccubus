/**
 * Nekomata
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <auto_ptr.h>
#include <cstring>
#include <cstdlib>
#include <nekomata/logging/Exception.h>
#include "StringUtil.h"
#include <cmath>
#include <sstream>

namespace nekomata {
namespace util {

std::string format(const std::string& fmt, ...)
{
	va_list lst;
	va_start(lst, fmt);
	std::string res(formatv(fmt, lst));
	va_end(lst);
	return res;
}
std::string formatv(const std::string& fmt, va_list args)
{
	char buff[8192];
	size_t len = vsnprintf(buff, 8192, fmt.c_str(), args);
	if(len < 0){
		throw logging::Exception(__FILE__, __LINE__, "Format string too long!!");
	}
	return buff;
}

std::string decodePercent(const std::string& str)
{
	char* from(new char[str.length()+1]);
	char* to(new char[str.length()+1]);
	std::memcpy(from, str.c_str(), str.length());
	from[str.length()] = '\0';
	size_t i=0,j=0;
	for(;i<str.length();++i, ++j){
		if(from[i] == '%'){
			char code[3];
			code[0] = from[i+1];
			code[1] = from[i+2];
			code[2] = '\0';
			i+=2;
			char* failed = 0;
			to[j] = static_cast<char>(std::strtol(code, &failed, 16) & 0xff);
			if(failed != &code[2]){
				throw logging::Exception(__FILE__, __LINE__, "Failed to decode percent: %s", str.c_str());
			}
		}else if(from[i]=='+'){
			to[j] = ' ';
		}else{
			to[j] = from[i];
		}
	}
	to[j]='\0';

	return std::string(to);
}

bool startsWith(const std::string& target, const std::string& prefix)
{
	return target.compare(0, prefix.size(), prefix) == 0;
}
bool endsWith(const std::string& target, const std::string& suffix)
{
	return target.compare(target.size()-suffix.size(), suffix.size(), suffix) == 0;
}

void split(const std::string& str, const std::string& sep, std::vector<std::string>& list)
{
	if(sep.size() <= 0){
		return;
	}
	size_t i = 0;
	size_t found = 0;
	while((found = str.find(sep, i)) != std::string::npos){
		if(found != i){
			list.push_back(str.substr(i, found-i));
		}
		i = found+sep.length();
	}
	if(i != str.size()){
		list.push_back(str.substr(i));
	}
}

static size_t findFirstOf(const std::string& str, const std::string* sep, size_t n, size_t from, size_t* offset, size_t* seplen)
{
	*offset = std::string::npos;
	for(size_t i = 0;i<n;++i){
		size_t found = str.find(sep[i], from);
		if(sep[i].size() > 0 && found != std::string::npos && (found < *offset || *offset == std::string::npos)){
			*offset = found;
			*seplen = sep[i].size();
		}
	}
	return *offset;
}

void split(const std::string& str, const std::string* sep, size_t n, std::vector<std::string>& list)
{
	size_t i = 0;
	size_t found = std::string::npos;
	size_t seplen = std::string::npos;
	while((findFirstOf(str, sep, n, i, &found, &seplen)) != std::string::npos){
		if(found != i){
			list.push_back(str.substr(i, found-i));
		}
		i = found+seplen;
	}
	if(i != str.size()){
		list.push_back(str.substr(i));
	}
}
void splitLine(const std::string& str, std::vector<std::string>& list)
{
	static const std::string lineSep[] = {
			"\n",
			"\r"
	};
	split(str, lineSep, list);
}
void splitSpace(const std::string& str, std::vector<std::string>& list)
{
	static const std::string spaces[] = {
			" ",
			"　"
	};
	split(str, spaces, list);
}

const std::string unescapeString(const std::string& str){
	std::stringstream ss;
	size_t last = 0;
	size_t idx;
	while(((idx = str.find("\\", last)) != std::string::npos) && (idx < str.size()-1) ){
		ss << str.substr(last, (idx-last));
		std::string tmp(ss.str());
		switch(str.at(++idx)){
		case 'n':
			ss << "\n";
			break;
		case 'r':
			ss << "\r";
			break;
		case 't':
			ss << "\t";
			break;
		case 'b':
			ss << "\b";
			break;
		case 'f':
			ss << "\f";
			break;
		case '\"':
			ss << "\"";
			break;
		case '\'':
			ss << "\'";
			break;
		case '\\':
			ss << "\\";
			break;
		default:
			ss << "\\";
			ss << str.at(idx);
			break;
		}
		last = idx+1;
	}
	ss << str.substr(last);
	std::string result = ss.str();
	return result;
}
}}