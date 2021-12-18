#include <iostream>
#include <vector>

using namespace std;

struct node {
	int id;
	int parent;
	int weight;
};//node struct ����, ������ ��ȣ, ����� ������ ��ȣ, ������ ����� ���ҷ� ������. 

class heap {
private:
	vector<node> nodes;//array ������� heap�� �����Ѵ�.

public:
	heap() {
		node n = { 0, 0, 0 };
		nodes.emplace_back(n);//���� 0��° index�� �Ⱦ��� ���� ������ ���� �Է��Ѵ�.
	}

	void upHeap(int child) {//�Է½� ���ϸ鼭 �ڸ� ã�ư��� �Լ�
		int parent = child / 2;//parent index ���� �����Ѵ�.
		if (parent < 2) {//parent index�� 2���� ������� �񱳸� �����Ѵ�.
			return;
		}
		if (nodes[parent].weight < nodes[child].weight) {//parent ���� weight�� child ���� weight������ ������� �񱳸� �����Ѵ�.
			return;
		}
		else if (nodes[parent].weight == nodes[child].weight) {//parent ���� weight�� child���� weight���� ���� ���
			if (nodes[parent].id > nodes[child].id) {//parent�� id�� node�� id���� ū ��� 
				node tmp = nodes[parent];
				nodes[parent] = nodes[child];
				nodes[child] = tmp;//parent ���� child ���� swap �Ѵ�.
				if (parent == 1) {//parent�� root node�� ��� �񱳸� �����Ѵ�.
					return;
				}
				this->upHeap(parent);//root node �ƴ� ��� �ٽ��ѹ� ���Ϸ� ����.
			}
			else {
				return;//parent�� id�� node�� id���� ���� ��� �ٷ� �񱳸� �����Ѵ�.
			}
		}
		else {//parent�� weight ���� child�� weight ������ ū ���
			node tmp = nodes[parent];
			nodes[parent] = nodes[child];
			nodes[child] = tmp;//parent ���� child ���� swap �Ѵ�.
			if (parent == 1) {//parent�� root node�� ��� �񱳸� �����Ѵ�.
				return;
			}
			this->upHeap(parent);//root node �ƴ� ��� �ٽ��ѹ� ���Ϸ� ����.
		}
		return;
	}

	void downHeap(int parent) {//���� �� root node�� �� ã������ ����Ǵ� �Լ�
		int comp = 0;
		int index = 0;
		int nodesS = nodes.size() - 1;
		if (parent * 2 > nodesS) {//parent�� ���� child�� index ���� heap�� size���� ū ��� �񱳸� �����Ѵ�.
			return;
		}
		else if (parent * 2 == nodesS) {//heap�� size�� parent�� ���� child�� index ���� ���� ���
			comp = nodes[parent * 2].weight;
			index = parent * 2;//�񱳰��� �ش� index�� parent�� ���� child�� �����Ѵ�.
		}
		else if (nodes[parent * 2].weight > nodes[parent * 2 + 1].weight) {//���� child�� weight ���� ������ child�� weight ������ Ŭ ���
			comp = nodes[parent * 2 + 1].weight;
			index = parent * 2 + 1;//�񱳰��� �ش� index�� parent�� ������ child�� �����Ѵ�.
		}
		else if (nodes[parent * 2].weight == nodes[parent * 2 + 1].weight) {//���� child�� weight ���� ������ child�� weight ���� ���� ���
			if (nodes[parent * 2].id > nodes[parent * 2 + 1].id) {//���� child�� id ���� ������ child�� id ������ Ŭ ���
				comp = nodes[parent * 2 + 1].weight;
				index = parent * 2 + 1;//�񱳰��� �ش� index�� parent�� ������ child�� �����Ѵ�.
			}
			else {//���� child�� id ���� ������ child�� id ������ ���� ���
				comp = nodes[parent * 2].weight;
				index = parent * 2;//�񱳰��� �ش� index�� parent�� ���� child�� �����Ѵ�.
			}
		}
		else {//���� child�� weight ���� ������ child�� weight ������ ���� ���
			comp = nodes[parent * 2].weight;
			index = parent * 2;
		}//�񱳰��� �ش� index�� parent�� ���� child�� �����Ѵ�.

		if (comp > nodes[parent].weight) {//�񱳰��� parent�� weight ������ Ŭ ��� �񱳸� �����Ѵ�.
			return;
		}
		else if (comp == nodes[parent].weight) {//�񱳰��� parent�� weight ���� ���� ��� 
			if (nodes[index].id > nodes[parent].id) {//�ش� �񱳰��� ���� child�� id ���� parent�� id������ Ŭ ��� �񱳸� �����Ѵ�.
				return;
			}
			else {//�ش� �񱳰��� ���� child�� id ���� parent�� id������ ���� ���
				node tmpN = nodes[index];
				nodes[index] = nodes[parent];
				nodes[parent] = tmpN;//�ش� �񱳰��� ���� child�� parent�� swap�Ѵ�.
				downHeap(index);//�ٽ��ѹ� ���Լ��� ȣ���Ѵ�.
			}
		}
		else {//�񱳰��� parent�� weight ������ ���� ���
			node tmpN = nodes[index];
			nodes[index] = nodes[parent];
			nodes[parent] = tmpN;//�ش� �񱳰��� ���� child�� parent�� swap�Ѵ�.
			downHeap(index);//�ٽ��ѹ� ���Լ��� ȣ���Ѵ�.
		}
		return;
	}

