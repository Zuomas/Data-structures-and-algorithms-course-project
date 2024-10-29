/**
 * @brief The Datastructures class
 * STUDENTS: Modify the code below to implement the functionality of the class.
 * Also remove comments from the parameter names when you implement an operation
 * (Commenting out parameter name prevents compiler from warning about unused
 * parameters on operations you haven't yet implemented.)
 */

#include "datastructures.hh"
#include "customtypes.hh"

Datastructures::Datastructures()
{
  // Write any initialization you need here
}

Datastructures::~Datastructures()
{
  // Write any cleanup you need here
}

unsigned int Datastructures::get_bite_count()
{
    return bites_.size();

}

void Datastructures::clear_all()
{
    //Korvataan tietorakenteet tyhjillä tietorakenteilla
    bites_ = {};
    contours_ = {};
    bite_coords_ = {};

    bitesAlphabetically_ = {};
    sortedBitesAlphabetically_ = {};
    bitesByDistance_ = {};
    sortedBitesByDistance_ = {};

}

std::vector<BiteID> Datastructures::all_bites()
{
    std::vector<BiteID> all_bites_id = {};

    for (auto& bite : bites_){
        all_bites_id.push_back(bite.first);
    }

    return all_bites_id;
}

bool Datastructures::add_bite(BiteID id, const Name & name, Coord xy)
{

    auto bite = bites_.find(id);
    if(bite != bites_.end()){  //Löytyykö bite. Jos löytyy, palautetaan false
        return false;
    }
    auto coord = bite_coords_.find(xy);
    if(coord != bite_coords_.end()){  //Onko koordinaatti jo käytössä
        return false;
    }

    Bite newBite = {id, name, xy};  //Lisätään bites_ tietorakenteeseen olio
    bites_ [id] = newBite;

    bite_coords_.insert(xy);    //Lisätään vektoriin käytetyt koordinaatit


    bitesAlphabetically_.insert(newBite);   //Oliot järjestettynä nimen mukaan
    bitesByDistance_.insert(newBite);       //Oliot järjestettynä etäisyyden mukaan
    alphabeticallyChanged_ = 1;
    ByDistanceChanged_ = 1;

    return true;
}

Name Datastructures::get_bite_name(BiteID id)
{
   if(auto bite = bites_.find(id); bite != bites_.end()){
        return bite->second.name_;
   }else{
       return NO_NAME;
   }
}

Coord Datastructures::get_bite_coord(BiteID id)
{
    if (auto bite = bites_.find(id); bite != bites_.end())
    {
        return bite->second.coord_;
    }

    return NO_COORD;
}

std::vector<BiteID> Datastructures::get_bites_alphabetically()
{
    if(alphabeticallyChanged_){
        sortedBitesAlphabetically_ = {};

        for(auto &bite : bitesAlphabetically_){
            sortedBitesAlphabetically_.push_back(bite.id_);//vektoriin lisäys
            alphabeticallyChanged_ = 0;
        }
    }

    return sortedBitesAlphabetically_;

}

std::vector<BiteID> Datastructures::get_bites_distance_increasing()
{

    if(ByDistanceChanged_){
        sortedBitesByDistance_ = {};

        for(auto &bite : bitesByDistance_){
            sortedBitesByDistance_.push_back(bite.id_);//vektoriin lisäys
            ByDistanceChanged_ = 0;
        }
    }

    return sortedBitesByDistance_;

}

BiteID Datastructures::find_bite_with_coord(Coord xy)
{
for(auto& bite : bites_){
        if(bite.second.coord_ == xy){
            return bite.first;
        }
    }
    return NO_BITE;

}

