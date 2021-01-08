#pragma once 
#ifndef GRAPH_H
#define GRAPH_H 


#include "da.h"
#include "queue.h"
#include "stack.h"
#include "llist.h" 
#include "pair.h"

const std::string G_INDEX_OUT_OF_RANGE_MESSAGE = "(G) Quack! Index out of range.";
const std::string G_NEGATIVE_SIZE_MESSAGE = "(G) Quack! Size < 0.";
const std::string G_ZERO_SIZE_MESSAGE = "(G) Quack! Size = 0.";
const std::string G_INCORRECT_GRAPH_MESSAGE = "(G) Quack! This operation cannot be performed on this graph.";



class Graph {
private:
	
	class Edge {
	private:
		int data = 1;
		int ver;
	public:
		Edge() { data = 1; ver = -1; };
		Edge(int ver, int data) { this->data = data; this->ver = ver; };
		virtual ~Edge() {};
		int getData() {
			return this->data;
		}
		int getVertex() {
			return this->ver;
		}
		bool operator==(Edge& other) {
			return (this->data == other.data) && (this->ver == other.ver);
		}
		bool operator!=(Edge& other) {
			return (this->data != other.data) || (this->ver != other.ver);
		}
	};
	
	class Vertex {
	private:
		LinkedList<Edge>* edges = nullptr;
		int color = 0;

	public:
		Vertex() { edges = new LinkedList<Edge>(); };
		/*bool findEdge(int ver, int data = 1) {
			Edge* tmp = new Edge(ver, data);
			return this->edges->find(*tmp);
		}*/
		void addEdge(int ver,int data = 1) {
			Edge* ed = new Edge( ver,data );
			this->edges->append(*ed);
		}
		int getEdgesCount() {
			return this->edges->getLength();
		}
		Edge getEdge(int i) {
			return this->edges->get(i);
		}
		int findEdge(int ver2) {
			for (int i = 0; i < this->getEdgesCount(); i++) {
				if (ver2 == this->getEdge(i).getVertex())
					return this->getEdge(i).getData();
			}
		}
		int getColor() {
			return this->color;
		}
		void setColor(int color) {
			this->color = color;
		}
		bool isNeighbor(int ver2) {
			for (int i = 0; i < this->getEdgesCount(); i++) {
				if (ver2 == this->getEdge(i).getVertex())
					return true;
			}
			return false;
		}
		
	};

