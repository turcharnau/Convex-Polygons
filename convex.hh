#ifndef convex_hh
#define convex_hh

#include "Point.hh"
#include <vector>

/** The Polygon class stores some two dimensional points in the plane
    and provides some usefull operations for it.
*/

struct Color{
	double r,g,b;
};

class Polygon{

	public:
		// Constructor: Defaults is the empty polygon (no vertices). //
		Polygon (const std::vector<Point>& v={}, const Color& rgb ={0.0,0.0,0.0});

		// Returns the area of the polygon. //
		double area () const;

		// Returns the perimeter of the polygon. //
		double perimeter () const;

		// Returns the number of vertices of the polygon. //
		int vertices () const;

		// Returns the centroid of the polygon. //
		Point centroid () const;

		// Sets the color of the polygon. //
		// Precondition: R,G,B values goes to 0 to 1. //
		void setcol (double R, double G, double B);

		// Returns the intersection of this polygon with another polygon. //
		Polygon& operator*= (const Polygon& p);

		Polygon operator* (const Polygon& p) const;

		// Returns the union of this polygon with another polygon. //
		Polygon& operator+= (const Polygon& p);

		Polygon operator+ (const Polygon& p) const;

		// Prints yes or not to tell whether the first is inside the second or not. //
		bool inside (const Polygon& p) const;

		// Indicates if a point is inside a polygon //
		bool dins (const Point& p) const;

		// Creates a new polygon with the four vertices corresponding to the bounding box of the given polygons. //
		Polygon bbox () const;

		// Returns the vector of points of the polygon //
		std::vector<Point> get_v () const;

		// Gets the value of the red color //
		double get_r () const;

		// Gets the value of the red color //
		double get_g () const;

		// Gets the value of the red color //
		double get_b () const;

		// Gets the structure of the rgb //
		Color get_rgb () const;

	private:

		//All the vertices will be saved in a array of points (x,y) implemented in "Point.hh"//
		std::vector<Point> v;

		Color rgb;

		void convexHull();

};

#endif