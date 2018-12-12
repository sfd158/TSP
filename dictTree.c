#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "dictTree.h"

struct dictWordTreeNode* initDictWordNode(struct dictWordTree *tree, const int _value,const int _has_node)
{
	struct dictWordTreeNode* node = (struct dictWordTreeNode*)malloc(sizeof(struct dictWordTreeNode));
	node->next = (struct dictWordTreeNode**)malloc(sizeof(struct dictWordTreeNode*)*(tree->nodeNextCnt));
	memset(node->next,0,sizeof(struct dictWordTreeNode*)*(tree->nodeNextCnt));
	node->value = _value;
	node->has_node = _has_node;
	tree->nodeCnt++;
	return node;
}
struct dictWordTree* initDictWordTree(const int _nodeNextCnt)
{
	struct dictWordTree * tree = (struct dictWordTree*)malloc(sizeof(struct dictWordTree));
	tree->nodeNextCnt = _nodeNextCnt;
	tree->wordCnt = 0;
	tree->nodeCnt = 0; 
	tree->root = initDictWordNode(tree,0,0);
	return tree; 
}
static void destroyDictWordNode(struct dictWordTree* tree, struct dictWordTreeNode * node)
{
	int i;
	if(node == NULL) return;
	for(i=0;i<tree->nodeNextCnt;i++)
	{
		if(node->next[i] != NULL)
		{
			destroyDictWordNode(tree, node->next[i]);
		}
	}
	free(node->next);
	free(node);
} 
void destroyDictWordTree(struct dictWordTree *tree)
{
	destroyDictWordNode(tree, tree->root);
	free(tree);
}
void insertDictWordTree(struct dictWordTree* tree, const char * s, const int value)
{
	const char *p = s;
	struct dictWordTreeNode * node = tree->root;
	while(*p != '\0')
	{
		int c = *p - 'a';
		if(c<0 || c>=tree->nodeNextCnt) return;
		if(node->next[c] == NULL)
		{
			node->next[c] = initDictWordNode(tree,0,0);
		}
		p++;
		node = node->next[c];
	}
	if(node->has_node)return;
	node->has_node = 1;
	node->value = value;
	tree->wordCnt++;
}
struct dictWordTreeNode* findDictWordTree(struct dictWordTree* tree, const char *s,int *depth)
{
	const char *p = s;
	struct dictWordTreeNode * node = tree->root;
	while(*p != '\0')
	{
		int c = *p - 'a';
		if(c<0 || c>=tree->nodeNextCnt) return NULL;
		if(node->next[c] != NULL)
		{
			p++;
			node = node->next[c];
		}
		else return NULL;
	}
	if(depth != NULL)
	{
		*depth = p-s;
	}
	return node;
}
void removeFromDictTree(struct dictWordTree* tree, const char *s)
{
	int depth;
	struct dictWordTreeNode* node = findDictWordTree(tree, s, &depth);
	if(node == NULL)return;
	
	node->value = 0;
	node->has_node = 0;
	tree->wordCnt--;
}

typedef struct outputQ
{
	struct dictWordTreeNode* node;
	int pa;
	int depth;
	int path;
}outputQ;
void outputDictTree(struct dictWordTree *tree, const int print_all)
{
	int head=0, tail=1, i;
	outputQ *q = (outputQ*)malloc(sizeof(outputQ)*(tree->nodeCnt));
	outputQ *r,*t;
	char * buf = (char*)malloc(sizeof(char)*(tree->nodeCnt+2));
	int bufcnt = 0;
	q[head].node=tree->root; q[head].pa=-1; q[head].depth=0;
	while(head < tail)
	{
		t = &q[head];
		for(i=0; i<tree->nodeNextCnt; i++)
		{
			if(t->node->next[i] != NULL)
			{
				r=&q[tail++];
				r->depth=t->depth+1; r->pa=head; r->node=t->node->next[i]; r->path=i;
				if(print_all || r->node->has_node)
				{
					bufcnt = 0;
					while(r->pa != -1)
					{
						buf[bufcnt++] = r->path+'a';
						r = &q[r->pa];
					}
					buf[bufcnt++] = '\0';
					strrev(buf);
					printf("%s\n",buf);
				}
				/*printf("path:%c depth:%d value:%d, has_node:%d\n",i+'a',r->depth,r->node->value,r->node->has_node);*/
			}
		}
		head++;
	}
}
