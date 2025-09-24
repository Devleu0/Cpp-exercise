/*
⚫️ Tic-Tac-Toe (콘솔 버전) ❌
3x3 게임 보드에 두 명의 플레이어(Player 'X'와 Player 'O')가 번갈아 가며 자신의 말을 놓습니다. 가로, 세로, 혹은 대각선으로 자신의 말을 세 개 연속으로 놓는 플레이어가 승리합니다.

📝 게임 설계
# 게임 보드 초기화

3x3 크기의 2차원 배열을 생성합니다.

보드의 각 칸을 '1'부터 '9'까지의 숫자로 초기화하여 플레이어가 위치를 쉽게 선택할 수 있도록 합니다.

# 게임 루프

게임이 끝날 때까지 (승자가 나오거나 비길 때까지) 다음을 반복합니다.

현재 게임 보드를 화면에 예쁘게 출력합니다.

현재 턴의 플레이어('X' 또는 'O')를 알려주고, 말을 놓을 위치(1-9)를 입력받습니다.

입력한 위치가 유효한지(이미 다른 말이 놓여있지 않은지, 1-9 범위 내인지) 확인합니다.

유효한 위치라면, 보드에 현재 플레이어의 말을 놓습니다.

# 승리 및 무승부 판정

말을 놓을 때마다 승리 조건이 달성되었는지 확인합니다.

가로 3줄 확인

세로 3줄 확인

대각선 2줄 확인

승자가 나오면, 승리 메시지를 출력하고 게임을 종료합니다.

9번의 턴이 모두 진행되었는데도 승자가 나오지 않으면, 무승부 메시지를 출력하고 게임을 종료합니다.

# 플레이어 턴 전환

한 플레이어가 말을 놓으면, 다음 턴은 상대방 플레이어에게 넘어갑니다.
*/
#include <iostream>
#include <vector>
#include <string>

// 게임 보드를 저장할 전역 변수 (char 2차원 배열)
char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

char currentPlayer = 'X'; // 시작 플레이어는 'X'

// 게임 보드를 화면에 출력하는 함수
void drawBoard() {
    // system("cls"); // Windows에서 화면을 지우고 싶을 때 사용
    // system("clear"); // Linux/macOS에서 화면을 지우고 싶을 때 사용
    std::cout << "=========================\n";
    std::cout << "      TIC-TAC-TOE\n";
    std::cout << "=========================\n";
    std::cout << "   Player 1 (X) - Player 2 (O)\n\n";

    for (int i = 0; i < 3; i++) {
        std::cout << "     |     |     \n";
        std::cout << "  " << board[i][0] << "  |  " << board[i][1] << "  |  " << board[i][2] << "  \n";
        std::cout << "_____|_____|_____\n";
    }
    std::cout << "     |     |     \n";
}

// 플레이어 턴을 바꾸는 함수
void switchPlayer() {
    if (currentPlayer == 'X') {
        currentPlayer = 'O';
    }
    else {
        currentPlayer = 'X';
    }
}

// 플레이어의 입력을 받아 보드에 표시하는 함수
void playerInput() {
    int choice;
    std::cout << "\nPlayer " << currentPlayer << ", 놓을 위치(1-9)를 선택하세요: ";
    std::cin >> choice;

    // 입력받은 숫자에 해당하는 배열 위치 계산
    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    // 유효성 검사: 해당 칸이 비어있는지 확인
    if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        std::cout << "\n>> 잘못된 위치입니다! 다른 곳을 선택하세요.\n";
        playerInput(); // 재귀 호출로 다시 입력받음
    }
    else {
        board[row][col] = currentPlayer;
    }
}

// 승리 조건을 확인하는 함수
char checkWin() {
    // 가로 확인
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return board[i][0];
    }
    // 세로 확인
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return board[0][i];
    }
    // 대각선 확인
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return board[0][2];

    return '/'; // 아무도 이기지 않은 상태
}

int main() {
    int turn = 0;
    drawBoard();

    // 게임 메인 루프 (최대 9턴까지 진행)
    while (turn < 9) {
        playerInput();
        drawBoard();
        turn++;

        // 승리자 확인
        char winner = checkWin();
        if (winner == 'X' || winner == 'O') {
            std::cout << "\n=========================\n";
            std::cout << "🎉 Player " << winner << "가 승리했습니다! 🎉\n";
            std::cout << "=========================\n";
            return 0; // 게임 종료
        }

        // 턴 전환
        switchPlayer();
    }

    // 9턴이 지났는데 승자가 없으면 무승부
    if (checkWin() == '/') {
        std::cout << "\n=========================\n";
        std::cout << "🤝 무승부입니다! 🤝\n";
        std::cout << "=========================\n";
    }

    return 0;
}