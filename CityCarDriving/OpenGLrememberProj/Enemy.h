#pragma once
#include <windows.h>
#include <iostream>

#include "ObjLoader.h"
#include <GL\gl.h>
#include <GL\glu.h>
#include "GL\glext.h"
#include <string>
#include <math.h>
#include "MyVector3d.h"
#include "Texture.h"
#include "MyOGL.h"

using namespace std;

class Enemy {
	int dx;
	ObjFile *obj;
	Texture tex;
public:
	Vector3 pos;
	float speed;
	float W, H;
	Enemy(ObjFile*, Vector3);
	void Move(int);
	void Draw(Texture*);
	bool Collide(Vector3, float, float);
};


Enemy::Enemy(ObjFile *obj_in, Vector3 obj_pos) {
	W = 4;
	H = 4;
	pos = obj_pos;
	dx = 1;
	speed = 1;
	obj = obj_in;
}
void Enemy::Draw(Texture *tex) {
	glPushMatrix();
	pos.setCoords(pos.X() + dx * speed, pos.Y(), pos.Z());
	glTranslatef(pos.X(), pos.Y(), pos.Z());
	glScalef(0.1, 0.1, 0.1);
	glRotatef(90, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	tex->bindTexture();
	obj->DrawObj();
	glPopMatrix();
}

void Enemy::Move(int d) {
	dx = d;
}

bool Enemy::Collide(Vector3 o_pos, float o_W, float o_H) {
	if ((o_pos.X() > pos.X() && o_pos.X() < pos.X() + W) && (o_pos.Y() > pos.Y() && o_pos.Y() < pos.Y() + H) ||
		(o_pos.X() + o_W > pos.X() && o_pos.X() + o_W < pos.X() + W) && (o_pos.Y() + o_H > pos.Y() && o_pos.Y() + o_H < pos.Y() + H))
	{
		return true;
	}
	return false;
}