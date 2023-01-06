#include "MapLevel1_1.h"
#include "PhysicsShapeCache.h"
#include "Sword.h"
#include "SwordSlash.h"
#include "GameManager.h"
#include "Skeleton.h"
USING_NS_CC;

void MapLevel1_1::initTileMap(cocos2d::Vec2 position)
{
    this->restroom = TMXTiledMap::create("maps/map1.2.tmx");
    this->restroom->setPosition(Vec2(position.x*0.5,position.y*0.5));
    this->restroom->setAnchorPoint(Vec2(0.5,0.5));
    this->restroom->setScaleX((80*16)/ this->restroom->getContentSize().width);
    this->restroom->setScaleY((45 * 16) /this->restroom->getContentSize().height);
    this->addChild(this->restroom,-1);

    auto objectGroup = this->restroom->getObjectGroup("WallCollision");
    for (auto &object: objectGroup->getObjects())
    {
        auto properties = object.asValueMap();
        auto x = properties.at("x").asInt() + properties.at("width").asInt()/2;
        auto y = properties.at("y").asInt() + properties.at("height").asInt() / 2;
        auto objectSize = Size(properties.at("width").asInt(), properties.at("height").asInt());
        auto wallBody = PhysicsBody::createBox(objectSize, PhysicsMaterial(1.0f, 0.0f, 0.0f));
        wallBody->setDynamic(false);
        wallBody->setContactTestBitmask(0xffff);
        wallBody->setCategoryBitmask(64);
        wallBody->setContactTestBitmask(51);
        auto wallNode = Node::create();
        wallNode->setPosition(x, y);
        wallNode->setPhysicsBody(wallBody);
        wallNode->setContentSize(objectSize);
        this->restroom->addChild(wallNode,2);
    }
}

cocos2d::Vec2 MapLevel1_1::tileCoordForPosition(cocos2d::Vec2 position)
{
    int x = position.x / restroom->getTileSize().width;
    int y = ((restroom->getMapSize().height * restroom->getTileSize().height) - position.y) / restroom->getTileSize().height;
    return cocos2d::Vec2(x,y);
}

void MapLevel1_1::initCameraUI()
{
    this->cameraUI = Camera::create();
    this->cameraUI->setCameraFlag(CameraFlag::USER1);
    this->addChild(cameraUI);
}

void MapLevel1_1::followHero()
{
    auto camera = getDefaultCamera();
    Vec2 targetPos = this->heroManager->getHero()->getPosition();
    auto visibleSize = Singleton<GameManager>::getIntsance()->getVisibleSize();
    targetPos.x = clampf(targetPos.x, (visibleSize.width - (BOUNDING_BOX.width - visibleSize.width)) / 2, (visibleSize.width + (BOUNDING_BOX.width - visibleSize.width)) / 2);
    targetPos.y = clampf(targetPos.y, (visibleSize.height - (BOUNDING_BOX.height - visibleSize.height)) / 2, (visibleSize.height + (BOUNDING_BOX.height - visibleSize.height)) / 2);
    Vec2 currentPos = camera->getPosition();
    currentPos = currentPos.lerp(targetPos, 0.1);
    camera->setPosition(currentPos);
}


Scene* MapLevel1_1::createScene()
{
    return MapLevel1_1::create();
}

bool MapLevel1_1::onContactBegin(cocos2d::PhysicsContact& _contact)
{
    if (m_contactStarted)
    {
        return true;
    }
    if ((_contact.getShapeA()->getCategoryBitmask() & _contact.getShapeB()->getCollisionBitmask()) <= 0 ||
        (_contact.getShapeB()->getCategoryBitmask() & _contact.getShapeA()->getCollisionBitmask()) <= 0)
    {
        return false;
    }

    auto nodeA = _contact.getShapeA()->getBody()->getNode();
    auto nodeB = _contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        int tagA = nodeA->getTag();
        int tagB = nodeB->getTag();
        if ((tagA == PLAYER_ATTACK_TAG && tagB == ENEMY_TAG)
            || (tagB == PLAYER_ATTACK_TAG && tagA == ENEMY_TAG))
        {
            WeaponSkill* attack = (WeaponSkill*)(tagA == PLAYER_ATTACK_TAG ? nodeA : nodeB);
            Enemy* enemy = (Enemy*)(tagA == ENEMY_TAG ? nodeA : nodeB);
            enemy->takeDamage(attack->getDamage());
        }
    }
    m_contactStarted = true;
    return true;
}

void MapLevel1_1::onContactSeparate(cocos2d::PhysicsContact& _contact)
{
    auto nodeA = _contact.getShapeA()->getBody()->getNode();
    auto nodeB = _contact.getShapeB()->getBody()->getNode();

    if (nodeA && nodeB)
    {
        //nodeA->setColor(Color3B::WHITE);
        //nodeB->setColor(Color3B::WHITE);
        m_contactStarted = false;
    }
}

void MapLevel1_1::onMouseMove(cocos2d::Event* event)
{
    EventMouse* e = (EventMouse*)event;
    this->lastMousePositon = e->getLocationInView();

}

// on "init" you need to initialize your instance
bool MapLevel1_1::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MapLevel1_1::onContactBegin, this);
    contactListener->onContactSeparate = CC_CALLBACK_1(MapLevel1_1::onContactSeparate, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseMove = CC_CALLBACK_1(MapLevel1_1::onMouseMove, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);

    this->initCameraUI();
    this->initTileMap((Vec2)visibleSize);

    Singleton<GameManager>::getIntsance()->addScene(this);
    Singleton<GameManager>::getIntsance()->addVisibleSize(visibleSize);

    this->heroManager->setScene(this);
    this->heroManager->spawnHero(HeroJob::Knight, Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto enemy = new Skeleton();
    enemy->setPosition(Vec2(visibleSize.width / 2 + 100, visibleSize.height / 2 + 100));
    this->addChild(enemy);

    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    //this->getPhysicsWorld()->setGravity(Vec2(0,-98));
    scheduleUpdate();
    return true;
}

void MapLevel1_1::update(float dt)
{
    this->followHero();
    heroManager->update(dt);
}
