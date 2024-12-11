#pragma once
#include <iostream>
#include <memory>
#include <string>

#include "utils.h"
#include "structs.h"

//#define DEBUG_MESSAGE 1


enum class Shape
{
	Triangle,
	Square,
	Pentagon,
	Hexagon,
	Heptagon,
	Circle
};


extern Point2f	g_StartPosition;
extern Rectf	g_Window;
