#ifndef __SDL_WIDGET_H_
#define __SDL_WIDGET_H_

#include <SDL.h>

#include "globals.h"

sdl_graphic *make_sdl_graphic(int num, int x, int y, graphics_data *packs);
SDL_Rect *make_sdl_rect(int x, int y, int w, int h);

#include <SDL.h>

class sdl_widget
{
	public:
		sdl_widget(int num, int x, int y, graphics_data *packs);
		~sdl_widget();
		virtual void draw(SDL_Surface *display);
		
		//for tracking what the mouse is over
		void mouseOn();
		void mouseOff();

		friend class sdl_user;
	protected:
		int visible;	//determines if the widget should be drawn
		sdl_graphic *one;
		
		bool have_mouse;
		
		bool contains(int x, int y);	//does this widget contain the given point?
		
		void mouse_to(SDL_MouseMotionEvent *to);
		void mouse_from(SDL_MouseMotionEvent *from);
		void mouse_move(SDL_MouseMotionEvent *from, SDL_MouseMotionEvent *to);
		void mouse_click(SDL_MouseButtonEvent *here);
};

#endif