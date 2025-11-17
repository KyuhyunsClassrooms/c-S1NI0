#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 게임판 (0~8번 칸)
char board[9];

// 게임판 초기화
void initBoard() {
    int i;
    for (i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

// 게임판 출력
void printBoard() {
    printf("\n");
    printf(" %c | %c | %c \n", board[0], board[1], board[2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[3], board[4], board[5]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[6], board[7], board[8]);
    printf("\n");
    printf("위치: 1 2 3\n");
    printf("      4 5 6\n");
    printf("      7 8 9\n\n");
}

// 승자 확인
char checkWinner() {
    int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // 가로
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // 세로
        {0, 4, 8}, {2, 4, 6}              // 대각선
    };
    
    int i;
    for (i = 0; i < 8; i++) {
        int a = lines[i][0];
        int b = lines[i][1];
        int c = lines[i][2];
        
        if (board[a] != ' ' && board[a] == board[b] && board[a] == board[c]) {
            return board[a];
        }
    }
    
    // 무승부 체크
    for (i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            return ' '; // 게임 진행 중
        }
    }
    
    return 'D'; // 무승부
}

// 이길 수 있는 자리 찾기
int findWin(char player) {
    int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},  // 가로
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},  // 세로
        {0, 4, 8}, {2, 4, 6}              // 대각선
    };
    
    int i, j;
    for (i = 0; i < 8; i++) {
        int count = 0;
        int empty = -1;
        
        for (j = 0; j < 3; j++) {
            int pos = lines[i][j];
            if (board[pos] == player) {
                count++;
            } else if (board[pos] == ' ') {
                empty = pos;
            }
        }
        
        if (count == 2 && empty != -1) {
            return empty;
        }
    }
    
    return -1; // 못 찾음
}

// 빈 칸 랜덤으로 선택
int getRandomMove() {
    int empty[9];
    int count = 0;
    int i;
    
    for (i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            empty[count] = i;
            count++;
        }
    }
    
    if (count == 0) return -1;
    
    return empty[rand() % count];
}

// AI가 수를 선택
int getAIMove(int aiFirst) {
    int move;
    
    // 규칙 1: 이길 수 있으면 이긴다
    move = findWin('X');
    if (move != -1) return move;
    
    // 규칙 2: 상대의 승리를 막는다
    move = findWin('O');
    if (move != -1) return move;
    
    // 규칙 3: 선공일 때는 반드시 중앙을 잡는다
    if (aiFirst && board[4] == ' ') {
        return 4;
    }
    
    // 규칙 4: 빈 칸에 수를 둔다
    return getRandomMove();
}

int main() {
    int choice, pos;
    int aiFirst;
    char winner;
    int playerTurn;
    
    srand(time(NULL));
    
    printf("================================\n");
    printf("   틱택토 게임\n");
    printf("================================\n");
    printf("당신: O, AI: X\n\n");
    
    printf("누가 먼저 시작할까요?\n");
    printf("1. 플레이어 선공\n");
    printf("2. AI 선공\n");
    printf("선택: ");
    scanf("%d", &choice);
    
    aiFirst = (choice == 2);
    
    initBoard();
    printBoard();
    
    playerTurn = (choice == 1);
    
    // 게임 시작
    while (1) {
        if (playerTurn) {
            // 플레이어 차례
            printf("당신의 차례! 위치를 선택하세요 (1-9): ");
            scanf("%d", &pos);
            pos = pos - 1;
            
            if (pos < 0 || pos > 8 || board[pos] != ' ') {
                printf("잘못된 위치입니다!\n");
                continue;
            }
            
            board[pos] = 'O';
        } 
        else {
            // AI 차례
            printf("AI가 생각 중...\n");
            pos = getAIMove(aiFirst);
            board[pos] = 'X';
            printf("AI가 %d번 위치에 두었습니다.\n", pos + 1);
        }
        
        printBoard();
        
        // 승자 확인
        winner = checkWinner();
        if (winner != ' ') {
            if (winner == 'O') {
                printf("🎉 축하합니다! 당신이 이겼어요!\n");
            } 
            else if (winner == 'X') {
                printf("😢 AI가 이겼어요!\n");
            } 
            else {
                printf("무승부!\n");
            }
            break;
        }
        
        // 차례 바꾸기
        playerTurn = !playerTurn;
    }
    
    printf("\n프로그램을 다시 실행하면 새 게임!\n");
    
    return 0;
}