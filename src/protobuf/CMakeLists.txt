project(protobuf)
cmake_minimum_required(VERSION 3.6)

set(EMBEDDED_PROTO_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/../../EmbeddedProto/src")
message("${EMBEDDED_PROTO_SOURCE}")
list(APPEND ${PROJECT_NAME}_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/ProtoReadBuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/ProtoWriteBuffer.cpp"
    "${EMBEDDED_PROTO_SOURCE}/Fields.cpp"
    "${EMBEDDED_PROTO_SOURCE}/MessageInterface.cpp"
    "${EMBEDDED_PROTO_SOURCE}/ReadBufferSection.cpp"
)

add_library(${PROJECT_NAME} OBJECT EXCLUDE_FROM_ALL ${${PROJECT_NAME}_SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC ${EMBEDDED_PROTO_SOURCE})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
