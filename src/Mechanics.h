#ifndef MECHANICS_H 
#define MECHANICS_H

const float SCREEN_WIDTH  = 600;
const float SCREEN_HEIGHT = 400;

class Player {
public: 
    Player(bool isLeft);
    
    float getX();
    float getY();
    float getW();
    float getH();

    void move(bool up);
    int getScore();
    void setPoint();
    void reset();

private: 

    float x, y; // Leftmost upper corner
    float width, height;
    int score;
};

class Ball {
public:
    void move(Player *p1, Player *p2);    
    void restart();
    float getX();
    float getY();

    bool hitsWith(Player *p);    
    void checkIfPoint(Player &p1, Player &p2);

private:
    float x, y;
    bool directionX, directionY; // 0 incrementa 1 decremental                                 
}; 

#endif
