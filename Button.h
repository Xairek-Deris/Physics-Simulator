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
        Button(const Texture& tex_def, const Texture& tex_press, const Texture& tex_dis, const Texture& tex_hov, const Box& box, Event_Loop& e_loop, void (*handler)(void*), void* data, bool shown, bool enabled)
        : m_texture_default{ &tex_def }, m_texture_pressed{ &tex_press }, m_texture_disabled{ &tex_dis }, m_texture_hovered{ &tex_dis }, m_box{ box }, m_event_loop{ &e_loop }, m_on_click{ handler }, m_data{ data }, 
            m_pressed{ false }, m_shown{ shown }, m_enabled{ enabled }, m_hovered{ false }  {}

        void Click() { m_event_loop->Push(m_on_click, m_data); }
        void MB1Down(const Point& point) { if(m_enabled && m_box.Contains(point)) m_pressed = true; }
        void MB1Up(const Point& point) { if(m_pressed && m_box.Contains(point)) Click(); m_pressed = false; }
        void Hover(const Point& point) { if(m_box.Contains(point)) m_hovered = true; else m_hovered = false; }
        void Paint() 
        {
            if(m_shown)
            {
                if(m_pressed) 
                    m_texture_pressed->Draw(m_box.Get_SDL_Rect());
                else m_texture_default->Draw(m_box.Get_SDL_Rect());
            }
        }
        bool Is_Shown() { return m_shown; }
        void Show() { m_shown = true; }
        void Hide() { m_shown = false; }
        bool Is_Enabled() { return m_enabled; }
        void Enable() { m_enabled = true; }
        void Disable() { m_enabled = false; }

    private:
        const Texture* m_texture_default;
        const Texture* m_texture_pressed;
        const Texture* m_texture_disabled;
        const Texture* m_texture_hovered;
        Box m_box;
        Event_Loop* m_event_loop;
        void (*m_on_click)(void* data);
        void* m_data;
        bool m_pressed;
        bool m_shown;
        bool m_enabled;
        bool m_hovered;
    };
}