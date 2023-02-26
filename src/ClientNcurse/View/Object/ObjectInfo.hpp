#ifndef _OBJECT_INFO_HPP
#define _OBJECT_INFO_HPP


class Point {

	int x, y;

public:

	Point(int x, int y) : x(x), y(y) {}
	
	// GETTERS
	int getX() const { return x; }
	int getY() const { return y; }

};

class Size : public Point {
public:
	using Point::Point;
};

class Position : public Point {
public:
	using Point::Point;
};


class ObjectInfo {

	Size size;
	Position pos;

public:

	ObjectInfo(Size size, Position pos) : size(size), pos(pos) {}
	ObjectInfo(int height, int width, int y, int x) : size(height, width), pos(x, y) {}

	// GETTERS
	Position getPos() const { return pos; }
	Size getSize() const { return size; }

	int getWidth() const { return size.getX(); }
	int getHeight() const { return size.getY(); }
	
	int getX() const { return pos.getX(); }
	int getY() const { return pos.getY(); }

};

#endif
