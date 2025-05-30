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