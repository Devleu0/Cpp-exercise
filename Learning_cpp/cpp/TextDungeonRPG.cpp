/*
🎮 텍스트 던전 RPG (Text Dungeon RPG)
플레이어는 용사가 되어 던전에 입장합니다. 각 층마다 몬스터가 등장하며, 플레이어는 공격, 회복, 도망 중 하나를 선택하여 몬스터와 싸워야 합니다.

📝 게임 설계
#게임 시작

플레이어의 캐릭터(용사)와 몬스터의 기본 능력치(체력, 공격력)를 설정합니다.

간단한 게임 배경 스토리를 출력합니다.

# 전투 루프

현재 플레이어와 몬스터의 상태(남은 체력)를 화면에 표시합니다.

플레이어에게 행동을 선택하라는 메뉴를 보여줍니다: 1. 공격, 2. 회복, 3. 도망.

# 플레이어 행동 처리

공격: 플레이어가 몬스터를 공격하고, 몬스터의 체력이 감소합니다.

회복: 플레이어가 물약을 사용해 자신의 체력을 일정량 회복합니다. 물약은 한정되어 있습니다.

도망: 전투를 포기하고 게임을 종료합니다.

# 몬스터 행동 처리

플레이어가 행동을 마치면, 몬스터가 플레이어를 공격하고 플레이어의 체력이 감소합니다.

공격력은 약간의 무작위성을 부여하여 매번 다른 피해를 주도록 합니다.

# 전투 결과 판정

플레이어 승리: 몬스터의 체력이 0 이하가 되면 플레이어가 승리합니다. 다음 층으로 이동하며, 더 강한 몬스터가 등장합니다.

플레이어 패배: 플레이어의 체력이 0 이하가 되면 게임 오버 메시지를 출력하고 게임이 종료됩니다.

도망: "용감하게 도망쳤습니다!" 메시지를 출력하고 게임이 종료됩니다.

게임 진행: 플레이어가 패배하거나 도망치지 않는 한, 2~5번 과정을 반복합니다.
*/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// 게임 캐릭터의 능력치를 구조체로 정의
struct Character {
    std::string name;
    int hp;
    int maxHp;
    int attackPower;
    int potions;
};

// 화면에 플레이어와 몬스터의 현재 상태를 출력하는 함수
void displayStatus(const Character& player, const Character& monster) {
    std::cout << "\n--------------------\n";
    std::cout << player.name << " | HP: " << player.hp << "/" << player.maxHp << " | 물약: " << player.potions << "개\n";
    std::cout << monster.name << " | HP: " << monster.hp << "/" << monster.maxHp << "\n";
    std::cout << "--------------------\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // 난수 시드 초기화

    // 플레이어 캐릭터 설정
    Character player = { "용사", 100, 100, 15, 3 }; // 이름, 현재체력, 최대체력, 공격력, 물약 개수

    int stage = 1; // 게임 스테이지

    std::cout << "=================================\n";
    std::cout << "      텍스트 던전 RPG ⚔️\n";
    std::cout << "=================================\n";
    std::cout << "깊은 던전으로 모험을 떠납니다...\n";

    // 게임 메인 루프 (플레이어가 살아있는 동안 계속됨)
    while (player.hp > 0) {
        // 스테이지별 몬스터 생성
        Character monster = { "고블린", 30 + (stage * 10), 30 + (stage * 10), 8 + (stage * 2), 0 };
        std::cout << "\n=================================\n";
        std::cout << "   [ Stage " << stage << " ]\n";
        std::cout << "야생의 " << monster.name << "이(가) 나타났다!\n";

        // 전투 루프 (몬스터가 살아있는 동안 계속됨)
        while (monster.hp > 0 && player.hp > 0) {
            displayStatus(player, monster);

            // 플레이어 행동 선택
            std::cout << "\n무엇을 할까?\n";
            std::cout << "1. 공격 🗡️\n";
            std::cout << "2. 물약 마시기 🧪 (" << player.potions << "개 남음)\n";
            std::cout << "3. 도망치기 🏃\n";
            std::cout << "선택: ";

            int choice;
            std::cin >> choice;

            // 선택에 따른 행동 처리
            if (choice == 1) {
                // 공격
                int damage = player.attackPower + (rand() % 6); // 0~5의 추가 피해
                monster.hp -= damage;
                std::cout << "\n>> " << player.name << "의 공격! " << monster.name << "에게 " << damage << "의 피해를 입혔다!\n";
            }
            else if (choice == 2) {
                // 회복
                if (player.potions > 0) {
                    player.potions--;
                    int healAmount = 30;
                    player.hp += healAmount;
                    if (player.hp > player.maxHp) {
                        player.hp = player.maxHp; // 최대 체력을 넘지 않도록
                    }
                    std::cout << "\n>> 물약을 사용했다! 체력을 " << healAmount << " 회복했다!\n";
                }
                else {
                    std::cout << "\n>> 물약이 없다!\n";
                    continue; // 몬스터에게 턴을 넘기지 않고 다시 선택
                }
            }
            else if (choice == 3) {
                // 도망
                std::cout << "\n>> 용감하게 도망쳤다...\n";
                return 0; // 게임 종료
            }
            else {
                std::cout << "\n>> 잘못된 선택이다! 기회를 날렸다...\n";
            }

            // 몬스터가 살아있다면 반격
            if (monster.hp > 0) {
                int monsterDamage = monster.attackPower + (rand() % 4); // 0~3의 추가 피해
                player.hp -= monsterDamage;
                std::cout << ">> " << monster.name << "의 반격! " << monsterDamage << "의 피해를 받았다!\n";
            }
        }

        // 전투 결과 판정
        if (player.hp <= 0) {
            std::cout << "\n=================================\n";
            std::cout << "GAME OVER... 💀\n";
            std::cout << player.name << "은(는) 쓰러졌다.\n";
            std::cout << "도달한 최고 스테이지: " << stage << "\n";
            std::cout << "=================================\n";
        }
        else {
            std::cout << "\n>> " << monster.name << "을(를) 물리쳤다!\n";
            stage++; // 다음 스테이지로
            player.attackPower += 2; // 스테이지 클리어 보상: 공격력 증가
            std::cout << ">> 용사의 공격력이 2 증가했다!\n";
        }
    }

    return 0;
}