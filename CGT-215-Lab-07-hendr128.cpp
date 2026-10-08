#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main()
{
    int windowX = 800;
    int windowY = 600;
    int wallSize = 20;

    // Create our window and world with gravity 0,1
    RenderWindow window(VideoMode(windowX, windowY), "Bounce");
    World world(Vector2f(0, 1));

    // Create the ball
    PhysicsCircle ball;
    ball.setCenter(Vector2f(windowX / 2, (windowY / 2) - 150));
    ball.setRadius(20);
    world.AddPhysicsBody(ball);
    ball.applyImpulse(Vector2f(0.3, 0.6));

    // Create the floor
    PhysicsRectangle floor;
    floor.setSize(Vector2f(windowX, wallSize));
    floor.setCenter(Vector2f(windowX / 2, windowY - (wallSize / 2)));
    floor.setStatic(true);
    world.AddPhysicsBody(floor);

    // Create the left wall
    PhysicsRectangle leftWall;
    leftWall.setSize(Vector2f(wallSize, windowY - (wallSize * 2)));
    leftWall.setCenter(Vector2f((wallSize / 2), windowY / 2));
    leftWall.setStatic(true);
    world.AddPhysicsBody(leftWall);

    // Create the right wall
    PhysicsRectangle rightWall;
    rightWall.setSize(Vector2f(wallSize, windowY - (wallSize * 2)));
    rightWall.setCenter(Vector2f(windowX - (wallSize / 2), windowY / 2));
    rightWall.setStatic(true);
    world.AddPhysicsBody(rightWall);

    // Create the ceiling
    PhysicsRectangle ceiling;
    ceiling.setSize(Vector2f(windowX, wallSize));
    ceiling.setCenter(Vector2f(windowX / 2, wallSize / 2));
    ceiling.setStatic(true);
    world.AddPhysicsBody(ceiling);

    // Create the center obstacle
    PhysicsRectangle obstacle;
    obstacle.setSize(Vector2f(100, 100));
    obstacle.setCenter(Vector2f(windowX / 2, windowY / 2));
    obstacle.setStatic(true);
    world.AddPhysicsBody(obstacle);

    // Print "thud" when the ball collides with a wall
    int thudCount(0);
    floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount++ << endl;
        };
    leftWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount++ << endl;
        };
    rightWall.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount++ << endl;
        };
    ceiling.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
        cout << "thud " << thudCount++ << endl;
        };

    // Print "bang" when the ball collides with the center obstacle
    int bangCount(0);
    obstacle.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
        cout << "bang " << bangCount++ << endl;
        if (bangCount == 3) exit(0);
        };

    Clock clock;
    Time lastTime(clock.getElapsedTime());
    while (true) {
        Time currentTime(clock.getElapsedTime());
        Time deltaTime(currentTime - lastTime);

        // Calculate ms since last frame
        int deltaTimeMS(deltaTime.asMilliseconds());
        if (deltaTimeMS > 0)
        {
            world.UpdatePhysics(deltaTimeMS);
            lastTime = currentTime;
        }

        // Draw the objects to the window
        window.clear(Color(0, 0, 0));
        window.draw(floor);
        window.draw(leftWall);
        window.draw(rightWall);
        window.draw(ceiling);
        window.draw(obstacle);
        window.draw(ball);
        window.display();
    }
}