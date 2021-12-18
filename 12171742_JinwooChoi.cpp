#include <iostream>
#include <vector>

using namespace std;

struct node {
	int id;
	int parent;
	int weight;
};//node struct 정의, 조형물 번호, 연결된 조형물 번호, 디자인 비용을 원소로 가진다. 

class heap {
private:
	vector<node> nodes;//array 기반으로 heap을 구현한다.

public:
	heap() {
		node n = { 0, 0, 0 };
		nodes.emplace_back(n);//최초 0번째 index는 안쓰기 위해 임의의 값을 입력한다.
	}

	void upHeap(int child) {//입력시 비교하면서 자리 찾아가는 함수
		int parent = child / 2;//parent index 값을 정의한다.
		if (parent < 2) {//parent index가 2보다 작은경우 비교를 종료한다.
			return;
		}
		if (nodes[parent].weight < nodes[child].weight) {//parent 값의 weight가 child 값의 weight값보다 작은경우 비교를 종료한다.
			return;
		}
		else if (nodes[parent].weight == nodes[child].weight) {//parent 값의 weight가 child값의 weight값과 같은 경우
			if (nodes[parent].id > nodes[child].id) {//parent의 id가 node의 id보다 큰 경우 
				node tmp = nodes[parent];
				nodes[parent] = nodes[child];
				nodes[child] = tmp;//parent 값을 child 값과 swap 한다.
				if (parent == 1) {//parent가 root node일 경우 비교를 종료한다.
					return;
				}
				this->upHeap(parent);//root node 아닐 경우 다시한번 비교하러 간다.
			}
			else {
				return;//parent의 id가 node의 id보다 작은 경우 바로 비교를 종료한다.
			}
		}
		else {//parent의 weight 값이 child의 weight 값보다 큰 경우
			node tmp = nodes[parent];
			nodes[parent] = nodes[child];
			nodes[child] = tmp;//parent 값을 child 값과 swap 한다.
			if (parent == 1) {//parent가 root node일 경우 비교를 종료한다.
				return;
			}
			this->upHeap(parent);//root node 아닐 경우 다시한번 비교하러 간다.
		}
		return;
	}

	void downHeap(int parent) {//삭제 시 root node의 값 찾기위해 실행되는 함수
		int comp = 0;
		int index = 0;
		int nodesS = nodes.size() - 1;
		if (parent * 2 > nodesS) {//parent의 왼쪽 child의 index 값이 heap의 size보다 큰 경우 비교를 종료한다.
			return;
		}
		else if (parent * 2 == nodesS) {//heap의 size와 parent의 왼쪽 child의 index 값이 같은 경우
			comp = nodes[parent * 2].weight;
			index = parent * 2;//비교값과 해당 index를 parent의 왼쪽 child로 설정한다.
		}
		else if (nodes[parent * 2].weight > nodes[parent * 2 + 1].weight) {//왼쪽 child의 weight 값이 오른쪽 child의 weight 값보다 클 경우
			comp = nodes[parent * 2 + 1].weight;
			index = parent * 2 + 1;//비교값과 해당 index를 parent의 오른쪽 child로 설정한다.
		}
		else if (nodes[parent * 2].weight == nodes[parent * 2 + 1].weight) {//왼쪽 child의 weight 값이 오른쪽 child의 weight 값과 같을 경우
			if (nodes[parent * 2].id > nodes[parent * 2 + 1].id) {//왼쪽 child의 id 값이 오른쪽 child의 id 값보다 클 경우
				comp = nodes[parent * 2 + 1].weight;
				index = parent * 2 + 1;//비교값과 해당 index를 parent의 오른쪽 child로 설정한다.
			}
			else {//왼쪽 child의 id 값이 오른쪽 child의 id 값보다 작을 경우
				comp = nodes[parent * 2].weight;
				index = parent * 2;//비교값과 해당 index를 parent의 왼쪽 child로 설정한다.
			}
		}
		else {//왼쪽 child의 weight 값이 오른쪽 child의 weight 값보다 작을 경우
			comp = nodes[parent * 2].weight;
			index = parent * 2;
		}//비교값과 해당 index를 parent의 왼쪽 child로 설정한다.

		if (comp > nodes[parent].weight) {//비교값이 parent의 weight 값보다 클 경우 비교를 종료한다.
			return;
		}
		else if (comp == nodes[parent].weight) {//비교값이 parent의 weight 값과 같을 경우 
			if (nodes[index].id > nodes[parent].id) {//해당 비교값을 가진 child의 id 값이 parent의 id값보다 클 경우 비교를 종료한다.
				return;
			}
			else {//해당 비교값을 가진 child의 id 값이 parent의 id값보다 작을 경우
				node tmpN = nodes[index];
				nodes[index] = nodes[parent];
				nodes[parent] = tmpN;//해당 비교값을 가진 child와 parent를 swap한다.
				downHeap(index);//다시한번 비교함수를 호출한다.
			}
		}
		else {//비교값이 parent의 weight 값보다 작을 경우
			node tmpN = nodes[index];
			nodes[index] = nodes[parent];
			nodes[parent] = tmpN;//해당 비교값을 가진 child와 parent를 swap한다.
			downHeap(index);//다시한번 비교함수를 호출한다.
		}
		return;
	}

