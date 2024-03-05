#include "_includes.i"

/*IDEA:  MOVE THIS FUCNTION SOMEWHERE ELSE */

Update_t update_mesh_positions(void) {

    srand(time(NULL));

    static int prev_pl_x = pl.pos.x;
    static int prev_pl_y = pl.pos.y;

    int deltaX = pl.pos.x - prev_pl_x;
    int deltaY = pl.pos.y - prev_pl_y;

    if (pl.pos.x + pl.pos.w >= screen_x) {
        current_map_idx = 1 + (rand() % ROOMS);

        while(current_map_idx == 1){ /* IDX 1 IS THE STARTING POSITION */
            current_map_idx = 1 + (rand() % ROOMS);
        }

        std::printf("Currenty at map <%d>\n",current_map_idx);

        pl.pos.x = 0 - pl.pos.w; /* Resetting position as we move along to a new map */
    }

    prev_pl_x = pl.pos.x;
    prev_pl_y = pl.pos.y;
}

MAIN_T main(int c, char** v){

    load_sprite_init("Spellixel.pix"); /* Initialise a window, a renderer and some universal sprites */
    init_font();
    init_enemy_font();
    init_ui();
    // load_and_play_wav_music("cubic_forest");

   /* TODO: IMPLEMENT FUNCTION POINTERS WHEREVER YOU CAN FOR ENEMY FUNCTIONS */
   /* TODO: IMPLEMENT FUNCTION POINTERS WHEREVER YOU CAN FOR ITEM FUNCTIONS */

    /*______________________________________________________________*/

    // chicken(400, 600);
    // chicken(600, 500);
    goblin(200 ,600);
    // hilbert(MID_X + 75, MID_Y);
    // villager(600,500);
    // sheep(1250, 330);
    // sheep(1300, 330);
    // sheep(1250, 400);

    /*______________________________________________________________*/

    /* TODO: RANDOMISE ITEM GENERATION */
    /* TODO: RANDOMISE ROOM GENERATION ( READ FROM THE MDF SEEDS ) */
    /* TODO: RANDOMISE ENEMY GENERATION */

    /*______________________________________________________________*/

    // init_podium(); /* Podium texture, ect */
    // spawn_item(MID_X, MID_Y, "county_crown");
    // spawn_item(600, 600, "county_necklace");
    // spawn_item(400, 600, "county_gauntlets");
    // spawn_item(500, 600, "goggles_of_greenflake");
    // spawn_item(200, 600, "medal_of_bloodmoon");

    /*______________________________________________________________*/
    
    SDL_Event e;
    bool not_running = RUNNING;

    while(!not_running){

        /* Different maps at each next room */

        std::string map_path = "maps/map" + std::to_string(current_map_idx) +  ".mdf";
        std::string mesh_path = "maps/mesh" +  std::to_string(current_map_idx) +  ".mdf";

        std::vector<std::vector<int>> background = load_map(map_path);
        std::vector<std::vector<int>> mesh_map = load_map(mesh_path);

        auto currentTime = std::chrono::high_resolution_clock::now();
        static auto prevTime = currentTime;
        std::chrono::duration<float> elapsed = currentTime - prevTime;
        prevTime = currentTime;

        float deltaTime = elapsed.count();

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

        /*
        for( auto& enemy : enemies){
            mesh_bullet_collision(enemy.sprite.sprite_bullets);
        }

        CRASHES THE PROGRAM, MODIFYING THE ARRAY WHILE ITERATING IT -> UPRECEDENTED BEHAVIOUR
        */

        update_player(deltaTime);
        update_mesh_positions();
        enemy_updates(deltaTime);

        shoot(0.1f); /* Update? ...maybe? */

        SDL_RenderClear(renderer); /* Clears the rendition, before re-rednering the screen */
        
        /**
         * @notes:
         * 
         * -Updates: player -> meshes -> enemies.
         * 
         * -Renditions: background -> meshes -> player -> player bullets -> enemies -> enemy bullets.
        */

        render_background_tiles(background); /* Memory leaks */ // FIXED
        render_mesh_tiles(mesh_map); /* Memory leaks 5 MB per tick */ //FIXED
        MESHES_F(pl.sprite_bullets);
        render_item();
        render_player();
        render_player_bullets();
        render_enemies(); 
        render_enemy_bullets();
        render_item_on_player(); /* Works as intended */

        // render_on_player("Nick Geuhrs");
        render_on_mouse_hover();

        render_UI(); /* IDEA: REPAINT THE UI */

        SDL_RenderPresent(renderer);
    }

    /* No input can be taken through the console until the window has been destroyed */

    SDL_Delay(100); /* Lower CPU overload */

    for (const auto& bullet : pl.sprite_bullets){
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
