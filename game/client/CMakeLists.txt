find_package(Protobuf REQUIRED)
PROTOBUF_GENERATE_CPP(PROTO_SRCS PROTO_HDRS ../proto/transition.proto)

add_executable(client main.cpp ${PROTO_SRCS} ${PROTO_HDRS} Client.cpp ../common/User.cpp Player.cpp Object.cpp ../messages/SessionCreatedMessage.cpp
        ../messages/UserInitMessage.cpp ../messages/UserToServerMessage.cpp ../messages/ServerToUserMessage.cpp

        tinyxml2.cpp tinyxml2.h TmxLevel.cpp TmxLevel.h Skin.cpp Skin.h View.cpp View.h Enemy.cpp Enemy.h Bullet.h Bullet.cpp Menus.cpp Menus.h)


target_include_directories(client
        PUBLIC
        ${PROTOBUF_INCLUDE_DIRS}
        ${CMAKE_CURRENT_BINARY_DIR}
        )

target_link_libraries(client PUBLIC ${PROTOBUF_LIBRARIES} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