	DynamicArray<Vertex*>* vertices = nullptr;
	bool weighted = false;
	bool directed = true;
	//int length = 0;

public:	
	// пустой граф
	Graph() { 
		vertices = new DynamicArray<Vertex*>();
		weighted = false;
		directed = true;
	};
	// грав из заданного количества вершин 
	Graph(int length) {
		//this->length = length;
		try	{ 
			this->vertices = new DynamicArray<Vertex*>(length); 
			weighted = false;
			directed = true;
		}
		catch (const std::exception& e) { throw e; }		
	} 
	// грав из заданного количества вершин 
	Graph(bool weight,bool direct) : Graph() {
		//this->length = length;
		try {
			this->directed = direct;
			this->weighted = weight;
		}
		catch (const std::exception& e) { throw e; }
	}
	Graph(int length,bool weight, bool direct) : Graph(length) {
		//this->length = length;
		try {			
			this->directed = direct;
			this->weighted = weight;
		}
		catch (const std::exception& e) { throw e; }
	}
	int getLength() {
		try { this->vertices->getLength(); }
		catch (const std::exception& e) { throw e; }		
	}
	bool getWeigth() {
		try { return this->weighted; }
		catch (const std::exception& e) { throw e; }
	}
	bool getDirect() {
		try { return this->directed; }
		catch (const std::exception& e) { throw e; }
	}
	//добавл€ем ребро, возврашаем его номер
	int addVertex() {
		Vertex* elem = new Vertex();
		try {
			this->vertices->append(elem);
			return vertices->getLength();
		}
		catch (const std::exception& e) { throw e; }
		
	}
	Vertex* get(int i) {
		return this->vertices->get(i);
	}
	//bool findEdge(int ver1,int ver2,int data = 1) {
	//	//for (int i = 0; i < this->getLength(); i++) {
	//		if (this->vertices->get(ver1).findEdge(ver2, data)) return true;
	//	//}
	//	return false;
	//}
	void addEdge(int ver1, int ver2, int data = 1) {
		if ((ver1 < 0) || (ver2 >= vertices->getLength())) throw std::out_of_range(G_INDEX_OUT_OF_RANGE_MESSAGE);
		if ((ver1 < 0) || (ver2 >= vertices->getLength())) throw std::out_of_range(G_INDEX_OUT_OF_RANGE_MESSAGE);
		try { 
			//if (!this->findEdge(ver1, ver2, data)) { // если такой дуги не было найдено
				this->get(ver1)->addEdge(ver2, data);
				// если граф не направленный - добавить дугу дл€ другого конца
				if (!this->directed) {
					this->get(ver2)->addEdge(ver1, data);
				}
			//}				
		}
		catch (const std::exception& e) { throw e; }		
	}
	// обход графа в ширину
	DynamicArray<int>* BFS(int ver1) {
		//int count_ver = this->getLength();
		DynamicArray<int>* res = new DynamicArray<int>(this->getLength());
		Queue<int>* queue = new Queue<int>(); // очередь вершин 
		DynamicArray<int>* visit = new DynamicArray<int>(this->getLength());
		for (int i = 0; i < this->getLength(); i++) {
			visit->append(0);
		}
		res->append(ver1);
		visit->set(1,ver1);
		queue->enqueue(ver1);
		while (queue->getLength() != 0) // пока очередь не пуста€ 
		{
			int ver = queue->dequeue();
			for (int j = 0; j < this->getLength(); j++) {
				// если €вл€етс€ соседом и ещЄ не была посещена
				if (this->get(ver)->isNeighbor(j) && (visit->get(j) == 0)) {
					res->append(j);
					visit->set(1, j);
					queue->enqueue(j);
				}
			}
		}			
		return res;
	}
	DynamicArray<int>* shortestPathBFS(int ver1,int ver2) {
		int i, j, ver;
		//DynamicArray<int>* res = new DynamicArray<int>(this->getLength()); // результат 
		DynamicArray<int>* visit = new DynamicArray<int>(this->getLength()); // вершины посещены или нет
		for (i = 0; i < this->getLength(); i++) {
			visit->append(0);
		}
		DynamicArray<int>* pred = new DynamicArray<int>(this->getLength()); // предшественники
		for (i = 0; i < this->getLength(); i++) {
			pred->append(-1);
		}
		Queue<int>* queue = new Queue<int>(); // очередь вершин 
		//res->append(ver1); 
		visit->set(1, ver1); 
		queue->enqueue(ver1); 
		while (queue->getLength() != 0) // пока очередь не пуста€ 
		{
			ver = queue->dequeue();
			for (j = 0; j < this->getLength(); j++) {
				// если €вл€етс€ соседом и ещЄ не была посещена
				if (this->get(ver)->isNeighbor(j) && (visit->get(j) == 0)) {
					//res->append(j);
					pred->set(ver,j);
					visit->set(1, j);
					queue->enqueue(j);
				}
			}
			//for (int j = 0; j < this->getLength(); j++) {}
			//for (int j = 0; j < this->getLength(); j++) {}
		}
		if (pred->get(ver2) == -1) return nullptr;
		Stack<int>* stack = new Stack<int>();
		stack->push(ver2);
		ver = ver2;
		while (pred->get(ver) != -1) { 
			ver = pred->get(ver);
			stack->push(ver);
		}
		int length = stack->getLength();
		DynamicArray<int>* res = new DynamicArray<int>(length);
		for (i = 0; i < length; i++) {
			res->append(stack->pop());
		}
		return res;
	}

