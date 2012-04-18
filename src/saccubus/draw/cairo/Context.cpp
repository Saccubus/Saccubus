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

#include "Context.h"
#include "Renderer.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace draw {
namespace cairo {

Context::Context(logging::Logger& log, std::tr1::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
:draw::Context(log, renderer)
{
	cairo_format_t cfmt;
	switch(fmt){
	case Renderer::RGB24:
		cfmt = CAIRO_FORMAT_RGB24;
		break;
	case Renderer::RGBA32:
		cfmt = CAIRO_FORMAT_ARGB32;
		break;
	default:
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon format: %d", fmt);
	}
	this->surface(cairo_image_surface_create_for_data(
			reinterpret_cast<unsigned char*>(data),
			cfmt,
			w,
			h,
			stride
			));
	this->cairo(cairo_create(this->surface()));
}

Context::~Context() {
	cairo_destroy(this->cairo());
	cairo_surface_destroy(this->surface());
}

float Context::width() const
{
	return cairo_image_surface_get_width(this->surface());
}
float Context::height() const
{
	return cairo_image_surface_get_height(this->surface());
}

}}}