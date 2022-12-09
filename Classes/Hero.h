#ifndef __HERO_H__
#define __HERO_H__
#include "Entity.h"
enum class HeroClasses
{
	Elf_M,
	Elf_F,
	Knight_M,
	Knight_F,
	Lizard,
	Wizard
};
class Hero:public Entity
{
private:
	EntityStats health_point;
	EntityStats mana_point;
	EntityStats damage_point;
	EntityStats movement_speed;
	void initHero();
public:
	Hero(HeroClasses classes, cocos2d::Vec2& position);
	~Hero();
	float getHealthPoint();
	void setHealthPoint(float health);
	float getManaPoint();
	void setManaPoint(float mana);
	float getDamagePoint();
	void setDamagePoint(float damage);
	float getMovementSpeed();
	void setMovementSpeed(float movementspeed);
};
#endif // !__HERO_H__
