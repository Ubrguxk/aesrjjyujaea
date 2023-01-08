#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>
#include<fstream>

using namespace std;
using namespace sf;

int score = 0;
float gameSpeed = 1;
const double SCREEN_WIDTH = 500;
const double SCREEN_HEIGH = 800;
// CALOSC DZIEJE SIE NA 500x800 
// notka jakby sie zmienialo np szeroosc by dodac boarders
Text text1;
Text text2;
clock_t start;
clock_t stop;
float czas;

bool czy_menu, czy_lose;

float Przeszkoda_1_x, Przeszkoda_1_y, Przeszkoda_2_x, Przeszkoda_2_y;
float Przeszkoda_3_x, Przeszkoda_3_y, Przeszkoda_4_x, Przeszkoda_4_y, Przeszkoda_5_x, Przeszkoda_5_y;

int getRandomNumber()
{
    static bool first = true;

    if (first) {
        srand(time(NULL));
        first = false;
    }

    float result = 50 + rand() % ((450 + 1) - 50);

    result = (result / 10) * 10;

    return result;
}



int main()
{
    RenderWindow oknoAplikacji(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Car Racing");
    oknoAplikacji.setFramerateLimit(60);

    czy_menu = false;
    czy_lose = false;

    Texture player, przeszkoda1, przeszkoda2, przeszkoda3, przeszkoda4, przeszkoda5, menu, tlo, game_over;

    getRandomNumber();
    Przeszkoda_1_x = getRandomNumber();
    Przeszkoda_2_x = getRandomNumber();
    Przeszkoda_3_x = getRandomNumber();
    Przeszkoda_4_x = getRandomNumber();
    Przeszkoda_5_x = getRandomNumber();

    Przeszkoda_1_y = -600;
    Przeszkoda_2_y = -300;
    Przeszkoda_3_y = -150;
    Przeszkoda_4_y = -450;
    Przeszkoda_5_y = 0;

    if (!tlo.loadFromFile("tlo.png")) return EXIT_FAILURE;
    if (!player.loadFromFile("czerwony.png")) return EXIT_FAILURE;
    if (!przeszkoda1.loadFromFile("pomaranczowy.png")) return EXIT_FAILURE;
    if (!przeszkoda2.loadFromFile("zielony.png")) return EXIT_FAILURE;
    if (!przeszkoda3.loadFromFile("zolty.png")) return EXIT_FAILURE;
    if (!przeszkoda4.loadFromFile("niebieski.png")) return EXIT_FAILURE;
    if (!przeszkoda5.loadFromFile("rozowy.png")) return EXIT_FAILURE;
    if (!menu.loadFromFile("menu.png")) return EXIT_FAILURE;
    if (!tlo.loadFromFile("tlo.png")) return EXIT_FAILURE;
    if (!game_over.loadFromFile("tloLOSE.png")) return EXIT_FAILURE;

    Sprite Player(player), Przeszkoda1(przeszkoda1), Przeszkoda2(przeszkoda2), Przeszkoda3(przeszkoda3), Przeszkoda4(przeszkoda4), Przeszkoda5(przeszkoda5), Menu(menu), Tlo(tlo), Game_Over(game_over);

    Vector2f Player_position(225, 700);
    //Poniwaz w taki sporob przyposujemy pzycje gracza to nie mamy odzielnych funkcji x, y tylko 
    // sie odwolujemy za pomoca Player_position.x i Player_position.y

    SoundBuffer gameSoundBuffer;
    gameSoundBuffer.loadFromFile("game.wav");
    Sound GameSound;
    GameSound.setBuffer(gameSoundBuffer);

    SoundBuffer menuSoundBuffer;
    menuSoundBuffer.loadFromFile("menu.wav");
    Sound menuSound;
    menuSound.setBuffer(menuSoundBuffer);

    SoundBuffer loseSoundBuffer;
    loseSoundBuffer.loadFromFile("lose.wav");
    Sound loseSound;
    loseSound.setBuffer(loseSoundBuffer);

    Font czcionka;
    czcionka.loadFromFile("arial.ttf");
    
    //OBSLUGA SCORES
    //ZAPIS DO PLIKU ODCZYT Z PLIKU
    text1.setFont(czcionka);
    text2.setFont(czcionka);
    text1.setCharacterSize(30);
    text2.setCharacterSize(30);
    text1.setFillColor(Color::White);
    text2.setFillColor(Color::White);

    fstream naj_wynik;
    naj_wynik.open("highscore.txt", ios::in);
    if (naj_wynik.good() == false) {
        return EXIT_FAILURE;
    }
    int wynik;
    naj_wynik >> wynik;
    naj_wynik.close();

    text1.setString(to_string(score));
    text1.setPosition(395, 362);
    text2.setString(to_string(wynik));
    text2.setPosition(445, 420);

    if (score > wynik) {
        naj_wynik.open("highscore.txt", ios::out);
        if (naj_wynik.good() == false) {
            return EXIT_FAILURE;
        }
        naj_wynik >> score;
        naj_wynik.close();
    }

    while (oknoAplikacji.isOpen())
    {

        if (czy_menu == true) {
            start = clock();
        }
        if (czy_lose == true) {
            stop = clock();
        }

        czas = (float)(stop - start) / CLOCKS_PER_SEC;
        score = czas;

        if (czy_menu == false && czy_lose == false) {
            menuSound.play();
        }
        if (czy_menu == true && czy_lose == false) {
            menuSound.stop();
            GameSound.play();
            GameSound.setLoop(true);
        }
        if (czy_lose == true) {
            GameSound.stop();
            loseSound.play();
        }
        Event zdarzenie;
        while (oknoAplikacji.pollEvent(zdarzenie))
        {
            if (zdarzenie.type == Event::Closed)
                oknoAplikacji.close();

            // WAZNE
            // Z DUZEJ LITERY - SPRITE
            // Z MALEJ LITERY - TEKSTURY
            // UZYWAJ DUZEJ LITERY 

            Przeszkoda1.setPosition(Przeszkoda_1_x, Przeszkoda_1_y);
            Przeszkoda2.setPosition(Przeszkoda_2_x, Przeszkoda_2_y);
            Przeszkoda3.setPosition(Przeszkoda_3_x, Przeszkoda_3_y);
            Przeszkoda4.setPosition(Przeszkoda_4_x, Przeszkoda_4_y);
            Przeszkoda5.setPosition(Przeszkoda_5_x, Przeszkoda_5_y);

            Player.setPosition(Player_position);

            if (zdarzenie.key.code == sf::Keyboard::Left || zdarzenie.key.code == sf::Keyboard::A) {
                if (Player_position.x > 25) {
                    Player_position.x -= 5;
                }
            }

            if (zdarzenie.key.code == sf::Keyboard::Right || zdarzenie.key.code == sf::Keyboard::D) {
                if (Player_position.x < 450) {
                    Player_position.x += 5;
                }
            }
            if (zdarzenie.key.code == sf::Keyboard::Down || zdarzenie.key.code == sf::Keyboard::S) {
                if (Player_position.y < 700) {
                    Player_position.y += 10;
                }
            }
            if (zdarzenie.key.code == sf::Keyboard::Up || zdarzenie.key.code == sf::Keyboard::W) {
                if (Player_position.y > 50) {
                    Player_position.y -= 15;
                }
            }
            if (zdarzenie.key.code == sf::Keyboard::Num1) {
                czy_menu = true;
                gameSpeed = 1;
            }
            if (zdarzenie.key.code == sf::Keyboard::Num2) {
                czy_menu = true;
                gameSpeed = 2;
            }
            if (zdarzenie.key.code == sf::Keyboard::Num3) {
                czy_menu = true;
                gameSpeed = 3;
            }
        }

        // tworzenie przeszkod

        if (czy_menu == true) {
            if (Przeszkoda_1_y > SCREEN_HEIGH)
            {
                Przeszkoda_1_y = -100;
                Przeszkoda_1_x = getRandomNumber();
            }

            else { Przeszkoda_1_y += gameSpeed; }


            if (Przeszkoda_2_y > SCREEN_HEIGH)
            {
                Przeszkoda_2_y = -100;
                Przeszkoda_2_x = getRandomNumber();
            }
            else { Przeszkoda_2_y += gameSpeed; }

            if (Przeszkoda_3_y > SCREEN_HEIGH)
            {
                Przeszkoda_3_y = -100;
                Przeszkoda_3_x = getRandomNumber();
            }

            else { Przeszkoda_3_y += gameSpeed; }

            if (Przeszkoda_4_y > SCREEN_HEIGH)
            {
                Przeszkoda_4_y = -100;
                Przeszkoda_4_x = getRandomNumber();
            }

            else { Przeszkoda_4_y += gameSpeed; }

            if (Przeszkoda_5_y > SCREEN_HEIGH)
            {
                Przeszkoda_5_y = -100;
                Przeszkoda_5_x = getRandomNumber();
            }

            else { Przeszkoda_5_y += gameSpeed; }

        }
        // kolizja 
        // tutaj zamiast return exit_failure dac odwolanie do int game over (ktore tak samo jak w tym projekcie z gituh zrobic)
        // i dopracowac te kolizje 

        if (((Player_position.x >= (Przeszkoda_1_x - 25)) && (Player_position.x <= (Przeszkoda_1_x + 25))) && ((Player_position.y >= (Przeszkoda_1_y - 50)) && (Player_position.y) <= (Przeszkoda_1_y + 50)))
        {
            czy_lose = true;
        }

        if (((Player_position.x >= (Przeszkoda_2_x - 25)) && (Player_position.x <= (Przeszkoda_2_x + 50))) && ((Player_position.y >= (Przeszkoda_2_y - 50)) && (Player_position.y) <= (Przeszkoda_2_y + 50)))
        {
            czy_lose = true;
        }

        if (((Player_position.x >= (Przeszkoda_3_x - 25)) && (Player_position.x <= (Przeszkoda_3_x + 50))) && ((Player_position.y >= (Przeszkoda_3_y - 50)) && (Player_position.y) <= (Przeszkoda_3_y + 50)))
        {
            czy_lose = true;
        }
        if (((Player_position.x >= (Przeszkoda_4_x - 25)) && (Player_position.x <= (Przeszkoda_4_x + 50))) && ((Player_position.y >= (Przeszkoda_4_y - 50)) && (Player_position.y) <= (Przeszkoda_4_y + 50)))
        {
            czy_lose = true;
        }

        if (((Player_position.x >= (Przeszkoda_5_x - 25)) && (Player_position.x <= (Przeszkoda_5_x + 50))) && ((Player_position.y >= (Przeszkoda_5_y - 50)) && (Player_position.y) <= (Przeszkoda_5_y + 25)))
        {
            czy_lose = true;
        }


        oknoAplikacji.clear();

        if (czy_menu == false) {
            oknoAplikacji.draw(Menu);
        }
        if (czy_menu == true) {

            oknoAplikacji.draw(Tlo);
            oknoAplikacji.draw(Player);
            oknoAplikacji.draw(Przeszkoda1);
            oknoAplikacji.draw(Przeszkoda2);
            oknoAplikacji.draw(Przeszkoda3);
            oknoAplikacji.draw(Przeszkoda4);
            oknoAplikacji.draw(Przeszkoda5);
        }
        if (czy_lose == true) {
            oknoAplikacji.draw(Game_Over);
            //oknoAplikacji.draw(text1);
            //oknoAplikacji.draw(text2);
        }
        oknoAplikacji.display();
    }
    return EXIT_SUCCESS;
}
