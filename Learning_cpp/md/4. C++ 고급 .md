# STL 및 파일 입출력

## 목차
### STL
1. [표준 템플릿 라이브러리 (STL)](#1-표준-템플릿-라이브러리-stl)
    * 1.1 [STL의 3대 구성 요소](#11-stl의-3대-구성-요소)
    * 1.2 [컨테이너](#12-컨테이너-예시)
        * 1.2.1 [Vector](#121-vector-예시)
        * 1.2.2 [Map](#122-map-예시)
    * 1.3 [반복자](#13-반복자-예시)
    * 1.4 [알고리즘](#14-알고리즘-예시)
    * 1.5 [STL 활용](#15-stl-활용-팁)

---
### 파일 입출력

1. [스트림(Stream) 개요](#stream)  
    * 1.1 [스트림의 내부 구조](#structure)  
    * 1.2. [버퍼(Buffer) 동작 원리](#buffer)  
    * 1.3. [스트림 플래그(flag) 설정 방법](#flags)  
2. [파일 입출력 개요](#overview)  
    * 2.1. [파일 입출력 클래스](#classes)  
    * 2.2. [심화 개념](#advanced)  

---




## 1. 표준 템플릿 라이브러리 (STL)  <a name="1-표준-템플릿-라이브러리-stl"></a>

* STL(Standard Template Library)은 C++의 핵심 라이브러리로, 일관성 있는 자료구조(Containers), 반복자(Iterators), 알고리즘(Algorithms)을 제공합니다. STL을 활용하면 복잡한 자료구조나 알고리즘을 직접 구현하지 않고도 효율적으로 개발할 수 있습니다.  

* STL의 장점은 재사용성, 일관성, 효율성입니다. 컨테이너는 데이터를 구조적으로 저장하고, 반복자는 해당 데이터를 탐색하는 방법을 표준화하며, 알고리즘은 데이터 처리 방법을 추상화합니다.

---

### 1.1 STL의 3대 구성 요소<a name="11-stl의-3대-구성-요소"></a>

#### 1.1.1 컨테이너 (Containers)  
컨테이너는 데이터를 저장하고 관리하는 자료구조입니다.  
STL에는 순차 컨테이너(Sequence Containers)와 연관 컨테이너(Associative Containers)가 있습니다.

- 순차 컨테이너: `vector`, `list`, `deque` — 데이터가 순서대로 저장됩니다.  
- 연관 컨테이너: `set`, `map` — 키-값 쌍 또는 고유 값을 기반으로 데이터를 저장합니다.

---

#### 1.1.2 반복자 (Iterators)  
반복자는 컨테이너 내부 요소를 순회하는 객체입니다.  
포인터처럼 동작하지만 컨테이너의 내부 구조를 은폐합니다.  
주요 반복자:
- `.begin()` : 첫 번째 요소를 가리킵니다.
- `.end()` : 마지막 요소 다음을 가리킵니다.
- `.rbegin()` : 역방향 순회를 시작합니다.
- `.rend()` : 역방향 순회의 끝을 나타냅니다.

---

#### 1.1.3 알고리즘 (Algorithms)  
* STL 알고리즘은 데이터 처리를 위한 표준화된 함수 집합입니다.  
* 대표적인 알고리즘: `sort`, `find`, `reverse`, `accumulate`, `max_element` 등.  
* 반복자를 인자로 받아 컨테이너의 데이터를 처리합니다.

---

### 1.2 컨테이너 예시<a name="12-컨테이너-예시"></a>

#### 1.2.1 Vector 예시  <a name="121-vector-예시"></a>

* `vector`는 동적 배열로, 크기를 자동으로 확장합니다.  
* 임의 접근이 가능하고 요소 삽입/삭제가 뒤쪽에서 빠릅니다.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {30, 10, 50, 20, 40};

    // sort 알고리즘으로 정렬
    std::sort(numbers.begin(), numbers.end());

    std::cout << "정렬된 숫자: ";
    for (int num : numbers) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}
````

---

#### 1.2.2 Map 예시<a name="122-map-예시"></a>

* `map`은 키-값 쌍으로 데이터를 저장합니다.
* 키는 고유해야 하며, 자동으로 정렬됩니다.

```cpp
#include <iostream>
#include <map>

int main() {
    std::map<std::string, int> scores;
    scores["홍길동"] = 95;
    scores["김철수"] = 87;

    for (const auto& pair : scores) {
        std::cout << pair.first << "의 점수: " << pair.second << std::endl;
    }
}
```

---

### 1.3 반복자 예시<a name="13-반복자-예시"></a>

* 반복자를 사용하면 컨테이너 구조에 관계없이 동일한 방식으로 요소를 순회할 수 있습니다.

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5};

    std::cout << "반복자를 이용한 출력: ";
    for (auto it = data.begin(); it != data.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}
```

---

### 1.4 알고리즘 예시<a name="14-알고리즘-예시"></a>

* 알고리즘은 반복자 범위를 인자로 받아 동작합니다. 이로 인해 컨테이너 독립적인 코드 작성이 가능합니다.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> numbers = {5, 2, 9, 1, 5, 6};

    // 최대값 찾기
    auto max_it = std::max_element(numbers.begin(), numbers.end());
    std::cout << "최대값: " << *max_it << std::endl;

    // 역순 정렬
    std::reverse(numbers.begin(), numbers.end());
    std::cout << "역순: ";
    for (int n : numbers) {
        std::cout << n << " ";
    }
    std::cout << std::endl;
}
```

---

### 1.5 STL 활용<a name="15-stl-활용-팁"></a>

* 가능한 STL 컨테이너와 알고리즘을 활용하면 직접 구현하는 시간과 오류를 줄일 수 있습니다.
* 알고리즘을 사용할 때는 반복자의 범위를 정확히 지정해야 합니다.
* 컨테이너 선택 시 삽입, 삭제, 접근 속도를 고려해야 합니다.

# C++ 스트림(Stream) 및 파일 입출력 심층 학습 자료

C++ 스트림의 개념부터 내부 구조, 버퍼 동작 원리, 플래그 설정 방법까지 심층적으로 설명합니다. 파일 입출력과 결합하여 C++ 입출력 처리의 전체 구조를 이해하는 데 도움을 줍니다.

## 1. 스트림(Stream) 개요 <a name="stream"></a>

C++에서 스트림은 데이터의 흐름을 추상화한 개념입니다.  
스트림은 데이터를 읽고 쓰는 방향을 표현하며, 입력 스트림(Input Stream)과 출력 스트림(Output Stream)이 있습니다.

### 스트림의 특징

- 스트림은 연속적인 데이터 흐름을 나타냅니다.
- 스트림을 사용하면 파일, 콘솔, 메모리 등 다양한 데이터 소스를 동일한 방식으로 처리할 수 있습니다.
- C++ 표준 라이브러리에서 스트림은 클래스 형태로 제공됩니다.

### 주요 스트림 종류

| 스트림 클래스       | 설명 |
|----------------------|------|
| `istream`           | 입력 스트림(키보드, 파일 등) |
| `ostream`           | 출력 스트림(콘솔, 파일 등) |
| `ifstream`          | 파일 입력 스트림 |
| `ofstream`          | 파일 출력 스트림 |
| `fstream`           | 파일 입출력 스트림 |
| `istringstream`     | 문자열 입력 스트림 |
| `ostringstream`     | 문자열 출력 스트림 |
| `stringstream`      | 문자열 입출력 스트림 |

### 표준 입출력 스트림

| 스트림 변수    | 설명 |
|-----------------|------|
| `cin`           | 표준 입력 스트림 (키보드 입력) |
| `cout`          | 표준 출력 스트림 (콘솔 출력) |
| `cerr`          | 표준 오류 출력 스트림 (버퍼 없음) |
| `clog`          | 표준 로그 출력 스트림 (버퍼 있음) |

예:

```cpp
#include <iostream>
using namespace std;

int main() {
    int num;
    cout << "숫자를 입력하세요: ";
    cin >> num;
    cout << "입력한 숫자는 " << num << "입니다." << endl;
}
````

---

## 1.1 스트림의 내부 구조 <a name="structure"></a>

C++ 스트림은 추상화된 입출력 장치로서, 내부적으로는 다음과 같이 구성됩니다.

```
[스트림 객체] → [버퍼(Buffer)] → [장치(Device)]
```

* 스트림 객체(stream object): `cin`, `cout`, `ifstream`, `ofstream` 등의 객체
* 버퍼(buffer): 데이터를 일시적으로 저장하는 메모리 공간
* 장치(device): 실제 데이터 입출력 대상(콘솔, 파일, 메모리 등)

 C++ 표준 스트림 클래스 계층 구조:

```
ios_base
  ├── istream
  │     └── ifstream
  ├── ostream
  │     └── ofstream
  └── iostream
        └── fstream
```

---

## 1.2 버퍼(Buffer) 동작 원리 <a name="buffer"></a>

버퍼는 데이터의 효율적인 입출력을 위해 사용됩니다.
스트림은 직접 장치와 통신하지 않고 버퍼를 통해 데이터를 처리합니다.

### 입력 스트림 버퍼 동작

1. 입력 요청 시 버퍼가 비어있으면 장치로부터 일정량의 데이터를 읽어옴.
2. 버퍼에서 데이터 제공.
3. 버퍼가 비워지면 다시 장치에서 데이터 로드.

### 출력 스트림 버퍼 동작

1. 출력 요청 시 버퍼에 데이터 저장.
2. 버퍼가 꽉 차거나 flush 조건 발생 시 장치로 전송.

 버퍼를 사용하면 입출력 속도가 향상되지만, 즉시 출력이 필요한 경우 `flush()`를 호출하거나 `endl`을 사용해야 합니다.

```cpp
#include <iostream>
using namespace std;

int main() {
    cout << "Hello" << flush; // 즉시 출력
    cout << " World" << endl; // 출력 + 버퍼 flush
}
```

---

## 1.3 스트림 플래그(flag) 설정 방법 <a name="flags"></a>

스트림 플래그는 입출력 방식과 버퍼 동작을 제어합니다.
`ios` 클래스의 플래그를 사용합니다.

### 주요 플래그

| 플래그              | 설명                    |
| ---------------- | --------------------- |
| `ios::app`       | 덧붙이기 모드 (append mode) |
| `ios::ate`       | 파일 끝에서 시작             |
| `ios::binary`    | 바이너리 모드               |
| `ios::in`        | 입력 모드                 |
| `ios::out`       | 출력 모드                 |
| `ios::trunc`     | 기존 파일 내용을 삭제          |
| `ios::nocreate`  | 파일이 없으면 생성하지 않음       |
| `ios::noreplace` | 기존 파일이 있으면 열지 않음      |

### 플래그 설정 방법

```cpp
#include <fstream>
using namespace std;

int main() {
    ofstream outFile("data.txt", ios::app | ios::out);
    outFile << "새로운 데이터 추가" << endl;
    outFile.close();
}
```

---

## 2. 파일 입출력 개요 <a name="overview"></a>

파일 입출력은 프로그램과 외부 파일 간의 데이터 교환입니다.
C++에서는 `<fstream>` 헤더를 포함하여 처리합니다.

* 입력(Input): 파일로부터 데이터를 읽어오는 작업
* 출력(Output): 파일에 데이터를 쓰는 작업

---

## 2.1 파일 입출력 클래스 <a name="classes"></a>

`<fstream>` 헤더에는 다음 세 가지 주요 클래스가 있습니다.

| 클래스        | 설명                 |
| ---------- | ------------------ |
| `ifstream` | 파일로부터 읽기 위한 클래스    |
| `ofstream` | 파일에 쓰기 위한 클래스      |
| `fstream`  | 읽기와 쓰기 모두 지원하는 클래스 |

## 파일 입출력 예제
### 숫자 데이터를 파일에 쓰고 읽기

```cpp
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ofstream outFile("numbers.txt");
    for (int i = 1; i <= 5; i++) {
        outFile << i << " ";
    }
    outFile.close();

    ifstream inFile("numbers.txt");
    int num;
    while (inFile >> num) {
        cout << num << " ";
    }
    inFile.close();
}
```

---

## 2.2 심화 개념 <a name="advanced"></a>

### 2.2.1 바이너리 파일 입출력

텍스트 대신 바이너리 형태로 파일을 읽고 쓰면 데이터 처리 속도가 빠릅니다.

```cpp
#include <iostream>
#include <fstream>
using namespace std;

struct Data {
    int id;
    double value;
};

int main() {
    Data d1 = {1, 3.14};

    ofstream outFile("data.bin", ios::binary);
    outFile.write(reinterpret_cast<char*>(&d1), sizeof(Data));
    outFile.close();

    Data d2;
    ifstream inFile("data.bin", ios::binary);
    inFile.read(reinterpret_cast<char*>(&d2), sizeof(Data));
    inFile.close();

    cout << d2.id << ", " << d2.value << endl;
}
```

---

### 2.2.2 파일 위치 제어

파일의 읽기/쓰기 위치를 조정할 수 있습니다.

* `seekg(pos)` — 읽기 위치 이동
* `seekp(pos)` — 쓰기 위치 이동
* `tellg()` — 현재 읽기 위치 반환
* `tellp()` — 현재 쓰기 위치 반환

```cpp
ifstream inFile("example.txt");
inFile.seekg(0, ios::beg); // 처음 위치로 이동
```

---

### 2.2.3 예외 처리

파일 입출력에서 오류 처리를 위해 예외를 사용할 수 있습니다.

```cpp
#include <iostream>
#include <fstream>
#include <exception>
using namespace std;

int main() {
    ifstream inFile;
    inFile.exceptions(ifstream::failbit | ifstream::badbit);

    try {
        inFile.open("not_exist.txt");
    } catch (const ios_base::failure& e) {
        cerr << "파일 열기 실패: " << e.what() << endl;
    }
}
```

---

## 정리

* 파일 입출력은 C++에서 `<fstream>` 클래스를 사용
* `ifstream`, `ofstream`, `fstream`이 기본 클래스
* `ios::app`, `ios::binary` 등 모드 옵션 활용 가능
* 바이너리 입출력, 파일 위치 제어, 예외 처리 등 고급 기능 학습 필요
