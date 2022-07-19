
#include "AsyncExample.hpp"
#include "SimpleExample.hpp"

#include "DemoApiClient.hpp"

#include "oatpp-curl/RequestExecutor.hpp"

#include "oatpp/web/client/HttpRequestExecutor.hpp"
#include "oatpp/network/tcp/client/ConnectionProvider.hpp"

#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp-openssl/client/ConnectionProvider.hpp"
#include "oatpp-openssl/Config.hpp"

#include <iostream>

std::shared_ptr<oatpp::web::client::RequestExecutor> createOatppExecutor() {
  OATPP_LOGD("App", "Using Oat++ native HttpRequestExecutor.");
  auto connectionProvider = oatpp::network::tcp::client::ConnectionProvider::createShared({"127.0.0.1", 3004});
  return oatpp::web::client::HttpRequestExecutor::createShared(connectionProvider);
}

std::shared_ptr<oatpp::web::client::RequestExecutor> createCurlExecutor() {
  OATPP_LOGD("App", "Using oatpp-curl RequestExecutor.");
  return oatpp::curl::RequestExecutor::createShared("https://127.0.0.1:3004/", false /* set verbose=true for dubug info */);
}

// auto config = oatpp::openssl::Config::createShared();
// auto connectionProvider = oatpp::openssl::client::ConnectionProvider::createShared(config, {"https://127.0.0.1:3004/", 3004});

  // tls_config_insecure_noverifycert(config->getTLSConfig());
  //  tls_config_insecure_noverifyname(config->getTLSConfig());


void run(){

  
  
  /* Create ObjectMapper for serialization of DTOs  */
  auto objectMapper = oatpp::parser::json::mapping::ObjectMapper::createShared();
  
  /* Create RequestExecutor which will execute ApiClient's requests */
  // auto requestExecutor = createOatppExecutor();   // <-- Always use oatpp native executor where's possible.
  auto requestExecutor = createCurlExecutor();  // <-- Curl request executor
  
  /* DemoApiClient uses DemoRequestExecutor and json::mapping::ObjectMapper */
  /* ObjectMapper passed here is used for serialization of outgoing DTOs */
  auto config = oatpp::openssl::Config::createShared();
  auto connectionProvider = oatpp::openssl::client::ConnectionProvider::createShared(config, {"https://127.0.0.1:3004/", 3004});

  auto client = DemoApiClient::createShared(requestExecutor, objectMapper);

  
  
  SimpleExample::runExample(client);
  // AsyncExample::runExample(client);
  
}

int main(int argc, const char * argv[]) {

  oatpp::base::Environment::init();
  
  run();
  
  /* Print how much objects were created during app running, and what have left-probably leaked */
  /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
  std::cout << "\nEnvironment:\n";
  std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
  std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
  
  oatpp::base::Environment::destroy();
}
