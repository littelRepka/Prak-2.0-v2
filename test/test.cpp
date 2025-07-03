#include "../controllers/Controller.cpp" // Assuming this file contains HelloController declaration
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <gtest/gtest.h>

// Test case for HelloController::get
TEST(HelloControllerTest, GetReturnsHelloResponse) {
  // Arrange
  Controller controller;

  // Create a dummy HttpRequest (not used in this example)
  auto request = drogon::HttpRequest::newHttpRequest();

  // Mock response callback
  drogon::HttpResponsePtr response;
  auto callback = [&response](const drogon::HttpResponsePtr &resp) {
    response = resp;
  };

  // Act
    std::vector<std::pair<std::vector<double>, std::string>> testCases = {
      {{10, 10, 10}, "{\"principal\":10.0,\"rate\":10.0,\"time\":10,\"total_amount\":25.937424601000025}"},
      {{100, 15, 10}, "{\"principal\":100.0,\"rate\":15.0,\"time\":10,\"total_amount\":404.55577357079068}"},
      {{100, 1, 50}, "{\"principal\":100.0,\"rate\":1.0,\"time\":50,\"total_amount\":164.46318218438827}"},
      {{0, 0, 0},"{\"principal\":0.0,\"rate\":0.0,\"time\":0,\"total_amount\":0.0}"}};

  for (const auto &[inputCity, expectedBody] : testCases) {
    controller.calculate(request, std::move(callback), inputCity.at(0), inputCity.at(1), inputCity.at(2));
  // Assert
  ASSERT_NE(response, nullptr);
  EXPECT_EQ(response->getStatusCode(), drogon::k200OK);
  EXPECT_EQ(response->getBody(), expectedBody);
  }
}