TEMPLATE = lib

include(../../../../global.pri)

CONFIG += warn_off

INCLUDEPATH += $$PWD/Box2D/include $$PWD/Box2D/src


HEADERS = \
   $$PWD/Box2D/extern/glfw/include/GLFW/glfw3.h \
   $$PWD/Box2D/extern/glfw/include/GLFW/glfw3native.h \
   $$PWD/Box2D/extern/glfw/src/cocoa_joystick.h \
   $$PWD/Box2D/extern/glfw/src/cocoa_platform.h \
   $$PWD/Box2D/extern/glfw/src/egl_context.h \
   $$PWD/Box2D/extern/glfw/src/glfw_config.h \
   $$PWD/Box2D/extern/glfw/src/glx_context.h \
   $$PWD/Box2D/extern/glfw/src/internal.h \
   $$PWD/Box2D/extern/glfw/src/linux_joystick.h \
   $$PWD/Box2D/extern/glfw/src/mappings.h \
   $$PWD/Box2D/extern/glfw/src/nsgl_context.h \
   $$PWD/Box2D/extern/glfw/src/null_joystick.h \
   $$PWD/Box2D/extern/glfw/src/null_platform.h \
   $$PWD/Box2D/extern/glfw/src/osmesa_context.h \
   $$PWD/Box2D/extern/glfw/src/posix_thread.h \
   $$PWD/Box2D/extern/glfw/src/posix_time.h \
   $$PWD/Box2D/extern/glfw/src/wgl_context.h \
   $$PWD/Box2D/extern/glfw/src/win32_joystick.h \
   $$PWD/Box2D/extern/glfw/src/win32_platform.h \
   $$PWD/Box2D/extern/glfw/src/wl_platform.h \
   $$PWD/Box2D/extern/glfw/src/x11_platform.h \
   $$PWD/Box2D/extern/glfw/src/xkb_unicode.h \
   $$PWD/Box2D/include/box2d/b2_block_allocator.h \
   $$PWD/Box2D/include/box2d/b2_body.h \
   $$PWD/Box2D/include/box2d/b2_broad_phase.h \
   $$PWD/Box2D/include/box2d/b2_chain_shape.h \
   $$PWD/Box2D/include/box2d/b2_circle_shape.h \
   $$PWD/Box2D/include/box2d/b2_collision.h \
   $$PWD/Box2D/include/box2d/b2_contact.h \
   $$PWD/Box2D/include/box2d/b2_contact_manager.h \
   $$PWD/Box2D/include/box2d/b2_distance.h \
   $$PWD/Box2D/include/box2d/b2_distance_joint.h \
   $$PWD/Box2D/include/box2d/b2_draw.h \
   $$PWD/Box2D/include/box2d/b2_dynamic_tree.h \
   $$PWD/Box2D/include/box2d/b2_edge_shape.h \
   $$PWD/Box2D/include/box2d/b2_fixture.h \
   $$PWD/Box2D/include/box2d/b2_friction_joint.h \
   $$PWD/Box2D/include/box2d/b2_gear_joint.h \
   $$PWD/Box2D/include/box2d/b2_growable_stack.h \
   $$PWD/Box2D/include/box2d/b2_joint.h \
   $$PWD/Box2D/include/box2d/b2_math.h \
   $$PWD/Box2D/include/box2d/b2_motor_joint.h \
   $$PWD/Box2D/include/box2d/b2_mouse_joint.h \
   $$PWD/Box2D/include/box2d/b2_polygon_shape.h \
   $$PWD/Box2D/include/box2d/b2_prismatic_joint.h \
   $$PWD/Box2D/include/box2d/b2_pulley_joint.h \
   $$PWD/Box2D/include/box2d/b2_revolute_joint.h \
   $$PWD/Box2D/include/box2d/b2_rope.h \
   $$PWD/Box2D/include/box2d/b2_rope_joint.h \
   $$PWD/Box2D/include/box2d/b2_settings.h \
   $$PWD/Box2D/include/box2d/b2_shape.h \
   $$PWD/Box2D/include/box2d/b2_stack_allocator.h \
   $$PWD/Box2D/include/box2d/b2_time_of_impact.h \
   $$PWD/Box2D/include/box2d/b2_time_step.h \
   $$PWD/Box2D/include/box2d/b2_timer.h \
   $$PWD/Box2D/include/box2d/b2_weld_joint.h \
   $$PWD/Box2D/include/box2d/b2_wheel_joint.h \
   $$PWD/Box2D/include/box2d/b2_world.h \
   $$PWD/Box2D/include/box2d/b2_world_callbacks.h \
   $$PWD/Box2D/include/box2d/box2d.h \
   $$PWD/Box2D/src/dynamics/b2_chain_circle_contact.h \
   $$PWD/Box2D/src/dynamics/b2_chain_polygon_contact.h \
   $$PWD/Box2D/src/dynamics/b2_circle_contact.h \
   $$PWD/Box2D/src/dynamics/b2_contact_solver.h \
   $$PWD/Box2D/src/dynamics/b2_edge_circle_contact.h \
   $$PWD/Box2D/src/dynamics/b2_edge_polygon_contact.h \
   $$PWD/Box2D/src/dynamics/b2_island.h \
   $$PWD/Box2D/src/dynamics/b2_polygon_circle_contact.h \
   $$PWD/Box2D/src/dynamics/b2_polygon_contact.h

