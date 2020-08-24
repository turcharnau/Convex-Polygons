	#include <iostream>
	#include <string>
	#include <map>
	#include <cassert>
	#include <sstream>
	#include <vector>
	#include <fstream>
	#include <pngwriter.h>
	using namespace std;

	#include "Point.hh"
	#include "convex.hh"

	map<string, Polygon> convexPoli;

	bool declarat(const string& name){
		auto it = convexPoli.find(name); //In order to check if the polygon is defined //
		return it != convexPoli.end();
	}

	bool empty_p(const Polygon& p){     //Returns if a polygon p is empty or not //
		vector <Point> pvector=p.get_v();
		return pvector.empty();
	}

//*************************************************************************************************************//

	void polygon(istringstream& iss){
		string name; iss>>name;
		vector <Point> pvector; double x,y;
		bool okey=true; //In order to decide the output //
		
		while(iss >> x){
			if(iss>>y) pvector.push_back(Point(x,y)); //vector of points of the polygon //
			else {
				cout<<"Error: incorrect declaration"<<endl;
				okey=false;
			}
		}
		if(okey){
			convexPoli[name]=Polygon(pvector);
			cout<<"ok"<<endl;
		}
	}

//*************************************************************************************************************//

	void print(istringstream& iss){
		string name; 
		iss>>name;
		string extra;
		if(iss>>extra) cout<<"Error: too many parameters";
		else{
			if(declarat(name)){

				vector<Point> pvector = convexPoli[name].get_v(); 
				int mida=pvector.size();
				cout<< name << " ";
				for(int i=0; i<mida; ++i) cout<<pvector[i].get_x()<<" "<<pvector[i].get_y()<<" ";

			}else{
				cout<<"Error: undefined identifier";
			}
		}
		cout<<endl;
	}

//*************************************************************************************************************//

	void area (istringstream& iss){
		string name; 
		iss>>name;
		string extra;
		if(iss>>extra) cout<<"Error: too many parameters"<<endl;
		else{
			if(declarat(name)) cout<<convexPoli[name].area()<<endl;
			else cout<<"Error: undefined identifier"<<endl;
		}
	}

//*************************************************************************************************************//

	void perimeter (istringstream& iss){
		string name;
		iss>>name;
		string extra;
		if(iss>>extra) cout<<"Error: too many parameters"<<endl;
		else{
			if(declarat(name)) cout<<convexPoli[name].perimeter()<<endl;
			else cout<<"Error: undefined identifier"<<endl;
		}
	}

//*************************************************************************************************************//

	void vertices (istringstream& iss){
		string name; iss>>name;
		string extra;
		if(iss>>extra) cout<<"Error: too many parameters"<<endl;
		else{
			if(declarat(name)) cout<<convexPoli[name].vertices()<<endl;
			else cout<<"Error: undefined identifier"<<endl;
		}
	}

//*************************************************************************************************************//

	void centroid (istringstream& iss){
		string name;
		iss>>name;
		string extra;
		if(iss>>extra) cout<<"Error: too many parameters"<<endl;
		else{

			if(declarat(name)){
			
				vector <Point> pvector = convexPoli[name].get_v(); 
				int mida=pvector.size();
				
				//A polygon with less than 3 vertices has no centroid //
				if(mida<3) cout<<"Error: Not enough points"<<endl;
				else{
					Point p = convexPoli[name].centroid();
					cout<<p.get_x()<<" "<<p.get_y()<<endl;
				}
			}else cout<<"Error: undefined identifier"<<endl;
		}
	}

//*************************************************************************************************************//

	void list (istringstream& iss){
		if(convexPoli.empty()) cout<<"Any polygon declared"<<endl;
		else{
			for(auto a : convexPoli){
				cout<<a.first<<" ";
			}
			cout<<endl;
		}
	}

//*************************************************************************************************************//

	void save (istringstream& iss){
		string file_name; iss>>file_name;
		 
		string pname;
		vector<string> pstring;
		while(iss>>pname){
			if(not declarat(pname)) {
				cout<<"Error: undefined identifier"<<endl;
				return;
			}else pstring.push_back(pname);
		}

		ofstream f; f.open(file_name);
		for(string name : pstring){

			vector <Point> pvector = convexPoli[name].get_v();
				
			f<<name<<" ";
			for(Point x:pvector) f<<x.get_x()<<" "<<x.get_y()<<" ";
			f<<endl;
		}
		f.close();	
		cout<<"ok"<<endl;
	}

