Name: James Iorgovan

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)
YES

---------------------------------------------------
Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?

First I modified the struct bst because it originally held the root as well the left and right node. This would allow me to keep track of each child node from the left and the right: leftNodes{numberOfLeft}, rightNodes{numberOfRight}, counter{numberOfTotal}
I also added the conditions:
int numberOfLeft = 0 so that we can track number of nodes in left subtree
int numberOfRight = 0 so that we can track number of nodes in right subtree
int numberOfTotal = 1 so that we can track number of nodes in subtree including the root


-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous question?  

static bst_node *_remove
static bst_node *_insert

The functions I had to modify were the insert helper and the remove helper. This is because for each time we loop successfully in our insert function, we want to keep track and increment the amount of nodes in the left subtree as well as adding to the counter. The same applies for our right subtree.

In our remove function, we do the opposite. Everytime we loop successfully, we decrement the amount of nodes in each subtree as well as the total counter.



-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime remained the same?


I ensured that assymptotic runtime remains the same by keeping accurate bookkeeping. As stated above, we have to keep track of each subtree to increment and decrement when required. Also, for most of the functions where I bookkeep, incrementation and decrementation statements doesn't change the runtime because in this case there are a maximum of 2 variable lines.

-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  ____5_______  


-----------------------------------------------
get_ith level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: For this I created a boolean helper function. This will first check to see if the root is set to nullptr and returns false if that is the case. If that does not pass then we check to see if the total node count is equal to 1. If it is we traverse through i for as long as it is equal to one a return the value of x within that template tree. Otherwise we will return false. If only the left nodes + 1 is == to i, we get the value stored as r for x and return true. This was we see that if we are traversing through the left subtree, as long as the value we are looking for is less than x, then we will traverse until we get what x is. The same instance applies for the right subtree in the else if statement. When testing for this it does not appear that we utizlise this function's property for every condition of every node so if we do not have to do that for the smallest element, then the runtime is O(h).

-----------------------------------------------
num_geq level of completion:  _____5______  

    How did you ensure O(h) runtime?

    ANSWER: For this function I checked to return 0 if the target value was greater than the max because no values could be greater than or equal to the largest value in the tree. Because it is running in conditions of BST, the runtime is O(h). If we do not return a 0, then we would check that the value we are looking for is greater than x and return the number of right nodes and suntree of the left in terms of what x is as well as adding one for the root. We only have 3 conditions which is when it is equal to nullptr, greater than the value of x, or less than. 

-----------------------------------------------
num_leq level of completion:  _____5_______

    How did you ensure O(h) runtime?

    ANSWER: For this function I kept it consistent by making an int helper function. I returned 0 if the target value is less than the minimum. If it wasnt then we would check the value is less than or equal to the number x. We could then return the number of left nodes and subtree of the right in terms of what x is, added to one (for the root). We only have 3 conditions which is when it is equal to nullptr, greater than the value of x, or less than. The same condition as num_geq applies as to why the runtime is O(h). 

-----------------------------------------------
num_range level of completion:  _____5_______

    How did you ensure O(h) runtime?

    ANSWER: For this function I first checked if the root was equal to nullptr. If so we return 0 because there is no range. I then make sure to initialize the total nodes to the counter intitialized at the beginning of my struct as well as the total right nodes to num_geq for the min and the total left nodes to num_leq for the max because we return the total of right and left subtree nodes and subtract the total nodes. This will give us the remainder of our total nodes which is 1 (which is our root). This ensures runtime of O(h) because it traverses through the BST with BST properties. 

-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: _____3______


Write a few sentences describing how you tested your solutions.  Are there any tests that in retrospect you wish you'd done?

	The way I tested by solutions is by checking each individual test at once. I began with t1 and t2 which dealt with the to_vector function. Until I managed to pass this I did not move on because some functions might have depended on correct output from this. I did make t1/make t2 and then ./t1 or ./t2 in order to see what the results were. I then did this for t3 and t4 which dealt with the get_ith function. I made sure that the t3 resulted correctly and then did the t4. These returned the correct values and then went onto t7 and t8 which dealt with num_leq. The same method was applied before moving on because some of the functions may have depended on correct output(mostly t14-16). After successful results the functions I was next able to correctly solve were t9 and t10 which was the num_geq. These were independent from t7 and t8 because we are given a binary search source (as well as for t7 and t8). These worked and I managed to get as far as passing t11-13 which dealt with the num_range. After this I understood that t14-16 dealt with the size balancing of the binary search tree. I was not able to pass the more complex test 3 of runtime because the ratio that the program is looking for is 2.50 whereas mine resulted in 3.63. 
	Some tests I wish I'd have done is seeing whether I would need the completion of the previous tests to complete t14-16 because this is where most of the points came from. It would be interesting to do this experiment to see the limits of what is curcial to passing the more complex tests of runtime and size balancing.
	The main issue that I came across overall was the runtime of the BST balance. Although it will all work and run without and errors or seg faults, it will just take some time. 

