#include "Hero.h"

USING_NS_CC;

void Hero::initHero()
{
    StatModifier* baseHP = new StatModifier(10, StatModifierType::Flat);
    this->health_point.addModifier(baseHP);
    StatModifier* baseMP = new StatModifier(5, StatModifierType::Flat, 0, this);
    this->mana_point.addModifier(baseMP);
    StatModifier* baseATK = new StatModifier(5, StatModifierType::Flat, 0, this);
    this->damage_point.addModifier(baseATK);
    StatModifier* baseMSP = new StatModifier(100, StatModifierType::Flat, 0, this);
    this->movement_speed.addModifier(baseMSP);
}

Hero::Hero(HeroJob heroJob, cocos2d::Vec2& position):Entity()
{
    /*initHero*/
    this->initHero();
    /*choice hero class*/
    int frameBegin = 0;
    int frameEnd = 3;
    float frameDelay = 0.15f;
    switch (heroJob)
    {
    case HeroJob::Elf_M:
        this->heroJob = HeroJob::Elf_M;
        this->setSpriteFrame(ELF_M_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, ELF_M_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    case HeroJob::Elf_F:
        this->heroJob = HeroJob::Elf_F;
        this->setSpriteFrame(ELF_F_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, ELF_F_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    case HeroJob::Knight_M:
        this->heroJob = HeroJob::Knight_M;
        this->setSpriteFrame(KNIGHT_M_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, KNIGHT_M_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    case HeroJob::Knight_F:
        this->heroJob = HeroJob::Knight_F;
        this->setSpriteFrame(KNIGHT_F_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, KNIGHT_F_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    case HeroJob::Lizard_M:
        this->heroJob = HeroJob::Lizard_M;
        this->setSpriteFrame(LIZARD_M_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, LIZARD_M_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    case HeroJob::Lizard_F:
        this->heroJob = HeroJob::Lizard_F;
        this->setSpriteFrame(LIZARD_F_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, LIZARD_F_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    case HeroJob::Wizard_M:
        this->heroJob = HeroJob::Wizard_M;
        this->setSpriteFrame(WIZARD_M_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, WIZARD_M_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    case HeroJob::Wizard_F:
        this->heroJob = HeroJob::Wizard_F;
        this->setSpriteFrame(WIZARD_F_IDLE, frameBegin);
        this->setAnimation(REPEAT::FOREVER, WIZARD_F_IDLE, frameBegin, frameEnd, frameDelay);
        break;
    }
    /*set hero position*/
    this->setPosition(position);
}

Hero::~Hero()
{
}

float Hero::getHealthPoint()
{
    return this->health_point.getValue();
}

HeroJob Hero::getHeroJob()
{
    return this->heroJob;
}

float Hero::getManaPoint()
{
    return this->mana_point.getValue();
}

float Hero::getDamagePoint()
{
    return this->damage_point.getValue();
}

float Hero::getMovementSpeed()
{
    return this->movement_speed.getValue();
}