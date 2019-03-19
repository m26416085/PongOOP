#include<iostream>
#include<SFML/Graphics.hpp>
#include<cmath>
#include<ctime>
#include<cstdlib>

using namespace std;

enum Direction
{
	Up, Left, Right, Down, Stop
};

class Ball
{
protected:
	float rad;
	sf::CircleShape ball;
	float spd, angle;
	float x, y;
public:
	Ball()
	{
		ball.setFillColor(sf::Color::Green);
		ball.setOutlineThickness(3);
		ball.setOutlineColor(sf::Color::Black);
	}
	Ball(float radd)
	{
		rad = radd;
	}
	void setRad(int radd)
	{
		rad = radd;
		ball.setRadius(rad);
	}
	int getRad()
	{
		return rad;
	}
	void setOrigin(float ballRad)
	{
		ball.setOrigin(ballRad/2, ballRad/2);
	}
	void setBallSpeed(float speed)
	{
		spd = speed;
	}
	float getBallSpeed()
	{
		return spd;
	}
	void setBallAngle(float anglee)
	{
		angle = anglee;
	}
	float getBallAngle()
	{
		return angle;
	}
	void defaultPosition(float gw, float gh)
	{
		ball.setPosition(gw/2,gh/2);
	}
	void Move(float temp)
	{
		ball.move(cos(angle) * temp, sin(angle) * temp);
	}
	void ballSetPosition(float temp1, float temp2)
	{
		ball.setPosition(temp1,temp2);
	}
	float ballGetX()
	{
		return ball.getPosition().x;
	}
	float ballGetY()
	{
		return ball.getPosition().y;
	}
	void Draw (sf::RenderWindow &window)
	{
		window.draw(ball);
	}
};
class Paddle
{
protected:
	float spd;
	Direction direction;
	sf::Vector2f paddleSize;
public:
	Paddle()
	{}
	virtual void setPaddleSize(sf::Vector2f paddlesize) = 0;
	virtual float getPaddleSizeX() = 0;
	virtual float getPaddleSizeY() = 0;
	virtual void setOrigin(sf::Vector2f paddlesize) = 0;
	virtual void setPaddleSpeed(float speed) = 0;
	virtual void defaultPosition(float gh, float gw) = 0;
};
class RightPaddle : public Paddle
{
protected:
	sf::RectangleShape rightPaddle;
public:
	RightPaddle()
	{
		rightPaddle.setFillColor(sf::Color::Blue);
		rightPaddle.setOutlineThickness(3);
		rightPaddle.setOutlineColor(sf::Color::Black);
	}
	void setPaddleSize(sf::Vector2f paddlesize)
	{
		paddleSize = paddlesize;
		rightPaddle.setSize(paddleSize - sf::Vector2f(3,3));
	}
	float getPaddleSizeX()
	{
		return paddleSize.x;
	}
	float getPaddleSizeY()
	{
		return paddleSize.y;
	}
	void setOrigin(sf::Vector2f paddlesize)
	{
		rightPaddle.setOrigin(paddlesize / 2.f);
	}
	void setPaddleSpeed(float speed)
	{
		spd = speed;
	}
	void defaultPosition(float gh, float gw)
	{
		rightPaddle.setPosition(gw - 10 - paddleSize.x / 2, gh / 2);
	}
	float RightgetX()
	{
		return rightPaddle.getPosition().x;
	}
	float RightgetY()
	{
		return rightPaddle.getPosition().y;
	}
	void RightMove(Direction direct)
	{
		direction = direct;
		if (direction == Direction::Stop)
		{
			rightPaddle.move(0.f,0.f);
		}
		else if (direction == Direction::Up)
		{
			rightPaddle.move(0.f, -spd);
		}
		else if (direction == Direction::Down)
		{
			rightPaddle.move(0.f, spd);
		}
	}
	void RightDraw(sf::RenderWindow &window)
	{
		window.draw(rightPaddle);
	}
};
class LeftPaddle : public Paddle
{
protected:
	sf::RectangleShape leftPaddle;
	sf::RectangleShape rightPaddle;
public:
	LeftPaddle()
	{
		leftPaddle.setFillColor(sf::Color::Magenta);
		leftPaddle.setOutlineThickness(3);
		leftPaddle.setOutlineColor(sf::Color::Black);
	}
	void setPaddleSize(sf::Vector2f paddlesize)
	{
		paddleSize = paddlesize;
		leftPaddle.setSize(paddleSize - sf::Vector2f(3,3));
	}
	float getPaddleSizeX()
	{
		return paddleSize.x;
	}
	float getPaddleSizeY()
	{
		return paddleSize.y;
	}
	void setOrigin(sf::Vector2f paddlesize)
	{
		leftPaddle.setOrigin(paddlesize / 2.f);
	}
	void setPaddleSpeed(float speed)
	{
		spd = speed;
	}
	void defaultPosition(float gh, float gw)
	{
		leftPaddle.setPosition(10 + paddleSize.x / 2, gh /2);
	}
	float LeftgetX()
	{
		return leftPaddle.getPosition().x;
	}
	float LeftgetY()
	{
		return leftPaddle.getPosition().y;
	}
	void LeftMove(Direction direct)
	{
		direction = direct;
		if (direction == Direction::Stop)
		{
			leftPaddle.move(0.f,0.f);
			rightPaddle.move(0.f,0.f);
		}
		else if (direction == Direction::Up)
		{
			leftPaddle.move(0.f, -spd);
		}
		else if (direction == Direction::Down)
		{
			leftPaddle.move(0.f, spd);
		}
	}
	void LeftDraw(sf::RenderWindow &window)
	{
		window.draw(leftPaddle);
	}
};

