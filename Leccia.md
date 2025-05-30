
## Веб-программирование на C++ и реализация REST API
## 1. Теоретическая часть
#### Что такое веб-программирование и зачем на C++
**Веб-программирование** - это разработка программного обеспечения, позволяющего клиенту (это браузер или мобильное приложение) взаимодействовать с сервером по протоколу HTTP/HTTPS. При этом запросы клиента отправляются на URL-адреса, а сервер возвращает ответы, часто в формате JSON или XML. Традиционно веб-серверы пишутся на языках высокого уровня (Python, Java, JavaScript/Node.js, PHP и др.), однако и C++ также может подходить. Преимущество использования C++ для веб-программирования связаны прежде всего с производительностью и эффективным управлением ресурсами. C++ позволяет создавать очень быстрые серверы с низкой задержкой и высокой пропускной способностью, что критично для систем, обрабатывающих большое число одновременных запросов. Кроме того, C++ дает тонкий контроль над выделением **памяти и потоками исполнения**, что может быть важно для тонкой настройки производительности. C++ - кроссплатформенный язык, и код на нём можно компилировать под разные ОС (Windows, Linux дистрибутивы, macOS и др.). 
### Плюсы C++ в веб-разработке: 
- высокая скорость и эффективность выполнения кода, контроль над ресурсами, 
- поддержка многопоточности, очень богатый набор библиотек (например, Boost.Beast для HTTP)
### Минусы C++: 
- более сложный синтаксис и длительная разработка (в сравнении с динамическими языками), 
- ручное управление памятью (отсутствие сборщика мусора), потенциальные уязвимости (например, утечки памяти или ошибочное обращение к памяти) и ограниченный выбор фреймворков по сравнению с экосистемами Java или JavaScript. 
- -Кроме того, инфраструктура разработки на C++ может требовать настройки (компиляция, "линковка" библиотек и т.д.), что увеличивает время написания и запуска, отладки кода. 

C++ используется для Web-разработки, когда важна **максимальная производительность** и контроль, но это требует от разработчика очень высокого уровня мастерства: нужно знать оптимизационные алгоритмы и разные низкоуровневые Best-практисы.

## Основы REST API
**REST (REpresentational State Transfer)** - архитектурный стиль взаимодействия клиент-сервер через стандартные методы HTTP. в **2000 году** в его докторской диссертации **«Architectural Styles and the Design of Network-based Software Architectures»** , защищённой в Университете Калифорнии в Ирвине. Эта работа заложила основы стандартизированного подхода к проектированию веб-сервисов, опираясь на архитектурные принципы HTTP и других протоколов. REST основывается на понятиях **"ресурса" и "глагола"**: **ресурс - это сущность, доступная по URL, а «глагол» - это HTTP-метод, описывающий действие над ресурсом**

- Другими словами, каждое RESTful API имеет набор ресурсов (например, /tasks для задач, /users для пользователей), и для каждого ресурса можно выполнять стандартные действия через HTTP-методы. Ключевые свойства REST:
	- Статусность (Statelessness): каждый запрос от клиента к серверу содержит всю информацию, необходимую для обработки, и сервер не хранит состояние между запросами. Это упрощает масштабирование, так как любой сервер может обслужить любой запрос без учёта предыдущих взаимодействий.
	- Идентификация ресурсов: каждый ресурс имеет уникальный URL. Например, /tasks/123 может обозначать задачу с ID=123.
	- Унифицированный интерфейс: используются стандартные HTTP-методы для операций над ресурсами, обычно (99% времени) это:
		- GET (получение), 
		- POST (создание), 
		- PUT (обновление на новый), 
		- DELETE (удаление).
		- PATCH (редактировани)
Это упрощает понимание API: например, GET /tasks - получить список задач, POST /tasks - создать новую задачу, GET /tasks/123 - получить задачу с id=123, PUT /tasks/123 - обновить её с нуля, DELETE /tasks/123 - удалить, PATCH /tasks/123 - изменить поле внутри.
	- Передача представлений ресурса: данные о ресурсах передаются в формате JSON (или XML/текст). JSON (JavaScript Object Notation) - легковесный текстовый формат обмена данными, удобный для людей и машин; он не зависит от языка программирования и широко используется для Веб апи.

Таким образом, REST позволяет разработчикам создавать стандартизированные веб-сервисы. В REST-подходе URL и методы используются "чётко и однозначно": URL указывает на ресурс, а метод определяет действие. Например, запрос POST /user создаёт нового пользователя, вместо неясных эндпоинтов вроде /user.php?action=create

