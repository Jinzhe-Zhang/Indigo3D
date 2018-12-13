#include "3DMath.h"
void matrix4x4f::rotate( const float &angle, vertex3 &axis )
//void matrix4x4f::rotate( const float &angle, float x, float y, float z )
{
	float s = (float)sin(angle*3.14159265358979323846f/180);
	float c = (float)cos(angle*3.14159265358979323846f/180);

//    axis.normalize();

	float ux = axis.x;
	float uy = axis.y;
	float uz = axis.z;

    m[0]  = c+(1-c)*ux*ux;		// x
	m[1]  = ux*uy*(1-c) + s*uz;
	m[2]  = (1-c) * ux*uz - s*uy;
	m[3]  = 0;
//---------------------
	m[4]  = (1-c)*ux*uy-uz*s;	// x
	m[5]  =c+(1-c)*uy*uy;
	m[6]  = (1-c) * uy*uz + s*ux;
	m[7]  = 0;
//---------------------
	m[8]  = (1-c)*ux*uz+uy*s;	// x
	m[9]  = (1-c)*uy*uz-ux*s;
	m[10] = c + (1-c) * pow(uz,2);
	m[11] = 0;
	
	m[12] = 0;
	m[13] = 0;
	m[14] = 0;
	m[15] = 1;
}
void matrix4x4f::transformVector( vertex3 *vec )
{
    vertex3 &v = *vec;
    float x = v.x;
    float y = v.y;
    float z = v.z;

	v.x = x * m[0] + y * m[4] + z * m[8];
    v.y = x * m[1] + y * m[5] +	z * m[9];
    v.z = x * m[2] + y * m[6] + z * m[10];
}


// 获得一个面的法线
vertex3 GetNormal(vertex3 a, vertex3 b, vertex3 c)
{
    double ux = (double)b.x - (double)a.x;
    double uy = (double)b.y - (double)a.y;
    double uz = (double)b.z - (double)a.z;
    double vx = (double)c.x - (double)a.x;
    double vy = (double)c.y - (double)a.y;
    double vz = (double)c.z - (double)a.z;

    double uux = (uy*vz)-(vy*uz);
    double uuy = (uz*vx)-(vz*ux);
    double uuz = (ux*vy)-(vx*uy);

	double fLength = sqrt( uux * uux + uuy * uuy + uuz * uuz );
	if(fLength == 0.0f)	fLength = 1.0f;
	uux /= fLength; uuy /= fLength;uuz /= fLength;

    vertex3 temp;
	temp.x = (float)uux;
	temp.y = (float)uuy;
	temp.z = (float)uuz;
    return temp;
}


float Distance(vertex3 vPoint1, vertex3 vPoint2)
{
	// This is the classic formula used in beginning algebra to return the
	// distance between 2 points.  Since it's 3D, we just add the z dimension:
	// 
	float distance = sqrt(  (vPoint1.x - vPoint2.x)*(vPoint1.x - vPoint2.x) +
							(vPoint1.y - vPoint2.y)*(vPoint1.y - vPoint2.y) +
							(vPoint1.z - vPoint2.z)*(vPoint1.z - vPoint2.z) );
	return distance;
	//
/*
	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );

	// Return the distance between the 2 points
	return (float)distance;
*/
}

vertex3 crossProduct(vertex3 v1, vertex3 v2 )
{
	vertex3 result;

	double vx = (v1.y * v2.z) - (v1.z * v2.y);
	double vy = (v1.z * v2.x) - (v1.x * v2.z);
	double vz = (v1.x * v2.y) - (v1.y * v2.x);

	result.x = vx;
	result.y = vy;
	result.z = vz;

	return result;
}


// 获得空间中一个点到一条线的最近交点
vertex3 ClosestPointOnLine(vertex3 vA, vertex3 vB, vertex3 vPoint)
{
	// Create the vector from end point vA to our point vPoint.
	vertex3 vVector1 = vPoint - vA;

	// Create a normalized direction vector from end point vA to end point vB
    vertex3 vVector2 = vB - vA;
		vVector2.GetUnitNormal();

	// Use the distance formula to find the distance of the line segment (or magnitude)
    float d = Distance(vA, vB);

	// Using the dot product, we project the vVector1 onto the vector vVector2.
	// This essentially gives us the distance from our projected vector from vA.
    float t = DotProduct(vVector2, vVector1);

	// If our projected distance from vA, "t", is less than or equal to 0, it must
	// be closest to the end point vA.  We want to return this end point.
    if (t <= 0) 
		return vA;

	// If our projected distance from vA, "t", is greater than or equal to the magnitude
	// or distance of the line segment, it must be closest to the end point vB.  So, return vB.
    if (t >= d) 
		return vB;
 
	// Here we create a vector that is of length t and in the direction of vVector2
    vertex3 vVector3 = vVector2 * t;

	// To find the closest point on the line segment, we just add vVector3 to the original
	// end point vA.  
    vertex3 vClosestPoint = vA + vVector3;

	// Return the closest point on the line segment
	return vClosestPoint;
}

float DotProduct(vertex3 vVector1, vertex3 vVector2) 
{
	// The dot product is this equation: V1.V2 = (V1.x * V2.x  +  V1.y * V2.y  +  V1.z * V2.z)
	// In math terms, it looks like this:  V1.V2 = ||V1|| ||V2|| cos(theta)
	
			 //    (V1.x * V2.x        +        V1.y * V2.y        +        V1.z * V2.z)
	return ( (vVector1.x * vVector2.x) + (vVector1.y * vVector2.y) + (vVector1.z * vVector2.z) );
}

