/*
================================
Logic to draw schematic
--------------------------------
Coded by:
Team Ostival (hello@ostival.org)
---------------------------------
*/

#include "DrawSchematic.h"



DrawSchematic::DrawSchematic(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Ostival Schematic Window");
    resize(400, 300); 
}

void DrawSchematic::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setPen(Qt::darkBlue);
    painter.setFont(QFont("Arial", 16, QFont::Bold));
    painter.drawText(20, 30, "Welcome to the Ostival Schematic Viewer");

    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);
    painter.setBrush(Qt::white);

    int gateWidth = 100;
    int gateHeight = 80;
    int x = (width() - gateWidth) / 2;
    int y = (height() - gateHeight) / 2;
    
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
    painter.drawPath(path);

    // Inversion bubble in NAND gate
    int bubbleRadius = 8;
    int bubbleX = x + gateWidth - 7;
    int bubbleY = y + gateHeight / 2 - bubbleRadius;
    painter.drawEllipse(bubbleX, bubbleY, bubbleRadius * 2, bubbleRadius * 2);

    // input input output lines
    pen.setWidth(1);
    
    painter.setPen(pen);
    painter.drawLine(x - 30, y + gateHeight / 4, x, y + gateHeight / 4);
    painter.drawLine(x - 30, y + (3 * gateHeight / 4), x, y + (3 * gateHeight / 4));
    painter.drawLine(bubbleX + bubbleRadius * 2, y + gateHeight / 2, bubbleX + bubbleRadius * 2 + 30, y + gateHeight / 2);

    QWidget::paintEvent(event);
}