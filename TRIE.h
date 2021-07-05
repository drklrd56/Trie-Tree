#ifndef TRIE_H_
#define TRIE_H_

#include <string>
#include <iostream>
#include<fstream>
#include <vector>

#define ALPHABETS 26
#define LONGEST_WORD_IN_DICTIONARY 189819

//insertWord(Word,Meaning,Synonyms,LengthSynonyms);

using namespace std;


// Only Defined function that i need not a Vector but a DATA STRUCTURE i need.
template<typename T>
class Vector
{
	T *data;
	int length;
	int cap;
public:
	Vector()
	{
		length = 10;
		data = new T[length];
		cap = 0;
	}
	Vector(int length)
	{
		if (length > 0)
			this->length = length;
		else
			this->length = 10;
		data = new T[length];
		cap = 0;
	}
	void clear()
	{
		data = NULL;
		data = new T[10];
		length = 10;
	}
	void resize(int length)
	{
		int newlength = 0,newCap=0;
		T *temp=NULL;
		if (length <= this->length)
		{
			temp = new T[length];
			newlength = length;
		}
		else if (this->length < length)
		{
			newlength = this->length;
			temp = new T[newlength];
		}
		for (int Index = 0; Index < newlength; Index++)
		{
			temp[Index] = data[Index];
			newCap++;
		}
		delete[] data;
		data = new T[length];
		this->length = length;
		this->cap = newCap;
		for (int Index = 0; Index < newlength; Index++)
		{
			data[Index] = temp[Index];
		}
		delete[] temp;
	}
	int size()
	{
		return length;
	}
	bool isEmpty()
	{
		if (cap == 0) return true;
		else 
			return false;
	}
	T& operator[](int index) {
		if (!isEmpty())
		{
			if (index >= 0)
				if (index <= cap)
					return data[index];
		}
	}
	const T& operator[](int index) const {
		if (!isEmpty())
		{
			if (index >= 0 && index <= cap)
				return data[index];
		}
	}
	void operator=(T& value)
	{
		if (cap == length)
			this->resize(length + 10);
		data[cap] = value;
		cap++;

	}
	
	
	vector<T> convertVector()
	{
		vector<T> returnVector;
		returnVector.resize(this->length);
		for (int Index = 0; Index < this->length; Index++)
			returnVector[Index] = data[Index];
		return returnVector;
	}
	void Dispay()
	{
		for (int Index = 0; Index < length; Index++)
			cout << data[Index] << endl;
	}
	~Vector()
	{
		//delete[] data;
		data = NULL;
		length = 0;
		cap = 0;
	}
};

template<typename T>
class Queue
{
	class Node
	{
	public:
		T data;
		Node* next;
	};
	Node* front;
	Node* rear;
	int wordCount;
public:
	Queue()
	{
		front = NULL;
		rear = NULL;
		wordCount = 0;
	}
	bool isEmpty()
	{
		return front == NULL;
	}
	void enqueue(T value)
	{
		Node* newNode = new Node();
		newNode->data = value;
		newNode->next = NULL;
		wordCount++;
		if (isEmpty())
		{
			rear = newNode;
			front = newNode;
		}
		else
		{
			rear->next = newNode;
			rear = newNode;
		}
	}
	T dequeue()
	{
		if (isEmpty())
		{
			std::cout << "Queue is Empty." << std::endl;
		}
		else
		{
			Node* temp = front->next;
			T value = front->data;
			delete front;
			front = temp;
			wordCount--;
			return value;
		}
	}
	void makeNull()
	{
		while (!isEmpty())
			dequeue();
	}
	void Display()
	{
		Node* currentNode = front;
		while (front)
		{
			cout << currentNode->data << endl;;
			currentNode = currentNode->next;
		}
	}
	int size()
	{
		return wordCount;
	}
	~Queue()
	{
		makeNull();
	}
};


