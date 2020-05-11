find_package(Protobuf REQUIRED)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ../proto/transition.proto)

add_executable(client main.cpp ${PROTO_SRCS} ${PROTO_HDRS} Client.cpp ../common/User.cpp Player.cpp Object.cpp ../messages/SessionCreatedMessage.cpp
        ../messages/UserInitMessage.cpp ../messages/UserToServerMessage.cpp ../messages/ServerToUserMessage.cpp)

target_include_directories(client
        PUBLIC
        ${PROTOBUF_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(client ${PROTOBUF_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
