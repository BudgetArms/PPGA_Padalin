//#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <iostream>
#include <SDL_opengl.h>
#include "utils.h"

#include "structs.h"


#pragma region OpenGLDrawFunctionality


void utils::SetColor(float r, float g, float b, float a = 1.f )
{
	glColor4f( r, g, b, a );
}

void utils::SetColor( const Color4f& color )
{
	glColor4f( color.r, color.g, color.b, color.a );
}

void utils::DrawPoint( float x, float y, float pointSize )
{
	glPointSize( pointSize );
	glBegin( GL_POINTS );
	{
		glVertex2f( x, y );
	}
	glEnd( );
}

void utils::DrawPoint( const Point2f& p, float pointSize )
{
	DrawPoint( p.x, p.y, pointSize );
}

void utils::DrawPoints( Point2f *pVertices, int nrVertices, float pointSize )
{
	glPointSize( pointSize );
	glBegin( GL_POINTS );
	{
		for ( int idx{ 0 }; idx < nrVertices; ++idx )
		{
			glVertex2f( pVertices[idx].x, pVertices[idx].y );
		}
	}
	glEnd( );
}

void utils::DrawLine( float x1, float y1, float x2, float y2, float lineWidth )
{
	glLineWidth( lineWidth );
	glBegin( GL_LINES );
	{
		glVertex2f( x1, y1 );
		glVertex2f( x2, y2 );
	}
	glEnd( );
}

void utils::DrawLine( const Point2f& p1, const Point2f& p2, float lineWidth )
{
	DrawLine( p1.x, p1.y, p2.x, p2.y, lineWidth );
}

void utils::DrawTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3, float lineWidth)
{
	glLineWidth(lineWidth);
	glBegin(GL_LINE_LOOP);
	{
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glVertex2f(p3.x, p3.y);
	}
	glEnd();
}

void utils::FillTriangle(const Point2f& p1, const Point2f& p2, const Point2f& p3)
{
	glBegin(GL_TRIANGLES);
	{
		glVertex2f(p1.x, p1.y);
		glVertex2f(p2.x, p2.y);
		glVertex2f(p3.x, p3.y);
	}
	glEnd();
}

void utils::DrawRect( float left, float bottom, float width, float height, float lineWidth )
{
	if (width > 0 && height > 0 && lineWidth > 0)
	{

		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}
}

void utils::DrawRect( const Point2f& bottomLeft, float width, float height, float lineWidth )
{
	DrawRect( bottomLeft.x, bottomLeft.y, width, height, lineWidth );
}

void utils::DrawRect( const Rectf& rect, float lineWidth )
{
	DrawRect( rect.left, rect.bottom, rect.width, rect.height, lineWidth );
}

void utils::FillRect( float left, float bottom, float width, float height )
{
	if (width > 0 && height > 0)
	{

		glBegin(GL_POLYGON);
		{
			glVertex2f(left, bottom);
			glVertex2f(left + width, bottom);
			glVertex2f(left + width, bottom + height);
			glVertex2f(left, bottom + height);
		}
		glEnd();
	}
}

void utils::FillRect( const Point2f& bottomLeft, float width, float height )
{
	FillRect( bottomLeft.x, bottomLeft.y, width, height );
}

void utils::FillRect( const Rectf& rect )
{
	FillRect( rect.left, rect.bottom, rect.width, rect.height );
}

void utils::DrawEllipse( float centerX, float centerY, float radX, float radY, float lineWidth )
{
	if (radX > 0 && radY > 0 && lineWidth > 0)
	{

		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glLineWidth(lineWidth);
		glBegin(GL_LINE_LOOP);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * cos(angle), centerY + radY * sin(angle));
			}
		}
		glEnd();
	}
}

void utils::DrawEllipse( const Point2f& center, float radX, float radY, float lineWidth )
{
	DrawEllipse( center.x, center.y, radX, radY, lineWidth );
}

void utils::DrawEllipse( const Ellipsef& ellipse, float lineWidth  )
{
	DrawEllipse( ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY, lineWidth );
}

void utils::FillEllipse( float centerX, float centerY, float radX, float radY )
{
	if (radX > 0 && radY > 0)
	{

		float dAngle{ radX > radY ? float(g_Pi / radX) : float(g_Pi / radY) };

		glBegin(GL_POLYGON);
		{
			for (float angle = 0.0; angle < float(2 * g_Pi); angle += dAngle)
			{
				glVertex2f(centerX + radX * cos(angle), centerY + radY * sin(angle));
			}
		}
		glEnd();
	}
}

void utils::FillEllipse( const Ellipsef& ellipse )
{
	FillEllipse( ellipse.center.x, ellipse.center.y, ellipse.radiusX, ellipse.radiusY );
}

void utils::FillEllipse( const Point2f& center, float radX, float radY )
{
	FillEllipse( center.x, center.y, radX, radY );
}

void utils::DrawArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle, float lineWidth )
{
	if ( fromAngle > tillAngle )
	{
		return;
	}

	float dAngle{ radX > radY ? float( g_Pi / radX ) : float( g_Pi / radY ) };

	glLineWidth( lineWidth );
	glBegin( GL_LINE_STRIP );
	{
		for ( float angle = fromAngle; angle < tillAngle; angle += dAngle )
		{
			glVertex2f( centerX + radX * cos( angle ), centerY + radY * sin( angle ) );
		}
		glVertex2f( centerX + radX * cos( tillAngle ), centerY + radY * sin( tillAngle ) );
	}
	glEnd( );

}

