/* LibTomCrypt, modular cryptographic library -- Tom St Denis
 *
 * LibTomCrypt is a library that provides various cryptographic
 * algorithms in a highly modular and flexible manner.
 *
 * The library is free for all purposes without any express
 * guarantee it works.
 *
 * Tom St Denis, tomstdenis@gmail.com, http://libtomcrypt.org
 */

/**
   @file gcm_test.c
   GCM implementation, testing, by Tom St Denis
*/
#include "tomcrypt.h"

#ifdef GCM_MODE

/** 
  Test the GCM code
  @return CRYPT_OK on success
 */
int gcm_test(void)
{
   static const struct {
       unsigned char K[32];
       int           keylen;
       unsigned char P[64];
       unsigned long ptlen;
		 unsigned char A[64];
       unsigned long alen;
       unsigned char IV[64];
       unsigned long IVlen;
       unsigned char C[64];
       unsigned char T[16];
   } tests[] = {

/* test case #1 */
{
  /* key */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  16,

  /* plaintext */
  { 0 },
  0,

  /* AAD data */
  { 0 },
  0,

  /* IV */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00 },
  12,

  /* ciphertext  */
  { 0 },

  /* tag */
  { 0x58, 0xe2, 0xfc, 0xce, 0xfa, 0x7e, 0x30, 0x61,
    0x36, 0x7f, 0x1d, 0x57, 0xa4, 0xe7, 0x45, 0x5a }
},

/* test case #2 */
{
  /* key */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  16,

  /* PT */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 },
  16,

  /* ADATA */
  { 0 },
  0,

  /* IV */
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00 },
  12,

  /* CT */
  { 0x03, 0x88, 0xda, 0xce, 0x60, 0xb6, 0xa3, 0x92,
    0xf3, 0x28, 0xc2, 0xb9, 0x71, 0xb2, 0xfe, 0x78 },

  /* TAG */
  { 0xab, 0x6e, 0x47, 0xd4, 0x2c, 0xec, 0x13, 0xbd,
    0xf5, 0x3a, 0x67, 0xb2, 0x12, 0x57, 0xbd, 0xdf }
},

/* test case #3 */
{
   /* key */
   { 0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 
     0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08, },
   16,

   /* PT */
   { 0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 
     0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a, 
     0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 
     0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72, 
     0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 
     0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25, 
     0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 
     0xba, 0x63, 0x7b, 0x39, 0x1a, 0xaf, 0xd2, 0x55, },
  64,

  /* ADATA */
  { 0 },
  0,

  /* IV */
  { 0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad, 
    0xde, 0xca, 0xf8, 0x88,  },
  12,
 
  /* CT */
  { 0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24, 
    0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c, 
    0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0, 
    0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e, 
    0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c, 
    0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05, 
    0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97, 
    0x3d, 0x58, 0xe0, 0x91, 0x47, 0x3f, 0x59, 0x85, },

  /* TAG */
  { 0x4d, 0x5c, 0x2a, 0xf3, 0x27, 0xcd, 0x64, 0xa6, 
    0x2c, 0xf3, 0x5a, 0xbd, 0x2b, 0xa6, 0xfa, 0xb4, }
},

/* test case #4 */
{
   /* key */
   { 0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 
     0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08, },
   16,

   /* PT */
   { 0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 
     0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a, 
     0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 
     0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72, 
     0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 
     0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25, 
     0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 
     0xba, 0x63, 0x7b, 0x39,  },
   60,

   /* ADATA */
   { 0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 
     0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 
     0xab, 0xad, 0xda, 0xd2,  },
   20,

   /* IV */
   { 0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad, 
     0xde, 0xca, 0xf8, 0x88,  },
   12,

   /* CT */
   { 0x42, 0x83, 0x1e, 0xc2, 0x21, 0x77, 0x74, 0x24, 
     0x4b, 0x72, 0x21, 0xb7, 0x84, 0xd0, 0xd4, 0x9c, 
     0xe3, 0xaa, 0x21, 0x2f, 0x2c, 0x02, 0xa4, 0xe0, 
     0x35, 0xc1, 0x7e, 0x23, 0x29, 0xac, 0xa1, 0x2e, 
     0x21, 0xd5, 0x14, 0xb2, 0x54, 0x66, 0x93, 0x1c, 
     0x7d, 0x8f, 0x6a, 0x5a, 0xac, 0x84, 0xaa, 0x05, 
     0x1b, 0xa3, 0x0b, 0x39, 0x6a, 0x0a, 0xac, 0x97, 
     0x3d, 0x58, 0xe0, 0x91,  },

   /* TAG */
   { 0x5b, 0xc9, 0x4f, 0xbc, 0x32, 0x21, 0xa5, 0xdb, 
     0x94, 0xfa, 0xe9, 0x5a, 0xe7, 0x12, 0x1a, 0x47, }

},

