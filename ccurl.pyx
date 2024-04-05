from libc.stddef cimport size_t 
from libc.stdlib cimport free
from libc.stdint cimport uint8_t, uint32_t, uint16_t

cdef extern from "curl/curl.h":
    char *curl_version()

cdef extern from "shim.h":
    char *curl_post_to(const char *url, const uint8_t *encoded_body, uint32_t body_len, char *content_type_header, size_t *resp_len, int *err_http_code, char post, uint16_t to_seconds)


cdef class CurlPy:
    cdef char *out_mem
    def __cinit__(self):
        self.out_mem = NULL

    def __dealloc__(self):
        if self.out_mem:
            free(self.out_mem)

    def request(self, url, encode_body, ct_header, post, timeout):
        """
        :param ct_header: content-type
        :param post: 是否post
        :param timeout: 超时,单位秒
        """
        cdef char *c_url = url
        cdef uint8_t *c_body
        cdef uint32_t c_lenb
        
        if encode_body:
            c_body = encode_body
            c_lenb = len(encode_body)
        else:
            c_body = NULL
            c_lenb = 0

        cdef char *c_header = ct_header
        cdef char c_post = post
        cdef uint16_t c_timeout = timeout

        cdef size_t resp_len
        cdef int http_code

        cdef char *resp = curl_post_to(
            c_url,
            c_body,
            c_lenb,
            c_header,
            &resp_len,
            &http_code,
            c_post,
            c_timeout
        )
        self.out_mem = resp
        return resp

    def curl_version(self):
        return curl_version()
