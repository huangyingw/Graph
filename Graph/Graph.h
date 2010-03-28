#include "E:\programming\pass\c++\s���ݽṹ���㷨\ѭ������\CirQueue.h"
#include "E:\programming\pass\c++\s���ݽṹ���㷨\ջ\stack.h"
template <class Type> struct Arc
{
	int pre;//����һ���
	int next;//����һ���
	Type weight;//����Ȩ
	bool isVisited;//��ǻ��Ƿ񱻷��ʹ�
};

template <class Type> struct EdgeNode
{	
	int adjVex; 
	struct EdgeNode<Type> *next;
	Type weight; //���ϵ�Ȩ
};

template <class Type> struct VertexNode//�������
{
	Type vertex; //������
	EdgeNode<Type> *firstEdge;//�߱�ͷָ��
};

template <class Type> class Graph
{
private:
	VertexNode<Type>* adjList;//�ڽӱ�
	int verNum;//ͼ�е�ǰ������s
	int arcNum;//ͼ�е�ǰ���� 
	bool nodeVisited[100]; //�ڵ���ʱ�־����,��ȫ����
	int arcVisited[100]; //�����ʱ�־������,ȫ����
	int leastDist[100];//��С��������
	Type** adjMatrix;//��Ȩֵ����
	void BFS(int k);
	bool isShortestVertex[MAX];//��ǵ�ǰ����Ƿ�����С�߼���
	Type* data;//ʵ�ִ洢������
	int* preVertex;//��ǰ����ǰһ�������±�� 
public:
	Graph(int *data,int dim,int n);
	void CreateAdjMatrix(int *data,int dim);
	void CreatAdjList();//���ڽӱ�洢ͼ
	void DFSTraverse();
	void PrintAdjMatrix();//��ӡ�ڽӾ���
	void BFSTraverse();
	int Prim(); //��С������PRIM�㷨
	void Kruscal();
	int Find(int arcVisited[],int f);//��δ�����ʹ��Ļ����±�
	void InitialShortestVertex();
	int LeastDistAddS();//�ӵ�ǰleastDist�������ҳ���С��,������ǰ��С�ı߶�Ӧ���ս�����isShortestVertex����
	void Dijkstra();//�������·���������������������
	void PrintShortestPath();//�����������еĽ����ӡ����
	void InitialLeastDist();/*��ʼ��leastDist����*/
};

template <class Type> int Graph<Type>:: LeastDistAddS()//�ӵ�ǰleastDist�������ҳ���С��,������ǰ��С�ı߶�Ӧ���ս�����isShortestVertex����
{
	//�洢��СleastDist valueֵ
	int LeastDistValue=MAX;
	//�洢��СleastDist ����±�ֵ
	int LeastDistIndex=-1;
	for(int i=0;i<5;i++)
	{
		if(leastDist[i]<LeastDistValue&&!isShortestVertex[i])
		{
			LeastDistValue=leastDist[i];
			LeastDistIndex=i;
		}
	}
	isShortestVertex[LeastDistIndex]=true;
	return LeastDistIndex;
}

template <class Type> void Graph<Type>::InitialShortestVertex()
{
	for(int i=0;i<verNum;i++)//dist,path�����ʼ��
	{
		//�ڽӾ����v��Ԫ�ظ��Ƶ�dist��
		isShortestVertex[i]=false;							//��������·���Ķ��㼯�ϳ�ʼ��
	}
}

template <class Type> void Graph<Type>::InitialLeastDist()/*��ʼ��leastDist����*/
{
	for(int i=0;i<verNum;i++)//leastDist�����ʼ��
	{
		leastDist[i]=adjMatrix[0][i];
		if(i!=0&&leastDist[i]<MAX)
		{
			preVertex[i]=0;
		}
		else
		{
			preVertex[i]=-1;					//·����������ʼ��
		}
	}
}

template <class Type> void Graph<Type>::Dijkstra()//Ĭ�ϴ�0�Ž�㿪ʼ�������·��
{
	InitialShortestVertex();//�ȳ�ʼ��isShortestVertex����
	InitialLeastDist();//��ʼ��leastDist����
	//�����0�Ž�����
	isShortestVertex[0]=true;
	leastDist[0]=0;//v��v�ľ���Ϊ0
	for(int i=0;i<verNum;i++)//�Ӷ���vȷ��n-1��·��
	{
		int min=MAX;
		int u=0;
		for(int j=0;j<verNum;j++)//ѡ��ǰ���ڼ���S�о������·���Ķ���u
		{
			if(!isShortestVertex[j]&&leastDist[j]<min)
			{
				u=j;
				min=leastDist[j];
			}
		}
		cout<<u<<" was selected into the shortest vertexes arrays"<<endl;
		isShortestVertex[u]=true;//������S���뼯��S����ʾ���������·����
		for(int w=0;w<verNum;w++)//�޸���u���ڵ�w�������̾���
		{
			if(!isShortestVertex[w]&&adjMatrix[u][w]<MAX&&leastDist[u]+adjMatrix[u][w]<leastDist[w])//w���㲻�����·���Ķ��㼯��&&u,w����&&��u��w�ľ���С�ڵ�ǰw�����·��
			{
				leastDist[w]=leastDist[u]+adjMatrix[u][w];//�޸�w����̾���
				/*cout<<"now changing the "<<w<<"'s dist to "<<leastDist[w]<<endl;
				cout<<"now changing the "<<w<<"'s neighbor vertex to be "<<u<<endl;*/
				preVertex[w]=u;//�޸�w�����·��
			}
		}
	}

}