	Pair< DynamicArray<int>*, DynamicArray<int>*> dijkstra(int ver1) {
		DynamicArray<int>* visit = new DynamicArray<int>(this->getLength());
		DynamicArray<int>* dist = new DynamicArray<int>(this->getLength());
		DynamicArray<int>* pred = new DynamicArray<int>(this->getLength());
		int i, t_min_dist; //текуща€ длина минимальной дистанции от стартовой вершины 
		int j;
		for (int i = 0; i < this->getLength(); i++) {
			visit->append(0);
			dist->append(INT_MAX);
			pred->append(-1);
		}
		visit->set(1, ver1); 
		for (i = 0; i < this->getLength(); i++) 
			if (this->get(ver1)->isNeighbor(i)) // если €вл€етс€ соседом
			{
				dist->set(this->get(ver1)->findEdge(i), i);
				pred->set(ver1, i);
			}
		while (true) {
			j = -1;
			t_min_dist = INT_MAX;
			for (i = 0; i < this->getLength(); i++)
				if (visit->get(i) == 0 && dist->get(i) < t_min_dist) {
					t_min_dist = dist->get(i);
					j = i;
				}
			if (j == -1) break; // не найдено необходимое рассто€ние 
			visit->set(1, j); // нашли и пометили как посещЄнный  
			//ƒл€ каждой непосещЄнной вершины i выполнить d[i] = min(d[i], d[j] + dist(j,i) 
			for (i = 0; i < this->getLength(); i++)
				if (visit->get(i) == 0 && this->get(j)->isNeighbor(i))
					if (dist->get(j) + this->get(j)->findEdge(i) < dist->get(i)) {
						dist->set(dist->get(j) + this->get(j)->findEdge(i), i);
						pred->set(j, i); //j - предшественник вершины i
					}
			//DynamicArray<int>* res = new DynamicArray<int>(this->getLength());
			//возвращаем пару - вершину и пару из двух дин. массивов) 
			
		}
		Pair< DynamicArray<int>*, DynamicArray<int>*> path = { pred, dist };
		//Pair<int, Pair< DynamicArray<int>*, DynamicArray<int>*>> res = { ver1, path };
		return path;
	}
	//возвращает массив пар (путь, длина)
	Pair< DynamicArray<int>*, int> dijkstra(int ver1, int ver2) {
		if (this->shortestPathBFS(ver1, ver2) == nullptr)
			throw std::logic_error(G_INCORRECT_GRAPH_MESSAGE);
		Pair< DynamicArray<int>*, DynamicArray<int>*> tmp = dijkstra(ver1);
		DynamicArray<int>* res_arr = new DynamicArray<int>(this->getLength());
		res_arr->append(ver1);
		additional_dijkstra(ver1, ver2, res_arr, tmp.first);
		Pair< DynamicArray<int>*, int> res = { res_arr, tmp.second->get(ver2) };
		return res;
	}
	//Pair< DynamicArray<int>*, int> dijkstra(int ver1,int ver2)
	void additional_dijkstra(int ver1, int ver2,DynamicArray<int>* res, DynamicArray<int>* pred) {
		if (pred->get(ver2) != ver1) additional_dijkstra(ver1, pred->get(ver2), res, pred);
		res->append(ver2);
	}
	DynamicArray<Pair<int, int>>* painting() {
		DynamicArray<Pair<int,int>>* res = new DynamicArray<Pair<int, int>>(this->getLength());
		Queue<int>* queue = new Queue<int>(); // очередь вершин 
		DynamicArray<int>* visit = new DynamicArray<int>(this->getLength());
		for (int i = 0; i < this->getLength(); i++) {
			visit->append(0);
		}
		int countcolor = 0;
		//res->append(0);
		visit->set(1, 0);
		queue->enqueue(0);
		while (true)	{
			while (queue->getLength() != 0) // пока очередь не пуста€ 
			{
				int ver = queue->dequeue();
				for (int j = 0; j < this->getLength(); j++) {
					// если €вл€етс€ соседом и ещЄ не была посещена
					if ((this->get(ver)->isNeighbor(j)|| this->get(j)->isNeighbor(ver)) && (visit->get(j) == 0)) {
						//res->append(j);
						visit->set(1, j);
						queue->enqueue(j);
					}
				}
				if (countcolor < 2) {
					countcolor++;
					//если цвет только 1 или его нет совсем 
					this->vertices->get(ver)->setColor(countcolor);
					this->vertices->get(ver);
					Pair<int, int> tmp = { ver,countcolor };
					res->append(tmp);
				}
				else {
					DynamicArray<int>* colors = new DynamicArray<int>(countcolor);
					for (int i = 0; i < countcolor; i++) {
						colors->append(0);
					}
					for (int j = 0; j < this->getLength(); j++)
						// если €вл€етс€ соседом и была посещена (покрашена)					
						if ((this->get(ver)->isNeighbor(j) || this->get(j)->isNeighbor(ver)) && (visit->get(j) != 0))
							if (this->get(j)->getColor() != 0)
								//цвет этой вершины ≈—“№ и он зан€т
								colors->set(1, this->get(j)->getColor() - 1);
					for (int j = 0; j < countcolor; j++)
						if (colors->get(j) == 0) {
							this->get(ver)->setColor(j+1);
							Pair<int, int> tmp = { ver,j+1 };
							res->append(tmp);
							break;
						}
					if (this->get(ver)->getColor() == 0) {
						countcolor++;
						this->get(ver)->setColor(countcolor);
						Pair<int, int> tmp = { ver,countcolor };
						res->append(tmp);
					}
				}
			}
			if (res->getLength() == this->getLength())
				break;
			else {
				for (int i = 0; i < getLength(); i++)
				{
					if (visit->get(i) == 0)
					{
						visit->set(1,i);
						queue->enqueue(i);
						break;
					}
				}
			}
		}
		return res;
	}
};


#endif // !GRAPH_H
