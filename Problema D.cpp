#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

struct Point {
    double x, y;
};

// Function to calculate Euclidean distance between two points
double distance(Point a, Point b) {
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

// Function to calculate the midpoint of the base of the pyramid
Point calculateMidpoint(Point p1, Point p2) {
    return {(p1.x + p2.x) / 2.0, (p1.y + p2.y) / 2.0};
}

int main() {
    // Input variables
    double x1, y1, x2, y2, h1;
    double x3, y3, x4, y4, h2;

    // Read input
    cin >> x1 >> y1 >> x2 >> y2 >> h1;
    cin >> x3 >> y3 >> x4 >> y4 >> h2;

    // Points defining the bases of the pyramids
    Point p1 = {x1, y1};
    Point p2 = {x2, y2};
    Point p3 = {x3, y3};
    Point p4 = {x4, y4};

    // Midpoints of the bases
    Point midpoint1 = calculateMidpoint(p1, p2);
    Point midpoint2 = calculateMidpoint(p3, p4);

    // Calculate the distance on the base plane
    double baseDistance = distance(midpoint1, midpoint2);

    // Calculate the distance between the peaks
    double distancePeaks = sqrt(baseDistance * baseDistance + (h1 + h2) * (h1 + h2));

    // Output the result with precision of 6 decimal places
    cout << fixed << setprecision(6) << distancePeaks << endl;

    return 0;
}