	void push(node val) {//heap에 새로운 원소 입력하는 함수
		nodes.emplace_back(val);//기반 배열에 원소를 입력한다.
		if (nodes.size() == 2) {//만약 root node라면 별도 작업없이 종료한다.
			return;
		}
		upHeap(nodes.size() - 1);//root node가 아니라면 비교함수를 호출한다.
	}

	node pop() {//heap에서 최소값을 빼고 해당 값을 return 하는 함수
		node top = this->nodes[1];// root node의 값을 저장한다.
		if (nodes.size() == 2) {//root node밖에 없을 경우
			nodes.pop_back();//삭제 후 해당 값 반환한다.
			return top;
		}
		nodes[1] = nodes.back();
		nodes.pop_back();//root node 아니라면 맨 마지막 값을 root node로 옮긴 후 해당 마지막 값의 위치를 삭제한다.
		downHeap(1);//비교함수를 호출한다.
		return top;//함수 종료 후 최소 값을 반환한다.
	}

	int size() {
		return this->nodes.size() - 1;
	}//0번째 노드 제외하고 실제 데이터 개수 반환해주는 함수
};


class graph {
private:
	vector<node> tree;//tree group
	vector<node> fringe;//fringe group
	vector<vector<int>> gList;//전체 그래프 데이터
	int structSize = 0;//그래프 데이터의 가로(세로) 값
public:
	graph(vector<vector<int>> list, int start, int size) {
		gList = list;
		structSize = size;
		node root = {start, 0, 0};
		tree.emplace_back(root);//생성자에서 그래프 데이터와 가로(세로)값을 받아오고 start vertex를 받아서 tree에 넣어준다.
	}

