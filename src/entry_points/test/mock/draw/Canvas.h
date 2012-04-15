/*
 * Canvas.h
 *
 *  Created on: 2012/04/14
 *      Author: psi
 */

#ifndef MOCK_DRAW_CANVAS_H_
#define MOCK_DRAW_CANVAS_H_

#include <vector>
#include "../../../../saccubus/draw/Canvas.h"

namespace saccubus {
namespace mock {
namespace draw {

class Sprite;
class Canvas: public saccubus::draw::Canvas {
private:
	std::vector<std::pair<std::pair<int, int>, Sprite* > > drawQuery;
public:
	typedef std::vector<std::pair<std::pair<int, int>, Sprite* > >::const_iterator QueryIterator;
	Canvas();
	virtual ~Canvas();
public:
	void draw(int x, int y, Sprite* spr);
	QueryIterator queryBegin();
	QueryIterator queryEnd();
	std::size_t querySize();
};

}}}
#endif /* MOCK_DRAW_CANVAS_H_ */