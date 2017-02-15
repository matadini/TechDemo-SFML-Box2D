/* TechDemo SFML/Box2D
Copyright (C) 2016 Matadini (matadini@hotmail.com)

This software is provided 'as-is', without any express
or implied warranty. In no event will the authors be
held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software
for any purpose, including commercial applications, and
to alter it and redistribute it freely, subject to the
following restrictions:

1. The origin of this software must not be misrepresented;
you must not claim that you wrote the original software.
If you use this software in a product, an acknowledgment
in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such,
and must not be misrepresented as being the original software.

3. This notice may not be removed or altered from any source distribution.


External libraries used by TechDemo SFML/Box2D
-------------------------------
* Qt5 is licensed under the LGPL license
* PhysicsFS is licensed under the zlib license.
* SFML is licensed under the zlib license.
* Box2D is licensed under the zlib license. */


#include "core_apps.h"


#include <iostream>
#include <memory>
#include <vector>

#include "assets.h"
#include "contact_detector.h"
#include "movable_body.h"
#include "identified_body.h"
#include "control_keys.h"
#include "fps_stabilizer.h"
#include "body_mover.h"
#include "globals.h"
#include "editor.h"
#include "box_creators.h"
#include "game_world.h"


void CoreApps::startExample()
{
    sf::RenderWindow* windowItem =
                        new sf::RenderWindow(
                            sf::VideoMode(800, 600, 32),
                            std::string("SFML/Box2D - tech demo"),
                            sf::Style::Default);

    std::shared_ptr<sf::RenderWindow> window(windowItem);
    std::shared_ptr<ControlKeys>playerControl(new ControlKeys());


    FpsStabilizer stabilizer(60);

    Assets::Resources resources("data.zip");
    GameWorld world(resources);


    MovableBody* playerPtr = world.getPlayer();
    ContactDetector* contactDetector = world.getContactDetector();


    while(window->isOpen())
    {
        /* OTHER */
        stabilizer.work();


        for(auto& item : world.listMovableBodies){
            item->getRenderBody()->setColor(sf::Color::White);
        }


        /* EVENTS */
        sf::Event myEvent;
        while(window->pollEvent(myEvent))
        {
            if(myEvent.type == sf::Event::Closed){
                window->close();
            }
        }

        if(sf::Keyboard::isKeyPressed(playerControl->MOVE_JUMP))
        {
            playerPtr->getMover()->move(
                        BodyMover::Direction::Jump);
        }

        if(sf::Keyboard::isKeyPressed(playerControl->MOVE_RIGHT))
        {
            playerPtr->getMover()->move(
                        BodyMover::Direction::Right);

            DrawableBodyAnimated* ptr =
                    (DrawableBodyAnimated*)playerPtr->getRenderBody();

            ptr->getAnimator()->setAnimation(0);


        }

        if(sf::Keyboard::isKeyPressed(playerControl->MOVE_LEFT))
        {
            playerPtr->getMover()->move(
                        BodyMover::Direction::Left);

            DrawableBodyAnimated* ptr =
                    (DrawableBodyAnimated*)playerPtr->getRenderBody();


            ptr->getAnimator()->setAnimation(1);
        }

        /* BOX2D */
        world.prepareWorld();

        for(auto& enemyItem : world.listMovableBodies)
        {
            break;
        }

        const bool contactCondition =
                (!contactDetector->isContactListIsEmpty()) &&
                    contactDetector->isContactListContains(
                        ContactDetector::Contact::Type::PlayerTouchEnemy);

        if(contactCondition)
        {
            std::vector<ContactDetector::Contact::Info> enemyContacts =
                    contactDetector->getContactList(
                        ContactDetector::Contact::Type::PlayerTouchEnemy);

            if(!enemyContacts.empty()){

                for(auto& contact : enemyContacts)
                {
                    break;
                }
            }
        }

        /* RENDER */
        window->clear(sf::Color::Black);

        for(auto& item : world.listMovableBodies){
            item->getRenderBody()->update();
            item->getRenderBody()->render(*window);
        }

        for(auto& item : world.listIdentifiedBodies){
            item->getRenderBody()->render(*window);
        }

        window->display();
    }
}

void beforeGameLoop(b2World& world)
{
    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 6;
    const int32 positionIterations = 2;
    world.Step(
            timeStep,
            velocityIterations,
            positionIterations);
}

void createArea(
        b2World* world,
        std::vector<IdentifiedBody>& list,
        Assets::Resources& resources)
{
    IdentifiedBody mapPlatformTop(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(world, 800, 40)),
                BodyUserData::Type::Map);

    mapPlatformTop.getRenderBody()->setPosition(400.f, 0.f);
    mapPlatformTop.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Map));


    IdentifiedBody mapPlatformBottom(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(world, 800, 40)),
                BodyUserData::Type::Map);

    mapPlatformBottom.getRenderBody()->setPosition(400.f, 600.f);
    mapPlatformBottom.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Map));


    IdentifiedBody mapWallLeft(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(world, 40, 800)),
                BodyUserData::Type::Wall);

    mapWallLeft.getRenderBody()->setPosition(0.f, 400.f);
    mapWallLeft.getRenderBody()->setVisable(false);
    mapWallLeft.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Wall));


    IdentifiedBody mapWallRight(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(world, 40, 800)),
                BodyUserData::Type::Wall);

    mapWallRight.getRenderBody()->setPosition(800.f, 400.f);
    mapWallRight.getRenderBody()->setVisable(false);
    mapWallRight.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Wall));


    list.push_back(mapPlatformTop);
    list.push_back(mapPlatformBottom);
    list.push_back(mapWallLeft);
    list.push_back(mapWallRight);
}

