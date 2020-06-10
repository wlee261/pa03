//prog1.cpp
//Winston Lee

#include<iostream>
#include <sstream>
#include<string>
#include<vector>
#include <iostream>
#include <sstream>
#include<fstream>
#include<cctype>
using namespace std;

//fix printHEight
//do search and range search
//make sure root implementation is correct

class AVL
{
public:
	struct node
    {
        pair <string,int> data;
        node* left;
        node* right;
        int height;
    };

	node* root;
	AVL()
	{
		root = NULL;
	}
	~AVL()
	{
		root = NULL;
	}

	string getSearch(string input)
	{
		return input.substr(7, input.length()-1);
	}

	string getRange(string input)
	{
		string words[5];
		istringstream ss(input);
		for(int i = 0; i < 5; i++)
		{
			string word;
			ss>>word;
			words[i] = word;

		}
		return words[2];

	}

	string getRange2(string input)
	{
		string words[5];
		istringstream ss(input);
		for(int i = 0; i < 5; i++)
		{
			string word;
			ss>>word;
			words[i] = word;

		}
		return words[4];
	}

	string getInsert(string input)
	{
		string ret = input.substr(7, input.length()-1);
		return ret;
	}

    void makeEmpty(node* t)
    {
        if(t == NULL)
            return;
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }

    void insertHelper(string input)
    {
    	insert(input, root);
    }
    node* insert(string input, node* t)
    {
    	int maxHeight;
        if(t == NULL)
        {
            t = new node;
            t->data.first = input;
            t->data.second = 1;
            t->height = 1;
            t->left = t->right = NULL;

        }
        else if(input.compare(t->data.first) < 0)
        {
            t->left = insert(input, t->left);
            if(height(t->left) - height(t->right) > 2)
            {
                if(input.compare(t->left->data.first) < 0)
                    t = LLR(t);
                else
                    t = RLR(t);
            }
        }
        else if(input.compare(t->data.first) > 0)
        {
            t->right = insert(input, t->right);
            if(height(t->right) - height(t->left) > 2)
            {
                if(input.compare(t->right->data.first) > 0)
                    t = RRL(t);
                else
                    t = LRR(t);
            }
        }
        if(height(t->left) > height(t->right))
        	maxHeight = height(t->left);
        else
        	maxHeight = height(t->right);
        t->height = maxHeight+1;

        if(t->height == 1)
        	root = t;
        cout << "root is " << root << ", height is " << t->height << endl;
        return t;
    }

    node* LLR(node* &t)
    {
    	int uMaxHeight;
    	int tMaxHeight;
        node* u = t->left;
        t->left = u->right;
        u->right = t;

        if(height(t->left) > height(t->right))
        	tMaxHeight = height(t->left);
        else
        	tMaxHeight = height(t->right);
        t->height = tMaxHeight+1;

        if(height(u->left) > t->height)
        	uMaxHeight = height(u->left);
        else
        	uMaxHeight = t->height;
        u->height = uMaxHeight+1;

        return u;
    }

    node* RRL(node* &t)
    {
    	int uMaxHeight;
    	int tMaxHeight;
        node* u = t->right;
        t->right = u->left;
        u->left = t;

        if(height(t->left) > height(t->right))
        	tMaxHeight = height(t->left);
        else
        	tMaxHeight = height(t->right);
        t->height = tMaxHeight+1;

        if(height(u->right) > t->height)
        	uMaxHeight = height(u->right);
        else
        	uMaxHeight = t->height;
        u->height = uMaxHeight+1;

        return u;
    }

    node* RLR(node* &t)
    {
        t->right = LLR(t->right);
        return RRL(t);
    }

    node* LRR(node* &t)
    {
        t->left = RRL(t->left);
        return LLR(t);
    }

    
    int height(node* t)
    {
    	if(t == NULL)
    		return 0;
    	else
    		return t->height;
    }

    void printHeight()
    {
    	cout << height(root);
    }

    void print() 
    {
    	printHelper(root);
    }

    void printHelper(node* t)
    {
    	cout << "(";
        if(t == NULL)
            return;
        cout << t->data.first << ":"<< t->data.second;
        printHelper(t->left);
        printHelper(t->right);
        cout << ")";
    }

    //constructor, destructor
    void searchHelper(string query)
    {
    	search(query, root);
    }
    node* search(string query, node* t)
    {
    	if (t == NULL){
    		cout << query << " not found";
    		return root;
    	}
    	else if(t->data.first == query){ 
    		cout << query << " found, count = " << t->data.second;
    		return t;
    	}
    	if (t->data.first < query) 
       		return search(query, t->right); 
    	return search(query, t->left); 
    }

