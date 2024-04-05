#include "shim.h"
#include "curl/curl.h"
#include <stdlib.h>
#include <string.h>

#define ca_path "./cacert.pem"

struct MemoryStruct
{
  char *memory;
  size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb,
                                  void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;

  char *temp = (char *)realloc(mem->memory, mem->size + realsize + 1);
  if (temp == NULL)
  {
    return 0;
  }

  mem->memory = temp;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

char *curl_post_to(const char *url, const uint8_t *encoded_body,
                   uint32_t body_len, char *content_type_header,
                   size_t *resp_len, int *err_http_code, char post,
                   uint16_t to_seconds)
{
  CURL *curl;
  CURLcode res;
  struct MemoryStruct chunk;
  *err_http_code = 200;

  chunk.memory = (char *)malloc(1);
  chunk.size = 0;

  curl_global_init(3);
  curl = curl_easy_init();

  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, to_seconds);

  curl_easy_impersonate(curl, "chrome116", 1);

  struct curl_slist h1 = {content_type_header, NULL};
  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, &h1);

  curl_easy_setopt(curl, CURLOPT_CAINFO, ca_path);

  if (1 == post)
  {
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    char cnt_len[32];
    snprintf(cnt_len, sizeof(cnt_len), "Content-Length: %d", body_len);
    curl_slist_append(&h1, cnt_len);

    curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, body_len);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, encoded_body);
  }

  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

  res = curl_easy_perform(curl);

  if (res != CURLE_OK)
  {
    free(chunk.memory);
    *resp_len = 0;
    curl_easy_cleanup(curl);
    return NULL;
  }

  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  curl_easy_cleanup(curl);

  if (http_code >= 400)
  {
    free(chunk.memory);
    *resp_len = 0;
    *err_http_code = http_code;

    return NULL;
  }

  *resp_len = chunk.size;
  return chunk.memory;
}