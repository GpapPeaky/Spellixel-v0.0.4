#include "mesh.h"

void mesh_bullet_collision(std::vector<Bullet>& bullet_vector){

    /* Bullet Collisions*/

    for(auto& mesh : meshes){
        for(auto& bullet : bullet_vector){
            auto newEnd = std::remove_if(bullet_vector.begin(), bullet_vector.end(), [&](Bullet& bullet){
                bool collided = (bullet.bullet_pos.x < mesh.pos.x + mesh.pos.w &&
                                    bullet.bullet_pos.x + bullet.bullet_pos.w > mesh.pos.x &&
                                    bullet.bullet_pos.y < mesh.pos.y + mesh.pos.h &&
                                    bullet.bullet_pos.y + bullet.bullet_pos.h > mesh.pos.y);

                if(collided){
                    SDL_FreeSurface(bullet.bullet_png);
                    SDL_DestroyTexture(bullet.bullet_texture);
                }

                return collided;
            });

            bullet_vector.erase(newEnd, bullet_vector.end());
        }
    }
}

void mesh_player_collision(void){

    /* Player Colliisions */

    for(auto& mesh : meshes){
        if((pl.pos.x < mesh.pos.x + mesh.pos.w &&
        pl.pos.x + pl.pos.w > mesh.pos.x &&
        pl.pos.y < mesh.pos.y + mesh.pos.h &&
        pl.pos.y + pl.pos.h > mesh.pos.y)){
            pl.acc.velocity_x = -pl.acc.velocity_x;
            pl.acc.velocity_y = -pl.acc.velocity_y;

            float overlapX = 0.0f;
            float overlapY = 0.0f;

            if (pl.pos.x < mesh.pos.x) {
                overlapX = pl.pos.x + pl.pos.w - mesh.pos.x;
            } else {
                overlapX = mesh.pos.x + mesh.pos.w - pl.pos.x;
            }

            if (pl.pos.y < mesh.pos.y) {
                overlapY = pl.pos.y + pl.pos.h - mesh.pos.y;
            } else {
                overlapY = mesh.pos.y + mesh.pos.h - pl.pos.y;
            }

            if (overlapX < overlapY) {
                pl.pos.x += (pl.pos.x < mesh.pos.x) ? -overlapX : overlapX;
            } else {
                pl.pos.y += (pl.pos.y < mesh.pos.y) ? -overlapY : overlapY;
            }

        pl.acc.velocity_x = -pl.acc.velocity_x;
        pl.acc.velocity_y = -pl.acc.velocity_y;

        }
    }
}

void mesh_collisions(std::vector <Bullet> &bullet_array){
    mesh_bullet_collision(bullet_array);
    mesh_player_collision();
}
