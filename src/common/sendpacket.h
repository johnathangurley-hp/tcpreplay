/* $Id$ */

/*
 * Copyright (c) 2006 Aaron Turner.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright owners nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "defines.h"
#ifdef HAVE_PF_PACKET
#include <sys/socket.h>
#endif

#ifndef _SENDPACKET_H_
#define _SENDPACKET_H_

union sendpacket_handle {
    pcap_t *pcap;
    int fd;
#ifdef HAVE_LIBNET
    libnet_t *lnet;
#endif
};

#define SENDPACKET_ERRBUF_SIZE 1024

struct sendpacket_s {
    int open;
    char device[20];
    char errbuf[SENDPACKET_ERRBUF_SIZE];
    COUNTER retry;
    COUNTER failed;
    COUNTER sent;
    COUNTER bytes_sent;
    COUNTER attempt;
    union sendpacket_handle handle;
    struct tcpr_ether_addr ether;
#ifdef HAVE_PF_PACKET
    struct sockaddr sa;
#endif
};

typedef struct sendpacket_s sendpacket_t;

int sendpacket(sendpacket_t *, const u_char *, size_t);
int sendpacket_close(sendpacket_t *);
char *sendpacket_geterr(sendpacket_t *);
char *sendpacket_getstat(sendpacket_t *);
sendpacket_t *sendpacket_open(const char *, char *);
struct tcpr_ether_addr *sendpacket_get_hwaddr(sendpacket_t *);

#endif /* _SENDPACKET_H_ */