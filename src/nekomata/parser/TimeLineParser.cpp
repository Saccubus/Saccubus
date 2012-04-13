/*
 * TimeLineParser.cpp
 *
 *  Created on: 2012/04/13
 *      Author: psi
 */

#include <nekomata/logging/Exception.h>
#include <cstdlib>
#include "TimeLineParser.h"
#include "Parser.h"
#include "../tree/Node.h"

namespace nekomata {
namespace parser {

TimeLineParser::TimeLineParser(std::istream& stream, const std::string& filename)
:stream(stream), filename(filename){
}

TimeLineParser::~TimeLineParser() {
}

void TimeLineParser::parseLine(std::multimap<float, std::tr1::shared_ptr<const system::Comment>, std::less<float> >& timeLine, const std::string& line)
{
	const size_t firstSep = line.find(':');
	if(firstSep == std::string::npos){
		throw logging::Exception(__FILE__, __LINE__, "failed to parse timeline: %s", line.c_str());
	}
	const size_t secondSep = line.find(':', firstSep+1);
	if(secondSep == std::string::npos){
		throw logging::Exception(__FILE__, __LINE__, "failed to parse timeline: %s", line.c_str());
	}
	const std::string timeStr(line.substr(0, firstSep));
	char* endPtr;
	const float time = std::strtof(timeStr.c_str(), &endPtr);
	if(*endPtr != '\0'){
		throw logging::Exception(__FILE__, __LINE__, "failed to parse time: %s", timeStr.c_str());
	}
	const std::string mail(line.substr(firstSep+1, secondSep));
	std::string message(line.substr(secondSep+1));
	if (message.at(message.size()-1) == '\n') message.erase(message.size()-1);
	if (message.at(message.size()-1) == '\r') message.erase(message.size()-1);
	switch(message.at(0))
	{
	case '\%':
	{
		std::tr1::shared_ptr<const system::Comment> com(new system::Comment(message.substr(1), time, true, mail, false, false, 0xffffff, 30, 0));
		timeLine.insert(std::pair<float, std::tr1::shared_ptr<const system::Comment> >(time, com));
		break;
	}
	case '/':
	{
		std::tr1::shared_ptr<const tree::Node> node(Parser::fromString(message.substr(1), filename)->parseProgram());
		std::tr1::shared_ptr<const system::Comment> com(new system::Comment(time, node));
		timeLine.insert(std::pair<float, std::tr1::shared_ptr<const system::Comment> >(time, com));
		break;
	}
	default:
	{
		std::tr1::shared_ptr<const system::Comment> com(new system::Comment(message, time, true, mail, false, false, 0xffffff, 30, 0));
		timeLine.insert(std::pair<float, std::tr1::shared_ptr<const system::Comment> >(time, com));
		break;
	}
	}
}

std::multimap<float, std::tr1::shared_ptr<const system::Comment>, std::less<float> > TimeLineParser::parse()
{
	std::multimap<float, std::tr1::shared_ptr<const system::Comment>, std::less<float> > timeLine;
	std::string buf;
	while(stream && std::getline(stream, buf)){
		this->parseLine(timeLine,buf);
	}
	return timeLine;
}


}}

