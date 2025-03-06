#pragma once
#ifndef menu_h
#define menu_h

#include <SFML/Graphics.hpp>

void showMainMenu(sf::RenderWindow& window, sf::Font& font);
bool startGame(int mouseX, int mouseY);
bool exitGame(int mouseX, int mouseY);
double extractBestTime(double bestTime, double defaultValueOfBestTime);

#endif // MENU_H

