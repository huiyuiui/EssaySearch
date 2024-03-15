#define FILE_EXTENSION ".txt"
#include <cstring>
#include <fstream>
#include <io.h>
#include <iostream>
#include <iterator>
#include <set>
#include <string>
#include <vector>
#define pair pair<string, int>

using namespace std;

typedef struct TrieNode
{
    TrieNode *a[26];
    int n;

    TrieNode()
    {
        memset(a, 0, sizeof(TrieNode *) * 26);
        n = 0;
    }
} TrieNode;

vector<TrieNode *> Tree;
vector<TrieNode *> TreeRev;

void addTrie(string str, TrieNode *root)
{
    TrieNode *p = root;
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
    for (auto chr : str)
    {
        if (!p->a[chr - 'a'])
            p->a[chr - 'a'] = new TrieNode();
        p = p->a[chr - 'a'];
    }
    p->n++;
}

void addTrieRev(string str, TrieNode *root)
{
    TrieNode *p = root;
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
    for (int i = length - 1; i >= 0; i--)
    {
        if (!p->a[str[i] - 'a'])
            p->a[str[i] - 'a'] = new TrieNode();
        p = p->a[str[i] - 'a'];
    }
    p->n++;
}

bool findTrie(string str, TrieNode *root)
{
    TrieNode *p = root;
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
    for (auto chr : str)
    {
        if (!p->a[chr - 'a'])
            return false;
        p = p->a[chr - 'a'];
    }
    return true;
}

bool findTrieRev(string str, TrieNode *root)
{
    TrieNode *p = root;
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
    for (int i = length - 1; i >= 0; i--)
    {
        if (!p->a[str[i] - 'a'])
            return false;
        p = p->a[str[i] - 'a'];
    }
    return true;
}

bool findTrieExact(string str, TrieNode *root)
{
    TrieNode *p = root;
    int length = str.length();
    for (int i = 0; i < length; i++)
    {
        str[i] = tolower(str[i]);
    }
    for (auto chr : str)
    {
        if (!p->a[chr - 'a'])
            return false;
        p = p->a[chr - 'a'];
    }
    return ((p->n) > 0);
}

void getFiles(string path, vector<string> &files)
{
    long hFile = 0;
    struct _finddata_t fileinfo;
    string p;
    if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
    {
        do
        {
            if ((fileinfo.attrib & _A_SUBDIR))
            {
                if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
                    getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
            }
            else
            {
                files.push_back(fileinfo.name);
            }
        } while (_findnext(hFile, &fileinfo) == 0);
        _findclose(hFile);
    }
}

vector<string> sortFiles(string data_dir)
{
    vector<string> files;
    vector<string> tempFiles;
    set<int> sortFiels;
    getFiles(data_dir, tempFiles);
    for (auto it : tempFiles)
    {
        int index = 0;
        for (int i = 0;; i++)
        {
            if (it[i] == '.')
                break;
            index = index * 10 + (it[i] - '0');
        }
        sortFiels.insert(index);
    }
    for (auto it : sortFiels)
    {
        files.push_back(to_string(it).append(".txt"));
    }
    return files;
}

vector<string> word_parse(vector<string> tmp_string)
{
    vector<string> parse_string;
    for (auto &word : tmp_string)
    {
        string new_str;
        for (auto &ch : word)
        {
            if (isalpha(ch))
                new_str.push_back(ch);
        }
        parse_string.emplace_back(new_str);
    }
    return parse_string;
}

vector<string> split(const string &str, const string &delim)
{
    vector<string> res;
    if ("" == str)
        return res;
    //鍏堝皣瑕佸垏鍓茬殑瀛椾覆寰瀞tring鍨嬪垾杞夋彌鐐篶har*鍨嬪垾
    char *strs = new char[str.length() + 1]; //涓嶈蹇樹簡
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p)
    {
        string s = p;     //鍒嗗壊寰楀埌鐨勫瓧涓茶綁鎻涚偤string鍨嬪垾
        res.push_back(s); //瀛樺叆绲愭灉闄ｅ垪
        p = strtok(NULL, d);
    }

    return res;
}

