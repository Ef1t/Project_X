add_executable(client main.cpp Client.cpp ../common/User.cpp Player.cpp Object.cpp ../messages/SessionCreatedMessage.cpp
        ../messages/UserInitMessage.cpp ../messages/UserToServerMessage.cpp ../messages/ServerToUserMessage.cpp
        tinyxml2.cpp tinyxml2.h TmxLevel.cpp TmxLevel.h)

target_link_libraries(client ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
