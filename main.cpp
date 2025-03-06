#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

#include "game.h"
#include "menu.h"

using namespace sf;
using namespace std;


int main() {
    RenderWindow window(VideoMode(400, 400), "Fifteen Puzzle");
    
    bool gameIsRunning = false;

    Font font;

    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return -1;
    }

    Event event;

    // Основний цикл
    while (window.isOpen()) {
        // Обробка подій
        // window.pollEvent(event) — функція, яка витягує події з черги подій, що виникли у вікні. 
        // Вона повертає true, якщо є нові події.
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
  
            // У C++ :: (двокрапка з подвійним знаком) використовується для доступу до елементів простору імен (namespace), класів або структур.
            // MouseButtonPressed — це один із членів класу Event, який вказує, що була натиснута кнопка миші.

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int mouseX = event.mouseButton.x;
                int mouseY = event.mouseButton.y;

                if (startGame(mouseX, mouseY)) {
                    gameIsRunning = true;
                }
                else if (exitGame(mouseX, mouseY)) {
                    window.close();
                    
                }
            }
        }

        showMainMenu(window, font);
        window.display();

        if (gameIsRunning) {
            window.close();  // Закриваємо меню перед відкриттям гри
            game();          // Запускаємо гру
        }
    }

    return 0;
}