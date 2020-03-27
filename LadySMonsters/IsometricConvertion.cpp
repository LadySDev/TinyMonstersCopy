#include "IsometricConvertion.h"

std::vector<sf::Vector2f> IsometricConvertion::orthoRectToIso(int unitX, int unitY)
{
    float isoUnitX = sqrt(2 * pow(unitX, 2));
    float isoUnitY = sqrt(2 * pow(unitY, 2));

    std::vector<sf::Vector2f> vOrtho = {
        sf::Vector2f(0, 0),
        sf::Vector2f(isoUnitX, 0),
        sf::Vector2f(isoUnitX, isoUnitY),
        sf::Vector2f(0, isoUnitY)
    };

    int rotation = 45;

    std::vector<sf::Vector2f> vIso = {
        vOrtho.at(0),
        orthographicToIsometric(vOrtho.at(0), vOrtho.at(1), rotation),
        orthographicToIsometric(vOrtho.at(0), vOrtho.at(2), rotation),
        orthographicToIsometric(vOrtho.at(0), vOrtho.at(3), rotation)
    };

    return vIso;
}

std::vector<sf::Vector2f> IsometricConvertion::orthoQuadToIso(int unit)
{
    float isoUnit = sqrt(2 * pow(unit, 2));

    std::vector<sf::Vector2f> vOrtho = {
        sf::Vector2f(0, 0),
        sf::Vector2f(isoUnit, 0),
        sf::Vector2f(isoUnit, isoUnit),
        sf::Vector2f(0, isoUnit)
    };

    int rotation = 45;

    std::vector<sf::Vector2f> vIso = {
        vOrtho.at(0),
        orthographicToIsometric(vOrtho.at(0), vOrtho.at(1), rotation),
        orthographicToIsometric(vOrtho.at(0), vOrtho.at(2), rotation),
        orthographicToIsometric(vOrtho.at(0), vOrtho.at(3), rotation)
    };

    return vIso;
}

sf::Vector2f IsometricConvertion::orthographicToIsometric(sf::Vector2f pivot, sf::Vector2f point, int angleDegree)
{
	float radian = M_PI * angleDegree / 180.f;
	sf::Vector2f v;

	//Rotation
	v.x = pivot.x + cos(radian) * (point.x - pivot.x) - sin(radian) * (point.y - pivot.y);
	v.y = pivot.y + sin(radian) * (point.x - pivot.x) + cos(radian) * (point.y - pivot.y);

	//Divide half height
	v.y = v.y - (abs(pivot.y - v.y) / 2);

	return v;
}

bool IsometricConvertion::isInsideTriangle(sf::Vector2f pointT0, sf::Vector2f pointT1, sf::Vector2f pointT2, sf::Vector2f point)
{
    //First
    int valDefault1 = (pointT0.x - pointT1.x) * (pointT0.y - pointT2.y) - 
                      (pointT0.y - pointT1.y) * (pointT0.x - pointT2.x);
    int valFound1 = (pointT0.x - pointT1.x) * (pointT0.y - point.y) -
                    (pointT0.y - pointT1.y) * (pointT0.x - point.x);

    bool  first = (valDefault1 >= 0 && valFound1 >= 0) || (valDefault1 <= 0 && valFound1 <= 0);

    //Second
    int valDefault2 = (pointT1.x - pointT2.x) * (pointT1.y - pointT0.y) -
                      (pointT1.y - pointT2.y) * (pointT1.x - pointT0.x);
    int valFound2 = (pointT1.x - pointT2.x) * (pointT1.y - point.y) -
                    (pointT1.y - pointT2.y) * (pointT1.x - point.x);

    bool  second = (valDefault2 >= 0 && valFound2 >= 0) || (valDefault2 <= 0 && valFound2 <= 0);
    
    //Third
    int valDefault3 = (pointT2.x - pointT0.x) * (pointT2.y - pointT1.y) -
                      (pointT2.y - pointT0.y) * (pointT2.x - pointT1.x);
    int valFound3 = (pointT2.x - pointT0.x) * (pointT2.y - point.y) -
                    (pointT2.y - pointT0.y) * (pointT2.x - point.x);

    bool  third = (valDefault3 >= 0 && valFound3 >= 0) || (valDefault3 <= 0 && valFound3 <= 0);

	return (first && second && third);
}

