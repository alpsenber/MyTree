#pragma once
class LCRS_node
{
public:
	int value; // значение узла дерева
	int size; // размер дерева
	LCRS_node* L_child;	// левый сын/дочь
	LCRS_node* R_sibling; // правый брат/сестра
	LCRS_node(int v)
	{
		value = v;
		size = 1;
		L_child = R_sibling = 0;
	}
	~LCRS_node()
	{
		if (L_child != 0) delete R_sibling;
		delete L_child;
	}
};

