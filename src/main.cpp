#include "_includes.i"
#include "_mod.i"

#ifdef cpc_mod

    Uint64 start, end, seconds;
    SDL_FRect cpc_pos;

#endif /* cpc_mod */

MAIN_T main(int c, char** v){

    load_sprite_init("Spellixel.pix"); /* Initialise a window, a renderer and some universal sprites */
    init_font();
    init_enemy_font();
    init_ui();
    init_podium();
    // load_and_play_wav_music("cubic_forest");

   /* TODO: IMPLEMENT FUNCTION POINTERS WHEREVER YOU CAN FOR ENEMY FUNCTIONS */
   /* TODO: IMPLEMENT FUNCTION POINTERS WHEREVER YOU CAN FOR ITEM FUNCTIONS */

    /*______________________________________________________________*/

    // chicken(400, 600);
    chicken(600, 500);
    goblin(200 ,600);
    hilbert(MID_X + 75, MID_Y);
    villager(600,500);
    sheep(1250, 330);
    sheep(1300, 330);
    sheep(1250, 400);

    /* TODO: TRY MAKING A MENU */

    /*______________________________________________________________*/

    /* TODO: RANDOMISE ITEM GENERATION */
    /* TODO: RANDOMISE ROOM GENERATION ( READ FROM THE MDF SEEDS ) */
    /* TODO: RANDOMISE ENEMY GENERATION */

    /*______________________________________________________________*/

    // init_podium(); /* Podium texture, ect */
    spawn_item(MID_X, MID_Y, "county_crown");
    // spawn_item(600, 600, "county_necklace");
    // spawn_item(400, 600, "county_gauntlets");
    // spawn_item(700, 600, "medal_of_bloodmoon");
    // spawn_item(500 + 150, 450, "goggles_of_greenflake");

    /*______________________________________________________________*/
    
    SDL_Event e;
    bool not_running = RUNNING;

    while(!not_running){

        #ifdef cpc_mod

            start = SDL_GetPerformanceCounter();
            cpc_pos.x = 0.0f;
            cpc_pos.y = 25.0f;

        #endif /* cpc_mod */

        /* Different maps at each next room */

        std::string map_path = "maps/map" + std::to_string(current_map_idx) +  ".mdf";
        std::string mesh_path = "maps/mesh" +  std::to_string(current_map_idx) +  ".mdf";

        std::vector<std::vector<int>> background = load_map(map_path);
        std::vector<std::vector<int>> mesh_map = load_map(mesh_path);

        auto current_time = std::chrono::high_resolution_clock::now();
        static auto prev_time = current_time;
        std::chrono::duration<float> elapsed = current_time - prev_time;
        prev_time = current_time;

        float dt = elapsed.count();

        while(SDL_PollEvent(&e) != 0){
            
            if(e.type == SDL_QUIT){
                not_running = NOT_RUNNING;
            }
            /* Handling Keyboard */
            handle_input(e);
            /* Handling Mouse */
            handle_shooting(e);
        }

        mesh_player_collision();
        mesh_bullet_collision(pl.sprite_bullets);
        item_player_collision();

        update_player(dt);
        update_mesh_positions();
        enemy_updates(dt);

        shoot(0.1f); /* Update? ...maybe? */

        SDL_RenderClear(renderer); /* Clears the rendition, before re-rednering the screen */
        
        /**
         * @notes:
         * 
         * -Updates: player -> meshes -> enemies.
         * 
         * -Renditions: background -> meshes -> player -> player bullets -> enemies -> enemy bullets.
        */

        render_background_tiles(background);
        render_mesh_tiles(mesh_map);
        MESHES_F(pl.sprite_bullets);
        render_item();
        render_enemies(); 
        render_player();
        render_player_bullets();
        render_enemy_bullets();
        render_item_on_player(); /* Works as intended */

        // render_on_player("Nick Geuhrs");
        render_on_mouse_hover();

        render_UI(); /* IDEA: REPAINT THE UI */

        #ifdef cpc_mod

            end = SDL_GetPerformanceCounter();

            seconds = (end - start);
            std::string cpc = "cpc: " + std::to_string(seconds);

            render_text(cpc, &cpc_pos);

        #endif /* cpc_mod */

        SDL_RenderPresent(renderer);
    }

    /* No input can be taken through the console until the window has been destroyed */

    SDL_Delay(100); /* Lower CPU overload */

    for(const auto& bullet : pl.sprite_bullets){
        SDL_DestroyTexture(bullet.bullet_texture);
    }

    for(const auto& mesh : meshes){
        SDL_DestroyTexture(mesh.sprite_texture);
    }

    for(const auto& enemy : enemies){
        SDL_DestroyTexture(enemy.sprite.sprite_texture);
    }

    Mix_CloseAudio();
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_FreeCursor(CURSOR);
    SDL_DestroyTexture(pltexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return EXIT_SUCCESS;
}

/* TODO: PACK ALL RENDITIONS AND UPDATES INTO ONE OR AT MOST TWO FUNCTIONS */
