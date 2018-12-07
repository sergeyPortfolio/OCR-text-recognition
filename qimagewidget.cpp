#include "qimagewidget.h"
#include <QMouseEvent>
#include <QtGui>
#include <QFileDialog>
#include <baseapi.h>
#include <allheaders.h>
#include <QMessageBox>

QImageWidget::QImageWidget(QWidget *parent) : QWidget(parent)
{
    m_noImgMessage = "No image";
    m_backGroundColor = Qt::white;
    m_margin = 4;
    connect(this, SIGNAL(marginChanged()), SLOT(repaint()));
    connect(this, SIGNAL(pixmapChanged()), SLOT(repaint()));
}

QRect QImageWidget::actualImgRect()
{
    imgRect = rect();
    imgRect.setSize(m_originalImg.size().scaled(size(), Qt::KeepAspectRatio));
    imgRect.moveCenter(rect().center());
    return imgRect;
}

void QImageWidget::updateMargins()
{
    ratio = (double)m_originalImg.height()/(double)m_originalImg.width();
    int hMargin = m_margin * ratio;
    int wMargin = m_margin;

    m_qmargins.setBottom(hMargin);
    m_qmargins.setTop(hMargin);
    m_qmargins.setLeft(wMargin);
    m_qmargins.setRight(wMargin);
}

void QImageWidget::readText()
{
     tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();

     if (api->Init(NULL, NULL) == 1){
         QMessageBox msgBox;
          msgBox.setText("tessdata not found");
          msgBox.show();
     }

     api->SetImage(m_areaImg.bits(),m_areaImg.width(),m_areaImg.height(),m_areaImg.depth()/8,m_areaImg.bytesPerLine());
     m_textFromImg = api->GetUTF8Text();
     api->End();
     emit imgTextChanged(m_textFromImg);

}

void QImageWidget::SetImage(QImage pixmap)
{
    m_originalImg = pixmap;
    updateMargins();
    emit pixmapChanged();
}

void QImageWidget::openFile()
{
     QString m_fileNamePicture = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                      "/home",
                                                      tr("Images (*.png)"));
     SetImage(QImage(m_fileNamePicture));
     emit pixmapChanged();
}

void QImageWidget::paintEvent(QPaintEvent *event)
{

    painter.begin(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();
    painter.setBackground(m_backGroundColor);
    painter.drawRect(rect());
    painter.restore();

    if(m_originalImg.isNull())
    {
        painter.drawText(rect(),Qt::AlignCenter, m_noImgMessage);
    }
    else
    {
        imgRect = actualImgRect();
        painter.drawImage(imgRect,m_originalImg);
    }
    if(m_pressOrRelese)
    {
        painter.setPen(Qt::red);
        painter.drawRect(m_rectArea);
    }
    painter.end();
}


void QImageWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_pressOrRelese = true;
        m_startPoint = event->pos();

    }
}

void QImageWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_endPoint = event->pos();
        m_pressOrRelese = false;
        m_areaImg = m_originalImg.copy(m_textArea);
        readText();
    }
}

void QImageWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->MouseMove)
    {
        m_endPoint = event->pos();
        GetArea();
        update();
    }
}

void QImageWidget::GetArea()
{
     double w = (double)m_originalImg.width()/(double)this->width();
     double h = (double)m_originalImg.height()/(double)this->height();

    if(m_startPoint.y() < m_endPoint.y() && m_startPoint.x() < m_endPoint.x())
     {
            m_rectArea.setCoords(m_startPoint.x(),
                                 m_startPoint.y(),
                                 m_endPoint.x(),
                                 m_endPoint.y());
            m_textArea.setCoords(m_startPoint.x()*w-m_qmargins.left(),
                                  m_startPoint.y()*h-m_qmargins.top(),
                                  m_endPoint.x()*w+m_qmargins.left(),
                                  m_endPoint.y()*h-m_qmargins.top());
    }
    else if(m_startPoint.y() > m_endPoint.y() && m_startPoint.x() < m_endPoint.x())
    {
            m_rectArea.setCoords(m_startPoint.x(),
                                 m_endPoint.y(),
                                 m_endPoint.x(),
                                 m_startPoint.y());

            m_textArea.setCoords(m_startPoint.x()*w-m_qmargins.left(),
                                  m_endPoint.y()*h-m_qmargins.top(),
                                  m_endPoint.x()*w+m_qmargins.left(),
                                  m_startPoint.y()*h-m_qmargins.top());
    }
    else if(m_startPoint.y() < m_endPoint.y() && m_startPoint.x() > m_endPoint.x())
    {
            m_rectArea.setCoords(m_endPoint.x(),
                                 m_startPoint.y(),
                                 m_startPoint.x(),
                                 m_endPoint.y());

            m_textArea.setCoords(m_endPoint.x()*w-m_qmargins.left(),
                                  m_startPoint.y()*h-m_qmargins.top(),
                                  m_startPoint.x()*w+m_qmargins.left(),
                                  m_endPoint.y()*h-m_qmargins.top());
    }
    else if(m_startPoint.y() > m_endPoint.y() && m_startPoint.x() > m_endPoint.x())
    {
            m_rectArea.setCoords(m_endPoint.x(),
                                 m_endPoint.y(),
                                 m_startPoint.x(),
                                 m_startPoint.y());

            m_rectArea.setCoords(m_endPoint.x()*w-m_qmargins.left(),
                                 m_endPoint.y()*h-m_qmargins.top(),
                                 m_startPoint.x()*w+m_qmargins.left(),
                                 m_startPoint.y()*h-m_qmargins.top());
    }
}



