#include "score.h"
#include <QFont>

Score::Score(int score, QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    this->score = score;

    setDefaultTextColor(Qt::white);
    setFont(QFont("Comic Sans MS", 24));
    set(score);
}

void Score::increase(int value)
{
    score += value;
    if (score < 0)
    {
        score = 0;
    }
    setPlainText("счет: " + QString::number(score));
}

int Score::get()
{
    return score;
}

void Score::set(int score)
{
    setPlainText("счет: " + QString::number(score));
    this->score = score;
}
