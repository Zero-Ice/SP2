#include "SceneSP.h"
#include "Application.h"

bool SceneSP::AABBCheck(const Obj &box1,const Obj &box2)
{

	return (box1.max.x > box2.min.x && 
		box1.min.x < box2.max.x && 
		box1.max.y > box2.min.y && 
		box1.min.y < box2.max.y &&
		box1.max.z > box2.min.z && 
		box1.min.z < box2.max.z);


}

void SceneSP::collisionprevent(vector<Obj>, Vector3 camerathing) 
{
	bool moveX = true ;

	Vector3 player = camerathing + camera.position; 

	Obj checkColli , forX , forZ;

	checkColli.max = player ;
	checkColli.min = player ;

	forX.max = Vector3(player.x , camera.position.y , camera.position.z ) ;
	forX.min = Vector3(player.x , camera.position.y , camera.position.z ) ;

	forZ.max = Vector3(camera.position.x , camera.position.y , player.z );
	forZ.min = Vector3(camera.position.x , camera.position.y , player.z );

	for(int x = 1 ; x < OBJ.size() ; ++x)
	{
		if ( AABBCheck(OBJ[x],checkColli)) 
		{
			//if x axis is the one touching
			if ( AABBCheck ( OBJ[x], forX)) 
			{
				camerathing.x = 0 ;
				moveX = false;
			}

			//if z axis is the one touching
			if ( AABBCheck ( OBJ[x], forZ)) 
			{
				camerathing.z = 0 ;
				moveX = true;
			}
		}
	}
	camera.position.x += camerathing.x ;
	camera.position.z += camerathing.z ;
	camera.target.x += camerathing.x ;
	camera.target.z += camerathing.z ;
	camera.targetwhere.x += camerathing.x;
	camera.targetwhere.z += camerathing.z;

}

void SceneSP::updatecollision(double dt)
{
	float MOVE_SPEED = 20.0f;

	updateobj();

	if (Application::IsKeyPressed('W')) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 precollide = view * dt * MOVE_SPEED; // if it moved it will be here 

		collisionprevent(OBJ,precollide);

	}
	else if (Application::IsKeyPressed('S')) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 backside = -view * dt * MOVE_SPEED;

		collisionprevent(OBJ,backside);

	}
	else if (Application::IsKeyPressed('D')) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0;
		Vector3 right = view.Cross(camera.up);
		right = right * dt * MOVE_SPEED;

		collisionprevent(OBJ,right);

	}
	else if (Application::IsKeyPressed('A')) 
	{

		Vector3 view = (camera.target - camera.position).Normalize();
		view.y = 0 ;
		Vector3 left = view.Cross(camera.up);
		left = -left * dt * MOVE_SPEED;

		collisionprevent(OBJ,left);
	}


	if ( AABBCheck(seewhere,OBJ[1]) == true )
		collisionsia = true;
	else
		collisionsia = false;

}

void SceneSP::updateobj()
{
	OBJ[0].max = camera.position + Vector3(1,1,1);
	OBJ[0].min = camera.position - Vector3(1,1,1);

	seewhere.max = camera.targetwhere + Vector3(0.2,0.1,0.2);
	seewhere.min = camera.targetwhere - Vector3(0.2,0.1,0.2);

}