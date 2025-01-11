Data-structures-and-algorithms-course-project. 


The project for the "Data Structures and Algorithms" course involves files I modified: datastructures.cc and datastructures.hh. 
These files implement custom data structures and algorithms for processing data. 
In summary, the project deals with contours and bites located on them. 
Both the bites and the contours have coordinates and can be linked to one another. 
The methods I implemented handle the relationships and coordinates between them. 

The key aspects of the project that come to mind are: optimization of efficiency, calculating efficiency, and the design of algorithms and data structures.


-----------------------------------------------------------------------------------------------------------------------------------------------------------
These are the Bite and Contour datastructures:

    struct Bite{
        BiteID id_ = 0;
        Name name_ = "";
        Coord coord_ = {NO_COORD};      //Bite coordinates
        Contour* contour_ = nullptr;   //Keeps track if contour is linked
    };


      struct Contour{
        ContourID id_= 0;
        Name name_ = "";                                      //Difference in height between surface level and contour
        ContourHeight height_ = 0;                            //Height
        std::vector<Coord> coords_ = {};                      //Contour coordinates

        Contour* parent_ = nullptr;                           //Contour can have only one parent
        std::vector<std::shared_ptr<Contour>> childs_ = {};   //Contour can have multiple children
        std::vector<std::shared_ptr<Bite>> bites_ = {};       //Keeps track of linked Bites
    };

        //Bite datastructures
    std::unordered_map<BiteID, Bite> bites_ = {};
    std::unordered_set<Coord> bite_coords_ = {};

      //Contour datastructures
    std::unordered_map<ContourID, Contour> contours_ = {};
