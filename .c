#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define UP_KEY 'w'
#define LEFT_KEY 'a'
#define DOWN_KEY 's'
#define RIGHT_KEY 'd'
#define INTERACT_KEY 'i'
#define TELEPORT '>'
#define MONSTER '¬'

#define SCREEN_WIDTH_FASE1 15
#define SCREEN_HEIGHT_FASE1 15

#define SCREEN_WIDTH_FASE2 32
#define SCREEN_HEIGHT_FASE2 32

int spikes_touched = 0;
int player_x = SCREEN_WIDTH_FASE1/ 2;
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

char mapfase2[SCREEN_HEIGHT_FASE2][SCREEN_WIDTH_FASE2] = {
    "************************************************************",
    "*                            *                             *",
    "*                            *                             *",
    "***************************  *   ***************************",
    "*                            *                             *",
    "*                            *                             *",
    "*  *****************************************************   *",
    "*                            *                             *",
    "*                            *                             *",
    "***************************  *   ***************************",
    "*                            *                             *",
    "*                            *                             *",
    "*  ******************************************************  *",
    "*                            *                             *",
    "*                            *                             *",
    "***************************  *  ****************************",
    "*                            *                             *",
    "*                            *                             *",
    "*  ******************************************************  *",
    "*                            *                             *",
    "*                            *                             *",
    "***************************  *  ****************************",
    "*                            *                             *",
    "*                            *                             *",
    "*  ******************************************************  *",
    "*                            *                             *",
    "*                            *                             *",
    "*                            *                             *",
    "*                            *                             *",
    "*		 		  *	   		        *",
    "****************************D*D*****************************",
    "*                            *                             *",
    "************************************************************",
};

typedef struct {
    int x, y;
    int doorID;
    int isLocked;
} Door;

