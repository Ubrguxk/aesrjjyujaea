#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <windows.h>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;
using namespace sf;

string stringscore = "";
int score = 0;
double gameSpeed = 1;
const double SCREEN_WIDTH = 500;
const double SCREEN_HEIGH = 800;
// CALOSC DZIEJE SIE NA 500x800 
bool lewy = false;
bool prawy = false;

float Przeszkoda_1_x, Przeszkoda_1_y, Przeszkoda_2_x, Przeszkoda_2_y;
float Przeszkoda_3_x, Przeszkoda_3_y, Przeszkoda_4_x, Przeszkoda_4_y, Przeszkoda_5_x, Przeszkoda_5_y;
float Punkt_x, Punkt_y;

int getRandomNumber()
{
    static bool first = true; 
   
    if (first) {
        srand(time(NULL)); 
        first = false; 
    }

    int result = 50 + rand() % ((450 + 1) - 50);

    result = (result / 10) * 10;

    return result;
}



int main()
{
    RenderWindow oknoAplikacji(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "");
    oknoAplikacji.setFramerateLimit(60);


    Texture player, przeszkoda1, przeszkoda2, przeszkoda3, przeszkoda4, przeszkoda5, punkt; 
    
    // wynik
    
    Font czcionka;
    czcionka.loadFromFile("arial.ttf");

    stringscore = "SCORE:" + to_string(score);
    Text text(stringscore, czcionka, 15);
    text.setPosition(5, 0);
  
    Przeszkoda_1_x = getRandomNumber();
    Przeszkoda_2_x = getRandomNumber();
    Przeszkoda_3_x = getRandomNumber();
    Przeszkoda_4_x = getRandomNumber();
    Przeszkoda_5_x = getRandomNumber();
    Punkt_x = getRandomNumber();

    Przeszkoda_1_y = 0;
    Przeszkoda_2_y = -100;
    Przeszkoda_3_y = -50;
    Przeszkoda_4_y = -200;
    Przeszkoda_5_y = 150;
    Punkt_y = -300;

    //if (!tlo.loadFromFile("menu.png")) return EXIT_FAILURE;
    if (!player.loadFromFile("czerwony.png")) return EXIT_FAILURE;
    if (!przeszkoda1.loadFromFile("pomaranczowy.png")) return EXIT_FAILURE;
    if (!przeszkoda2.loadFromFile("zielony.png")) return EXIT_FAILURE;
    if (!przeszkoda3.loadFromFile("zolty.png")) return EXIT_FAILURE;
    if (!przeszkoda4.loadFromFile("niebieski.png")) return EXIT_FAILURE;
    if (!przeszkoda5.loadFromFile("rozowy.png")) return EXIT_FAILURE;
    if (!punkt.loadFromFile("fioletowy.png")) return EXIT_FAILURE;

    Sprite Player(player), Przeszkoda1(przeszkoda1), Przeszkoda2(przeszkoda2), Przeszkoda3(przeszkoda3), Przeszkoda4(przeszkoda4), Przeszkoda5(przeszkoda5), Punkt(punkt);

    Vector2f Player_position(225, 750);

    while (oknoAplikacji.isOpen())
    {

        Event zdarzenie;
        while (oknoAplikacji.pollEvent(zdarzenie))
        {
            if (zdarzenie.type == Event::Closed)
                oknoAplikacji.close();

            // WAZNE
            // Z DUZEJ LITERY - SPRITE
            // Z MALEJ LITERY - TEKSTURY
            // UZYWAJ DUZEJ LITERY 

            Przeszkoda2.setPosition(Przeszkoda_1_x, Przeszkoda_1_y);
            Przeszkoda2.setPosition(Przeszkoda_2_x, Przeszkoda_2_y);
            Przeszkoda3.setPosition(Przeszkoda_3_x, Przeszkoda_3_y);
            Przeszkoda4.setPosition(Przeszkoda_4_x, Przeszkoda_4_y);
            Przeszkoda5.setPosition(Przeszkoda_5_x, Przeszkoda_5_y);
            Punkt.setPosition(Punkt_x, Punkt_y);

            Player.setPosition(Player_position);

            if (zdarzenie.key.code == sf::Keyboard::Left || zdarzenie.key.code == sf::Keyboard::A) {
                if (Player_position.x > 0) {
                    Player_position.x -= 5;
                }
            }

           if (zdarzenie.key.code == sf::Keyboard::Right || zdarzenie.key.code == sf::Keyboard::D) {
               if (Player_position.x < 800) {
                    Player_position.x += 5;
                }
            }
           if (zdarzenie.key.code == sf::Keyboard::Down || zdarzenie.key.code == sf::Keyboard::S) {
               if (Player_position.y < 800) {
                   Player_position.y += 5;
               }
           }
           if (zdarzenie.key.code == sf::Keyboard::Up || zdarzenie.key.code == sf::Keyboard::W) {
               if (Player_position.y > 0) {
                   Player_position.y -= 5;
               }
           }
        }
  
        // tworzenie przeszkod

        if (Przeszkoda_1_y > SCREEN_HEIGH)
        {
            Przeszkoda_1_y = 0;
            Przeszkoda_1_x = getRandomNumber();
            score++;
        }
        else { Przeszkoda_1_y += gameSpeed; }

        if (Przeszkoda_2_y > SCREEN_HEIGH)
        {
            Przeszkoda_2_y = 0;
            Przeszkoda_2_x = getRandomNumber();
            score++;
        }
        else { Przeszkoda_2_y += gameSpeed;}

        if (Przeszkoda_3_y > SCREEN_HEIGH)
        {
            Przeszkoda_3_y = 0;
            Przeszkoda_3_x = getRandomNumber();
            score++;
        }

        else { Przeszkoda_3_y += gameSpeed; }

        if (Przeszkoda_4_y > SCREEN_HEIGH)
        {
            Przeszkoda_4_y = 0;
            Przeszkoda_4_x = getRandomNumber();
            score++;
        }

        else { Przeszkoda_4_y += gameSpeed; }

        if (Przeszkoda_5_y > SCREEN_HEIGH)
        {
            Przeszkoda_5_y = 0;
            Przeszkoda_5_x = getRandomNumber();
            score++;
        }

        else { Przeszkoda_5_y += gameSpeed; }

        if (Punkt_y > SCREEN_HEIGH)
        {
            Sleep(30);
            Przeszkoda_5_y = 0;
            Przeszkoda_5_x = getRandomNumber();

        }

        else { Przeszkoda_5_y += gameSpeed; }

        // kolizja 
        
        if (((Player_position.x >= (Przeszkoda_1_x - 25)) && (Player_position.x <= (Przeszkoda_1_x + 25))) && ((Player_position.y >= (Przeszkoda_1_y - 25)) && (Player_position.y) <= (Przeszkoda_1_y + 25)))
        {
            return EXIT_FAILURE;
        }

        if (((Player_position.x >= (Przeszkoda_2_x - 25)) && (Player_position.x <= (Przeszkoda_2_x + 25))) && ((Player_position.y >= (Przeszkoda_2_y - 25)) && (Player_position.y) <= (Przeszkoda_2_y + 25)))
        {
            return EXIT_FAILURE;
        }
        
        if (((Player_position.x >= (Przeszkoda_3_x - 25)) && (Player_position.x <= (Przeszkoda_3_x + 25))) && ((Player_position.y >= (Przeszkoda_3_y - 25)) && (Player_position.y) <= (Przeszkoda_3_y + 25)))
        {
            return EXIT_FAILURE;
        }
        if (((Player_position.x >= (Przeszkoda_4_x - 25)) && (Player_position.x <= (Przeszkoda_4_x + 25))) && ((Player_position.y >= (Przeszkoda_4_y - 25)) && (Player_position.y) <= (Przeszkoda_4_y + 25)))
        {
            return EXIT_FAILURE;
        }

        if (((Player_position.x >= (Przeszkoda_5_x - 25)) && (Player_position.x <= (Przeszkoda_5_x + 25))) && ((Player_position.y >= (Przeszkoda_5_y - 25)) && (Player_position.y) <= (Przeszkoda_5_y + 25)))
        {
            return EXIT_FAILURE;
        }

        if (((Player_position.x >= (Punkt_x - 25)) && (Player_position.x <= (Punkt_x + 25))) && ((Player_position.y >= (Punkt_y - 25)) && (Player_position.y) <= (Punkt_y + 25)))
        {
            score = score + 5;
        }

        //oknoAplikacji.draw(tlo);
        oknoAplikacji.clear();

        //oknoAplikacji.draw(Tlo);
        oknoAplikacji.draw(Player);
        oknoAplikacji.draw(Przeszkoda1);
        oknoAplikacji.draw(Przeszkoda2);
        oknoAplikacji.draw(Przeszkoda3);
        oknoAplikacji.draw(Przeszkoda4);
        oknoAplikacji.draw(Przeszkoda5);
        oknoAplikacji.draw(Punkt);
        oknoAplikacji.draw(text);
     

        oknoAplikacji.display();
    }
    return EXIT_SUCCESS;
}