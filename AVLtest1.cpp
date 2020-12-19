/*
 * testAVLTree.cpp
 *
 *  Created on: 19 ���� 2013
 *      Author: shirel
 */

#include "tree.h"
#include <vector>
#include <ostream>
#include <random>
#include <chrono>
#include <algorithm>

int main(){
AvlTree <int,int> tree;
	//Specific Cases

/*correct output for the four next cases
1 BF: 0 Height: 0
2 BF: 0 Height: 1
3 BF: 0 Height: 0 */

//basic LL root change case1
std::cout<<"case1"<<std::endl;
	tree.insert(3,3);
	tree.insert(2,2);
	tree.insert(1,1);
	tree.print(0);
	tree.~AvlTree(); 
	AvlTree<int,int>tree1;

	//basic LR root change case2
	std::cout<<"case2"<<std::endl;
	tree1.insert(3,3);
	tree1.insert(1,1);
	tree1.insert(2,2);
	tree1.print(0);
	tree1.~AvlTree(); 
	AvlTree<int,int>tree2;

	//basic RR root change case3
	std::cout<<"case3"<<std::endl;
	tree2.insert(1,1);
	tree2.insert(2,2);
	tree2.insert(3,3);
	tree2.print(0);
	tree2.~AvlTree();
	 AvlTree<int,int>tree3;

	//basic RL root change case4
	std::cout<<"case4"<<std::endl;
	tree3.insert(1,1);
	tree3.insert(3,3);
	tree3.insert(2,2);
	tree3.print(0);
	tree3.~AvlTree(); 
	AvlTree<int,int>tree4;
//basic LR not root change case5
/*correct output
1 BF: 0 Height: 0
2 BF: 0 Height: 1
3 BF: 0 Height: 0
4 BF: 1 Height: 2
5 BF: 0 Height: 0
6 BF: 1 Height: 3
7 BF: 0 Height: 0
8 BF: 1 Height: 1 */
std::cout<<"case5"<<std::endl;
	tree4.insert(6,6);
	tree4.insert(4,4);
	tree4.insert(8,8);
	tree4.insert(3,3);
	tree4.insert(5,5);
	tree4.insert(7,7);
	tree4.insert(1,1);
	tree4.insert(2,2);
	tree4.print(0);
	tree4.~AvlTree(); 
	AvlTree<int,int>tree5;
	//basic LL not root change case6
	/*correct output
1 BF: 0 Height: 0
2 BF: 0 Height: 1
3 BF: 0 Height: 0
4 BF: 1 Height: 2
5 BF: 0 Height: 0
6 BF: 1 Height: 3
7 BF: 0 Height: 0
8 BF: 1 Height: 1 */
std::cout<<"case6"<<std::endl;
	tree5.insert(6,6);
	tree5.insert(4,4);
	tree5.insert(8,8);
	tree5.insert(3,3);
	tree5.insert(5,5);
	tree5.insert(7,7);
	tree5.insert(2,2);
	tree5.insert(1,1);
	tree5.print(0);
	tree5.~AvlTree(); 
	AvlTree<int,int>tree6;

	//basic RR not root change case7
	/*correct output
1 BF: 0 Height: 0
2 BF: 0 Height: 1
3 BF: 0 Height: 0
5 BF: 1 Height: 2
7 BF: 0 Height: 0*/
std::cout<<"case7"<<std::endl;
	tree6.insert(5,5);
	tree6.insert(7,7);
	tree6.insert(1,1);
	tree6.insert(2,2);
	tree6.insert(3,3);
	tree6.print(0);
	tree6.~AvlTree(); 
	AvlTree<int,int>tree7;




	//basic RL not root change case8
	/*correct output
1 BF: 0 Height: 0
2 BF: 0 Height: 1
3 BF: 0 Height: 0
5 BF: 1 Height: 2
7 BF: 0 Height: 0*/
std::cout<<"case8"<<std::endl;
	tree7.insert(5,5);
	tree7.insert(7,7);
	tree7.insert(1,1);
	tree7.insert(3,3);
	tree7.insert(2,2);
	tree7.print(0);
	tree7.~AvlTree(); 
	AvlTree<int,int>tree8;

	//root deletion no roll successor is a neighbour case9
	/*correct output
2 BF: 0 Height: 0
3 BF: 1 Height: 1
5 BF: 1 Height: 2
6 BF: 0 Height: 0*/
std::cout<<"case9"<<std::endl;
	tree8.insert(4,4);
	tree8.insert(5,5);
	tree8.insert(3,3);
	tree8.insert(2,2);
	tree8.insert(6,6);
	tree8.Delete(4);
	tree8.print(0);
	tree8.~AvlTree(); 
	AvlTree<int,int>tree9;

		//root deletion no roll successor is not a neighbour case10
	/*correct output
2 BF: 0 Height: 0
3 BF: 1 Height: 1
5 BF: 0 Height: 2
6 BF: 0 Height: 0
7 BF: 0 Height: 1
8 BF: 0 Height: 0 */
std::cout<<"case10"<<std::endl;
	tree9.insert(4,4);
	tree9.insert(3,3);
	tree9.insert(7,7);
	tree9.insert(2,2);
	tree9.insert(5,5);
	tree9.insert(8,8);
	tree9.insert(6,6);
	tree9.Delete(4);
	tree9.print(0);
	tree9.~AvlTree(); 
	AvlTree<int,int>tree10;


    //node deletion no roll successor is a neighbour case11
	/*correct output
1 BF: 0 Height: 0
2 BF: 1 Height: 1
4 BF: 1 Height: 2
5 BF: 0 Height: 0
7 BF: 1 Height: 3
8 BF: -1 Height: 1
9 BF: 0 Height: 0*/
std::cout<<"case11"<<std::endl;
	tree10.insert(7,7);
	tree10.insert(3,3);
	tree10.insert(8,8);
	tree10.insert(2,2);
	tree10.insert(4,4);
	tree10.insert(9,9);
	tree10.insert(5,5);
	tree10.insert(1,1);
	tree10.Delete(3);
	tree10.print(0);
	tree10.~AvlTree(); 
	AvlTree<int,int>tree11;

	//node deletion no roll successor is not a neighbour case12
	/*correct output
1 BF: 0 Height: 0
2 BF: 1 Height: 1
5 BF: 0 Height: 2
6 BF: 0 Height: 0
7 BF: 0 Height: 1
8 BF: 0 Height: 0
9 BF: 0 Height: 3
10 BF: 0 Height: 0
12 BF: -1 Height: 2
13 BF: -1 Height: 1
14 BF: 0 Height: 0*/
std::cout<<"case12"<<std::endl;
	tree11.insert(9,9);
	tree11.insert(3,3);
	tree11.insert(12,12);
	tree11.insert(2,2);
	tree11.insert(7,7);
	tree11.insert(10,10);
	tree11.insert(13,13);
	tree11.insert(1,1);
	tree11.insert(5,5);
	tree11.insert(8,8);
	tree11.insert(14,14);
	tree11.insert(6,6);
	tree11.Delete(3);
	tree11.print(0);
	tree11.~AvlTree();
	 AvlTree<int,int>tree12;

	//node deletion causing LR case13
	/*correct output
1 BF: 0 Height: 0
2 BF: 0 Height: 1
3 BF: 0 Height: 0
4 BF: 0 Height: 2
7 BF: -1 Height: 1
8 BF: 0 Height: 0*/
std::cout<<"case13"<<std::endl;
	tree12.insert(7,7);
	tree12.insert(2,2);
	tree12.insert(8,8);
	tree12.insert(1,1);
	tree12.insert(4,4);
	tree12.insert(9,9);
	tree12.insert(3,3);
	tree12.Delete(9);
	tree12.print(0);
	tree12.~AvlTree();
	 AvlTree<int,int>tree13;

	//node deletion causing LL case14
	/*correct output
1 BF: 0 Height: 0
2 BF: 1 Height: 1
3 BF: 0 Height: 2
4 BF: 0 Height: 0
7 BF: 0 Height: 1
8 BF: 0 Height: 0*/
std::cout<<"case14"<<std::endl;
	tree13.insert(7,7);
	tree13.insert(3,3);
	tree13.insert(8,8);
	tree13.insert(2,2);
	tree13.insert(4,4);
	tree13.insert(9,9);
	tree13.insert(1,1);
	tree13.Delete(9);
	tree13.print(0);
	tree13.~AvlTree(); 
	AvlTree<int,int>tree14;

	//node deletion causing RR case15
	/*correct output
2 BF: 0 Height: 0
3 BF: 0 Height: 1
7 BF: 0 Height: 0
8 BF: 0 Height: 2
9 BF: -1 Height: 1
10 BF: 0 Height: 0*/
std::cout<<"case15"<<std::endl;
	tree14.insert(3,3);
	tree14.insert(2,2);
	tree14.insert(8,8);
	tree14.insert(7,7);
	tree14.insert(1,1);
	tree14.insert(9,9);
	tree14.insert(10,10);
	tree14.Delete(1);
	tree14.print(0);
	tree14.~AvlTree(); 
	AvlTree<int,int>tree15;

	//node deletion causing RL case16
	/*correct output
2 BF: 0 Height: 0
3 BF: 1 Height: 1
7 BF: 0 Height: 2
10 BF: 0 Height: 0
13 BF: 0 Height: 1
14 BF: 0 Height: 0*/
std::cout<<"case16"<<std::endl;
	tree15.insert(3,3);
	tree15.insert(2,2);
	tree15.insert(13,13);
	tree15.insert(7,7);
	tree15.insert(1,1);
	tree15.insert(14,14);
	tree15.insert(10,10);
	tree15.Delete(1);
	tree15.print(0);
	tree15.~AvlTree();
	 AvlTree<int,int>tree16;

	//double rotations RL and RR case 17
	/*correct output
3 BF: 0 Height: 0
5 BF: 0 Height: 1
7 BF: 0 Height: 0
9 BF: 0 Height: 2
11 BF: 0 Height: 0
13 BF: 1 Height: 1
15 BF: 0 Height: 3
17 BF: 0 Height: 0
19 BF: -1 Height: 2
21 BF: -1 Height: 1
23 BF: 0 Height: 0*/
std::cout<<"case17"<<std::endl;
	tree16.insert(9,9);
	tree16.insert(3,3);
	tree16.insert(15,15);
	tree16.insert(1,1);
	tree16.insert(7,7);
	tree16.insert(13,13);
	tree16.insert(19,19);
	tree16.insert(5,5);
	tree16.insert(11,11);
	tree16.insert(17,17);
	tree16.insert(21,21);
	tree16.insert(23,23);
	tree16.Delete(1);
	tree16.print(0);
	tree16.~AvlTree();
	AvlTree<int,int> tree17;

	//double rotations RR and RR case 18
	/*correct output
3 BF: 0 Height: 0
7 BF: 0 Height: 1
8 BF: 0 Height: 0
9 BF: 0 Height: 2
11 BF: 0 Height: 0
13 BF: 1 Height: 1
15 BF: 0 Height: 3
17 BF: 0 Height: 0
19 BF: -1 Height: 2
21 BF: -1 Height: 1
23 BF: 0 Height: 0*/
std::cout<<"case18"<<std::endl;
	tree17.insert(9,9);
	tree17.insert(3,3);
	tree17.insert(15,15);
	tree17.insert(1,1);
	tree17.insert(7,7);
	tree17.insert(13,13);
	tree17.insert(19,19);
	tree17.insert(8,8);
	tree17.insert(11,11);
	tree17.insert(17,17);
	tree17.insert(21,21);
	tree17.insert(23,23);
	tree17.Delete(1);
	tree17.print(0);
	tree17.~AvlTree();
	 AvlTree<int,int> tree18;

	//double rotations RL and LL case 19
	/*correct output
6 BF: 0 Height: 0
7 BF: 1 Height: 1
8 BF: 1 Height: 2
9 BF: 0 Height: 0
10 BF: 0 Height: 3
11 BF: -1 Height: 1
12 BF: 0 Height: 0
15 BF: 0 Height: 2
17 BF: 0 Height: 0
18 BF: 0 Height: 1
20 BF: 0 Height: 0
	 */
	std::cout<<"case19"<<std::endl;
	tree18.insert(15,15);
	tree18.insert(10,10);
	tree18.insert(20,20);
	tree18.insert(8,8);
	tree18.insert(11,11);
	tree18.insert(17,17);
	tree18.insert(21,21);
	tree18.insert(7,7);
	tree18.insert(9,9);
	tree18.insert(12,12);
	tree18.insert(18,18);
	tree18.insert(6,6);
	tree18.Delete(21);
	tree18.print(0);
	tree18.~AvlTree();
	 AvlTree<int,int>tree19;

	//double rotations LR and LL case 20
	/*correct output
6 BF: 0 Height: 0
7 BF: 1 Height: 1
8 BF: 1 Height: 2
9 BF: 0 Height: 0
10 BF: 0 Height: 3
11 BF: -1 Height: 1
12 BF: 0 Height: 0
15 BF: 0 Height: 2
20 BF: 0 Height: 0
21 BF: 0 Height: 1
22 BF: 0 Height: 0 */
std::cout<<"case20"<<std::endl;
	tree19.insert(15,15);
	tree19.insert(10,10);
	tree19.insert(20,20);
	tree19.insert(8,8);
	tree19.insert(11,11);
	tree19.insert(17,17);
	tree19.insert(22,22);
	tree19.insert(7,7);
	tree19.insert(9,9);
	tree19.insert(12,12);
	tree19.insert(21,21);
	tree19.insert(6,6);
	tree19.Delete(17);
	tree19.print(0);
	tree19.~AvlTree();
	 AvlTree<int,int>tree20;

	//delete node cause LR case21
	/*correct output
2 BF: 0 Height: 0
3 BF: -1 Height: 2
4 BF: 0 Height: 0
6 BF: 1 Height: 1*/
std::cout<<"case21"<<std::endl;
	tree20.insert(5,5);
	tree20.insert(3,3);
	tree20.insert(6,6);
	tree20.insert(2,2);
	tree20.insert(4,4);
	tree20.Delete(5);
	tree20.print(0);
	tree20.~AvlTree(); 
	AvlTree<int,int>tree21;

	//delete node cause LR case22
	/*correct output
2 BF: 0 Height: 0
3 BF: 0 Height: 1
6 BF: 0 Height: 0*/
std::cout<<"case22"<<std::endl;
	tree21.insert(5,5);
	tree21.insert(3,3);
	tree21.insert(6,6);
	tree21.insert(2,2);
	tree21.Delete(5);
	tree21.print(0);
	tree21.~AvlTree(); 
	AvlTree<int,int>tree22;

	std::vector<int> vector;
	 for (int i=1; i<=100; i++) vector.push_back(i);

	 //Randomly insert and removes nodes
	 for (int k = 0; k < 20; ++k) {
		 unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		 shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
		 for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
				tree22.insert(*it,*it);
		 }
		 int arr[100];
		 
		 tree22.print(0);
		 
		 
		 shuffle (vector.begin(), vector.end(), std::default_random_engine(seed));
		 for (std::vector<int>::iterator it = vector.begin() ; it != vector.end(); ++it){
				tree22.Delete(*it);
				

		 }
		 

		 tree22.~AvlTree(); 
		 AvlTree<int,int>tree23;
		 tree23.print(0);
		 std::cout << '\n';
	
	 }

	return 0;
}

