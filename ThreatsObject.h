#ifndef _THREATS_OBJECT_H_
#define _THREATS_OBJECT_H_

#include "BaseObject.h"
#include "AmoObject.h"
#include "MainObject.h"
#include "vector"

#define WIDTH_THREAT 79
#define HEIGHT_THREAT 57

class ThreatObject : public BaseObject
{
private:
	int x_val;
	int y_val;

	std::vector<AmoObject*> p_amo_list;

public:
	ThreatObject();
	~ThreatObject();

	void HandleMove(const int& x_border, const int& y_border);
	void HandleInputAction(SDL_Event events);

	void set_x_val(const double& val) { x_val = val; }
	void set_y_val(const int& val) { y_val = val; }
	int get_x_val() const { return x_val; }
	int get_y_val() const { return y_val; }

	void SetAmoList(std::vector<AmoObject*> amo_list) { p_amo_list = amo_list; }
	std::vector<AmoObject*> GetAmoList() const { return p_amo_list; }
	void InitAmo(AmoObject* p_amo);
	void ThreatShoot(SDL_Surface* des, const int& x_limit, const int& y_limit);
	void Reset(const int& xborder);
	void ResetAmo(AmoObject* p_amo);

};

#endif