bool Datastructures::change_bite_coord(BiteID id, Coord newcoord)
{
    auto bite = bites_.find(id);
    if(bite == bites_.end()){  //Löytyykö bite. Jos ei, palautetaan tyhjä false
      return false;
    }
    Coord old_coord = bite->second.coord_;

    auto coord = bite_coords_.find(newcoord);
    if(coord != bite_coords_.end()){  //Löytyykö bite. Jos ei, palautetaan tyhjä false
        return false;
    }

    if(bite->second.contour_ != nullptr){           //Jos bite sijoitettuna käyrälle, tarkistetaan onko haluttu koordinaatti contour koordinaateissa
        std::vector<Coord> coords = bite->second.contour_->coords_;

        auto it = std::find(coords.begin(), coords.end(), newcoord); //bite->second.coord_
        if (it != coords.end()) {
            return false;
        }
    }

    bite->second.coord_ = newcoord;
    bite_coords_.insert(newcoord);
    bite_coords_.erase(old_coord);
    ByDistanceChanged_ = 1;

    return true;

}

bool Datastructures::add_contour(ContourID id, const Name & name, ContourHeight height,
                                 std::vector<Coord> coords)
{

    auto contour = contours_.find(id);
    if(contour != contours_.end()){  //Löytyykö samall id:lla käyrää
        return false;

    }else if(coords.size() <= 0){   //Saatu koordinaattilista on tyhjä
        return false;

    }else if(height > MAX_CONTOUR_HEIGHT || height < -MAX_CONTOUR_HEIGHT){   //Korkeus ei kelpaa
        return false;
    }

    Contour newContour = {id, name, height, coords};//Lisätään käyrä
    contours_ [id] = newContour;
    return true;
}

std::vector<ContourID> Datastructures::all_contours()
{
    std::vector<ContourID> all_contour_id = {};

    for (auto& contour : contours_){
        all_contour_id.push_back(contour.first);
    }

    return all_contour_id;

}

Name Datastructures::get_contour_name(ContourID id)
{
    if(auto contour = contours_.find(id); contour != contours_.end()){
        return contour->second.name_;
    }else{
        return NO_NAME;
    }
}

std::vector<Coord> Datastructures::get_contour_coords(ContourID id)
{
    if(auto contour = contours_.find(id); contour != contours_.end()){
        return contour->second.coords_;
    }else{
        std::vector<Coord> no_coord = {NO_COORD};
        return no_coord;
    }
}

ContourHeight Datastructures::get_contour_height(ContourID id)
{
    if(auto contour = contours_.find(id); contour != contours_.end()){
        return contour->second.height_;
    }else{
        return NO_CONTOUR_HEIGHT;
    }
}

bool Datastructures::add_subcontour_to_contour(ContourID id,
                                               ContourID parentid)
{
    auto child = contours_.find(id);
    auto parent = contours_.find(parentid);

    if(child == contours_.end()){  //Löytyykö lapsikäyrä
        return false;

    }
    else if(parent == contours_.end()){    //Löytyykö vanhempi käyrä
        return false;
    }
    else if(child->second.parent_ != nullptr){
        return false;

    }
    else if(std::abs(child->second.height_) < std::abs(parent->second.height_)){
         return false;

    }
    else if((std::abs(child->second.height_ -parent->second.height_)) != 1 ){
          return false;

        }
    else{

            child->second.parent_ = &parent->second;                                //Asetetaan child:lle vanhempi "parent"
            parent->second.childs_.push_back(std::shared_ptr<Contour>(new Contour(child->second)));  // Add child to parent's children
            return true;
    }
}

bool Datastructures::add_bite_to_contour(BiteID biteid, ContourID contourid)
{
    auto bite = bites_.find(biteid);
    auto contour = contours_.find(contourid);
    if(bite == bites_.end()){  //Löytyykö bite. Jos ei, palautetaan false
        return false;
    }else if(contour == contours_.end()){  //Löytyykö contour. Jos ei, palautetaan false
        return false;
    }else if(bite->second.contour_ != nullptr){ //Onko bite:lla jo contour asetettuna
        return false;
    }else{
        for(const auto coords : contour->second.coords_){
            if(bite->second.coord_ == coords){
                bite->second.contour_ = &(contour->second);
                contour->second.bites_.push_back(std::make_shared<Bite>(bite->second));
                return true;    //Lisäämme Bite:n contour:iin
            }
        }
       return false;
    }
}

