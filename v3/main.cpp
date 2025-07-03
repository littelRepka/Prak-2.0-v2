
#include <drogon/drogon.h>

int main() {
    // Загружаем контроллеры, указанные в CMakeLists.txt
    drogon::app().loadConfigFile("config.json");

    // Запускаем сервер
    drogon::app().run();
    return 0;
}