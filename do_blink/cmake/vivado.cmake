function(GEN_DEF_JSON_VIVADO)
  set(options)
  set(oneValueArgs NAME DCP USE_VIVADO_PPLOCS)
  set(multiValueArgs)
  cmake_parse_arguments(
      GEN_DEF_JSON_VIVADO
    "${options}"
    "${oneValueArgs}"
    "${multiValueArgs}"
    ${ARGN}
  )
  set(DCP ${GEN_DEF_JSON_VIVADO_DCP})
  set(USE_VIVADO_PPLOCS ${GEN_DEF_JSON_VIVADO_USE_VIVADO_PPLOCS})
  set(GEN_VPR_NODES_TCL ${doblink_SOURCE_DIR}/do_blink/tcl/gen_vpr_nodes.tcl)
  if(NOT (DEFINED ENV{DOBLINK_VIVADO_SETTINGS}))
      message(FATAL_ERROR "Please define DOBLINK_VIVADO_SETTINGS to vivado's settings64.sh.")
  endif()

  add_custom_command(
    OUTPUT definition.json
    COMMAND ${doblink_SOURCE_DIR}/do_blink/utils/vivado.sh -mode batch -source
        ${GEN_VPR_NODES_TCL} -tclargs ${DCP} ${USE_VIVADO_PPLOCS}
        > ${CMAKE_CURRENT_BINARY_DIR}/vivado.stdout.log
    WORKING_DIRECTORY ${WORK_DIR}
    DEPENDS ${GEN_VPR_NODES_TCL}
    )
  add_file_target(FILE definition.json GENERATED)
endfunction()