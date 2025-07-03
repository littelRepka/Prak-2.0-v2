#include "../../src/CityInfoController.cpp" // Assuming this file contains CityInfoController declaration
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <gtest/gtest.h>

// Test case for CityInfoController::getCityInfo
TEST(CityInfoControllerTest, GetCityInfoReturnsCorrectResponse) {
  // Arrange
  CityInfoController controller;

  // Create a dummy HttpRequest (not used in this example)
  auto request = drogon::HttpRequest::newHttpRequest();

  // Mock response callback
  drogon::HttpResponsePtr response;
  auto callback = [&response](const drogon::HttpResponsePtr &resp) {
    response = resp;
  };

  // Act: Call getCityInfo with different city names
  std::vector<std::pair<std::string, std::string>> testCases = {
      {"newyork", "New York is a large city in the United States."},
      {"LONDON", "London is the capital of the United Kingdom."},
      {"Tokyo", "Tokyo is the capital of Japan."},
      {"unknown", "City information not found."}};

  for (const auto &[inputCity, expectedBody] : testCases) {
    controller.getCityInfo(request, std::move(callback), inputCity);

    // Assert
    ASSERT_NE(response, nullptr);
    EXPECT_EQ(response->getStatusCode(), drogon::k200OK);
    EXPECT_EQ(response->getBody(), expectedBody);
  }
}