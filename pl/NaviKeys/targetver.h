#pragma once

// Uwzglednienie elementu SDKDDKVer.h powoduje zdefiniowanie najnowszej dostepnej platformy systemu Windows.
// Jesli chcesz skompilowac aplikacje dla poprzedniej platformy systemu Windows, uwzglednij element WinSDKVer.h 
// i ustaw makro _WIN32_WINNT na platforme, ktora ma byc obslugiwana, przed uwzglednieniem elementu SDKDDKVer.h.
#include <SDKDDKVer.h>
