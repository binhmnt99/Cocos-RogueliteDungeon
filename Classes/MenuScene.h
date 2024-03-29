#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class MenuScene : public Scene
{
private:
    int backgroundMusic = -1;
    bool soundOn = true;
    Label *soundLabel;
public:
    static Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
};

#endif // __MAIN_MENU_SCENE_H__
