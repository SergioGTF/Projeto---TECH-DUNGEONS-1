#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define UP_KEY 'w'
#define LEFT_KEY 'a'
#define DOWN_KEY 's'
#define RIGHT_KEY 'd'
#define INTERACT_KEY 'i'

#define SCREEN_WIDTH_FASE1 15
#define SCREEN_HEIGHT_FASE1 15

int spikes_touched = 0;
int player_x = SCREEN_WIDTH_FASE1 / 2;
int player_y = SCREEN_HEIGHT_FASE1 / 2;
int player_health = 3;
int game_restart_count = 0;
int current_fase = 1;

char mapfase1[SCREEN_WIDTH_FASE1][SCREEN_HEIGHT_FASE1] = {
    "***************",
    "*             *",
    "*      ********",
    "*             *",
    "********      *",
    "*             *",
    "*      ********",
    "*             *",
    "********      *",
    "*             *",
    "*       *******",
    "*             *",
    "*********     *",
    "D             *",
    "***************",
};

typedef struct {
    int x, y;
    int doorID;
    int isLocked;
} Door;

Door doors[] = {
    {0, 13, 1, 1},  //Localização da porta na fase 1
};

int numDoors = sizeof(doors) / sizeof(doors[0]);

typedef struct {
    int x, y;
    int keyID;
} KeyPosition;

KeyPosition keyPositions[] = {
    {1, 9, 1},  //Localização da chave na fase 1
};

int numKeys = sizeof(keyPositions) / sizeof(keyPositions[0]);

int game_running = 1;
HANDLE console;

void move_up() {
    if (player_y > 0 && mapfase1[player_y - 1][player_x] != '*') {
        int next_x = player_x;
        int next_y = player_y - 1;

        // Verifica a localização da porta fechada
        for (int i = 0; i < numDoors; i++) {
            if (next_x == doors[i].x && next_y == doors[i].y && doors[i].isLocked) {
                return;
            }
        }
        player_y--;
    }
}

void move_left() {
    if (player_x > 0 && mapfase1[player_y][player_x - 1] != '*') {
        int next_x = player_x - 1;
        int next_y = player_y;

        // Verifica se a localização contém a porta fechada
        for (int i = 0; i < numDoors; i++) {
            if (next_x == doors[i].x && next_y == doors[i].y && doors[i].isLocked) {
                printf("|----------------------------------------------------------------------------|\n");
                printf("|Essa porta esta trancada. Encontre a chave correspondente para destranca-la.|\n");
                printf("|----------------------------------------------------------------------------|\n");
                Sleep(500);
                return;
            }
        }
        player_x--;
    }
}

void move_down() {
    if (player_y < SCREEN_HEIGHT_FASE1 - 1 && mapfase1[player_y + 1][player_x] != '*') {
        player_y++;
    }
}

void move_right() {
    if (player_x < SCREEN_WIDTH_FASE1 - 1 && mapfase1[player_y][player_x + 1] != '*') {
        player_x++;
    }
}

void interact() {
    // Verifica se o jogador está em uma localização que contém uma chave
    for (int i = 0; i < numKeys; i++) {
        if (player_x == keyPositions[i].x && player_y == keyPositions[i].y) {
            printf("Voce pegou a chave %d!\n", keyPositions[i].keyID);
            Sleep(500);

            // Verifica se a chave corresponde à porta que está trancada
            for (int j = 0; j < numDoors; j++) {
                if (keyPositions[i].keyID == doors[j].doorID) {
                    doors[j].isLocked = 0; // Destrancar a porta com a chave
                    printf("Você destrancou a porta com a chave %d!\n", keyPositions[i].keyID);
                    Sleep(500);

                    // Trocar o símbolo da porta fechada "D" pelo símbolo da porta aberta "="
                    mapfase1[doors[j].y][doors[j].x] = '=';
                    return;
                }
            }
            return;
        }
    }

    // Verifica se o personagem está em uma posição que contém uma porta trancada
    for (int i = 0; i < numDoors; i++) {
        if (player_x == doors[i].x && player_y == doors[i].y && doors[i].isLocked) {
            return;
        }
    }

    // Verifica se o personagem está em uma posição que contém uma porta aberta
    for (int i = 0; i < numDoors; i++) {
        if (player_x == doors[i].x && player_y == doors[i].y && !doors[i].isLocked) {
            return;
        }
    }
}

void reset_map(char map[SCREEN_HEIGHT_FASE1][SCREEN_WIDTH_FASE1]);
void check_spike_damage() {
    if (mapfase1[player_y][player_x] == '#') {
        player_health--;
        printf("Voce foi atingido por um espinho! Vidas restantes: %d\n", player_health);
        Sleep(500);

        if (player_health <= 0) {
            spikes_touched++;
            if (spikes_touched >= 2) {
                // Reiniciar o mapa
                reset_map(mapfase1);
                spikes_touched = 0;
            }
            else {
                // Encerrar o jogo
                printf("______________________________\n");
                printf("|          GAME OVER!        |\n");
                printf("|Voce reiniciou o mapa 1 vez!|\n");
                printf("------------------------------\n");
                Sleep(2000);
                game_running = 0;
            }
        }
    }
}

void reset_game() {
    reset_map(mapfase1);
    spikes_touched = 0;
    game_restart_count++;

    if (game_restart_count >= 3) {
        game_running = 0;
    }
}

void reset_map(char map[SCREEN_HEIGHT_FASE1][SCREEN_WIDTH_FASE1]) {    
    // Restaurar a posição inicial do jogador
    player_x = SCREEN_WIDTH_FASE1 / 2;
    player_y = SCREEN_HEIGHT_FASE1 / 2;
    
    // Restaurar a quantidade de vida do jogador
    player_health = 3;
}

void draw_health() {
    printf("Vida: ");
    for (int i = 0; i < player_health; i++) {
        printf("&");
    }
    printf("\n");
}

void game_loop() {
    while (game_running) {
        if (player_health <= 0) {
            reset_game();
        }
        for (int y = 0; y < SCREEN_HEIGHT_FASE1; y++) {
            for (int x = 0; x < SCREEN_WIDTH_FASE1; x++) {
                if (x == player_x && y == player_y) {
                    printf("&");
                } else {
                    printf("%c", mapfase1[y][x]);
                }
            }
            printf("\n");
        }
        
        draw_health();

        char input = getch();
        switch (input) {
            case UP_KEY:
                move_up();
                break;
            case LEFT_KEY:
                move_left();
                break;
            case DOWN_KEY:
                move_down();
                break;
            case RIGHT_KEY:
                move_right();
                break;
            case INTERACT_KEY:
                interact();
                break;
            default:
                break;
        }

        check_spike_damage();

        system("cls");
        SetConsoleCursorPosition(console, (COORD){0, 0});
    }
}

int main() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, 1); // Define a cor do texto
    console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor_info;
    GetConsoleCursorInfo(console, &cursor_info);
    cursor_info.bVisible = 0;
    SetConsoleCursorInfo(console, &cursor_info);
    system("mode con: cols=80 lines=24");
    system("cls");

    game_loop();

    return 0;
}
