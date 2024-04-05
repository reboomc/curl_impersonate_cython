#ifndef SHIM_H
#define SHIM_H

#include <stddef.h>
#include <stdint.h>

#define CURL_STATICLIB

char *curl_post_to(const char *url, const uint8_t *encoded_body,
                   uint32_t body_len, char *content_type_header,
                   size_t *resp_len, int *err_http_code, char post,
                   uint16_t to_seconds);

#endif