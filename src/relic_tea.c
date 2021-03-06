#include "relic_tea.h"
#include "relic_tea_core.h"
#include <string.h>

// encrypt and decrypt functions perform the TEA block cipher
// and are found in relic_tea_core.c
// This provides an interface for CBC and CBC-MAC mode en/decryption.

static Crypto _relic_tea_interface;

// De/encryption mode functions

void _CBC_ENCRYPT_BASE_MODE (uint32_t * msgIn, 
			     uint16_t len, 
			     uint32_t * IV, 
			     uint32_t * k, 
			     uint32_t * msgOut, 
			     uint32_t * MAC) {
  /* 
     Input: msgIn: input message in unsigned 32-bit blocks,
     len : length of message in unsigned 32-bit blocks,
     IV  : initialization vector, should be an array of 2 uint32_t,
     k   : 128-bit key as an array of 4 uint32_t,
     Output: msgOut: taken as input and written to a waiting memory location,
     will usually be the same as msgIn to encrypt in-place.
     Needs to be len + (len % 2)
  */
  uint32_t * chain = IV;
  uint32_t blockBuffer[2];
  uint16_t i;
  uint16_t numBlocks = (len - (len % 2)) / 2;
  
  for (i = 0; i < numBlocks; i++) {
    blockBuffer[0] = *msgIn ^ *chain;
    blockBuffer[1] = *msgIn ^ *(chain+1);
    encrypt(blockBuffer, k);
    
    *msgOut = blockBuffer[0];
    *(msgOut+1) = blockBuffer[1];
    chain = msgOut;
    
    msgIn += 2;
    msgOut += 2;
  }
  
  if (len % 2 == 1) {
    blockBuffer[0] = *msgIn ^ *chain;
    blockBuffer[1] = 0x00000000 ^ *(chain+1);
    encrypt(blockBuffer, k);
    
    *msgOut = blockBuffer[0];
    *(msgOut+1) = blockBuffer[1];
    
    if (MAC != NULL) {
      *MAC = *msgOut;
      *(MAC+1) = *(msgOut+1);
    }
  } else if (MAC != NULL) {
    *MAC = *(msgOut - 2);
    *(MAC+1) = *(msgOut -1);
  }
}

void _CBC_DECRYPT_BASE_MODE (uint32_t * msgIn, 
			     uint16_t len, 
			     uint32_t * IV, 
			     uint32_t * k,
			     uint32_t * msgOut) {
  uint32_t * chain = IV;
  uint32_t blockBuffer[2];
  uint16_t i;
  uint16_t numBlocks = len / 2;
  
  for (i = 0; i < numBlocks; i++){
    blockBuffer[0] = *msgIn;
    blockBuffer[1] = *(msgIn+1);
    decrypt(blockBuffer, k);
    
    *msgOut	= blockBuffer[0] ^ *chain;
    *(msgOut+1) = blockBuffer[1] ^ *(chain+1);
    
    msgIn += 2;
    msgOut += 2;
  }
}

// Interface and set-up functions

void _CBC_Encypt () {
  uint32_t IV[2];
  IV[0] = _relic_tea_interface.rng() << 24 |
    _relic_tea_interface.rng() << 16 |
    _relic_tea_interface.rng() << 8  |
    _relic_tea_interface.rng();
  IV[1] = _relic_tea_interface.rng() << 24 |
    _relic_tea_interface.rng() << 16 |
    _relic_tea_interface.rng() << 8 |
    _relic_tea_interface.rng();
  _CBC_ENCRYPT_BASE_MODE((uint32_t *)_relic_tea_interface.MessageBuffer, 
			 ENCRYPTION_MESSAGE_BUFFER_SIZE/4, 
			 IV, 
			 _relic_tea_interface.key,
			 (uint32_t *)_relic_tea_interface.MessageBuffer,
			 NULL);
}

void _CBC_Decrypt (uint32_t * ct, uint16_t len, uint32_t * IV) {
  uint16_t copyLen = len <= ENCRYPTION_MESSAGE_BUFFER_SIZE ? 
    len : ENCRYPTION_MESSAGE_BUFFER_SIZE;
  memcpy(_relic_tea_interface.MessageBuffer, ct, copyLen);
  _CBC_DECRYPT_BASE_MODE ((uint32_t *)_relic_tea_interface.MessageBuffer, 
			  len,
			  IV, 
			  _relic_tea_interface.key, 
			  (uint32_t *)_relic_tea_interface.MessageBuffer);
}

void _CBC_MAC (uint32_t * msg, uint16_t len) {
  uint32_t IV[2] = {0x00000000, 0x00000000};
  _CBC_ENCRYPT_BASE_MODE((uint32_t *)_relic_tea_interface.MessageBuffer, 
			 len, 
			 IV, 
			 _relic_tea_interface.MACKey,
			 (uint32_t *)_relic_tea_interface.MessageBuffer,
			 (uint32_t *)_relic_tea_interface.MACBuffer);
}

void _Crypto_SetNewKey(uint32_t * newKey) {
  _relic_tea_interface.key[0] = *newKey;
  _relic_tea_interface.key[1] = *(newKey+1);
  _relic_tea_interface.key[2] = *(newKey+2);
  _relic_tea_interface.key[3] = *(newKey+3);
}

void _Crypto_SetMACKey(uint32_t * newMACKey) {
  _relic_tea_interface.MACKey[0] = *newMACKey;
  _relic_tea_interface.MACKey[1] = *(newMACKey+1);
  _relic_tea_interface.MACKey[2] = *(newMACKey+2);
  _relic_tea_interface.MACKey[3] = *(newMACKey+3);
}

Crypto * initCrypto(RNG rng, uint32_t * key) {
  _relic_tea_interface.rng = rng;
  _relic_tea_interface.encrypt = &_CBC_Encypt;
  _relic_tea_interface.decrypt = &_CBC_Decrypt;
  _relic_tea_interface.MAC = &_CBC_MAC;
  _relic_tea_interface.setKey = &_Crypto_SetNewKey;
  _relic_tea_interface.setMACKey = &_Crypto_SetMACKey;
  _relic_tea_interface.setKey(key);
  
  return &_relic_tea_interface;
}

