:- ensure_loaded(borders).
:- ensure_loaded(cities).
:- ensure_loaded(countries).
:- ensure_loaded(rivers).

?- country(X, _, _, _, _, _, _, _), borders(france, X), borders(spain, X).

country(C) :-
    country(C, _, _, _, _, _, _, _).

larger(Country1, Country2) :-

    country(Country1, _, _, _, Area1, _, _, _), 
    country(Country2, _, _, _, Area2, _, _, _), 
    Area1 > Area2.

river_country(River, Country) :-
   country(Country),
   river(River, Cs),
   member(Country, Cs).

country_region(Country, Region) :-
    country(Country, Region, _, _, _, _, _, _).

river_2region(River) :-
    river_country(River, C1),
    river_country(River, C2),
    country_region(C1, R1),
    country_region(C2, R2),
    R1 \= R2.
