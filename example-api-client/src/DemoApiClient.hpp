#ifndef DemoApiClient_hpp
#define DemoApiClient_hpp

#include "DemoApiModels.hpp"

#include "oatpp/web/client/ApiClient.hpp"
#include "oatpp/core/macro/codegen.hpp"

class DemoApiClient : public oatpp::web::client::ApiClient {
#include OATPP_CODEGEN_BEGIN(ApiClient)
  
  API_CLIENT_INIT(DemoApiClient)
  
  //-----------------------------------------------------------------------------------------------
  // Synchronous calls
  
  API_CALL_ASYNC("GET", "/", getRootAsync)
  
  API_CALL("GET", "get1", doget)
  API_CALL("POST", "post1", doPost, BODY_STRING(String, body))
  API_CALL("PUT", "put", doPut, BODY_STRING(String, body))
  API_CALL("PATCH", "patch", doPatch, BODY_STRING(String, body))
  API_CALL("DELETE", "delete", doDelete)
  
  API_CALL("POST", "post", doPostWithDto, BODY_DTO(Object<MyRequestDto>, body))
  
  API_CALL("GET", "get1", doGetAnything, PATH(String, parameter))
  API_CALL("POST", "post1", doPostAnything, PATH(String, parameter), BODY_STRING(String, body))
  API_CALL("PUT", "anything/{parameter}", doPutAnything, PATH(String, parameter), BODY_STRING(String, body))
  API_CALL("PATCH", "anything/{parameter}", doPatchAnything, PATH(String, parameter), BODY_STRING(String, body))
  API_CALL("DELETE", "anything/{parameter}", doDeleteAnything, PATH(String, parameter))
  
  //-----------------------------------------------------------------------------------------------
  // Same calls but async
  
  API_CALL_ASYNC("GET", "get1", doGetAsync)
  API_CALL_ASYNC("POST", "post1", doPostAsync, BODY_STRING(String, body))
  API_CALL_ASYNC("PUT", "put", doPutAsync, BODY_STRING(String, body))
  API_CALL_ASYNC("PATCH", "patch", doPatchAsync, BODY_STRING(String, body))
  API_CALL_ASYNC("DELETE", "delete", doDeleteAsync)
  
  API_CALL_ASYNC("POST", "post1", doPostWithDtoAsync, BODY_DTO(Object<MyRequestDto>, body))
  
  API_CALL_ASYNC("GET", "get1", doGetAnythingAsync, PATH(String, parameter))
  API_CALL_ASYNC("POST", "post1", doPostAnythingAsync, PATH(String, parameter), BODY_STRING(String, body))
  API_CALL_ASYNC("PUT", "anything/{parameter}", doPutAnythingAsync, PATH(String, parameter), BODY_STRING(String, body))
  API_CALL_ASYNC("PATCH", "anything/{parameter}", doPatchAnythingAsync, PATH(String, parameter), BODY_STRING(String, body))
  API_CALL_ASYNC("DELETE", "anything/{parameter}", doDeleteAnythingAsync, PATH(String, parameter))
  
#include OATPP_CODEGEN_END(ApiClient)
};

#endif /* DemoApiClient_hpp */
