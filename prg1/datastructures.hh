// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include "customtypes.hh"
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <memory>
#include <set>
#include <unordered_set>

// Add your own STL includes below this comment

template <typename Type>
Type random_in_range(Type start, Type end);

// This is the class you are supposed to implement

class Datastructures
{
public:
  Datastructures();
  ~Datastructures();

  // Estimate of performance: O(1)
  // Short rationale for estimate: map.size() on vakioaikainen
  unsigned int get_bite_count();

  // Estimate of performance: O(1)
  // Short rationale for estimate: Vapautamme tietorakenteiden muistinvarauksen vakioajassa O(1)
  void clear_all();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Map läpi käyminen on O(n) ja vectoriin pushback() tapahtuu pääasiallisesti ajassa O(1)
  std::vector<BiteID> all_bites();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Vertaamme map- ja set-tietorakenteisiin arvoa, ja tässä lisäys- sekä etsintä-operaatiot
  //tapahtuvat keskimäärin nopeudella O(n)
  bool add_bite(BiteID /*id*/, const Name & /*name*/, Coord /*xy*/);

  // Estimate of performance: O(n)
  // Short rationale for estimate: etsimme unordered_map-tietorakenteesta arvoja, joka tapahtuu O(n) -nopeudella
  Name get_bite_name(BiteID /*id*/);

  // Estimate of performance: O(n)
  // Short rationale for estimate: etsimme unordered_map-tietorakenteesta arvoja, joka tapahtuu O(n) -nopeudella
  Coord get_bite_coord(BiteID /*id*/);

  // We recommend you implement the operations below only after implementing the
  // ones above

  // Estimate of performance: O(n)
  // Short rationale for estimate: Järjestäminen suoritetaan set-tietorakenteeseen järjestämällä, joka on O(log n)
  //Hidasteena on for loop, jossa käydään alkiot läpi, jolloin nopeus on O(n)
  std::vector<BiteID> get_bites_alphabetically();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Järjestäminen suoritetaan set-tietorakenteeseen järjestämällä, joka on O(log n)
  //Hidasteena on for loop, jossa käydään alkiot läpi, jolloin nopeus on O(n)
  std::vector<BiteID> get_bites_distance_increasing();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Pahimmassa tapauksessa joudutaan käymään kaikki map oliot läpi, jolloin se on O(n)
  BiteID find_bite_with_coord(Coord /*xy*/);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Käymme kaikki bites_ läpi sekä etsimme contourin koordinaatit. Molemmat tapahtuu ajassa O(n)
  bool change_bite_coord(BiteID /*id*/, Coord /*newcoord*/);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Metodi on O(n) koska vektori kopioidaan, joka suoritetaan ajassa O(n)
  //unordered_map -tietorakenteesta etsiminen
  bool add_contour(ContourID /*id*/, const Name & /*name*/, ContourHeight /*height*/,
                   std::vector<Coord> /*coords*/);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Käymme kaikki käyrät läpi ja lisäämme ne vektorin perään. O(n)
  std::vector<ContourID> all_contours();

  // Estimate of performance: O(n)
  // Short rationale for estimate: Etsimme unordered_map -tietorakenteesta, joka tapahtuu pajimmillaan ajassa O(n)
  Name get_contour_name(ContourID /*id*/);

  // Estimate of performance: O(n) ≈ Θ(1)
  // Short rationale for estimate: Etsimme unordered_map tietorakenteesta avaimella, O(n) ≈ Θ(1)
  std::vector<Coord> get_contour_coords(ContourID /*id*/);

  // Estimate of performance: O(n) ≈ Θ(1)
  // Short rationale for estimate: Etsimme unordered_map tietorakenteesta avaimella, O(n) ≈ Θ(1)
  ContourHeight get_contour_height(ContourID /*id*/);

  // Estimate of performance: O(n) ≈ Θ(1)
  // Short rationale for estimate: Etsimme kahdesta unordered_map tietorakenteesta avaimella, O(n) ≈ Θ(1)
  bool add_subcontour_to_contour(ContourID /*id*/, ContourID /*parentid*/);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Joudumme käymään vektorin koordinaatit läpi, jonka vuoksi O(n)
  bool add_bite_to_contour(BiteID biteid, ContourID /*parentid*/);

