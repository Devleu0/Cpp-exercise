#include <iostream>
#include <string>
#include <cstdio>
#include <format>

using std::cout;
using std::cin;

//int add()
/*
int add(int a, int b) {
    return a + b;
}
*/

int main()
{
    // I/O basics
    /*
    std::string name;
    std::cout << "이름을 입력하세요: ";
    std::cin >> name;
    std::cout << "Hello World!, " << name << "san" << std::endl;

    printf("Hello World!, %ssan \n", name.c_str());
    */

    //if else / switch case break default
    /*
    int score;
    
    cout << std::format("점수를 입력하세요>>");
    cin >> score;

    if (score > 90) {
        cout << "A\n";
    }
    else if (score > 80) {
        cout << "B\n";
    }
    else if (score > 70) {
        cout << "C\n";
    }
    else {
        cout << "Hey!\n";
    }
    
    switch (score / 10) {
    case 10:
    case 9:
        cout << "A";
        break;
    case 8:
        cout << "B";
        break;
    case 7:
        cout << "C";
        break;
    default:
        cout << "Hey!!";
    }
    */

    // for while 
    /*
    for (int i = 0; i < 10; i++) {
        cout << i << " ";
    }
    int j = 0;
    while (j <= 10) {
        cout << 10 - j << " ";
        j++;
    }
    output: 0 ~ 10 ~ 0
    */

    // func
    /*    
    int num1 = 0, num2 = 0;
    cout << "숫자(2~4개)를 입력하세요>>";
    cin >> num1 >> num2;
    cout << add(num1, num2);
    */

    // array
    /*
    int scores[5] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < 5; i++) {
        cout << std::format("scores[{}] = ", i) << scores[i] << std::endl;
    }
    */

    // N-dimensional array
    /*
    int matrix[3][3] = { {1,2,3},{4,5,6},{7,8,9} };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j];
        }
    */

    //pointer * reference &
    /*
    int num = 0;
    cout << num << std::endl;   //0

    int* num_pointer = &num;
    cout << *num_pointer << std::endl;  //0

    *num_pointer = 5;
    cout << num << std::endl;   //5

    int& num_ref = num;
    num_ref = 10;
    cout << num << std::endl;   //10
    */
    return 0;
}


