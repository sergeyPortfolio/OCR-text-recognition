#ifndef QIMAGEWIDGET_H
#define QIMAGEWIDGET_H
#include <QWidget>
#include <QPixmap>
#include <QMargins>
#include <QPainter>

class QImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QImageWidget(QWidget *parent = nullptr);
private:
    QRect imgRect;
    QImage m_originalImg;
    QImage m_areaImg;
    QString m_textFromImg;
    QString m_noImgMessage;
    int m_margin;
    QMargins m_qmargins;
    QColor m_backGroundColor;
    QPoint m_startPoint;
    QPoint m_endPoint;
    QPainter painter;
    bool m_pressOrRelese;
    QRect m_rectArea;
    QPoint m_textStart, m_textEnd;
    QRect m_textArea;
    double ratio;
    QRect actualImgRect();
    void updateMargins();
    void readText();

public:
    void GetArea();
    void SetImage(QImage pixmap);
    QImage GetPixmap(){return m_originalImg;}
    int GetMargin(){return m_margin;}

signals:
    void pixmapChanged();
    void marginChanged();
    void areaChanged();
    void imgTextChanged(QString str);

public slots:
    void openFile();

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

};

#endif // QIMAGEWIDGET_H
