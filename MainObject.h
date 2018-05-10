#ifndef _MAIN_OBJECT_H_
#define _MAIN_OBJECT_H_

#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_MAIN_OBJECT 113
#define HEIGHT_MAIN_OBJECT 78

class MainObject : public BaseObject
{
private:
	int x_val;
	int y_val;
	
	std::vector<AmoObject*> p_amo_list;

public:
	MainObject();

	void HandleMove();
	void HandleInputAction(SDL_Event events);
	void SetAmoList(std::vector<AmoObject*> amo_list) { p_amo_list = amo_list; }
	std::vector<AmoObject*> GetAmoList() const { return p_amo_list; }
	void RemoveAmo(const int& idx);
};

#endif
