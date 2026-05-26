#ifndef __AES_ALT_H
#define __AES_ALT_H

#include <stdint.h>

#include "fr30xx.h"

typedef struct {
    enum_AES_KEY_MODE_t key_mode;
    uint8_t key[32];
} mbedtls_aes_context;

typedef struct {
    mbedtls_aes_context crypt; /*!< The AES context to use for AES block
                                        encryption or decryption. */
    mbedtls_aes_context tweak; /*!< The AES context used for tweak
                                        computation. */
} mbedtls_aes_xts_context;

#endif  // _AES_ALT_H
