#include "background.h"
#include "function.h"
#include "tile_map.h"
#include "character.h"
#include "npc.h"
#include "Cham.h"
#include "SmartMap.h"
#include "fire.h"

BackGround g_background;

bool Init() {
	int res = SDL_Init(SDL_INIT_VIDEO);
	if (res < 0) return false;

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	g_window = SDL_CreateWindow("game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (g_window != NULL) {
		g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_screen != 0) {
			SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			int ImgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(ImgFlags) && ImgFlags)) {
				return false;
			}
			else return true;
		}
	}
	return true;
}

bool LoadBackGround() {
	bool res = g_background.LoadImg("img/background1.jpg", g_screen);
	if (res == false) return false;
	else return true;
}

void close() {
	Mix_Quit();
	g_background.Free();
	SDL_DestroyRenderer(g_screen);
	g_screen = NULL;
	SDL_DestroyWindow(g_window);
	g_window = NULL;
	IMG_Quit();
	SDL_Quit();
}


int main(int argc, char* argv[]) {
	srand(time(0));

	if (Init() == false) return -1;
	if (LoadBackGround() == false) return -1;

	srand(time(0));

	GameMap game_map;
	game_map.LoadMap("map/bando3.txt");
	game_map.LoadPixel(g_screen);
	Map g_map = game_map.GetMap();


	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048);
	Mix_Music* g_music;
	g_music = Mix_LoadMUS("music/musicgame.mp3");
	Mix_PlayMusic(g_music, -1);

	SmartMap g_smart(g_map);

	Cham g_cham;
	g_cham.LoadImg("img/cham1.png", g_screen);

	Character g_player;
	g_player.LoadImg("img/pacnu.png", g_screen);
	
	
	NPC g_npc(750, 500);
	g_npc.LoadImg("img/maxanh.png", g_screen);

	NPC g_npc01(700, 500);
	g_npc01.LoadImg("img/mahong.png", g_screen);

	NPC g_npc02(650, 500);
	g_npc02.LoadImg("img/mado.png", g_screen);

	NPC g_npc03(600, 500);
	g_npc03.LoadImg("img/macam.png", g_screen);


	Fire g_fire01(50, 400);
	g_fire01.LoadImg("img/fire.png", g_screen);

	Fire g_fire02(150, 1000);
	g_fire02.LoadImg("img/fire.png", g_screen);

	Fire g_fire03(950, 1100);
	g_fire03.LoadImg("img/fire.png", g_screen);

	Fire g_fire04(1250, 650);
	g_fire04.LoadImg("img/fire.png", g_screen);

	int i = 0;
	bool quit = false;
	while (!quit) {
		if (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				quit = true;
			}
			else {
				g_player.Move(g_event);
				
				
				
				//cout << i++ << endl;

			}
			
		}

		

		g_player.Go(g_map, g_smart);
		g_player.MoveMapForCharacter(g_map);
		g_player.SetMapXY(g_map.now_x_, g_map.now_y_);

		g_smart.FollowCharacter(g_player.Getx_Pos(), g_player.Gety_Pos());


		
		//if (g_npc01.Motion(g_player.Getx_Pos(), g_player.Gety_Pos())) {		
		//			g_npc01.NpcVirtualMove(g_player.Getx_Pos(), g_player.Gety_Pos(), g_map);
					//cout << " ngu" << endl;
					//g_npc01.b();
		//}
		//if (g_npc01.LuaTheo(g_player.Getx_Pos(), g_player.Gety_Pos(), g_map ) ) {
		//	cout << true;
		//}

		
		g_npc.Move(g_map, g_smart);
		g_npc.SetMapXYNPC(g_map.now_x_, g_map.now_y_);

		g_npc01.Move(g_map, g_smart);
		g_npc01.SetMapXYNPC(g_map.now_x_, g_map.now_y_);
		

		g_npc02.Move(g_map, g_smart);
		g_npc02.SetMapXYNPC(g_map.now_x_, g_map.now_y_);
		
		g_npc03.Move(g_map, g_smart);
		g_npc03.SetMapXYNPC(g_map.now_x_, g_map.now_y_);

		
		g_cham.SetMapCham(g_map.now_x_, g_map.now_y_);
		g_cham.Delete(g_player.Getx_Pos(), g_player.Gety_Pos());

		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);

		game_map.Setmap(g_map);
		game_map.DrawMap(g_screen);


		g_cham.ShowCham(g_screen);

		g_player.Show(g_screen);

		g_npc.ShowNPC(g_screen);
		g_npc01.ShowNPC(g_screen);
		g_npc02.ShowNPC(g_screen);
		g_npc03.ShowNPC(g_screen);

		g_fire01.SetMapXYFire(g_map.now_x_, g_map.now_y_);
		g_fire01.ShowFire(g_screen);
		g_fire02.SetMapXYFire(g_map.now_x_, g_map.now_y_);
		g_fire02.ShowFire(g_screen);
		g_fire03.SetMapXYFire(g_map.now_x_, g_map.now_y_);
		g_fire03.ShowFire(g_screen);
		g_fire04.SetMapXYFire(g_map.now_x_, g_map.now_y_);
		g_fire04.ShowFire(g_screen);

		if (g_npc.LoseNPC(g_player.Getx_Pos(), g_player.Gety_Pos() ) ) i++;
		if (g_npc01.LoseNPC(g_player.Getx_Pos(), g_player.Gety_Pos())) i++;
		if (g_npc02.LoseNPC(g_player.Getx_Pos(), g_player.Gety_Pos())) i++;
		if (g_npc03.LoseNPC(g_player.Getx_Pos(), g_player.Gety_Pos())) i++;

		

		SDL_RenderPresent(g_screen);

		
		if (g_cham.WinCham() || i > 1) {
			g_music = Mix_LoadMUS("music/thua.mp3");
			Mix_PlayMusic(g_music, -1);
			SDL_Delay(4000);
			quit = true;
		}
		
	}


	Mix_FreeMusic(g_music);
	g_music = NULL;
	quit = false;
	while (!quit) {
		while (SDL_PollEvent(&g_event) != 0) {
			if (g_event.type == SDL_QUIT) {
				quit = true;
			}
			

		}
		SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
		SDL_RenderClear(g_screen);

		g_background.Render(g_screen, NULL);


		SDL_RenderPresent(g_screen);
	}




	
	

	close();
	

	return 0;
}