/* test case #5 */
{
   /* key */
   { 0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 
     0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08, },
   16,

   /* PT */
   { 0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 
     0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a, 
     0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 
     0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72, 
     0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 
     0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25, 
     0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 
     0xba, 0x63, 0x7b, 0x39,  },
   60,

   /* ADATA */
   { 0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 
     0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 
     0xab, 0xad, 0xda, 0xd2,  },
   20,

   /* IV */
   { 0xca, 0xfe, 0xba, 0xbe, 0xfa, 0xce, 0xdb, 0xad, },
   8,

   /* CT */
   { 0x61, 0x35, 0x3b, 0x4c, 0x28, 0x06, 0x93, 0x4a, 
     0x77, 0x7f, 0xf5, 0x1f, 0xa2, 0x2a, 0x47, 0x55, 
     0x69, 0x9b, 0x2a, 0x71, 0x4f, 0xcd, 0xc6, 0xf8, 
     0x37, 0x66, 0xe5, 0xf9, 0x7b, 0x6c, 0x74, 0x23, 
     0x73, 0x80, 0x69, 0x00, 0xe4, 0x9f, 0x24, 0xb2, 
     0x2b, 0x09, 0x75, 0x44, 0xd4, 0x89, 0x6b, 0x42, 
     0x49, 0x89, 0xb5, 0xe1, 0xeb, 0xac, 0x0f, 0x07, 
     0xc2, 0x3f, 0x45, 0x98,  },

   /* TAG */
   { 0x36, 0x12, 0xd2, 0xe7, 0x9e, 0x3b, 0x07, 0x85, 
     0x56, 0x1b, 0xe1, 0x4a, 0xac, 0xa2, 0xfc, 0xcb, }
},

/* test case #6 */
{
   /* key */
   { 0xfe, 0xff, 0xe9, 0x92, 0x86, 0x65, 0x73, 0x1c, 
     0x6d, 0x6a, 0x8f, 0x94, 0x67, 0x30, 0x83, 0x08, },
   16,

   /* PT */
   { 0xd9, 0x31, 0x32, 0x25, 0xf8, 0x84, 0x06, 0xe5, 
     0xa5, 0x59, 0x09, 0xc5, 0xaf, 0xf5, 0x26, 0x9a, 
     0x86, 0xa7, 0xa9, 0x53, 0x15, 0x34, 0xf7, 0xda, 
     0x2e, 0x4c, 0x30, 0x3d, 0x8a, 0x31, 0x8a, 0x72, 
     0x1c, 0x3c, 0x0c, 0x95, 0x95, 0x68, 0x09, 0x53, 
     0x2f, 0xcf, 0x0e, 0x24, 0x49, 0xa6, 0xb5, 0x25, 
     0xb1, 0x6a, 0xed, 0xf5, 0xaa, 0x0d, 0xe6, 0x57, 
     0xba, 0x63, 0x7b, 0x39,  },
   60,

   /* ADATA */
   { 0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 
     0xfe, 0xed, 0xfa, 0xce, 0xde, 0xad, 0xbe, 0xef, 
     0xab, 0xad, 0xda, 0xd2,  },
   20,

   /* IV */
   { 0x93, 0x13, 0x22, 0x5d, 0xf8, 0x84, 0x06, 0xe5, 
     0x55, 0x90, 0x9c, 0x5a, 0xff, 0x52, 0x69, 0xaa, 
     0x6a, 0x7a, 0x95, 0x38, 0x53, 0x4f, 0x7d, 0xa1, 
     0xe4, 0xc3, 0x03, 0xd2, 0xa3, 0x18, 0xa7, 0x28, 
     0xc3, 0xc0, 0xc9, 0x51, 0x56, 0x80, 0x95, 0x39, 
     0xfc, 0xf0, 0xe2, 0x42, 0x9a, 0x6b, 0x52, 0x54, 
     0x16, 0xae, 0xdb, 0xf5, 0xa0, 0xde, 0x6a, 0x57, 
     0xa6, 0x37, 0xb3, 0x9b,  },
   60,

   /* CT */
   { 0x8c, 0xe2, 0x49, 0x98, 0x62, 0x56, 0x15, 0xb6, 
     0x03, 0xa0, 0x33, 0xac, 0xa1, 0x3f, 0xb8, 0x94, 
     0xbe, 0x91, 0x12, 0xa5, 0xc3, 0xa2, 0x11, 0xa8, 
     0xba, 0x26, 0x2a, 0x3c, 0xca, 0x7e, 0x2c, 0xa7, 
     0x01, 0xe4, 0xa9, 0xa4, 0xfb, 0xa4, 0x3c, 0x90, 
     0xcc, 0xdc, 0xb2, 0x81, 0xd4, 0x8c, 0x7c, 0x6f, 
     0xd6, 0x28, 0x75, 0xd2, 0xac, 0xa4, 0x17, 0x03, 
     0x4c, 0x34, 0xae, 0xe5,  },

   /* TAG */
   { 0x61, 0x9c, 0xc5, 0xae, 0xff, 0xfe, 0x0b, 0xfa, 
     0x46, 0x2a, 0xf4, 0x3c, 0x16, 0x99, 0xd0, 0x50, }
}

