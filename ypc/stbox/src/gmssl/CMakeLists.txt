include_directories(${PROJECT_SOURCE_DIR}/ypc/stbox/include/ypc/stbox/)

set(gmssl_src
	sha256.c
	sm3.c
	asn1.c
	sm2_alg.c
	sm2_key.c
	sm2_lib.c
	sm4_common.c
	sm4_setkey.c
	sm4_enc.c
	aes.c
	aes_modes.c
	hex.c
	gf128.c
	gcm.c
	sm4_modes.c
	block_cipher.c
  )

add_library(gmssl
  SHARED
  ${gmssl_src}
  )
target_link_libraries(gmssl dl)

add_sgx_library(stbox_gmssl_t
  stbox_gmssl_t
  SRCS "${gmssl_src}")

