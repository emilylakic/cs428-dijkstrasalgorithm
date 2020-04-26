#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <set>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {

  //checking if right number of arguments are provided
  if(argc != 3) {
    printf("Must provide 2 arguments\n");
    return -1;
  }

  vector<char> nodeNames; //node names
  vector<string> lines; //lines from graph input txt file (comma separated)
  vector<char> path; //path determined by dijkstra's algorithm (list of indeces that correspond to node nodeNames array)
  vector<char> unvisited; //not constant, list of all nodes that have not been visited
  vector<int> distanceValues;// D(V) values at each node (corresponds to nodeNames)
  vector<vector<int>> progress;

  ifstream inFile(argv[1]); //open input file from first argument
  char startingNode = argv[2][0]; //set starting node to second argument
  string line; //temporary line to be replaced by input
  if (inFile.is_open()) {
    while (getline(inFile, line)) {

      //if the first line (#),
      if(line.at(0) == '#') {
        // for(unsigned i = 0; i < line.length(); i++) {
        //   if((line.at(i) != '#') && (line.at(i) != ',')) {
        //   nodeNames.push_back(line.at(i));//add all of the nodes
        //   }
        // }
      }
      else {
        lines.push_back(line);//add line to vector
        nodeNames.push_back(line.at(0));//add node to list of nodes
        unvisited.push_back(line.at(0));//add node to unvisited list
      }
    }

    //print out each node in the list
    for (unsigned n=0; n<nodeNames.size(); ++n) {
        //cout << nodeNames.at( n ) << endl;
    }
  inFile.close(); //done reading input
  }

  bool validNode = false; //flag for checking if start node is valid
  for(unsigned i = 0; i < nodeNames.size() ; i++) {
    if (nodeNames.at(i) == startingNode) {
      //printf("VALID\n"); //if any of the nodes are valid(starting node provided is equal to a node in the list, we are good
      validNode = true;
      break;
    }
  }
  if(validNode == false){return -1;}//else return

  //two dimensional array to represent edges
  int adjMatrix[nodeNames.size()][nodeNames.size()];

  //loop through the array
  for(unsigned i=0; i < nodeNames.size(); i++) {
    string distances = lines.at(i);
    int counter = 0;
    unsigned index = 2;
    string value = "";
    while(index<distances.length()) {
      int endIndex = distances.find(",",index);
      value = distances.substr(index,endIndex);
      adjMatrix[i][counter] = stoi(value); //loop through a line and set the each value to corresponding value in adjMatrix
      counter++;
      index = endIndex+1;
    }
  }

  //print out adj matrix
  // for(unsigned row = 0;row<nodeNames.size();row++){
  //   for(unsigned column = 0; column<nodeNames.size();column++){
  //     cout<<adjMatrix[row][column]<<" ";
  //   }
  //   cout<<endl;
  // }

  path.push_back(startingNode); //add the starting node to the path

  //takes startingNode out of unvisited and determines its index
  unsigned startingIndex = -1;
  for(unsigned i = 0; i < unvisited.size(); i++) {
    if(unvisited.at(i)==startingNode) {
      startingIndex = i;
      break;
    }
  }


  //for(unsigned i = 0; i < nodeNames.size(); i++) {
  //  printf("%c\n",nodeNames.at(i));
  //}
  vector<char> printList = unvisited;
  unvisited.erase(unvisited.begin()+startingIndex);//removes the starting node

  for(unsigned i = 0; i < nodeNames.size(); i++) {
    distanceValues.push_back(adjMatrix[startingIndex][i]);
  }



  progress.push_back(distanceValues);
  for(unsigned i = 0;i<progress.at(0).size();i++){
  }
  //cout<<endl;

  //
  // What we want to do: Loop through distanceValues [i],
  // check if the value's character (i) is not in the current path ( = in unvisited)
  // determine which i value had the minimum value
  // add that value index's char to the path, remove it from unvisited
  // at that new node we added loop, determine adjacent nodes that are also unvisited
  // set their distance value to the minimum of either the distance value currently or distance value of the new node + the distance value or adjMatrix[vIndex][index of new node]
  // repeat until no nodes are in unvisited
  //start of algorithm-------------------------------------------

  //cout<<"STARTING TO LOOP"<<endl;
  int counter=0;
  while(unvisited.size() != 0) {
    //printf("Length of unvisited: %lu\n",unvisited.size());
    //vector of indeces that are nodes adjacent to given node (starting node)
    //vector<int> adjacentIndeces;

    int minIndex =  -1;

    // cout<<"\n#"<<counter<<" GETTING Sweaty:\n------------------\nDistance Value: ";
    // for(unsigned c = 0;c<distanceValues.size();c++){
    //   cout<<distanceValues.at(c)<<"\t";
    // }
    // cout<<endl;

    //loop through distanceValues

    for(unsigned i = 0; i < distanceValues.size(); i++) {

      char visitingChar = nodeNames.at(i);


      //determines if not visited yet

      bool notVisited=false;
      for(unsigned k = 0;k<unvisited.size();k++){
        if(visitingChar==unvisited.at(k)){
          notVisited=true;
          break;
        }
      }



      if(notVisited){
        //might need to check for 9999
        if(minIndex==-1){
            minIndex=i;
        }
        else{
          if(distanceValues.at(i)<distanceValues.at(minIndex)){
            minIndex=i;
          }
        }
      }
      else{

      }
    }
    //index of minimum value should be found
    //want to find its character
    //trap
    if(minIndex==-1){
      char finalChar = unvisited.at(0);
      for(unsigned w = 0;w<nodeNames.size();w++){
        if(nodeNames.at(w)==finalChar){
          minIndex=w;

        }
      }
    }

    char newChar = nodeNames.at(minIndex);
    path.push_back(newChar);

    unsigned eraseIndex = -1;
    for(unsigned q = 0;q<unvisited.size();q++){
      if(newChar==unvisited.at(q)){
        eraseIndex = q;
      }
    }

    unvisited.erase(unvisited.begin()+eraseIndex);//pop of new node from unvisited

    for (unsigned h = 0;h<distanceValues.size();h++){
      int edgeValue = adjMatrix[minIndex][h];
      int checkingChar = nodeNames.at(h);
      bool notDiscovered = false;
      for(unsigned y = 0;y<unvisited.size();y++){
        if(checkingChar==unvisited.at(y)){
          notDiscovered=true;
          break;
        }
      }


      if((edgeValue!=9999) && (notDiscovered)){
        int currentValue = distanceValues.at(h);
        int compValue = distanceValues.at(minIndex)+edgeValue;
        if(compValue<currentValue){
          distanceValues.at(h)=compValue;
        }
      }
    }


    progress.push_back(distanceValues);


    //cout<<"Path"<<endl;
    // for(unsigned i = 0;i<path.size();i++){
    //   cout<<path.at(i);
    // }
    // cout<<endl;


    //printf("%c\n",unvisited.at(0));
    counter++;
  }

  //printf("\n\n\nLength of unvisited: %lu\n",unvisited.size());
  //end of algorithm---------------------------------------------

  //start of printing-------------------------------------------
  cout<<"Start\t";
  for(unsigned q = 0;q<printList.size();q++){
    cout<<"D("<<printList.at(q)<<")\t";
  }
  cout<<endl;
  for(unsigned q = 0;q<printList.size()+1;q++){
    cout<<"----\t";
  }
  cout<<endl;
  //vector<vector<int>> pathIndeces;

  for(unsigned f = 0;f<progress.size();f++){
    vector<char> currentPathChars;
    for(unsigned p = 0; p<=f;p++){
      cout<<path.at(p);
      currentPathChars.push_back(path.at(p));
    }
    vector<int> currentPathIndeces;
    while(currentPathChars.size()!=0){
      for(unsigned g = 0;g<nodeNames.size();g++){
        if(nodeNames.at(g)==currentPathChars.at(0)){
          currentPathIndeces.push_back(g);

          currentPathChars.erase(currentPathChars.begin()+0);
          break;
        }
      }
    }

    // cout<<endl;
    // for(unsigned fuck =0;fuck<currentPathIndeces.size();fuck++){
    //   cout<<currentPathIndeces.at(fuck)<<",";
    // }
    // cout<<endl;



    cout<<"\t";
    for(unsigned i = 0;i<progress.at(f).size();i++){
      bool ableToPrint= true;
      for(unsigned m = 0;m<currentPathIndeces.size();m++){
        if(i==(unsigned)currentPathIndeces.at(m)){
          ableToPrint=false;
          break;
        }
      }
      if(ableToPrint){
        if(progress.at(f).at(i)==9999){
          cout<<"inf\t";
        }
        else{
          cout<<progress.at(f).at(i)<<"\t";
        }

      }else{
        cout<<"-\t";
      }

    }
    cout<<endl;
  }

  //end of printing---------------------------------------------
  return 0;
}
