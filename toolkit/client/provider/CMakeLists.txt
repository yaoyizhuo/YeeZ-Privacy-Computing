add_executable(provider_tools
  main.cpp)
target_link_libraries(provider_tools ypc_core stbox_common_u keymgr_module ypc_stdeth_u)
install(TARGETS provider_tools DESTINATION bin)

