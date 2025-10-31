/*
================================
Logic to draw schematic
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include "DrawSchematic.h"

DrawSchematic::DrawSchematic(QWidget *parent) : QWidget(parent){
    setWindowTitle("Ostival Schematic Window");
    resize(600, 400); 
}

DrawSchematic::~DrawSchematic(){
    qDebug("DrawSchematic destroyed");
}

void DrawSchematic::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::darkBlue);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(20, 30, "Welcome to the Ostival Schematic Viewer");

    drawAND(painter,50,50,0.5);
    drawOR(painter,125,50,0.5);
    drawNOT(painter,200,50,0.5);
    drawNAND(painter,250,50,0.5);
    drawNOR(painter,50,200,0.5);
    drawXOR(painter,100,200,0.5);
    drawXNOR(painter,150,200,0.5);

    QWidget::paintEvent(event);
}

void DrawSchematic::drawAND(QPainter &painter, double x, double y, double scale){
    painter.save();
    painter.translate(x, y);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    double gateWidth = 80 * scale;
    double gateHeight = 60 * scale;

    // Need rectagle and semicircle
    QRect rectPart(x, y, gateWidth / 2, gateHeight);
    QRect arcBoundingRect(x + gateWidth / 2 - gateHeight / 2, y, gateHeight, gateHeight);

    // AND gate body
    QPainterPath path;

    QPoint topLeft = rectPart.topLeft();
    QPoint topRight = rectPart.topRight();
    QPoint bottomLeft = rectPart.bottomLeft();
    QPoint bottomRight = rectPart.bottomRight();

    path.moveTo(bottomLeft);
    path.lineTo(topLeft);
    path.lineTo(topRight);
    path.arcTo(arcBoundingRect, 90.0, -180.0); 
    path.lineTo(bottomLeft);
    painter.drawPath(path);

    int bubbleRadius = 8;
    int bubbleX = x + gateWidth - 7;

    // input input output connections
    painter.drawLine(x - 30, y + gateHeight / 4, x, y + gateHeight / 4);
    painter.drawLine(x - 30, y + (3 * gateHeight / 4), x, y + (3 * gateHeight / 4));
    painter.drawLine(x + gateWidth, y + gateHeight / 2, x + gateWidth + 30, y + gateHeight / 2);

    painter.restore();
}

void DrawSchematic::drawOR(QPainter &painter, double x, double y, double scale){
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    double width = 80 * scale;
    double height = 60 * scale;

    QRectF rectangle(x, y, width, height);
    painter.drawRect(rectangle);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10 * scale, QFont::Bold));
    painter.drawText(rectangle, Qt::AlignCenter, "OR");

    painter.restore();
}

void DrawSchematic::drawNOT(QPainter &painter, double x, double y, double scale){
    painter.save();
    painter.translate(x, y);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    double gateWidth = 80 * scale;
    double gateHeight = 60 * scale;

    QPoint p1(x, y);
    QPoint p2(x + gateWidth, y + gateHeight/2);
    QPoint p3(x, y + gateHeight);

    painter.drawLine(p1, p2);
    painter.drawLine(p2, p3);
    painter.drawLine(p3, p1);

    // Not Bubble
    int bubbleRadius = 8;
    int bubbleX = x + gateWidth - 7;
    int bubbleY = y + gateHeight / 2 - bubbleRadius;
    painter.drawEllipse(bubbleX, bubbleY, bubbleRadius * 2, bubbleRadius * 2);

    // Input Output
    painter.drawLine(x - 30, y + gateHeight / 2, x, y + gateHeight / 2);
    painter.drawLine(bubbleX + bubbleRadius * 2, y + gateHeight / 2, bubbleX + bubbleRadius * 2 + 30, y + gateHeight / 2);

    painter.restore();
}

void DrawSchematic::drawNAND(QPainter &painter, double x, double y, double scale){
    painter.save();
    painter.translate(x, y);

    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    double gateWidth = 80 * scale;
    double gateHeight = 60 * scale;

    // Need rectagle and semicircle
    QRect rectPart(x, y, gateWidth / 2, gateHeight);
    QRect arcBoundingRect(x + gateWidth / 2 - gateHeight / 2, y, gateHeight, gateHeight);

    // NAND gate body
    QPainterPath path;

    QPoint topLeft = rectPart.topLeft();
    QPoint topRight = rectPart.topRight();
    QPoint bottomLeft = rectPart.bottomLeft();
    QPoint bottomRight = rectPart.bottomRight();

    path.moveTo(bottomLeft);
    path.lineTo(topLeft);
    path.lineTo(topRight);
    path.arcTo(arcBoundingRect, 90.0, -180.0); 
    path.lineTo(bottomLeft);
    painter.drawPath(path);

    // Inversion bubble in NAND gate
    int bubbleRadius = 8;
    int bubbleX = x + gateWidth - 7;
    int bubbleY = y + gateHeight / 2 - bubbleRadius;
    painter.drawEllipse(bubbleX, bubbleY, bubbleRadius * 2, bubbleRadius * 2);

    // input input output connections
    painter.drawLine(x - 30, y + gateHeight / 4, x, y + gateHeight / 4);
    painter.drawLine(x - 30, y + (3 * gateHeight / 4), x, y + (3 * gateHeight / 4));
    painter.drawLine(bubbleX + bubbleRadius * 2, y + gateHeight / 2, bubbleX + bubbleRadius * 2 + 30, y + gateHeight / 2);

    painter.restore();
}

void DrawSchematic::drawNOR(QPainter &painter, double x, double y, double scale){
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    double width = 80 * scale;
    double height = 60 * scale;

    QRectF rectangle(x, y, width, height);
    painter.drawRect(rectangle);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10 * scale, QFont::Bold));
    painter.drawText(rectangle, Qt::AlignCenter, "NOR");

    painter.restore();
}

void DrawSchematic::drawXOR(QPainter &painter, double x, double y, double scale){
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    double width = 80 * scale;
    double height = 60 * scale;

    QRectF rectangle(x, y, width, height);
    painter.drawRect(rectangle);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10 * scale, QFont::Bold));
    painter.drawText(rectangle, Qt::AlignCenter, "XOR");

    painter.restore();
}

void DrawSchematic::drawXNOR(QPainter &painter, double x, double y, double scale){
    painter.save();
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(Qt::cyan);

    double width = 80 * scale;
    double height = 60 * scale;

    QRectF rectangle(x, y, width, height);
    painter.drawRect(rectangle);

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 10 * scale, QFont::Bold));
    painter.drawText(rectangle, Qt::AlignCenter, "XNOR");

    painter.restore();
}