#include "convex.hh"
#include "Point.hh"
#include <algorithm>
#include <cassert>
#include <vector>
using namespace std;


//*************************************************************************************************************//

	// Constructor //
	Polygon::Polygon(const vector<Point>& v, const Color& rgb)
	:	v(v),
		rgb(rgb)
	{
		convexHull();
		assert(rgb.r<=1 and rgb.r>=0);
		assert(rgb.g<=1 and rgb.g>=0);
		assert(rgb.b<=1 and rgb.b>=0);
	}

//*************************************************************************************************************//

	// Returns the area of the polygon. //
	double Polygon::area () const {
		double area=0;
		int n=v.size();
		if(n<=2) return 0; //A line a point or an empty polygon//


		//In order to compute the area we will use the "Shoelace formula"//
		for(int i=0; i<n-1;++i){
			area += v[i].get_x()*v[i+1].get_y()-v[i+1].get_x()*v[i].get_y();
		}
		area += v[n-1].get_x()*v[0].get_y()-v[0].get_x()*v[n-1].get_y();

		if(abs(area)<E) return 0;
		return -area/2;
	}

//*************************************************************************************************************//

	// Returns the perimeter of the polygon. //
	double Polygon::perimeter () const {
		double perimeter=0;
		int n=v.size();
		for(int i=0; i<n; ++i){
			perimeter += v[i%n].distance(v[(i+1)%n]);
		}
		return perimeter;
	}

//*************************************************************************************************************//

	// Returns the number of vertices of the polygon. //
	int Polygon::vertices () const{
		return v.size();
	}

//*************************************************************************************************************//

	Point Polygon::centroid () const{
		int mida=v.size();
		double area=0;
		double cx=0; double cy = 0;

		//We use a variant of the gauss determinant//
		for(int i=0; i<mida-1; ++i){
			
			double aux = v[i].get_x()*v[i+1].get_y()-v[i+1].get_x()*v[i].get_y();

			area+=aux; //Part of the formula uses the operations to compute the area so we can reuse them//

			cx+=(v[i].get_x()+v[i+1].get_x())*aux;
			cy+=(v[i].get_y()+v[i+1].get_y())*aux;
		}

		double aux= v.back().get_x()*v[0].get_y()-v[0].get_x()*v.back().get_y();

		area+=aux;

		cx+=(v.back().get_x()+v[0].get_x())*aux;
		cy+=(v.back().get_y()+v[0].get_y())*aux;

		double x_coord=cx/(6*(area/2)); if(abs(0-x_coord)<E) x_coord*=-1;
		double y_coord=cy/(6*(area/2)); if(abs(0-y_coord)<E) y_coord*=-1;

		return Point (x_coord, y_coord);
	}

//*************************************************************************************************************//

	// Sets the color of the polygon. //
	// Precondition: R,G,B values goes to 0 to 1. //
	void Polygon::setcol (double R, double G, double B){
		rgb.r=R; rgb.b=B; rgb.g=G;
	}

//*************************************************************************************************************//

	void search_intersec(Point& i1, Point& i2, Point& j1, Point& j2, vector <Point>& inside){

		//a1x + b1y = c1//
		double a1 = i2.get_y()-i1.get_y();
		double b1 = i1.get_x()-i2.get_x();
		double c1 = a1*i1.get_x()+b1*i1.get_y();

		//a2x + b2y = c2//
		double a2 = j2.get_y()-j1.get_y();
		double b2 = j1.get_x()-j2.get_x();
		double c2 = a2*j1.get_x()+b2*j1.get_y();

		//We make the determinant//
		double det = a1*b2 - a2*b1;

		if(abs(det)>E){
			double x = (b2*c1 - b1*c2)/det;
			double y = (a1*c2 - a2*c1)/det;
			if(x<=E) x=0; 
			if(y<=E) y=0;
			Point intersec = Point(x,y);
						
			vector <Point> VAB={i1, i2};
			Polygon AB = Polygon(VAB);
			vector <Point> VCD={j1, j2};
			Polygon CD = Polygon(VCD);

			if(AB.dins(intersec) and CD.dins(intersec)) inside.push_back(intersec);
		}
	}

	Polygon& Polygon::operator*=(const Polygon& p) {
		vector <Point> inside;

		if(not v.empty() and not p.get_v().empty()){
			//We search the points of p inside *this//
			for(Point a:v){
				if(p.dins(a)) inside.push_back(a);
			}
			//We search the points of *this inside p//
			vector<Point> pvector =p.get_v();
			for(Point b: pvector){
				if(this->dins(b)) inside.push_back(b);
			}

			//We search the intersection points between every segment of the two polygons//
			int mida_v=v.size(); int mida_pv=pvector.size();
			for(int i = 0; i<mida_v-1;++i){
				for(int j = 0; j<mida_pv-1; ++j){
					search_intersec(v[i],v[i+1],pvector[j],pvector[j+1],inside);
				}
				search_intersec(v[i], v[i+1], pvector.back(), pvector[0], inside);
			}
			for(int j=0; j<mida_pv-1; ++j){
				search_intersec(v.back(), v[0], pvector[j], pvector[j+1], inside);
			}
			search_intersec(v.back(),v[0],pvector.back(), pvector[0], inside);

		v=inside;
	}
		convexHull();
		return *this;
	}

	Polygon Polygon::operator* (const Polygon& p) const {
		Polygon pol = p;
		pol *= *this;
		return pol;
	}

