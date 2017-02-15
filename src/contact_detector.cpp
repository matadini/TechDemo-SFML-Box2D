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


#include "contact_detector.h"

#include <Box2D/Box2D.h>
#include "body_user_data.h"

void
ContactDetector::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    if(bodyA != nullptr && bodyB != nullptr){

        Contact::Type contactType = getContactType(bodyA, bodyB);

        if(this->isContactShouldBeServerd(contactType))
        {
            Contact::Info newDiaryElement =
                    this->constructContactInfo(
                        contactType, bodyA, bodyB);

            if(!isContactInfoExistsInDiary(newDiaryElement)){
                m_contactDiary.push_back(newDiaryElement);
            }
        }
    }
}


void
ContactDetector::EndContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();

    if(bodyA != nullptr && bodyB != nullptr){

        Contact::Type contactType = getContactType(bodyA, bodyB);

        if(this->isContactShouldBeServerd(contactType))
        {
            Contact::Info diaryItem =
                    this->constructContactInfo(
                        contactType, bodyA, bodyB);

            if(this->isContactInfoExistsInDiary(diaryItem)){
                const int index = this->getContactInfoItemIndex(diaryItem);
                m_contactDiary.erase(m_contactDiary.begin() + index);
            }
        }
    }
}


/* Nie wszystkie zdarzenia cial bedziemy
 * rejestrowac stad funkcja sprawdzajaca
 * czy zdarzenie nalezy do listy
 * interesujacych nas zdarzen. */
bool
ContactDetector::isContactShouldBeServerd(Contact::Type type) const
{
    return
        type == Contact::Type::PlayerTouchEnemy ||
        type == Contact::Type::PlayerTouchWall;
}


/* Zwraca typ zdarzenia jaki
 * okreslilismy miedzy dwoma cialami. */
ContactDetector::Contact::Type
ContactDetector::getContactType(b2Body *bodyA, b2Body *bodyB) const
{
    BodyUserData* bodyUserDataA = (BodyUserData*)(bodyA->GetUserData());
    BodyUserData* bodyUserDataB = (BodyUserData*)(bodyB->GetUserData());

    BodyUserData::Type bodyTypeA = bodyUserDataA->getType();
    BodyUserData::Type bodyTypeB = bodyUserDataB->getType();


    const bool bodyIsPlayer =
            bodyTypeA == BodyUserData::Type::Player ||
            bodyTypeB == BodyUserData::Type::Player;

    const bool bodyIsEnemy =
            bodyTypeA == BodyUserData::Type::Enemy ||
            bodyTypeB == BodyUserData::Type::Enemy;

    const bool bodyIsWall =
            bodyTypeA == BodyUserData::Type::Wall ||
            bodyTypeB == BodyUserData::Type::Wall;


    Contact::Type contactType = Contact::Type::Empty;
    if(bodyIsPlayer && bodyIsEnemy)
    {
        contactType = Contact::Type::PlayerTouchEnemy;
    }

    if(bodyIsPlayer && bodyIsWall)
    {
        contactType = Contact::Type::PlayerTouchWall;
    }
    return contactType;
}


/* Funkcja konstruuje obiekt
 * dziennika zdarzen. Okresla
 * rowniez ktore z cial jest
 * graczem i autematycznie przypisuje
 * cialo gracza do bodyPtrFirst. */
ContactDetector::Contact::Info
ContactDetector::constructContactInfo(
        Contact::Type type,
        b2Body *contactBodyA,
        b2Body *contactBodyB) const
{
    BodyUserData* bodyUserDataA =
            (BodyUserData*)(contactBodyA->GetUserData());

    BodyUserData::Type bodyTypeA = bodyUserDataA->getType();

    Contact::Info newDiaryElement;
    if(bodyTypeA == BodyUserData::Type::Player)
    {
        newDiaryElement.bodyPtrFirst = contactBodyA;
        newDiaryElement.bodyPtrSecond = contactBodyB;
    } else {
        newDiaryElement.bodyPtrFirst = contactBodyB;
        newDiaryElement.bodyPtrSecond = contactBodyA;
    }
    newDiaryElement.type = type;

    return newDiaryElement;
}


/* Funkcja zwraca liste obiektow
 * dziennika zdarzen o interesujacym
 * nas typie. */
std::vector<ContactDetector::Contact::Info>
ContactDetector::getContactList(Contact::Type type)
{
    std::vector<ContactDetector::Contact::Info> toReturn;
    for(const Contact::Info& item : m_contactDiary){

        if(item.type == type){
            toReturn.push_back(item);
        }
    }
    return toReturn;
}


bool
ContactDetector::isContactListContains(Contact::Type type) const
{
    bool toReturn = false;
    for(const Contact::Info& item : m_contactDiary){

        if(item.type == type){
            toReturn = true;
            break;
        }
    }
    return toReturn;
}


bool
ContactDetector::isContactListIsEmpty() const
{
    return m_contactDiary.empty();
}


bool
ContactDetector::isContactInfoExistsInDiary(const Contact::Info& data) const
{
    bool toReturn = false;
    for(const Contact::Info& item : m_contactDiary){

        const bool condition =
                item.type == data.type &&
                item.bodyPtrFirst == data.bodyPtrFirst &&
                item.bodyPtrSecond == data.bodyPtrSecond;

        if(condition){
            toReturn = true;
            break;
        }
    }
    return toReturn;
}


int
ContactDetector::getContactInfoItemIndex(
        const ContactDetector::Contact::Info& data) const
{
    int toReturn = 0;

    const int listSize = m_contactDiary.size();
    for(int i = 0; i < listSize; ++i){

        const Contact::Info* item = &m_contactDiary.at(i);

        const bool condition =
                item->type == data.type &&
                item->bodyPtrFirst == data.bodyPtrFirst &&
                item->bodyPtrSecond == data.bodyPtrSecond;

        if(condition){
            toReturn = i;
            break;
        }
    }

    return toReturn;
}