int main(int argc, char *argv[])
{
    string data_dir = argv[1] + string("/");
    string query = string(argv[2]);
    string output = string(argv[3]);

    fstream fi;
    fstream fq;
    fstream fo;

    string file, title_name, tmp;
    vector<string> tmp_string;
    vector<string> allTitle;

    fq.open(query, ios::in);
    fo.open(output, ios::out);

    int totalFile;
    //build
    for (int i = 0;; i++)
    {
        //open file
        fi.open(data_dir + to_string(i) + FILE_EXTENSION, ios::in);
        if (fi.is_open() == 0)
        {
            totalFile = i;
            break;
        }

        TrieNode *root = new TrieNode();
        TrieNode *rootRev = new TrieNode();

        // GET TITLENAME
        getline(fi, title_name);
        allTitle.push_back(title_name);

        // GET TITLENAME WORD ARRAY
        tmp_string = split(title_name, " ");

        vector<string> title = word_parse(tmp_string); //get currect title

        //build
        for (auto word : title)
        {
            addTrie(word, root);
            addTrieRev(word, rootRev);
        }

        // GET CONTENT LINE BY LINE
        while (getline(fi, tmp))
        {

            // GET CONTENT WORD VECTOR
            tmp_string = split(tmp, " ");

            // PARSE CONTENT
            vector<string> content = word_parse(tmp_string);
            for (auto word : content)
            {
                addTrie(word, root);
                addTrieRev(word, rootRev);
            }
        }
        Tree.push_back(root);
        TreeRev.push_back(rootRev);
        // CLOSE FILE
        fi.close();
    }

    //search
    int nowFile;
    int haveAns;
    int type;
    string queryStr;
    while (getline(fq, queryStr))
    {
        //get query and type respectively
        vector<pair> queryPair;
        int length = queryStr.length();
        for (int i = 0; i < length; i++)
        {
            if (queryStr[i] == ' ')
            {
                continue;
            }
            else if (queryStr[i] == '"') //exact
            {
                type = 1;
                string tempQuery;
                for (int j = i + 1;; j++)
                {
                    if (queryStr[j] == '"')
                    {
                        i = j;
                        queryPair.push_back(pair(tempQuery, type));
                        break;
                    }
                    tempQuery += queryStr[j];
                }
            }
            else if (queryStr[i] == '*') //suffix
            {
                type = 2;
                string tempQuery;
                for (int j = i + 1;; j++)
                {
                    if (queryStr[j] == '*')
                    {
                        i = j;
                        queryPair.push_back(pair(tempQuery, type));
                        break;
                    }
                    tempQuery += queryStr[j];
                }
            }
            else if (queryStr[i] == '/')
            {
                type = 3;
                queryPair.push_back(pair("/", type));
            }
            else if (queryStr[i] == '+')
            {
                type = 4;
                queryPair.push_back(pair("+", type));
            }
            else //prefix
            {
                type = 5;
                string tempQuery;
                for (int j = i;; j++)
                {
                    tempQuery += queryStr[j];
                    if ((queryStr[j + 1] == ' ') || (j + 1 == length))
                    {
                        i = j + 1;
                        queryPair.push_back(pair(tempQuery, type));
                        break;
                    }
                }
            }
        }

        //search every files by queryPair
        nowFile = 0;
        int nowQueryIdx;
        int notFound = 1;
        for (int i = 0; i < totalFile; i++)
        {
            haveAns = 0;
            nowQueryIdx = 0;
            for (auto iter : queryPair)
            {
                if (nowQueryIdx == 0) //first one do it directly
                {
                    if (queryPair[nowQueryIdx].second == 1) //exact
                        haveAns = findTrieExact(queryPair[nowQueryIdx].first, Tree[nowFile]);
                    else if (queryPair[nowQueryIdx].second == 2) //suffix
                        haveAns = findTrieRev(queryPair[nowQueryIdx].first, TreeRev[nowFile]);
                    else if (queryPair[nowQueryIdx].second == 5) //prefix
                        haveAns = findTrie(queryPair[nowQueryIdx].first, Tree[nowFile]);
                    nowQueryIdx++;
                    continue;
                }
                if (queryPair[nowQueryIdx].second == 3 || queryPair[nowQueryIdx].second == 4)
                {
                    nowQueryIdx++;
                    continue;
                }
                else
                {
                    int nowAns;
                    if (queryPair[nowQueryIdx].second == 1) //exact
                        nowAns = findTrieExact(queryPair[nowQueryIdx].first, Tree[nowFile]);
                    else if (queryPair[nowQueryIdx].second == 2) //suffix
                        nowAns = findTrieRev(queryPair[nowQueryIdx].first, TreeRev[nowFile]);
                    else if (queryPair[nowQueryIdx].second == 5) //prefix
                        nowAns = findTrie(queryPair[nowQueryIdx].first, Tree[nowFile]);
                    //operation
                    if (queryPair[nowQueryIdx - 1].second == 3)
                    { //or
                        haveAns = haveAns | nowAns;
                    }
                    else if (queryPair[nowQueryIdx - 1].second == 4)
                    { //and
                        haveAns = haveAns & nowAns;
                    }
                    nowQueryIdx++;
                    continue;
                }
            }
            if (haveAns)
            {
                notFound = 0;
                fo << allTitle[nowFile] << endl;
            }
            nowFile++;
        }
        if (notFound)
        {
            fo << "Not Found!" << endl;
        }
    }
}
//g++ -std=c++17 -o essay-search.exe main.cpp -lstdc++fs
//.\essay-search.exe .\data-more query-more.txt output3.txt