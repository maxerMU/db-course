
#ifndef MyController_hpp
#define MyController_hpp

#include "dto/DTOs.hpp"

#include "Utils.hpp"

#include <unistd.h>
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/web/server/api/ApiController.hpp"

/**
 * Sample Api Controller.
 */
class MyController : public oatpp::web::server::api::ApiController {
 private:
  typedef MyController __ControllerType;

 public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize
   * DTOs.
   */
  MyController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper) {}

 public:
/**
 *  Begin ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_BEGIN(ApiController)

  ENDPOINT_ASYNC("GET", "/test1", Plaintext){

      ENDPOINT_ASYNC_INIT(Plaintext)

          Action act() override{std::string res = "dummy1";
  const auto& response =
      controller -> createResponse(Status::CODE_200, res.c_str());
  response->putHeader(Header::CONTENT_TYPE,
                      oatpp::data::share::StringKeyLabel(nullptr,
                                                         (p_char8) "text/plain",
                                                         10));
  response->putHeader("Date", Utils::renderTime());
  return _return(response);
}
}
;

ENDPOINT_ASYNC("GET", "/test2", Json){

    ENDPOINT_ASYNC_INIT(Json)

        Action act() override{std::string res = "dummy1";
std::string append = "dummy1";
for (size_t i = 0; i < 200000; i++) {
  res += append;
}

const auto& response =
    controller -> createResponse(Status::CODE_200, res.c_str());
response->putHeader(Header::CONTENT_TYPE,
                    oatpp::data::share::StringKeyLabel(nullptr,
                                                       (p_char8) "text/plain",
                                                       10));
response->putHeader("Date", Utils::renderTime());
return _return(response);
}
}
;

/**
 *  Finish ENDPOINTs generation ('ApiController' codegen)
 */
#include OATPP_CODEGEN_END(ApiController)
}
;

#endif /* MyController_hpp */
