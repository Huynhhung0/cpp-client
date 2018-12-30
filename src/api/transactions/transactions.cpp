
#include "api/transactions/transactions.h"

#include <cstdio>

std::string Ark::Client::API::Transactions::getUnconfirmed(
  const char *const identifier
) {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s?id=%s", Ark::Client::API::Paths::Transactions::unconfirmed, identifier);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Transactions::all(
  int limit /* = 5 */,
  int page /* = 1 */
) {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s?limit=%d&page=%d", Ark::Client::API::Paths::Transactions::base, limit, page);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Transactions::get(
  const char *const identifier
) {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s/%s", Ark::Client::API::Paths::Transactions::base, identifier);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Transactions::allUnconfirmed(
  int limit /* = 5 */,
  int page /* =1 */
) {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s?limit=%d&page=%d", Ark::Client::API::Paths::Transactions::unconfirmed, limit, page);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Transactions::types() {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s", Ark::Client::API::Paths::Transactions::types);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Transactions::search(const std::map<std::string, std::string>& body_parameters, int limit /* = 5 */, int page /* = 1 */) {
  char uri[96] = { };
  snprintf(uri, sizeof(uri), "%s?limit=%d&page=%d", Ark::Client::API::Paths::Transactions::search, limit, page);
  std::string parameterBuffer;
  for (const auto& p : body_parameters) {
    parameterBuffer += p.first + '=' + p.second + '&';
  }
  return http_->post(uri, parameterBuffer.c_str());
}
