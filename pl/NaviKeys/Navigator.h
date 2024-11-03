#pragma once

#include "Framework.h"


const double PI = 3.1415926535897932384626433832795;


class CNavigator
{
public:
    // Biezaca lokalizacja w przestrzeni
    struct {
        double x;
        double y;
        double z;
        double q = 1.0;        // kwant przemieszczenia
    } Location;

    // Biezaca orientacja (katy przestrzenne Eulera)
    struct {
        double a;
        double b;
        double g;
        double q = PI / 36;    // kwant obrotu (5 deg)
    } Orientation;

    double Zoom = 1.0;

    VOID OnMoveLeft();
    VOID OnMoveForward();
    VOID OnMoveRight();
    VOID OnMoveBack();
    VOID OnLiftUp();
    VOID OnLowerDown();
    VOID OnPointUp();
    VOID OnPointLeft();
    VOID OnTiltLeft();
    VOID OnPointDown();
    VOID OnPointRight();
    VOID OnTiltRight();
    VOID OnZoomIn();
    VOID OnZoomOut();
    VOID GoHome();
};
extern CNavigator Navigator;




#define ALMOST(x, y) (fabs((x) - (y)) < (.5E-7))

inline double normalize(double Angle)
{
    // Jesli podany kat lezy na granicy dozwolonych wartosci, ...
    if (ALMOST(Angle, 0) || ALMOST(Angle, 2 * PI))
        // ... to natychmiastowe zwrocenie kata zerowego (wyliczenia zbedne)
        return 0;

    // Jesli podany kat przekracza (ujemnie lub dodatnio) kat pelny ...
    if (Angle <= -2 * PI || 2 * PI <= Angle)
        // ... zredukowanie wielokrotnosci kata pelnego
        Angle -= int(.5 * Angle / PI) * 2 * PI;

    // Zwrocenie znormalizowanego kata, przy czym gdy jego wartosc jest ujemna
    // wyliczane jest doplenienie dodatnie do kata pelnego
    return (Angle < 0) ? Angle + 2 * PI : Angle;
}


inline double toDeg(const double Angle) {
    // Przeliczenie miary lukowej [rad] na stopniowa [deg]
    return Angle * 180 / PI;
}


inline double toRad(const double Angle) {
    // Przeliczenie miary stopniowej [deg] na lukowa [rad]
    return Angle * PI / 180;
}