void utils::DrawArc( const Point2f& center, float radX, float radY, float fromAngle, float tillAngle, float lineWidth )
{
	DrawArc( center.x, center.y, radX, radY, fromAngle, tillAngle, lineWidth );
}

void utils::FillArc( float centerX, float centerY, float radX, float radY, float fromAngle, float tillAngle )
{
	if ( fromAngle > tillAngle )
	{
		return;
	}
	float dAngle{ radX > radY ? float( g_Pi / radX ) : float( g_Pi / radY ) };

	glBegin( GL_POLYGON );
	{
		glVertex2f( centerX, centerY );
		for ( float angle = fromAngle; angle < tillAngle; angle += dAngle )
		{
			glVertex2f( centerX + radX * cos( angle ), centerY + radY * sin( angle ) );
		}
		glVertex2f( centerX + radX * cos( tillAngle ), centerY + radY * sin( tillAngle ) );
	}
	glEnd( );
}

void utils::FillArc( const Point2f& center, float radX, float radY, float fromAngle, float tillAngle )
{
	FillArc( center.x, center.y, radX, radY, fromAngle, tillAngle );
}

void utils::DrawPolygon( const std::vector<Point2f>& vertices, bool closed, float lineWidth )
{
	DrawPolygon( vertices.data( ), vertices.size( ), closed, lineWidth );
}

void utils::DrawPolygon( const Point2f* pVertices, size_t nrVertices, bool closed, float lineWidth )
{
	glLineWidth( lineWidth );
	closed ? glBegin( GL_LINE_LOOP ) : glBegin( GL_LINE_STRIP );
	{
		for ( size_t idx{ 0 }; idx < nrVertices; ++idx )
		{
			glVertex2f( pVertices[idx].x, pVertices[idx].y );
		}
	}
	glEnd( );
}

void utils::FillPolygon( const std::vector<Point2f>& vertices )
{
	FillPolygon( vertices.data( ), vertices.size( ) );
}

void utils::FillPolygon( const Point2f *pVertices, size_t nrVertices )
{
	glBegin( GL_POLYGON );
	{
		for ( size_t idx{ 0 }; idx < nrVertices; ++idx )
		{
			glVertex2f( pVertices[idx].x, pVertices[idx].y );
		}
	}
	glEnd( );
}


#pragma endregion OpenGLDrawFunctionality


#pragma region CollisionFunctionality

float utils::GetDistance(float x1, float y1, float x2, float y2)
{
	return (sqrtf((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

float utils::GetDistance(const Point2f& p1, const Point2f& p2)
{
	return GetDistance(p1.x, p1.y, p2.x, p2.y);
}

bool utils::IsPointInRect(const Point2f& p, const Rectf& r)
{
	return false;

	return (p.x >= r.left &&
		p.x <= r.left + r.width &&
		p.y >= r.bottom &&
		p.y <= r.bottom + r.height);
}

bool utils::IsOverlapping(const Point2f& a, const Point2f& b, const Rectf& r)
{
	return false;


	// if one of the line segment end points is in the rect
	if (utils::IsPointInRect(a, r) || utils::IsPointInRect(b, r))
	{
		return true;
	}

	HitInfo hitInfo{};
	Point2f vertices[]{ Point2f {r.left, r.bottom},
		Point2f{ r.left + r.width, r.bottom },
		Point2f{ r.left + r.width, r.bottom + r.height },
		Point2f{ r.left, r.bottom + r.height } };

	return Raycast(vertices, 4, a, b, hitInfo);
}

bool utils::IsOverlapping(const Rectf& r1, const Rectf& r2)
{
	return false;

	// If one rectangle is on left side of the other
	if ((r1.left + r1.width) < r2.left || (r2.left + r2.width) < r1.left)
	{
		return false;
	}

	// If one rectangle is under the other
	if (r1.bottom > (r2.bottom + r2.height) || r2.bottom > (r1.bottom + r1.height))
	{
		return false;
	}

	return true;
}

bool utils::IsPointInPolygon(const Point2f& p, const std::vector<Point2f>& vertices)
{

	return false;
}

bool utils::IsPointInPolygon(const Point2f& p, const Point2f* vertices, size_t nrVertices)
{
	
	return false;
}

bool utils::IntersectLineSegments(const Point2f& p1, const Point2f& p2, const Point2f& q1, const Point2f& q2, float& outLambda1, float& outLambda2, float epsilon)
{

	return false;
}

bool utils::Raycast(const std::vector<Point2f>& vertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
{

	return false;
}

bool utils::Raycast(const Point2f* vertices, const size_t nrVertices, const Point2f& rayP1, const Point2f& rayP2, HitInfo& hitInfo)
{

	return false;
}

bool  utils::IsPointOnLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
{
	return false;
}

float  utils::DistPointLineSegment(const Point2f& p, const Point2f& a, const Point2f& b)
{

	return false;
}

bool utils::IntersectRectLine(const Rectf& r, const Point2f& p1, const Point2f& p2, float& intersectMin, float& intersectMax)
{

	return false;
}

#pragma endregion CollisionFunctionality

