#include "Mechanics.h"

//This code is more random than std::rand() 
#include <chrono>
#include <random>
std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());    

void Ball::move(Player *p1, Player *p2) {
    x += (directionX ? 1 : -1);
    y += (directionY ? 1 : -1);

    if (y == 0 || y == SCREEN_HEIGHT - 10)
        directionY = !directionY;
}

void Ball::restart() {
    x = SCREEN_WIDTH / 2;
    y = SCREEN_HEIGHT / 2;
    directionX = rng() % 2;
    directionY = rng() % 2;
}

float Ball::getX() {
    return x;
}

float Ball::getY() {
    return y;
}

bool Ball::hitsWith(Player *p) {
    float playerLeft = p->getX();
    float playerRight = playerLeft + p->getW();
    float playerTop = p->getY();
    float playerBottom = playerTop + p->getH();

    float ballLeft = x;
    float ballRight = x + 10.0f;
    float ballTop = y;
    float ballBottom = y + 10.0f;

    if (ballRight < playerLeft || ballLeft > playerRight || 
        ballBottom < playerTop || ballTop > playerBottom) {
        return false;
    }

    directionX = !directionX;
    return true;
}

void Ball::checkIfPoint(Player &p1, Player &p2) {
    if (x == 0) {
        p2.setPoint();
        restart();
        return;
    }
    if (x + 10.f == SCREEN_WIDTH) {
        p1.setPoint();
        restart();
        return;
    }
}

Player::Player(bool isLeft) {
    height = 100.0f;
    width = 10.0f;
    x = isLeft ? 0 : SCREEN_WIDTH - 10.0f;
    y =  SCREEN_HEIGHT / 2 - height / 2;
    reset();
}

float Player::getX() {
    return x;
}

float Player::getY() {
    return y;
}

float Player::getH() {
    return height;
}

float Player::getW() {
    return width;
}

void Player::move(bool up) {
    y += (up ? 1 : -1);    
}

int Player::getScore() {
    return score;
}

void Player::setPoint() {
    score += 1;
}

void Player::reset() {
    score = 0;
}
