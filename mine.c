
#include <stdio.h>
#include <conio.h>  // для Windows, getch() и kbhit()
#include <windows.h> // для управления курсором и цветом консоли

void setCursorPosition(int x, int y) {
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMenu(int selected);
void printTicTacToe(char board[3][3]);
int checkWin(char board[3][3]);
int isDraw(char board[3][3]);
void ticTacToeGame();

void printMenu(int selected) {
    const char *menu[] = {"Начать", "Лидеры", "Об игре", "Выход"};
    system("cls");
    printf("Меню (используйте стрелки ↑↓ и цифры 1-4, Enter для выбора)\n\n");
    for (int i = 0; i < 4; i++) {
        if (i == selected) {
            printf(" > %d. %s\n", i+1, menu[i]);
        } else {
            printf("   %d. %s\n", i+1, menu[i]);
        }
    }
}

void printTicTacToe(char board[3][3]) {
    system("cls");
    printf("Игра: Крестики-нолики\n\n");
    printf("  1   2   3\n");
    for (int i = 0; i < 3; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j] == '\0' ? ' ' : board[i][j]);
            if (j < 2) printf("|");
        }
        printf("\n");
        if (i < 2) printf("  ---+---+---\n");
    }
    printf("\n");
}

int checkWin(char board[3][3]) {
    // Проверка строк и столбцов
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != '\0' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
        if (board[0][i] != '\0' && board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    // Проверка диагоналей
    if (board[0][0] != '\0' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] != '\0' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];

    return 0; // Нет победителя
}

int isDraw(char board[3][3]) {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] == '\0') return 0;
    return 1;
}

void ticTacToeGame() {
    char board[3][3] = { {'\0','\0','\0'}, {'\0','\0','\0'}, {'\0','\0','\0'} };
    int row, col;
    char player = 'X';
    int win = 0;

    while (1) {
        printTicTacToe(board);
        printf("Ход игрока %c\n", player);
        printf("Введите номер строки (1-3): ");
        char cRow = _getch();
        printf("%c\n", cRow);
        printf("Введите номер столбца (1-3): ");
        char cCol = _getch();
        printf("%c\n", cCol);

        row = cRow - '1';
        col = cCol - '1';

        if (row < 0 || row > 2 || col < 0 || col > 2) {
            printf("Некорректный ввод! Попробуйте еще раз...\n");
            Sleep(1000);
            continue;
        }
        if (board[row][col] != '\0') {
            printf("Ячейка занята! Попробуйте еще раз...\n");
            Sleep(1000);
            continue;
        }

        board[row][col] = player;

        win = checkWin(board);
        if (win) {
            printTicTacToe(board);
            printf("Победил игрок %c!\n", win);
            break;
        } else if (isDraw(board)) {
            printTicTacToe(board);
            printf("Ничья!\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    printf("Нажмите любую клавишу, чтобы вернуться в меню...");
    _getch();
}

int main() {
    int selected = 0;
    int key;

    printMenu(selected);

    while (1) {
        key = _getch();

        if (key == 0 || key == 224) {
            key = _getch();
            if (key == 72) {
                selected = (selected == 0) ? 3 : selected - 1;
            } else if (key == 80) {
                selected = (selected == 3) ? 0 : selected + 1;
            }
            printMenu(selected);
        } else if (key >= '1' && key <= '4') {
            selected = key - '1';
            printMenu(selected);
        } else if (key == 13) {
            if (selected == 0) {
                ticTacToeGame();
                printMenu(selected);
            } else {
                system("cls");
                const char *menu[] = {"Начать", "Лидеры", "Об игре", "Выход"};
                printf("Вы выбрали: %d. %s\n", selected + 1, menu[selected]);
                if (selected == 3) {  // "Выход"
                    break;
                }
                printf("Нажмите любую клавишу чтобы вернуться в меню...");
                _getch();
                printMenu(selected);
            }
        }
    }
    return 0;
}

