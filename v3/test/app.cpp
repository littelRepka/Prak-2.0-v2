#include <drogon/drogon.h>
using namespace drogon;

int main() {
    app().registerHandler("/", [](const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback){
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("Hello from Drogon in Alpine!");
        resp->setStatusCode(k200OK);
        callback(resp);
    });

    LOG_INFO << "Starting server on 0.0.0.0:8080";
    app().listen("0.0.0.0", 8080);
    app().run();

    return 0;
}