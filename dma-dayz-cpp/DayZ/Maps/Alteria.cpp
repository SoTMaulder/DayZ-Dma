#include "Alteria.h"

ImVec2 DayZ::Alteria::translatePoint(const DMARender::Vector3& gamePoint)
{
    return ImVec2(gamePoint.x, 8448.0f - gamePoint.z);
}
