find_package(Protobuf REQUIRED)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ../proto/transition.proto)

add_executable(server
               main.cpp
               ${PROTO_SRCS}
               ${PROTO_HDRS}
               Server.cpp
               Session.cpp
               ../common/User.cpp
               ../messages/UserInitMessage.cpp
               ../messages/SessionCreatedMessage.cpp
               GameObject.cpp
               Player.cpp
               ../messages/UserToServerMessage.cpp
               ../messages/ServerToUserMessage.cpp
               Enemy.h
               Enemy.cpp
               Wall.h
               Wall.cpp
               Collision.cpp
               Collision.h
               Bullet.cpp
               Bullet.h
               Spike.cpp
               Spike.h
               Lava.cpp
               Lava.h)


target_include_directories(server
        PUBLIC
        ${PROTOBUF_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(server PUBLIC ${PROTOBUF_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