std::vector<ContourID> Datastructures::get_bite_in_contours(BiteID id)
{
    auto bite = bites_.find(id);
    if(bite == bites_.end()){  //Löytyykö bite. Jos ei, palautetaan tyhjä vektori
        return {NO_CONTOUR};
    }
    else if(bite->second.contour_ == nullptr) {
        return {};
    }


    std::vector<ContourID> contour_chain = {};
    Contour* current = bite->second.contour_;

    while (current != nullptr) {  //Tarkistetaan kuinka pitkään löytyy vanhempia, ja lisätään nämä palautettavaan vectoriin
        contour_chain.push_back(current->id_);
        current = current->parent_;
    }

    return contour_chain;  //Palautetaan biteen linkattu contour ketju

}

std::vector<ContourID>
Datastructures::all_subcontours_of_contour(ContourID id)
{
  //throw NotImplemented("all_subcontours_of_contour");
    auto contour = contours_.find(id);
    if(contour == contours_.end()){  //Löytyykö contour. Jos ei, palautetaan tyhjä vektori
        return {NO_CONTOUR};
    }

    std::vector<ContourID> subcontours_to_be_returned = {}; //Palautettava

    std::function<void(const Contour&)> collectSubcontours = [&](const Contour& contour) {
        for (const auto& childContour : contour.childs_) {
            // Lisätään lapsikorkeuskäyrän ID vektoriin
            subcontours_to_be_returned.push_back(childContour->id_);
            // Rekursiivisesti käydään lapsikorkeuskäyrän lapsikorkeudet
            collectSubcontours(*childContour);
        }
    };

    // Aloitetaan alikäyrien kerääminen annetusta korkeuskäyrästä
    collectSubcontours(contour->second);



    return subcontours_to_be_returned;

}

ContourID
Datastructures::get_closest_common_ancestor_of_contours(ContourID /*id1*/,
                                                        ContourID /*id2*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_closest_common_ancestor_of_contours");
}

bool Datastructures::remove_bite(BiteID id)
{
     // Replace the line below with your implementation
    auto bite = bites_.find(id);
        if(bite == bites_.end()){  //Löytyykö bite. Jos ei, palautetaan tyhjä vektori
            return false;
        }
    Coord removeCoord = bite->second.coord_;
    bites_.erase(id);
    bite_coords_.erase(removeCoord);


    //poistetaan aakkosjärjestyksestä bite
    auto itAlphabet = std::find_if(bitesAlphabetically_.begin(), bitesAlphabetically_.end(),
                                   [&id](const Bite& b) { return b.id_ == id; });
    if (itAlphabet != bitesAlphabetically_.end()) {
        bitesAlphabetically_.erase(itAlphabet);
        sortedBitesAlphabetically_ = {};
        alphabeticallyChanged_ = 1;
    }

    //Poistetaan manhattan-etäisyyysjärjestyksestä
    auto itDistance = std::find_if(bitesByDistance_.begin(), bitesByDistance_.end(),
                                   [&id](const Bite& b) { return b.id_ == id; });
    if (itDistance != bitesByDistance_.end()) {
        bitesByDistance_.erase(itDistance);
        sortedBitesByDistance_ = {};
        ByDistanceChanged_ = 1;
    }


    //Poistetaan bite siihen liittyvistä contour-rakenteista
    for (auto& [contourID, contour] : contours_) {
        auto itBite = std::find_if(contour.bites_.begin(), contour.bites_.end(),
                                   [&id](const std::shared_ptr<Bite>& b) { return b->id_ == id; });
        if (itBite != contour.bites_.end()) {
            contour.bites_.erase(itBite);
        }
    }

    return true;

    }


std::vector<BiteID> Datastructures::get_bites_closest_to(Coord /*xy*/)
{
  // Replace the line below with your implementation
  throw NotImplemented("get_bites_closest_to");
}