	node trav() {
		int start = tree.back().id - 1;//start node index
		int fSize = fringe.size();
		for (int i = 0; i < structSize; i++) {//start node와 다른 모든 node들을 확인하고 연결 되어있다면 fringe에 넣는다.
			bool isMatch = false;
			if (gList[start][i] == -1) {//연결되지 않았으면 다음 node를 확인한다.
				continue;
			}
			int nodeId = i + 1;
			for (int j = 0; j < fSize; j++) {//이미 fringe에 들어간 node인지 검사한다.
				if (nodeId == fringe[j].id) {//만약 이미 fringe에 있을 경우
					isMatch = true;
					if (gList[start][i] < fringe[j].weight) {//또한 이미 fringe에 있는 weight 값보다 현재 weight 값이 더 작을경우
						gList[fringe[j].id - 1][fringe[j].parent - 1] = -1;//해당 fringe의 이전 parent 값을 삭제한다.
						fringe[j].weight = gList[start][i];
						fringe[j].parent = start + 1;//fringe parent, weight 값을 update 한다.
						break;
					}
					else {//또한 이미 fringe에 있는 weight 값보다 현재 weight 값이 더 클 경우
						gList[fringe[j].id - 1][start] = -1;
						gList[start][fringe[j].id - 1] = -1;//해당 fringe의 현재 parent 값을 삭제한다.
						break;
					}
				}
			}
			if (isMatch) {
				isMatch = false;
				continue;//다음 fringe 확인하러 이동한다.
			}
			node tmpN = { nodeId, start + 1, gList[start][i] };//이미 fringe에 있는 node가 아닌경우 node data를 생성한다.
			fringe.emplace_back(tmpN);//이후 fringe에 데이터를 넣는다.
		}

		heap* pq = new heap();//priority queue를 선언한다.
		int frinS = fringe.size();

		for (int i = 0; i < frinS; i++) {
			pq->push(this->fringe[i]);//fringe에 있는 노드들을 모두 priority queue에 입력한다.
		} 
		
		node shortest = pq->pop();//priority queue에서 하나만 뺀다.

		for (int i = 0; i < frinS; i++) {
			if (fringe[i].id == shortest.id) {
				fringe.erase(fringe.begin() + i);
				break;
			}
		}// 뺀 값에 해당하는 fringe 값을 fringe 배열에서 지운다.
		tree.emplace_back(shortest);//tree에 해당 노드 정보를 입력한다.

		gList[shortest.id - 1][start] = -1;
		for (int i = 0; i < structSize; i++) {
			gList[start][i] = -1;
		}//연결 후 필요없는 그래프 정보를 지운다.
		int treeS = tree.size() - 1;
		for (int i = 0; i < treeS; i++) {
			gList[shortest.id - 1][tree[i].id - 1] = -1;
		}//연결 후 필요없는 그래프 정보를 지운다.
		
		delete pq;
		return shortest;//priority queue를 해제 후 이번에 tree에 입력한 node를 반환한다.
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int structInfo, walkingInfo, test;
	cin >> structInfo >> walkingInfo >> test;//조형물 정보, 그 사이의 디자인 비용, 질문 횟수를 입력받는다.
	
	vector<vector<int>> list;
	for (int i = 0; i < structInfo; i++) {
		vector<int> tmpVec(structInfo, -1);
		list.emplace_back(tmpVec);
	}//조형물 정보를 유지할 배열 기반 그래프 구조를 생성한다.

	bool isThere = false;
	for (int i = 0; i < walkingInfo; i++) {
		int st1, st2, weight;
		cin >> st1 >> st2 >> weight;//조형물 정보를 입력받는다.
		if (list[st1 - 1][st2 - 1] != -1) {//만약 중복된 정보일 경우
			isThere = true;
		}
		if (isThere) {
			isThere = false;//중복된 정보일 경우 다음 번 입력 받으러 간다.
		}
		else {//중복된 정보가 아닐 경우 그래프에 해당 정보를 입력한다.
			list[st1 - 1][st2 - 1] = weight;
			list[st2 - 1][st1 - 1] = weight;
		}
	}

	for (int testCase = 0; testCase < test; testCase++) {//질의 횟수만큼 반복한다.
		char p;
		int start;
		cin >> p >> start;// 시작 node id를 입력받는다.
		graph* g = new graph(list, start, structInfo);//graph를 선언하고 그래프, 시작 node id, 구조물 개수(그래프 구조의 가로)를 넘겨준다.

		vector<int> path;
		path.emplace_back(start);//경로 배열에 시작 node id를 입력한다.
		int totalWeight = 0;
		for (int i = 0; i < structInfo - 1; i++) {
			node n = g->trav();//구조물 개수 - 1 번 경로 탐색을 수행한다.
			path.emplace_back(n.id);//매번 반환받는 노드 구조체에서 id값을 path 배열에 저장한다.
			totalWeight += n.weight;//매번 반환받는 노드 구조체에서 weight값을 totalWeight값에 더해간다.
		}
		cout << totalWeight;//총 합을 출력한다.

		int pathS = path.size();
		for (int i = 0; i < pathS; i++) {
			cout << " " << path[i];
		}//각 경로 정보를 순서대로 출력한다.
		cout << "\n";
		delete g;//그래프 객체 할당을 해제한다
	}
	return 0;
}