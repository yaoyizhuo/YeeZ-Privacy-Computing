
set(T_SRCS ${PROJECT_SOURCE_DIR}/ypc/keymgr/default/gmssl/ekeymgr.cpp
  ${PROJECT_SOURCE_DIR}/ypc/core/src/core_t/ecommon/signer_verify.cpp
  ${PROJECT_SOURCE_DIR}/ypc/core/src/core_t/ecommon/package.cpp
  ${FF_SRC_PATH}/net/common/archive.cpp
  )

set(edl_path ${PROJECT_SOURCE_DIR}/ypc/core/edl/:${PROJECT_SOURCE_DIR}/ypc/stbox/src)

add_enclave_library(keymgr_gmssl
  SRCS ${T_SRCS}
  EDL ../enclave/ekeymgr.edl
  EDL_SEARCH_PATHS "${edl_path}")

target_link_libraries(keymgr_gmssl stbox_common_t stbox_channel_t stbox_crypto_t sgx_gmssl_ecc_t ypc_gmssl_t dl)

enclave_sign(keymgr_gmssl KEY ${PROJECT_SOURCE_DIR}/ypc/keymgr/default/enclave/ekeymgr_private.pem
  CONFIG ${PROJECT_SOURCE_DIR}/ypc/keymgr/default/enclave/ekeymgr.config.xml)
install(FILES ${PROJECT_SOURCE_DIR}/lib/keymgr_gmssl.signed.so DESTINATION lib COMPONENT c_keymgr OPTIONAL)
