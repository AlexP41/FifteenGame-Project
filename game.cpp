#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>


#include "game.h"
#include "menu.h"
#include "main.h"


using namespace sf;
using namespace std;


const int SIZE = 4; // Розмір поля 4x4
const int TILE_SIZE = 100; // Розмір кожної плитки
const int WINDOW_SIZE = TILE_SIZE * SIZE; // Розмір вікна





class Fifteens {

private:
    vector<int>tiles;

public:
    int size = 4; // By default 4 x 4
    

    // Constructor
    Fifteens() {
        reset();
    }


    void reset()
    {
        tiles.clear();
        for (size_t i = 0; i < size * size - 1; ++i)
        {
            tiles.push_back(i+1);
        }
        tiles.push_back(0);
    }

    void showTilesOnScreen(RenderWindow& window)
    {
        for (size_t i = 0; i < size * size; ++i)
        {
            int X_pos = (i % size) * TILE_SIZE;
            int Y_pos = (i / size) * TILE_SIZE;

            // Створення об'єкту "плитка"
            RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE));

            // Встановлюємо плитку на відповідне місце
            tile.setPosition(X_pos, Y_pos);

            // Задаємо параметри для кожної плитки
            tile.setOutlineColor(Color::Black);
            tile.setOutlineThickness(3);


            if (tiles[i] != 0) {

                tile.setFillColor(Color::Cyan);

                // Створюємо шрифт "Arial"
                Font font;
                if (!font.loadFromFile("Fonts/Arial.ttf")) {
                    cerr << "Error loading font!" << endl;
                }

                // Створюємо шрифт текст із номером плитки
                Text text(to_string(tiles[i]), font, 30);

                // Встановлюємо колір 
                text.setFillColor(sf::Color::Black);

                // Встановлюємо текст по середины плитки із урахуванням товщини бордерів
                text.setPosition(X_pos + TILE_SIZE / 2 - text.getLocalBounds().width / 2,
                    Y_pos + TILE_SIZE / 2 - text.getLocalBounds().height / 2);



                // відображаємо плитку і текст
                window.draw(tile);
                window.draw(text);
            }

            else {

                tile.setFillColor(Color::White);
                tile.setOutlineColor(Color::Black);
                tile.setOutlineThickness(3);

                window.draw(tile);
            }
        }
           
    }

    void shuffle() {

        /*random_shuffle(tiles.begin(), tiles.end());*/

        /*srand((time(0))); 
        for (int i = 0; i < size * size; ++i) {
            int j = std::rand() % (SIZE * SIZE);
            swap(tiles[i], tiles[j]);
        }*/
        swap(tiles[size*size-2], tiles[size * size - 1]);
    }

    int findEmptyTile() const {
        for (int i = 0; i < size * size; ++i) {
            if (tiles[i] == 0) return i;
        }
        return -1;
    } //const тут означає, що метод не змінює жодних змінних-членів (tiles) цього класу.



    bool validToMoveTile(int indexOfTileToMove) {
        int indexOfEmptyTile = findEmptyTile();

        // Перевірка, чи плитка може переміщатися зліва, справа, зверху або знизу
        if ((indexOfTileToMove == indexOfEmptyTile - 1 && indexOfTileToMove / size == indexOfEmptyTile / size) ||  // плитка ліворуч
            (indexOfTileToMove == indexOfEmptyTile + 1 && indexOfTileToMove / size == indexOfEmptyTile / size) ||  // плитка праворуч
            (indexOfTileToMove == indexOfEmptyTile - size) || // плитка зверху
            (indexOfTileToMove == indexOfEmptyTile + size))   // плитка знизу
        {
            return true;
        }

        return false;
    }

    void moveTile(int indexOfTileToMove)
    {
        int indexOfEmptyTile = findEmptyTile();

        if (validToMoveTile(indexOfTileToMove)) swap(tiles[indexOfTileToMove], tiles[indexOfEmptyTile]);
    
    }

    bool isSolved() const {
        for (int i = 0; i < SIZE * SIZE - 1; ++i) {
            if (tiles[i] != i + 1) return false;
        }
        return tiles[SIZE * SIZE - 1] == 0;
    }

    int getClickedTilePosition(int mouseX, int mouseY)
    {
        int row = mouseY / TILE_SIZE;
        int col = mouseX / TILE_SIZE;
        int index = row * size + col;

        if (index >= 0 && index < size * size) {
            return index;
        }
        return -1; // Якщо не на плитку
    }


};



int game() {
    system("chcp 1251>null");

    // Створюємо вікно розміру 800x600
    RenderWindow gameWindow(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML Window Fifteen Game");
    
    bool isWin = false;
    bool startCountTime = true; // Важливий момент про який я не одразу здогадався, 
                //адже нам потрібно починати відлік тільки один раз, а не кожний раз під час виконання циклу while (gameWindow.isOpen())

    // Об'єкт для обробки подій
    Event event;

    Clock clock;

    Fifteens myFifteens;
    
    myFifteens.shuffle();

    Font font;
    if (!font.loadFromFile("Fonts/Arial.ttf")) {
        cerr << "Error loading font!" << endl;
        return -1;
    }








    // Основний цикл
    while (gameWindow.isOpen()) {
        // Обробка подій
        // window.pollEvent(event) — функція, яка витягує події з черги подій, що виникли у вікні. 
        // Вона повертає true, якщо є нові події.
        while (gameWindow.pollEvent(event)) {
            if (event.type == Event::Closed) {
                
                gameWindow.close(); // Закриваємо вікно при натисканні "Закрити"
                
            }

            // Перевірка чи натиснута миша
            if (event.type == Event::MouseButtonPressed) {
                // Перевірка чи натиснута ЛІВА кнопка миші
                if (event.key.code == Mouse::Left) 
                {
                    Vector2i pos = Mouse::getPosition(gameWindow);

                    int mouseX = pos.x;
                    int mouseY = pos.y;


                    int selectedTile = myFifteens.getClickedTilePosition(mouseX, mouseY);

                    if (selectedTile != -1) myFifteens.moveTile(selectedTile);
                }

            }

        }

       
        // Очищаємо вікно чорним кольором
        gameWindow.clear(Color::Black);

        // Малюємо пятнашки на екрані
        myFifteens.showTilesOnScreen(gameWindow);


        // якщо пятнашкі розв'язані
        if (myFifteens.isSolved()) {
            Text winText("You Win!", font, 50);
            winText.setFillColor(Color::Green);
            winText.setPosition(100, 150);

            gameWindow.clear(Color::Yellow);  // Очищаємо екран жовтим кольором

            gameWindow.draw(winText);  // Малюємо текст "You Win!

            isWin = true;

            if (startCountTime) // Важливий момент про який я не одразу здогадався, 
                //адже нам потрібно починати відлік тільки один раз, а не кожний раз під час виконання циклу while (gameWindow.isOpen())
            {
                clock.restart(); // Перезапускаємо годинник, щоб почати відлік часу
                startCountTime = false;
            }
        }

        
        if (isWin && clock.getElapsedTime().asSeconds() >= 3) {
            gameWindow.close();// Закриваємо вікно після 3 секунд
            main();
        
        }

        // Оновлюємо вікно
        gameWindow.display();
    }

    return 0;
}
