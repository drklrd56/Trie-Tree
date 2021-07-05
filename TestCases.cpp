#include "TRIE.h"
#include <cstdlib>
#include <iostream>
#include <vector> 
#include <string>
#include <fstream>
#include "gtest/gtest.h"


TEST(testTRIE, Inputfileopen)
{
	ifstream is("..\\trie\\dictionary.txt",std::ifstream::in);
	
	if(!is.is_open())
		{
			
			ASSERT_TRUE(false);
		}
	else
	{
		ASSERT_TRUE(true);
	}
	is.close();

		
}


TEST(testTRIE, OutputAscendingDescending)
{
                TRIE test;
                test.CreateDictionary("..\\trie\\dictionary.txt");
                vector<string> ListOfWords = test.OutputAscending();
                string data;

        data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"listen"));

		data = ListOfWords[1];
		EXPECT_EQ(0, strcmp(data,"peck"));

		data = ListOfWords[2];
		EXPECT_EQ(0, strcmp(data,"pecked"));

		data = ListOfWords[3];
		EXPECT_EQ(0, strcmp(data,"peppers"));

		data = ListOfWords[4];
		EXPECT_EQ(0, strcmp(data,"picked"));

		data = ListOfWords[5];
		EXPECT_EQ(0, strcmp(data,"pickled"));

		data = ListOfWords[6];
		EXPECT_EQ(0, strcmp(data,"piper"));

		data = ListOfWords[7];
		EXPECT_EQ(0, strcmp(data,"silent"));

		ListOfWords = test.OutputDescending();

		data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"silent"));

		data = ListOfWords[1];
		EXPECT_EQ(0, strcmp(data,"piper"));
		
		data = ListOfWords[2];
		EXPECT_EQ(0, strcmp(data,"pickled"));

		data = ListOfWords[3];
		EXPECT_EQ(0, strcmp(data,"picked"));

		data = ListOfWords[4];
		EXPECT_EQ(0, strcmp(data,"peppers"));

		data = ListOfWords[5];
		EXPECT_EQ(0, strcmp(data,"pecked"));                

		data = ListOfWords[6];
		EXPECT_EQ(0, strcmp(data,"peck"));		
		
        data = ListOfWords[7];
		EXPECT_EQ(0, strcmp(data,"listen"));
}


TEST(testTRIE, FindWord)
{
	TRIE test;
        test.CreateDictionary("..\\trie\\dictionary.txt");
	EXPECT_EQ(1, test.FindWord("peck"));
	EXPECT_EQ(1, test.FindWord("piper"));
	EXPECT_EQ(0, test.FindWord("apple"));

		
}

TEST(testTRIE, FindSynonyms)
{
	TRIE test;
        test.CreateDictionary("..\\trie\\dictionary.txt");

	vector<string> ListOfSynonyms = test.FindSynonyms("peck");
        string data;
		data = ListOfSynonyms[0];
		EXPECT_EQ(0, strcmp(data,"strike"));

		data = ListOfSynonyms[1];
		EXPECT_EQ(0, strcmp(data,"beak"));

		data = ListOfSynonyms[2];
		EXPECT_EQ(0, strcmp(data,"pick"));
		
}


TEST(testTRIE, FindMeaning)
{
	TRIE test;
        test.CreateDictionary("..\\trie\\dictionary.txt");
	string data = test.FindMeaning("peck");
	EXPECT_EQ(0, strcmp(data,"a stroke or bite by a bird with its beak."));
	data = test.FindMeaning("piper");
	EXPECT_EQ(0, strcmp(data,"a person who plays a pipe, especially an itinerant musician."));
		
}


TEST(testTRIE, FindPrefix)
{
	TRIE test;
        test.CreateDictionary("..\\trie\\dictionary.txt");
	vector<string> ListOfWords = test.OutputPrefix("pick");
	string data;
		data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"picked"));

		data = ListOfWords[1];
		EXPECT_EQ(0, strcmp(data,"pickled"));
		
}


TEST(testTRIE, FindSmallerGreaterEqual)
{
	TRIE test;
        test.CreateDictionary("..\\trie\\dictionary.txt");
	vector<string> ListOfWords = test.OutputSmaller(6);
	string data;
		data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"peck"));

		data = ListOfWords[1];
		EXPECT_EQ(0, strcmp(data,"piper"));
		


	ListOfWords = test.OutputSE(5);

		data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"peck"));

		data = ListOfWords[1];
		EXPECT_EQ(0, strcmp(data,"piper"));


	ListOfWords = test.OutputGreater(6);

		data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"peppers"));

		data = ListOfWords[1];
		EXPECT_EQ(0, strcmp(data,"pickled"));

}

TEST(testTRIE, FindAnagrams)
{
	TRIE test;
        test.CreateDictionary("..\\trie\\dictionary.txt");
	vector<string> ListOfWords = test.OutputAnagrams("listen");
	string data;
		data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"silent"));
		
}


TEST(testTRIE, FindSuffix)
{
	TRIE test;
        test.CreateDictionary("..\\trie\\dictionary.txt");
	vector<string> ListOfWords = test.OutputSuffix("cked");
	string data;
		data = ListOfWords[0];
		EXPECT_EQ(0, strcmp(data,"pecked"));

		data = ListOfWords[1];
		EXPECT_EQ(0, strcmp(data,"picked"));
		
}
