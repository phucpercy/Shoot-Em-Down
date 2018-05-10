#ifndef _AMO_OBJECT_H_
#define _AMO_OBJECT_H_

#include "BaseObject.h"

#define WIDTH_ROCKET 75
#define HEIGHT_ROCKET 35

#define WIDTH_BULLET 53
#define HEIGHT_BULLET 26

class AmoObject : public BaseObject
{
private:
	int x_val;
	int y_val;
	bool is_move;
	int amo_type;

public:
	AmoObject();
	~AmoObject();

	enum AmoType
	{
		NONE = 0,
		ROCKET = 1,
		BULLET = 2
	};

	void HandleInputAction(SDL_Event events);
	void HandleMove(const int& x_border, const int& y_border);
	void HandleThreatAmo();

	int getType() const { return amo_type; }
	void setType(const int& type) { amo_type = type; }

	bool get_is_move() const { return is_move; }
	void set_is_move(bool isMove) { is_move = isMove; }
	void SetWidthHeight(const int& width, const int& height)
	{
		rect.w = width;
		rect.h = height;
	}

	void set_x_val(const int& val) { x_val = val; }
	void set_y_val(const int& val) { y_val = val; }

	int get_x_val() const { return x_val; }
	int get_y_val() const { return y_val; }
};

#endif
