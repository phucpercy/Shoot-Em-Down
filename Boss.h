#ifndef _BOSS_H_
#define _BOSS_H_

#include "BaseObject.h"
#include "AmoObject.h"
#include <vector>

#define WIDTH_BOSS 200
#define HEIGHT_BOSS 133

class Boss : public BaseObject
{
private:
	int x_val;
	int y_val;
	int boss_hp;

	std::vector<AmoObject*> p_amo_list;

public:
	Boss();
	~Boss();

	void BossMoveOut();
	void HandleBossMove(const int& x_desPos, const int& y_desPos);

	int GetBossHP() const { return boss_hp; }
	void SetBossHP(const int& hp) { boss_hp = hp; }

	void SetAmoList(std::vector<AmoObject*> amo_list) { p_amo_list = amo_list; }
	void InitAmo(AmoObject* p_amo);
	void BossShoot(SDL_Surface* des, const int& x_limit, const int& y_limit);
	std::vector <AmoObject*> GetAmoList() const { return p_amo_list; }

};

#endif
