#include "stdafx.h"
#include <uv.h>


void on_dev_read(uv_udp_t *req, ssize_t nread, const uv_buf_t * pBuf, const struct sockaddr *addr, unsigned flags);