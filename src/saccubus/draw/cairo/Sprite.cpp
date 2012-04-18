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

#include "Sprite.h"
#include "Context.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace draw {
namespace cairo {

Sprite::Sprite(logging::Logger& log, std::tr1::shared_ptr<draw::Renderer*> renderer, int w, int h)
:draw::RawSprite(log, renderer, w, h)
{
	this->surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h));
}

Sprite::~Sprite() {
	cairo_surface_destroy(this->surface());
	this->surface(0);
}

void Sprite::draw(std::tr1::shared_ptr<saccubus::draw::Context> _ctx, int x, int y)
{
	cairo::Context& ctx = dynamic_cast<cairo::Context&>(*(_ctx.get()));
	cairo_set_source_surface(ctx.cairo(), this->surface(), x, y);
	//FIXME: ええと、どうやるんだっけ
	//cairo_clip_extents(ctx.cairo(), x, y, (x+this->_width), (y+this->_height) );
	cairo_paint(ctx.cairo());
}
void Sprite::lock(void** data, int* w, int* h, int* stride)
{
	*w = this->width();
	*h = this->height();
	cairo_surface_flush(this->surface());
}
void Sprite::unlock()
{
	cairo_surface_mark_dirty_rectangle(this->surface(), 0, 0, this->width(), this->height());
}


}}}