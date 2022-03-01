#include <iostream>
#include <uwebsockets/App.h>
#include <vector>
#include <thread>
#include <algorithm>

struct UserConnection
{
    std::string* user_name;
    unsigned long user_id;
};

// Client -> server
// SET_NAME = Mike - усановить имя
// MESSAGE_TO = id, message - отправить сообщение пользователю ID = id;

// Server -> client
// NEW_USER, Mike(Name), 12345(ID)

int main()
{
    //атомарный тип данных, позволяет корректно работать с перемнной в многопточности, специально был придуман для многопоточности!
    std::atomic_ulong latest_user_id = 10; //id подключившихся пользователей будет начинаться с 10
                                           //с каждым новым пользователем будем инкрементировать значение
    std::vector<std::thread*> threads(std::thread::hardware_concurrency()); //возвращает число, которое определяет сколько ПК поддерживает паралельных потоков 
    //Мы создали список указателей потоков, дальше функцией transform перебираем каждый элемент
    //вектора в которм создаем новый поток с Вебсокетсервером.
    transform(threads.begin(), threads.end(), threads.begin(), [&latest_user_id](auto* thr)
        {
        return new std::thread([&latest_user_id]()
            {
            uWS::App().ws<UserConnection>("/*",
                {
                   .open = [&latest_user_id](auto* ws)
                    {
                        //что делать при подключении пользователя
                        UserConnection* data = ws->getUserData();
                        data->user_id = latest_user_id++;
                        std::cout << "New user connected, ID: " << data->user_id << std::endl;
                        ws->subscribe("broadcast"); // каждого пользователя подключаем к каналу broadcast
                        ws->subscribe("user#"+ std::to_string(data->user_id));
                    },
                    .message = [&latest_user_id](auto* ws, std::string_view message, uWS::OpCode opCode)
                    {
                        //что делать при получении сообщения
                        UserConnection* data = ws->getUserData();
                        std::cout << "New Message " << message << ", User ID = " << data->user_id << std::endl;
                        auto beginning = message.substr(0, 8);
                        if (beginning == "SET_NAME") //пользователь прислал своё имя
                        {
                            auto name = message.substr(11);
                            data->user_name = new std::string(name);
                            std::cout << "User set their name ID = " << data->user_id << " Name = " << *data->user_name << std::endl;
                            std::string broadcast_message = format("NEW_USER:,{},{}", name, data->user_id);
                            ws->publish("broadcast", broadcast_message, opCode, false);//всех пользователей канала broadcast оповещаем о подключении нового пользователя
                        }
                        auto is_message_t0 = message.substr(0, 11);
                        if (is_message_t0 == "MESSAGE_TO")
                        {
                            //кто-то послал сообщение
                            auto rest = message.substr(11); //id, message
                            int position = rest.find(",");
                            if (position != -1)
                            {
                                auto id_string = rest.substr(0, position);
                                auto user_massage = rest.substr(position + 1);
                                ws->publish("user#" + std::string(id_string), user_massage, opCode, false);
                            }
                        }
                     }   
                }).listen(9999, [&latest_user_id](auto* token)
                    {
                        if (token)
                            std::cout << "Server started and listening on port 9999!" << std::endl;
                        else
                            std::cout << "Server failed to start!" << std::endl;
                    }).run();
            });
        });

    for_each(threads.begin(), threads.end(), [](auto* thr) {thr->join(); });
}