//*************************************************************************************************************//


	Polygon& Polygon::operator+= (const Polygon& p){
		vector <Point> pvector= p.get_v();
		// We make a vector with all the points and make a convex hull //
		v.insert(v.end(), pvector.begin(), pvector.end());
		convexHull();
		return *this;
	}

	Polygon Polygon::operator+ (const Polygon& p) const {
		Polygon pol = p;
		pol += *this;
		return pol;
	}

//*************************************************************************************************************//

	Polygon Polygon::bbox() const{
		/* We look for the max and min coordenates in order to compute a
		rectangular box that comprise all the polygon*/
		double max_x=v[0].get_x(); double max_y=v[0].get_y();
		double min_x=v[0].get_x(); double min_y=v[0].get_y();
		int n=v.size();
		if(n>1){
			for(int i=1; i<n; ++i){
				if(v[i].get_x()>=max_x) max_x=v[i].get_x();
				if(v[i].get_x()<=min_x) min_x=v[i].get_x();
				if(v[i].get_y()>=max_y) max_y=v[i].get_y();
				if(v[i].get_y()<=min_y) min_y=v[i].get_y();
			}
		}
		Point a ={min_x,min_y}; Point b = {min_x, max_y}; 
		Point c = {max_x, max_y}; Point d ={max_x, min_y};
		vector<Point> box = {a,b,c,d};
		return Polygon(box);
	}

//*************************************************************************************************************//

	bool Polygon::inside(const Polygon& p) const{
		int n=v.size();
		if(n==0) return false;
		for(Point a : v){
			if(not p.dins(a)) return false;
		}
		return true;
	}

	bool Polygon::dins(const Point& p) const{
		int mida=v.size();
		// Special cases //
		if(mida == 0) return false;
		if(mida == 1) return v[0]==p;
		if(mida == 2) {
			if(p.in_line(v[0],v[1])){
				return p.get_x()>= v[0].get_x() and p.get_x() <= v[1].get_x() and ((p.get_y()>= v[0].get_y() 
					and p.get_y()<=v[1].get_y()) or (p.get_y()<= v[0].get_y() and p.get_y()>=v[1].get_y()));
			}
			else return false;
		}
		/* Iterative program: divides the polygon in 2 parts and decides in wich part is the point located 
		The base case its a triangle*/
		else{
			int e=1; int d=v.size()-1;
			while(e+1!=d){
				int m=(e+d+1)/2;
				if(v[0].strict_leftof(v[m],p)) d=m;
				else e=m;
			}
			// If its in the right part of the 3 segments it will be inside the polygon //
			return not ((v[0].strict_leftof(v[e],p)) or (v[e].strict_leftof(v[d],p)) or (v[d].strict_leftof(v[0],p)));
		}
	}

//*************************************************************************************************************//
	
	// Returns the vector of points of the polygon //
	vector <Point> Polygon::get_v () const {
		return v;
	}

//*************************************************************************************************************//

	double Polygon::get_r() const{
		return rgb.r;
	}

//*************************************************************************************************************//

	double Polygon::get_g() const{
		return rgb.g;
	}

//*************************************************************************************************************//

	double Polygon::get_b() const{
		return rgb.b;
	}

//*************************************************************************************************************//

	Color Polygon::get_rgb() const{
		return rgb;
	}

//*******************************************|CONVEX HULL|****************************************************//

		struct compara{
			Point p;
			bool operator()(const Point& a, const Point& b){
				// Special cases where the slope is infinite//
				if(p.get_x()==a.get_x() and b.get_x() == p.get_x()) return a.get_y()<b.get_y();
				if(p.get_x()==a.get_x()) return true;
				if(p.get_x()==b.get_x()) return false;
				
				//Ordering by looking its slopes//
				if(p.slope(a)==p.slope(b)) return p.distance(a)<p.distance(b);
				return p.slope(a)>p.slope(b);
			}
		};

		void simplePoly(vector<Point>& v){
			Point p=v[0];
			for(Point q:v){
				if(q.get_x()<p.get_x()) p=q;
				if(q.get_x()==p.get_x() and q.get_y()<p.get_y()) p=q;
			}
			compara comp;
			comp.p=p;
			sort(v.begin(), v.end(), comp); // sorts the points //
		}

		void eliminacio_duplicats(vector<Point>& v){
			vector<Point> aux; int mida= v.size();
			aux.push_back(v[0]);
			for(int i=1; i<mida; ++i){
				if(v[i]!=v[i-1]) aux.push_back(v[i]);
			}
			v=aux;
		}

		void graham(vector<Point>& v){
			vector<Point> q={v[0], v[1]};
	    	int m=1; 
	    	int mida=v.size();
	    	for(int i=2; i<mida; ++i){
	    		Point p=v[i];
	    		while(q[m-1].leftof(q[m],p) and m>0){
	    			--m; q.pop_back();
	    		}
	    		++m; q.push_back(v[i]);	
	    	}
	 		v=q;
		}

		void Polygon::convexHull(){
			if(v.size()<1) return;
			simplePoly(v);
			eliminacio_duplicats(v);
			if(v.size()>=3) graham(v);
			
		}

//*************************************************************************************************************//