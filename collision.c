#include "collision.h"
#include "figure.h"
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static int isPointInRect(Figure r_fig, double px, double py) {
  double rx, ry, rw, rh;
  getFigureXY(&rx, &ry, r_fig);
  getRectangleWH(r_fig, &rw, &rh);
  return (px >= rx && px <= rx + rw && py >= ry && py <= ry + rh);
}

static int orientation(double px, double py, double qx, double qy, double rx,
                       double ry) {
  double val = (qy - py) * (rx - qx) - (qx - px) * (ry - qy);
  if (fabs(val) < DBL_EPSILON)
    return 0;
  return (val > 0) ? 1 : 2;
}

static int onSegment(double px, double py, double qx, double qy, double rx,
                     double ry) {
  return (qx <= fmax(px, rx) && qx >= fmin(px, rx) && qy <= fmax(py, ry) &&
          qy >= fmin(py, ry));
}

static int overlapLineLine(double p1x, double p1y, double p2x, double p2y,
                           double p3x, double p3y, double p4x, double p4y) {
  int o1 = orientation(p1x, p1y, p2x, p2y, p3x, p3y);
  int o2 = orientation(p1x, p1y, p2x, p2y, p4x, p4y);
  int o3 = orientation(p3x, p3y, p4x, p4y, p1x, p1y);
  int o4 = orientation(p3x, p3y, p4x, p4y, p2x, p2y);
  if (o1 != o2 && o3 != o4)
    return 1;
  if (o1 == 0 && onSegment(p1x, p1y, p3x, p3y, p2x, p2y))
    return 1;
  if (o2 == 0 && onSegment(p1x, p1y, p4x, p4y, p2x, p2y))
    return 1;
  if (o3 == 0 && onSegment(p3x, p3y, p1x, p1y, p4x, p4y))
    return 1;
  if (o4 == 0 && onSegment(p3x, p3y, p2x, p2y, p4x, p4y))
    return 1;
  return 0;
}

static int overlapCircleCircle(Figure c1, Figure c2) {
  double x1, y1, r1, x2, y2, r2;
  getFigureXY(&x1, &y1, c1);
  r1 = getCircleR(c1);
  getFigureXY(&x2, &y2, c2);
  r2 = getCircleR(c2);
  double distSq = pow(x1 - x2, 2) + pow(y1 - y2, 2);
  double radiusSum = r1 + r2;
  return distSq <= (radiusSum * radiusSum);
}

static int overlapRectangleRectangle(Figure r1, Figure r2) {
  double r1x, r1y, r1w, r1h;
  double r2x, r2y, r2w, r2h;
  getFigureXY(&r1x, &r1y, r1);
  getRectangleWH(r1, &r1w, &r1h);
  getFigureXY(&r2x, &r2y, r2);
  getRectangleWH(r2, &r2w, &r2h);
  int overlapX = (r1x < r2x + r2w) && (r1x + r1w > r2x);
  int overlapY = (r1y < r2y + r2h) && (r1y + r1h > r2y);
  return overlapX && overlapY;
}

static int overlapCircleRectangle(Figure c, Figure r) {
  double cx, cy, cr;
  double rx, ry, rw, rh;
  getFigureXY(&cx, &cy, c);
  cr = getCircleR(c);
  getFigureXY(&rx, &ry, r);
  getRectangleWH(r, &rw, &rh);
  double closestX = fmax(rx, fmin(cx, rx + rw));
  double closestY = fmax(ry, fmin(cy, ry + rh));
  double distSq = pow(cx - closestX, 2) + pow(cy - closestY, 2);
  return distSq <= (cr * cr);
}

static int overlapCircleLine(Figure c, double x1, double y1, double x2,
                             double y2) {
  double cx, cy, cr;
  getFigureXY(&cx, &cy, c);
  cr = getCircleR(c);
  double dx = x2 - x1;
  double dy = y2 - y1;
  double lenSq = dx * dx + dy * dy;
  double t;
  if (lenSq < DBL_EPSILON)
    t = 0.0;
  else
    t = ((cx - x1) * dx + (cy - y1) * dy) / lenSq;
  t = fmax(0.0, fmin(1.0, t));
  double closestX = x1 + t * dx;
  double closestY = y1 + t * dy;
  double distSq = pow(cx - closestX, 2) + pow(cy - closestY, 2);
  return distSq <= (cr * cr);
}

static int overlapRectangleLine(Figure r, double x1, double y1, double x2,
                                double y2) {
  if (isPointInRect(r, x1, y1) || isPointInRect(r, x2, y2))
    return 1;
  double rx, ry, rw, rh;
  getFigureXY(&rx, &ry, r);
  getRectangleWH(r, &rw, &rh);
  double rx2 = rx + rw;
  double ry2 = ry + rh;
  if (overlapLineLine(x1, y1, x2, y2, rx, ry, rx2, ry))
    return 1;
  if (overlapLineLine(x1, y1, x2, y2, rx, ry2, rx2, ry2))
    return 1;
  if (overlapLineLine(x1, y1, x2, y2, rx, ry, rx, ry2))
    return 1;
  if (overlapLineLine(x1, y1, x2, y2, rx2, ry, rx2, ry2))
    return 1;
  return 0;
}

int figuresOverlap(Figure f1, Figure f2) {
  if (!f1 || !f2)
    return 0;
  int type1 = getFigureType(f1);
  int type2 = getFigureType(f2);
  double f1_lx1, f1_ly1, f1_lx2, f1_ly2;
  double f2_lx1, f2_ly1, f2_lx2, f2_ly2;
  if (type1 == LINE)
    getLineP(f1, &f1_lx1, &f1_ly1, &f1_lx2, &f1_ly2);
  else if (type1 == TEXT)
    getTextP(f1, &f1_lx1, &f1_ly1, &f1_lx2, &f1_ly2);
  if (type2 == LINE)
    getLineP(f2, &f2_lx1, &f2_ly1, &f2_lx2, &f2_ly2);
  else if (type2 == TEXT)
    getTextP(f2, &f2_lx1, &f2_ly1, &f2_lx2, &f2_ly2);

  if (type1 == CIRCLE) {
    if (type2 == CIRCLE) {
      return overlapCircleCircle(f1, f2);
    } else if (type2 == RECTANGLE) {
      return overlapCircleRectangle(f1, f2);
    } else if (type2 == LINE || type2 == TEXT) {
      return overlapCircleLine(f1, f2_lx1, f2_ly1, f2_lx2, f2_ly2);
    }
  } else if (type1 == RECTANGLE) {
    if (type2 == CIRCLE) {
      return overlapCircleRectangle(f2, f1);
    } else if (type2 == RECTANGLE) {
      return overlapRectangleRectangle(f1, f2);
    } else if (type2 == LINE || type2 == TEXT) {
      return overlapRectangleLine(f1, f2_lx1, f2_ly1, f2_lx2, f2_ly2);
    }
  } else if (type1 == LINE || type1 == TEXT) {
    if (type2 == CIRCLE) {
      return overlapCircleLine(f2, f1_lx1, f1_ly1, f1_lx2, f1_ly2); // Reusa
    } else if (type2 == RECTANGLE) {
      return overlapRectangleLine(f2, f1_lx1, f1_ly1, f1_lx2, f1_ly2); // Reusa
    } else if (type2 == LINE || type2 == TEXT) {
      return overlapLineLine(f1_lx1, f1_ly1, f1_lx2, f1_ly2, f2_lx1, f2_ly1,
                             f2_lx2, f2_ly2);
    }
  }
  return 0;
}