Door doors[] = {
    {0, 13, 1, 1},  //Localização da porta na fase 1
    {29, 27, 30, 30}, //Localização da porta na fase 2
    {31, 27, 30, 30}, //Localização da porta na fase 2
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

int game_running = 2;
HANDLE console;

void move_up() {
	int i;
    if (player_y > 0 && mapfase1[player_y - 1][player_x] != '*') {
        int next_x = player_x;
        int next_y = player_y - 1;

        //Verifica a localização da porta fechada
        for (i = 0; i < numDoors; i++) {
            if (next_x == doors[i].x && next_y == doors[i].y && doors[i].isLocked) {
                return;
            }
        }
        player_y--;
        
        // Verifica se o jogador chegou na posição da porta de transição
        if (current_fase == 1 && player_x == doors[0].x && player_y == doors[0].y) {
    		current_fase = 2;
		} else if (current_fase == 2 && player_x == doors[1].x && player_y == doors[1].y) {
    		// Lógica para passar para a próxima fase ou concluir o jogo
    		game_running = 0;
    		current_fase = 2;
		}
    } 
}

void move_left() {
	int i;
    if (player_x > 0 && mapfase1[player_y][player_x - 1] != '*') {
        int next_x = player_x - 1;
        int next_y = player_y;

        // Verifica se a localização contém a porta fechada
        for (i = 0; i < numDoors; i++) {
            if (next_x == doors[i].x && next_y == doors[i].y && doors[i].isLocked) {
            	printf("|----------------------------------------------------------------------------|\n");
            	printf("|Essa porta esta trancada. Encontre a chave correspondente para destranca-la.|\n");
            	printf("|----------------------------------------------------------------------------|\n");
				Sleep(500);
                return;
            }
		}
        player_x--;
        
        // Verifica se o jogador chegou na posição da porta de transição da fase1
        if (current_fase == 1 && player_x == doors[0].x && player_y == doors[0].y) {
        	game_running = 0;
            current_fase = 2;

        }
    } 
}

void move_down() {
    if (player_y < SCREEN_HEIGHT_FASE1 - 1 && mapfase1[player_y + 1][player_x] != '*') {
        player_y++;
    }
    
    // Verifica se o jogador chegou na posição da porta de transição
        if (current_fase == 1 && player_x == doors[0].x && player_y == doors[0].y) {
        	game_running = 0;
            current_fase = 2;
        }
}

void move_right() {
    if (player_x < SCREEN_WIDTH_FASE1 - 1 && mapfase1[player_y][player_x + 1] != '*') {
        player_x++;
    }
    // Verifica se o jogador chegou na posição da porta de transição
        if (current_fase == 1 && player_x == doors[0].x && player_y == doors[0].y) {
        	game_running = 0;
            current_fase = 2;
        }
}

void removeDoor(int doorID) {
    int i, j;
    for (i = 0; i < numDoors; i++) {
        if (doors[i].doorID == doorID) {
            for (j = i; j < numDoors - 1; j++) {
                doors[j] = doors[j + 1];
            }
            numDoors--;
            break;
        }
    }
}

void interact() {
    int i, j;

    // Verifica se o jogador está em uma localização que contém uma chave
    for (i = 0; i < numKeys; i++) {
        if (player_x == keyPositions[i].x && player_y == keyPositions[i].y) {
            printf("Voce pegou a chave %d!\n", keyPositions[i].keyID);
            Sleep(500);

            // Remove a chave do array de posições de chaves
            for (j = i; j < numKeys - 1; j++) {
                keyPositions[j] = keyPositions[j + 1];
            }
            numKeys--;

            // Verifica se a chave corresponde à porta que está trancada
            for (j = 0; j < numDoors; j++) {
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
    for (i = 0; i < numDoors; i++) {
        if (player_x == doors[i].x && player_y == doors[i].y && doors[i].isLocked) {
            return;
        }
    }

    // Verifica se o personagem está em uma posição que contém uma porta aberta
    for (i = 0; i < numDoors; i++) {
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
                game_running = 1;
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
        if (current_fase == 1 && player_x == doors[0].x && player_y == doors[0].y) {
    		current_fase = 2;
    reset_game();
}
else if (current_fase == 2 && player_x == doors[1].x && player_y == doors[1].y) {
    // Lógica para passar para a próxima fase ou concluir o jogo
}
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
    int i;
    for (i = 0; i < player_health; i++) {
        printf("&");
    }
    printf("\n");
}



void show_menu() {
#define START_KEY '1'
#define TUTORIAL_KEY '2'
#define QUIT_KEY '3'
    
	system("cls");
 	printf("             \n");
 	printf("                 --------------------------------------------\n");
    printf("                 | MM     MM   EEEEEE   NN    N  UU      UU |\n");
	printf("                 | M M   M M   EE       N N   N  UU      UU |\n");
	printf("                 | M  M M  M   EEEEE    N  N  N  UU      UU |\n");
	printf("                 | M   M   M   EE       N   N N  UU      UU |\n");
	printf("                 | M       M   EEEEEE   N    NN    UUUUUU   |\n");
	printf("                 --------------------------------------------\n");
	printf("             \n");
	printf("            _ \n");
    printf("           |1| Iniciar jogo\n");
 	printf("            - \n");
	printf("            _ \n");
    printf("           |2| Tutorial\n");
 	printf("            - \n");
	printf("            _ \n");
	printf("           |3|  Sair\n");
 	printf("            - \n");
}


void show_tutorial() {
	system("cls");
    printf("                            === TUTORIAL ===\n");
 	printf("             \n");
	printf("  O jogo e uma aventura/quebra-cabeca onde o objetivo e passar por tres niveis.\n");
	printf("  Em cada nivel, voce deve se mover para recolher uma chave para abrir uma \n porta fechada.\n");
	printf("             \n");
    printf("                 Voce pode usar os seguintes comandos:\n");
    printf("  _\n");
	printf(" |W | = Mover uma unidade para cima.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |A | = Move uma unidade para a esquerda.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |S | = Mover uma unidade para baixo.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |D | = Move uma unidade para a direita.\n");
	printf(" ---\n");
	printf("  _\n");
   	printf(" |I | = Interagir com um objeto.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |& | = Simbolo que representa o jogador.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |* | = Simbolo que representa uma parede, o jogador ao se movimentar não pode passar pela parede.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |@ | = Simbolo que representa a chave para abrir a porta para finalizar a fase, a porta abre no momento que o jogador interage com a chave.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |D | =  Simbolo que representa a porta fechada.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |= | =  Simbolo que representa a porta aberta quando o jogador interage com a chave.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |O | = Simbolo que representa um botao que o usuario pode interagir, o botao fica no chao e o jogador deve ficar em cima dele para poder interagir.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |# | =  Simbolo que representa um espinho. A fase e reiniciada quando o jogador toca no espinho, caso a fase seja reiniciada tres vezes, o jogo volta para o menu principal.\n");
    printf(" ---\n");
	printf("  _\n");
	printf(" |> | = Simbolo que representa um teletransporte. O teletransporte sempre deve vir em pares, quando o jogador toca em um ele e transportado para o outro e vice-versa.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |¬ | =  Simbolo que representa o monstro nivel 1. O mostro tem um movimento aleatório, logo, ele movimenta um bloco para cima ou para direita ou para esquerda ou para baixo. O mostro sempre faz uma movimentação depois do usuario se movimentar ou interagir com um objeto.\n");
	printf(" ---\n");
	printf("  _\n");
	printf(" |K | =  Simbolo que representa o monstro nivel 2. O monstro nivel dois tem uma inteligência de se movimentar na direção do jogador. O monstro não precisa saber desviar de obstaculos, ele sempre vai andar em linha reta em direçao do jogador.\n");
	printf(" ---\n");
	printf("                    Pressione qualquer tecla para continuar...\n");
    getch();
}

void game_loop() {
    while (game_running) {
        if (player_health <= 0) {
            reset_game();
        }
        int x, y, k;
        for (y = 0; y < SCREEN_HEIGHT_FASE1; y++) {
            for (x = 0; x < SCREEN_WIDTH_FASE1; x++) {
                if (x == player_x && y == player_y) {
                    printf("&");
                } else {
                    int containsKey = 0;
                    for (k = 0; k < numKeys; k++) {
                        if (x == keyPositions[k].x && y == keyPositions[k].y) {
                            containsKey = 1;
                            break;
                        } 
                    }
                    if (containsKey) {
                        printf("@");
                    } else {
                        printf("%c", mapfase1[y][x]);
                    }
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
    // Verificar se o jogador está na posição da porta final da fase 1
	   if (player_x == doors[0].x && player_y == doors[0].y) {
            game_running = 1;  // Fase 1 concluída, encerrar o jogo da fase 1
            current_fase = 2;  // Avançar para a fase 2
        }
   while (game_running = 2) {
   	   if (player_health <= 0) {
            reset_game();
        }
        int x, y, k;
        for (y = 0; y < SCREEN_HEIGHT_FASE2; y++) {
            for (x = 0; x < SCREEN_WIDTH_FASE2; x++) {
                if (x == player_x && y == player_y) {
                    printf("&");
                } else {
                    int containsKey = 0;
                    for (k = 0; k < numKeys; k++) {
                        if (x == keyPositions[k].x && y == keyPositions[k].y) {
                            containsKey = 1;
                            break;
                        } 
                    }
                    if (containsKey) {
                        printf("@");
                    } else {
                        printf("%c", mapfase2[y][x]);
                    }
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

    while (game_running) {
        show_menu();
        char choice = getch();
          
        switch (choice) {
            case START_KEY:
                game_loop();
                break;
            case TUTORIAL_KEY:
                show_tutorial();
                break;
            case QUIT_KEY:
                game_running = 0;
                break;
            
            default:
                printf("Escolha invalida. Por favor, tente novamente.\n");
                Sleep(500);
                break;
        }

        system("cls");
	}
	return 0;
}
