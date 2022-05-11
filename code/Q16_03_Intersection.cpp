#include <iostream>

using namespace std;

struct Point {
    double x;
    double y;
};

struct Line {
    double slope;
    double y;

    Line(Point start,Point end) {
        double deltaY = end.y - start.y;
        double deltaX = end.x - start.x;
        slope = deltaY / deltaX; 
        y = end.y - slope * end.x;
    }
};

bool isBetween(double start, double middle, double end) {
    if (start > end) {
        return end <= middle && middle <= start;
    } else {
        return start <= middle && middle <= end;
    }
}

bool isBetween(Point start, Point middle, Point end) {
    return isBetween(start.x, middle.x, end.x) && isBetween(start.y, middle.y, end.y);
}

Point intersection(Point start1,Point end1,Point start2,Point end2) {
    if (start1.x > end1.x) swap(start1, end1);
    if (start2.x > end2.x) swap(start2, end2);
    if (start1.x > start2.x) {
        swap(start1,start2);
        swap(end1,end2);
    }
    Line line1(start1,end1);
    Line line2(start2,end2);

    if (line1.slope == line2.slope) {
        if (line1.y == line2.y && isBetween(start1,start2,end1)) {
            return start2;
        }
    }

    double x = (line2.y - line1.y) / (line1.slope - line2.slope);
    double y = x * line1.slope + line1.y;
    Point intersection{x, y};

    if (isBetween(start1, intersection, end1) && isBetween(start2, intersection, end2)) {
        return intersection;
    }

    return {};
}

int main() {
    auto res = intersection({0,0},{1,1},{0,1},{1,0});
    cout << res.x << " " << res.y << endl;
}