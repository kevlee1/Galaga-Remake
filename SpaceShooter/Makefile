main:
	g++ main.cpp Api.cpp Coordinate.cpp BasicAlien.cpp StrongerAlien.cpp RapidFireAlien.cpp BossAlien.cpp View.cpp GameModel.cpp Level.cpp Collidable.cpp Player.cpp Missile.cpp Upgrade.cpp  Enemy.cpp -I./Frameworks/SDL2.framework/Headers -I./Frameworks/SDL2_image.framework/Headers -I./Frameworks/SDL2_ttf.framework/Headers -I./Frameworks/SDL2_mixer.framework/Headers -framework SDL2 -framework SDL2_image -framework SDL2_mixer -framework SDL2_ttf -F./Frameworks -std=c++11 -lcurlpp -lcurl -o game.out -rpath @executable_path/Frameworks 	

clean:
	rm sdl.out a.out

all:
	main
