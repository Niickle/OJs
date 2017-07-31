#include <string>

using namespace std;

struct DictTree;
typedef struct DictTree DictTree;

DictTree* dictTreeInit();
int dictTreeInsert(DictTree* pRoot, const string str);   //return overlapped length
DictTree* dictTreeSearch(DictTree* pRoot, const string str);
void dictTreeDestroy(DictTree* pRoot);

#include <map>

struct DictTree {
    int num;
    bool chosen;
    map<char, DictTree*> branch;
};

inline DictTree* dictTreeInit(){
    DictTree* pRoot = new DictTree;
    pRoot->num = 1;
    pRoot->chosen = false;
    return pRoot;
}

int dictTreeInsert(DictTree* pRoot, const string str){   //return overlapped length and number
    if ( !pRoot || str.length() <= 0 )
        return 0;

    int ret = 0;    
    while (ret < (int)str.length() && pRoot->branch.find(str[ret]) != pRoot->branch.end()){
        pRoot = pRoot->branch[str[ret]];
        pRoot->num++;
        ret++;
    }
    
    for (unsigned int i = ret; i < str.length(); i++){
        pRoot->branch[str[i]] = dictTreeInit();
        pRoot = pRoot->branch[str[i]];
    }
    
    return ret;
}

DictTree* dictTreeSearch(DictTree* pRoot, const string str){
    if ( !pRoot || str.length() <= 0 )
        return 0;

    map<char, DictTree*>::iterator it;
    for (unsigned int i = 0; i < str.length(); i++){
        it = pRoot->branch.find( str[i] );
        if( it != pRoot->branch.end() )
            pRoot = it->second;
        else
            return NULL;
    }
    
    return pRoot;
}

void dictTreeDestroy(DictTree* pRoot){
    for (map<char, DictTree*>::iterator it = pRoot->branch.begin(); it != pRoot->branch.end(); it++){
        dictTreeDestroy(it->second);
    }
    delete pRoot;
}

#include <iostream>

int main(){
	//input
	string str;
	cin>>str;
    int len = (int)str.length();
    
    int max = 0;
    int* overlapLen = new int[len];
    DictTree* pRoot = dictTreeInit();
	
	//solve
    for (int i = str.length() - 1; i >= 0; i--){
        overlapLen[i] = dictTreeInsert(pRoot, str.substr(i));
        max = max > overlapLen[i] ? max : overlapLen[i];
    }

	//output
	if (max > 0){
        string strTmp;
        DictTree* pNode;
        for (unsigned int i = 0; i < str.length(); i++){
            if (overlapLen[i] == max){
                strTmp = str.substr(i, max);
                pNode = dictTreeSearch(pRoot, strTmp);
                if (pNode && !pNode->chosen) {
                    cout<<strTmp<<':'<<pNode->num<<endl;
                    pNode->chosen = true;
                }
            }
        }
    }
    
    //delete
    delete [] overlapLen;
    dictTreeDestroy(pRoot);
	
	return 0;
}
