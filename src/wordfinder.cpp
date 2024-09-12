#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

//random words from test letter set rsttee


//isWord to check if word
bool inVect(const std::string& potWord, std::vector<std::vector<std::string>> wordList) {
    int n = potWord.length();
    if(n>8){
        return std::find(wordList[9].begin(), wordList[9].end(), potWord) != wordList[9].end();
    }else{
        return std::find(wordList[n].begin(), wordList[n].end(), potWord) != wordList[n].end();
    }
}
bool inVect(const std::string& potWord, std::vector<std::string> wordList) {
    return std::find(wordList.begin(), wordList.end(), potWord) != wordList.end();
}

std::vector<std::string> listPerms(const std::vector<std::vector<std::string>>& dict, const std::vector<char>& letters){
    //made to list permutations of a set of characters found in dict string vector
    //recursive solution?
    //call listPerms, which finds all perms of passed length, then runs listPerms once for each letter removed
    //does not run another recursive round if word length ==3
    std::vector<std::string> permutations;
    int i = 0;
    //store dict as a vector of vectors to be able to pull up explicit length of words
    while(dict[letters.size()].size()>i){
        if(std::is_permutation(dict[letters.size()][i].begin(), dict[letters.size()][i].end(), letters.begin())){
            permutations.push_back(dict[letters.size()][i]);
            std::cout << "added to perm list: " << dict[letters.size()][i] << std::endl;
            i++;
        }else if(!std::is_permutation(dict[letters.size()][i].begin(), dict[letters.size()][i].end(), letters.begin())){
            i++;
        }else {
            std::cout << "critial error at line 40" << std::endl;
            break;
        }

    }

    if(letters.size()==3){
        return permutations;
    }else {
        int n = 0;
        std::vector<char> letterShort;
        std::vector<std::string> temp;
        while(letters.size()>n){
            letterShort = letters;
            letterShort.erase(letterShort.begin()+n);
            temp = listPerms(dict,letterShort);
            permutations.insert(permutations.end(), temp.begin(), temp.end());
            n++;
        }
        return permutations;
    }
}

int main() {
    // Opening the file
    std::ifstream file("../words_alpha.txt");

    std::vector<std::vector<std::string>>  dictionary; //init dictionary
    std::vector<std::string> dict1;
    std::vector<std::string> dict2;
    std::vector<std::string> dict3;
    std::vector<std::string> dict4;
    std::vector<std::string> dict5;
    std::vector<std::string> dict6;
    std::vector<std::string> dict7;
    std::vector<std::string> dict8;
    std::vector<std::string> dict9;
    dictionary.push_back(dict1);
    dictionary.push_back(dict2);
    dictionary.push_back(dict3);
    dictionary.push_back(dict4);
    dictionary.push_back(dict5);
    dictionary.push_back(dict6);
    dictionary.push_back(dict7);
    dictionary.push_back(dict8);
    dictionary.push_back(dict9);

    std::string str;
    // Read the next line from File until it reaches the end
    while (file >> str) {
        // Now keep reading next line
        // and push it in vector function until end of file
        int n = str.length();
        if(n>8){
            dictionary[9].push_back(str);
        }else{
            dictionary[n].push_back(str);
        }
    }

    //getting letters and creating permslist
    std::string input;
    std::cout << "Provide a word >=3 in length" << std:: endl;
    std::cin >> input;
    std::vector<char> inputChars;
    int n = 0;
    while(input.length()>n){
        inputChars.push_back(input[n]);
        n++;
    }
    std::vector<std::string> permutations = listPerms(dictionary, inputChars);;
    std::cout << permutations.size() << " words added" << std::endl;

    //create "level"
    std::vector<std::string> levelWords = {};//list of words that appear in current level
    int levelNum = 10; //enter number of words in level here
    int rng = rand() % permutations.size();
    levelWords.push_back(permutations[rng]);
    while(levelWords.size()<levelNum-2){
        rng = rand() % permutations.size();
        for(int i = 0; i<levelWords.size(); i++){
            if(permutations[rng]==levelWords[i]){
                break;
            }
            std::cout << i << ": " << permutations[rng] << std::endl;
        }
        levelWords.push_back(permutations[rng]);
        std::cout << levelWords.size() << ": " << levelWords[levelWords.size()-1] << std::endl;
        std::cout << "is " << levelWords.size() << " < " << levelNum-2 << std::endl;
    }


    //"gameplay" time
    std::cout << input << std::endl; //send letters
    std::string inputWord;
    std::vector<std::string> levelFound;
    std::vector<std::string> bonusFound;
    while(levelFound.size()<levelWords.size()){//loop until all correct words have been found
        std::cin >> inputWord; //get guess
        if(inVect(inputWord,levelFound) | inVect(inputWord,bonusFound)){//test if already found
            std::cout << "Already found!" << std::endl;
        }else if(inVect(inputWord, levelWords)){//test if in level
            std::cout << "Hit!" << std::endl;
            levelFound.push_back(inputWord);
        }else if(inVect(inputWord, permutations)){//test if in dictionary
            std::cout << "Bonus Hit!" << std::endl;
            bonusFound.push_back(inputWord);
        }else{
            std::cout << "Not in level!" << std::endl;
        }

    } std::cout << "You win!" << std::endl;


    return 0;
}