	void push(node val) {//heap�� ���ο� ���� �Է��ϴ� �Լ�
		nodes.emplace_back(val);//��� �迭�� ���Ҹ� �Է��Ѵ�.
		if (nodes.size() == 2) {//���� root node��� ���� �۾����� �����Ѵ�.
			return;
		}
		upHeap(nodes.size() - 1);//root node�� �ƴ϶�� ���Լ��� ȣ���Ѵ�.
	}

	node pop() {//heap���� �ּҰ��� ���� �ش� ���� return �ϴ� �Լ�
		node top = this->nodes[1];// root node�� ���� �����Ѵ�.
		if (nodes.size() == 2) {//root node�ۿ� ���� ���
			nodes.pop_back();//���� �� �ش� �� ��ȯ�Ѵ�.
			return top;
		}
		nodes[1] = nodes.back();
		nodes.pop_back();//root node �ƴ϶�� �� ������ ���� root node�� �ű� �� �ش� ������ ���� ��ġ�� �����Ѵ�.
		downHeap(1);//���Լ��� ȣ���Ѵ�.
		return top;//�Լ� ���� �� �ּ� ���� ��ȯ�Ѵ�.
	}

	int size() {
		return this->nodes.size() - 1;
	}//0��° ��� �����ϰ� ���� ������ ���� ��ȯ���ִ� �Լ�
};


class graph {
private:
	vector<node> tree;//tree group
	vector<node> fringe;//fringe group
	vector<vector<int>> gList;//��ü �׷��� ������
	int structSize = 0;//�׷��� �������� ����(����) ��
public:
	graph(vector<vector<int>> list, int start, int size) {
		gList = list;
		structSize = size;
		node root = {start, 0, 0};
		tree.emplace_back(root);//�����ڿ��� �׷��� �����Ϳ� ����(����)���� �޾ƿ��� start vertex�� �޾Ƽ� tree�� �־��ش�.
	}

