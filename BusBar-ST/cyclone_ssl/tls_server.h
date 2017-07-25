/**
 * @file tls_server.h
 * @brief Handshake message processing (TLS server)
 *
 * @section License
 *
 * Copyright (C) 2010-2016 Oryx Embedded SARL. All rights reserved.
 *
 * This file is part of CycloneSSL Open.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * @author Oryx Embedded SARL (www.oryx-embedded.com)
 * @version 1.7.2
 **/

#ifndef _TLS_SERVER_H
#define _TLS_SERVER_H

//Dependencies
#include "tls.h"

//Server specific functions
error_t tlsServerHandshake(TlsContext *context);
error_t tlsParseClientMessage(TlsContext *context);

error_t tlsSendServerHello(TlsContext *context);
error_t tlsSendServerKeyExchange(TlsContext *context);
error_t tlsSendCertificateRequest(TlsContext *context);
error_t tlsSendServerHelloDone(TlsContext *context);

error_t tlsParseClientHello(TlsContext *context, const TlsClientHello *message, size_t length);
error_t tlsParseClientKeyExchange(TlsContext *context, const TlsClientKeyExchange *message, size_t length);
error_t tlsParseCertificateVerify(TlsContext *context, const TlsCertificateVerify *message, size_t length);

#endif
