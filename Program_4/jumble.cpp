#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <algorithm>


void ssort(std::string &s) {
  std::sort(s.begin(), s.end());
}

/*int sizeOfLargestClass(std::unordered_map<std::string, std::vector<std::string>> hashTable){
    int  max = 0;
    for(auto &elem : hashTable){
		std::cout << elem.first << ":"  <<  std::endl;
	  //  if(hashTable.length() > max){
      //      max = hashTable.length();
        }
     return max;
}*/

int main(int argc, char *argv[]){

  std::unordered_map<std::string, std::vector<std::string>> hashTable;
  int numberOfWords = 0;
 
 std::ifstream file;
  std::string word;

  if(argc != 2) {
    std::cout << "usage:  ./jumble <filename>\n";
    std::cout << "goodbye\n";
    return 1;
  }
  file.open(argv[1], std::ios::in);

  if(!file.is_open()){
    std::cout << "Error: could not open file '" <<
                     argv[1] << "'\n";
    std::cout << "goodbye\n";
    return 1;
  }

  std::cout << "reading input file...\n";

//------------------------------------------------------------------------------

  //to not print the last word twice
  while(file >> word) {
    //increment the number of words each time you count a word
    numberOfWords++;

     //prevent from losing the actual word when you sort it alphabetically 
     std::string temp = word;
     //call function ssort and the parameter is temp because that is what we are sorting
     ssort(temp);
    
    //find key in hash table, if this is true, the key was not in the hash table
    if(hashTable.find(temp) == hashTable.end()){
    //create a vector to put the word inside it
    std::vector<std::string> valueToHash;
    //append word to the end of the vector
    valueToHash.push_back(word);
    //insert key and value into hash table
    hashTable.insert(make_pair(temp, valueToHash)); 
    }else{
        //set vector to a temp vector. copy vector from the hash table into a temp vector
        std::vector<std::string> tempVector(hashTable[temp]);
        tempVector.push_back(word);
        //is accessing our hash table using the key and set it to temp vector
        hashTable[temp] = tempVector;
    }
  }

  long unsigned int largestClass = 0;
  std::string largestKey = "";
  for(std::pair<std::string, std::vector<std::string>> n: hashTable){
	if(n.second.size() > largestClass){
		largestClass = n.second.size();
		largestKey = n.first;
	}
  }
    


  std::cout << "start entering jumble words (ctrl)-d to terminate\n" << std::endl;
  

  while(std::cin >> word) {
    
    //alphabeticalize the jumble of letters before checking to see if user input is valid as a valid anagram
    ssort(word);
    if(hashTable.count(word)==0) {
       std::cout << "sorry, for '" << word << 
            "' no anagrams found...try again '\n";
          
    }
    else {
		std::cout << "english anagrams found: \n" << std::endl;
		for (int i = 0; i < hashTable[word].size(); i++)
			std::cout << hashTable[word][i] << std::endl;
	}
  }

    std::cout << "REPORT: " << std::endl;
    
    std::cout << "num_words: " << numberOfWords;
    std::cout << "\n";
    
    std::cout << "num_classes: " << hashTable.size();
    std::cout << "\n";
   
    std::cout << "size-of-largest-class: " << largestClass; 
    std::cout << "\n";

    std::cout << "largest-class key: " << largestKey;
    std::cout << "\n";
	
 	std::cout << "members of largest class: " << std::endl;
 	for(std::string ass : hashTable[largestKey])
		std::cout << ass << std::endl;
    
return 0;
}
