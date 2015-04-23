#ifndef RectStash_h
#define RectStash_h

#include <iostream>
#include <vector>

using namespace std;

class Vec
{
	public:
		float x,y;
		static Vec null;
		Vec()
		{
			x= 0.0f;
			y= 0.0f; 
		}
		Vec(float x, float y)
		{
			this->x = x;
			this->y = y;
		}


		void add(Vec u)
		{
			this->x += u.x;
			this->y += u.y;
		}

		void print()
		{
			std::cout << "(" << x << ", " << y << ")" << std::endl;
		}

};

class Rect
{
	public:
		float x, y, width, height;
		float r,g,b;
		bool select;
		Rect()
		{
			x= 0.0f;
			y= 0.0f; 
			width= 0.0f; 
			height= 0.0f;
			r = 0.0f;
			g = 0.0f;
			b = 0.0f;
			select = false;
		}
		Rect(float x, float y, float width, float height, float r, float g, float b)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
			this->r = r;
			this->g = g;
			this->b = b;
			select = false;
		}

		bool contains(Vec a)
		{
			if
			(
					a.x >= x 
				&&	a.x <= (x + width) 
				&&	a.y >= (y - height) 
				&&	a.y <= y
			) 	return true;

			else return false;
		}

		void draw()
		{
			//draw box
			glBegin(GL_POLYGON);
			glColor3f(r,g,b);
			glVertex2d(x,         y);
			glVertex2d(x + width, y);
	        glVertex2d(x + width, y + height);
	        glVertex2d(x,         y + height);
	        glEnd();
	        
	        //draw selected outline (thicker than thin border)
	        if(select)
	        {
	        	glLineWidth(5);
		        glBegin(GL_LINES);
		       	//glColor3f(1,1,1); 												//selected outline is white
		        glColor3f(1, 1, 1); //selected outline is same but a little bit darker
		        glVertex2d(x,         y);
		        glVertex2d(x + width, y);
		        glVertex2d(x + width, y);
		        glVertex2d(x + width, y + height);
		        glVertex2d(x + width, y + height);
		        glVertex2d(x,         y + height);
		        glVertex2d(x,         y + height);
		        glVertex2d(x,         y);
		        glEnd();

		        glBegin(GL_LINES);
				glColor3f ( 1, 1, 1);
				glVertex2d ( -1, height + y);
				glVertex2d ( 1, height + y);
				glEnd();
	        }
		}

		void print()
		{
			std::cout << "(" << x << ", " << y << ")" << std::endl;
		}

};

class StashRect
{
	public:
		vector<Rect*> stash;

		StashRect(){}
		StashRect(float x, float y, float width, float height, float r, float g, float b)
		{
			stash.push_back(new Rect(x,y,width,height,r,g,b));
		}

		~StashRect()
		{
			stash.clear();
		}

		void add(float x, float y, float width, float height, float r, float g, float b)
		{
			stash.push_back(new Rect(x,y,width,height,r,g,b));
		}

		int search(float x, float y)
		{
			Vec point(x,y);
			int i= 0;
			while(i < stash.size())
			{
				if(stash[i]->contains(point)) 	return i;
				i++;
			}
			return -1;
		}
};

#endif