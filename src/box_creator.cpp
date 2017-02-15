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


#include "box_creators.h"

#include "Box2D/Box2D.h"
#include "globals.h"


b2World* BoxCreators::createWorld()
{
    b2Vec2 myGravity(0.f, 9.8f);
    return new b2World(myGravity);
}

b2Body* BoxCreators::createStaticBody(
            b2World* world,
            const double height,
            const double width)
{
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(
                (height/2)*G_PIXELS_TO_METERES,
                (width/2)*G_PIXELS_TO_METERES);

    b2FixtureDef bodyFixture;
    bodyFixture.density = 1.f;
    bodyFixture.friction = 0.2f;
    bodyFixture.shape = &bodyShape;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;


    b2Body* myBody = world->CreateBody(&bodyDef);
    myBody->CreateFixture(&bodyFixture);
    return myBody;
}


b2Body* BoxCreators::createPlayerBody(b2World* world)
{
    /* Umownie nasz bohater
     * bedzie kwadratem 40x40 px. */
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(20*G_PIXELS_TO_METERES, 20*G_PIXELS_TO_METERES);

    b2FixtureDef bodyFixture;
    bodyFixture.density = 0.1f;
    bodyFixture.friction = 0.2f;
    bodyFixture.shape = &bodyShape;

    /* Typ ciala definiujemy w b2BodyDef
     * w przypadku ruchomego obiektu gracza
     * zastosujemy cialo dynamiczne. */
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2Body* myBody = world->CreateBody(&bodyDef);
    myBody->CreateFixture(&bodyFixture);

    /* Domyslnie kazde cialo posiada
     * "naprawiona" rotacje, czyli
     * fizycznie sie nie obraca, w naszym
     * przykladzie chcemy jednak aby cialo
     * bylo bardziej *wyluzowane*. */
    myBody->SetFixedRotation(false);
    return myBody;
}


b2Body* BoxCreators::createDynamicBody(
            b2World* world,
            const float width,
            const float height)
{
    /* Wielkosc ciala przesylamy
     * w parametrach. */
    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(
                (width/2)*G_PIXELS_TO_METERES,
                (height/2)*G_PIXELS_TO_METERES);

    b2FixtureDef bodyFixture;
    bodyFixture.density = 0.1f;
    bodyFixture.friction = 0.2f;
    bodyFixture.shape = &bodyShape;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;

    b2Body* myBody = world->CreateBody(&bodyDef);
    myBody->CreateFixture(&bodyFixture);

    /* Wylaczamy "naprawiona" rotacje,
     * stwierdzilem ze troche slabo wyglada
     * grzybek ktory po przewroceniu ma
     * narzady ruchu na policzku. */
    myBody->SetFixedRotation(true);
    return myBody;
}
