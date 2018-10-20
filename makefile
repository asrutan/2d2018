kawaii: game.o main.o hud.o movement.o player.o enemy.o world.o display.o texture.o textTexture.o tile.o camFocus.o collision.o collideBox.o entity.o background.o trackerEnemy.o
	g++ game.o main.o hud.o movement.o player.o enemy.o world.o display.o texture.o textTexture.o tile.o camFocus.o collision.o collideBox.o entity.o background.o trackerEnemy.o -w -lSDL2 -lSDL2_image -lSDL2_ttf -fstack-protector -o kawaii
main.o: main.cpp game.h
	g++ -c main.cpp
display.o: display.cpp display.h 
	g++ -c display.cpp
game.o: game.cpp game.h hud.h movement.h player.h enemy.h display.h texture.h textTexture.h tile.h world.h camFocus.h collision.h background.h trackerEnemy.h entity.h
	g++ -c game.cpp
hud.o: hud.cpp hud.h
	g++ -c hud.cpp
movement.o: movement.cpp movement.h
	g++ -c movement.cpp
entity.o: entity.cpp entity.h
	g++ -c entity.cpp
player.o: player.cpp player.h collision.h collideBox.h entity.h
	g++ -c player.cpp
enemy.o: enemy.cpp enemy.h collision.h collideBox.h entity.h
	g++ -c enemy.cpp
trackerEnemy.o: trackerEnemy.cpp trackerEnemy.h enemy.h collideBox.h entity.h
	g++ -c trackerEnemy.cpp
world.o: world.cpp world.h tile.h
	g++ -c world.cpp
texture.o: texture.cpp texture.h display.h
	g++ -c texture.cpp
textTexture.o: textTexture.cpp textTexture.h display.h
	g++ -c textTexture.cpp
tile.o: tile.cpp tile.h display.h texture.h collideBox.h
	g++ -c tile.cpp
camFocus.o: camFocus.cpp camFocus.h player.h enemy.h world.h
	g++ -c camFocus.cpp
collision.o: collision.cpp collision.h world.h player.h enemy.h collideBox.h entity.h
	g++ -c collision.cpp
collideBox.o: collideBox.cpp collideBox.h
	g++ -c collideBox.cpp
background.o: background.cpp background.h
	g++ -c background.cpp

clean:
	rm -f *.o
	rm kawaii
