#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>
#include <algorithm>

#include "game.h"
#include "menu.h"

using namespace sf;
using namespace std;


const int SIZE = 4; // ����� ���� 4x4
const int TILE_SIZE = 100; // ����� ����� ������
const int WINDOW_SIZE = TILE_SIZE * SIZE; // ����� ����

//class Menu {
//
//public:
//   
//    void showMainMenu(RenderWindow& window, Font& font) {
//        // ��������� ����
//        Text title("Fifteen Puzzle", font, 50);
//        title.setFillColor(Color::White);
//        title.setPosition(50, 100);
//
//        // ������ ��� ������ ���
//        Text playButton("Start Game", font, 30);
//        playButton.setFillColor(Color::Green);
//        playButton.setPosition(100, 200);
//
//        // ������ ��� ������
//        Text exitButton("Exit", font, 30);
//        exitButton.setFillColor(Color::Red);
//        exitButton.setPosition(100, 300);
//
//        // ������� ��� ����
//        window.clear(Color::Black);  // ������� �����
//        window.draw(title);
//        window.draw(playButton);
//        window.draw(exitButton);
//    }
//
//    bool startGame(int mouseX, int mouseY) {
//        if (mouseX >= 100 && mouseX <= 400 && mouseY >= 200 && mouseY <= 230) {
//            return true;
//        }
//        return false;
//    }
//
//    bool exitGame(int mouseX, int mouseY) {
//        if (mouseX >= 100 && mouseX <= 400 && mouseY >= 300 && mouseY <= 330) {
//            return true;  
//        }
//        return false;
//    }
//};
//
//
//int menu() {
//    Menu menu;
//
//
//    Event event;
//
//    Font font;
//    if (!font.loadFromFile("Fonts/Arial.ttf")) {
//        cerr << "Error loading font!" << endl;
//        return -1;
//    }
//
//    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML Window Fifteen Game");
//
//
//    while (window.isOpen()) {
//        // ������� ����
//        // window.pollEvent(event) � �������, ��� ������ ��䳿 � ����� ����, �� ������� � ���. 
//        // ���� ������� true, ���� � ��� ��䳿.
//        while (window.pollEvent(event)) {
//            if (event.type == Event::Closed) {
//                window.close(); // ��������� ���� ��� ��������� "�������"
//            }
//
//            // �������� �� ��������� ����
//            if (event.type == Event::MouseButtonPressed) {
//                // �������� �� ��������� ˲�� ������ ����
//                if (event.key.code == Mouse::Left)
//                {
//                    Vector2i pos = Mouse::getPosition(window);
//
//                    int mouseX = pos.x;
//                    int mouseY = pos.y;
//
//
//                    if (menu.startGame(mouseX, mouseY)) {
//                        game();
//
//                    }
//                    // ���� ��������� ������ "Exit"
//                    else if (menu.exitGame(mouseX, mouseY)) {
//                        window.close();  // ��������� ���
//                    }
//                   
//                }
//            }
//
//            
//        }
//
//        menu.showMainMenu(window, font);
//
//        // ��������� ����
//        window.display();
//    }
//
//    return 0;

void showMainMenu(RenderWindow& window, Font& font) {
    // ��������� ����
    Text title("Fifteen Puzzle", font, 50);
    title.setFillColor(Color::White);
    title.setPosition(50, 100);

    // ������ ��� ������ ���
    Text playButton("Start Game", font, 30);
    playButton.setFillColor(Color::Green);
    playButton.setPosition(100, 200);

    // ������ ��� ������
    Text exitButton("Exit", font, 30);
    exitButton.setFillColor(Color::Red);
    exitButton.setPosition(100, 300);

    // ������� ��� ����
    window.clear(Color::Black);  // ������� �����
    window.draw(title);
    window.draw(playButton);
    window.draw(exitButton);
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