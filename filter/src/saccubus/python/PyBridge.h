/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once
#include <string>
#include <map>
#include <vector>
#include <nicomo/Model.h>
#include "../classdefs.h"

namespace saccubus {
namespace python {

class PyBridgeImpl;
class PyBridge {
private:
	cinamo::Logger& log;
	PyBridgeImpl* const impl;
public:
	PyBridge(cinamo::Logger& log);
	virtual ~PyBridge();
public:
	const nicomo::model::Video* resolveResource(std::string const& video_id, const std::multimap<std::string, std::string>& args);
	bool askCommentShouldBeIgnored(std::string const& filename, const nicomo::model::Comment& com);
};

}}
