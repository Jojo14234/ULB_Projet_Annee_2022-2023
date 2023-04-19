/**
 * Project Untitled
 */

#pragma once


template <typename T1=float, typename T2=float>
class ObjectInfo {

	T1 size_x;
	T1 size_y;

	T2 pos_x;
	T2 pos_y;

public:

	ObjectInfo()=default;
	ObjectInfo(T1 sx, T1 sy, T2 px, T2 py) : size_x(sx), size_y(sy), pos_x(px), pos_y(py) {}

	// SETTERS
	void setSize(T1 sx, T1 sy) { size_x = sx; size_y = sy; }
	void setPosition(T2 px, T2 py) { pos_x = px; pos_y = py; }

	// GETTERS
	T1 getHeight() const { return size_y; }
	T1 getWidth() const { return size_x; }

	T2 getX() const { return pos_x; }
	T2 getY() const { return pos_y; }

};