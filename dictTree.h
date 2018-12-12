
#ifndef DICT_TREE_H
#define DICT_TREE_H
struct dictWordTreeNode
{
	struct dictWordTreeNode ** next;
	int value;
	int has_node;
};
struct dictWordTree
{
	struct dictWordTreeNode * root;
	int nodeNextCnt;
	int wordCnt;
	int nodeCnt;
};
struct dictWordTreeNode* initDictWordNode(struct dictWordTree *tree, const int _value,const int _has_node);
struct dictWordTree* initDictWordTree(const int _nodeNextCnt);
void destroyDictWordTree(struct dictWordTree *tree);
void insertDictWordTree(struct dictWordTree* tree, const char * s, const int value);
struct dictWordTreeNode* findDictWordTree(struct dictWordTree* tree, const char *s, int *depth);
void removeFromDictTree(struct dictWordTree* tree, const char *s);
void outputDictTree(struct dictWordTree * tree,const int print_all);
#endif