Сервер на запросы должен отвечать соответствующими статус-кодами HTTP. Самые популярные примеры:
- **Код 200 (OK)** означает, что запрос успешно выполнен
- **Код 201 (Created)** обычно возвращается, когда новый ресурс успешно создан (обычно в ответ на POST)
- **Код 400 (Bad Request)** Если клиент отправил некорректный запрос.
- **Код 404 (Not Found)** Если запрошенный ресурс не найден
- **Код 500 (Internal Server Error)**. При внутренней ошибке сервера

Эти коды позволяют клиенту понять, что произошло, и предпринимать соответствующие действия (повторить запрос, обработать ошибку и т.д.).

### Обзор протокола HTTP
HTTP (Hypertext Transfer Protocol) - это базовый протокол Интернета для взаимодействия клиент-сервер. Коммуникация основана на сообщениях: запросы (request) от клиента и ответы (response) от сервера. Каждое сообщение состоит из трёх частей: стартовой строки (request-line или status-line), набора заголовков (HTTP headers) и тела сообщения (body).

Для запроса стартовая строка имеет формат 
`METHOD URL HTTP/VERSION`
(например, `GET /api/tasks HTTP/1.1`). Далее следуют заголовки (`Content-Type`,` Host`, `Authorization` и др.) и возможно тело (для POST/PUT с данными JSON).
Для ответа стартовая строка выглядит как 
```HTTP/VERSION STATUS_CODE REASON```
(например, `HTTP/1.1 200 OK`), после чего идут заголовки и тело (например, JSON-данные).
Протокол HTTP/1.1 поддерживает постоянные соединения (keep-alive), при которых одно TCP-соединение может обслуживать несколько запросов подряд, что повышает эффективность. HTTP является **stateless** - то есть у сервера по умолчанию нет состояния между запросами, каждый запрос независим и не зависит друг от дружки. Это обеспечивает масштабируемость и надёжность. Новые версии, такие как HTTP/2, повышают эффективность передачи (сжатие заголовков, мультиплексирование), но принципы REST остаются теми же. 

В целом, веб-программирование на C++ означает реализацию вышеописанных механизмов (приём HTTP-запросов, маршрутизация к ресурсам, формирование ответов, сериализация/десериализация JSON и т.д.) с помощью C++-инструментов и библиотек. В качестве примеров библиотек для работы с HTTP и JSON часто упоминаются Boost.Beast (HTTP+WebSocket) и nlohmann/json (JSON for Modern C++).

## 2. Практическая часть
Мы создадим простой REST-сервер на C++ под Windows с использованием Boost.Beast и nlohmann/json. Сервер будет хранить простую коллекцию задач (или заметок) в памяти и поддерживать CRUD-операции по HTTP.
### Установка Boost и зависимостей
**Boost** - это набор высококачественных C++ библиотек, в том числе и для создания REST. Чтобы использовать Boost.Beast, требуется сам Boost (и Boost.Asio) и компилятор C++11 или выше. Boost.Beast - заголовочная библиотека (header-only), построенная на Boost.Asio.

Её можно получить следующими способами:
- **Через vcpkg** (рекомендуется для Windows):
1. Скачайте и установите vcpkg
```bash
git clone https://github.com/microsoft/vcpkg.git
cd .\vcpkg\
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```
Если  будет использоваться vcpkg, для билда с CMAKE потребуется указывать путь, который выдастся в установке, смотря куда вы установили путь.
```
DCMAKE_TOOLCHAIN_FILE=C:/Users/...{Ваш путь}.../vcpkg/scripts/buildsystems/vcpkg.cmake
```
3. В командной строке выполните 
```
vcpkg install boost-beast
vcpkg install nlohmann-json
 ```
 Это установит Boost (включая Boost.Asio) и библиотеку JSON в систему.
4. Настройте интеграцию vcpkg с CMake (vcpkg integrate install), чтобы CMake автоматически находил эти пакеты.
- Альтернативный путь - **Ручная установка Boost:**
5. Скачайте Boost с официального сайта (boost_1_82_0.zip) и распакуйте.
6. Подключите папку boost в настройки include-пути. Многие библиотеки Boost заголовочные, их не нужно отдельно компилировать. Boost.Beast входит в Boost с версии 1.66+. 
7. Для Boost.Asio может потребоваться подключить системную библиотеку для сокетов (Ws2_32.lib) на Windows.

