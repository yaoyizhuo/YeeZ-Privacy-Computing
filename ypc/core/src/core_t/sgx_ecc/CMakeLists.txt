add_trusted_library(sgx_gmssl_ecc_t
  sgx_gmssl_ecc_t
  SRCS gmssl_ecc_impl.cpp
  EDL ../../../edl/ecc.edl
  EDL_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ypc/stbox/src/)
target_link_libraries(sgx_gmssl_ecc_t stbox_crypto_t)
#install(TARGETS sgx_ecc_t DESTINATION lib COMPONENT c_ypc_core OPTIONAL)

add_trusted_library(sgx_eth_ecc_t
  sgx_eth_ecc_t
  SRCS stdeth_ecc_impl.cpp
  EDL ../../../edl/ecc.edl
  EDL_SEARCH_PATHS ${PROJECT_SOURCE_DIR}/ypc/stbox/src/)
target_link_libraries(sgx_eth_ecc_t stbox_crypto_t)