class TRIE
{
private:
    struct TrieNode
    {
        char value;
        string Meaning;
        Vector<string> Synonyms;
        bool isWord;
        TrieNode *Character[ALPHABETS];
        void insertSynonyms(Vector<string> synon)
        {
			Synonyms.clear();
			Synonyms.resize(synon.size());
			for (int Index = 0; Index < synon.size(); Index++)
			{
				Synonyms[Index] = synon[Index];
			}
        }
        void insertMeanings(string Mean)
        {
            Meaning=Mean;
        }
    };
    TrieNode *root;
	int totalWords;
    TrieNode* createNode(char key)
    {
        TrieNode *newNode=new TrieNode();
        newNode->value=key;
		newNode->Meaning="";
		newNode->isWord=false;
        return newNode;
    }
    int getKey(char key)
    {
        int expKey;
        if(key>96 && key<123)
            expKey=int(key)-32;
        else if(key>64 && key<91)
            expKey=int(key);
        else
            expKey=-1;
		//cout << expKey << endl;
		expKey -= 65;
        return expKey;
    }
    bool checkWord(string Word)
    {
        bool retValue=true;
		for (int Index = 0; Word[Index] != '\0'; Index++)
            if(getKey(Word[Index])==-1)
                return false;
        return retValue;
    }
	void insertWord(string Word, string Meaning, Vector<string>& Synonyms)
	{
		int Index = 0, expansionKey;
		TrieNode *currentNode = root; TrieNode *newNode;
		if (checkWord(Word))
		{
			while (Word[Index] != '\0')
			{
				newNode = createNode(Word[Index]);
				expansionKey = getKey(Word[Index]);
				if (currentNode->Character[expansionKey] == NULL)
					currentNode->Character[expansionKey] = newNode;
				currentNode = currentNode->Character[expansionKey];
				Index++;
			}
			totalWords++;
			currentNode->insertSynonyms(Synonyms);
			currentNode->insertMeanings(Meaning);
			currentNode->isWord = true;
		}
	}
	void DisplayWords(TrieNode* currentNode,string word)
	{
		if (currentNode->isWord)
		{
			cout <<"WORD : "<< word << endl;
			cout <<"MEANING : " << currentNode->Meaning << endl;
			int length=currentNode->Synonyms.size();
			cout << "SYNONYMS : " << endl;
			for (int Index = 0; Index < length; Index++)
				cout << currentNode->Synonyms[Index] << endl;
		}
		for (int Index = 0; Index < ALPHABETS; Index++)
			if (currentNode->Character[Index])
				DisplayWords(currentNode->Character[Index], word + currentNode->Character[Index]->value);
	}
	void getWords(TrieNode* currentNode, string word,Vector<string>& Words,int& WordsIndex)
	{
		if (currentNode->isWord)
		{
			Words[WordsIndex] = word;
			WordsIndex++;
		}
		for (int Index = 0; Index < ALPHABETS; Index++)
			if (currentNode->Character[Index])
				getWords(currentNode->Character[Index], word+ currentNode->Character[Index]->value,Words,WordsIndex);
	}
	void FindRelatedData(TrieNode* currentNode,string word, Vector<string>& Words, int& WordsIndex,int type,string SearchWord)
	{
		if (currentNode->isWord)
		{
			if (word == SearchWord){
				if (type == 1){
					Words.resize(currentNode->Synonyms.size());
					for (int Index = 0; Index < currentNode->Synonyms.size(); Index++)
						Words[Index] = currentNode->Synonyms[Index];
					return;
				}
				else if (type == 2){
					Words[0] = currentNode->Meaning;
					return;
				}
			}
		}
		for (int Index = 0; Index < ALPHABETS; Index++)
			if (currentNode->Character[Index])
				FindRelatedData(currentNode->Character[Index], word+currentNode->Character[Index]->value,Words, WordsIndex,type,SearchWord);
	}
	bool checkAnagram(string Word1,string Word2)
	{
		if (Word1.length() != Word2.length())
			return false;
		int letter[256];
		int expansionKey;
		for (int Index = 0; Index < Word1.length(); Index++)
		{
			letter[getKey(Word1[Index])]=1;
		}
		for (int Index = 0; Index < Word1.length(); Index++)
		{
			if (letter[getKey(Word2[Index])] != 1)
				return false;
		}
		return true;
	}
public:
    TRIE()
    {
		root = new TrieNode();
		root->isWord = false;
		root->Meaning = "";
		root->value = '\0';
		for (int Index = 0; Index < ALPHABETS; Index++)
		{
			root->Character[Index] = NULL;
		}
		totalWords = 0;
    }
	void CreateDictionary(string path)// "..\\trie\\dictionary.txt")
	{
		ifstream inputFile;
		inputFile.open(path);
		string Line="Start",Word,Meaning,prevLine="",Actual_Word;
		Vector<string> Synonyms;
		Queue<string> tempSyn;
		if (inputFile.is_open())
		{
			getline(inputFile, Line, '\n');
			while (!inputFile.eof())
			{
				if (Line == "")
					break;
				if (Line[0] == '-' && Line[1] != '-')
					Actual_Word=Word = Line.substr(1, Line.length());
				getline(inputFile, Line, '\n');
				if (Line[0] == '-' && Line[1] == '-')
					Meaning = Line.substr(2, Line.length());
				while (Line != "")
				{
					getline(inputFile, Line, '\n');
					if (Line == "") break;
					if (Line == prevLine) break;
					if (Line[0] == '-')
					{
						Word = Line.substr(1, Line.length());
						break;
					}
					else
						tempSyn.enqueue(Line);
					prevLine = Line;
				}
				Synonyms.clear();
				Synonyms.resize(tempSyn.size());
				for (int Index = 0; !tempSyn.isEmpty();Index++) {
					prevLine = tempSyn.dequeue();
					Synonyms[Index]=prevLine;
				}
				insertWord(Actual_Word, Meaning, Synonyms);
			}
		}
		else
			cout << "ERROR : Path not Found." << endl;
	}
	Vector<string> OutputAscending()
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word = "";
		getWords(root, word, Words, WordIndex);
		string temp;
		
