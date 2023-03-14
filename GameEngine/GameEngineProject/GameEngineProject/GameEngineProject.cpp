// GameEngineProject.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "GraphicsSubsystem.h"

using namespace std;

/*
class Movement;


Graphics graphics;
Physics physics;

const float moveAmount = 0.1f;

//EventData class
class EventData
{
public:

    EventData() {};
    ~EventData() {};

    enum class typeOfEvent { movementUp, movementLeft, movementRight, movementDown };
};


// Executes the movement to go Left on the Movement class
class MovementCommandLeft: public EventData
{
public:
    MovementCommandLeft() : myType(typeOfEvent::movementLeft) {}
    ~MovementCommandLeft() {}


    const typeOfEvent myType;
};

// Executes the movement to go Right on the Movement class
class MovementCommandRight: public EventData
{
public:

    MovementCommandRight() : myType(typeOfEvent::movementRight){}
    ~MovementCommandRight(){}

    const typeOfEvent myType;
};

// Executes the movement to go Upwards on the Movement class
class MovementCommandUp: public EventData
{
public:
    MovementCommandUp() : myType(typeOfEvent::movementUp) {}
    ~MovementCommandUp() {}

    const typeOfEvent myType;
};

// Executes the movement to go Downwards on the Movement class
class MovementCommandDown: public EventData
{
public:
    MovementCommandDown() : myType(typeOfEvent::movementDown) {}
    ~MovementCommandDown() {}

    const typeOfEvent myType;
};


void moveLeft(EventData* myPointer);
void moveRight(EventData* myPointer);
void moveUp(EventData* myPointer);
void moveDown(EventData* myPointer); 





int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game Window");
    sf::Event event; 



    b2Vec2 gravity(0.0f, 0.0f);
    b2World world(gravity);

    float scalingFactor = 200.0f;

    graphics.SquareConfig();

    float squareHalfWidth = 0.5f;

    b2PolygonShape squareBox;
    squareBox.SetAsBox(squareHalfWidth, squareHalfWidth);

    b2BodyDef squareBD;
    squareBD.type = b2_dynamicBody;
    squareBD.position.Set(3.5f, -0.5f);  // Initial Postion is (400px, 400px) = (2m,2m)

    //not working
    physics.square = world.CreateBody(&squareBD);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &squareBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;

    physics.square->CreateFixture(&fixtureDef);


    sf::Vector2f squareGraphicsPosition;
    b2Vec2 squarePhysicsPosition;

    squareGraphicsPosition.x = (squarePhysicsPosition.x - squareHalfWidth) * scalingFactor;
    squareGraphicsPosition.y = (squarePhysicsPosition.y + squareHalfWidth) * scalingFactor * -1.0f;

    graphics.squareShape.setPosition(squareGraphicsPosition);

    float timeStep = 1.0f / 120.0f;
    int velocityIterations = 8;
    int positionIterations = 3;




    //Command Keys
    MovementCommandLeft* keyA_ = new MovementCommandLeft;
    MovementCommandUp* keyW_ = new MovementCommandUp;
    MovementCommandRight* keyD_ = new MovementCommandRight;
    MovementCommandDown* keyS_ = new MovementCommandDown;


    while (window.isOpen())
    {

        world.Step(timeStep, velocityIterations, positionIterations);

        moveLeft((EventData*)keyA_);
        moveRight((EventData*)keyD_);
        moveUp((EventData*)keyW_);
        moveDown((EventData*)keyS_);



        window.pollEvent(event);

        if (event.type == sf::Event::Closed)
        {
            window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }

        squarePhysicsPosition = physics.square->GetPosition();
        squareGraphicsPosition.x = (squarePhysicsPosition.x - squareHalfWidth) * scalingFactor;
        squareGraphicsPosition.y = (squarePhysicsPosition.y + squareHalfWidth) * scalingFactor * -1.0f;

        graphics.squareShape.setPosition(squareGraphicsPosition);


        graphics.Render(window);

    }

    delete keyA_;
    delete keyD_;
    delete keyW_;
    delete keyS_;

    return 0;
}

void moveLeft(EventData* myPointer)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        physics.square->SetLinearVelocity(b2Vec2(-moveAmount,0.0f)); //Moves the square by the offset of -0.5 in the X axis from its current position
    }
}

void moveRight(EventData* myPointer)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        physics.square->SetLinearVelocity(b2Vec2(moveAmount, 0.0f)); //Moves the square by the offset of 0.5 in the X axis from its current position
    }
}

void moveUp(EventData* myPointer)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        physics.square->SetLinearVelocity(b2Vec2(0.0f, moveAmount)); //Moves the square by the offset of -0.5 in the Y axis from its current position
    }
}

void moveDown(EventData* myPointer)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        physics.square->SetLinearVelocity(b2Vec2(0.0f, -moveAmount)); //Moves the square by the offset of 0.5 in the Y axis from its current position
    }
}
*/

int main() {
   /*
   while (window.isOpen())
    {
        
        //graphics.Render(window);
        window.clear(sf::Color::Cyan);
        window.display();
    }
   */

   GameEngine* myGame = new GameEngine();
   bool running = true;

   while (running)
   {
       running = myGame->Update();
   }

   delete myGame;



    return 0;
}


