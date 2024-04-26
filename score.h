#ifndef SCORE_H
#define SCORE_H

#include <QGraphicsTextItem>

class Score : public QGraphicsTextItem
{
public:
    Score(int score, QGraphicsItem *parent = nullptr);

    void increase(int value);

    int get();
    void set(int score);

private:
    int score;
};

#endif // SCORE_H