//*************************************************************************************************************//

	void load (istringstream& iss){
		string file_name; iss>>file_name;
		ifstream f(file_name);

		if(f.fail()) cout<<"Error: file not found"<<endl;
		else{
			string linea;
			while(getline(f,linea)){
				istringstream txt(linea);
				string name; txt>>name;
				double x,y;
				vector<Point> pvector;
				while(txt>>x>>y) pvector.push_back({x,y});
				convexPoli[name] = Polygon(pvector);
			}
			f.close();
			cout<<"ok"<<endl;
		}
	}

//*************************************************************************************************************//

	void setcol(istringstream& iss){
		string name; 
		iss>> name;
		if(declarat(name)){
			double R,G,B;
			if(iss>>R>>G>>B){
				string extra;
				if(iss>>extra) cout<<"Error: too many parameters"<<endl;
				else{
					if((R<=1 and R>=0) and (G<=1 and G>=0) and (B<=1 and B>=0)){
						assert(R<=1 and R>=0); assert(G<=1 and G>=0); assert(B<=1 and B>=0);
						convexPoli[name].setcol(R,G,B);
						cout<<"ok"<<endl;
						
					}else cout<<"Not a valid set of colors (Remember: from 0 to 1)"<<endl;
				}

			}else cout<<"Error: not enough parameters"<<endl;

		}else cout<<"Error: undefined identifier"<<endl;
	}

//*************************************************************************************************************//

	Polygon find_bbox (vector <Polygon>& poly_vector){ 
		/*First of all, we will look for the bbox of all the set of polygons in order to find
		easely the maximum points to scale the vector */
		Polygon aux;
		for(Polygon& p : poly_vector){
			if(not empty_p(p)) aux+=p;
		} 
		return aux.bbox();
	}

	double find_max (Polygon& bbox_max){
		// This function searches the maximum coordenate in absolute value of the bbox //
		// We substract the LL point in order to locate the bbox in the (0,0) position //
		Point LL=bbox_max.get_v()[0];

		vector <Point> bbox_points = bbox_max.get_v();

		double max_x=abs(bbox_points[0].get_x()-LL.get_x());
		double max_y=abs(bbox_points[0].get_y()-LL.get_y());
		int mida=bbox_points.size();

		for(int i=1; i<mida; ++i){
			if (max_x<abs(bbox_points[i].get_x()-LL.get_x())) max_x= abs(bbox_points[i].get_x()-LL.get_x());
			if (max_y<abs(bbox_points[i].get_y()-LL.get_y())) max_y= abs(bbox_points[i].get_y()-LL.get_y());
		}

		if(max_x>=max_y) return max_x;
		else return max_y;
	}

	void scale_points(vector <Polygon>& poly_vector, double scale_fact, Polygon bbox_max, Point LL){

		// We multiply every point of the different polygons and we add 2 (the edge) //
		// We also substract the LL again //
		vector <Polygon> aux;
		double ll_x=LL.get_x(); double ll_y=LL.get_y();
		for(Polygon p: poly_vector){
			vector <Point> pvector= p.get_v();
			
			int mida=pvector.size();
			for(int i=0; i<mida; ++i){
				pvector[i]  = Point((((pvector[i].get_x()-ll_x)*scale_fact)+2), (((pvector[i].get_y()-ll_y)*scale_fact)+2));
			}
			Polygon p_scaled=Polygon(pvector, p.get_rgb());
			aux.push_back(p_scaled);
		}

		poly_vector=aux;
	}

	void scale(vector <Polygon>& poly_vector){

		Polygon bbox_max=find_bbox(poly_vector);
		Point LL=bbox_max.get_v()[0];
		double scale_fact=496/find_max(bbox_max);
		scale_points(poly_vector, scale_fact, bbox_max, LL);
	}

	void draw(istringstream& iss){
		string filename; iss>>filename; 
		vector <Polygon> poly_vector;
		string name;
		while(iss>>name){
			if(declarat(name) and not empty_p(convexPoli[name])) poly_vector.push_back(convexPoli[name]);
			else{
				cout<<"Error: wrong input"<<endl;
				return;
			}
		}
		
		scale(poly_vector);

		const char * filename_bo = filename.c_str();
		pngwriter png(500, 500, 1.0, filename_bo);

		for(Polygon p : poly_vector){
			vector <Point> pvector = p.get_v();

			// We plot the polygons //
			int mida = pvector.size();
			for(int i=0; i<mida-1;++i){
				png.line(pvector[i].get_x(), pvector[i].get_y(), pvector[i+1].get_x(), pvector[i+1].get_y(),
				p.get_r(), p.get_g(), p.get_b());
			}
			// The last line //
			png.line(pvector[mida-1].get_x(), pvector[mida-1].get_y(), pvector[0].get_x(), pvector[0].get_y(),
			p.get_r(), p.get_g(), p.get_b());
		}
	    png.close();
	    cout<<"ok"<<endl;
	}

