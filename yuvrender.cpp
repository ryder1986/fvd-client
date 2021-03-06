#include "yuvrender.h"
//#include "common_routine.h"
//#include "g_define.h"
     QPoint pt[16];
     QPoint pt_rear[16];
  QPoint p1;
  QPoint p2;
  QPoint p3;

YuvRender::YuvRender(QWidget *parent) :
    QGLWidget(parent),video_width(VIDEO_WIDTH),video_height(VIDEO_HEIGHT),pressed_x(0),pressed_y(0)
{
}
void YuvRender::set_buf(char *buffer)
{
    memcpy(yuv_buf,buffer,VIDEO_WIDTH*VIDEO_HEIGHT*3/2);
}

void YuvRender::initializeGL()
{

}

void YuvRender::resizeGL(int w, int h)
{

}
static int flg=0;

void YuvRender::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.beginNativePainting();
    makeCurrent();
    CONVERT_YUV420PtoRGB24((unsigned char *)yuv_buf,(unsigned char *)rgb_buf,video_width,video_height);
    glPixelZoom(1.0f*this->width()/video_width, 1.0f*this->height()/video_height);
#if 0
    glDrawPixels(video_width, video_height,GL_RGB, GL_UNSIGNED_BYTE, rgb_buf);
#else
   // QImage img((uchar *)rgb_buf,video_width,video_height,QImage::Format_RGB888);
    QImage img((uchar *)rgb_buf,video_width,video_height,QImage::Format_RGB888);
    painter.drawImage(QRect(0,0,this->width(),this->height()),img);
#endif
    painter.endNativePainting();
    QBrush red_brush_trans(QColor(0,0,200,100));
    painter.setBrush(red_brush_trans);
   // pressed_x=0;
   // pressed_y=0;
//  if(flg++>10)


    painter.drawEllipse(pressed_x,pressed_y,100,100);
    QPen testpen(red_brush_trans,10);
   painter.setPen(testpen);

  for(int i=0;i<8;i++){
      painter.drawLine(pt[i*2],pt[i*2+1]);
 }


  for(int i=0;i<8;i++){
      painter.drawLine(pt[i*2],pt[i*2+1]);
 }

  for(int i=0;i<8;i++){
      painter.drawLine(pt_rear[i*2],pt_rear[i*2+1]);
 }
  painter.drawEllipse(p1,10,10);
  painter.drawEllipse(p2,10,10);
  painter.drawEllipse(p3,10,10);
   }