	node trav() {
		int start = tree.back().id - 1;//start node index
		int fSize = fringe.size();
		for (int i = 0; i < structSize; i++) {//start node�� �ٸ� ��� node���� Ȯ���ϰ� ���� �Ǿ��ִٸ� fringe�� �ִ´�.
			bool isMatch = false;
			if (gList[start][i] == -1) {//������� �ʾ����� ���� node�� Ȯ���Ѵ�.
				continue;
			}
			int nodeId = i + 1;
			for (int j = 0; j < fSize; j++) {//�̹� fringe�� �� node���� �˻��Ѵ�.
				if (nodeId == fringe[j].id) {//���� �̹� fringe�� ���� ���
					isMatch = true;
					if (gList[start][i] < fringe[j].weight) {//���� �̹� fringe�� �ִ� weight ������ ���� weight ���� �� �������
						gList[fringe[j].id - 1][fringe[j].parent - 1] = -1;//�ش� fringe�� ���� parent ���� �����Ѵ�.
						fringe[j].weight = gList[start][i];
						fringe[j].parent = start + 1;//fringe parent, weight ���� update �Ѵ�.
						break;
					}
					else {//���� �̹� fringe�� �ִ� weight ������ ���� weight ���� �� Ŭ ���
						gList[fringe[j].id - 1][start] = -1;
						gList[start][fringe[j].id - 1] = -1;//�ش� fringe�� ���� parent ���� �����Ѵ�.
						break;
					}
				}
			}
			if (isMatch) {
				isMatch = false;
				continue;//���� fringe Ȯ���Ϸ� �̵��Ѵ�.
			}
			node tmpN = { nodeId, start + 1, gList[start][i] };//�̹� fringe�� �ִ� node�� �ƴѰ�� node data�� �����Ѵ�.
			fringe.emplace_back(tmpN);//���� fringe�� �����͸� �ִ´�.
		}

		heap* pq = new heap();//priority queue�� �����Ѵ�.
		int frinS = fringe.size();

		for (int i = 0; i < frinS; i++) {
			pq->push(this->fringe[i]);//fringe�� �ִ� ������ ��� priority queue�� �Է��Ѵ�.
		} 
		
		node shortest = pq->pop();//priority queue���� �ϳ��� ����.

		for (int i = 0; i < frinS; i++) {
			if (fringe[i].id == shortest.id) {
				fringe.erase(fringe.begin() + i);
				break;
			}
		}// �� ���� �ش��ϴ� fringe ���� fringe �迭���� �����.
		tree.emplace_back(shortest);//tree�� �ش� ��� ������ �Է��Ѵ�.

		gList[shortest.id - 1][start] = -1;
		for (int i = 0; i < structSize; i++) {
			gList[start][i] = -1;
		}//���� �� �ʿ���� �׷��� ������ �����.
		int treeS = tree.size() - 1;
		for (int i = 0; i < treeS; i++) {
			gList[shortest.id - 1][tree[i].id - 1] = -1;
		}//���� �� �ʿ���� �׷��� ������ �����.
		
		delete pq;
		return shortest;//priority queue�� ���� �� �̹��� tree�� �Է��� node�� ��ȯ�Ѵ�.
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int structInfo, walkingInfo, test;
	cin >> structInfo >> walkingInfo >> test;//������ ����, �� ������ ������ ���, ���� Ƚ���� �Է¹޴´�.
	
	vector<vector<int>> list;
	for (int i = 0; i < structInfo; i++) {
		vector<int> tmpVec(structInfo, -1);
		list.emplace_back(tmpVec);
	}//������ ������ ������ �迭 ��� �׷��� ������ �����Ѵ�.

	bool isThere = false;
	for (int i = 0; i < walkingInfo; i++) {
		int st1, st2, weight;
		cin >> st1 >> st2 >> weight;//������ ������ �Է¹޴´�.
		if (list[st1 - 1][st2 - 1] != -1) {//���� �ߺ��� ������ ���
			isThere = true;
		}
		if (isThere) {
			isThere = false;//�ߺ��� ������ ��� ���� �� �Է� ������ ����.
		}
		else {//�ߺ��� ������ �ƴ� ��� �׷����� �ش� ������ �Է��Ѵ�.
			list[st1 - 1][st2 - 1] = weight;
			list[st2 - 1][st1 - 1] = weight;
		}
	}

	for (int testCase = 0; testCase < test; testCase++) {//���� Ƚ����ŭ �ݺ��Ѵ�.
		char p;
		int start;
		cin >> p >> start;// ���� node id�� �Է¹޴´�.
		graph* g = new graph(list, start, structInfo);//graph�� �����ϰ� �׷���, ���� node id, ������ ����(�׷��� ������ ����)�� �Ѱ��ش�.

		vector<int> path;
		path.emplace_back(start);//��� �迭�� ���� node id�� �Է��Ѵ�.
		int totalWeight = 0;
		for (int i = 0; i < structInfo - 1; i++) {
			node n = g->trav();//������ ���� - 1 �� ��� Ž���� �����Ѵ�.
			path.emplace_back(n.id);//�Ź� ��ȯ�޴� ��� ����ü���� id���� path �迭�� �����Ѵ�.
			totalWeight += n.weight;//�Ź� ��ȯ�޴� ��� ����ü���� weight���� totalWeight���� ���ذ���.
		}
		cout << totalWeight;//�� ���� ����Ѵ�.

		int pathS = path.size();
		for (int i = 0; i < pathS; i++) {
			cout << " " << path[i];
		}//�� ��� ������ ������� ����Ѵ�.
		cout << "\n";
		delete g;//�׷��� ��ü �Ҵ��� �����Ѵ�
	}
	return 0;
}