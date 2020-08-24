#ifndef Point_hh
#define Point_hh


/** The Point class stores a two dimensional point in the plane
    and provides some usefull operations for it.
*/

const double E = 1e-12;

class Point {

public:

    /** Constructor. */
    Point (double x_coord=0, double y_coord=0);

    /** Gets the x coordinate of this point. */
    double get_x () const;

    /** Gets the y coordinate of this point. */
    double get_y () const;

    /** Returns the distance to point p from this point. */
    double distance (const Point& p) const;

    /** Compares this point to point p. */
    bool operator== (const Point& p) const;

    /** Compares this point to point p. */
    bool operator!= (const Point& p) const;

    /** Adds the coordinates of p to this point and returns this point. */
    Point& operator+= (const Point& p);

    /** Returns the point resulting of adding the coordinates of this point and p. */
    Point operator+ (const Point& p) const;

    /** Substracts the coordinates of p to this point and returns this point. */
    Point& operator-= (const Point& p);

    /** Returns the point resulting of substracting the coordinates of this point and p. */
    Point operator- (const Point& p) const;

    //Says if a point it's in the left part respect two other points//
    bool leftof(const Point& p1, const Point& p) const;

    bool strict_leftof(const Point& p1, const Point& p) const;

    //If three points are allineated //
    bool in_line(const Point& p1, const Point& p) const;

    double slope (const Point& p) const;

private:

    /** Coordinates of the point. */
    double x, y;

};


#endif
