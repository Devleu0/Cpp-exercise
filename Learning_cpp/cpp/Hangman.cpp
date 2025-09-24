/*
💀 행맨 게임 (Hangman) 📋
컴퓨터가 비밀 단어를 하나 정하면, 플레이어는 알파벳을 하나씩 추측하여 단어를 맞춥니다. 플레이어는 정해진 횟수만큼만 틀릴 수 있습니다.

📝 게임 설계
단어 목록 준비:

게임에 사용할 단어 목록을 만듭니다. vector<string>을 사용하면 편리합니다.

게임이 시작될 때 이 목록에서 무작위로 단어 하나를 선택합니다.

게임 초기화:

플레이어에게 남은 목숨(기회)을 설정합니다 (예: 6번).

추측한 단어의 상태를 표시할 문자열을 만듭니다 (예: "apple"이면 "_ _ _ _ _").

플레이어가 이미 시도한 알파벳들을 기록할 공간을 마련합니다.

게임 루프:

게임이 끝날 때까지 (단어를 맞추거나, 목숨을 모두 잃을 때까지) 다음을 반복합니다.

현재까지 맞춘 단어의 상태, 남은 목숨, 그리고 이미 시도한 알파벳 목록을 화면에 출력합니다.

플레이어에게 알파벳 한 글자를 입력받습니다.

입력 처리:

정답인 경우: 입력한 알파벳이 비밀 단어에 포함되어 있다면, 해당 위치의 _를 알파벳으로 바꿉니다.

오답인 경우: 입력한 알파벳이 단어에 없다면, 목숨을 하나 줄입니다.

이미 시도한 알파벳을 다시 입력한 경우, 알려주고 턴을 넘기지 않습니다.

게임 종료 판정:

승리: 단어의 모든 _가 채워지면 "승리" 메시지를 출력하고 게임을 종료합니다.

패배: 남은 목숨이 0이 되면 "패배" 메시지와 함께 정답 단어를 알려주고 게임을 종료합니다.
*/
#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <algorithm> // find 함수를 사용하기 위해 필요

// 게임 상태를 화면에 출력하는 함수
void drawGame(int lives, const std::string& progress, const std::vector<char>& guessedLetters) {
    std::cout << "\n=================================\n";
    std::cout << "           HANGMAN GAME\n";
    std::cout << "=================================\n";
    std::cout << "남은 목숨: " << lives << " ❤️\n\n";

    // 행맨 그림 (간단하게 표현)
    std::vector<std::string> hangman_art = {
        " +---+\n |   |\n     |\n     |\n     |\n     |\n=======", // 6
        " +---+\n |   |\n O   |\n     |\n     |\n     |\n=======", // 5
        " +---+\n |   |\n O   |\n |   |\n     |\n     |\n=======", // 4
        " +---+\n |   |\n O   |\n/|   |\n     |\n     |\n=======", // 3
        " +---+\n |   |\n O   |\n/|\\  |\n     |\n     |\n=======", // 2
        " +---+\n |   |\n O   |\n/|\\  |\n/    |\n     |\n=======", // 1
        " +---+\n |   |\n O   |\n/|\\  |\n/ \\  |\n     |\n======="  // 0
    };
    std::cout << hangman_art[lives] << "\n\n";

    // 단어 진행 상황 출력
    std::cout << "단어: ";
    for (char c : progress) {
        std::cout << c << " ";
    }
    std::cout << "\n\n";

    // 추측한 알파벳 목록 출력
    std::cout << "시도한 알파벳: ";
    for (char c : guessedLetters) {
        std::cout << c << " ";
    }
    std::cout << "\n---------------------------------\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    // 단어 목록
    std::vector<std::string> words = { "apple", "banana", "orange", "grape", "strawberry", "computer", "programming" };

    // 무작위로 단어 선택
    std::string secretWord = words[rand() % words.size()];
    std::string wordProgress(secretWord.length(), '_');

    int lives = 6;
    std::vector<char> guessedLetters;
    char guess;

    // 게임 루프
    while (lives > 0 && wordProgress != secretWord) {
        drawGame(lives, wordProgress, guessedLetters);

        std::cout << "알파벳을 추측하세요: ";
        std::cin >> guess;

        // 소문자로 변환
        guess = tolower(guess);

        // 이미 추측한 알파벳인지 확인
        if (std::find(guessedLetters.begin(), guessedLetters.end(), guess) != guessedLetters.end()) {
            std::cout << "\n>> 이미 시도한 알파벳입니다! 다른 알파벳을 선택하세요.\n";
            continue;
        }

        guessedLetters.push_back(guess);

        // 단어에 추측한 알파벳이 있는지 확인
        size_t foundPos = secretWord.find(guess);
        if (foundPos != std::string::npos) {
            std::cout << "\n>> 맞았습니다!\n";
            for (size_t i = 0; i < secretWord.length(); ++i) {
                if (secretWord[i] == guess) {
                    wordProgress[i] = guess;
                }
            }
        }
        else {
            std::cout << "\n>> 틀렸습니다...\n";
            lives--;
        }
    }

    // 게임 종료 후 결과 출력
    drawGame(lives, wordProgress, guessedLetters);

    if (wordProgress == secretWord) {
        std::cout << "\n=================================\n";
        std::cout << "🎉 축하합니다! 단어를 맞췄습니다! 🎉\n";
        std::cout << "정답은 \"" << secretWord << "\" 였습니다.\n";
        std::cout << "=================================\n";
    }
    else {
        std::cout << "\n=================================\n";
        std::cout << "GAME OVER... 💀\n";
        std::cout << "정답은 \"" << secretWord << "\" 였습니다.\n";
        std::cout << "=================================\n";
    }

    return 0;
}
