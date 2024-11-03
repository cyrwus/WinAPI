#include "Navigator.h"
#include "MainWindow.h"
#include "StatusBar.h"


//------------------------------------------------------------------------------
// Obsluga polecenia "Powrot na start"
//
VOID CNavigator::GoHome()
{
    // Ustawienie lokalizacji w punkcie zerowym ...
    Location.x = 0.0;
    Location.y = 0.0;
    Location.z = 0.0;
    // ... oraz wyzerowanie rotacji ...
    Orientation.a = 0.0;
    Orientation.b = 0.0;
    Orientation.g = 0.0;
    // ... i zresetowanie zoom
    Zoom = 1.0;
}


//------------------------------------------------------------------------------
// Obsluga polecenia "Ruch w prawo"
// 
VOID CNavigator::OnMoveRight()
{
    // Przemieszczenie wzdluz osi X w strone dodatnia
    Location.x += Location.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Ruch w lewo"
//
VOID CNavigator::OnMoveLeft()
{
    // Przemieszczenie wzdluz osi X w strone ujemna
    Location.x -= Location.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Ruch do przodu"
//
VOID CNavigator::OnMoveForward()
{
    // Przemieszczenie wzdluz osi Z w strone dodatnia
    Location.z += Location.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Ruch do tylu"
//
VOID CNavigator::OnMoveBack()
{
    // Przemieszczenie wzdluz osi Z w strone ujemna
    Location.z -= Location.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Ruch do gory"
//
VOID CNavigator::OnLiftUp()
{
    // Przemieszczenie wzdluz osi Y w strone dodatnia
    Location.y += Location.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Ruch do dolu"
//
VOID CNavigator::OnLowerDown()
{
    // Przemieszczenie wzdluz osi Y w strone ujemna
    Location.y -= Location.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Obrot do gory"
//
VOID CNavigator::OnPointUp()
{
    // Rotacja wokol osi X przeciwnie do ruchu wsk. zegara,
    // czyli o dodatni kat alpha
    Orientation.a += Orientation.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Obrot do dolu"
//
VOID CNavigator::OnPointDown()
{
    // Rotacja wokol osi X zgodnie z ruchem wsk. zegara,
    // czyli o ujemny kat alpha
    Orientation.a -= Orientation.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Obrot w lewo"
//
VOID CNavigator::OnPointLeft()
{
    // Rotacja wokol osi Y przeciwnie do ruchu wsk. zegara,
    // czyli o dodatni kat beta
    Orientation.b += Orientation.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Obrot w prawo"
//
VOID CNavigator::OnPointRight()
{
    // Rotacja wokol osi Y zgodnie z ruchem wsk. zegara,
    // czyli o ujemny kat beta
    Orientation.b -= Orientation.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Przechyl w lewo"
//
VOID CNavigator::OnTiltLeft()
{
    // Rotacja wokol osi Z przeciwnie do ruchu wsk. zegara,
    // czyli o dodatni kat gamma
    Orientation.g += Orientation.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Przechyl w prawo"
//
VOID CNavigator::OnTiltRight()
{
    // Rotacja wokol osi Z zgodnie z ruchem wsk. zegara,
    // czyli o ujemny kat gamma
    Orientation.g -= Orientation.q;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Przyblizenie widoku"
//
VOID CNavigator::OnZoomIn()
{
    Zoom *= 1.125;
};


//------------------------------------------------------------------------------
// Obsluga polecenia "Oddalenie widoku"
//
VOID CNavigator::OnZoomOut()
{
    Zoom /= 1.125;
};
