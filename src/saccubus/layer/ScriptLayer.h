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

#include <nekomata/system/System.h>

#include "../classdefs.h"
#include "Layer.h"
#include "../util/ClassAccessor.h"
#include "NekomataSystem.h"
#include "item/NekoItem.h"

#ifndef Saccubus_NEKOMATALAYER_H__CPP_
#define Saccubus_NEKOMATALAYER_H__CPP_

namespace saccubus {
namespace layer {

class ScriptLayer: public Layer {
	DEF_ATTR_ACCESSOR(private, private, NekomataSystem*, nekoSystem);
private:
	void resolvePos(std::tr1::shared_ptr<saccubus::draw::Context> ctx, item::NekoItem* nekoItem, float screenWidth, float screenHeight, float* x, float* y);
public:
	ScriptLayer(logging::Logger& log, NekomataSystem* nekoSystem);
	virtual ~ScriptLayer();
	/******************************************************************************************************************
	 * レイヤ
	 ******************************************************************************************************************/
	virtual void draw(std::tr1::shared_ptr<saccubus::draw::Context> ctx, float vpos);
	virtual bool onClick(int x, int y);
};

}}
#endif /* INCLUDE_GUARD */
