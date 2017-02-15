TEMPLATE = app
CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle
QT += core

win32: LIBS += -L$$PWD/lib/SFML/lib/release -lsfml-system
win32: LIBS += -L$$PWD/lib/SFML/lib/release -lsfml-window
win32: LIBS += -L$$PWD/lib/SFML/lib/release -lsfml-graphics
win32: LIBS += -L$$PWD/lib/SFML/lib/release -lsfml-audio
win32: LIBS += -L$$PWD/lib/Box2D/lib/release -llibBox2D
win32: LIBS += -L$$PWD/lib/PhysFS/lib/release -llibphysfs

unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lphysfs
unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lsfml-audio
unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lsfml-window
unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lsfml-system
unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lsfml-graphics
unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lsfml-audio
unix:!macx: LIBS += -L$$PWD/../../../../usr/lib/x86_64-linux-gnu/ -lBox2D

INCLUDEPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu
DEPENDPATH += $$PWD/../../../../usr/lib/x86_64-linux-gnu

INCLUDEPATH += $$PWD/lib/PhysFS/include
INCLUDEPATH += $$PWD/lib/SFML/include
INCLUDEPATH += $$PWD/lib/Box2D/include
INCLUDEPATH += $$PWD/src/converter/original_code
INCLUDEPATH += $$PWD/src/converter
INCLUDEPATH += $$PWD/src/editor/render
INCLUDEPATH += $$PWD/src/editor/json
INCLUDEPATH += $$PWD/src/editor
INCLUDEPATH += $$PWD/src/shared
INCLUDEPATH += $$PWD/src/core/fps_stabilizer
INCLUDEPATH += $$PWD/src/core/game_world/map_builder
INCLUDEPATH += $$PWD/src/core/game_world
INCLUDEPATH += $$PWD/src/core/assets
INCLUDEPATH += $$PWD/src/core/skills
INCLUDEPATH += $$PWD/src/core/physics
INCLUDEPATH += $$PWD/src/core/physics/map_items
INCLUDEPATH += $$PWD/src/core/physics/drawable_body
INCLUDEPATH += $$PWD/src/core/apps
INCLUDEPATH += $$PWD/src/core/apps/pixzen
INCLUDEPATH += $$PWD/src/core/margins
INCLUDEPATH += $$PWD/src/core/


DEPENDPATH += $$PWD/lib/PhysFS/include
DEPENDPATH += $$PWD/lib/SFML/include
DEPENDPATH += $$PWD/lib/Box2D/include




DISTFILES += \
    icon.ico \
    app.rc

RC_FILE += app.rc



SOURCES += \
    src/main.cpp \
    src/body_mover.cpp \
    src/observer.cpp \
    src/observer_data.cpp \
    src/contact_detector.cpp \
    src/body_user_data.cpp \
    src/world_contact_listener.cpp \
    src/body_jump_validator.cpp \
    src/fps_stabilizer.cpp \
    src/identified_body.cpp \
    src/movable_body.cpp \
    src/assets_zip.cpp \
    src/assets.cpp \
    src/assets_file.cpp \
    src/enemy_behavior.cpp \
    src/drawable_body.cpp \
    src/animator.cpp \
    src/game_map.cpp \
    src/game_obj_register.cpp \
    src/render_nt.cpp \
    src/mouse_manager.cpp \
    src/json.cpp \
    src/editor.cpp \
    src/render_nt_graphics.cpp \
    src/render_nt_graphics_painter.cpp \
    src/map_modifier.cpp \
    src/game_world.cpp \
    src/box_creator.cpp \
    src/map_builder.cpp \
    src/core_apps.cpp

HEADERS += \
    src/body_mover.h \
    src/observer.h \
    src/observer_data.h \
    src/contact_detector.h \
    src/body_user_data.h \
    src/world_contact_listener.h \
    src/body_jump_validator.h \
    src/fps_stabilizer.h \
    src/identified_body.h \
    src/movable_body.h \
    src/searchers.h \
    src/assets.h \
    src/enemy_behavior.h \
    src/control_keys.h \
    src/globals.h \
    src/drawable_body.h \
    src/animator.h \
    src/game_map.h \
    src/game_obj_register.h \
    src/render_nt.h \
    src/mouse_manager.h \
    src/editor_globals.h \
    src/json.h \
    src/editor.h \
    src/map_modifier.h \
    src/game_world.h \
    src/map_builder.h \
    src/box_creators.h \
    src/core_apps.h



