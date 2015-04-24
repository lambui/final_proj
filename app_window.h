
// Ensure the header file is included only once in multi-file projects
#ifndef APP_WINDOW_H
#define APP_WINDOW_H

#include <vector>
# include "glut_window.h"
#include "RectStash.h"

// The functionality of your application should be implemented inside AppWindow
class AppWindow : public GlutWindow
 { private :
    enum MenuEv { o0, o1, o2, o3,  o4, o5, o6, o7, o8};
    float _markx, _marky;
    float offsetx, offsety;
    int _w, _h;

    float Time;
    float distance;
    float beginX;
    vector<float> lam1;
    StashRect lam;

   public :
    AppWindow ( const char* label, int x, int y, int w, int h );
    void windowToScene ( float& x, float &y );

   private : // functions derived from the base class
    virtual void handle ( const Event& e );
    virtual void draw();
    virtual void resize ( int w, int h );

    //quickSort
    void quickSort(vector<Rect*> &stash, int left, int right);

    //mergeSort
    void merge(vector<Rect*> &stash, int i, int j);
    void mergeSort(vector<Rect*> &stash, int p, int q, int r);

    //reset: reset back to unsorted vector (same set of data)
    void reset(vector<Rect*> &stash);

    //change: change data set
    void change(vector<Rect*> &stash);
 };

#endif // APP_WINDOW_H
