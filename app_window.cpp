
# include <iostream>
#include <math.h> //for mergesort
#include <climits> //for mergesort
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
	addMenuEntry ( "Merge Sort", o8 );
	addMenuEntry ( "Reset", o3 );
	addMenuEntry ( "NO DELAY", o4 );
	addMenuEntry ( "Delay 5.0ms per step", o5 );
	addMenuEntry ( "Delay 50.0ms per step", o6 );
	addMenuEntry ( "Delay 100.0ms per step", o7 );


	distance = 0.01; //distance between two Rect
	beginX = -0.995; //x coordinate of the first rect - starting coordinate

	initialize(100, lam1); //randomize 100 different heights

	//create vector of Rect based on vector of random height, lam1
	int i = 0;
	float temp_x = beginX;
	float temp_y = -0.5;
	float temp_width = 0.01; //width of each Rect
	while(i < lam1.size())
	{
		lam.add(temp_x, temp_y, temp_width, lam1[i], 0.2,0.2,0.2);
		temp_x += (temp_width + distance);
		i++;
	}
	cout << endl;

	Time = 5.0; //delay
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

	//Keyboard event
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

			case '.':
				cout << ". is pressed" << endl;
				change(lam.stash);
				break;

			case 13:
			case '1':
				cout << "Enter or 1 is pressed" << endl;
				quickSort(lam.stash, 0, lam.stash.size()-1);
				break;

			case '2':
				cout << "2 is pressed" << endl;
				merge(lam.stash, 0, lam.stash.size()-1);
				break;

			case 27: // Esc was pressed
				exit(1);
		}
		printVec(lam.stash);
	} 

	//Rightclick event
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
				
			case 8:
				cout << "Merge Sort" << endl;
				merge(lam.stash, 0, lam.stash.size()-1);
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


//quickSort
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
			stash[i]->x = beginX + (stash[i]->width + distance)*i;
			stash[j]->x = beginX + (stash[j]->width + distance)*j;

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
			stash[a]->r = 0.8;
			stash[a]->b = 0.2;
			stash[a]->g = 0.2;
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
			stash[a]->r = 0.8;
			stash[a]->b = 0.2;
			stash[a]->g = 0.2;
			stash[a]->select = false;
			a++;
		}
		draw();
	}

	a = left;
	while(a <= right)
	{
		stash[a]->r = 0.8;
		stash[a]->b = 0.2;
		stash[a]->g = 0.2;
		stash[a]->select = false;
		a++;
	}
	draw();
}

//mergeSort
void AppWindow::mergeSort(vector<Rect* > &A, int p, int q, int r)
{
	int veryBIG = INT_MAX;

	int i = p;
	int j = q+1;

	float L[1000]; //i
	float R[1000]; //j

	int a = 0;
	while(i <= q)
	{
		L[a] = A[i]->height;
		i++;
		a++;
	}
	L[a] = veryBIG;

	a = 0;
	while(j <= r)
	{
		R[a] = A[j]->height;
		j++;
		a++;
	}
	R[a] = veryBIG;

	i = 0;
	j = 0;
	for(int k = p; k <= r; k++)
	{
		if(R[j] <= L[i])
		{
			if(R[j] == veryBIG) break;

			A[k]->r = 0;
			A[k]->b = 1;
			A[k]->g = 0;
			draw();
			wait(Time);

			A[k]->height = R[j];

			A[k]->r = 0;
			A[k]->b = 0;
			A[k]->g = 1;
			draw();
			wait(Time);

			A[k]->r = 1;
			A[k]->b = 1;
			A[k]->g = 1;
			draw();

			j++;
		}
		else
		{
			A[k]->r = 0;
			A[k]->b = 1;
			A[k]->g = 0;
			draw();
			wait(Time);

			A[k]->height = L[i];

			A[k]->r = 0;
			A[k]->b = 0;
			A[k]->g = 1;
			draw();
			wait(Time);

			A[k]->r = 1;
			A[k]->b = 1;
			A[k]->g = 1;
			draw();
			wait(Time);

			i++;
		}
	}

	for(int k = p; k <= r; k++)
	{
		A[k]->r = 0.8;
		A[k]->b = 0.2;
		A[k]->g = 0.2;
		draw();
		wait(Time);
	}
}

void AppWindow::merge(vector<Rect* > &A, int i, int j)
{
	if(i < j)
	{
		int q = floor((i+j)/2);
		merge(A,i,q);
		merge(A,q+1,j);
		mergeSort(A,i,q,j);
	}
}

//reset
void AppWindow::reset(vector<Rect*> &stash)
{
	stash.clear();
	int i = 0;
	float temp_x = beginX;
	float temp_y = -0.5;
	float temp_width = 0.01;
	while(i < lam1.size())
	{
		lam.add(temp_x, temp_y, temp_width, lam1[i], 0.2,0.2,0.2);
		temp_x += (temp_width + distance);
		i++;
	}
	cout << endl;
	draw();
}

void AppWindow::change(vector<Rect*> &stash)
{
	stash.clear();
	lam1.clear();
	initialize(100, lam1); //randomize 100 different heights

	int i = 0;
	float temp_x = beginX;
	float temp_y = -0.5;
	float temp_width = 0.01;
	while(i < lam1.size())
	{
		lam.add(temp_x, temp_y, temp_width, lam1[i], 0.2,0.2,0.2);
		temp_x += (temp_width + distance);
		i++;
	}
	cout << endl;
	draw();
}
