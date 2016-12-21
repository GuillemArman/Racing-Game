#include "PhysVehicle3D.h"
#include "Primitive.h"
#include "Bullet/include/btBulletDynamicsCommon.h"

// ----------------------------------------------------------------------------
VehicleInfo::~VehicleInfo()
{
	//if(wheels != NULL)
		//delete wheels;
}

// ----------------------------------------------------------------------------
PhysVehicle3D::PhysVehicle3D(btRigidBody* body, btRaycastVehicle* vehicle, const VehicleInfo& info) : PhysBody3D(body), vehicle(vehicle), info(info)
{
	body->setUserPointer(this);
}

// ----------------------------------------------------------------------------
PhysVehicle3D::~PhysVehicle3D()
{
	delete vehicle;
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Render(Color color)
{
	Cylinder wheel;

	wheel.color = Black;

	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		wheel.radius = info.wheels[0].radius;
		wheel.height = info.wheels[0].width;

		vehicle->updateWheelTransform(i);
		vehicle->getWheelInfo(i).m_worldTransform.getOpenGLMatrix(&wheel.transform);

		wheel.Render();
	}

	btQuaternion q = vehicle->getChassisWorldTransform().getRotation();

	Cube chassis(info.chassis_size.x, info.chassis_size.y, info.chassis_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&chassis.transform);

	btVector3 offset(info.chassis_offset.x, info.chassis_offset.y, info.chassis_offset.z);
	offset = offset.rotate(q.getAxis(), q.getAngle());

	chassis.transform.M[12] += offset.getX();
	chassis.transform.M[13] += offset.getY();
	chassis.transform.M[14] += offset.getZ();

	chassis.color = color;
	chassis.Render();

	//car top

	Cube winger(info.winger_size.x, info.winger_size.y, info.winger_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&winger.transform);

	btVector3 offset2(info.winger_offset.x, info.winger_offset.y, info.winger_offset.z);
	offset2 = offset2.rotate(q.getAxis(), q.getAngle());

	winger.transform.M[12] += offset2.getX();
	winger.transform.M[13] += offset2.getY();
	winger.transform.M[14] += offset2.getZ();

	winger.color = Black;
	winger.Render();

	// sticks

	Cube stick(info.stick_size.x, info.stick_size.y, info.stick_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stick.transform);

	btVector3 offset3(info.stick_offset.x, info.stick_offset.y, info.stick_offset.z);
	offset3 = offset3.rotate(q.getAxis(), q.getAngle());

	stick.transform.M[12] += offset3.getX();
	stick.transform.M[13] += offset3.getY();
	stick.transform.M[14] += offset3.getZ();

	stick.color = White;
	stick.Render();

	Cube stick2(info.stick2_size.x, info.stick2_size.y, info.stick2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&stick2.transform);

	btVector3 offset4(info.stick2_offset.x, info.stick2_offset.y, info.stick2_offset.z);
	offset4 = offset4.rotate(q.getAxis(), q.getAngle());

	stick2.transform.M[12] += offset4.getX();
	stick2.transform.M[13] += offset4.getY();
	stick2.transform.M[14] += offset4.getZ();

	stick2.color = White;
	stick2.Render();

	// centre car

	Cube centre(info.centre_size.x, info.centre_size.y, info.centre_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&centre.transform);

	btVector3 offset5(info.centre_offset.x, info.centre_offset.y, info.centre_offset.z);
	offset5 = offset5.rotate(q.getAxis(), q.getAngle());

	centre.transform.M[12] += offset5.getX();
	centre.transform.M[13] += offset5.getY();
	centre.transform.M[14] += offset5.getZ();

	centre.color = Blue;
	centre.Render();

	// front = back

	Cube back(info.back_size.x, info.back_size.y, info.back_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&back.transform);

	btVector3 offset6(info.back_offset.x, info.back_offset.y, info.back_offset.z);
	offset6 = offset6.rotate(q.getAxis(), q.getAngle());

	back.transform.M[12] += offset6.getX();
	back.transform.M[13] += offset6.getY();
	back.transform.M[14] += offset6.getZ();

	back.color = color;
	back.Render();

	// lights

	Cube light1(info.light1_size.x, info.light1_size.y, info.light1_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&light1.transform);

	btVector3 offset7(info.light1_offset.x, info.light1_offset.y, info.light1_offset.z);
	offset7 = offset7.rotate(q.getAxis(), q.getAngle());

	light1.transform.M[12] += offset7.getX();
	light1.transform.M[13] += offset7.getY();
	light1.transform.M[14] += offset7.getZ();

	light1.color = Yellow;
	light1.Render();

	Cube light2(info.light2_size.x, info.light2_size.y, info.light2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&light2.transform);

	btVector3 offset8(info.light2_offset.x, info.light2_offset.y, info.light2_offset.z);
	offset8 = offset8.rotate(q.getAxis(), q.getAngle());

	light2.transform.M[12] += offset8.getX();
	light2.transform.M[13] += offset8.getY();
	light2.transform.M[14] += offset8.getZ();

	light2.color = Yellow;
	light2.Render();

	//car top

	Cube _winger(info._winger_size.x, info._winger_size.y, info._winger_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&_winger.transform);

	btVector3 _offset2(info._winger_offset.x, info._winger_offset.y, info._winger_offset.z);
	_offset2 = _offset2.rotate(q.getAxis(), q.getAngle());

	_winger.transform.M[12] += _offset2.getX();
	_winger.transform.M[13] += _offset2.getY();
	_winger.transform.M[14] += _offset2.getZ();

	_winger.color = Black;
	_winger.Render();

	// sticks

	Cube _stick(info._stick_size.x, info._stick_size.y, info._stick_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&_stick.transform);

	btVector3 _offset3(info._stick_offset.x, info._stick_offset.y, info._stick_offset.z);
	_offset3 = _offset3.rotate(q.getAxis(), q.getAngle());

	_stick.transform.M[12] += _offset3.getX();
	_stick.transform.M[13] += _offset3.getY();
	_stick.transform.M[14] += _offset3.getZ();

	_stick.color = White;
	_stick.Render();


	Cube _stick2(info._stick2_size.x, info._stick2_size.y, info._stick2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&_stick2.transform);

	btVector3 _offset4(info._stick2_offset.x, info._stick2_offset.y, info._stick2_offset.z);
	_offset4 = _offset4.rotate(q.getAxis(), q.getAngle());

	_stick2.transform.M[12] += _offset4.getX();
	_stick2.transform.M[13] += _offset4.getY();
	_stick2.transform.M[14] += _offset4.getZ();

	_stick2.color = White;
	_stick2.Render();

	// centre car

	Cube _centre(info._centre_size.x, info._centre_size.y, info._centre_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&_centre.transform);

	btVector3 _offset5(info._centre_offset.x, info._centre_offset.y, info._centre_offset.z);
	_offset5 = _offset5.rotate(q.getAxis(), q.getAngle());

	_centre.transform.M[12] += _offset5.getX();
	_centre.transform.M[13] += _offset5.getY();
	_centre.transform.M[14] += _offset5.getZ();

	_centre.color = Blue;
	_centre.Render();

	// front = back

	Cube _back(info._back_size.x, info._back_size.y, info._back_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&_back.transform);

	btVector3 _offset6(info._back_offset.x, info._back_offset.y, info._back_offset.z);
	_offset6 = _offset6.rotate(q.getAxis(), q.getAngle());

	_back.transform.M[12] += _offset6.getX();
	_back.transform.M[13] += _offset6.getY();
	_back.transform.M[14] += _offset6.getZ();

	_back.color = color;
	_back.Render();

	// lights

	Cube _light1(info._light1_size.x, info._light1_size.y, info._light1_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&_light1.transform);

	btVector3 _offset7(info._light1_offset.x, info._light1_offset.y, info._light1_offset.z);
	_offset7 = _offset7.rotate(q.getAxis(), q.getAngle());

	_light1.transform.M[12] += _offset7.getX();
	_light1.transform.M[13] += _offset7.getY();
	_light1.transform.M[14] += _offset7.getZ();

	_light1.color = Yellow;
	_light1.Render();

	Cube _light2(info._light2_size.x, info._light2_size.y, info._light2_size.z);
	vehicle->getChassisWorldTransform().getOpenGLMatrix(&_light2.transform);

	btVector3 _offset8(info._light2_offset.x, info._light2_offset.y, info._light2_offset.z);
	_offset8 = _offset8.rotate(q.getAxis(), q.getAngle());

	_light2.transform.M[12] += _offset8.getX();
	_light2.transform.M[13] += _offset8.getY();
	_light2.transform.M[14] += _offset8.getZ();

	_light2.color = Yellow;
	_light2.Render();
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::ApplyEngineForce(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].drive == true)
		{
			vehicle->applyEngineForce(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Brake(float force)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].brake == true)
		{
			vehicle->setBrake(force, i);
		}
	}
}

// ----------------------------------------------------------------------------
void PhysVehicle3D::Turn(float degrees)
{
	for(int i = 0; i < vehicle->getNumWheels(); ++i)
	{
		if(info.wheels[i].steering == true)
		{
			vehicle->setSteeringValue(degrees, i);
		}
	}
}

// ----------------------------------------------------------------------------
float PhysVehicle3D::GetKmh() const
{
	return vehicle->getCurrentSpeedKmHour();
}