#include "Takistan.h"

ImVec2 DayZ::Takistan::translatePoint(const DMARender::Vector3& gamePoint)
{
    return ImVec2(gamePoint.x, 12736.0f - gamePoint.z);
}