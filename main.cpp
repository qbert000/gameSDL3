#include "background.h"
#include "function.h"
#include "tile_map.h"
#include "character.h"
#include "npc.h"
#include "Cham.h"
#include "SmartMap.h"

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
	bool res = g_background.LoadImg("img/anime.png", g_screen);
	if (res == false) return false;
	else return true;
}

void close() {
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
	game_map.LoadMap("map/bando2.txt");
	game_map.LoadPixel(g_screen);
	Map g_map = game_map.GetMap();



	SmartMap g_smart(g_map);


	Cham g_cham;
	g_cham.LoadImg("img/cham.png", g_screen);


	Character g_player;
	g_player.LoadImg("img/pacnu.png", g_screen);
	
	
	NPC g_npc(700, 600);
	g_npc.LoadImg("img/maxanh.png", g_screen);

	NPC g_npc01(150, 550);
	g_npc01.LoadImg("img/mahong.png", g_screen);

	NPC g_npc02(100, 0);
	g_npc02.LoadImg("img/mado.png", g_screen);

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


		g_npc.Move(g_map, g_smart);
		g_npc.SetMapXYNPC(g_map.now_x_, g_map.now_y_);
		

		//if (g_npc01.Motion(g_player.Getx_Pos(), g_player.Gety_Pos())) {		
		//			g_npc01.NpcVirtualMove(g_player.Getx_Pos(), g_player.Gety_Pos(), g_map);
					//cout << " ngu" << endl;
					//g_npc01.b();
		//}
		//if (g_npc01.LuaTheo(g_player.Getx_Pos(), g_player.Gety_Pos(), g_map ) ) {
		//	cout << true;
		//}


		g_npc01.Move(g_map, g_smart);
		g_npc01.SetMapXYNPC(g_map.now_x_, g_map.now_y_);
		

		g_npc02.Move(g_map, g_smart);
		g_npc02.SetMapXYNPC(g_map.now_x_, g_map.now_y_);
		


		
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

		if (g_npc.LoseNPC(g_player.Getx_Pos(), g_player.Gety_Pos() ) ) quit = true;
		if (g_npc01.LoseNPC(g_player.Getx_Pos(), g_player.Gety_Pos())) quit = true;
		if (g_npc02.LoseNPC(g_player.Getx_Pos(), g_player.Gety_Pos())) quit = true;


		SDL_RenderPresent(g_screen);

		//SDL_Delay(50);
		if (g_cham.WinCham()) {
			SDL_Delay(1000);
			quit = true;
		}
		//if (g_player.WinGame(g_map)) {
		//	quit = true;
		//};
	}

	//close();
	//if (Init() == false) return -1;
	//if (LoadBackGround() == false) return -1;







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