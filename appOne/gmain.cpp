#include"libOne.h"
#include<rand.h>
#include<time.h>
struct GAME {
    const int TITLE = 0;
    const int SELECT = 1;
    const int PLAY = 2;
    const int CLEAR = 3;
    const int OVER = 4;
    int game_state = TITLE;
};
struct BLOCK {
    float block_Size = 0;
    char bomb_Flag = 0;
    //0=未選択、NOT地雷.
    //1=未選択、地雷.
    //2=選択後、NOT地雷.
    //3=地雷予想.
    char memory_mine = 0;
    bool player_flag = 0;
    bool bomb_prediction = 0;
};
struct NUMBER {
    char input_Row = 15;
    int Square_input_Row = 0;
    char input_level = 7;
};
struct SELECT_PLAYER {
    const int SELECT_ROW = 0;
    const int SELECT_LEVEL = 1;
    const int GO_PLAY = 2;
    int select_state = SELECT_ROW;
    char select_number= 0;
    char select_level = 0;
};
struct PLAYER {
    bool start_position = 0;
    int position = 0;
    char Player_Size = 20;
};
void TITLE(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer) {
    clear(0);
    fill(255);
    textSize(215);
    text("マインスイーパー", 100, 400);
    textSize(150);
    text("Start to Press SPACE", 210, 700);
    if (isTrigger(KEY_SPACE)) {
        g_pointer->game_state= g_pointer->SELECT;
    }
}
void set_block_Size(struct BLOCK* b_pointer, struct NUMBER* n_pointer) {
    b_pointer->block_Size = Height / n_pointer->input_Row;
}
void set_mine(struct BLOCK* b_pointer, struct NUMBER* n_pointer) {
    int judgment_mine = 0;
    srand((unsigned int)time(0));
    n_pointer->Square_input_Row = n_pointer->input_Row * n_pointer->input_Row;
    for (int x = 0; x < n_pointer->Square_input_Row; x++) {
        judgment_mine = rand() % n_pointer->input_level;
        if (judgment_mine == 0) {
            b_pointer[x].bomb_Flag = 1;
        }
    }
}
void Text(struct GAME* g_pointer, struct NUMBER* n_pointer) {
    textSize(100);
    fill(255);
    if (g_pointer->game_state == g_pointer->SELECT) {
        text("W ↑", width -600, 150);
        text("S ↓", width -600, 250);
        text("A:D   ←:→", width -600, 400);
        text("  難易度", width -600, 600);
        text("←低：高→", width - 600, 700);
    }
    textSize(100);
    fill(255);
    if (g_pointer->game_state == g_pointer->PLAY) {
        text(n_pointer->input_Row, height+100, 100);
        text("×", height + 200, 100);
        text(n_pointer->input_Row, height + 300, 100);
        text("level;", height + 100, 200);
        text(n_pointer->input_level,height + 500, 200);
        text("  W   :  ↑", height+100, 400);
        text("A S D :←↓→", height+100, 500);
        text("Press E : DASH", height+100, 700);
        text("Press Q :", height + 100, 800);
        text(": PREDICTION", height + 100, 900);
    }
    textSize(100);
    fill(255);
    if (g_pointer->game_state == g_pointer->OVER) {
        text("GAME_OVER" ,height + 200, 300);
        text("Press_SPACE", height + 150, 700);
        text("Restart", height + 150, 900);
    }
    textSize(100);
    fill(255);
    if (g_pointer->game_state == g_pointer->CLEAR) {
        text("GAME_CLEAR", height + 200, 300);
        text("Press_SPACE", height + 150, 700);
        text("Restart", height + 150, 900);
    }

}
void SELECT(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct SELECT_PLAYER* s_pointer) {
    clear(0);
    Text(g_pointer, n_pointer);
    textSize(100);
    if (isTrigger(KEY_W)) { s_pointer->select_state -= 1; }
    if (isTrigger(KEY_S)) { s_pointer->select_state += 1; }
    s_pointer->select_state %= 3;
    if (s_pointer->select_state == -1) {
        s_pointer->select_state = 2;
    }
    if (s_pointer->select_state == s_pointer->SELECT_ROW) {
        text("→Select Row", 200, 200);
        if (isTrigger(KEY_A)) { n_pointer->input_Row--; }
        if (isTrigger(KEY_D)) { n_pointer->input_Row++; }
        if (n_pointer->input_Row > 30) {
            n_pointer->input_Row %= 27;
        }
        if (n_pointer->input_Row < 4) {
            n_pointer->input_Row += 27;
        }
        s_pointer->select_level = n_pointer->input_Row;
        text(n_pointer->input_Row, 950, 200);
        fill(255);
        text("Select Level", 200, 500);
        text(n_pointer->input_level, 950, 500);
        fill(255);
        rect((width / 2) - 300, height - 400, 600, 200);
        fill(0);
        text("Press_SPACE", (width / 2) - 275, height - 300);
        text("Play", (width / 2) - 100, height - 200);
    }
    else if (s_pointer->select_state == s_pointer->SELECT_LEVEL) {
        fill(255);
        text("Select Row", 200, 200);
        text(n_pointer->input_Row, 950, 200);
        text("→Select Level", 200, 500);
        if (isTrigger(KEY_A)) { n_pointer->input_level++; }
        if (isTrigger(KEY_D)) { n_pointer->input_level--; }
        if (n_pointer->input_level > n_pointer->input_Row/2+1) {
            n_pointer->input_level -= 1;
        }
        if (n_pointer->input_level < 2) {
            n_pointer->input_level++;
        }
        if (n_pointer->input_level == 1) {
            n_pointer->input_level++;
        }
        text(n_pointer->input_level, 950, 500);
        fill(255);
        rect((width / 2) - 300, height - 400, 600, 200);
        fill(0);
        text("Press_SPACE", (width / 2) - 275, height - 300);
        text("Play", (width / 2) - 100, height - 200);
        s_pointer->select_level = n_pointer->input_level;
    }
    else if (s_pointer->select_state == s_pointer->GO_PLAY) {
        fill(255);
        text("Select Row", 200, 200);
        text(n_pointer->input_Row, 950, 200);
        fill(255);
        text("Select Level", 200, 500);
        text(n_pointer->input_level, 950, 500);
        fill(150);
        rect((width / 2) - 300, height - 400, 600, 200);
        fill(0);
        text("Press_SPACE", (width / 2) - 275, height - 300);
        text("Play", (width / 2) - 100, height - 200);
    }
    if (s_pointer->select_state == s_pointer->GO_PLAY && isTrigger(KEY_SPACE)) {
        set_block_Size(b_pointer, n_pointer);
        set_mine(b_pointer, n_pointer);
        g_pointer->game_state = g_pointer->PLAY;
    }
}
void stage_draw(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
    int i = 0;
    for (int y = 0; y < n_pointer->input_Row; y++) {
        for (int x = 0; x < n_pointer->input_Row; x++) {
            fill(0, 255, 0);
            rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
            if (b_pointer[i].bomb_Flag == 0) {
                fill(0, 255, 0);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
            }
            else if (b_pointer[i].bomb_Flag == 2) {
                fill(123, 123, 123);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                fill(255, 255, 255);
                textSize(b_pointer->block_Size);
                text(b_pointer[i].memory_mine, (b_pointer->block_Size * x)+(b_pointer->block_Size/4), b_pointer->block_Size * (y + 1));
            }
            if (b_pointer[i].player_flag == 1) {
                fill(0, 0, 0);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size / 3, b_pointer->block_Size / 3);
            }
            if (b_pointer[i].bomb_prediction ==1) {
                fill(255, 0, 0);
                rect((b_pointer->block_Size * x)+ (b_pointer->block_Size /3), (b_pointer->block_Size * y)+ (b_pointer->block_Size / 3), b_pointer->block_Size/3, b_pointer->block_Size / 3);
            }
            /*debug
            else if (b_pointer[i].bomb_Flag == 1) {
                fill(255, 0, 0);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
            }
            else if (b_pointer[i].bomb_Flag == 3) {
                fill(255, 0, 0);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
            }
            */
            i++;
        }
    }
}
void clear_decision(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
    int sum = 0;
    for (int i = 0; i < n_pointer->Square_input_Row; i++) {
        if (b_pointer[i].bomb_Flag == 0) {
            sum++;
        }
    }
    if (sum==0) {
            g_pointer->game_state = g_pointer->CLEAR;
    }
}
void  serect_block(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
    if (p_pointer->start_position == 0) {
        b_pointer[p_pointer->position].player_flag = 1;
        p_pointer->start_position = 1;
    }
    if (isTrigger(KEY_W)) { 
        b_pointer[p_pointer->position].player_flag = 0;
        p_pointer->position -= n_pointer->input_Row;
        if (p_pointer->position < 0) {
            p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
        }
        b_pointer[p_pointer->position].player_flag = 1;
    }
    if (isTrigger(KEY_A)) {
        b_pointer[p_pointer->position].player_flag = 0;
        p_pointer->position -= 1;
        if (p_pointer->position < 0) {
            p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
        }
        b_pointer[p_pointer->position].player_flag = 1;
    }
    if (isTrigger(KEY_S)) {
        b_pointer[p_pointer->position].player_flag = 0;
        p_pointer->position += n_pointer->input_Row;
        if (p_pointer->position >= n_pointer->Square_input_Row) {
            p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
        }
        b_pointer[p_pointer->position].player_flag = 1;
    }
    if (isTrigger(KEY_D)) { 
        b_pointer[p_pointer->position].player_flag = 0;
        p_pointer->position += 1;
        if (p_pointer->position >= n_pointer->Square_input_Row) {
            p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
        }
        b_pointer[p_pointer->position].player_flag = 1;
    }
    if (isPress(KEY_E)) {
        if (isPress(KEY_W)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position -= n_pointer->input_Row;
            if (p_pointer->position < 0) {
                p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }
        if (isPress(KEY_A)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position -= 1;
            if (p_pointer->position < 0) {
                p_pointer->position = n_pointer->Square_input_Row + p_pointer->position;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }
        if (isPress(KEY_S)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position += n_pointer->input_Row;
            if (p_pointer->position >= n_pointer->Square_input_Row) {
                p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }
        if (isPress(KEY_D)) {
            b_pointer[p_pointer->position].player_flag = 0;
            p_pointer->position += 1;
            if (p_pointer->position >= n_pointer->Square_input_Row) {
                p_pointer->position = p_pointer->position % n_pointer->Square_input_Row;
            }
            b_pointer[p_pointer->position].player_flag = 1;
        }

    }
}
void  Search_mine(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
    b_pointer[p_pointer->position].memory_mine = 0;
    if (p_pointer->position == 0) {
        if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
    }
    else if (p_pointer->position == n_pointer->input_Row-1) {
        if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
    }

    else if (p_pointer->position < n_pointer->input_Row) {
        if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
    }
    else if ((p_pointer->position % n_pointer->input_Row) == 0) {
        if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position - n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position - n_pointer->input_Row) + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
    }
    else if (((p_pointer->position+1) % n_pointer->input_Row) == 0) {
        if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position - n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position - n_pointer->input_Row) - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
    }
    else {
        if (b_pointer[p_pointer->position + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position + n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[p_pointer->position - n_pointer->input_Row].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position + n_pointer->input_Row) - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position - n_pointer->input_Row) + 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
        if (b_pointer[(p_pointer->position - n_pointer->input_Row) - 1].bomb_Flag == 1) {
            b_pointer[p_pointer->position].memory_mine++;
        }
    }
}
void  Push_Block(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
    if(isTrigger(KEY_SPACE)){
        if (b_pointer[p_pointer->position].bomb_Flag == 0) {
            b_pointer[p_pointer->position].bomb_Flag = 2;
            Search_mine(b_pointer, n_pointer, p_pointer);
        }
        if (b_pointer[p_pointer->position].bomb_Flag == 1) {
            g_pointer->game_state = g_pointer->OVER;
        }
    }
    if (isTrigger(KEY_Q)) {
        if (b_pointer[p_pointer->position].bomb_prediction ==0) {
            b_pointer[p_pointer->position].bomb_prediction = 1;
        }
        else{
            b_pointer[p_pointer->position].bomb_prediction = 0;
        }
    }
}
void PLAY(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer,struct PLAYER* p_pointer) {
        serect_block(b_pointer, n_pointer, p_pointer);
        Push_Block(g_pointer, b_pointer, n_pointer, p_pointer);
        clear_decision(g_pointer, b_pointer, n_pointer, p_pointer);
        clear(0);
        stage_draw(b_pointer,n_pointer,p_pointer);
        Text(g_pointer, n_pointer);
}
void Game_finish_stage_draw(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer) {
    int i = 0;
    for (int y = 0; y < n_pointer->input_Row; y++) {
        for (int x = 0; x < n_pointer->input_Row; x++) {
            if (b_pointer[i].bomb_Flag == 0) {
                fill(0, 255, 0);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
            }
            else if (b_pointer[i].bomb_Flag == 1) {
                fill(255, 0, 0);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
            }
            else if (b_pointer[i].bomb_Flag == 2) {
                fill(123, 123, 123);
                rect(b_pointer->block_Size * x, b_pointer->block_Size * y, b_pointer->block_Size, b_pointer->block_Size);
                fill(255, 255, 255);
                textSize(b_pointer->block_Size);
                text(b_pointer[i].memory_mine, (b_pointer->block_Size * x) + (b_pointer->block_Size / 4), b_pointer->block_Size * (y + 1));
            }
            i++;
        }
    }
}
void INIT_stage(struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
    for (int i = 0; i < n_pointer->Square_input_Row; i++) {
        b_pointer[i].bomb_Flag = 0;
    }
    for (int i = 0; i < n_pointer->Square_input_Row; i++) {
        b_pointer[i].bomb_prediction = 0;
    }
    b_pointer[p_pointer->position].player_flag = 0;
    p_pointer->start_position = 0;
    p_pointer->position = 0;
    s_pointer->select_state = s_pointer->SELECT_ROW;
}
void OVER(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
    clear(0);
    Text(g_pointer, n_pointer);
    Game_finish_stage_draw(b_pointer, n_pointer, p_pointer);
    if (isTrigger(KEY_SPACE)) {
        INIT_stage(b_pointer, n_pointer, p_pointer, s_pointer);
        g_pointer->game_state = g_pointer->SELECT;
    }
}
void CLEAR(struct GAME* g_pointer, struct BLOCK* b_pointer, struct NUMBER* n_pointer, struct PLAYER* p_pointer, struct SELECT_PLAYER* s_pointer) {
    clear(0);
    Text(g_pointer, n_pointer);
    Game_finish_stage_draw(b_pointer, n_pointer, p_pointer);
    if (isTrigger(KEY_SPACE)) {
        INIT_stage(b_pointer, n_pointer, p_pointer, s_pointer);
        g_pointer->game_state = g_pointer->SELECT;
    }
}
void gmain() {
    struct GAME game;
    struct BLOCK block[930];
    struct NUMBER number;
    struct PLAYER player;
    struct SELECT_PLAYER select;
    window(1920, 1080, full);
    while (notQuit) {

        if (game.game_state == game.TITLE) { TITLE(&game, block, &number); }
        else if (game.game_state == game.SELECT) { SELECT(&game, block, &number, &select); }
        else if (game.game_state == game.PLAY) { PLAY(&game, block, &number, &player); }
        else if (game.game_state == game.OVER) { OVER(&game, block, &number, &player,&select); }
        else if (game.game_state == game.CLEAR) { CLEAR(&game, block, &number, &player,&select); }
    }
}