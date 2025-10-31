/*
================================
Logic to draw schematic
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/


#ifndef DRAWSCHEMATIC_H
#define DRAWSCHEMATIC_H



#include <QWidget>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <QPoint>

class DrawSchematic : public QWidget
{
    Q_OBJECT

public:
    explicit DrawSchematic(QWidget *parent = nullptr);
    ~DrawSchematic();

protected:
    void paintEvent(QPaintEvent *event) override;           // to draw custom shapes

    void drawAND(QPainter &painter, double x, double y, double scale);
    void drawOR(QPainter &painter, double x, double y, double scale);
    void drawNOT(QPainter &painter, double x, double y, double scale);

    void drawNAND(QPainter &painter, double x, double y, double scale);
    void drawNOR(QPainter &painter, double x, double y, double scale);

    void drawXOR(QPainter &painter, double x, double y, double scale);
    void drawXNOR(QPainter &painter, double x, double y, double scale);
};


#endif