/* rest of test cases are the same except AES key size changes... ignored... */
};
   int           idx, err;
   unsigned long x, y;
   gcm_state     gcm;
   unsigned char out[2][64], T[2][16];

   /* find aes */
   idx = find_cipher("aes");
   if (idx == -1) {
      idx = find_cipher("rijndael");
      if (idx == -1) {
         return CRYPT_NOP;
      }
   }

   for (x = 0; x < (int)(sizeof(tests)/sizeof(tests[0])); x++) {
       y = sizeof(T[0]);
       if ((err = gcm_memory(idx, tests[x].K, tests[x].keylen,
                             tests[x].IV, tests[x].IVlen,
                             tests[x].A, tests[x].alen,
                             (unsigned char*)tests[x].P, tests[x].ptlen,
                             out[0], T[0], &y, GCM_ENCRYPT)) != CRYPT_OK) {
          return err;
       }

       if (memcmp(out[0], tests[x].C, tests[x].ptlen)) {
#if 0
          printf("\nCiphertext wrong %lu\n", x);
          for (y = 0; y < tests[x].ptlen; y++) {
              printf("%02x", out[0][y] & 255);
          }
          printf("\n");
#endif
          return CRYPT_FAIL_TESTVECTOR;
       }

       if (memcmp(T[0], tests[x].T, 16)) {
#if 0
          printf("\nTag on plaintext wrong %lu\n", x);
          for (y = 0; y < 16; y++) {
              printf("%02x", T[0][y] & 255);
          }
          printf("\n");
#endif
          return CRYPT_FAIL_TESTVECTOR;
       }

       y = sizeof(T[1]);
       if ((err = gcm_memory(idx, tests[x].K, tests[x].keylen,
                             tests[x].IV, tests[x].IVlen,
                             tests[x].A, tests[x].alen,
                             out[1], tests[x].ptlen,
                             out[0], T[1], &y, GCM_DECRYPT)) != CRYPT_OK) {
          return err;
       }

       if (memcmp(out[1], tests[x].P, tests[x].ptlen)) {
#if 0
          printf("\nplaintext wrong %lu\n", x);
          for (y = 0; y < tests[x].ptlen; y++) {
              printf("%02x", out[0][y] & 255);
          }
          printf("\n");
#endif
          return CRYPT_FAIL_TESTVECTOR;
       }

       if (memcmp(T[1], tests[x].T, 16)) {
#if 0
          printf("\nTag on ciphertext wrong %lu\n", x);
          for (y = 0; y < 16; y++) {
              printf("%02x", T[1][y] & 255);
          }
          printf("\n");
#endif
          return CRYPT_FAIL_TESTVECTOR;
       }

   }
   return CRYPT_OK;
}

#endif

