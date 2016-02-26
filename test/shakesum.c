/**
 * @cond internal
 * @file shakesum.c
 * @copyright
 *   Copyright (c) 2015 Cryptography Research, Inc.  \n
 *   Released under the MIT License.  See LICENSE.txt for license information.
 * @author Mike Hamburg
 * @brief SHA3 utility, to be combined with test vectors eventually...
 */

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <decaf/shake.h>
#include <decaf/sha512.h>

static void usage() {
    fprintf(
        stderr,
        "shakesum [shake256|shake128|sha3-224|sha3-384|sha3-512|sha512] < infile > outfile\n"
    );
}

int main(int argc, char **argv) {
    (void)argc; (void)argv;

    keccak_sponge_t sponge;
    sha512_ctx_t sha512;
    unsigned char buf[1024];
    
    unsigned int outlen = 512;
    shake256_gen_init(sponge);
    
    int use_sha512 = 0;

    /* Sloppy.  Real utility would parse --algo, --size ... */
    if (argc > 1) {
        if (!strcmp(argv[1], "shake256") || !strcmp(argv[1], "SHAKE256")) {
            outlen = 512;
            shake256_gen_init(sponge);
        } else if (!strcmp(argv[1], "shake128") || !strcmp(argv[1], "SHAKE128")) {
            outlen = 512;
            shake128_gen_init(sponge);
        } else if (!strcmp(argv[1], "sha3-224") || !strcmp(argv[1], "SHA3-224")) {
            outlen = 224/8;
            sha3_224_gen_init(sponge);
        } else if (!strcmp(argv[1], "sha3-256") || !strcmp(argv[1], "SHA3-256")) {
            outlen = 256/8;
            sha3_256_gen_init(sponge);
        } else if (!strcmp(argv[1], "sha3-384") || !strcmp(argv[1], "SHA3-384")) {
            outlen = 384/8;
            sha3_384_gen_init(sponge);
        } else if (!strcmp(argv[1], "sha3-512") || !strcmp(argv[1], "SHA3-512")) {
            outlen = 512/8;
            sha3_512_gen_init(sponge);
        } else if (!strcmp(argv[1], "sha512") || !strcmp(argv[1], "SHA512")) {
            outlen = 512/8;
            use_sha512 = 1;
            sha512_init(sha512);
        } else {
            usage();
            return 2;
        }
    }

    ssize_t red;
    do {
        red = read(0, buf, sizeof(buf));
        if (red>0) {
            if (use_sha512) sha512_update(sha512,buf,red);
            else sha3_update(sponge,buf,red);
        }
    } while (red>0);

    if (use_sha512) {
        sha512_final(sha512,buf,outlen);
        sha512_destroy(sha512);
    } else {
        sha3_output(sponge,buf,outlen);
        sponge_destroy(sponge);
    }
    unsigned i;
    for (i=0; i<outlen; i++) {
        printf("%02x", buf[i]);
    }
    printf("\n");

    return 0;
}