- **nlohmann/json** - популярная header-only библиотека для работы с JSON. Её можно получить, скачав единичный заголовочный файл json.hpp или через пакетный менеджер (например, vcpkg install nlohmann-json). 

В итоге проект будет включать следующие зависимости: **Boost.Beast** (в составе Boost), **Boost.Asio** (Boost.System), и **nlohmann/json.**

### Структура проекта

Наш проект будет состоять из:

-   **main.cpp** - основной файл с реализацией сервера.
    
-   **CMakeLists.txt** - файл конфигурации CMake.

- **test_tasks.cpp** - файл для тестов
    

В `main.cpp` будем:

1.  Устанавливать сетевой слушатель на указанный адрес и порт.
    
2.  Принимать входящие соединения и читать HTTP-запрос.
    
3.  Обрабатывать запрос: разбирать URL, метод, возможно тело JSON.
    
4.  Выполнять операции над локальным хранилищем задач (в данном случае – вектор или карта).
    
5.  Формировать HTTP-ответ с соответствующим кодом и JSON-данными.
    

Хранилище задач реализуем просто, например через `std::map<int, Task>` в памяти. Структура `Task` может иметь поля `id`, `title`, `description`. ID будем генерировать самостоятельно.

Обработка запроса:

-   Разберём `request.target()` – строку URL.
    
-   Если запрос на `/tasks` с GET – вернём список всех задач в JSON.
    
-   Если POST `/tasks` – прочитаем JSON из тела, создадим новую задачу, вернём 201 Created.
    
-   Если GET `/tasks/{id}` – попытаемся найти задачу с заданным ID и вернуть её или 404.
    
-   Если PUT `/tasks/{id}` – обновим существующую задачу (если есть) или вернём 404.
    
-   Если DELETE `/tasks/{id}` – удалим задачу или вернём 404.
    

Обычный цикл сервера (однопоточный, для простоты) будет таким: слушаем порт, принимаем соединение, читаем запрос, обрабатываем, отправляем ответ, закрываем соединение. Для многозадачности можно было бы использовать `async` и отдельные потоки.

## Наш REST сервер (main.cpp)