template <class Type> void Graph<Type>::PrintShortestPath()//�����������еĽ����ӡ����
{
	int vertexNum;
	for(int i=0;i<verNum;i++)
	{
		vertexNum=i;
		SeqStack<Type> *stack=new SeqStack<Type>();
		stack->InitStack();
		cout<<i<<":";
		if(vertexNum>=0)
		{
			stack->Push(vertexNum);
		}
		vertexNum=preVertex[vertexNum];
		while(vertexNum>=0)
		{	
			stack->Push(vertexNum);
			vertexNum=preVertex[vertexNum];
		}
		
		while(!stack->StackEmpty())
		{
			cout<<stack->Pop()<<",";
		}
		cout<<"->"<<leastDist[i]<<endl;
	}
	
}
template <class Type> void Graph<Type>::CreatAdjList()//���ڽӱ�洢ͼ
{
	EdgeNode<Type> *arc;
	for(int i=0;i<verNum;i++)
	{
		adjList[i].vertex=i;
		adjList[i].firstEdge=NULL;
	}
	for(int i=0;i<verNum;++i)
	{
		for(int j=0;j<verNum;++j)
		{
			if(adjList[i].firstEdge==NULL)
			{
				if(adjMatrix[i][j]>0&&adjMatrix[i][j]<MAX&&j<verNum)
				{
					arc=new EdgeNode<Type>();
					arc->adjVex=j;
					arc->weight=adjMatrix[i][j];
					arc->next=NULL;
					adjList[i].firstEdge=arc;
				}
			}
			else
			{
				if(adjMatrix[i][j]>0&&adjMatrix[i][j]<MAX&&j<verNum)
				{
					arc=new EdgeNode<Type>();
					arc->adjVex=j;
					arc->weight=adjMatrix[i][j];
					arc->next=adjList[i].firstEdge;
					adjList[i].firstEdge=arc;
				}
			}
		}
	}
}

template <class Type> int Graph<Type>::Find(int arcVisited[],int f)//��δ�����ʹ��Ļ����±�
{
	while(arcVisited[f]>0)
	{
		f=arcVisited[f];
	}
	return f;
}

template <class Type> void Graph<Type>::Kruscal()
{ 
	//��ʼ��edgs����
	Arc<Type> arcs[20];
	int k=0;
	for(int i=0;i<verNum;++i)
	{
		for(int j=i;j<verNum;++j)
		{
			if(adjMatrix[i][j]<MAX)
			{
				arcs[k].pre=i;
				arcs[k].next=j;
				arcs[k].weight=adjMatrix[i][j];
				arcs[k].isVisited=false;
				++k;
			}
		}
	}

	int preMIN,nextMIN,weightMIN,indexMIN,begG,endG;
	for(int i=0;i<arcNum;++i)
		arcVisited[i]=0; 
	for(int j=0;j<arcNum;++j)
	{
		weightMIN=MAX;//Ѱ��weightֵ��С��edges,������С��
		for(int i=0;i<arcNum;++i)
		{
			if(!arcs[i].isVisited&&arcs[i].weight<weightMIN)
			{
				weightMIN=arcs[i].weight;
				preMIN=arcs[i].pre;
				nextMIN=arcs[i].next;
				indexMIN=i;
			}
		}
		
		begG=Find(arcVisited,preMIN);
		endG=Find(arcVisited,nextMIN); 
		arcs[indexMIN].isVisited=true;
		if(begG!=endG)//������ͨ��ͼ
		{
			/*for(int i=0;i<verNum;i++)
			{
				cout<<i<<":"<<arcVisited[i]<<", ";
			}*/
			
			arcVisited[begG]=endG;//���begG���ڽӽڵ�ΪendG
			/*cout<<begG<<","<<endG<<endl;*/
			cout<<"("<<preMIN<<","<<nextMIN<<")"<<weightMIN;
			cout<<endl;
		}
	}
}

