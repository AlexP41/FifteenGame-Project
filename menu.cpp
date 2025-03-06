#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>


#include "game.h"
#include "menu.h"

using namespace sf;
using namespace std;


const int SIZE = 4; // Розмір поля 4x4
const int TILE_SIZE = 100; // Розмір кожної плитки
const int WINDOW_SIZE = TILE_SIZE * SIZE; // Розмір вікна




double extractBestTime(double bestTime, double defaultValueOfBestTime) {

    ifstream file("the-best-time.txt", ios::in);
    if (!file)
    {
        cout << "File has not been found." << endl;
        return defaultValueOfBestTime;
    }

    string current_line;

    while (getline(file, current_line))
    {
        try
        {
            bestTime = stod(current_line); // Використовуємо stod для перетворення рядка в double
            break;
        }
        catch (const exception&)
        {
            continue;
        }
    }
    file.close();

    // якщо початкоового значення не отримано
    if (bestTime == defaultValueOfBestTime)
    {
        bestTime = numeric_limits<double>::max();
    }




    return bestTime;
}




void showMainMenu(RenderWindow& window, Font& font) {
    // Заголовок меню
    Text title("Fifteen Puzzle", font, 50);
    title.setFillColor(Color::White);
    title.setPosition(50, 100);

    // Кнопка для старту гри
    Text playButton("Start Game", font, 30);
    playButton.setFillColor(Color::Green);
    playButton.setPosition(100, 200);

    // Кнопка для виходу
    Text exitButton("Exit", font, 30);
    exitButton.setFillColor(Color::Red);
    exitButton.setPosition(100, 300);

    // Найкращій результат
    double bestTime = -1;
    bestTime = extractBestTime(bestTime, -1);



    // Конвертуємо у години, хвилини та секунди
    int hours = static_cast<int>(bestTime) / 3600; // Цілі години
    int minutes = (static_cast<int>(bestTime) % 3600) / 60; // Цілі хвилини
    int seconds = static_cast<int>(bestTime) % 60; // Залишок — секунди

    // Форматування тексту
    string bestTimeText;
    if (bestTime == numeric_limits<double>::max()) {
        bestTimeText = "Best result: 0 hr 0 min 0 sec";
    }
    else {
        bestTimeText = "Best result: " + to_string(hours) + " hr " +
            to_string(minutes) + " min " +
            to_string(seconds) + " sec";
    }






    Text bestResult(bestTimeText, font, 15);
    bestResult.setFillColor(Color::Cyan);
    bestResult.setPosition(50, 20);

    // Малюємо все меню
    window.clear(Color::Black);  // Очищаємо екран
    window.draw(title);
    window.draw(playButton);
    window.draw(exitButton);
    window.draw(bestResult);
}

bool startGame(int mouseX, int mouseY) {
    if (mouseX >= 100 && mouseX <= 400 && mouseY >= 200 && mouseY <= 230) {
        return true;
    }
    return false;
}

bool exitGame(int mouseX, int mouseY) {
    if (mouseX >= 100 && mouseX <= 400 && mouseY >= 300 && mouseY <= 330) {
        return true;
    }
    return false;

}

