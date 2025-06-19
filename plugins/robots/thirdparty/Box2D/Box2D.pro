TEMPLATE = lib

include(../../../../global.pri)

CONFIG += warn_off

INCLUDEPATH += $$PWD/Box2D/include $$PWD/Box2D/src

HEADERS = \
   $$PWD/Box2D/include/box2d/box2d.h \
   $$PWD/Box2D/src/aabb.h \
   $$PWD/Box2D/src/array.h \
   $$PWD/Box2D/src/arena_allocator.h \
   $$PWD/Box2D/src/atomic.h \
   $$PWD/Box2D/src/bitset.h \
   $$PWD/Box2D/src/body.h \
   $$PWD/Box2D/src/broad_phase.h \
   $$PWD/Box2D/src/constraint_graph.h \
   $$PWD/Box2D/src/contact.h \
   $$PWD/Box2D/src/contact_solver.h \
   $$PWD/Box2D/src/core.h \
   $$PWD/Box2D/src/id_pool.h \
   $$PWD/Box2D/src/island.h \
   $$PWD/Box2D/src/joint.h \
   $$PWD/Box2D/src/physics_world.h \
   $$PWD/Box2D/src/sensor.h \
   $$PWD/Box2D/src/shape.h \
   $$PWD/Box2D/src/solver.h \
   $$PWD/Box2D/src/solver_set.h \
   $$PWD/Box2D/src/table.h \

SOURCES = \
   $$PWD/Box2D/src/aabb.c \
   $$PWD/Box2D/src/arena_allocator.c \
   $$PWD/Box2D/src/array.c \
   $$PWD/Box2D/src/bitset.c \
   $$PWD/Box2D/src/body.c \
   $$PWD/Box2D/src/broad_phase.c \
   $$PWD/Box2D/src/constraint_graph.c \
   $$PWD/Box2D/src/contact.c \
   $$PWD/Box2D/src/contact_solver.c \
   $$PWD/Box2D/src/core.c \
   $$PWD/Box2D/src/distance.c \
   $$PWD/Box2D/src/distance_joint.c \
   $$PWD/Box2D/src/dynamic_tree.c \
   $$PWD/Box2D/src/geometry.c \
   $$PWD/Box2D/src/hull.c \
   $$PWD/Box2D/src/id_pool.c \
   $$PWD/Box2D/src/island.c \
   $$PWD/Box2D/src/joint.c \
   $$PWD/Box2D/src/manifold.c \
   $$PWD/Box2D/src/math_functions.c \
   $$PWD/Box2D/src/motor_joint.c \
   $$PWD/Box2D/src/mouse_joint.c \
   $$PWD/Box2D/src/mover.c \
   $$PWD/Box2D/src/physics_world.c \
   $$PWD/Box2D/src/prismatic_joint.c \
   $$PWD/Box2D/src/revolute_joint.c \
   $$PWD/Box2D/src/sensor.c \
   $$PWD/Box2D/src/shape.c \
   $$PWD/Box2D/src/solver.c \
   $$PWD/Box2D/src/solver_set.c \
   $$PWD/Box2D/src/table.c \
   $$PWD/Box2D/src/timer.c \
   $$PWD/Box2D/src/types.c \
   $$PWD/Box2D/src/weld_joint.c \
   $$PWD/Box2D/src/wheel_joint.c \