```cpp
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>

using namespace std;

namespace beast = boost::beast;
namespace http  = beast::http;
namespace net   = boost::asio;
using tcp       = net::ip::tcp;
using json      = nlohmann::json;

// структура задачи
struct Task {
    int Id;
    string Title;
    string Desc;
};

// хранилище задач
map<int, Task> tasks;
int id_counter = 1; // счетчик айди

// отправка ответа клиенту
void send(tcp::socket& sock, http::response<http::string_body>&& reply) {
    reply.prepare_payload();
    http::write(sock, reply);
}

int main(int argc, char* argv[]) {
    // проверка аргументов
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " address port\n";
        return 1;
    }

    auto addr = net::ip::make_address(argv[1]);
    unsigned short port = atoi(argv[2]);

    net::io_context ctx{1};
    tcp::acceptor acceptor{ctx, {addr, port}};
    cout << "Сервер запущен на " << argv[1] << ":" << argv[2] << "\n";

    while (true) {
        tcp::socket sock{ctx};
        acceptor.accept(sock); // принимаем соединение

        beast::flat_buffer buffer;  
        http::request<http::string_body> req;  
        http::read(sock, buffer, req); // читаем запрос

        // формируем ответ
        http::response<http::string_body> resp;
        resp.version(req.version());
        resp.set(http::field::server, "MyCPPServer");
        resp.set(http::field::content_type, "application/json");
        resp.keep_alive(false);

        string path = string(req.target()); // путь из запроса

        // обработка GET /tasks
        if (req.method() == http::verb::get && path == "/tasks") {
            json arr = json::array();
            for (auto& p : tasks) {
                Task& t = p.second;
                arr.push_back({{"Id", t.Id}, {"Title", t.Title}, {"Desc", t.Desc}});
            }
            resp.result(http::status::ok);
            resp.body() = arr.dump();
        }

        // обработка GET /tasks/1
        else if (req.method() == http::verb::get && path.find("/tasks/") == 0) {
            try {
                int id = stoi(path.substr(7));
                auto it = tasks.find(id);
                if (it != tasks.end()) {
                    Task& t = it->second;
                    json j = {{"Id", t.Id}, {"Title", t.Title}, {"Desc", t.Desc}};
                    resp.result(http::status::ok);
                    resp.body() = j.dump();
                } else {
                    resp.result(http::status::not_found);
                    resp.body() = R"({"error":"не найдено"})";
                }
            } catch (...) {
                resp.result(http::status::bad_request);
                resp.body() = R"({"error":"неверный айди"})";
            }
        }

        // обработка POST /tasks
        else if (req.method() == http::verb::post && path == "/tasks") {
            try {
                auto j = json::parse(req.body());
                Task t;
                t.Id = id_counter++;
                t.Title = j.value("title", "");
                t.Desc = j.value("description", "");
                tasks[t.Id] = t;
                resp.result(http::status::created);
                json out = {{"Id", t.Id}, {"Title", t.Title}, {"Desc", t.Desc}};
                resp.body() = out.dump();
            } catch (...) {
                resp.result(http::status::bad_request);
                resp.body() = R"({"error":"ошибка парсинга"})";
            }
        }

        // обработка PUT /tasks/1
        else if (req.method() == http::verb::put && path.find("/tasks/") == 0) {
            try {
                int id = stoi(path.substr(7));
                auto it = tasks.find(id);
                if (it != tasks.end()) {
                    auto j = json::parse(req.body());
                    Task& t = it->second;
                    if (j.contains("title")) t.Title = j["title"];
                    if (j.contains("description")) t.Desc = j["description"];
                    json out = {{"Id", t.Id}, {"Title", t.Title}, {"Desc", t.Desc}};
                    resp.result(http::status::ok);
                    resp.body() = out.dump();
                } else {
                    resp.result(http::status::not_found);
                    resp.body() = R"({"error":"не найдено"})";
                }
            } catch (...) {
                resp.result(http::status::bad_request);
                resp.body() = R"({"error":"ошибка"})";
            }
        }

        // обработка DELETE /tasks/1
        else if (req.method() == http::verb::delete_ && path.find("/tasks/") == 0) {
            try {
                int id = stoi(path.substr(7));
                if (tasks.erase(id)) {
                    resp.result(http::status::ok);
                    resp.body() = R"({"result":"удалено"})";
                } else {
                    resp.result(http::status::not_found);
                    resp.body() = R"({"error":"не найдено"})";
                }
            } catch (...) {
                resp.result(http::status::bad_request);
                resp.body() = R"({"error":"ошибка"})";
            }
        }

        // все остальные запросы не делаем
        else {
            resp.result(http::status::bad_request);
            resp.body() = R"({"error":"неизвестный запрос"})";
        }

        send(sock, std::move(resp)); // отправляем ответ
    }

    return 0;
}
```
Запускать из папки build\Debug
```
.\rest_server.exe 0.0.0.0 8080
```

**Пояснения к коду:**

-   Мы используем Boost.Beast (`boost::beast::http`) для работы с HTTP. Классы `http::request<http::string_body>` и `http::response<http::string_body>` позволяют легко читать/писать HTTP с телом в виде строки.
    
-   Сервер принимает соединения в цикле `while (true)`. Для каждого соединения создаём `tcp::socket` и принимаем запрос через `acceptor.accept(socket)`. Затем читаем запрос с помощью `http::read`.
    
-   URL запроса получаем через `req.target()`. В примере мы просто сравниваем строки: `"/tasks"` или начинающиеся с `"/tasks/"`. Для реальных приложений можно использовать роутер или регулярные выражения.
    
-   Для работы с JSON используется библиотека nlohmann/json. Пример: `json j = json::parse(req.body())` читает JSON из тела запроса, а `json::dump()` возвращает строку JSON.
    
-   Ответ строим в объекте `http::response`. Обязательно вызываем `res.prepare_payload()`, чтобы установились заголовки `Content-Length` и т.д. Потом отправляем ответ с помощью `http::write`.
    
-   Статусы ответов устанавливаем через `res.result(http::status::ok)`, `created`, `not_found` и т.д. Типы статусов описаны в MDN. Например, `http::status::created` соответствует 201.
    
-   Хранилище задач – простая `std::map<int, Task> tasks`. Поле `next_id` обеспечивает уникальность ID. Мы не подключаем базу данных, всё хранится в памяти.


### Сборка проекта через CMake

`CMakeLists.txt`, который собирает наш сервер (файл `main.cpp`):

