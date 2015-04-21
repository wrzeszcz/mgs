MGS
=============
ver. 0.1 2015

Program oparty na koncepcji blokowego modelu złoża, pozwala na obliczenie zasobów metodą mini-bloków 
z wykorzystaniem metod geostatycznych (interpolacji metodą krigingu zwykłego) 
lub deterministycznych (interpolacji metodą odwrotnych odległości).

Aplikacja składa się z dwóch głównych modułów: obliczeniowego i graficznego. 
Moduł obliczeniowy napisany jest w języku C++ z wykorzystaniem bibliotek szablonów STL
oraz TNT do obliczeń algebry liniowej. 
Interfejs graficzny zrealizowany jest z wykorzystaniem biblioteki Qt oraz OpenGL. 
Aplikacje wykonano w wieloplatformowym środowisku programistycznym QtCreator co pozwala, 
bez modyfikacji kodu źródłowego na kompilacje na platformy Windows i Linux.

Wykonany program może być traktowany jako uproszczony kalkulator do wstępnego szacowania zasobów. 
Może również stanowić platformę dydaktyczną lub testową dla implementacji i wizualizacji algorytmów geostatystycznych, 
interpolator dowolnych danych przestrzennych lub edukacyjną prezentację metodyki modelowania blokowego złóż oraz
szacowania ich zasobów.
