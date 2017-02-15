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


#include "game_obj_register.h"

std::shared_ptr<GameObjRegister> GameObjRegister::ptr = nullptr;

GameObjRegister::GameObjRegister()
{
    list[Index::Empty]  = std::string("EMPTY");
    list[Index::Player] = std::string("HERO");
    list[Index::Enemy]  = std::string("STR_ENEMY");
    list[Index::MapFlor] = std::string("MAP_FLOR");
    list[Index::MapWall] = std::string("MAP_WALL");
    list[Index::MapFlorUp] = std::string("MAP_FLOR_UP");

    list[Index::MapInvisableWall]   = std::string("MAP_INVISABLE_WALL");
    list[Index::MapRotatedPlatform] = std::string("MAP_ROTATED");
}

GameObjRegister* GameObjRegister::get()
{
    if(ptr == nullptr){
        ptr = std::make_shared<GameObjRegister>(GameObjRegister());
    }
    return ptr.get();
}