bool InsidePolygon(vertex3 vIntersection, vertex3 Poly[])
{

	const double MATCH_FACTOR = 0.999;		// Used to cover up the error in floating point
	double Angle = 0.0;						// Initialize the angle
	vertex3 vA, vB;						// Create temp vectors
	
	for (int i = 0; i < 3; i++)		// Go in a circle to each vertex and get the angle between
	{	
		vA = Poly[i] - vIntersection;			// Subtract the intersection point from the current vertex
												// Subtract the point from the next vertex
		vB = Poly[(i + 1) % 3] - vIntersection;
												
		Angle += AngleBetweenVectors(vA, vB);	// Find the angle between the 2 vectors and add them all up as we go along
	}

	if(Angle >= (MATCH_FACTOR * (2.0 * M_PI)) )	// If the angle is greater than 2 PI, (360 degrees)
		return true;							// The point is inside of the polygon
		
	return false;								// If you get here, it obviously wasn't inside the polygon, so Return FALSE

}
double AngleBetweenVectors(vertex3 Vector1, vertex3 Vector2)
{							
	// Get the dot product of the vectors
	float dotProduct = DotProduct(Vector1, Vector2);				

	// Get the product of both of the vectors magnitudes
	float vectorsMagnitude = Magnitude(Vector1) * Magnitude(Vector2) ;

	// Get the angle in radians between the 2 vectors
	double angle = acos( dotProduct / vectorsMagnitude );

	// Here we make sure that the angle is not a -1.#IND0000000 number, which means indefinate
	if(_isnan(angle))
		return 0;
	
	// Return the angle in radians
	return( angle );
}
float Magnitude(vertex3 vNormal)
{
	// This will give us the magnitude or "Norm" as some say, of our normal.
	// Here is the equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)  Where V is the vector

	return (float)sqrt( (vNormal.x * vNormal.x) + (vNormal.y * vNormal.y) + (vNormal.z * vNormal.z) );
}
/*----------------------------------------------------------------
 线段到面的交点
 这里的误差值是 1.0f
 ALLOW_ERROR_C = 1.0f
 *----------------------------------------------------------------*/

bool getLineAB_to_PlaneIntersectionPoint(	vertex3 vLineStart, 
											vertex3 vLineEnd,
											vertex3 vPointInPlane, 
											vertex3 vPlaneNormal,
											vertex3 *vIntersection )
{
//	vPlaneNormal.GetUnitNormal();

	double	 fLineLength;
	double    fPercentage;
    double    fDistanceFromPlane;

	double nx = (double)vPlaneNormal.x;
	double ny = (double)vPlaneNormal.y;
	double nz = (double)vPlaneNormal.z;

	double dx = (double)vLineEnd.x - (double)vLineStart.x;
	double dy = (double)vLineEnd.y - (double)vLineStart.y;
	double dz = (double)vLineEnd.z - (double)vLineStart.z;

	fLineLength = nx*dx + ny*dy + nz*dz;

	// 如果线的 [两点到面的距离的和] 少于 0.01f ,那么就说明了线就是和面平衡.
	// 或者说明了,线太短了,就算它和面垂直.

	if( fabsf( fLineLength ) < 0.01f )
        return false;

	double lx = (double)vPointInPlane.x - (double)vLineStart.x;
	double ly = (double)vPointInPlane.y - (double)vLineStart.y;
	double lz = (double)vPointInPlane.z - (double)vLineStart.z;

	fDistanceFromPlane = nx*lx + ny*ly + nz*lz;
	// fDistanceFromPlane 就是线的开始点到面的距离.

	fPercentage	= fDistanceFromPlane / fLineLength;
	if( fPercentage < 0.0f || fPercentage > 1.0f ) return false;// 如果带线段外就不理啦！

	lx = (double)vLineStart.x + dx * fPercentage;
	ly = (double)vLineStart.y + dy * fPercentage;
	lz = (double)vLineStart.z + dz * fPercentage;

	vIntersection->x = (float)lx;
	vIntersection->y = (float)ly;
	vIntersection->z = (float)lz;
	return true;

/*
	float	 fLineLength;
	float    fPercentage;
    float    fDistanceFromPlane;

	vPlaneNormal.GetUnitNormal();
	vertex3 vDirection = vLineEnd - vLineStart;

	fLineLength = DotProduct( vDirection, vPlaneNormal );

	// 如果线的两点到面的距离的和少于 1 ,那么就说明了线就是和面平衡.
	// 或者说明了,线太短了,就算它和面垂直.

	if( fabsf( fLineLength ) < ALLOW_ERROR_C )
        return false;

	vertex3 L1 = vPointInPlane - vLineStart;

	fDistanceFromPlane = DotProduct( L1, vPlaneNormal );
	// fDistanceFromPlane 就是线的开始点到面的距离.

	// How far from Linestart , intersection is as a percentage of 0 to 1
	fPercentage	= fDistanceFromPlane / fLineLength;

	if( fPercentage < 0.0f || fPercentage > 1.0f ) // 如果带线段外就不理啦！
        return false;

	// Add the percentage of the line to line start
	*vIntersection = vLineStart + vDirection * fPercentage;

	return true;
*/
}