template <class Type> int Graph<Type>::Prim() //��С������PRIM�㷨
{
	Type* lowCost=new Type[verNum];//LOWCOST[i]�洢i��ǰ����U�ֱ�ʣ��������·��
	Type* preVex=new Type[verNum]; //preVex[i]�洢i��ǰһ�����,preVex[]�洢���·����U�еĽ��

	
	int i,j,k,MIN; 
	
	for(i=1;i<verNum;i++) //n�����㣬n-1���� 
	{
		lowCost[i]=adjMatrix[0][i]; //��ʼ�� 
		preVex[i]=0; //����δ���뵽��С�������� 
	}	
	
	lowCost[0]=0; //��־����1����U����,
	
	for(i=1;i<verNum;i++) //�γ�n-1���ߵ������� 
	{
		MIN=MAX; 
		k=0; 

		for(j=1;j<verNum;j++) //Ѱ����С��,����һ��������U,��һ��������V�� 
		{
			if((lowCost[j]<MIN)&&(lowCost[j]!=0)) //lowCost[j]!=0˵������j����U
			{
				MIN=lowCost[j]; 
				k=j; 
			} 
		}

		cout<<preVex[k]<<","<<k<<","<<MIN<<endl;
		lowCost[k]=0; //����k����U 
		
		for(j=1;j<verNum;j++) //�޸��ɶ���k����������ߵ�Ȩֵ 
		{
			if(lowCost[j]>adjMatrix[k][j]) 
			{
				lowCost[j]=adjMatrix[k][j]; 
				preVex[j]=k; //�ڴ˴�����preVex��ֵ
				/*cout<<j<<"->"<<k<<":"<<lowCost[j]<<endl;*/
			} 
		}
	}  
	return 0;
} 

template <class Type> void Graph<Type>::CreateAdjMatrix(int *data,int dim)
{
	adjMatrix=new Type*[dim];
	for(int i=0;i<dim;i++)
	{
		adjMatrix[i]=new Type[dim];
		for(int j=0;j<dim;j++)
		{
			adjMatrix[i][j]=data[i*dim+j];
		}
	}
}

template <class Type> Graph<Type>::Graph(int *data,int dim,int n)//�˷����ǰ��½�����ͷ���ĺ���
{
	verNum=n;
	arcNum=20;
	adjList=new VertexNode<Type>[verNum];
	preVertex=new int[verNum];
	for(int i=0;i<dim;i++)
	{
		adjList[i].firstEdge=NULL;
		for(int j=i+1;j<dim;j++)
		{
			if(data[i*dim+j]<MAX)
			{
				EdgeNode<Type> *edgeNode=new EdgeNode<Type>;
				edgeNode->adjVex=j;
				edgeNode->next=adjList[i].firstEdge;
				adjList[i].firstEdge=edgeNode;
			}
		}
	}
}

template <class Type> void Graph<Type>::PrintAdjMatrix()//��ӡ�ڽӾ���
{
	EdgeNode<Type> *node;
	for(int i=0;i<verNum;i++)
	{
		node=adjList[i].firstEdge;
		cout<<adjList[i].vertex;
		while(NULL!=node)
		{
			cout<<"->"<<node->adjVex<<"("<<node->weight<<")";
			node=node->next;
		}
		cout<<endl;
	}
}

template <class Type> void Graph<Type>::BFSTraverse()
{ 
	int i;
	for(i=0;i<verNum;i++)
		nodeVisited[i]=false;
	for(i=0;i<verNum;i++)
	{
		if(!nodeVisited[i])
		{
			BFS(i);
		}
	}
	cout<<endl;
}

template <class Type> void Graph<Type>::BFS(int k)
{
	cout<<k<<",";
	nodeVisited[k]=true;
	CirQueue<int> *q=new CirQueue<int>;
	q->InitQueue();
	EdgeNode<Type> *node=adjList[k].firstEdge;
	while(node!=NULL&&!nodeVisited[node->adjVex])
	{
		cout<<node->adjVex<<",";
		q->EnQueue(node->adjVex);
		nodeVisited[node->adjVex]=true;
		node=node->next;
	}
	if(!q->QueueEmpty())
	{
		k=q->DeQueue();
		if(!nodeVisited[k])
		{
			BFS(k);
		}
	}
	else
	{
		return;
	}
}

template <class Type> void Graph<Type>::DFSTraverse()//�����������
{
	int count=0;
	for(int i=0;i<verNum;i++)
		nodeVisited[i]=false;
	for(int i=0;i<verNum;i++)
	{
		if(nodeVisited[i]==false)
		{
			nodeVisited[i]=true;
			cout<<i<<",";
			EdgeNode<Type> *edgeNode=adjList[i].firstEdge;
			while(edgeNode!=NULL)
			{
				if(nodeVisited[edgeNode->adjVex]==false)
				{
					cout<<edgeNode->adjVex<<",";
					nodeVisited[edgeNode->adjVex]=true;
				}
				edgeNode=edgeNode->next;
			}
		}
	}
	cout<<endl;
}


