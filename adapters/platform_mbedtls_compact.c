// Copyright (c) Microsoft. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include "azure_c_shared_utility/platform.h"
#include "azure_c_shared_utility/sntp.h"
#include "azure_c_shared_utility/tlsio_mbedtls.h"

static const char* const ntpServer = "pool.ntp.org";

/* Codes_SRS_PLATFORM_OPENSSL_COMPACT_30_004: [ The platform_init shall initialize the tlsio adapter. ] */
/* Codes_SRS_PLATFORM_OPENSSL_COMPACT_30_005: [ The platform_init shall initialize the sntp client. ] */
int platform_init(void)
{
	// SNTP_SetServerName logs any necessary errors
	int result = SNTP_SetServerName(ntpServer);
	if (result == 0)
	{
		// SNTP_Init will have logged its own errors if necessary
		result = SNTP_Init();
	}
    return result;
}

/* Codes_SRS_PLATFORM_OPENSSL_COMPACT_30_008: [ The platform_get_default_tlsio shall return a set of tlsio functions provided by the OpenSSL micro tlsio implementation. ] */
const IO_INTERFACE_DESCRIPTION* platform_get_default_tlsio(void)
{
    return tlsio_mbedtls_get_interface_description();
}

STRING_HANDLE platform_get_platform_info(void)
{
    return STRING_construct("(mbedtls_compact)");
}

/* Codes_SRS_PLATFORM_OPENSSL_COMPACT_30_006: [ The platform_deinit shall deinitialize the sntp client. ] */
/* Codes_SRS_PLATFORM_OPENSSL_COMPACT_30_007: [ The platform_deinit shall deinitialize the tlsio adapter. ] */
void platform_deinit(void)
{
	SNTP_Deinit();

	// The tlsio adapter for this platform does not need (or support) deinitialization
}
