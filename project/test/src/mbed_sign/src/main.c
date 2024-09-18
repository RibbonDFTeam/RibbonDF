#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/rsa.h"
#include "mbedtls/sha256.h"
#include "mbedtls/pk.h"
#include <stdio.h>
#include <string.h>

// 生成密钥对
int generate_key_pair(mbedtls_pk_context *pk)
{
    mbedtls_rsa_context rsa;
    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    const char *pers = "rsa_genkey";
    int ret;

    mbedtls_entropy_init(&entropy);
    mbedtls_ctr_drbg_init(&ctr_drbg);
    mbedtls_rsa_init(&rsa);

    if ((ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy,
                                     (const unsigned char *)pers, strlen(pers)))
        != 0)
    {
        return ret;
    }

    if ((ret = mbedtls_rsa_gen_key(&rsa, mbedtls_ctr_drbg_random, &ctr_drbg, 2048, 65537)) != 0)
    {
        return ret;
    }

    mbedtls_pk_init(pk);
    if ((ret = mbedtls_pk_setup(pk, mbedtls_pk_info_from_type(MBEDTLS_PK_RSA))) != 0)
    {
        return ret;
    }

    mbedtls_rsa_context *rsa_ctx = mbedtls_pk_rsa(*pk);
    mbedtls_rsa_copy(rsa_ctx, &rsa);

    mbedtls_rsa_free(&rsa);
    mbedtls_ctr_drbg_free(&ctr_drbg);
    mbedtls_entropy_free(&entropy);

    return 0;
}

// 签名
int sign_data(mbedtls_pk_context *pk, const unsigned char *data, size_t data_len, unsigned char *sig, size_t *sig_len)
{
    int ret;
    unsigned char hash[32];

    mbedtls_sha256(data, data_len, hash, 0);

    if ((ret = mbedtls_pk_sign(pk, MBEDTLS_MD_SHA256, hash, 0, sig, MBEDTLS_MPI_MAX_SIZE, sig_len,
                               mbedtls_ctr_drbg_random, NULL))
        != 0)
    {
        return ret;
    }

    return 0;
}

// 验证签名
int verify_signature(mbedtls_pk_context *pk, const unsigned char *data, size_t data_len, const unsigned char *sig, size_t sig_len)
{
    int ret;
    unsigned char hash[32];

    mbedtls_sha256(data, data_len, hash, 0);

    if ((ret = mbedtls_pk_verify(pk, MBEDTLS_MD_SHA256, hash, 0, sig, sig_len)) != 0)
    {
        return ret;
    }

    return 0;
}

int main()
{
    mbedtls_pk_context pk;
    unsigned char sig[MBEDTLS_MPI_MAX_SIZE];
    size_t sig_len;
    const char *message = "Hello, World!";
    int ret;

    // 生成密钥对
    if ((ret = generate_key_pair(&pk)) != 0)
    {
        printf("Failed to generate key pair: -0x%04x\n", -ret);
        return 1;
    }

    // 签名
    if ((ret = sign_data(&pk, (const unsigned char *)message, strlen(message), sig, &sig_len)) != 0)
    {
        printf("Failed to sign data: -0x%04x\n", -ret);
        mbedtls_pk_free(&pk);
        return 1;
    }

    printf("Signature: %s\n", sig);

    // 验证签名
    if ((ret = verify_signature(&pk, (const unsigned char *)message, strlen(message), sig, sig_len)) == 0)
    {
        printf("Signature verified successfully\n");
    }
    else
    {
        printf("Signature verification failed: -0x%04x\n", -ret);
    }

    // 释放资源
    mbedtls_pk_free(&pk);

    return 0;
}
