# Windows API C/C++ w przykładach

## Wprowadzenie
Repozytorium zawiera przykłady prostych programów w języku C/C++, które demonstrują użycie podstawowych funkcji *Windows API*. Projekty zostały przygotowane z myślą o osobach, które chcą poznać praktyczne zastosowania API Windows w tworzeniu aplikacji okienkowych. Każdy projekt pokazuje, jak korzystać z różnych elementów systemowych, takich jak okna dialogowe, paski menu, paski statusu itp.
Zasób będzie stopniowo rozbudowywany o kolejne przykłady.

## Spis
* [SimpleApp](./pl/SimpleApp/) — Minimalna aplikacja oparta o Windows API. Zawiera okno główne z menu, a także okienko dialogowe "O programie" o strukturze zdefiniowanej w zasobach (resource-based dialog).

* [StatusBar](./pl/StatusBar/) — Prosta aplikacja oparta o Windows API z przykładem użycia paska statusowego (standardowej kontrolki systemowej). Zawiera okno główne z menu oraz pasek statusowy podzielony na sekcje. W sekcjach paska wyświetlany jest bieżący stan klawiszy przełącznikowych NumLock, CapsLock i ScrollLock.

* [NaviKeys](./pl/NaviKeys/) — Aplikacja bazująca na rozwiązaniu StatusBar, rozszerzona o obsługę klawiszy kursora oraz klawiszy specjalnych Shift i Ctrl, w celu nawigowania w przestrzeni. Z poziomu menu głównego można włączać i wyłączać pasek statusowy, który w licznych sekcjach wyświetla bieżący stan klawiszy przełącznikowych oraz pełną, dynamicznie aktualizowaną informację o położeniu obserwatora, w tym jego współrzędne oraz kąty rotacji w przestrzeni 3D. Opis klawiszy nawigacyjnych dostępny jest w oknie dialogowym „Klawisze nawigacyjne”. Zarówno to okno, jak i okno „O programie” są zdefiniowane jako zasoby (resource-based dialog).
