project(ShootingShuttle CXX)
set(SHUTTLE "Shooting shuttle")

add_executable(${SHUTTLE} main.cpp
    Game.cpp
    Game.hpp
    entities/Ship.hpp
    entities/Enemy.hpp
    entities/Bullet.hpp
    entities/Button.hpp
    utils/Level.hpp
    entities/BulletGenerator.hpp
    utils/Lobby.hpp

    entities/Enemy.cpp
    entities/Bullet.cpp
    entities/Ship.cpp
    entities/Button.cpp
    utils/Level.cpp
    entities/BulletGenerator.cpp
    utils/Lobby.cpp
)
target_link_libraries(${SHUTTLE}
    PRIVATE ${LIBNAME}md
)