```C
cmake_minimum_required(VERSION 3.10)
project(CPP_REST_Server)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Если хотите подавить предупреждение FindBoost:
# cmake_policy(SET CMP0167 NEW)

# Находим Boost (только компонент system, Beast/Asio header-only)
find_package(Boost REQUIRED COMPONENTS system)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

# Находим JSON
find_package(nlohmann_json CONFIG REQUIRED)

# Находим Catch2 (vcpkg catch2 предоставляет цель Catch2::Catch2WithMain)
find_package(Catch2 CONFIG REQUIRED)

# основной сервер 
add_executable(rest_server main.cpp)

if(WIN32)
    target_link_libraries(rest_server PRIVATE ws2_32)
endif()
target_link_libraries(rest_server
    PRIVATE
        Boost::system
        nlohmann_json::nlohmann_json
)

# юнит-тесты
enable_testing()
add_executable(tests test_tasks.cpp)

if(WIN32)
    target_link_libraries(tests PRIVATE ws2_32)
endif()
target_link_libraries(tests
    PRIVATE
        Boost::system
        nlohmann_json::nlohmann_json
        Catch2::Catch2WithMain
)

add_test(NAME all_unit_tests COMMAND tests)

```

**Объяснение CMake:**

-   `find_package(Boost REQUIRED)` находит Boost. Мы используем header-only компоненты Beast и Asio, поэтому достаточно подключить include-пути через `${Boost_INCLUDE_DIRS}` (с флагом `Boost::headers`).
    
-   На Windows для сетевых вызовов Asio необходимо линковать системную библиотеку Winsock (`ws2_32.lib`). В CMake это делается условным блоком:
    
```cmake
    if(WIN32)
        target_link_libraries(<target> PRIVATE ws2_32)
    endif()
```
    
-   `find_package(nlohmann_json CONFIG REQUIRED)` находит библиотеку nlohmann/json (например, установленную через vcpkg) и предоставляет таргет `nlohmann_json::nlohmann_json`.
    
-   `find_package(Catch2 CONFIG REQUIRED)` находит фреймворк Catch2 для юнит-тестов и предоставляет таргет `Catch2::Catch2`.
    
-   `target_link_libraries(rest_server PRIVATE Boost::headers Boost::system nlohmann_json::nlohmann_json)`:
    
    -   `Boost::headers` — include-только заголовки Boost.Beast/Asio.
        
    -   `Boost::system` — линковка библиотеки Boost.System, необходимой для работы Asio.
        
    -   `nlohmann_json::nlohmann_json` — библиотека JSON.
        
-   Для тестового таргета `tests` дополнительно линкуем `Catch2::Catch2`, чтобы была доступна макрос-библиотека Catch2.

**После настройки `CMakeLists.txt` можно собрать проект командами вместе с vcpkg**
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=C:/Users/{Путь до vcpkg}/vcpkg/scripts/buildsystems/vcpkg.cmake
cmake --build .
```

В результате получится исполняемый файл `rest_server.exe` , который можно запустить указав адрес и порт, например:
```bash
rest_server 0.0.0.0 8080
```
Теперь сервер слушает входящие HTTP-запросы на порту 8080. А тесты запустим через
```
./tests
```


## ## Тестирование через Postman

После запуска сервера вы можете протестировать его работу с помощью **Postman** — удобного инструмента для тестирования API. Потребуется скачать приложение Postman на ПК и зарегестрироваться через Google аккаунт. Варианты тестирования:

### 1. Добавление задачи (POST)

Добавить новую задачу в систему. Потребуется создать New Collection и уже в ней, кликнув ПКМ, нажать Add Request

#### Настройки:

-   **Метод:** `POST`
-   **URL:** `http://localhost:8080/tasks`
-   **Headers:**
    -   `Content-Type`: `application/json`
-   **Body (raw / JSON):**
```json
{
  "title": "Test Task",
  "description": "Sample description"
}
```
#### Как выполнить:

1.  Выберите метод `POST` в левой части адресной строки.
2.  Введите URL: `http://localhost:8080/tasks`.
3.  Перейдите на вкладку **Headers** и добавьте пару:
    -   Key: `Content-Type`, Value: `application/json`.
4.  Переключитесь на вкладку **Body** , выберите `raw`, затем из выпадающего списка справа — `JSON`.
5.  Вставьте JSON-тело как указано выше.
6.  Нажмите **Send** .
7. Для всех других запросов идея похожая

Если в строке ответа пришел 201 Created, значит, всё получилось.

Пример успешного выполнения:
<img width="990" alt="image" src="https://github.com/user-attachments/assets/6acec1cc-ee8f-4168-9336-118c7199b26f" />


### 2. Получение списка задач (GET)

Получить список всех задач.

#### Настройки:

-   **Метод:** `GET`
-   **URL:** `http://localhost:8080/tasks`

