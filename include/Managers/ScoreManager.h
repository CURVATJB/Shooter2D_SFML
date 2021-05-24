#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "Signal.h"

class ScoreManager
{
public:
    static void ModifyScore(int modif);

    //donne le signal émit par cette classe
    static Signal<int>& GetSignal()
    {
        return m_signal;
    }

    inline static Signal<int> m_signal;

	static int GetScore()
	{
        return m_score;
	}
	
private:
    ScoreManager() = default;
    
    static inline int m_score;

};
#endif
