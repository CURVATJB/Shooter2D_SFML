#include "Managers/ScoreManager.h"


void ScoreManager::ModifyScore(int modif)
{
    m_score += modif;
    
    m_signal(m_score);
}

