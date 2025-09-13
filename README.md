# 🔍 Scanner

**Scanner** — это многопоточный файловый сканер на C++20, который ищет вредоносные файлы по их MD5-хэшу.  
Хэши известных вредоносных объектов берутся из CSV-базы. Результаты проверки сохраняются в лог-файл.

## 🚀 Возможности

- Рекурсивное сканирование директории.
- Подсчет **MD5-хэшей** файлов (через OpenSSL).
- Сравнение с базой вредоносных хэшей (CSV).
- Многопоточная обработка файлов (**ThreadPool**).
- Генерация отчета с результатами.
- Набор **юнит-тестов** на GoogleTest.

## 📦 Зависимости

- [CMake ≥ 3.11](https://cmake.org/)
- [C++20](https://en.cppreference.com/w/cpp/20)
- [Boost.Program_options](https://www.boost.org/doc/libs/release/doc/html/program_options.html)
- [OpenSSL](https://www.openssl.org/)
- [GoogleTest](https://github.com/google/googletest) (для тестов)

## ⚙️ Сборка

```bash
git clone https://github.com/yourname/scanner.git
cd scanner
mkdir build && cd build
cmake ..
cmake --build .
````

После сборки будут доступны:

* `main` — основная программа.
* `test_util` — тесты.

## ▶️ Использование

Программа принимает три аргумента:

```bash
./scanner --base <csv> --log <logfile> --path <directory>
```

### Пример

```bash
./scanner --base base.csv --log report.log --path ./files
```

Где:

* `base.csv` — база вредоносных хэшей в формате:

  ```
  <md5>;<verdict>
  098f6bcd4621d373cade4e832627b4f6;Virus
  d41d8cd98f00b204e9800998ecf8427e;EmptyFile
  ```

* `report.log` — файл, в который будет записан отчет:

  ```
  /path/to/file.txt;098f6bcd4621d373cade4e832627b4f6;Virus
  ```

* `./files` — директория для сканирования.

### Пример вывода в консоль

```
===== Scan Report =====
Processed files: 100
Malicious files: 17
Errors: 0
Elapsed time: 0.53214
```

## 🧪 Тестирование

Для запуска тестов:

```bash
cd build
ctest --output-on-failure
```

Тесты проверяют:

* корректность вычисления MD5,
* правильное определение заражённых файлов,
* обработку ошибок при открытии файлов,
* e2e-поведение на подготовленных тестовых данных.

## 📂 Структура проекта

```
.
├── CMakeLists.txt        # корневой CMake
├── main.cpp              # точка входа
├── inc/                  # заголовочные файлы
├── src/                  # исходники
├── tests/                # тесты (GoogleTest)
└── build/                # каталог для сборки
```
