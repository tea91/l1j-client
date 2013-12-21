#include "draw_maint_sprites.h"

#include "globals.h"
#include "resources/prepared_graphics.h"
#include "sdl_user.h"
#include "widgets/sdl_animate_button.h"
#include "widgets/sdl_input_box.h"
#include "widgets/sdl_text_button.h"
#include "widgets/sprite.h"
#include "widgets/text_box.h"

load_ptr::load_ptr(draw_maint_sprites *bla, int val)
{
	ref = bla;
	which = val;
}

void load_ptr::go()
{
	
}

draw_maint_sprites::draw_maint_sprites(sdl_user *self)
	: sdl_drawmode(self)
{
	owner->game_music.change_music("sound/music0.mp3");

	num_gfx = 0;
	gfx = 0;
	
	num_widgets = 2;

	widgets = new sdl_widget*[num_widgets];
	
	widget_key_focus = 0;
	
	x = 2786;	//dark elf is 2786
	//2778 is a good blob sprite
	y = 8;

	widgets[0] = 0;
	widgets[1] = new sdl_text_button("Return", 310, 420, owner, 
		(funcptr*)new dam_ptr(owner, DRAWMODE_ADMIN_MAIN));
	widgets[1]->set_key_focus(true);
	redo_sprite();
	//widgets[num_servers+1] = new sprite(50, 50, "6258-0.spr", owner);
		//6256-173 nothing?
		//6256-181 nothing?
}

draw_maint_sprites::~draw_maint_sprites()
{
}

void draw_maint_sprites::key_press(SDL_KeyboardEvent *button)
{
	while (SDL_mutexP(draw_mtx) == -1) {};
	sdl_drawmode::key_press(button);
	if (button->type == SDL_KEYDOWN)
	{
		switch(button->keysym.sym)
		{
			case SDLK_LEFT:
				y--;
				redo_sprite();
				break;
			case SDLK_RIGHT:
				y++;
				redo_sprite();
				break;
			case SDLK_UP:
				x++;
				redo_sprite();
				break;
			case SDLK_DOWN:
				x--;
				redo_sprite();
				break;
			case SDLK_PAGEUP:
				x += 100;
				redo_sprite();
				break;
			case SDLK_PAGEDOWN:
				x -= 100;
				if (x < 0)
					x = 0;
				redo_sprite();
				break;
			default:
				break;
		}
	}
	SDL_mutexV(draw_mtx);
}

bool draw_maint_sprites::mouse_leave()
{
	return false;
}

void draw_maint_sprites::redo_sprite()
{
	while (SDL_mutexP(draw_mtx) == -1) {};
	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (widgets[0] != 0)
	{
		delete widgets[0];
		widgets[0] = 0;
	}
	widgets[0] = new sprite(320, 400, owner);//new_name, owner);
	((sprite*)(widgets[0]))->load(320, 400, x, y);
	SDL_mutexV(draw_mtx);
}

bool draw_maint_sprites::quit_request()
{
	//owner->stop_thread = true;
	return true;
}

void draw_maint_sprites::draw(SDL_Surface *display)
{
	while (SDL_mutexP(draw_mtx) == -1) {};
	SDL_FillRect(display, NULL, 0x1234);
	char dispstr[255];
	sprintf(dispstr, "Sprite %d-%d", x, y);
	lineage_font.draw(display, 220, 280, dispstr, 0xFFFE);
	sdl_drawmode::draw(display);
	SDL_mutexV(draw_mtx);
}