		return Words;
	}
	Vector<string> OutputDescending()
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word = "";
		getWords(root, word,Words, WordIndex);
		string temp;
		for (int Index_Outer = 0,Index=Words.size()-1; Index_Outer < Words.size()/2; Index_Outer++)
		{
			temp = Words[Index];
			Words[Index] = Words[Index_Outer];
			Words[Index_Outer] = temp;
			Index--;
		}
		return Words;
	}
	bool FindWord(string key)
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word="";
		getWords(root, word,Words, WordIndex);
		bool isFound = false;
		for (int Index = 0; Index < Words.size(); Index++) {
			if (Words[Index] == key) {
				isFound = true;
				break;
			}
		}
		return isFound;

	}
	Vector< string> FindSynonyms(string key)
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word = "";
		FindRelatedData(root, word, Words, WordIndex,1,key);
		return Words;// .convertVector();
	}
	string FindMeaning(string key)
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(1);
		int WordIndex = 0;
		string word = "";
		FindRelatedData(root, word,Words, WordIndex, 2, key);
		return Words[0];
	}
	Vector<string> OutputPrefix(string prefix)
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word = "";
		getWords(root, word,Words, WordIndex);
		int size = 0,Index_Main=0;
		Vector<string> returnVector;
		returnVector.resize(totalWords);
		string checkWord;
		for (int Index_Outer = 0; Index_Outer < Words.size(); Index_Outer++)
		{
			checkWord = Words[Index_Outer].substr(0,prefix.length());
			if ( checkWord== prefix)
			{
				returnVector[Index_Main] = Words[Index_Outer];
				Index_Main++;
				size++;
			}
		}
		returnVector.resize(size);
		return returnVector;// .convertVector();
	}
	Vector<string> OutputSmaller(int length)
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word = "";
		getWords(root, word,Words, WordIndex);
		int size = 0, Index_Main = 0;
		Vector<string> returnVector;
		returnVector.resize(totalWords);
		for (int Index_Outer = 0; Index_Outer < Words.size(); Index_Outer++)
		{
			if (Words[Index_Outer].length()<length)
			{
				returnVector[Index_Main] = Words[Index_Outer];
				Index_Main++;
				size++;
			}
		}
		returnVector.resize(size);
		return returnVector;// .convertVector();
	}
	Vector<string> OutputSE(int length)
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word = "";
		getWords(root, word,Words, WordIndex);
		int size = 0, Index_Main = 0;
		Vector<string> returnVector;
		returnVector.resize(totalWords);
		for (int Index_Outer = 0; Index_Outer < Words.size(); Index_Outer++)
		{
			if (Words[Index_Outer].length() <= length)
			{
				returnVector[Index_Main] = Words[Index_Outer];
				Index_Main++;
				size++;
			}
		}
		returnVector.resize(size);
		return returnVector;// .convertVector();
	}
	Vector<string> OutputGreater(int length)
	{
		Vector<string> Words;
		Words.clear();
		Words.resize(totalWords);
		int WordIndex = 0;
		string word = "";
		getWords(root, word,Words, WordIndex);
		int size = 0, Index_Main = 0;
		Vector<string> returnVector;
		returnVector.resize(totalWords);
		for (int Index_Outer = 0; Index_Outer < Words.size(); Index_Outer++)
		{
			if (Words[Index_Outer].length() > length)
			{
				returnVector[Index_Main] = Words[Index_Outer];
				Index_Main++;
				size++;
			}
		}
		returnVector.resize(size);
		return returnVector;//.convertVector();
	}
	Vector<string> OutputAnagrams(string key)
	{
		if (totalWords > 0)
		{
			Vector<string> Words;
			Words.clear();
			Words.resize(totalWords);
			int WordIndex = 0;
			string word = "";
			getWords(root, word,Words, WordIndex);
			int size = 0, Index_Main = 0;
			Vector<string> returnVector;
			returnVector.resize(totalWords);
			for (int Index_Outer = 0; Index_Outer < Words.size(); Index_Outer++)
			{
				if (Words[Index_Outer] != key)
				{
					if (checkAnagram(Words[Index_Outer], key))
					{
						returnVector[Index_Main] = Words[Index_Outer];
						Index_Main++;
						size++;
					}
				}
			}
			returnVector.resize(size);
			return returnVector;// .convertVector();
		}
	}
	Vector<string> OutputSuffix(string suffix)
	{
		if (totalWords > 0)
		{
			Vector<string> Words;
			Words.clear();
			Words.resize(totalWords);
			int WordIndex = 0;
			string word = "";
			getWords(root, word,Words, WordIndex);
			int size = 0, Index_Main = 0;
			Vector<string> returnVector;
			returnVector.resize(totalWords);
			string checkWord;
			for (int Index_Outer = 0; Index_Outer < Words.size(); Index_Outer++)
			{
				checkWord = Words[Index_Outer].substr(Words[Index_Outer].length() - suffix.length(), Words[Index_Outer].length());
				if (checkWord == suffix)
				{
					returnVector[Index_Main] = Words[Index_Outer];
					Index_Main++;
					size++;
				}
			}
			returnVector.resize(size);
			return returnVector;//.convertVector();
		}
	}
	void Display()
	{
		int currentIndex = 0;
		string Word = "";
		DisplayWords(root, Word);
	}
};

#endif