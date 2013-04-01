/**
 * Saccubus
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

#pragma once
#include <stdio.h>
#include <gtest/gtest.h>

#include <memory>
using std::shared_ptr;
#include <iostream>
#include "../src/saccubus/logging/Exception.h"
#include "../src/saccubus/logging/Logger.h"
using namespace saccubus::logging;

#define MATERIAL_DIR "_TestMaterials/"

#define NULL_STREAM (*((std::ostream*)0))
static Logger log_trace(std::cout, Logger::TRACE_);
static Logger log_err(std::cout, Logger::ERROR_);

#define MOCK_ACCESSOR_EXPAND(super, type, name)\
public:\
	type name() {return this->super::name(); }\
	void name(type const& val) { this->super::name(val); }
