/*
========================================
VCD Viewer
----------------------------------------
Coded by:
Team Ostival (hello@ostival.org)
----------------------------------------
*/
#include <QGraphicsRectItem>
#include <QGraphicsTextItem>
#include <QMouseEvent>
#include <cmath>
#include <QRandomGenerator>
#include "VcdViewer.h"

VcdViewer::VcdViewer(QWidget *parent): QDialog(parent){
    setWindowTitle("Ostival VCD Viewer");
    setMinimumSize(1000, 600);

    diagramWidget = new TimingDiagramWidget(this);
    diagramWidget->drawDummyVcdData();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(diagramWidget);
    setLayout(mainLayout);
}

TimingDiagramWidget::TimingDiagramWidget(QWidget *parent): QGraphicsView(parent),scene(new QGraphicsScene(this)){
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
    setOptimizationFlag(QGraphicsView::DontAdjustForAntialiasing, true);
    setOptimizationFlag(QGraphicsView::DontSavePainterState, true);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setStyleSheet("border: 1px solid #333; background-color: #1E1E1E;");
}

void TimingDiagramWidget::drawDummyVcdData(){
    scene->clear();
    const int timeRange = 5000;
    const int numSignals = 25;
    const int signalHeight = 100;
    const int yStart = 50;

    scene->setSceneRect(-50, 0, timeRange + 100, (numSignals * signalHeight) + yStart + 50);

    QPen timePen(QColor("#555555"), 0.5);
    for (int t = 0; t <= timeRange; t += 500) { 
        scene->addLine(t, 0, t, scene->height(), timePen);
        QGraphicsTextItem *timeLabel = scene->addText(QString::number(t) + " ns");
        timeLabel->setPos(t, scene->height() - 30);
        timeLabel->setDefaultTextColor(QColor("#AAAAAA"));
    }

    for (int i = 0; i < numSignals; ++i) {
        int yOffset = yStart + (i * signalHeight);
        QString label = QString("Signal_%1").arg(i);

        QList<QPointF> data;
        bool state = false;

        for (int t = 0; t <= timeRange; t += 10) { 
            if (QRandomGenerator::global()->bounded(100) < 5) {
                state = !state;
            }
            data << QPointF(t, state ? 1.0 : 0.0);
        }
        drawDigitalSignal(scene, yOffset, signalHeight, label, data);
    }

    fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding); 

    const QRectF rect = scene->sceneRect();
    centerOn(rect.left(), rect.center().y());
}

void TimingDiagramWidget::drawDigitalSignal(QGraphicsScene *s, int yOffset, int height, const QString &label, const QList<QPointF> &data){
    QGraphicsTextItem *text = s->addText(label);
    text->setPos(-40, yOffset + height / 3);
    text->setDefaultTextColor(QColor("#F8F8F2"));

    QPen boundaryPen(QColor("#444444"), 1);
    s->addLine(data.first().x(), yOffset, data.last().x(), yOffset, boundaryPen);

    QPen signalPen(QColor("#00FFFF"), 2);
    QPainterPath path;

    if (!data.isEmpty()) {
        double startY = yOffset + height - (data.first().y() * (height * 0.7));
        path.moveTo(data.first().x(), startY);
        for (int i = 1; i < data.size(); ++i) {
            QPointF p1 = data[i-1];
            QPointF p2 = data[i];
            double y1 = yOffset + height - (p1.y() * (height * 0.7));
            double y2 = yOffset + height - (p2.y() * (height * 0.7));
            if (y1 != y2) {
                path.lineTo(p2.x(), y1);
                path.lineTo(p2.x(), y2);
            } else {
                path.lineTo(p2.x(), y2);
            }
        }
    }
    s->addPath(path, signalPen);
}


void TimingDiagramWidget::wheelEvent(QWheelEvent *event){
    const double scaleFactor = 1.15;
    if (event->angleDelta().y() > 0) {
        scale(scaleFactor, scaleFactor);
    } else {
        scale(1.0 / scaleFactor, 1.0 / scaleFactor);
    }
}

void TimingDiagramWidget::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        isPanning = true;
        lastPanPoint = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
    } else {
        QGraphicsView::mousePressEvent(event);
    }
}

void TimingDiagramWidget::mouseMoveEvent(QMouseEvent *event){
    if (isPanning) {
        QPointF delta = mapToScene(event->pos()) - mapToScene(lastPanPoint.toPoint());
        translate(-delta.x(), 0); 
        lastPanPoint = event->pos();
        event->accept();
    } else {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void TimingDiagramWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && isPanning) {
        isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
    } else {
        QGraphicsView::mouseReleaseEvent(event);
    }
}