  // Estimate of performance: O(n)
  // Short rationale for estimate: Joudumme käymään subcontourit läpi osoittimien kautta
  std::vector<ContourID> get_bite_in_contours(BiteID /*id*/);

  // Non-compulsory operations

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<ContourID> all_subcontours_of_contour(ContourID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  std::vector<BiteID> get_bites_closest_to(Coord /*xy*/);

  // Estimate of performance:O(n^2)
  // Short rationale for estimate:Joudumme käymään contour tietorakenteen läpi, jonka sisässä mäymme bitet sisältävän vektorin läpi.
  bool remove_bite(BiteID /*id*/);

  // Estimate of performance:
  // Short rationale for estimate:
  ContourID get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                    ContourID /*id2*/);

private:
  // Add stuff needed for your class implementation here

    struct Contour;


    //Omatekemä tietorakenne suupaloille. Suupalat ovat yksilöitä ja jokaisella suupapalla oma koordinaatti.
    struct Bite{

        BiteID id_ = 0;
        Name name_ = "";
        Coord coord_ = {NO_COORD};

        Contour* contour_ = nullptr;

    };


    //Omatekemä korkeuskäyrä, jossa useita koordinaatteja listana. Jokaisella korkeuskäyrällä on korkeus, joka poikkeaa
    //maanpinnan tasosta, jonka korkeus on 0.
    struct Contour{

        ContourID id_= 0;
        Name name_ = "";                                    //Poikkeuma maan pinnan tasosta, joka on 0
        ContourHeight height_ = 0;                          //Korkeus
        std::vector<Coord> coords_ = {};                    //Käyrän koordinaatit

        Contour* parent_ = nullptr;                         //Korkeuskäyrällä voi olla yksi vanhempi
        std::vector<std::shared_ptr<Contour>> childs_ = {};                 //korkeuskäyrällä voi olla monta lasta
        std::vector<std::shared_ptr<Bite>> bites_ = {};      //Pitää kirjaa käyrään yhdistetyistä suupaloista

    };


    //Bites tietorakenteet
    std::unordered_map<BiteID, Bite> bites_ = {};
    std::unordered_set<Coord> bite_coords_ = {};

    //Contour tietorakenteet
    std::unordered_map<ContourID, Contour> contours_ = {};


    /*-------------OPTIMOINTI---------------*/

    //Aakkoset
    static bool compareByAlphabets(const Bite& b1, const Bite& b2) {

        if(b1.name_ != b2.name_){
            return b1.name_ < b2.name_;  // Järjestetään nimen mukaan
        }else{
            return b1.id_ < b2.id_;  // Jos etäisyys on sama, järjestetään id:n mukaan
        }
    };
    //Tietorakenteet aakkosjärjestykselle
    std::set<Bite, decltype(&compareByAlphabets)> bitesAlphabetically_{&compareByAlphabets};
    std::vector<BiteID> sortedBitesAlphabetically_ = {};
    bool alphabeticallyChanged_ = 0;



    //Etäisyys
    static bool compareByManhattan(const Bite& b1, const Bite& b2) {
        int distance1 = std::abs(b1.coord_.x) + std::abs(b1.coord_.y);
        int distance2 = std::abs(b2.coord_.x) + std::abs(b2.coord_.y);
        // Jos etäisyydet ovat samat, vertaillaan ID:tä
        if(distance1 != distance2){
            return distance1 < distance2;
        }else{
            return b1.id_ < b2.id_;
        }
    };
    //Tietorakenteet manhattan-etäisyydelle
    std::set<Bite, decltype(&compareByManhattan)> bitesByDistance_{&compareByManhattan};
    std::vector<BiteID> sortedBitesByDistance_ = {};
    bool ByDistanceChanged_ = 0;




};

#endif // DATASTRUCTURES_HH
