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