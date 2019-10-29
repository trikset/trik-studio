TEMPLATE = lib

include(../../../../global.pri)

CONFIG += warn_off

INCLUDEPATH += $$PWD/Box2D

HEADERS += \
	$$PWD/Box2D/Box2D/Box2D.h \
	$$PWD/Box2D/Box2D/Common/b2Math.h \
	$$PWD/Box2D/Box2D/Common/b2BlockAllocator.h \
	$$PWD/Box2D/Box2D/Common/b2StackAllocator.h \
	$$PWD/Box2D/Box2D/Common/b2Settings.h \
	$$PWD/Box2D/Box2D/Common/b2GrowableStack.h \
	$$PWD/Box2D/Box2D/Common/b2Draw.h \
	$$PWD/Box2D/Box2D/Common/b2Timer.h \
	$$PWD/Box2D/Box2D/Dynamics/b2TimeStep.h \
	$$PWD/Box2D/Box2D/Dynamics/b2ContactManager.h \
	$$PWD/Box2D/Box2D/Dynamics/b2World.h \
	$$PWD/Box2D/Box2D/Dynamics/b2Island.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2Contact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.h \
	$$PWD/Box2D/Box2D/Dynamics/b2Body.h \
	$$PWD/Box2D/Box2D/Dynamics/b2Fixture.h \
	$$PWD/Box2D/Box2D/Dynamics/b2WorldCallbacks.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2GearJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2Joint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.h \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.h \
	$$PWD/Box2D/Box2D/Rope/b2Rope.h \
	$$PWD/Box2D/Box2D/Collision/b2TimeOfImpact.h \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2Shape.h \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2ChainShape.h \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2EdgeShape.h \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2CircleShape.h \
	$$PWD/Box2D/Box2D/Collision/b2BroadPhase.h \
	$$PWD/Box2D/Box2D/Collision/b2Collision.h \
	$$PWD/Box2D/Box2D/Collision/b2Distance.h \
	$$PWD/Box2D/Box2D/Collision/b2DynamicTree.h \

SOURCES += \
	$$PWD/Box2D/Box2D/Common/b2StackAllocator.cpp \
	$$PWD/Box2D/Box2D/Common/b2BlockAllocator.cpp \
	$$PWD/Box2D/Box2D/Common/b2Math.cpp \
	$$PWD/Box2D/Box2D/Common/b2Timer.cpp \
	$$PWD/Box2D/Box2D/Common/b2Settings.cpp \
	$$PWD/Box2D/Box2D/Common/b2Draw.cpp \
	$$PWD/Box2D/Box2D/Dynamics/b2ContactManager.cpp \
	$$PWD/Box2D/Box2D/Dynamics/b2Body.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2Contact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.cpp \
	$$PWD/Box2D/Box2D/Dynamics/b2World.cpp \
	$$PWD/Box2D/Box2D/Dynamics/b2Fixture.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2GearJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2Joint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.cpp \
	$$PWD/Box2D/Box2D/Dynamics/b2WorldCallbacks.cpp \
	$$PWD/Box2D/Box2D/Dynamics/b2Island.cpp \
	$$PWD/Box2D/Box2D/Rope/b2Rope.cpp \
	$$PWD/Box2D/Box2D/Collision/b2DynamicTree.cpp \
	$$PWD/Box2D/Box2D/Collision/b2CollideEdge.cpp \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2CircleShape.cpp \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2EdgeShape.cpp \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2ChainShape.cpp \
	$$PWD/Box2D/Box2D/Collision/Shapes/b2PolygonShape.cpp \
	$$PWD/Box2D/Box2D/Collision/b2BroadPhase.cpp \
	$$PWD/Box2D/Box2D/Collision/b2CollidePolygon.cpp \
	$$PWD/Box2D/Box2D/Collision/b2TimeOfImpact.cpp \
	$$PWD/Box2D/Box2D/Collision/b2Collision.cpp \
	$$PWD/Box2D/Box2D/Collision/b2CollideCircle.cpp \
	$$PWD/Box2D/Box2D/Collision/b2Distance.cpp \
