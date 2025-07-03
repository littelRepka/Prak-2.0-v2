#include <drogon/HttpController.h>
#include"calk.h"
#include <sstream>

using namespace drogon;

class Controller : public HttpController<Controller>
{
public:
    Controller() = default;

    METHOD_LIST_BEGIN
        ADD_METHOD_TO(Controller::calculate, "/api/{principal}/{rate}/{time}", Get);
    METHOD_LIST_END

    void calculate(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   double principal,
                   double rate,
                   int time)
    {
        // Переводим процент в долю (например, 5% → 0.05)
        double r = rate / 100.0;

        // Формула сложного процента: A = P * (1 + r)^t
        double amount = principal * std::pow(1 + r, time);

        // Формируем JSON-ответ
        Json::Value result;
        result["principal"] = principal;
        result["rate"] = rate;
        result["time"] = time;
        result["total_amount"] = amount;

        auto resp = HttpResponse::newHttpJsonResponse(result);
        callback(resp);
    }
};