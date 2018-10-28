#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H
#include <vector>
#include <iostream>

using std::vector;

class GridWorld {

  private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.

    int nrows, ncols;
	int totalPopulation = 0;

    // Doubly linked list for person array
    struct personArray{
    int id, row, col;
    bool checkIfAlive = false;
    personNode* dllPointer = nullptr; // Doubly linked list pointer
    personArray(int id, int row, int col, bool checkIfAlive, personNode* dllpointer){
    // store address for respectively linked lists
    this->id = id;
    this->row = row;
    this->col = col;
    this->checkIfAlive = checkIfAlive;
    this->dllPointer = dllPointer;
    }
};                                             
}
 List** gridWorldArray;
    List morgue;
                                                                                 // Doubly linked list for each person node
    struct personNode{                                                           int id;
    personNode* prev = nullptr;                                                  personNode* next = nullptr;
    personNode(int id, personNode * p = nullptr, personNode * n = nullptr){
    this->id = id;
    prev = p;
    next = n;
    }

    // DLL to traverse through person list
    struct List{
    int listLength = 0;
    personNode* front = nullptr;
    personNode* back = nullptr;
    }
};


  public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all
    *    districtricts are empty (a wasteland!).
    */
    // your constructor code here!
    // new array for GridWorld district
    GridWorld(unsigned nrows, unsigned ncols){
        gridWorldArray = new List*[nrows];
        for(int i = 0; i < nrows; i++){
            gridWorldArray[i] = new List[ncols];
        }

        this->nrows = nrows; // store address of nrows
        this->ncols = ncols; // ncols address
	//	this.personID = personID;

    }
    ~GridWorld(){
      // your destructor code here.
      // NTS: i == nrow, j == ncols
      int i, j;
      for(i = 0; i < nrows; i++){
        for(j = 0; j < ncols; j++){
            if(gridWorldArray[i][j]->front != nullptr){  // as long as front of array is not nullptr set to temp Node to then clear list
                personNode * temp = gridWorldArray[i][j]->front;
                if(personNode(&gridWorldArray[i][j]), temp)
                delete temp;
          }
        }
      }
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
    bool birth(int row, int col, int &id){
        // check if user input is invalid
        if(row < 0 || row >= nrows || col < 0 || col >= ncols)
        return false;
    }

    /*
     * function: death
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){

      return false;
    }
        // check if morgue is empty by iterating listLength struct
        if(morgue->listLength == 0)
    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int personID, int &row, int &col)const{
      return false;
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int personID, int targetRow, int targetCol){
      return false;
    }

    std::vector<int> * members(int row, int col)const{

      return nullptr;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
      return (totalPopulation - morgue.listLength); // subtracts morgue from totalPopulation
    }

    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
        if(row < 0 || row >= nrows || col < 0 || col >= ncols){ // check to see if user input a valid district
        return 0;
    }

    return gridWorldArray[row][col].listLength; // return district pop
}
    /*
     * function: num_rows
     * description:  returns number of rows in world
     */

    int num_rows()const {
      return nrows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
      return ncols;
    }
};
#endif