//*************************************************************************************************************//

	void intersection (istringstream& iss){
		string name; vector<string> v;
		while(iss>>name){
			v.push_back(name);
		}
			// Two cases: p1*=p2 or p1 = p2*p3 //
			if(v.size()<2) cout<<"Error: too few parameters"<<endl; 
			if(v.size()==2){

				if(declarat(v[0]) and declarat(v[1])){
					convexPoli[v[0]]*=convexPoli[v[1]];
					cout<<"ok"<<endl;
				}else{
					cout<<"Error: undefined identifier"<<endl;
					return;
				}
			}

			if(v.size()==3){
				if(declarat(v[1]) and declarat(v[2])){
					convexPoli[v[0]]=convexPoli[v[1]]*convexPoli[v[2]];
					cout<<"ok"<<endl;
				}else{
					cout<<"Error: undefined identifier"<<endl;
					return;
				}
			}
			if(v.size()>3) cout<<"Error: too much parameters"<<endl;
		} 

//*************************************************************************************************************//

		void add (istringstream& iss){
		string name; vector<string> v;
		while(iss>>name){
			v.push_back(name);
		}
		// Two cases: p1+=p2 or p1 = p2+p3 //
		if(v.size()<2) cout<<"Error: too few parameters"<<endl; 
		if(v.size()==2){

			if(declarat(v[0]) and declarat(v[1])){
				convexPoli[v[0]]+=convexPoli[v[1]];
				cout<<"ok"<<endl;
			}else{
				cout<<"Error: undefined identifier"<<endl;
				return;
			}
		}

		if(v.size()==3){
			if(declarat(v[1]) and declarat(v[2])){
				convexPoli[v[0]]=convexPoli[v[1]]+convexPoli[v[2]];
				cout<<"ok"<<endl;
			}else{
				cout<<"Error: undefined identifier"<<endl;
				return;
			}
		}
		if(v.size()>3) cout<<"Error: too much parameters"<<endl;
	} 


//*************************************************************************************************************//

	void bbox(istringstream& iss){
		string bbox_name; iss>>bbox_name;
		string name; 
		vector <Point> bboxes; // In this vector we will store all the points of the bboxes of the polygons //

		while(iss>>name){
			if(declarat(name)){
				if(convexPoli[name].get_v().size()>0){ //First of all we make de bboxes of the polygons //

					Polygon p = convexPoli[name].bbox(); 
					vector<Point> pvector=p.get_v(); 
					bboxes.insert(bboxes.end(),pvector.begin(),pvector.end());
				}
			}else{
				cout<<"Error: undefined identifier"<<endl;
				return;
			}
		}

		if(not bboxes.empty()){
			Polygon p = Polygon(bboxes);
			convexPoli[bbox_name] = p.bbox(); //This is the bbox of all polygons //
			cout<<"ok"<<endl;
		}else cout<<"Error: wrong input"<<endl;
	}

//*************************************************************************************************************//

	void inside (istringstream& iss){
		string name1, name2;
		iss>>name1>>name2;
		string extra;
		if(iss>>extra) cout<<"Error: too much parameters"<<endl;
		else {
			if(declarat(name1) and declarat(name2)){
				cout<< ((convexPoli[name1]).inside(convexPoli[name2]) ? "yes" : "no")<<endl;
			}else{
				cout<<"Error: undefined identifier"<<endl;
				return;
			}
		}
	}

//*************************************************************************************************************//

	int main(){
		cout.setf(ios::fixed);
		cout.precision(3);

		string line; 
		while(getline(cin,line)){
			istringstream iss(line);
			string action; iss>>action;
					 if(action == "polygon")		polygon(iss);
				else if(action == "print")			print(iss);
				else if(action == "area")			area(iss);
				else if(action == "vertices")		vertices(iss);
				else if(action == "perimeter")		perimeter(iss);
				else if(action == "centroid")		centroid(iss);
				else if(action == "list")			list(iss);
				else if(action == "save")			save(iss);
				else if(action == "load")			load(iss);
				else if(action == "setcol")			setcol(iss);
				else if(action == "draw")			draw(iss);
				else if(action == "intersection") 	intersection(iss);
				else if(action == "union")			add(iss);
				else if(action == "inside")			inside(iss);
				else if(action == "bbox")			bbox(iss);
				else if(action == "#")				cout<<"#"<<endl;
				else								cout<<"Error: unrecognized command"<<endl;				
			}
		} 