    void rangeSearchHelper(string word1, string word2)
    {
    	rangeSearch(word1, word2, root);
    }
	void rangeSearch(string word1, string word2, node* t) //pass in the root
	{
		if(word1 < t->data.first)
			rangeSearch(word1, word2, t->left);

		if(word1 <= t->data.first && word2 >= t->data.first)
			cout << t->data.first << endl;

		if(word2 > t->data.first)
			rangeSearch(word1, word2, t->right);

	}

};

int main(int argc, char* argv[])
{
    AVL avl;
    /*std::string line;
    std::ifstream myfile ("PA3_dataset.txt");
    if (myfile.is_open())
    {
        while ( getline (myfile,line) )
        {
            avl.insertHelper(line);
        }
        myfile.close();
    }
    else std::cout << "Unable to open file"; */
    std::string commands = argv[1];
    std::vector<std::string> result;
    std::stringstream s_stream(commands);
    while(s_stream.good())
    {
    std::string substr;
        getline(s_stream, substr, ',');
        result.push_back(substr);
    }

    for(int i = result.size()-1; i >= 0; i--)
    {
    	//cout << result[i] << endl;
        if(result[i].substr(0,5) == "searc"){
            avl.searchHelper(avl.getSearch(result[i]));
        }
        else if(result[i].substr(0,5) == "inser"){
            avl.insertHelper(avl.getInsert(result[i]));
        }
        else if(result[i].substr(0,5) == "range"){
            avl.rangeSearchHelper(avl.getRange(result[i]), avl.getRange2(result[i]));
        }
        else if(result[i].substr(0,5) == "print"){
            avl.print();
        }
        else if(result[i].substr(0,5) == "height"){
            avl.printHeight();
        }
        
    }

}
/*class 25Tree
{
	struct node
	{
		pair<String, int> data[4];
		Node *c1, *c2, *c3, *c4, *c5, parent;
		int height;
	}
	node()
	{
		for(int i = 0; i < 4; i++)
		{
			data[i] = NULL;
		}
		c1 = c2 = c3 = c4 = c5 = NULL;
	}
	node(String afirst, String bfirst, String cfirst, String dfirst, int asec, int bsec, int csec, int dsec, node *c1in, node *c2in, node *c3in, node *c4in, node *c5in, int inHeight)
	{
		data[0].first = afirst;
		data[1].first = bfirst;
		data[2].first = cfirst;
		data[3].first = dfirst;
		data[0].second = asec;
		data[1].second = bsec;
		data[2].escond = csec;
		data[3].second = dsec;
		c1 = c1in;
		c2 = c2in;
		c3 = c3in;
		c4 = c4in;
		c5 = c5in;
		height = inHeight;
		parent = NULL;
	}

	node* search(String query, Node* t)
    {
    	if (t == NULL){
    		cout << query << " not found";
    		return;
    	}
    	else if(t->data[0].first == query){ 
    		cout << query << " found, count = " << t->A.second;
    		return t;
    	}
    	else if(t->data[1].first == query){ 
    		cout << query << " found, count = " << t->B.second;
    		return t;
    	}
    	else if(t->data[2].first == query){ 
    		cout << query << " found, count = " << t->C.second;
    		return t;
    	}
    	else if(t->data[3].first == query){ 
    		cout << query << " found, count = " << t->D.second;
    		return t;
    	}
    	if (query < t->data[0].first) 
       		return search(t->c1, query);
       	else if (query > t->data[0].first && query < t->data[1].first) 
       		return search(t->c2, query); 
       	else if (query > t->data[1].first && query < t->data[2].first) 
       		return search(t->c3, query);
       	else if (query > t->data[2].first && query < t->data[3].first) 
       		return search(t->c4, query); 
       	return search(t->c5, query); 
    }

    void insert(String input, node *t)
    {
    	if(t->c1 == NULL)//if we're at a leaf
    	{
    		if(t->data[3] == NULL)//if the array is not full
    		{
    			if(input < data[0].first)
    			{
    				String temp, temp2;
    				int current = 0;
    				temp = data[current].first;
    				while(data[current+1] != NULL)
    				{
    					temp2 = data[current+1].first;
    					data[current+1] = temp;
    					temp = temp2;
    					current++;

    				}
    				data[current+1].first = temp;
    				data[0].first = input;
    			}
    		}
    		else //split
    		{

    		} 

    	}
    	if(input < t->data[0].first)
    		return insert(input, c1);
    	else if(input > t->data[0].first && (t->data[1] == NULL || input < t->data[1]))
    		return insert(input, c2);
    	else if(input > t->data[1].first && (t->data[2] == NULL || input < t->data[2]))
    		return insert(input, c3);
    	else if(input > t->data[2].first && (t->data[3] == NULL || input < t->data[3]))
    		return insert(input, c4);
    	else
    		return insert(input, c5);
    		
    	
    	
    	//go left/right until hit leaf
    	//check if the node is full
    	//split if it is
    	//recursively check if the above nodes are affected by the split
    }


	//insert word, increment counter
	//range search
	//print function preorder
	//print height
};*/


