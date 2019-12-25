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

class Player {
	float speed;
	float dx, dy;
public:
	Vector3 pos;
	int W, H;
	Player(Vector3);
	void Keys();
	void Draw(ObjFile*, Texture*);
};

Player::Player(Vector3 obj_pos) {
	W = 2;
	H = 3;
	pos = obj_pos;
	dx = 0;
	dy = 0;
	speed = 0.5;
}
void Player::Keys() {
	if (OpenGL::isKeyPressed('D'))
	{
		dy = 1;
	}
	if (OpenGL::isKeyPressed('A'))
	{
		dy = -1;
	}
	if (OpenGL::isKeyPressed('W'))
	{
		dx = -1;
	}
	if (OpenGL::isKeyPressed('S'))
	{
		dx = 0.5;
	}
}
void Player::Draw(ObjFile *obj, Texture *tex) {
	glPushMatrix();
	pos.setCoords(pos.X() + dx * speed, pos.Y() + dy * speed, pos.Z());
	if(pos.Y() <= -6)
		pos.setCoords(pos.X(), -6, pos.Z());
	if(pos.Y() >= 6)
		pos.setCoords(pos.X(), 6, pos.Z());
	glTranslatef(pos.X(), pos.Y(), pos.Z());
	glScalef(1.5, 1.5, 1.5);
	glRotatef(90, 1, 0, 0);
	glRotatef(-90, 0, 1, 0);
	dx = 0;
	dy = 0;
	tex->bindTexture();
	obj->DrawObj();
	glPopMatrix();
}