void main()
{
	int windowW = 1200;
	int windowH = 600;
	sf::RenderWindow window(sf::VideoMode(windowW, windowH, 32), "Pong", sf::Style::Titlebar | sf::Style::Close);

	sf::Vector2f paddleSize(25,100);
	float ballrad = 10.f;

	//left paddle right paddle
	LeftPaddle leftPaddle; RightPaddle rightPaddle;
	leftPaddle.setPaddleSize(paddleSize); rightPaddle.setPaddleSize(paddleSize);
	leftPaddle.setOrigin(paddleSize); rightPaddle.setOrigin(paddleSize);
	float pspeed = 5.f;
	leftPaddle.setPaddleSpeed(pspeed); rightPaddle.setPaddleSpeed(pspeed);

	//ball
	Ball ball;
	ball.setRad(ballrad - 3);
	ball.setOrigin(ballrad);
	float ballspd = 400.f; ball.setBallSpeed(ballspd);
	float ballagl = 0; ball.setBallAngle(ballagl);

	sf::Font font;
	font.loadFromFile("arial.ttf");
	sf::Text pauseMessage;
	pauseMessage.setColor(sf::Color::Black);
	pauseMessage.setFont(font);
	pauseMessage.setCharacterSize(66);
	pauseMessage.setPosition(100, 120);
	pauseMessage.setString("PONG! Press Space");

	sf::Clock clock;
	bool isPlaying = false;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if ((event.type == sf::Event::Closed) || (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
			{
				window.close();
				break;
			}
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
			{
				if (!isPlaying)
				{
					//start
					isPlaying = true;

					//reset game
					leftPaddle.defaultPosition(windowH,windowW);
					rightPaddle.defaultPosition(windowH,windowW);
					ball.defaultPosition(windowW,windowH);
					ball.setBallSpeed(ballspd);

					while (abs(cos(ball.getBallAngle()) < 0.7f))
					{
						ball.setBallAngle((rand() % 360) * 2 * 3.14 / 360);
					}
				}
			}
		}

		if (isPlaying)
		{
			//fps game turun kalau laptop tidak di charge
			window.setFramerateLimit(60);
			float deltaTime = clock.restart().asSeconds();

			//move ball
			float temp = ball.getBallSpeed() * deltaTime;
			ball.Move(temp);

			//collison
			if (ball.ballGetX() - ball.getRad() < 0)
			{
				isPlaying = false;
				pauseMessage.setString("P2 Win!\n");
				ball.defaultPosition(windowW,windowH);
				ball.setBallSpeed(ballspd);
			}
			else if (ball.ballGetX() + ball.getRad() > windowW)
			{
				isPlaying = false;
				pauseMessage.setString("P1 Win!\n");
			}
			if (ball.ballGetY() - ball.getRad() < 0)
			{
				ball.setBallAngle(-ball.getBallAngle());
				ball.ballSetPosition(ball.ballGetX(), ball.getRad() + 0.1);
			}
			if (ball.ballGetY() + ball.getRad() > windowH)
			{
				ball.setBallAngle(-ball.getBallAngle());
				ball.ballSetPosition(ball.ballGetX(), windowH - ball.getRad() - 0.1);
			}

			//collison paddle
			if (ball.ballGetX() - ball.getRad() < leftPaddle.LeftgetX() + leftPaddle.getPaddleSizeX() / 2 && ball.ballGetX() - ball.getRad() > leftPaddle.LeftgetX() &&
				ball.ballGetY() + ball.getRad() >= leftPaddle.LeftgetY() - leftPaddle.getPaddleSizeY() / 2 && ball.ballGetY() - ball.getRad() <= leftPaddle.LeftgetY() + leftPaddle.getPaddleSizeY() / 2)
			{
				if (ball.ballGetY() > leftPaddle.LeftgetY())
				{
					ball.setBallAngle(3.14 - ball.getBallAngle() + (rand() % 20) * 3.14 / 180);
					ball.setBallSpeed(ball.getBallSpeed() + 35);
				}
				else
				{
					ball.setBallAngle(3.14 - ball.getBallAngle() - (rand() % 20) * 3.14 / 180);
					ball.setBallSpeed(ball.getBallSpeed() + 35);
				}
				ball.ballSetPosition(leftPaddle.LeftgetX() + ball.getRad() + leftPaddle.getPaddleSizeX() / 2 + 0.1f, ball.ballGetY());
			}

			if (ball.ballGetX() + ball.getRad() > rightPaddle.RightgetX() - rightPaddle.getPaddleSizeX() / 2 && ball.ballGetX() + ball.getRad() < rightPaddle.RightgetX() &&
				ball.ballGetY() + ball.getRad() >= rightPaddle.RightgetY() - rightPaddle.getPaddleSizeY() / 2 && ball.ballGetY() - ball.getRad() <= rightPaddle.RightgetY() + rightPaddle.getPaddleSizeY() / 2)
			{
				if (ball.ballGetY() > rightPaddle.RightgetY())
				{
					ball.setBallAngle(3.14 - ball.getBallAngle() + (rand() % 20) * 3.14 / 180);
					ball.setBallSpeed(ball.getBallSpeed() + 35);
				}
				else
				{
					ball.setBallAngle(3.14 - ball.getBallAngle() - (rand() % 20) * 3.14 / 180);
					ball.setBallSpeed(ball.getBallSpeed() + 35);
				}

				ball.ballSetPosition(rightPaddle.RightgetX() - ball.getRad() - rightPaddle.getPaddleSizeX() / 2 - 0.1f, ball.ballGetY());
			}

			//player 1
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (leftPaddle.LeftgetY() - leftPaddle.getPaddleSizeY() / 2 > 5))
			{
				leftPaddle.LeftMove(Direction::Up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (leftPaddle.LeftgetY() + leftPaddle.getPaddleSizeY() / 2 < windowH - 5))
			{
				leftPaddle.LeftMove(Direction::Down);
			}

			//player 2
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && (rightPaddle.RightgetY() - rightPaddle.getPaddleSizeY() / 2 > 5))
			{
				rightPaddle.RightMove(Direction::Up);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && (rightPaddle.RightgetY() + rightPaddle.getPaddleSizeY() / 2 < windowH - 5))
			{
				rightPaddle.RightMove(Direction::Down);
			}
		}

		window.clear(sf::Color(253,251,0));

		if (isPlaying)
		{
			leftPaddle.LeftDraw(window);
			rightPaddle.RightDraw(window);
			ball.Draw(window);
		}
		else
		{
			window.draw(pauseMessage);
		}

		window.display();
	}
}