void CoreApps::startSecondExample()
{
    sf::RenderWindow* windowItem =
                        new sf::RenderWindow(
                            sf::VideoMode(800, 600, 32),
                            std::string("SFML/Box2D - tech demo"),
                            sf::Style::Default);

    std::shared_ptr<sf::RenderWindow> window(windowItem);
    std::shared_ptr<ControlKeys>playerControl(new ControlKeys());

    FpsStabilizer stabilizer(60);


    /* Map section. */
    ContactDetector myContactLister;
    std::unique_ptr<b2World> myWorld(BoxCreators::createWorld());
    myWorld.get()->SetContactListener(&myContactLister);


    Assets::Resources resources("data.zip");

    std::vector<IdentifiedBody> listWorldBodies;

    createArea(myWorld.get(), listWorldBodies, resources);


    /* Player item. */
    sf::Texture playerTexture;
    if(!playerTexture.loadFromFile("walk.png")){
        std::cout << __func__ << " -walki.png problem\n";
    }


    sf::Vector2f oneFrameSize(104.f, 150.f);
    sf::Vector2f playerBodySize(75.f, 100.f);

    sf::RectangleShape shapeForAnimation;
    shapeForAnimation.setSize(playerBodySize);
    shapeForAnimation.setOrigin(
            shapeForAnimation.getSize().x/2,
            shapeForAnimation.getSize().y/2);
    shapeForAnimation.setPosition(sf::Vector2f(250, 250.f));
    shapeForAnimation.setTexture(&playerTexture);


    MovableBody playerItem(
                    new DrawableBodyAnimated(
                        BoxCreators::createDynamicBody(
                            myWorld.get(),
                            playerBodySize.x,
                            playerBodySize.y),
                        new Animator(
                                &shapeForAnimation,
                                oneFrameSize)),
                BodyUserData::Type::Player);

    playerItem.getRenderBody()->setPosition(400.f, 10.f);
    playerItem.getMover()->setJumpForce(4.5f);

    /* Enemy A. */
    MovableBody enemyItem(
                new DrawableBodyGenerated(
                        BoxCreators::createDynamicBody(myWorld.get(), 90, 60)),
                BodyUserData::Type::Enemy);

    enemyItem.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Enemy));

    enemyItem.getRenderBody()->setPosition(600.f, 50.f);
    enemyItem.getMover()->setJumpForce(3.f);
    enemyItem.getMover()->setMaxSpeed(2.5f);


    /* Enemy B. */
    MovableBody enemyItemB(
                new DrawableBodyGenerated(
                        BoxCreators::createDynamicBody(myWorld.get(), 90, 60)),
                BodyUserData::Type::Enemy);

    enemyItemB.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Enemy));

    enemyItemB.getRenderBody()->setPosition(150.f, 50.f);
    enemyItemB.getMover()->setJumpForce(3.f);
    enemyItemB.getMover()->setMaxSpeed(2.5f);


    /* Ewidencja wrogow. */
    std::vector<MovableBody> listEnemies;
    listEnemies.push_back(enemyItem);
    listEnemies.push_back(enemyItemB);


    sf::Color backgroundColor;
    while(window->isOpen())
    {

        /* OTHER */
        stabilizer.work();
        backgroundColor = sf::Color::Black;
        for(MovableBody& item : listEnemies){
            item.getRenderBody()->setColor(sf::Color::White);
        }


        /* EVENTS */
        sf::Event myEvent;
        while(window->pollEvent(myEvent))
        {
            if(myEvent.type == sf::Event::Closed){
                window->close();
            }
        }

        if(sf::Keyboard::isKeyPressed(playerControl->MOVE_JUMP))
        {
            playerItem.getMover()->move(
                        BodyMover::Direction::Jump);
        }

        if(sf::Keyboard::isKeyPressed(playerControl->MOVE_RIGHT))
        {
            playerItem.getMover()->move(
                        BodyMover::Direction::Right);

            DrawableBodyAnimated* ptr =
                    (DrawableBodyAnimated*)playerItem.getRenderBody();

            ptr->getAnimator()->setAnimation(0);


        }

        if(sf::Keyboard::isKeyPressed(playerControl->MOVE_LEFT))
        {
            playerItem.getMover()->move(
                        BodyMover::Direction::Left);

            DrawableBodyAnimated* ptr =
                    (DrawableBodyAnimated*)playerItem.getRenderBody();


            ptr->getAnimator()->setAnimation(1);
        }


        /* BOX2D */
        beforeGameLoop(*myWorld.get());

        for(auto& enemyItem : listEnemies)
        {
            break;
        }

        const bool contactCondition =
                (!myContactLister.isContactListIsEmpty()) &&
                    myContactLister.isContactListContains(
                        ContactDetector::Contact::Type::PlayerTouchEnemy);

        if(contactCondition)
        {
            std::vector<ContactDetector::Contact::Info> enemyContacts =
                    myContactLister.getContactList(
                        ContactDetector::Contact::Type::PlayerTouchEnemy);

            if(!enemyContacts.empty()){

                for(auto& contact : enemyContacts)
                {
                    break;
                }
            }
        }


        /* RENDER */
        window->clear(backgroundColor);

        playerItem.getRenderBody()->update();
        playerItem.getRenderBody()->render(*window);

        for(auto& item : listEnemies){
            item.getRenderBody()->update();
            item.getRenderBody()->render(*window);
        }

        for(auto& item : listWorldBodies){
            item.getRenderBody()->render(*window);
        }

        window->display();
    }
}