Ожидаемый ответ:
```json
[
  {
    "Id": 1,
    "Title": "Test Task",
    "Desc": "Sample description"
  }
]
```
Статус: **200 OK**

### 3. Обновление задачи (PUT)

Обновить существующую задачу по её ID.

#### Настройки:

-   **Метод:** `PUT`
-   **URL:** `http://localhost:8080/tasks/1`
-   **Headers:**
    -   `Content-Type`: `application/json`
**Body (raw / JSON)**
```json
{
  "description": "Update"
}
```
Ожидаемый результат
```json
{
  "Id": 1,
  "Title": "Test Task",
  "Desc": "Update"
}
```
Статус: **200 OK**

### 4. Удаление задачи (DELETE)

Удалить задачу по её ID.

#### Настройки:

-   **Метод:** `DELETE`
-   **URL:** `http://localhost:8080/tasks/1`
Ожидаемый результат:
```json
{"result":"deleted"}
```
Статус: **200 OK**


Get запрос также можно протестировать через браузер - перейти по URL сервера.


## Юнит-тесты
Нужно будет установить Catch 2
```
.\vcpkg install catch2
```

```cpp
#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

// структура задачи
struct Task {
    int Id;
    std::string Title;
    std::string Desc;
};

// глобальное хранилище задач
std::map<int, Task> tasks;
int id_counter = 1; // счетчик айди

// функция добавления задачи
Task add(const std::string& title, const std::string& desc) {
    Task t;
    t.Id = id_counter++;
    t.Title = title;
    t.Desc = desc;
    tasks[t.Id] = t;
    return t;
}

// обновление задачи
bool update(int id, const std::string& title, const std::string& desc) {
    auto it = tasks.find(id);
    if (it == tasks.end()) return false;
    it->second.Title = title;
    it->second.Desc = desc;
    return true;
}

// удаление задачи
bool del(int id) {
    return tasks.erase(id) > 0;
}

// поиск задачи
Task* find(int id) {
    auto it = tasks.find(id);
    return (it != tasks.end()) ? &it->second : nullptr;
}

// очистка хранилища
void clear() {
    tasks.clear();
    id_counter = 1;
}

// тест сериализации json
TEST_CASE("json тест", "[json]") {
    Task t1 = {1, "test", "desc"};
    json j = {
        {"Id", t1.Id},
        {"Title", t1.Title},
        {"Desc", t1.Desc}
    };
    
    // проверка полей json
    REQUIRE(j["Id"] == 1);
    REQUIRE(j["Title"] == "test");
    REQUIRE(j["Desc"] == "desc");

    // обратная проверка
    Task t2;
    t2.Id = j["Id"];
    t2.Title = j["Title"];
    t2.Desc = j["Desc"];
    REQUIRE(t2.Id == 1);
    REQUIRE(t2.Title == "test");
    REQUIRE(t2.Desc == "desc");
}

// тест crud операций
TEST_CASE("тест хранилища", "[storage]") {
    clear(); 

    SECTION("добавление и поиск") {
        Task t = add("title1", "desc1");
        REQUIRE(t.Id == 1); // первый айди
        REQUIRE(t.Title == "title1");
        REQUIRE(t.Desc == "desc1");

        Task* found = find(1);
        REQUIRE(found != nullptr);
        REQUIRE(found->Title == "title1");
        REQUIRE(found->Desc == "desc1");
    }

    SECTION("обновление") {
        Task t = add("old", "old");
        REQUIRE(update(t.Id, "new", "new_desc"));
        Task* updated = find(t.Id);
        REQUIRE(updated != nullptr);
        REQUIRE(updated->Title == "new");
        REQUIRE(updated->Desc == "new_desc");
    }

    SECTION("обновление несуществующей") {
        clear();
        REQUIRE(!update(999, "x", "y")); // должен вернуть false
    }

    SECTION("удаление") {
        Task t = add("a", "b");
        REQUIRE(del(t.Id)); // удаляем
        REQUIRE(find(t.Id) == nullptr); // не должно быть
    }

    SECTION("удаление несуществующей") {
        clear();
        REQUIRE(!del(5)); // тоже false
    }
}
```
Запускать из папки build\Debug проекта которые уже был отбилжен 
```
.\tests.exe
```

Пример успешного выполнения:
<img width="451" alt="image" src="https://github.com/user-attachments/assets/23a87dd2-06b1-4db2-b08b-cceb1098ea17" />

Однако полные интеграционные тесты лучше проводить через реальные HTTP-запросы, так как взаимодействие сервера с клиентом сложно подменить заглушками.
