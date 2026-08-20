CXX = g++

CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

RAYLIB_PATH = /home/uservranger/raylib

INCLUDES = -I$(RAYLIB_PATH)/src

LIBS = $(RAYLIB_PATH)/build/raylib/libraylib.a \
	-lGL -lm -lpthread -ldl -lrt -lX11

TARGET = 31-16

SRC = src/main.cpp \
	src/GameFonts.cpp \
	src/GameText.cpp \
	src/HealthBar.cpp \
	src/PlayerProgress.cpp \
	src/ExperienceBar.cpp \
	src/GameAudio.cpp \
	src/Entity.cpp \
	src/Actor.cpp \
	src/Player.cpp \
	src/Enemy.cpp \
	src/EnemySpawner.cpp \
	src/WaveManager.cpp \
	src/Collision.cpp \
	src/EnemySeparation.cpp \
	src/Projectile.cpp \
	src/ProjectileManager.cpp \
	src/Weapon.cpp \
	src/ProjectileWeapon.cpp \
	src/BasicGunWeapon.cpp \
	src/BoomerangWeapon.cpp \
	src/BulletProjectile.cpp \
	src/BoomerangProjectile.cpp \
	src/MeleeAttack.cpp \
	src/MeleeManager.cpp \
	src/MeleeWeapon.cpp \
	src/SwordWeapon.cpp \
	src/SwordAttack.cpp \
	src/BeamWeapon.cpp \
	src/BeamAttack.cpp \
	src/AuraWeapon.cpp \
	src/AuraAttack.cpp \
	src/XPOrb.cpp \
	src/XPManager.cpp \
	src/LevelUpMenu.cpp \
	src/WeaponDraw.cpp \

all:
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(SRC) $(LIBS) -o $(TARGET)

clean:
	rm -f $(TARGET)

fclean: clean

re: fclean all

.PHONY: all clean fclean re