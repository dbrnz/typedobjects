include("${CMAKE_CURRENT_LIST_DIR}/typedobjectTargets.cmake")

GET_FILENAME_COMPONENT (SELF_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${SELF_DIR}" PATH)
if (NOT WIN32)
  GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)
endif (NOT WIN32)

set(typedobject_INCLUDE_DIR "${_IMPORT_PREFIX}/include")
set(typedobject_LIBRARY_DIRS "${_IMPORT_PREFIX}/lib")

