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

	Position pos;
	Size size;

public:

	ObjectInfo(Position pos, Size size) : pos(pos), size(size) {}
	ObjectInfo(int x, int y, int height, int width) : pos(x, y), size(height, width) {}

	// GETTERS
	Position getPos() const { return pos; }
	Size getSize() const { return size; }
	
	int getX() const { return pos.getX(); }
	int getY() const { return pos.getY(); }
	int getWidth() const { return size.getY(); }
	int getHeight() const { return size.getX(); }

};

#endif
