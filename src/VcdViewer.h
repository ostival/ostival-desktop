/*
========================================
VCD Viewer
----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------
*/
#ifndef VCDVIEWER_H
#define VCDVIEWER_H

#include <QDialog>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QScrollBar>

class TimingDiagramWidget : public QGraphicsView{
    Q_OBJECT
public:
    explicit TimingDiagramWidget(QWidget *parent = nullptr);
    void drawDummyVcdData();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QGraphicsScene *scene;
    QPointF lastPanPoint;
    bool isPanning = false;
    void drawDigitalSignal(QGraphicsScene *s, int yOffset, int height, const QString &label, const QList<QPointF> &data);

};

class VcdViewer : public QDialog{
    Q_OBJECT
public:
    explicit VcdViewer(QWidget *parent = nullptr);

private:
    TimingDiagramWidget *diagramWidget;
};

#endif
