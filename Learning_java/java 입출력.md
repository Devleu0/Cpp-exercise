java 입출력

## Java 입출력

콘솔 입출력이란 프로그램과 사용자가 서로 소통하는 가장 기본적인 방법이에요. 쉽게 말해, 프로그램을 통해 사용자에게 메시지를 보여주고, 반대로 사용자로부터 정보를 입력받는 과정이라고 할 수 있죠.

### 1. 콘솔에 출력하기

자바에서 콘솔에 메시지를 출력하는 방법은 주로 `System.out.println()`과 `System.out.print()` 두 가지를 사용해요.

*   `System.out.println("문자열")`: 문자열을 출력하고 다음 줄로 넘어가요. 'print' 뒤에 'ln'은 'line'을 의미합니다.
*   `System.out.print("문자열")`: 문자열만 출력하고 다음 줄로 넘어가지 않아요.

예를 들어, 아래 코드와 같이 두 개의 문장을 출력하면 결과는 조금 달라져요.

```java
public class ConsoleOutputExample {
    public static void main(String[] args) {
        System.out.println("안녕하세요!");
        System.out.println("반갑습니다.");
        System.out.print("첫 번째 줄입니다.");
        System.out.print("두 번째 줄입니다.");
    }
}
```

위 코드를 실행하면 다음과 같은 결과가 나타납니다.
```출력
안녕하세요!
반갑습니다.
첫 번째 줄입니다.두 번째 줄입니다.
```
println은 줄을 바꾸기 때문에 "안녕하세요!"와 "반갑습니다."가 각각 다른 줄에 출력되지만, print는 줄을 바꾸지 않아서 "첫 번째 줄입니다."와 "두 번째 줄입니다."가 한 줄에 이어서 출력되는 것을 볼 수 있어요.

### 2. 콘솔에서 입력받기
자바에서 사용자의 입력을 받으려면 Scanner라는 클래스를 사용해야 합니다. Scanner 클래스는 java.util 패키지에 포함되어 있어서, 사용하기 전에 먼저 import 문으로 불러와야 해요.

사용 방법:

Scanner 클래스를 import 합니다: import java.util.Scanner;

Scanner 객체를 만듭니다: Scanner scanner = new Scanner(System.in);

next()나 nextLine(), nextInt() 같은 메서드를 사용해 원하는 타입의 값을 입력받습니다.

next(): 공백 이전의 한 단어를 입력받습니다.

nextLine(): 한 줄 전체를 입력받습니다.

nextInt(): 정수를 입력받습니다.

아래 예제 코드를 통해 사용법을 더 자세히 알아볼까요?
Console Input Example
9월 19일 오후 3:10
```java
import java.util.Scanner;

public class ConsoleInputExample {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("이름을 입력하세요: ");
        String name = scanner.nextLine();

        System.out.print("나이를 입력하세요: ");
        int age = scanner.nextInt();

        System.out.println("당신의 이름은: " + name);
        System.out.println("당신의 나이는: " + age);

        scanner.close();
    }
}
```


위 코드를 실행하면 프로그램이 "이름을 입력하세요: "라는 메시지를 출력하고, 사용자가 이름을 입력할 때까지 기다려요. 이름과 나이를 입력하면 그 값을 변수에 저장하고, 다시 콘솔에 출력해 줍니다.

scanner.close()는 사용이 끝난 Scanner 객체의 자원을 해제하는 역할을 하므로, 항상 마지막에 호출하는 것이 좋습니다.

콘솔 입출력은 모든 프로그래밍의 기본이 되는 중요한 개념이에요. 