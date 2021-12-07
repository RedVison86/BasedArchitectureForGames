#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <ctime>

// player class //

class Player
{
    private:
        sf::Texture txr;
        sf::Sprite spr;
        float moveSpeed;

        void initVariable()
        {
            this->moveSpeed = 10.f;

        }

        void initSprite()
        {
            this->txr.loadFromFile("../...png");
            this->spr.setTexture(this->txr);
        }

    public:
        Player(float x = 100.f, float y = 100.f)
        {
            this->spr.setPosition(x, y);
            this->initVariable();
            this->initSprite();
        }

        virtual ~Player()
        {

        }


        void updateInput()
        {

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                this->spr.move(-this->moveSpeed, 0.f);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                this->spr.move(this->moveSpeed, 0.f);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                this->spr.move(0.f, -this->moveSpeed);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            {
                this->spr.move(0.f, this->moveSpeed);
            }

        }

        void updateWindowCollision(sf::RenderTarget *target)
        {
            // left
            if (this->spr.getGlobalBounds().left <= 0.f)
            {
                this->spr.setPosition(0.f, this->spr.getGlobalBounds().top);
            }
            // right
            if (this->spr.getGlobalBounds().left + this->spr.getGlobalBounds().width >= target->getSize().x)
            {
                this->spr.setPosition(target->getSize().x - this->spr.getGlobalBounds().width, this->spr.getGlobalBounds().top);
            }
            // top
            if (this->spr.getGlobalBounds().top <= 0.f)
            {
                this->spr.setPosition(this->spr.getGlobalBounds().left, 0.f);
            }
            // bottom
            if (this->spr.getGlobalBounds().top + this->spr.getGlobalBounds().height >= target->getSize().y)
            {
                this->spr.setPosition(this->spr.getGlobalBounds().left, target->getSize().y - this->spr.getGlobalBounds().height);
            }


        }

        void update(sf::RenderTarget *target)
        {
            this->updateInput();
            this->updateWindowCollision(target);
        }

        void render(sf::RenderTarget *target)
        {
            target->draw(this->spr);
        }
};


// game class //

class Game
{

    private:
        sf::RenderWindow *window;
        bool endGame;
        sf::VideoMode videoMode;
        sf::Event eve;

        Player player;

        void initVariable()
        {
            this->endGame = false;
        }

        void initWindow()
        {
            this->videoMode = sf::VideoMode(400, 533);
            this->window = new sf::RenderWindow(videoMode, "gb", sf::Style::Close);
            this->window->setFramerateLimit(60);
        }


    public:
        Game()
        {
            this->initVariable();
            this->initWindow();
        }

        ~Game()
        {
            delete this->window;
        }

        const bool running() const
        {
            return this->window->isOpen();
        }

        void pollEvent()
        {
            while(this->window->pollEvent(this->eve))
            {
                switch(this->eve.type)
                {

                case sf::Event::Closed:
                    this->window->close();
                    break;

                case sf::Event::KeyPressed:
                    if (this->eve.key.code == sf::Keyboard::Escape)
                    {
                        this->window->close();
                    }

                    break;
                }
            }

        }

        void update()
        {
            this->pollEvent();
            this->player.update(this->window);
        }

        void render()
        {
            this->window->clear();

            this->player.render(this->window);

            this->window->display();
        }


};

int main()
{
    // init //
    srand(time(0));

    // init game //
    Game game;

    while(game.running())
    {
        game.update();
        game.render();

    }

    // end //
    return 0;
}
