<img src="https://www.colorado.edu/cs/profiles/express/themes/ucb/images/cu-boulder-logo-text-black.svg" alt="CU Boulder Logo" width="500">

# CSCI 2270: Data Structures <br/> University Courses Database Project

## Introduction
The objective of this project is to write an application that reads a list of University courses from a data file and then inserts them into two separate hash tables. The first hash table will use the Open Addressing collision resolution scheme and the second hash table will use the Chaining collision resolution scheme. Users should be able to search the hash tables for a specific course number or display all of the courses. It’s your objective to compare and contrast the hashing collision resolution methods. Additionally, the application should maintain a list of courses taught by each professor by using a binary search tree data structure. Users should be able to search for a professor and view all of the courses taught by the Professor.

## Free Response Questions:
1. Does one hashing collision resolution work better than the other?

Based on this project, I would say that chaining worked better. It resulted in fewer collisions overall, and required fewer search operations. I would say that for a very large data set, say with a million records, the result would be the same. With a million records, as the table approaches a full state, the quadratic probing function would have to search through basically all 1 million buckets before finding an empty one, which is way slower than just traversing the linked list.

2. We used the same BST for both hashing mechanisms. What alternative data structure would you advise?

I suppose there's no reason we couldn't have also used hash tables instead of the BSTs. It probably would have made insertion much more efficient, as well as searching. 

3. Explain a few ways you could improve the application

Well, this is obviously outside the scope of the class but a GUI would be nice, like using some HTML and CSS to make a nice front end portal for people to search though the data and view the output. As far as back end goes, I think that instead of storing the Professor information in the Course structs as a BST node, we should have just stored the data as strings and ints, as attributes in the Course struct. That way, you wouldn't have to search through the tree for each Course in the hash table to link the correct BST node the Course. You could just read all that data in at the same time, and then output it when searched for. The separate data structure for the professors is still useful of course, to see information about what courses they all teach. 
