/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#include "Sprite.h"
#include "Context.h"
#include "../../logging/Exception.h"

namespace saccubus {
namespace draw {
namespace cairo {

Sprite::Sprite(std::shared_ptr<draw::Renderer*> renderer, int w, int h)
:draw::RawSprite(renderer, w, h)
{
	this->surface(cairo_image_surface_create(CAIRO_FORMAT_ARGB32, w, h));
}

Sprite::Sprite(std::shared_ptr<draw::Renderer*> renderer, enum draw::Renderer::Format fmt, void* data, int w, int h, int stride)
:draw::RawSprite(renderer, w, h)
{
	cairo_format_t cfmt = cairo::Renderer::toCairoFormat(fmt);
	if(cfmt == CAIRO_FORMAT_INVALID){
		throw logging::Exception(__FILE__, __LINE__, "[BUG] Unknwon format: %d", fmt);
	}
	this->surface(cairo_image_surface_create_for_data(reinterpret_cast<unsigned char*>(data), cfmt, w, h, stride));
	switch(cairo_surface_status(this->surface())){
	case CAIRO_STATUS_SUCCESS:
		break;
	case CAIRO_STATUS_INVALID_STRIDE:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo surface. Invalid stride: %d != %d", stride, cairo_format_stride_for_width(cfmt, w));
	default:
		throw logging::Exception(__FILE__, __LINE__, "Failed to create cairo surface. Unknwon error.");
	}
}
Sprite::~Sprite() {
	cairo_surface_destroy(this->surface());
	this->surface(0);
}

void Sprite::draw(std::shared_ptr<saccubus::draw::Context> _ctx, int x, int y)
{
	cairo::Context& ctx = dynamic_cast<cairo::Context&>(*(_ctx.get()));
	cairo_set_source_surface(ctx.cairo(), this->surface(), x, y);
	cairo_rectangle(ctx.cairo(), x, y, this->width(), this->height());
	cairo_clip(ctx.cairo());
	cairo_paint(ctx.cairo());
	cairo_reset_clip(ctx.cairo());
}
void Sprite::lock(void** data, int* w, int* h, int* stride)
{
	cairo_surface_flush(this->surface());
	*w = this->width();
	*h = this->height();
	*stride = cairo_image_surface_get_stride(this->surface());
	*data = cairo_image_surface_get_data(this->surface());
}
void Sprite::unlock()
{
	cairo_surface_mark_dirty_rectangle(this->surface(), 0, 0, this->width(), this->height());
}


}}}
