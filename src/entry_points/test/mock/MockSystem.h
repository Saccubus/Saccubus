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

#ifndef Saccubus_MOCKSYSTEM_H__CPP_
#define Saccubus_MOCKSYSTEM_H__CPP_

#include <nekomata/system/System.h>

namespace saccubus {
namespace mock {

class MockSystem: public nekomata::system::System {
public:
	MockSystem();
	virtual ~MockSystem();
	virtual std::tr1::shared_ptr<const nekomata::system::Comment> nextComment();
};

}}
#endif /* INCLUDE_GUARD */
