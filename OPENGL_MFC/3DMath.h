

#ifndef __3DMATH_H__
#define __3DMATH_H__

#include <math.h>
#include <float.h>	// 使用 _isnan() for acos()

#define M_PI			3.1415926535897932f
#define M_PIHUDU		M_PI/180.0f



class vertex3
{
public:
    float x;
    float y;
    float z;

    vertex3(void){x = y = z = 0.0f;}
    vertex3(float x_, float y_, float z_){x=x_; y=y_; z=z_;}

	vertex3 operator + ( const vertex3 &other ){
		vertex3 vResult(0.0f, 0.0f, 0.0f);
		vResult.x = x + other.x;
		vResult.y = y + other.y;
		vResult.z = z + other.z;
		return vResult;
	}
	vertex3 operator - ( const vertex3 &other ){
		vertex3 vResult(0.0f, 0.0f, 0.0f);
		vResult.x = x - other.x;
		vResult.y = y - other.y;
		vResult.z = z - other.z;
		return vResult;
	}
	vertex3 operator*( const float num ){
		vertex3 vResult(0.0f, 0.0f, 0.0f);
		vResult.x = x * num;
		vResult.y = y * num;
		vResult.z = z * num;
		return vResult;
	}
	vertex3 operator/( const float num ){
		vertex3 vResult(0.0f, 0.0f, 0.0f);
		vResult.x = x / num;
		vResult.y = y / num;
		vResult.z = z / num;
		return vResult;
	}
	vertex3 operator = ( const vertex3 &other ){
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}

    vertex3 operator += (const vertex3 a){return vertex3(x+=a.x, y+=a.y, z+=a.z);};
    vertex3 operator -= (const vertex3 a){return vertex3(x-+a.x, y-=a.y, z-=a.z);};

	vertex3 operator + ( void ) const{
		return *this;
	}
	vertex3 operator - ( void ) const{
		vertex3 vResult(-x, -y, -z);
		return vResult;
	}

	// 得到向良的长度
	float length(){
/*
		double ux=x;
		double uy=y;
		double uz=z;
		double tmplength=sqrt( ux * ux + uy * uy + uz * uz );
		return (float)tmplength;
*/
		return( (float)sqrt( x * x + y * y + z * z ) );
	}

	// 使向量单位化
	void GetUnitNormal(){
		float fLength = length();
		if(fLength == 0.0f)	fLength = 1.0f;
		x /= fLength;y /= fLength;z /= fLength;
	}
	vertex3 UnitNormal(){
		float fLength = length();
		if(fLength == 0.0f)	fLength = 1.0f;
		x /= fLength;y /= fLength;z /= fLength;

		vertex3 vResult(x, y, z);
		return vResult;
	}
};




class vertex2
{
public:

    float x;
    float y;

    vertex2(void){x = y = 0.0f;}
    vertex2(float x_, float y_){x=x_; y=y_;}

	vertex2 operator+(vertex2 a){return vertex2(a.x + x, a.y + y);}
	vertex2 operator-(vertex2 a){return vertex2(x - a.x, y - a.y);}
	vertex2 operator*(float num){return vertex2(x * num, y * num);}
	vertex2 operator/(float num){return vertex2(x / num, y / num);}

	vertex2 operator = ( const vertex3 &other ){
		x = other.x;
		y = other.y;
		return *this;
	}


    vertex2 operator += (const vertex2 a){return vertex2(x+=a.x, y+=a.y);};
    vertex2 operator -= (const vertex2 a){return vertex2(x-+a.x, y-=a.y);};
};





class matrix4x4f
{
public:

	float m[16];

    matrix4x4f()  { identity(); }
/*
	matrix4x4f( float m0, float m4, float  m8, float m12,
               float m1, float m5, float  m9, float m13,
               float m2, float m6, float m10, float m14,
               float m3, float m7, float m11, float m15 );
*/
	void identity(void)
		{
			m[0]=1.0f; m[4]=0.0f; m[8] =0.0f; m[12]=0.0f;
			m[1]=0.0f; m[5]=1.0f; m[9] =0.0f; m[13]=0.0f;
			m[2]=0.0f; m[6]=0.0f; m[10]=1.0f; m[14]=0.0f;
			m[3]=0.0f; m[7]=0.0f; m[11]=0.0f; m[15]=1.0f;
		}

	void rotate(const float &angle, vertex3 &axis);
    void transformVector( vertex3 *vec );

    // Operators...
	matrix4x4f operator + (const matrix4x4f &other);
	matrix4x4f operator - (const matrix4x4f &other);
	matrix4x4f operator * (const matrix4x4f &other);
	matrix4x4f operator * (const float scalar);
};


// 获得一个面的法线
vertex3 GetNormal(vertex3 a, vertex3 b, vertex3 c);

// 得到两个点之间的距离
float Distance(vertex3 vPoint1, vertex3 vPoint2);

// 获得空间中一个点到一条线的最近交点
vertex3 ClosestPointOnLine(vertex3 vA, vertex3 vB, vertex3 vPoint);


// 知道一个点是否在一个面上
bool InsidePolygon(vertex3 vIntersection, vertex3 Poly[]);

vertex3 crossProduct(vertex3 v1, vertex3 v2 );

// 获得两个向量相乘的值
float DotProduct(vertex3 vVector1, vertex3 vVector2);
double AngleBetweenVectors(vertex3 Vector1, vertex3 Vector2);
float Magnitude(vertex3 vNormal);

// 线段到面的交点
bool getLineAB_to_PlaneIntersectionPoint(	vertex3 vLineStart, 
											vertex3 vLineEnd,
											vertex3 vPointInPlane, 
											vertex3 vPlaneNormal,
											vertex3 *vIntersection );
#endif //__3DMATH_H__