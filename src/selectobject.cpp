#include "selectobject.h"
void mouse( int event, int x, int y, int flags, void* param );
selectObject::selectObject()
{

}
string name = "Firset Image";
/*
 * 选择矩形目标
 */
int selectObject::get_regions(Mat frame,vector<Rect>& regions)
{

    params p;
    int i, x1, y1, x2, y2, w, h;

      /* use mouse callback to allow user to define object regions */
    p.win_name = name;
    frame.copyTo(p.orig_img);
    p.n = 0;
    namedWindow(name, 1 );
    imshow(name, frame );
    setMouseCallback(name, &mouse, &p );
    waitKey(0);
    for( i = 0; i < p.n; i++ )
    {
          x1 = MIN( p.loc1[i].x, p.loc2[i].x );
          x2 = MAX( p.loc1[i].x, p.loc2[i].x );
          y1 = MIN( p.loc1[i].y, p.loc2[i].y );
          y2 = MAX( p.loc1[i].y, p.loc2[i].y );
          w = x2 - x1;
          h = y2 - y1;

          /* ensure odd width and height */
          w = ( w % 2 )? w : w+1;
          h = ( h % 2 )? h : h+1;
		  regions.push_back(Rect(x1, y1, w, h));
    }
    return p.n;
}
void mouse( int event, int x, int y, int flags, void* param )
{
  params* p = (params*)param;
  Point* loc;
  int n;
  Mat tmp;
  static int pressed = false;

  /* on left button press, remember first corner of rectangle around object */
  if( event == CV_EVENT_LBUTTONDOWN )
  {
      n = p->n;
      if( n == MAX_OBJECTS )
        return;
      loc = p->loc1;
      loc[n].x = x;
      loc[n].y = y;
      pressed = true;
  }

  /* on left button up, finalize the rectangle and draw it in black */
  else if( event == CV_EVENT_LBUTTONUP )
  {
      n = p->n;
      if( n == MAX_OBJECTS )
        return;
      loc = p->loc2;
      loc[n].x = x;
      loc[n].y = y;

      rectangle( p->orig_img, p->loc1[n], loc[n], CV_RGB(0,0,0), 1, 8, 0 );
      imshow( p->win_name, p->orig_img );
      pressed = false;
      p->n++;
    }

  /* on mouse move with left button down, draw rectangle as defined in white */
  else if( event == CV_EVENT_MOUSEMOVE  &&  flags & CV_EVENT_FLAG_LBUTTON )
  {
      n = p->n;
      if( n == MAX_OBJECTS )
        return;
      p->orig_img.copyTo(tmp);
      loc = p->loc1;
      rectangle( tmp, loc[n], Point(x, y), CV_RGB(255,255,255), 1, 8, 0 );
      imshow( p->win_name, tmp );

      p->cur_img = tmp;
  }
}

