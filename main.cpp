#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <iostream>


using namespace sf;
using namespace std;


const int SIZE = 4; // ����� ���� 4x4
const int TILE_SIZE = 100; // ����� ����� ������
const int WINDOW_SIZE = TILE_SIZE * SIZE; // ����� ����


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

            // ��������� ��'���� "������"
            RectangleShape tile(Vector2f(TILE_SIZE, TILE_SIZE));

            // ������������ ������ �� �������� ����
            tile.setPosition(X_pos, Y_pos);

            // ������ ��������� ��� ����� ������
            tile.setOutlineColor(Color::Black);
            tile.setOutlineThickness(3);


            if (tiles[i] != 0) {

                tile.setFillColor(Color::Cyan);

                // ��������� ����� "Arial"
                Font font;
                if (!font.loadFromFile("Fonts/Arial.ttf")) {
                    cerr << "Error loading font!" << endl;
                }

                // ��������� ����� ����� �� ������� ������
                Text text(to_string(tiles[i]), font, 30);

                // ������������ ���� 
                text.setFillColor(sf::Color::Black);

                // ������������ ����� �� �������� ������ �� ����������� ������� �������
                text.setPosition(X_pos + TILE_SIZE / 2 - text.getLocalBounds().width / 2,
                    Y_pos + TILE_SIZE / 2 - text.getLocalBounds().height / 2);



                // ���������� ������ � �����
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

};



int main() {

    // ��������� ���� ������ 800x600
    RenderWindow window(VideoMode(WINDOW_SIZE, WINDOW_SIZE), "SFML Window Fifteen Game");
    
    

    // Sprite creation

    /*Texture texture;
    if (!texture.loadFromFile("mySprite.jpg")) return EXIT_FAILURE;
    
    Sprite sprite(texture);*/


    // Text

   /* Font font;
    if (!font.loadFromFile("arial.ttf"))
        return EXIT_FAILURE;
    Text text("Hello SFML", font, 50);*/
   


    // ��'��� ��� ������� ����
    Event event;

    Fifteens myFifteens;

    // �������� ����
    while (window.isOpen()) {
        // ������� ����
        // window.pollEvent(event) � �������, ��� ������ ��䳿 � ����� ����, �� ������� � ���. 
        // ���� ������� true, ���� � ��� ��䳿.
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close(); // ��������� ���� ��� ��������� "�������"
            }
        }

        // ������� ���� ������ ��������
        window.clear(Color::Black);

        // ������� ���� �� �����
        myFifteens.showTilesOnScreen(window);

        // ��������� ����
        window.display();
    }

    return 0;
}
