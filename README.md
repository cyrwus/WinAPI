# Windows API C/C++ w przykładach

## Wprowadzenie
Repozytorium zawiera przykłady prostych programów w języku C/C++, które demonstrują użycie podstawowych funkcji *Windows API*. Projekty zostały przygotowane z myślą o osobach, które chcą poznać praktyczne zastosowania API Windows w tworzeniu aplikacji okienkowych. Każdy projekt pokazuje, jak korzystać z różnych elementów systemowych, takich jak okna dialogowe, paski menu, paski statusu itp.
Zasób będzie stopniowo rozbudowywany o kolejne przykłady.

## Spis
* [SimpleApp](./pl/SimpleApp/)
 - Minimalna aplikacja oparta o Windows API. Zawiera okno główne z menu, a także okienko dialogowe "O programie" o strukturze zdefiniowanej w zasobach (resource-based dialog).

* [StatusBar](./pl/StatusBar/)
Prosta aplikacja oparta o Windows API z przykładem użycia paska statusowego (standardowej kontrolki systemowej). Zawiera okno główne z menu oraz pasek statusowy podzielony na sekcje. W sekcjach paska wyświetlany jest bieżący stan 
 - klawiszy przełącznikowych NumLock, CapsLock i ScrollLock.

* [NaviKeys](./pl/NaviKeys/)
 - Aplikacja bazująca na rozwiązaniu StatusBar, mocniej wykorzystująca obsługę klawiszy specjalnych takich jak Shift, Ctrl, w połączeniu z klawiszami kursora, w celu nawigowania w trójwymiarowej przestrzeni. Z dostępnego w oknie głównym menu można wybrać widoczność paska statusowego. Liczne sekcje paska wyświetlają nie tylko bieżący stan klawiszy przełącznikowych lecz również na bieżąco wyliczane położenie obserwatora, tj. jego lokalizację oraz orientację/rotację w przestrzeni 3D. Kombinacje klawiszy służące do nawigowania zostały opisane w okienku dialogowym "Klawisze nawigacyjne". Podobnie jak ono, również okienko dialogowe "O programie" zdefiniowano jako zasób (resource-based dialog).
