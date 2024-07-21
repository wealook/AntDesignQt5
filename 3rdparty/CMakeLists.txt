 option(SPDLOG_BUILD_EXAMPLE "" OFF)
 option(SPDLOG_INSTALL "" OFF)
 add_subdirectory(spdlog)
 set_target_properties(spdlog PROPERTIES FOLDER ${third_party_folder}/spdlog)

