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

#ifndef CAIRO_SIMPLESHAPEFACTORY_H__CPP_
#define CAIRO_SIMPLESHAPEFACTORY_H__CPP_

#include "Renderer.h"
#include "../ShapeFactory.h"

namespace saccubus {
namespace draw {
namespace cairo {

class SimpleShapeFactory: public saccubus::draw::ShapeFactory {
public:
	SimpleShapeFactory(logging::Logger& log, cairo::Renderer* renderer);
	virtual ~SimpleShapeFactory();
public:
	virtual Sprite::Handler<draw::Sprite> renderButton(int w, int h, unsigned int color);
	virtual Sprite::Handler<draw::Sprite> renderShape(const nekomata::system::Shape* const shape);
};

}}}
#endif /* INCLUDE_GUARD */
