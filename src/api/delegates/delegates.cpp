
#include "api/delegates/delegates.h"

#include <cstdio>

std::string Ark::Client::API::Delegates::get(const char *const identifier)
{
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s/%s", Ark::Client::API::Paths::Delegates::base, identifier);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Delegates::all(
  int limit /* = 5 */,
  int page /* = 1 */
) {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s?limit=%d&page=%d", Ark::Client::API::Paths::Delegates::base, limit, page);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Delegates::blocks(
  const char *const identifier,
  int limit /* = 5 */,
  int page /* = 1 */
) {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s/%s/blocks?limit=%d&page=%d", Ark::Client::API::Paths::Delegates::base, identifier, limit, page);
  return http_->get(uri);
}

/***/

std::string Ark::Client::API::Delegates::voters(
  const char *const identifier,
  int limit /* = 5 */,
  int page /* = 1 */
) {
  char uri[128] = { };
  snprintf(uri, sizeof(uri), "%s/%s/voters?limit=%d&page=%d", Ark::Client::API::Paths::Delegates::base, identifier, limit, page);
  return http_->get(uri);
}
