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


#include "map_builder.h"
#include "box_creators.h"
#include "body_mover.h"

MapBuilder::Base::Base(b2World* world)
    : m_world(world)
{

}

MapBuilder::TechDemo::TechDemo(b2World* world) : Base(world)
{

}

void MapBuilder::TechDemo::createArea(
        std::vector<std::shared_ptr<IdentifiedBody>>& list,
        Assets::Resources& resources)
{
    IdentifiedBody mapPlatformTop(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(m_world, 800, 40)),
                BodyUserData::Type::Map);

    mapPlatformTop.getRenderBody()->setPosition(400.f, 0.f);
    mapPlatformTop.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Map));


    IdentifiedBody mapPlatformBottom(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(m_world, 800, 40)),
                BodyUserData::Type::Map);

    mapPlatformBottom.getRenderBody()->setPosition(400.f, 600.f);
    mapPlatformBottom.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Map));


    IdentifiedBody mapWallLeft(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(m_world, 40, 800)),
                BodyUserData::Type::Wall);

    mapWallLeft.getRenderBody()->setPosition(0.f, 400.f);
    mapWallLeft.getRenderBody()->setVisable(false);
    mapWallLeft.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Wall));


    IdentifiedBody mapWallRight(
                new DrawableBodyGenerated(
                    BoxCreators::createStaticBody(m_world, 40, 800)),
                BodyUserData::Type::Wall);

    mapWallRight.getRenderBody()->setPosition(800.f, 400.f);
    mapWallRight.getRenderBody()->setVisable(false);
    mapWallRight.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Wall));


    list.push_back(std::make_shared<IdentifiedBody>(mapPlatformTop));
    list.push_back(std::make_shared<IdentifiedBody>(mapPlatformBottom));
    list.push_back(std::make_shared<IdentifiedBody>(mapWallLeft));
    list.push_back(std::make_shared<IdentifiedBody>(mapWallRight));
}


void MapBuilder::TechDemo::createDynamicBodies(
        std::vector<std::shared_ptr<MovableBody>>& list,
        Assets::Resources& resources)
{
    sf::Vector2f oneFrameSize(104.f, 150.f);
    sf::Vector2f playerBodySize(75.f, 100.f);


    sf::RectangleShape* shapeForAnimation = new sf::RectangleShape();
    shapeForAnimation->setSize(playerBodySize);
    shapeForAnimation->setOrigin(
            shapeForAnimation->getSize().x/2,
            shapeForAnimation->getSize().y/2);
    shapeForAnimation->setPosition(sf::Vector2f(250, 250.f));
    shapeForAnimation->setTexture(
                resources.getTexture(
                    Assets::Textures::Player));


    MovableBody playerItem(
                    new DrawableBodyAnimated(
                        BoxCreators::createDynamicBody(
                            m_world,
                            playerBodySize.x,
                            playerBodySize.y),
                        new Animator(
                                shapeForAnimation,
                                oneFrameSize)),
                BodyUserData::Type::Player);

    playerItem.getRenderBody()->setPosition(400.f, 10.f);
    playerItem.getMover()->setJumpForce(4.5f);
    playerItem.getMover()->setMaxSpeed(3.5);

    /* Enemy A. */
    MovableBody enemyItem(
                new DrawableBodyGenerated(
                        BoxCreators::createDynamicBody(m_world, 90, 60)),
                BodyUserData::Type::Enemy);

    enemyItem.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Enemy));

    enemyItem.getRenderBody()->setPosition(600.f, 50.f);
    enemyItem.getMover()->setJumpForce(3.f);
    enemyItem.getMover()->setMaxSpeed(2.5f);


    /* Enemy B. */
    MovableBody enemyItemB(
                new DrawableBodyGenerated(
                        BoxCreators::createDynamicBody(m_world, 90, 60)),
                BodyUserData::Type::Enemy);

    enemyItemB.getRenderBody()->setTexture(
                *resources.getTexture(Assets::Textures::Enemy));

    enemyItemB.getRenderBody()->setPosition(150.f, 50.f);
    enemyItemB.getMover()->setJumpForce(3.f);
    enemyItemB.getMover()->setMaxSpeed(2.5f);


    /* Ewidencja wrogow. */
    list.push_back(std::make_shared<MovableBody>(playerItem));
    list.push_back(std::make_shared<MovableBody>(enemyItem));
    list.push_back(std::make_shared<MovableBody>(enemyItemB));
}
