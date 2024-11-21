#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define HEIGHT 20
#define WIDTH 40

void gotoxy(int x, int y) {
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

void limites() {
    for (int i = 0; i < WIDTH; i++) {
        gotoxy(i, 0); printf("%c", 205);
        gotoxy(i, HEIGHT); printf("%c", 205);
    }
    for (int i = 0; i <= HEIGHT; i++) {
        gotoxy(0, i); printf("%c", 186);
        gotoxy(WIDTH, i); printf("%c", 186);
    }
    gotoxy(0, 0); printf("%c", 201);
    gotoxy(WIDTH, 0); printf("%c", 187);
    gotoxy(0, HEIGHT); printf("%c", 200);
    gotoxy(WIDTH, HEIGHT); printf("%c", 188);
}

void player(int x, int y) {
    gotoxy(x, y - 1); printf("%c", 219);
    gotoxy(x, y); printf("%c", 219);
    gotoxy(x, y + 1); printf("%c", 219);
}

void borrar(int x, int y) {
    gotoxy(x, y - 1); printf(" ");
    gotoxy(x, y); printf(" ");
    gotoxy(x, y + 1); printf(" ");
}

void dibujar_pelota(int x, int y) {
    gotoxy(x, y); printf("O");
}

void borrar_pelota(int x, int y) {
    gotoxy(x, y); printf(" ");
}

int main() {
    int x1 = 2, y1 = 10;
    int x2 = WIDTH - 2, y2 = 10;
    int px = WIDTH / 2, py = HEIGHT / 2;
    int dx = 1, dy = 1;
    int puntos1 = 0, puntos2 = 0;
    bool game = true;
    
    limites();
    player(x1, y1);
    player(x2, y2);
    dibujar_pelota(px, py);
    
    while (game) {
        if (kbhit()) {
            char tecla = getch();
            if (tecla == 'w' && y1 > 1) {
                borrar(x1, y1);
                y1--;
            }
            if (tecla == 's' && y1 < HEIGHT - 1) {
                borrar(x1, y1);
                y1++;
            }
            if (tecla == 'o' && y2 > 1) {
                borrar(x2, y2);
                y2--;
            }
            if (tecla == 'l' && y2 < HEIGHT - 1) {
                borrar(x2, y2);
                y2++;
            }
            if (tecla == 'q') game = false;
        }

        borrar_pelota(px, py);
        px += dx;
        py += dy;

        if (py == 1 || py == HEIGHT - 1) dy = -dy;
        if (px == x1 + 1 && (py == y1 || py == y1 - 1 || py == y1 + 1)) {
            dx = -dx;
        }
        if (px == x2 - 1 && (py == y2 || py == y2 - 1 || py == y2 + 1)) {
            dx = -dx;
        }

        if (px == 0) {
            puntos2++;
            px = WIDTH / 2;
            py = HEIGHT / 2;
            dx = 1;
            dy = 1;
        }
        if (px == WIDTH) {
            puntos1++;
            px = WIDTH / 2;
            py = HEIGHT / 2;
            dx = -1;
            dy = -1;
        }

        dibujar_pelota(px, py);
        player(x1, y1);
        player(x2, y2);
        
        gotoxy(WIDTH + 2, 2);
        printf("Jugador 1: %d", puntos1);
        gotoxy(WIDTH + 2, 4);
        printf("Jugador 2: %d", puntos2);
        
        Sleep(50);
    }
    
    gotoxy(WIDTH / 2 - 5, HEIGHT + 2);
    if (puntos1 > puntos2) {
        printf("Jugador 1 GANA con %d puntos", puntos1);
    } else if (puntos2 > puntos1) {
        printf("Jugador 2 GANA con %d puntos", puntos2);
    } else {
        printf("¡Es un EMPATE!");
    }

    gotoxy(0, HEIGHT + 4);
    return 0;
}

