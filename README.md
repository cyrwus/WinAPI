# Windows API C/C++ w przykładach

Repozytorium zawiera przykłady prostych programów w języku C/C++, które demonstrują użycie podstawowych funkcji *Windows API*. 

## Wykaz projektów
* [SimpleApp](./pl/SimpleApp/) — Minimalna aplikacja tworząca okno główne z menu. Zawiera także okienko dialogowe "O programie" zdefiniowane w pliku zasobów (resource-based dialog). Program nie posiada struktury obiektowej i wykorzystuje funkcje Windows API.

* [StatusBar](./pl/StatusBar/) — Prosta aplikacja oparta o Windows API z przykładem użycia paska statusowego (standardowej kontrolki systemowej). Zawiera okno główne z menu oraz pasek statusowy podzielony na sekcje. W sekcjach paska wyświetlany jest bieżący stan klawiszy przełącznikowych NumLock, CapsLock i ScrollLock. Pasek automatycznie dostosowuje szerokość wybranych sekcji, w reakcji na zmiany szerokości okna głównego.

* [NaviKeys](./pl/NaviKeys/) — Aplikacja bazująca na projekcie StatusBar, rozszerzona o obsługę klawiszy kursora oraz klawiszy specjalnych Shift i Ctrl, w celu nawigowania w przestrzeni. Z poziomu menu głównego można włączać i wyłączać pasek statusowy. W licznych sekcjach paska wyświetlany jest bieżący stan klawiszy przełącznikowych oraz pełna, dynamicznie aktualizowana informacja o położeniu obserwatora, w tym jego współrzędne oraz kąty rotacji w przestrzeni 3D. Opis klawiszy nawigacyjnych dostępny jest w oknie dialogowym „Klawisze nawigacyjne”. Zarówno to okno, jak i okienko „O programie” zdefiniowane są jako zasoby (resource-based dialog).
