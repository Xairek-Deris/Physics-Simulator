#pragma once

#include <SDL2/SDL.h>

#include "Box.h"
#include "Events.h"
#include "Point.h"
#include "Texture.h"

namespace phys
{
    class Button
    {
    public:
        Button(const Texture& tex_up, const Texture& tex_down, const Box& box, Event_Loop& e_loop, void (*handler)(void*), void* data, bool shown, bool enabled)
        : m_texture_up{ &tex_up }, m_texture_down{ &tex_down }, m_box{ box }, m_event_loop{ &e_loop }, m_on_click{ handler }, m_data{ data }, m_pressed{ false }, m_shown{ shown }, m_enabled{ enabled } {}

        void Click() { m_event_loop->Push(m_on_click, m_data); }
        void MB1Down(Point point) { if(m_box.Contains(point)) m_pressed = true; }
        void MB1Up(Point point) { if(m_pressed && m_box.Contains(point)) Click(); m_pressed = false; }
        void Paint() 
        {
            if(m_shown)
            {
                if(m_pressed) 
                    m_texture_down->Draw(m_box.Get_SDL_Rect());
                else m_texture_up->Draw(m_box.Get_SDL_Rect());
            }
        }
        bool Is_Shown() { return m_shown; }
        void Show() { m_shown = true; }
        void Hide() { m_shown = false; }
        bool Is_Enabled() { return m_enabled; }
        void Enable() { m_enabled = true; }
        void Disable() { m_enabled = false; }

    private:
        const Texture* m_texture_up;
        const Texture* m_texture_down;
        Box m_box;
        Event_Loop* m_event_loop;
        void (*m_on_click)(void* data);
        void* m_data;
        bool m_pressed;
        bool m_shown;
        bool m_enabled;
    };
}