/*
###  콘솔 스네이크 게임 (Console Snake Game) ### 
플레이어는 뱀을 조종하여 화면에 나타나는 먹이를 먹어야 합니다. 
먹이를 먹을 때마다 뱀의 꼬리가 길어집니다. 
뱀이 벽이나 자기 자신의 몸에 부딪히면 게임이 종료됩니다.

### 게임 설계 ### 
###  게임 환경 설정 ### 

* 게임 화면의 가로, 세로 크기를 정의합니다.
* 뱀의 초기 위치와 먹이의 위치를 설정합니다.
* 플레이어의 점수와 게임 오버 상태를 관리할 변수를 만듭니다.

###  실시간 입력 처리 ### 

사용자가 키보드 방향키(또는 W, A, S, D)를 눌렀을 때, 뱀의 진행 방향을 즉시 변경해야 합니다.

이를 위해 논블로킹(non-blocking) 입력 방식이 필요합니다. 
즉, 키 입력이 없을 때도 게임은 계속 진행되어야 합니다. (Windows에서는 <conio.h>의 _kbhit() 함수를 사용합니다.)

###  게임 루프 ### 

* 화면 그리기 (Draw): 현재 게임 상태(벽, 뱀, 먹이, 점수)를 콘솔에 그립니다. 화면 깜빡임을 줄이기 위해 커서 위치를 (0,0)으로 옮겨 덮어쓰는 트릭을 사용합니다.
* 입력 처리 (Input): 키보드 입력이 있는지 확인하고 뱀의 방향을 업데이트합니다. 단, 현재 진행 방향의 정반대 방향으로는 움직일 수 없습니다 (예: 오른쪽으로 갈 때 왼쪽 키 입력 무시).

###  로직 업데이트 (Logic) ### 

* 현재 방향으로 뱀의 머리를 한 칸 이동시킵니다.

* 뱀이 벽에 부딪혔는지 확인합니다.
* 뱀이 자기 몸에 부딪혔는지 확인합니다.
* 뱀이 먹이를 먹었는지 확인합니다. 
    * 먹었다면 점수를 올리고, 꼬리를 길게 만들고, 새로운 위치에 먹이를 생성합니다. 
    * 먹지 않았다면 꼬리 마지막 칸을 지워 길이가 유지되도록 합니다.

* 지연 (Delay): 게임 속도를 조절하기 위해 루프마다 아주 짧은 시간 동안 프로그램을 멈춥니다 (Sleep() 함수 사용).
*/
#include <iostream>
#include <vector>
#include <conio.h>    // _kbhit(), _getch()  (Windows 전용)
#include <windows.h>  // Sleep(), SetConsoleCursorPosition() (Windows 전용)

// 게임 설정 상수
const int width = 40;
const int height = 20;

// 전역 변수
bool gameOver;
int x, y, fruitX, fruitY, score;
std::vector<int> tailX, tailY;
int nTail;

// 뱀의 이동 방향을 나타내는 열거형
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// 커서 위치를 이동시키는 함수 (화면 깜빡임 방지)
void setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

// 게임 초기화 함수
void Setup() {
    gameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
    score = 0;
    nTail = 0;
    tailX.clear();
    tailY.clear();
}

// 화면을 그리는 함수
void Draw() {
    setCursorPosition(0, 0); // 커서를 왼쪽 상단으로 이동
    // 위쪽 벽
    for (int i = 0; i < width + 2; i++) std::cout << "#";
    std::cout << std::endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0) std::cout << "#"; // 왼쪽 벽

            if (i == y && j == x) {
                std::cout << "O"; // 뱀 머리
            }
            else if (i == fruitY && j == fruitX) {
                std::cout << "F"; // 먹이
            }
            else {
                bool printTail = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "o"; // 뱀 꼬리
                        printTail = true;
                    }
                }
                if (!printTail) std::cout << " ";
            }

            if (j == width - 1) std::cout << "#"; // 오른쪽 벽
        }
        std::cout << std::endl;
    }

    // 아래쪽 벽
    for (int i = 0; i < width + 2; i++) std::cout << "#";
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}

// 사용자 입력을 처리하는 함수
void Input() {
    if (_kbhit()) { // 키보드 입력이 있는지 확인
        switch (_getch()) { // 어떤 키가 눌렸는지 확인
        case 'a':
            if (dir != RIGHT) dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT) dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN) dir = UP;
            break;
        case 's':
            if (dir != UP) dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}

// 게임 로직을 업데이트하는 함수
void Logic() {
    // 꼬리 위치 업데이트
    int prevX = tailX.empty() ? x : tailX[0];
    int prevY = tailY.empty() ? y : tailY[0];
    int prev2X, prev2Y;
    if (!tailX.empty()) {
        tailX[0] = x;
        tailY[0] = y;
    }
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // 머리 위치 업데이트
    switch (dir) {
    case LEFT:  x--; break;
    case RIGHT: x++; break;
    case UP:    y--; break;
    case DOWN:  y++; break;
    default:    break;
    }

    // 벽 충돌 확인
    if (x >= width || x < 0 || y >= height || y < 0) {
        gameOver = true;
    }
    // 몸 충돌 확인
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // 먹이를 먹었는지 확인
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % width;
        fruitY = rand() % height;
        nTail++;
        tailX.push_back(0); // 꼬리 벡터 크기 늘리기
        tailY.push_back(0);
    }
}

int main() {
    srand(time(0));
    Setup();
    while (!gameOver) {
        Draw();
        Input();
        Logic();
        Sleep(100); // 게임 속도 조절 (ms)
    }

    setCursorPosition(width / 2 - 5, height / 2);
    std::cout << "GAME OVER!" << std::endl;

    return 0;
}