////the function checks if point lies on line segment 'start-end' 
//bool IsometricConvertion::onSegment(sf::Vector2f start, sf::Vector2f end, sf::Vector2f point)
//{
//	if (point.x <= std::max(start.x, end.x) && 
//		point.x >= std::min(start.x, end.x) &&
//		point.y <= std::max(start.y, end.y) && 
//		point.y >= std::min(start.y, end.y))
//		return true;
//	return false;
//}
//
//int IsometricConvertion::orientation(sf::Vector2f start, sf::Vector2f end, sf::Vector2f point)
//{
//	int val = (point.y - start.y) * (end.x - point.x) -	(point.x - start.x) * (end.y - point.y);
//
//	if (val == 0) return 0;  // colinear 
//	return (val > 0) ? 1 : 2; // clock or counterclock wise
//}
//
//// The function that returns true if line segment 'start1-end1' and 'start2-end2' intersect. 
//bool IsometricConvertion::doIntersect(sf::Vector2f start1, sf::Vector2f end1, sf::Vector2f start2, sf::Vector2f end2)
//{
//    // Find the four orientations needed for general and 
//    // special cases 
//    int o1 = orientation(start1, end1, start2);
//    int o2 = orientation(start1, end1, end2);
//    int o3 = orientation(start2, end2, start1);
//    int o4 = orientation(start2, end2, end1);
//
//    // General case 
//    if (o1 != o2 && o3 != o4)
//        return true;
//
//    // Special Cases 
//    // p1, q1 and p2 are colinear and p2 lies on segment p1q1 
//    if (o1 == 0 && onSegment(start1, start2, end1)) return true;
//
//    // p1, q1 and p2 are colinear and q2 lies on segment p1q1 
//    if (o2 == 0 && onSegment(start1, end2, end1)) return true;
//
//    // p2, q2 and p1 are colinear and p1 lies on segment p2q2 
//    if (o3 == 0 && onSegment(start2, start1, end2)) return true;
//
//    // p2, q2 and q1 are colinear and q1 lies on segment p2q2 
//    if (o4 == 0 && onSegment(start2, end1, end2)) return true;
//
//    return false; // Doesn't fall in any of the above cases 
//}
//
//// Returns true if the point lies inside the polygon with n vertices 
//bool IsometricConvertion::isInside(std::vector<sf::Vector2f*> polygon, int n, sf::Vector2f point)
//{
//    // There must be at least 3 vertices in polygon[] 
//    if (n < 3)  return false;
//
//    // Create a point for line segment from p to infinite 
//    sf::Vector2f extreme = { 5000, point.y };
//
//    // Count intersections of the above line with sides of polygon 
//    int count = 0, i = 0;
//    do
//    {
//        int next = (i + 1) % n;
//
//        // Check if the line segment from 'p' to 'extreme' intersects 
//        // with the line segment from 'polygon[i]' to 'polygon[next]' 
//        if (doIntersect(*polygon[i], *polygon[next], point, extreme))
//        {
//            // If the point 'p' is colinear with line segment 'i-next', 
//            // then check if it lies on segment. If it lies, return true, 
//            // otherwise false 
//            if (orientation(*polygon[i], point, *polygon[next]) == 0)
//                return onSegment(*polygon[i], point, *polygon[next]);
//
//            count++;
//        }
//        i = next;
//    } while (i != 0);
//
//    // Return true if count is odd, false otherwise 
//    return count & 1;  // Same as (count%2 == 1) 
//}
