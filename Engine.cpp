#include "Engine.h"

#include "Clock.h"
#include "Space.h"

void phys::Engine::Run()
{
	if(m_stopped)
	{
		m_stopped = false;
		m_paused = false;
        m_stop = false;
        m_pause = false;
		m_clock.Start();
    	while(!m_stop)
        {
            if(!m_pause)
            {
                m_paused = false;
                while (!m_pause)
                {
                    Update(m_clock.Lap());
                } 
                m_paused = true;
            }
        }
        m_stopped = true;
	}
}