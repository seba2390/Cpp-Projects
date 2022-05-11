#include <iostream> // Standard input/output stream (printing to console etc.)
#include <fstream>  // For input/out streams to files

#include <cmath>    // For using math functions (cos etc.)
#include <cassert>  // For doing assert statements

struct tabulatedData {double* tab_x; double* tab_y; double* interval; int nr_points;};
typedef struct tabulatedData tabulatedData;


double my_function(double x)
{
    return x * x * x * cos(2 * x) - 0.5 * x * x + x;
}

// Filling tab_x and tab_y in interval with nr_points according to function f
void setDataPoints(double (*f)(double), tabulatedData myData)
{
    int i;
    double x        =  myData.interval[0];
    double stepsize = (myData.interval[1] - myData.interval[0]) / (myData.nr_points - 1) ;// -1 to include endpoints in interval
    for(i = 0; i < myData.nr_points; i++)
    {
        myData.tab_x[i] = x; myData.tab_y[i] = f(x);
        x = x + stepsize;
    }   
}

void writeOut(std::string filename, tabulatedData myData)
{
    std::fstream myFileStream;
    myFileStream.open(filename,std::ios::out);
    int i;
    for(i = 0; i < myData.nr_points; i++) 
    {
        myFileStream << myData.tab_x[i] << "  " << myData.tab_y[i];
        myFileStream << "\n";
    }  
    myFileStream.close();
}


// Function for doing binary search - locates the lower/left interval index for x, in tab_x, by bisection
// (only works for sorted arrays)
int binary_search(int n, double* tab_x, double x)
{  
    int low = 0, high = n;
    int index = -1;
    if (tab_x[0] == x)
    {
        return 0;
    }
    while (low <= high) 
    {
        int mid = low + (high - low) / 2;
        if (tab_x[mid] < x) 
        {
            index = mid;
            low   = mid +1;
        }
        else if (tab_x[mid] > x) 
        {
            high = mid - 1;
        }
        else if (tab_x[mid] == x) 
        {
            high = mid - 1;
        }
    }
    return index;
}

// Function for evaluating linear spline at given x
double linear_spline(tabulatedData myData, double x)
{

	int i = binary_search(myData.nr_points-1,myData.tab_x,x); // Lower index of interval

    // dy/dx corresponds to a vals in quad spline
    double dy = (myData.tab_y[i+1] - myData.tab_y[i]);
    double dx = (myData.tab_x[i+1] - myData.tab_x[i]);

	return myData.tab_y[i] + (dy / dx) * (x - myData.tab_x[i]);
}



int main ()
{
    /* ----- TABULATION PART ----- */
    double tabulation_interval[2] = {-16.,16.};
    int    nr_tabulated_points    = 60;
    double tabulated_x[nr_tabulated_points]; double tabulated_y[nr_tabulated_points];

    // Setting tabulated points according to my_function
    tabulatedData tabData = {tabulated_x,tabulated_y,tabulation_interval,nr_tabulated_points};
    setDataPoints(*my_function,tabData);

    // Writing out tabulated points (for plotting)
    std::string tab_filename = "tabulated_data.txt";
    writeOut(tab_filename,tabData);


    /* ----- CONSTANTS FOR SPLINES ----- */
    int RESOLUTION             = 1000;  // Factor determining resolution of spline
    int nr_spline_points       = nr_tabulated_points * RESOLUTION;
    double spline_interval[2]  = {tabulation_interval[0],tabulation_interval[1]};


    /* ----- LINEAR SPLINE PART ----- */
    double lin_spline_x[nr_spline_points]; double lin_spline_y[nr_spline_points];
    
    // Setting tabulated points according to linear spline
    tabulatedData linSplineData = {lin_spline_x,lin_spline_y,spline_interval,nr_spline_points};
    double x        =  linSplineData.interval[0];
    double stepsize = (linSplineData.interval[1] - linSplineData.interval[0]) / (linSplineData.nr_points - 1) ; // -1 to include endpoints in interval
    
    for(int i = 0; i < linSplineData.nr_points; i++)
    {
        linSplineData.tab_x[i] = x; linSplineData.tab_y[i] = linear_spline(tabData,x);
        x = x + stepsize;
    }  
    // Writing out tabulated points (for plotting)
    std::string linSplineFilename = "lin_spline_data.txt";
    writeOut(linSplineFilename,linSplineData);    


    system("python plot.py");
}