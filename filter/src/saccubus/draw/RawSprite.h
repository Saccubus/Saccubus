/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */
#pragma once

#include "Sprite.h"

namespace saccubus {
namespace draw {
/**
 * スプライトをまとめたスプライトではなくて、実際の絵を持つスプライトを表す。
 */
class RawSprite: public saccubus::draw::Sprite {
public:
	class Session{
	private:
		Sprite::Handler<RawSprite> const sprite;
		void* _data;
		int _w;
		int _h;
		int _stride;
	public:
		Session(Sprite::Handler<RawSprite> spr);
		virtual ~Session();
	public:
		void* data() const;
		int width() const;
		int height() const;
		int stride() const;
	};
private:
	std::shared_ptr<Renderer*> _renderer;
	bool _locked;
	int _width;
	int _height;
	int _origWidth;
	int _origHeight;
public:
	virtual int width() const;
	virtual int height() const;
protected:
	int origWidth() const;
	int origHeight() const;
	void width(int val);
	void height(int val);
protected:
	RawSprite(std::shared_ptr<Renderer*> _renderer);
	RawSprite(std::shared_ptr<Renderer*> _renderer, int w, int h);
	Renderer* renderer(){ return *(_renderer.get()); };
public:
	virtual ~RawSprite();
protected:
	virtual void lock(void** data, int* w, int* h, int* stride) = 0;
	virtual void unlock() = 0;
	virtual void onFree();
public:
	virtual void draw(std::shared_ptr<draw::Context> ctx, int x, int y) = 0;
	virtual void resize(int w, int h);
};

}}
