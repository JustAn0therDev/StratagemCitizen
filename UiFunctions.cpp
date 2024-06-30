#include "UiFunctions.h"

bool UiFunctions::IsMouseInsideRectangle(Vector2 minPos, Vector2 maxPos)
{
    Vector2 mousePos = GetMousePosition();

    return mousePos.y >= minPos.y && 
           mousePos.y <= maxPos.y && 
           mousePos.x <= maxPos.x && 
           mousePos.x >= minPos.x;
}