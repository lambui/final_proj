
# include <iostream>
#include <unistd.h> //for sleep()
# include "app_window.h"
#include "quick.h"

AppWindow::AppWindow ( const char* label, int x, int y, int w, int h )
          :GlutWindow ( label, x, y, w, h )
 {
   _markx = 0;
   _marky = 0;
   offsetx = 0;
   offsety = 0;
   addMenuEntry ( "Quick Sort", o0 );
   addMenuEntry ( "Insertion Sort", o1 );
   addMenuEntry ( "Heap Sort", o2 );
   addMenuEntry ( "Reset", o3 );
   addMenuEntry ( "NO DELAY", o4 );
   addMenuEntry ( "Delay 5.0ms per step", o5 );
   addMenuEntry ( "Delay 50.0ms per step", o6 );
   addMenuEntry ( "Delay 100.0ms per step", o7 );


   initialize(66, lam1);

   int i = 0;
   float temp_x = -0.99;
   float temp_y = -0.5;
   float temp_width = 0.02;
   while(i < lam1.size())
   {
      lam.add(temp_x, temp_y, temp_width, lam1[i], 0.2,0.2,0.2);
      temp_x += (temp_width + 0.01);
      i++;
   }
   cout << endl;
    Time = 5.0;
 }

// mouse events are in window coordinates, but your scene is in [0,1]x[0,1],
// so make here the conversion when needed
void AppWindow::windowToScene ( float& x, float &y )
 {
   x = (2.0f*(x/float(_w))) - 1.0f;
   y = 1.0f - (2.0f*(y/float(_h)));
 }

// Called every time there is a window event
void AppWindow::handle ( const Event& e )
 {
   bool rd=true;

   if ( e.type==Keyboard )
   {
      switch ( e.key )
      { 
        case ' ': // space bar
  	   std::cout << "Space pressed.\n";
         _markx = 1.5;
         _marky = 1.5;
         redraw();
  	   break;

       case '0':
        cout << "0 is pressed" << endl;
        reset(lam.stash);
        break;

       case 13:
       case '1':
        cout << "Enter or 1 is pressed" << endl;
        quickSort(lam.stash, 0, lam.stash.size()-1);
        break;

        case 27: // Esc was pressed
         exit(1);
     }
      printVec(lam.stash);
   } 

   if( e.type==Menu )
   { 
      switch(e.menuev)
      {
        case 0:
          cout << "Quick Sort" << endl;
          quickSort(lam.stash, 0, lam.stash.size()-1);
          break;
        case 1:
          cout << "Insertion Sort" << endl;
          break;
        case 2:
          cout << "Heap Sort" << endl;
          break;
        case 3:
          cout << "Reset" << endl;
          reset(lam.stash);
          break;
        case 4:
          cout << "NO DELAY" << endl;
          Time = 0.0;
          break;
        case 5:
          cout << "Delay 5.0ms per step" << endl;
          Time = 5.0;
          break;
        case 6:
          cout << "Delay 50.0ms per step" << endl;
          Time = 50.0;
          break;
        case 7:
          cout << "Delay 100.0ms per step" << endl;
          Time = 100.0;
          break;
      }
      printVec(lam.stash);
      rd=true; // no need to redraw
    }

   if (rd) redraw(); // ask the window to be rendered when possible
}

void AppWindow::resize ( int w, int h )
 {
   // Define that OpenGL should use the whole window for rendering
   glViewport( 0, 0, w, h );
   _w=w; _h=h;
 }

 // here we will redraw the scene according to the current state of the application.
void AppWindow::draw() //set custom to smaller than -1 if dont want to use
 {
   // Clear the rendering window
   glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

   // Clear the trasnformation stack
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity();

   // Set drawing color to yellow
   glColor3d ( 1.0, 0.9, 0.3);    

   int i = 0;
   while(i < lam.stash.size())
   {
      lam.stash[i]->draw();
      i++;
   }

   // Swap buffers
   glFlush();         // flush the pipeline (usually not necessary)
   glutSwapBuffers(); // we were drawing to the back buffer, now bring it to the front
}

void AppWindow::quickSort(vector<Rect*> &stash, int left, int right)
{
  int mid = floor(((right-left)-1)/2);
  mid += left;

  float pivot = stash[mid]->height;
  stash[mid]->select = true;
  draw();

  int i = left;
  int j = right;


  while(i < j)
  {
    stash[i]->r = 0;
    stash[i]->b = 1;
    stash[i]->g = 0;

    stash[j]->r = 0;
    stash[j]->b = 1;
    stash[j]->g = 0;
    draw();
    wait(Time);
    
    while(stash[i]->height < pivot)
    {
      stash[i]->r = 0.2;
      stash[i]->b = 0.2;
      stash[i]->g = 0.2;
      draw();
      wait(Time);
      i++;

      stash[i]->r = 0;
      stash[i]->b = 1;
      stash[i]->g = 0;
      draw();
      wait(Time);
    }
    while(stash[j]->height > pivot)
    {
      stash[j]->r = 0.2;
      stash[j]->b = 0.2;
      stash[j]->g = 0.2;
      draw();
      wait(Time);
      j--;

      stash[j]->r = 0;
      stash[j]->b = 1;
      stash[j]->g = 0;
      draw();
      wait(Time);
    }

    if(i <= j)
    {
      stash[i]->r = 1;
      stash[i]->b = 1;
      stash[i]->g = 0;

      stash[j]->r = 1;
      stash[j]->b = 1;
      stash[j]->g = 0;
      draw();
      wait(Time);

      stash[i]->r = 0.2;
      stash[i]->b = 0.2;
      stash[i]->g = 0.2;

      stash[j]->r = 0.2;
      stash[j]->b = 0.2;
      stash[j]->g = 0.2;
      swap(stash[i],stash[j]);
      stash[i]->x = -0.99 + (stash[i]->width + 0.01)*i;
      stash[j]->x = -0.99 + (stash[j]->width + 0.01)*j;

      draw();
      wait(Time);

      i++;
      j--;
    }
    
    stash[i-1]->r = 0.2;
    stash[i-1]->b = 0.2;
    stash[i-1]->g = 0.2;

    stash[j+1]->r = 0.2;
    stash[j+1]->b = 0.2;
    stash[j+1]->g = 0.2;
    draw();
  }


  int a = 0;
  while(a < stash.size())
  {
    stash[a]->select=false;
    a++;
  }
  wait(Time);
  draw();

  if(left < j)
  {
    quickSort(stash, left, j);

    a = left;
    while(a <= j)
    {
      stash[a]->r = 1;
      stash[a]->b = 0;
      stash[a]->g = 1;
      stash[a]->select = false;
      a++;
    }
    draw();
  }
  if(i < right)
  {
    quickSort(stash, i, right);

    a = i;
    while(a <= right)
    {
      stash[a]->r = 1;
      stash[a]->b = 0;
      stash[a]->g = 1;
      stash[a]->select = false;
      a++;
    }
    draw();
  }

  a = left;
  while(a <= right)
  {
    stash[a]->r = 1;
    stash[a]->b = 0;
    stash[a]->g = 1;
    stash[a]->select = false;
    a++;
  }
  draw();
}

void AppWindow::reset(vector<Rect*> &stash)
{
  stash.clear();
  int i = 0;
   float temp_x = -0.99;
   float temp_y = -0.5;
   float temp_width = 0.02;
   while(i < lam1.size())
   {
      lam.add(temp_x, temp_y, temp_width, lam1[i], 0.2,0.2,0.2);
      temp_x += (temp_width + 0.01);
      i++;
   }
   cout << endl;
   draw();

}
