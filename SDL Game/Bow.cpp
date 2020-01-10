#include "Bow.h"

Vector2D Bow::bowSize = { 60.0f, 80.0f };
Vector2D Bow::bowOffsetIdle[] = { {14.0f, 58.0f}, {16.0f, 54.0f}, {16.0f, 50.0f}, {16.0f, 50.0f} };
Vector2D Bow::bowOffsetWalk[] = { {6.0f, 54.0f}, {-30.0f, 22.0f}, {-18.0f, 50.0f}, {-6.0f, 24.0f} };
double Bow::bowOffsetAngleWalk[] = { 315.0, 315.0, 270.0, 270.0 };