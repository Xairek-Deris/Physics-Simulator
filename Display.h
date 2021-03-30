#pragma once

#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_thread.h>

#include "Space.h"
#include "Vec.h"
#include "Window.h"

namespace phys
{
    class Display
    {
    public:
        Display(Window& window, const Space& space, const std::string& texture_filename);

        void Start();
        void Stop();
        void Set_Camera(Vector& position) { m_camera = position; }
        void Set_Zoom(double zoom) { m_zoom = zoom; }

    private:
        SDL_Surface* m_surface;
        SDL_Thread* m_thread;
        Window* m_window;
        const Space* m_space;
        Vector m_camera;
        double m_zoom;
        bool m_stop;
        static int Function(void* display);
    };
}