SOURCES = \
#   $$PWD/Box2D/extern/glfw/src/cocoa_time.c \
#   $$PWD/Box2D/extern/glfw/src/context.c \
#   $$PWD/Box2D/extern/glfw/src/egl_context.c \
#   $$PWD/Box2D/extern/glfw/src/glx_context.c \
#   $$PWD/Box2D/extern/glfw/src/init.c \
#   $$PWD/Box2D/extern/glfw/src/input.c \
#   $$PWD/Box2D/extern/glfw/src/linux_joystick.c \
#   $$PWD/Box2D/extern/glfw/src/monitor.c \
#   $$PWD/Box2D/extern/glfw/src/null_init.c \
#   $$PWD/Box2D/extern/glfw/src/null_joystick.c \
#   $$PWD/Box2D/extern/glfw/src/null_monitor.c \
#   $$PWD/Box2D/extern/glfw/src/null_window.c \
#   $$PWD/Box2D/extern/glfw/src/osmesa_context.c \
#   $$PWD/Box2D/extern/glfw/src/posix_thread.c \
#   $$PWD/Box2D/extern/glfw/src/posix_time.c \
#   $$PWD/Box2D/extern/glfw/src/vulkan.c \
#   $$PWD/Box2D/extern/glfw/src/wgl_context.c \
#   $$PWD/Box2D/extern/glfw/src/win32_init.c \
#   $$PWD/Box2D/extern/glfw/src/win32_joystick.c \
#   $$PWD/Box2D/extern/glfw/src/win32_monitor.c \
#   $$PWD/Box2D/extern/glfw/src/win32_thread.c \
#   $$PWD/Box2D/extern/glfw/src/win32_time.c \
#   $$PWD/Box2D/extern/glfw/src/win32_window.c \
#   $$PWD/Box2D/extern/glfw/src/window.c \
#   $$PWD/Box2D/extern/glfw/src/wl_init.c \
#   $$PWD/Box2D/extern/glfw/src/wl_monitor.c \
#   $$PWD/Box2D/extern/glfw/src/wl_window.c \
#   $$PWD/Box2D/extern/glfw/src/x11_init.c \
#   $$PWD/Box2D/extern/glfw/src/x11_monitor.c \
#   $$PWD/Box2D/extern/glfw/src/x11_window.c \
#   $$PWD/Box2D/extern/glfw/src/xkb_unicode.c \
   $$PWD/Box2D/src/collision/b2_broad_phase.cpp \
   $$PWD/Box2D/src/collision/b2_chain_shape.cpp \
   $$PWD/Box2D/src/collision/b2_circle_shape.cpp \
   $$PWD/Box2D/src/collision/b2_collide_circle.cpp \
   $$PWD/Box2D/src/collision/b2_collide_edge.cpp \
   $$PWD/Box2D/src/collision/b2_collide_polygon.cpp \
   $$PWD/Box2D/src/collision/b2_collision.cpp \
   $$PWD/Box2D/src/collision/b2_distance.cpp \
   $$PWD/Box2D/src/collision/b2_dynamic_tree.cpp \
   $$PWD/Box2D/src/collision/b2_edge_shape.cpp \
   $$PWD/Box2D/src/collision/b2_polygon_shape.cpp \
   $$PWD/Box2D/src/collision/b2_time_of_impact.cpp \
   $$PWD/Box2D/src/common/b2_block_allocator.cpp \
   $$PWD/Box2D/src/common/b2_draw.cpp \
   $$PWD/Box2D/src/common/b2_math.cpp \
   $$PWD/Box2D/src/common/b2_settings.cpp \
   $$PWD/Box2D/src/common/b2_stack_allocator.cpp \
   $$PWD/Box2D/src/common/b2_timer.cpp \
   $$PWD/Box2D/src/dynamics/b2_body.cpp \
   $$PWD/Box2D/src/dynamics/b2_chain_circle_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_chain_polygon_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_circle_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_contact_manager.cpp \
   $$PWD/Box2D/src/dynamics/b2_contact_solver.cpp \
   $$PWD/Box2D/src/dynamics/b2_distance_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_edge_circle_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_edge_polygon_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_fixture.cpp \
   $$PWD/Box2D/src/dynamics/b2_friction_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_gear_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_island.cpp \
   $$PWD/Box2D/src/dynamics/b2_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_motor_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_mouse_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_polygon_circle_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_polygon_contact.cpp \
   $$PWD/Box2D/src/dynamics/b2_prismatic_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_pulley_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_revolute_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_rope_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_weld_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_wheel_joint.cpp \
   $$PWD/Box2D/src/dynamics/b2_world.cpp \
   $$PWD/Box2D/src/dynamics/b2_world_callbacks.cpp \
   $$PWD/Box2D/src/rope/b2_rope.cpp

#INCLUDEPATH = \
#    $$PWD/Box2D/extern/glad/include/glad \
#    $$PWD/Box2D/extern/glad/include/KHR \
#    $$PWD/Box2D/extern/glfw/include/GLFW \
#    $$PWD/Box2D/extern/glfw/src \
#    $$PWD/Box2D/include/box2d \
#    $$PWD/Box2D/src/dynamics

#DEFINES =

