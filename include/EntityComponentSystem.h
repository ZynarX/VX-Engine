#include <iostream>
#include <SDL.h>
#pragma once

typedef struct {

} Property;

typedef struct
{
	int mode;
	int amount;
} Hostility;

typedef struct
{
	int X;
	int Y;
} Position;

typedef struct
{
	int X;
	int Y;
} Size;

typedef struct
{
	Uint32 Red;
	Uint32 Green;
	Uint32 Blue;
} Color;

typedef struct
{
	Position Position;
	Size Size;
} Transform;
